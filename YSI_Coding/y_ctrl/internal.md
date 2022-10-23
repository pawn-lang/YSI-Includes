# *y_ctrl* Internal Details

## Introduction

This tutorial will cover several aspects of *y_ctrl* in great detail, as it is an excellent entry
point in to several advanced techniques, including `#emit`, `@emit`, disassembly, and code scanning.
The most important first part is to understand what the library actually does, and what control
registers are.

Control registers are special bits of memory that when written to (or sometimes read from) do
something more than just return a value.  All computers have these, they are a fundamental part of
writing drivers and other low-level code.  For example: starting a CPU timer is done by writing a
value to a special address, sending data to a USB device is done by writing it to a special memory
location, even basic rendering is done via special registers.  Sometimes these registers are
actually memory addresses and written to in the normal way, and sometimes there is a separate list
of "addresses" for these registers accessed using a different instruction.

In pawn the special registers hold information such as the current instruction pointer (CIP, which
instruction is currently being run), the stack pointer, offsets to the start of the code and data
segments, and more.  There are seven by default, numbered `0` to `6`.  The crashdetect plugin adds
registers `0xFF` and `0xFE` for sending it instructions (as opposed to using normal functions since
the plugin is optional and may not exist).  These registers are read using `LCTRL` and written using
`SCTRL`.  The read result is placed in `pri` and the write data is (usually) read from `pri`:

```pawn
// Get the file offset to the start of the data segment.
#emit LCTRL        __dat     // 1
// `pri` now holds the offset.

// Increase the stack pointer (register 4) by 8.
#emit LCTRL        __stk     // 4
#emit ADD.C        __2_cells // 8
#emit SCTRL        __stk     // 4
```

For the purposes of this library the most important difference is that `pri` doesn't change when you
use `SCTRL` (so needs restoring), while `LCTRL` does change.  Other than that, since the two are so
similar we can simply ignore half the code for the purposes of documentation and instead concentrate
on `LCTRL`.

One important note - the library only handles register numbers over 255.  Anything in the range
0-255 is reserved for the VM and plugins.

## Decorator

Previously YSI would introduce new function types with new keywords such as `hook`, `timer`,
`global`, etc.  But this causes issues with the compiler specifically if it too adds new features
with the same keywords, and other libraries more generally as they can have macros or variables
with the same name as well.  Most of these functions aren't even really worthy of a new language
feature (which is what a keyword would be for).  A lower tier of introduction is the tags used by
libraries such as *y_commands* (`YCMD:`), but this too is wrong - they aren't tags they function
modifiers msquerading as tags.  So we need something that doesn't look like another language
feature (keywords and tags), isn't likely to conflict with future updates, yet still indicates the
special status and processing of the function.  Fortunately, other languages have already solved
this in the form of *decorators* (also know as "annotations").

A decorator appears next to a function to indicate that it does something special, but can be
defined by libraries not just the compiler.  They have a variety of syntaxes, but the one settled on
for pawn is `@name(optional, parameters)`.  Because of compiler limitations these have to go on the
same line as the function (unlike like in most languages).  So the code to declare a new `LCTRL`
handler becomes:

```pawn
@lctrl(300) Handler()
{
}
```

`@lctrl` is the `LCTRL` declaration decorator; `300` is the number of register being defined; and
`Handler` is the name of the processing function - it isn't used here but must exist to be a valid
function definition.

The definition for the decorator is:

```pawn
#define @lctrl(%0)%1(%2) @y_L%0(); @y_L%0() { return %1(0, 0); } %1(%2)
```

`%0` is the number of the control register; `%1` is the function name; and `%2` are the names of the
parameters passed to the processing function, of which there are always two - `pri` and `alt` for
the respective registers.

`@y_L` is a standard YSI function prefix.  The leading `@` makes the function public, the `y` is
just because YSI, the `_` is to separate parts, and the `L` is a unique identifier for this
feature (in fact the uniqueness is both that letter and the order of `y`/`_`/`L`).  The prefix is
both highly unique, being unlikely to conflict with anything else (if someone else adopts this
technique, please use another letter besides `y`), and exactly four letters long.  This makes
searching for functions that start with this sequence in the AMX header very quick and easy as four
bytes are one cell, so the prefix can be scanned for using simple numeric comparisons instead of
complex string comparisons (made more complicated by strings in the AMX header being partially
reversed).

