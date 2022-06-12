#if defined _INC_y_thirdpartyinclude
	#endinput
#endif
#define _INC_y_thirdpartyinclude

/*+
 * <library
 *   name="y_thirdpartyinclude"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Try and include all YSI dependencies, looking in as many places as needed."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 *//** *//*
Legal:
	Version: MPL 1.1
	
	The contents of this file are subject to the Mozilla Public License Version 
	1.1 the "License"; you may not use this file except in compliance with 
	the License. You may obtain a copy of the License at 
	http://www.mozilla.org/MPL/
	
	Software distributed under the License is distributed on an "AS IS" basis,
	WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
	for the specific language governing rights and limitations under the
	License.
	
	The Original Code is the YSI framework.
	
	The Initial Developer of the Original Code is Alex "Y_Less" Cole.
	Portions created by the Initial Developer are Copyright (c) 2022
	the Initial Developer. All Rights Reserved.

Contributors:
	Y_Less
	koolk
	JoeBullet/Google63
	g_aSlice/Slice
	Misiur
	samphunter
	tianmeta
	maddinat0r
	spacemud
	Crayder
	Dayvison
	Ahmad45123
	Zeex
	irinel1996
	Yiin-
	Chaprnks
	Konstantinos
	Masterchen09
	Southclaws
	PatchwerkQWER
	m0k1
	paulommu
	udan111
	Cheaterman

Thanks:
	JoeBullet/Google63 - Handy arbitrary ASM jump code using SCTRL.
	ZeeX - Very productive conversations.
	koolk - IsPlayerinAreaEx code.
	TheAlpha - Danish translation.
	breadfish - German translation.
	Fireburn - Dutch translation.
	yom - French translation.
	50p - Polish translation.
	Zamaroht - Spanish translation.
	Los - Portuguese translation.
	Dracoblue, sintax, mabako, Xtreme, other coders - Producing other modes for
		me to strive to better.
	Pixels^ - Running XScripters where the idea was born.
	Matite - Pestering me to release it and using it.

Very special thanks to:
	Thiadmer - PAWN, whose limits continue to amaze me!
	Kye/Kalcor - SA:MP.
	SA:MP Team past, present and future - SA:MP.

Optional plugins:
	Gamer_Z - GPS.
	Incognito - Streamer.
	Me - sscanf2, fixes2, Whirlpool.
*/

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning push
	#pragma warning disable 231
#endif

// If the files only exist in one place, they will only be included once because
// of using "#tryinclude.inc".  If they happen to exist in two places, their own
// internal include guards (or the compiler's one) will prevent their multiple
// inclusions.  I don't know why I ever made YSI use its own internal version...

