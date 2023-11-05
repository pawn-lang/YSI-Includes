#if defined _INC_y_const_correct
	#endinput
#endif
#define _INC_y_const_correct

// There are four main cases to consider when writing code that must be fully
// compatible with all compilers and libraries in being const-correct:
// 
//   1. Old compiler, old includes - `const` isn't checked, so it doesn't matter
//      whether it is used or not.  For this case we gate the `#pragma` because
//      it doesn't exist.
//
//   2. Old compiler, new includes - As above.
//
//   3. New compiler, new includes - `const` is checked, and the code is const-
//      correct.
//
//   4. New compiler, old includes - This is the tricky one, because people have
//      updated one part of their stack, but not another one.  Supporting this
//      edge-case required either new native definitions or `#pragma warning`,
//      but we can now bypass the compiler const check within our const-correct
//      boundary.
//
//      The obvious solution is to make this code not const-correct either, but
//      that's not an option for people who are on the new compiler and want
//      const-correctness; and is just pushing the issue further up the stack.
//      So we need to make the external API of this library const-correct, but
//      internally call const-incorrect code.
//
// First check if people are on the newest compiler, and don't have any const-
// correct includes.  If they don't, define `SAMP_CONST_INCORRECT`.  Also has
// extra checks for the two known const-correct define variants.  While another
// one may be introduced by another library, I, Y_Less, hereby solemnly swear
// this I will not add a new mutually-exclusive define (`OPEN_MP_CONST_CORRECT`
// already exists, but along-side `SAMP_CONST_CORRECT`).
#if defined FIX_const
	#if FIX_const
		// We get const-correctness from fixes.inc.
		#define SAMP_CONST_CORRECT
	#endif
#endif

#if !defined __const
	#define __const
#endif

#if !defined SAMP_CONST_CORRECT
	// The libraries are not const-corret.
	#define SAMP_CONST_INCORRECT
	#if defined __PawnBuild
		#if __PawnBuild >= 9
			// But they should be.
			#undef __const
			#define __const __const_impl
		#endif
	#endif
#endif

#if !defined __const_decl
	#define __const_decl

	// Again, this is required because of the restriction to not redefine
	// natives.  I've named it `__const` because it is very core.
	stock __const_impl(const arr[])
	{
		// This works by replacing the hidden return address on the stack with
		// the true address of our data then lying to the compiler to say we're
		// passing a normal array.
		//
		// Sadly the `__emit` version doesn't work.  If it did this would be
		// acceptable as const-correctness and `__emit` are in the same compiler
		// versions:
		//
		//   #define __const(%0) __emit(load.s.pri %0, push.pri)
		//
		#emit LOAD.S.pri arr
		#emit STOR.S.pri 16
		#emit RETN
		new ret[1];
		return ret;
	}
#endif