The public function defines the register number by its name (thus defines will not work in the
decorator) and calls the implementing function (the handler).  At this stage only dummy data
(`0, 0`) is given for `pri` and `alt`, the call merely exists to be found and manipulated later.
The value from the handler function `%1` is returned from the public function to ensure that the
compiler enforces users return a value.  `LCTRL` handlers must by definition return something,
because they are *Load ConTRoL register* functions.  Adding `return` here will give a warning if the
handler function doesn't also contain `return`.  `SCTRL` shouldn't return a value and so it discards
any returned values and doesn't require the handler to contain `return`:

```pawn
#define @sctrl(%0)%1(%2) @y_S%0(); @y_S%0() { %1(0, 0); } %1(%2)
```

## Header

```pawn
#define @y_L%0\32; @y_L
```

This is just a standard space consuming macro.  It matches `@y_L` (the function prefix) on its own.
A macro called `A` will not match `AA`, similarly this macro called `@y_L` will not match
`@y_LHandler`.  `%0\32;` then matches anything up to the next space (`\32` being the decimal code
for the space character) and deletes it.  The space should be the very next character, but the `%0`
is always required because of compiler limitations.  The net result is that this macro turns
`@y_L Handler` (with a space) in to `@y_LHandler` (without one).  This technique is again seen all
over YSI and is the reason why many macros work regardless of spacing.

```pawn
static stock
	YSI_g_sBaseRelocation,
	YSI_g_sLCTRLStubAddress;

#define CALL@CTRL_LCTRLStub%8() CTRL_LCTRLStub%8()
```

These are both to do with `addressof`.  `addressof`, from *amx_assembly*, returns the address in the
AMX of a function (hence the name).  However, because it is a compiler hack it needs to know how the
function is called (but never does call it).  This is done by a macro starting `CALL@`, then the
name of the function being called - in this case `CTRL_LCTRLStub`.  `CTRL_LCTRLStub` takes no
parameters, so the result of the macro is the empty call `CTRL_LCTRLStub()`.

Because the return of `addressof` is then modified (to be relative to the server base address
instead of the AMX base address) the result is cached in `YSI_g_sLCTRLStubAddress`.

## `OnCodeInit`

`OnCodeInit` is called when the script is first loaded.  This could be `OnFilterScriptInit`,
`OnGameModeInit`, `OnNPCModeInit`, or `OnJITInit` (currently), and is called before the main
initialisation code is run in `OnScriptInit`.  Because YSI itself uses this callback to set some
things up many features such as `hook` and `inline` do not work yet within this callback.

```pawn
YSI_g_sBaseRelocation = -DisasmReloc(0);
YSI_g_sLCTRLStubAddress = addressof (CTRL_LCTRLStub) + 4 + YSI_g_sBaseRelocation;
```

This is where the address of `CTRL_LCTRLStub` is looked up (what this function does will be
explained later).  `DisasmReloc` is normally used when analysing code to convert the server absolute
addresses found the assembly after the script loads back to the script absolute addresses found in
the AMX stored on disk (the VM relocates all jumps on script load).  Here it is slightly abused by
getting the script address of the server address naught and negating it to be able to perform the
same relocations as the VM does.

`addressof` gets the address of the start of the function (in the AMX), `+ 4` skips over the first
instruction (usually `PROC`, and definitely `PROC` for this function), and `+ YSI_g_sBaseRelocation`
performs the previously mentioned relocation to get the real address in the server of the function,
rather than the logical address in the script.

## Code Scanner

A code scanner scans code.  It is a way to search through the compiled running code for specific
patterns of assembly, with basic wildcards.  The scanner to detect an unknown function called with
no parameters would be:

```pawn
CodeScanMatcherPattern(matcher,
	OP(PUSH_C, 0)
	OP(CALL, ???)
);
```

The syntax is entirely custom.  Note the lack of commas between the `OP`s, the use of `???` for an
unknown operand, and the essential use of separate lines for each opcode, the `_` instead of `.` in
the opcode name, and the use of all upper-case letters for the opcode.  These are all essential
parts of the syntax, it is sadly not very flexible.