#tryinclude <amx\addressof.inc>
#tryinclude <amx_assembly\addressof.inc>
#tryinclude <amx_assembly-master\addressof.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\addressof.inc>
#tryinclude "..\..\amx\addressof.inc"
#tryinclude "..\..\amx_assembly\addressof.inc"
#tryinclude "..\..\amx_assembly-master\addressof.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\addressof.inc"
#tryinclude "..\..\..\amx\addressof.inc"
#tryinclude "..\..\..\amx_assembly\addressof.inc"
#tryinclude "..\..\..\amx_assembly-master\addressof.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\addressof.inc"
#tryinclude "addressof.inc"
#tryinclude <addressof.inc>
#if !defined ADDRESSOF_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\addressof_jit.inc>
#tryinclude <amx_assembly\addressof_jit.inc>
#tryinclude <amx_assembly-master\addressof_jit.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\addressof_jit.inc>
#tryinclude "..\..\amx\addressof_jit.inc"
#tryinclude "..\..\amx_assembly\addressof_jit.inc"
#tryinclude "..\..\amx_assembly-master\addressof_jit.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\addressof_jit.inc"
#tryinclude "..\..\..\amx\addressof_jit.inc"
#tryinclude "..\..\..\amx_assembly\addressof_jit.inc"
#tryinclude "..\..\..\amx_assembly-master\addressof_jit.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\addressof_jit.inc"
#tryinclude "addressof_jit.inc"
#tryinclude <addressof_jit.inc>
#if !defined ADDRESSOF_JIT_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\amx.inc>
#tryinclude <amx_assembly\amx.inc>
#tryinclude <amx_assembly-master\amx.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\amx.inc>
#tryinclude "..\..\amx\amx.inc"
#tryinclude "..\..\amx_assembly\amx.inc"
#tryinclude "..\..\amx_assembly-master\amx.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\amx.inc"
#tryinclude "..\..\..\amx\amx.inc"
#tryinclude "..\..\..\amx_assembly\amx.inc"
#tryinclude "..\..\..\amx_assembly-master\amx.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\amx.inc"
#tryinclude "amx.inc"
#tryinclude <amx.inc>
#if !defined AMX_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\amx_base.inc>
#tryinclude <amx_assembly\amx_base.inc>
#tryinclude <amx_assembly-master\amx_base.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\amx_base.inc>
#tryinclude "..\..\amx\amx_base.inc"
#tryinclude "..\..\amx_assembly\amx_base.inc"
#tryinclude "..\..\amx_assembly-master\amx_base.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\amx_base.inc"
#tryinclude "..\..\..\amx\amx_base.inc"
#tryinclude "..\..\..\amx_assembly\amx_base.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_base.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\amx_base.inc"
#tryinclude "amx_base.inc"
#tryinclude <amx_base.inc>
#if !defined AMX_BASE_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\amx_header.inc>
#tryinclude <amx_assembly\amx_header.inc>
#tryinclude <amx_assembly-master\amx_header.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\amx_header.inc>
#tryinclude "..\..\amx\amx_header.inc"
#tryinclude "..\..\amx_assembly\amx_header.inc"
#tryinclude "..\..\amx_assembly-master\amx_header.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\amx_header.inc"
#tryinclude "..\..\..\amx\amx_header.inc"
#tryinclude "..\..\..\amx_assembly\amx_header.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_header.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\amx_header.inc"
#tryinclude "amx_header.inc"
#tryinclude <amx_header.inc>
#if !defined AMX_HEADER_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\amx_memory.inc>
#tryinclude <amx_assembly\amx_memory.inc>
#tryinclude <amx_assembly-master\amx_memory.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\amx_memory.inc>
#tryinclude "..\..\amx\amx_memory.inc"
#tryinclude "..\..\amx_assembly\amx_memory.inc"
#tryinclude "..\..\amx_assembly-master\amx_memory.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\amx_memory.inc"
#tryinclude "..\..\..\amx\amx_memory.inc"
#tryinclude "..\..\..\amx_assembly\amx_memory.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_memory.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\amx_memory.inc"
#tryinclude "amx_memory.inc"
#tryinclude <amx_memory.inc>
#if !defined AMX_MEMORY_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\asm.inc>
#tryinclude <amx_assembly\asm.inc>
#tryinclude <amx_assembly-master\asm.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\asm.inc>
#tryinclude "..\..\amx\asm.inc"
#tryinclude "..\..\amx_assembly\asm.inc"
#tryinclude "..\..\amx_assembly-master\asm.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\asm.inc"
#tryinclude "..\..\..\amx\asm.inc"
#tryinclude "..\..\..\amx_assembly\asm.inc"
#tryinclude "..\..\..\amx_assembly-master\asm.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\asm.inc"
#tryinclude "asm.inc"
#tryinclude <asm.inc>
#if !defined ASM_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\asm_macros.inc>
#tryinclude <amx_assembly\asm_macros.inc>
#tryinclude <amx_assembly-master\asm_macros.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\asm_macros.inc>
#tryinclude "..\..\amx\asm_macros.inc"
#tryinclude "..\..\amx_assembly\asm_macros.inc"
#tryinclude "..\..\amx_assembly-master\asm_macros.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\asm_macros.inc"
#tryinclude "..\..\..\amx\asm_macros.inc"
#tryinclude "..\..\..\amx_assembly\asm_macros.inc"
#tryinclude "..\..\..\amx_assembly-master\asm_macros.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\asm_macros.inc"
#tryinclude "asm_macros.inc"
#tryinclude <asm_macros.inc>
#if !defined ASM_MACROS_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\codescan.inc>
#tryinclude <amx_assembly\codescan.inc>
#tryinclude <amx_assembly-master\codescan.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\codescan.inc>
#tryinclude "..\..\amx\codescan.inc"
#tryinclude "..\..\amx_assembly\codescan.inc"
#tryinclude "..\..\amx_assembly-master\codescan.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\codescan.inc"
#tryinclude "..\..\..\amx\codescan.inc"
#tryinclude "..\..\..\amx_assembly\codescan.inc"
#tryinclude "..\..\..\amx_assembly-master\codescan.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\codescan.inc"
#tryinclude "codescan.inc"
#tryinclude <codescan.inc>
#if !defined CODESCAN_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\amx_jit.inc>
#tryinclude <amx_assembly\amx_jit.inc>
#tryinclude <amx_assembly-master\amx_jit.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\amx_jit.inc>
#tryinclude "..\..\amx\amx_jit.inc"
#tryinclude "..\..\amx_assembly\amx_jit.inc"
#tryinclude "..\..\amx_assembly-master\amx_jit.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\amx_jit.inc"
#tryinclude "..\..\..\amx\amx_jit.inc"
#tryinclude "..\..\..\amx_assembly\amx_jit.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_jit.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\amx_jit.inc"
#tryinclude "amx_jit.inc"
#tryinclude <amx_jit.inc>
#if !defined AMX_JIT_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\disasm.inc>
#tryinclude <amx_assembly\disasm.inc>
#tryinclude <amx_assembly-master\disasm.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\disasm.inc>
#tryinclude "..\..\amx\disasm.inc"
#tryinclude "..\..\amx_assembly\disasm.inc"
#tryinclude "..\..\amx_assembly-master\disasm.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\disasm.inc"
#tryinclude "..\..\..\amx\disasm.inc"
#tryinclude "..\..\..\amx_assembly\disasm.inc"
#tryinclude "..\..\..\amx_assembly-master\disasm.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\disasm.inc"
#tryinclude "disasm.inc"
#tryinclude <disasm.inc>
#if !defined DISASM_INC
	#define AMX_INCLUDING_FAILED
