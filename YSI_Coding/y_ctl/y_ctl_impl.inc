#define @y_L%0\32; @y_L
#define @y_S%0\32; @y_S

// The `LCTRL` and `SCTRL` codes are replaced by `CALL`s to these public
// functions.  We thus need to be exceptionally careful about the code run in
// them.  They need to set the parameters (since there was no value pushed), and
// preserve both `pri` and `alt` to pass to the child implementation.
#define @lctrl(%0)%1(%2) @y_L%0(); @y_L%0(){return %1(0,0);}
#define @sctrl(%0)%1(%2) @y_S%0(); @y_S%0(){%1(0,0);}

// The code found in the function.  Replaces everything, including `PROC` (so
// there is no frame update yet):

// Pass `pri` and `alt` as parameters, and get the return address.
@emit SWAP.alt
@emit PUSH.pri

// Push the parameter count.
@emit PUSH.C           8

// Push the return address.
@emit PUSH.alt

// Jump to the function.
@emit JUMP             function

// There is no way that can't fit within the code space reserved by the wrapper
// public.  By my maths the smallest it can possibly be is ten cells:
//
//     PROC
//     PUSH.C              0
//     PUSH.C              0
//     PUSH.C              8
//     CALL                %1
//     RETN
//
// And the code we actually want is only seven cells.  Even with `#pragma naked`
// removing `PROC` and `RETN` we would have enough space.