While a matcher as seen above looks for one single pattern, a scanner often consists of multiple
matchers.  These might look for subtle variations on the same compiled code, different sections of
the same long code, or as here entirely independent bits of code.  One or more matchers are added to
a scanner, then the scanner is run; looping through the entire compiled assembly and carefully
comparing each address to all the matchers.  Once code matching a given pattern is found the
callback for that matcher is found.  The scanner also tracks stack sizes through `PUSH`/`POP`s,
`CALL`s, `JUMP`s, and more; and this additional data is also provided to the match callback.

The scanner here only needs to find single `LCTRL`s and single `SCTRL`s so there are just two
matchers.  It also matches all `LCTRL`s and `SCTRL`s regardless of the value of their parameter, so
this is left as a wildcard (`???`):

```pawn
new scanner[CodeScanner];
CodeScanInit(scanner);

new lctrl[CodeScanMatcher];
CodeScanMatcherInit(lctrl, &CTRL_FoundLCTRL);
CodeScanMatcherPattern(lctrl,
	OP(LCTRL, ???)
);
CodeScanAddMatcher(scanner, lctrl);

CodeScanRun(scanner);
```

`&CTRL_FoundLCTRL` is optional syntax for `addressof (CTRL_FoundLCTRL)` when the type of the
function is known in advance, and when the receiving function (`CodeScanMatcherInit`) enables the
syntax.  This is why `#define CALL@CTRL_FoundLCTRL%8() CTRL_FoundLCTRL%8(something)` isn't needed.

`CodeScanInit` declares the overall scanner.  `CodeScanMatcherInit` declares a single pattern.
`CodeScanMatcherPattern` defines the pattern for the matcher.  `CodeScanAddMatcher` adds the
matcher to the scanner.  `CodeScanRun` runs the scanner, and thus all the added matchers.

When an `LCTRL` is found the function `CTRL_FoundLCTRL` is called, and is passed information
relating to the location of the opcode, its parameters, the stack, and more.  But this will come.

## `AMX_GetPublicPointerPrefix`

This is where we start exploiting the earlier mention of the fact that `@y_L` is exactly four bytes,
so one cell.  `AMX_GetPublicPointerPrefix` returns a `Pointer` to a `Public` function, filtering
only for those that start with a given `Prefix`.  `AMX_GetPublicPrefix` would return the name and
`AMX_GetPublicEntryPrefix` would return the address in the AMX header of the public function
information table.  There are also `Get` functions for `Tag`s, `PubVar`s, and `Native`s.  The loop
works by starting at public table index `0` (in `idx`) and each iteration returns the next index to
check.  Once there are no more publics to check the value returned is `0` again and the loop ends.

So `idx` is the next public index to check, `addr` is the address returned when there is a match,
and `_A<@y_L>` is the prefix to scan for, but how is it?  `_A<>` is a macro similar to `_H<>` or
`_I<>` from *y_stringhash*, or `_C<>` also from *y_amx*, which converts a string to a number at
compile-time.  This is equivalent to doing:

```pawn
new prefix = ('@' << 0) | ('y' << 8) ('_' << 16) ('L' << 24);
```