#endif

//#tryinclude <amx\dynamic_call.inc>
//#tryinclude <amx_assembly\dynamic_call.inc>
//#tryinclude <amx_assembly-master\dynamic_call.inc>
//#tryinclude <amx_assembly-master\amx_assembly-master\dynamic_call.inc>
//#tryinclude "..\..\amx\dynamic_call.inc"
//#tryinclude "..\..\amx_assembly\dynamic_call.inc"
//#tryinclude "..\..\amx_assembly-master\dynamic_call.inc"
//#tryinclude "..\..\amx_assembly-master\amx_assembly-master\dynamic_call.inc"
//#tryinclude "..\..\..\amx\dynamic_call.inc"
//#tryinclude "..\..\..\amx_assembly\dynamic_call.inc"
//#tryinclude "..\..\..\amx_assembly-master\dynamic_call.inc"
//#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\dynamic_call.inc"
//#tryinclude "dynamic_call.inc"
//#tryinclude <dynamic_call.inc>
//#if !defined DYNAMIC_CALL_INC
//	#define AMX_INCLUDING_FAILED
//#endif

#tryinclude <amx\frame_info.inc>
#tryinclude <amx_assembly\frame_info.inc>
#tryinclude <amx_assembly-master\frame_info.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\frame_info.inc>
#tryinclude "..\..\amx\frame_info.inc"
#tryinclude "..\..\amx_assembly\frame_info.inc"
#tryinclude "..\..\amx_assembly-master\frame_info.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\frame_info.inc"
#tryinclude "..\..\..\amx\frame_info.inc"
#tryinclude "..\..\..\amx_assembly\frame_info.inc"
#tryinclude "..\..\..\amx_assembly-master\frame_info.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\frame_info.inc"
#tryinclude "frame_info.inc"
#tryinclude <frame_info.inc>
#if !defined FRAME_INFO_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude <amx\heap_alloc.inc>
#tryinclude <amx_assembly\heap_alloc.inc>
#tryinclude <amx_assembly-master\heap_alloc.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\heap_alloc.inc>
#tryinclude "..\..\amx\heap_alloc.inc"
#tryinclude "..\..\amx_assembly\heap_alloc.inc"
#tryinclude "..\..\amx_assembly-master\heap_alloc.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\heap_alloc.inc"
#tryinclude "..\..\..\amx\heap_alloc.inc"
#tryinclude "..\..\..\amx_assembly\heap_alloc.inc"
#tryinclude "..\..\..\amx_assembly-master\heap_alloc.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\heap_alloc.inc"
#tryinclude "heap_alloc.inc"
#tryinclude <heap_alloc.inc>
#if !defined HEAP_ALLOC_INC
	#define AMX_INCLUDING_FAILED
#endif

