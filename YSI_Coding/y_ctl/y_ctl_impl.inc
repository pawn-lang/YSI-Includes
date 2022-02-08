#define @y_L%0\32; @y_L
#define @y_S%0\32; @y_S

// The `LCTRL` and `SCTRL` codes are replaced by `CALL`s to these public
// functions.  We thus need to be exceptionally careful about the code run in
// them.  They need to set the parameters (since there was no value pushed), and
// preserve both `pri` and `alt` to pass to the child implementation.
#define @lctrl(%0)%1(%2) @y_L%0(); @y_L%0();
#define @lctrl(%0)%1(%2) @y_S%0(); @y_S%0();

// The code found in the function.

// Pass `pri` and `alt` as parameters, and get the previous frame.
@emit SWAP.alt
@emit PUSH.pri

// Push a parameter count of THREE parameters, not TWO.  The extra one is the
// original return address we couldn't remove.
@emit PUSH.C           12

// Move the original return address' location in the stack.
@emit PUSH.S           4

// Reset the frame.
@emit MOVE.pri
@emit SCTRL            5

// Jump to the function.
@emit JUMP             function.

