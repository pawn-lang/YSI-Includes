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
segments, and more.  There are 7 by default, numbered `0` to `6`.  The crashdetect plugin adds
registers `0xFF` and `0xFE` for sending it instructions (as opposed to using normal functions since
the plugin is optional and may not exist).  These registers are read using `LCTRL` and written using
`SCTRL`.  The read result is placed in `pri` and the write data is (usually) read from `pri`:

```pawn
// Get the file offset to the start of the data segment.
#emit LCTRL        1
// `pri` now holds the offset.

// Increase the stack pointer (register 4) by 8.
#emit LCTRL        4
#emit ADD.C        8
#emit SCTRL        4
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
	YSI_g_sLCTRLStubAddress;

#define CALL@CTRL_LCTRLStub CTRL_LCTRLStub()
```

These are both to do with `addressof`.  `addressof`, from amx_assembly, returns the address in the
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
new
	base = -DisasmReloc(0);
YSI_g_sLCTRLStubAddress = addressof (CTRL_LCTRLStub) + 4 + base;
```

This is where the address of `CTRL_LCTRLStub` is looked up (what this function does will be
explained later).  `DisasmReloc` is normally used when analysing code to convert the server absolute
addresses found the assembly after the script loads back to the script absolute addresses found in
the AMX stored on disk (the VM relocates all jumps on script load).  Here it is slightly abused by
getting the script address of the server address naught and negating it to be able to perform the
same relocations as the VM does.

`addressof` gets the address of the start of the function (in the AMX), `+ 4` skips over the first
instruction (usually `PROC`, and definitely `PROC` for this function), and `+ base` performs the
previously mentioned relocation to get the real address in the server of the function, rather than
the logical address in the script.

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
syntax.  This is why `#define CALL@CTRL_FoundLCTRL CTRL_FoundLCTRL(something)` isn't needed.

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

The original plan was to replace the `@y_L` public function's code with a trampoline specific to
that one handler, but there was too much code to fit in (if someone can do it, please let me know).
Although the basic call is only eight cells, the trampoline with its stack modifications is slightly
longer and doesn't fit in the space afforded by that short function call at `-O1 -d0`.  Another
option is to just insert more dummy code in to the `public` to make it slightly longer and provide
some more code generation space.