//#tryinclude <amx\jit.inc>
//#tryinclude <amx_assembly\jit.inc>
//#tryinclude <amx_assembly-master\jit.inc>
//#tryinclude <amx_assembly-master\amx_assembly-master\jit.inc>
//#tryinclude "..\..\amx\jit.inc"
//#tryinclude "..\..\amx_assembly\jit.inc"
//#tryinclude "..\..\amx_assembly-master\jit.inc"
//#tryinclude "..\..\amx_assembly-master\amx_assembly-master\jit.inc"
//#tryinclude "..\..\..\amx\jit.inc"
//#tryinclude "..\..\..\amx_assembly\jit.inc"
//#tryinclude "..\..\..\amx_assembly-master\jit.inc"
//#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\jit.inc"
//#tryinclude "jit.inc"
//#tryinclude <jit.inc>
//#if !defined JIT_INC
//	#define AMX_INCLUDING_FAILED
//#endif

#tryinclude <amx\opcode.inc>
#tryinclude <amx_assembly\opcode.inc>
#tryinclude <amx_assembly-master\opcode.inc>
#tryinclude <amx_assembly-master\amx_assembly-master\opcode.inc>
#tryinclude "..\..\amx\opcode.inc"
#tryinclude "..\..\amx_assembly\opcode.inc"
#tryinclude "..\..\amx_assembly-master\opcode.inc"
#tryinclude "..\..\amx_assembly-master\amx_assembly-master\opcode.inc"
#tryinclude "..\..\..\amx\opcode.inc"
#tryinclude "..\..\..\amx_assembly\opcode.inc"
#tryinclude "..\..\..\amx_assembly-master\opcode.inc"
#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\opcode.inc"
#tryinclude "opcode.inc"
#tryinclude <opcode.inc>
#if !defined OPCODE_INC
	#define AMX_INCLUDING_FAILED
#endif