But much simpler, and without needing to remember the endianness of the string.  `_C<>` is the same,
but for the opposite endianness - `_A<>` produces C strings, `_C<>` produces packed pawn strings
(it's *A* for *AMX* as opposed to *C* for *C* if that rightfully seems confusing).  These two macros
are also carefully tuned for exactly this use-case - `@`, `_`, and `y`, the three characters in
every single prefix in YSI, are given the highest priority in pre-processor macro matches to
reduce the size of intermediate code.  The end-result in the AMX is a single number, thanks to the
way the compiler shrinks tags and does basic maths at compile-time; though the interim stages can be
quite large.  For example:

```pawn
new prefix = (_:he:@E_:(_:he:@E_:@E@:(_:he:(_:he:@E_:@E@:@Ey:@EA:@EB:@EC:@ED:@EE:@EF:@EG:@EH:@EI:@EJ:@EK:(_:0)|76<<0+8+8+8)|95<<0+8+8)|121<<0+8)|64<<0);
```

Becomes:

```pawn
new prefix = 1281325376;
```

This number, stored as little-endian, becomes identical to the C string `@y_L`.  And because it is a
number not a string, faster comparisons can be used when looping through the header to determine if
the start of a function name matches it.

Once each public function is found, the pointer to the function is passed on to another function
which does some code rewriting within it:

```pawn
new
	idx = 0,
	addr;
while ((idx = AMX_GetPublicPointerPrefix(idx, addr, _A<@y_L>)))
{
	CTRL_WriteLCTRLStub(addr);
}
```

It is important that finding these publics is done after the code scanning.  Well, actually it
isn't...  *y_hooks* uses some very similar code to search for functions starting with `@yH_` to list
all the hooks for specific callbacks.  In both cases the public functions aren't actually "used".
The special prefix is only used in `OnCodeInit`, as mentioned above, to find these defined functions
and they are only `public` to enable this.  Normal functions aren't named, the compiler removes that
information because a computer doesn't need it, it just calls things by address alone.  This
scanning functionality needs the name so needs a function type that keeps its name - i.e. public
functions, those already called by name through the VM.  This is why features like `SetTimer` and
`CallLocalFunction` can work using a string.  Despite needing the name for this initialisation, the
special functions here and in *y_hooks* are never normally called by name; only their addresses are
used in code generation.  Thus *y_hooks* actually removes the functions from the header once it has
finished initialisation (see `Hooks_InvalidateName` and `Hooks_SortPublics`) to speed up lookups for
real `public` functions later on.  *y_ctrl* could do the same thing, but currently doesn't.  If it
did this replacement would have to be after the code generation to ensure the code generation
worked.

## Trampolines

The code handlers have the signature:

```pawn
Handler(pri, alt)
```

And `LCTRL` handlers return a value that should be stored in `pri`.  Calling a function involves
pusing the parameters, pushing the byte size of the parameters, calling the function, then saving
the result.  `LCTRL` also needs to ensure that `alt` is the same before and after the call.  This
means calling a handler looks something like this:

```asm
PUSH.alt           ; Save a copy of `alt`.
PUSH.alt           ; Pass `alt` as a parameter to the function.
PUSH.pri           ; Pass `pri` as a parameter to the function.
PUSH.C     8       ; Push the size of the parameters.
CALL       Handler ; Call the handler.
; After the function, execution returns to here.
POP.alt            ; Restore the copy of `alt`.
; Now do something with the return value in `pri`.
```

That should be nice and easy, but isn't.  The problem is that we scan the code for `LCTRL ???` and
replace that single opcode with a call to the handler.  There's no space for any more code to be
inserted without moving a lot of other code around.  Eight cells of code isn't going to fix in two
cells of space - we need a *trampoline*.

A *trampoline* is a short simple function that calls a more complex one, or otherwise redirects code
execution.  The `LCTRL ???` is replaced by `CALL Trampoline`, and that code handles pushing
parameters and sizes, calling the handler, and restoring `alt`.  Normally a function with no
parameters would be called as:

```asm
PUSH.C     0       ; Push the size of the parameters.
CALL       Func    ; Call the function.
```

But there isn't even space to put the `PUSH.C 0`, so the trampoline needs to be written carefully to
be aware of the fact that it was called incorrectly.  `RETN` (the assembly version of `return`)
expects the size of the parameters to have been pushed, and without that will just see rubbish as
the parameter count and corrupt the stack.  So the trampoline must modify its own frame (the part of
the stack with the current function's parameters) to re-insert the parameter size.  With all that
extra effort the obvious question is "Why not use `JUMP` instead of `CALL`?"  `JUMP` doesn't need
parameters or counts, and is only two cells.  The reason is:

```asm
; After the function, execution returns to here.
```

`JUMP` just goes somewhere else, it can't return to where it was called from.  `CALL` saves the
return address for `RETN` to go back to later.  The other option would be to not use `RETN` at the
end of the trampoline, and instead restore the calling function's frame pointer and jump to the
return address manually (this time using `JUMP`, or more likely `SCTRL 6`).  This avoids the
parameter count problem, but causes many more issues with keeping `pri` and `alt` correct - you
can't invoke `SCTRL 6` AND maintain the return value, they both need `pri`.

### Short `CALL` Stack

The original plan was to replace the `@y_L` public function's code with a trampoline specific to
that one handler, but there was too much code to fit in (if someone can do it, please let me know).
Although the basic call is only eight cells, the trampoline with its stack modifications is slightly
longer and doesn't fit in the space afforded by that short function call at `-O1 -d0`.  Another
option is to just insert more dummy code in to the public to make it slightly longer and provide
some more code generation space.  However, the method opted for was to replace the `LCTRL` with a
`CALL` to a trampoline function replacing the original public, and in there push a pointer to the
final handler then `JUMP` to the full trampoline code (thus only requiring one instance of that
code).  The jump address is the modified one obtained earlier.  Thus the code within the public
becomes nothing more than:

```asm
PUSH.C     handlerAddress
JUMP       YSI_g_sLCTRLStubAddress
```

`CALL` pushes the return address, this code pushes the target address, so the state of the stack by
the time the trampoline is called looks like:

| Frame offset         | Contents             |
| -------------------- | -------------------- |
| ???                  | Return Address       |
| ??? - 4              | Handler Address      |

A function normally starts with `PROC`, which updates the frame pointer.  It hasn't yet been called,
so the offsets are still unknown.  Normally before `PROC` the stack would look like:

| Frame offset         | Contents             |
| -------------------- | -------------------- |
| ??? + N              | Parameters           |
| ???                  | Parameter Size       |
| ??? - 4              | Return Address       |

And after `PROC` saving the previous frame address and updating to the new one:

| Frame offset         | Contents             |
| -------------------- | -------------------- |
| 12+                  | Parameters           |
| 8                    | Parameter Size       |
| 4                    | Return Address       |
| 0                    | Previous Frame       |

So this is the target.  The handler address is a parameter to the function, as are both `pri` and
`alt`.

### Trampoline Code

As explained above the jump skips the `PROC` at the start of the function so the first instructions
continue operating in the previous function's stack frame:

```pawn
// The call to this function skips the `PROC` - we don't want it.
```

Push more "parameters" to the function, i.e. save `pri` and `alt` for later:

```pawn
// Save `pri` and `alt.
#emit PUSH.alt
#emit PUSH.pri
```

The stack now looks like:

| Frame offset         | Contents             |
| -------------------- | -------------------- |
| ???                  | Return Address       |
| ??? -  4             | Handler Address      |
| ??? -  8             | alt                  |
| ??? - 12             | pri                  |

These are treated as the parameters to the function and now the standard entry can be done.  First
the parameter size is pushed (`16`).  Then normally `CALL` would happen to push the return address
but we already have the return address from a `CALL` earlier so push a placeholder.  Then correctly
start the function with `PROC`:

```pawn
// We can finally "enter" the function.
#emit PUSH.C           16
#emit PUSH.pri
#emit PROC
```

`PROC` updates the frame pointer, so the stack is now:

| Frame offset         | Contents             |
| -------------------- | -------------------- |
| 24                   | Return Address       |
| 20                   | Handler Address      |
| 16                   | alt                  |
| 12                   | pri                  |
| 8                    | Parameter Size (16)  |
| 4                    | Placeholder Return   |
| 0                    | Previous Frame       |

Calling `RETN` at this point will fail because although we have the return address stored, it is in
the wrong place, so fix that and replace the "Placeholder Return" (address `+4`) with the real
return (address `+24`):

```pawn
// Get the return address.
#emit LOAD.S.pri       24
#emit STOR.S.pri       4
```

At this point the trampoline's stack is correct and the function is fully entered.  We have
succeeded in calling a function with just two cells of space.  The next job is to call the handler
stored in "Handler Address" (address `+20`).  This will be called more correctly, so first push the
parameters and size to that function.  This pushes the saved copies of `pri` and `alt` from the
trampoline's parameters.  `PUSH.alt` and `PUSH.pri` won't work any more as too much other code has
been done in the interim and has changed their values.  The values of `pri` and `alt` passed in
need to be the values they had before the original `LCTRL ???` instruction:

```pawn
// Push the `pri` and `alt` parameters.
#emit PUSH.S           16
#emit PUSH.S           12
#emit PUSH.C           8
```

Now call the function by pointer.  `CALL` won't work as that takes a constant so the functionality
of `CALL` is replicated - pushing the return address and then updating the current instruction
pointer (the `CIP`).  `CALL`, `JUMP`, and other instructions work by modifying `CIP`, which means
when the next instruction is read it is read from a totally different location.  `CIP` can also be
written to directly, ironically using `SCTRL 6`.  So the moment `SCTRL 6` finishes the next
instruction will be somewhere else entirely (the code scanner library is aware of this trick and
treats it the same as `CALL`).  But before that the return address needs to be pushed, and needs to
be the address of the instruction immediately following the `SCTRL 6`:

```pawn
#emit LCTRL            6
#emit ADD.C            36
#emit LCTRL            8
```

`LCTRL 6` gets the value of `CIP` (technically the value of `CIP` at the END of that instruction, so
really a pointer to the `ADD.C 36` instruction).  There are nine cells, thirty-six bytes, between
the end of the `LCTRL 6` instruction and the end of the `SCTRL 6` instruction, so that is the
modification needed to be made.  Then `LCTRL 8` is called, but didn't we earlier say there were only
seven control registers, numbered `0` to `6`?  What is this one?  `LCTRL 8` is a register in the JIT
plugin that takes a pawn code address and translates it to a JIT code address.  If the code is
running under the JIT plugin this step is essential to correct the return address.  If the code
isn't running in the JIT plugin this step does nothing at all.  The standard pawn VM doesn't know
the control register `8`, so just instantly returns without altering `pri` or `alt`.  As also
mentioned earlier *y_ctrl* doesn't modify registers from 0-255, this is another example of why.

Finally the return address is pushed as would be done automatically by `CALL`, the target handler
function's address is loaded from parameter `20`, and execution jumps to that point:

```pawn
#emit PUSH.pri
#emit LOAD.S.pri       20
#emit SCTRL            6
```

Once the handler returns (the handler is just a normal function in this respect) is the only place
where the code in `CTRL_SCTRLStub` and `CTRL_LCTRLStub` differ.  `CTRL_LCTRLStub` needs to restore
only `alt` to its previous value (stored earlier in its parameters), then return:

```pawn
// We return to here, from which cleanup is easy.
#emit LOAD.S.alt       16
#emit RETN
```

`CTRL_SCTRLStub` needs to restore both `pri` and `alt`, then return:

```pawn
// We return to here, from which cleanup is easy.
#emit LOAD.S.alt       16
#emit LOAD.S.pri       12
#emit RETN
```

Because by the point the frame has been repaired, the `RETN` here behaves correctly, removes all the
parameters from the stack, reverts the frame pointer to the previous one, and returns execution to
the original call point.

## Writing The Public

Thus far we have scanned the code for `LCTRL ???`s and `SCTRL ???`s, looped over the public
functions, and shown the code from the trampolines (aka the *stub8 functions), but none of these
things have actually been linked together.  While as said before the public function should be:

```asm
PUSH.C     handlerAddress
JUMP       YSI_g_sLCTRLStubAddress
```

It currently isn't, it is still just the default code generated by the compiler (i.e.
`return %1(0, 0); `).  The `AMX_GetPublicPointerPrefix` loops calls a function called
`CTRL_WriteLCTRLStub`, which is where this rewriting happens.

### Getting `handlerAddress`

The first half of `CTRL_WriteLCTRLStub` looks for the address of the handler function to jump to.
Since the code in the public by default is just `return handler(0, 0);` this address is found by
looping through all the instructions in the function until a `CALL` opcode is found, using the
*disasm.inc* library from *amx_assembly*.

```pawn
// Find the call target.
new
	handlerAddress,
	dctx[DisasmContext];
DisasmInit(dctx, addr);
```

First a disassembly context is declared.  This just stores things like the current address being
read and the parameters to the last read opcode.  `handlerAddress` will store the handler function
address, `dctx` is short for *disassembly context*, and the initialisation function `DisasmInit`
takes both the context and the address of the current public function found by
`AMX_GetPublicEntryPrefix` and passed in as a parameter.  This means that the code will start
disassembling (similar to decompiling but not) the public function found earlier.

The code loops over instructions as long as there are instructions left.  This checks the current
address is within the `COD` segment (the part of the AMX with all the code), if it is it reads the
current instuction and parameters, advances the pointer for the next call, and returns true.  While
this would continue the loop until the entire `COD` segment has been read, the `break` later ends
the loop early:

```pawn
while (DisasmNext(dctx))
```

Look for the first `CALL` instruction:

```pawn
if (DisasmGetOpcode(dctx) == OP_CALL)
```

If a `CALL` was found, get the parameter, store it in `handlerAddress`, and end the loop:

```pawn
// Search the function for a call to the implementation.
handlerAddress = DisasmGetOperandReloc(dctx);
break;
```

*disasm.inc* has `DisasmGetOperand` and `DisasmGetOperandReloc`.  `CALL` is one of the instructions
mentioned earlier whose parameters (*operaands*) are relocated by the VM when the mode starts.  The
function address is changed from an AMX address to a server address.  We need the original AMX
address because that's what `SCTRL 6` takes, so the operand is loaded and relocated, hence calling
`DisasmGetOperandReloc` instead.

### Writing The Code

The second half of `CTRL_WriteLCTRLStub` overwrites the code currently in the public function (which
isn't really `public` anymore, just some handy spare space to put new code in).  This writing is
done by *asm.inc*, which provides functions to write instructions anywhere in the AMX.  Because of
VM protections, only instructions written within the `COD` segment will be run, which is why the old
code in the public is being replaced.  A function to write an opcode somewhere looks like:

```pawn
AsmEmitAddC(ctx, 4);
```

Which will generate:

```asm
ADD.C      4
```

Place it at the current pointer in `ctx`, and advance the pointer by eight bytes (two cells).

That code can become cumbersome, so to mirror `#emit` (and now `__emit`) there are macros provided
by the library to wrap these function calls using `@emit`.  That function call can be written as:

```pawn
@emit ADD.C            4
```

Notice that because `ctx` is not specified in the `@emit` macro but is a parameter to the underlying
function, the context must ALWAYS be called `ctx` when using these macros.  Multiple styles are
also supported, so `ADD.C`, `add.c`, `ADD.c`, etc. are all suppported (just like with `#emit`).

Of course, to write to `ctx` we must first declare and initialise it:

```pawn
new
	ctx[AsmContext];
AsmInitPtr(ctx, addr + AMX_HEADER_COD, 32);
```

`addr` was the parameter passed earlier; however, `addr` is an address in the `COD` segment, while
`AsmInitPtr` takes an address in the `DAT` segment (the part of the AMX with all the global
variables).  We can still write in to the `COD` segment, but only by modifying the pointer to be an
offset in the `DAT` segment so large it ends up going in to the other segment.  Hence
`+ AMX_HEADER_COD`.  `32` is just the size of the area in bytes that we will write to.

The code is replacing a function called `@y_L300` (for example) with tiny stub code that isn't a
valid function.  While unlikely, someone could try and call this function directly via `@y_L300();`
or `CallLocalFunction` etc.  So the first few instructions generate a tiny but valid function at the
exact start address of the existing function (this code actually replaces `PROC` with `PROC`).  This
tiny function calls the trampoline in exactly the same way as the code replacing `LCTRL ???` will:

```pawn
// Write a function in case someone tries to call this public normally.
@emit PROC
@emit CALL.abs         addr + 16
@emit RETN
```

Anyone for some reason calling the function will now hit this and still get the result.

Now we can finally write the trampoline:

```pawn
// Push the implementation address and jump to the common register preserving
// stub, so that `pri` and `alt` aren't clobbered (skipping `PROC`).
@emit PUSH.C           handlerAddress
@emit JUMP             YSI_g_sLCTRLStubAddress
```

Which is exactly the assembly mentioned above!

## Replacing `LCTRL ???`

Having set everything else up and explained all the trampoline code, we can finally return to the
`CTRL_FoundLCTRL` function found when the code scan matcher finds an instance of `LCTRL ???`.  You
will recall the matcher is set up as:

```pawn
CodeScanMatcherInit(lctrl, &CTRL_FoundLCTRL);
CodeScanMatcherPattern(lctrl,
	OP(LCTRL, ???)
);
```

`CodeScanMatcherInit` can use `&` to get the address of any function whose signature is:

```pawn
MatcherFunction(const scanner[CodeScanner])
```

Note: Plus optional meta-data not used here.

Every time an `LCTRL` opcode with any operand is found this function is called:

```pawn
static stock CTRL_FoundLCTRL(const scanner[CodeScanner])
```

The `scanner` variable holds information about which scanner was being run, where in the code the
match started, the values of wildcards, and more.  Since we need to know which `LCTRL ???` this is
we get the value of the first wildcard (*hole*), and ignore it if it is `0 <= operand <= 255`:

```pawn
new reg = CodeScanGetMatchHole(scanner, 0);
if (0 <= reg <= 255)
{
	// Reserved registers (VM and plugins).  Do nothing.
	return;
}
```

As in `CTRL_WriteLCTRLStub` we create an `asm.inc` context to write code to the location of the
match (again adjusting for `DAT` -> `COD`), with enough space to write two cells:

```pawn
new
	ctx[AsmContext];
AsmInitPtr(ctx, CodeScanGetMatchAddress(scanner) + AMX_HEADER_COD, 8);
```

The public function that was replaced above with some of the trampoline code is what this
`LCTRL ???` must be replaced with a call to.  So first find the pointer to it.  This uses
`AMX_GetPublicPointer`, which takes a full string name, not `AMX_GetPublicPointerPrefix` which is
more useful for looping over many similar functions.  This time we want an exact match.  The
function still returns a non-zero index if there is a match so this can be tested to ensure there
was a function with the exact given name:

First construct the name, as `@y_L` followed by the control register number:

```pawn
new
	ptr,
	name[FUNCTION_LENGTH];
format(name, sizeof (name), "@y_L%d", reg);
```

Then search for a function with this exact name:

```pawn
AMX_GetPublicPointer(0, ptr, name);
```

Remember earlier when the code contained `LCTRL 8` to translate addresses if the JIT plugin was in
use?  This demonstrates a fundamental part of control registers - they are optional.  If control
register 8 doesn't exist, nothing happens.  There is no compile-time error, there is no run-time
crash.  `pri` and `alt` keep exactly their previous values.  The crashdetect plugin include uses
this exact feature to detect the presense of the plugin.  It sets `pri` to some invalid value first
then calls `LCTRL 255`.  If `pri` is `0` or `1` the plugin exists and changed `pri`, if it is still
the invalid value there was no handler for the register.

This is what this `if` check determines.  Is there a handler registered anywhere to deal with this
number of control register?  If there is, insert the `CALL` code discussed before.  If there isn't
the result should be the same as the input, and the simplest way to do that is to just remove the
load entirely:

```pawn
if (AMX_GetPublicPointer(0, ptr, name))
{
	@emit CALL.abs         ptr + 16
}
else
{
	@emit NOP
	@emit NOP
}
```

The `ptr + 16` skips over the first four cells of the public function, which is where the tiny
fallback handler was inserted in case someone decided to call the function directly for some reason.

## Conclusion

That is it!  This code:

* Scans the entire assembly for `LCTRL ???` instructions.
* Extracts the value of the register.
* Looks up a handler for that register.
* If the handler is found, replaces the entire instruction with a partially invalid call to a trampoline.
* Searches again for all registered handlers and replaces them with said trampoline.
* That trampoline pushes the address of the true handler function and calls another trampoline (because of code size limitations).
* This second common trampoline fixes the stack from the partially invalid calls.
* It also saves the values of `pri` and `alt` to be restored after the handler completes.
* And finally calls the handler.

At this point the execution is in normal pawn code and the handler can do anything:

```pawn
#include <YSI_Coding\y_ctrl>

@lctrl(2022) Handler(pri, alt)
{
	printf("Our control register has been called!");
	new year;
	getdate(year);
	if (year == pri)
	{
		printf("Yes, we are in %d.", pri);
		return 1;
	}
	printf("No, we are in %d.", year);
	return 0;
}

main()
{
	// Check if the year is 2022.
	new is2022 = 0;
	#emit CONST.pri        2022
	#emit LCTRL            2022
	#emit STOR.S.pri       is2022
	if (is2022 == 2022)
	{
		// `pri` was still `2022` after being set by `CONST.pri`, therefore
		// the handler wasn't called and so doesn't exist.
		print("The handler can't return `2022`, so it doesn't exist.");
	}
	else
	{
		print(is2022 ? ("Yes") : ("No"));
	}
}
```

And remember - all this code is doubled, once for `LCTRL` and once for `SCTRL`.