//#tryinclude <amx\os.inc>
//#tryinclude <amx_assembly\os.inc>
//#tryinclude <amx_assembly-master\os.inc>
//#tryinclude <amx_assembly-master\amx_assembly-master\os.inc>
//#tryinclude "..\..\amx\os.inc"
//#tryinclude "..\..\amx_assembly\os.inc"
//#tryinclude "..\..\amx_assembly-master\os.inc"
//#tryinclude "..\..\amx_assembly-master\amx_assembly-master\os.inc"
//#tryinclude "..\..\..\amx\os.inc"
//#tryinclude "..\..\..\amx_assembly\os.inc"
//#tryinclude "..\..\..\amx_assembly-master\os.inc"
//#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\os.inc"
//#tryinclude "os.inc"
//#tryinclude <os.inc>
//#if !defined OS_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude <amx\phys_memory.inc>
//#tryinclude <amx_assembly\phys_memory.inc>
//#tryinclude <amx_assembly-master\phys_memory.inc>
//#tryinclude <amx_assembly-master\amx_assembly-master\phys_memory.inc>
//#tryinclude "..\..\amx\phys_memory.inc"
//#tryinclude "..\..\amx_assembly\phys_memory.inc"
//#tryinclude "..\..\amx_assembly-master\phys_memory.inc"
//#tryinclude "..\..\amx_assembly-master\amx_assembly-master\phys_memory.inc"
//#tryinclude "..\..\..\amx\phys_memory.inc"
//#tryinclude "..\..\..\amx_assembly\phys_memory.inc"
//#tryinclude "..\..\..\amx_assembly-master\phys_memory.inc"
//#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\phys_memory.inc"
//#tryinclude "phys_memory.inc"
//#tryinclude <phys_memory.inc>
//#if !defined PHYS_MEMORY_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude <amx\profiler.inc>
//#tryinclude <amx_assembly\profiler.inc>
//#tryinclude <amx_assembly-master\profiler.inc>
//#tryinclude <amx_assembly-master\amx_assembly-master\profiler.inc>
//#tryinclude "..\..\amx\profiler.inc"
//#tryinclude "..\..\amx_assembly\profiler.inc"
//#tryinclude "..\..\amx_assembly-master\profiler.inc"
//#tryinclude "..\..\amx_assembly-master\amx_assembly-master\profiler.inc"
//#tryinclude "..\..\..\amx\profiler.inc"
//#tryinclude "..\..\..\amx_assembly\profiler.inc"
//#tryinclude "..\..\..\amx_assembly-master\profiler.inc"
//#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\profiler.inc"
//#tryinclude "profiler.inc"
//#tryinclude <profiler.inc>
//#if !defined PROFILER_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude <amx\shellcode.inc>
//#tryinclude <amx_assembly\shellcode.inc>
//#tryinclude <amx_assembly-master\shellcode.inc>
//#tryinclude <amx_assembly-master\amx_assembly-master\shellcode.inc>
//#tryinclude "..\..\amx\shellcode.inc"
//#tryinclude "..\..\amx_assembly\shellcode.inc"
//#tryinclude "..\..\amx_assembly-master\shellcode.inc"
//#tryinclude "..\..\amx_assembly-master\amx_assembly-master\shellcode.inc"
//#tryinclude "..\..\..\amx\shellcode.inc"
//#tryinclude "..\..\..\amx_assembly\shellcode.inc"
//#tryinclude "..\..\..\amx_assembly-master\shellcode.inc"
//#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\shellcode.inc"
//#tryinclude "shellcode.inc"
//#tryinclude <shellcode.inc>
//#if !defined SHELLCODE_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude <amx\stack_dump.inc>
//#tryinclude <amx_assembly\stack_dump.inc>
//#tryinclude <amx_assembly-master\stack_dump.inc>
//#tryinclude <amx_assembly-master\amx_assembly-master\stack_dump.inc>
//#tryinclude "..\..\amx\stack_dump.inc"
//#tryinclude "..\..\amx_assembly\stack_dump.inc"
//#tryinclude "..\..\amx_assembly-master\stack_dump.inc"
//#tryinclude "..\..\amx_assembly-master\amx_assembly-master\stack_dump.inc"
//#tryinclude "..\..\..\amx\stack_dump.inc"
//#tryinclude "..\..\..\amx_assembly\stack_dump.inc"
//#tryinclude "..\..\..\amx_assembly-master\stack_dump.inc"
//#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\stack_dump.inc"
//#tryinclude "stack_dump.inc"
//#tryinclude <stack_dump.inc>
//#if !defined STACK_DUMP_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude <amx\stack_trace.inc>
//#tryinclude <amx_assembly\stack_trace.inc>
//#tryinclude <amx_assembly-master\stack_trace.inc>
//#tryinclude <amx_assembly-master\amx_assembly-master\stack_trace.inc>
//#tryinclude "..\..\amx\stack_trace.inc"
//#tryinclude "..\..\amx_assembly\stack_trace.inc"
//#tryinclude "..\..\amx_assembly-master\stack_trace.inc"
//#tryinclude "..\..\amx_assembly-master\amx_assembly-master\stack_trace.inc"
//#tryinclude "..\..\..\amx\stack_trace.inc"
//#tryinclude "..\..\..\amx_assembly\stack_trace.inc"
//#tryinclude "..\..\..\amx_assembly-master\stack_trace.inc"
//#tryinclude "..\..\..\amx_assembly-master\amx_assembly-master\stack_trace.inc"
//#tryinclude "stack_trace.inc"
//#tryinclude <stack_trace.inc>
//#if !defined STACK_TRACE_INC
//	#define AMX_INCLUDING_FAILED
//#endif

#if defined AMX_INCLUDING_FAILED
	#error Download `https://github.com/Zeex/amx_assembly/archive/refs/heads/master.zip` and extract it to `include\`.
#elseif !defined HasSysreqD
	#error Re-download `https://github.com/Zeex/amx_assembly/archive/refs/heads/master.zip` and extract it to `include\`.
#endif

//#tryinclude <md-sort\md-sort.inc>
//#tryinclude <md-sort-master\md-sort.inc>
//#tryinclude <md-sort-master\md-sort-master\md-sort.inc>
//#tryinclude "..\..\md-sort\md-sort.inc"
//#tryinclude "..\..\md-sort-master\md-sort.inc"
//#tryinclude "..\..\md-sort-master\md-sort-master\md-sort.inc"
//#tryinclude "..\..\..\md-sort\md-sort.inc"
//#tryinclude "..\..\..\md-sort-master\md-sort.inc"
//#tryinclude "..\..\..\md-sort-master\md-sort-master\md-sort.inc"
//#tryinclude "md-sort.inc"
//#tryinclude <md-sort.inc>
//#if !defined _INC_md_sort
//	#error Download `https://github.com/oscar-broman/md-sort/archive/refs/heads/master.zip` and extract it to `include\`.
//#elseif !defined ResetDeepArray_Entry
//	#error Re-download `https://github.com/oscar-broman/md-sort/archive/refs/heads/master.zip` and extract it to `include\`.
//#endif

//#tryinclude <formatex\formatex.inc>
//#tryinclude <formatex-master\formatex.inc>
//#tryinclude <formatex-master\formatex-master\formatex.inc>
//#tryinclude "..\..\formatex\formatex.inc"
//#tryinclude "..\..\formatex-master\formatex.inc"
//#tryinclude "..\..\formatex-master\formatex-master\formatex.inc"
//#tryinclude "..\..\..\formatex\formatex.inc"
//#tryinclude "..\..\..\formatex-master\formatex.inc"
//#tryinclude "..\..\..\formatex-master\formatex-master\formatex.inc"
//#tryinclude "formatex.inc"
//#tryinclude <formatex.inc>
//#if !defined _INC_md_sort
//	#error Download `https://github.com/Y-Less/formatex/archive/refs/heads/master.zip` and extract it to `include\`.
//#elseif !defined FormatFlags
//	#error Re-download `https://github.com/Y-Less/formatex/archive/refs/heads/master.zip` and extract it to `include\`.
//#endif

// Manually fix earlier versions.
#if !defined _INC_code_parse_inc
	#undef u@
#endif
#tryinclude <code-parse\code-parse.inc>
#tryinclude <code-parse.inc\code-parse.inc>
#tryinclude <code-parse.inc-master\code-parse.inc>
#tryinclude <code-parse.inc-master\code-parse.inc-master\code-parse.inc>
#tryinclude "..\..\code-parse\code-parse.inc"
#tryinclude "..\..\code-parse.inc\code-parse.inc"
#tryinclude "..\..\code-parse.inc-master\code-parse.inc"
#tryinclude "..\..\code-parse.inc-master\code-parse.inc-master\code-parse.inc"
#tryinclude "..\..\..\code-parse\code-parse.inc"
#tryinclude "..\..\..\code-parse.inc\code-parse.inc"
#tryinclude "..\..\..\code-parse.inc-master\code-parse.inc"
#tryinclude "..\..\..\code-parse.inc-master\code-parse.inc-master\code-parse.inc"
#tryinclude "code-parse.inc"
#tryinclude <code-parse.inc>
#if defined _INC_code_parse_inc
	#undef u@
#else
	#error Download `https://github.com/Y-Less/code-parse.inc/archive/refs/heads/master.zip` and extract it to `include\`.
//#elseif !defined __code_parse_u@_1
//	#error Re-download `https://github.com/Y-Less/code-parse.inc/archive/refs/heads/master.zip` and extract it to `include\`.
#endif
#define u@$ 1]);

#tryinclude <indirection\indirection.inc>
#tryinclude <indirection-master\indirection.inc>
#tryinclude <indirection-master\indirection-master\indirection.inc>
#tryinclude "..\..\indirection\indirection.inc"
#tryinclude "..\..\indirection-master\indirection.inc"
#tryinclude "..\..\indirection-master\indirection-master\indirection.inc"
#tryinclude "..\..\..\indirection\indirection.inc"
#tryinclude "..\..\..\indirection-master\indirection.inc"
#tryinclude "..\..\..\indirection-master\indirection-master\indirection.inc"
#tryinclude "indirection.inc"
#tryinclude <indirection.inc>
#if !defined _INC_indirection
	#error Download `https://github.com/Y-Less/indirection/archive/refs/heads/master.zip` and extract it to `include\`.
#elseif !defined Indirect_Init || defined TAGOF@ || defined __TAGOF
	#error Re-download `https://github.com/Y-Less/indirection/archive/refs/heads/master.zip` and extract it to `include\`.
#endif

// "y_thirdpartyinclude_tests" is NOT included here when tests are active, because it complicates
// dependency orders massively!

public OnCodeInit()
{
	StillInALS(300);
	AddressofResolve();
	StillInALS(301);
	Indirect_Init();
	StillInALS(303);
	#if defined ThirdParty_OnCodeInit
		return ThirdParty_OnCodeInit();
	#else
		return 1;
	#endif
}

#undef OnCodeInit
#define OnCodeInit ThirdParty_OnCodeInit
#if defined ThirdParty_OnCodeInit
	forward ThirdParty_OnCodeInit();
#endif

#if __COMPILER_WARNING_SUPPRESSION
	#pragma warning pop
#endif

#include "y_codeparse"
#include "y_dumpamx"

