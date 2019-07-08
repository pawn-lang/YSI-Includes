#if defined _INC_y_thirdpartyinclude
	#endinput
#endif
#define _INC_y_thirdpartyinclude

/*+
 * <library name="y_thirdpartyinclude">
 * <section>
 *  Description
 * </section>
 *  Try and include all YSI dependencies, looking in as many places as needed.
 * <section>
 *  Version
 * </section>
 *  1.0
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
	Portions created by the Initial Developer are Copyright C 2011
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
// of using "#tryinclude".  If they happen to exist in two places, their own
// internal include guards (or the compiler's one) will prevent their multiple
// inclusions.  I don't know why I ever made YSI use its own internal version...

#tryinclude "..\..\amx\addressof"
#tryinclude <amx_assembly\addressof>
#tryinclude "..\..\amx_assembly\addressof"
#tryinclude "..\..\..\amx_assembly\addressof"
#tryinclude "addressof"
#tryinclude <addressof>
#if !defined ADDRESSOF_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\addressof_jit"
#tryinclude <amx_assembly\addressof_jit>
#tryinclude "..\..\amx_assembly\addressof_jit"
#tryinclude "..\..\..\amx_assembly\addressof_jit"
#tryinclude "addressof_jit"
#tryinclude <addressof_jit>
#if !defined ADDRESSOF_JIT_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\amx"
#tryinclude <amx_assembly\amx>
#tryinclude "..\..\amx_assembly\amx"
#tryinclude "..\..\..\amx_assembly\amx"
#tryinclude "amx"
#tryinclude <amx>
#if !defined AMX_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\amx_base"
#tryinclude <amx_assembly\amx_base>
#tryinclude "..\..\amx_assembly\amx_base"
#tryinclude "..\..\..\amx_assembly\amx_base"
#tryinclude "amx_base"
#tryinclude <amx_base>
#if !defined AMX_BASE_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\amx_header"
#tryinclude <amx_assembly\amx_header>
#tryinclude "..\..\amx_assembly\amx_header"
#tryinclude "..\..\..\amx_assembly\amx_header"
#tryinclude "amx_header"
#tryinclude <amx_header>
#if !defined AMX_HEADER_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\amx_memory"
#tryinclude <amx_assembly\amx_memory>
#tryinclude "..\..\amx_assembly\amx_memory"
#tryinclude "..\..\..\amx_assembly\amx_memory"
#tryinclude "amx_memory"
#tryinclude <amx_memory>
#if !defined AMX_MEMORY_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\asm"
#tryinclude <amx_assembly\asm>
#tryinclude "..\..\amx_assembly\asm"
#tryinclude "..\..\..\amx_assembly\asm"
#tryinclude "asm"
#tryinclude <asm>
#if !defined ASM_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\asm_macros"
#tryinclude <amx_assembly\asm_macros>
#tryinclude "..\..\amx_assembly\asm_macros"
#tryinclude "..\..\..\amx_assembly\asm_macros"
#tryinclude "asm_macros"
#tryinclude <asm_macros>
#if !defined ASM_MACROS_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\codescan"
#tryinclude <amx_assembly\codescan>
#tryinclude "..\..\amx_assembly\codescan"
#tryinclude "..\..\..\amx_assembly\codescan"
#tryinclude "codescan"
#tryinclude <codescan>
#if !defined CODESCAN_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\amx_jit"
#tryinclude <amx_assembly\amx_jit>
#tryinclude "..\..\amx_assembly\amx_jit"
#tryinclude "..\..\..\amx_assembly\amx_jit"
#tryinclude "amx_jit"
#tryinclude <amx_jit>
#if !defined AMX_JIT_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\disasm"
#tryinclude <amx_assembly\disasm>
#tryinclude "..\..\amx_assembly\disasm"
#tryinclude "..\..\..\amx_assembly\disasm"
#tryinclude "disasm"
#tryinclude <disasm>
#if !defined DISASM_INC
	#define AMX_INCLUDING_FAILED
#endif

//#tryinclude "..\..\amx\dynamic_call"
//#tryinclude <amx_assembly\dynamic_call>
//#tryinclude "..\..\amx_assembly\dynamic_call"
//#tryinclude "..\..\..\amx_assembly\dynamic_call"
//#tryinclude "dynamic_call"
//#tryinclude <dynamic_call>
//#if !defined DYNAMIC_CALL_INC
//	#define AMX_INCLUDING_FAILED
//#endif

#tryinclude "..\..\amx\frame_info"
#tryinclude <amx_assembly\frame_info>
#tryinclude "..\..\amx_assembly\frame_info"
#tryinclude "..\..\..\amx_assembly\frame_info"
#tryinclude "dynamic_call"
#tryinclude <dynamic_call>
#if !defined FRAME_INFO_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\..\amx\heap_alloc"
#tryinclude <amx_assembly\heap_alloc>
#tryinclude "..\..\amx_assembly\heap_alloc"
#tryinclude "..\..\..\amx_assembly\heap_alloc"
#tryinclude "heap_alloc"
#tryinclude <heap_alloc>
#if !defined HEAP_ALLOC_INC
	#define AMX_INCLUDING_FAILED
#endif

//#tryinclude "..\..\amx\jit"
//#tryinclude <amx_assembly\jit>
//#tryinclude "..\..\amx_assembly\jit"
//#tryinclude "..\..\..\amx_assembly\jit"
//#tryinclude "jit"
//#tryinclude <jit>
//#if !defined JIT_INC
//	#define AMX_INCLUDING_FAILED
//#endif

#tryinclude "..\..\amx\opcode"
#tryinclude <amx_assembly\opcode>
#tryinclude "..\..\amx_assembly\opcode"
#tryinclude "..\..\..\amx_assembly\opcode"
#tryinclude "opcode"
#tryinclude <opcode>
#if !defined OPCODE_INC
	#define AMX_INCLUDING_FAILED
#endif

//#tryinclude "..\..\amx\os"
//#tryinclude <amx_assembly\os>
//#tryinclude "..\..\amx_assembly\os"
//#tryinclude "..\..\..\amx_assembly\os"
//#tryinclude "os"
//#tryinclude <os>
//#if !defined OS_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude "..\..\amx\phys_memory"
//#tryinclude <amx_assembly\phys_memory>
//#tryinclude "..\..\amx_assembly\phys_memory"
//#tryinclude "..\..\..\amx_assembly\phys_memory"
//#tryinclude "phys_memory"
//#tryinclude <phys_memory>
//#if !defined PHYS_MEMORY_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude "..\..\amx\profiler"
//#tryinclude <amx_assembly\profiler>
//#tryinclude "..\..\amx_assembly\profiler"
//#tryinclude "..\..\..\amx_assembly\profiler"
//#tryinclude "profiler"
//#tryinclude <profiler>
//#if !defined PROFILER_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude "..\..\amx\shellcode"
//#tryinclude <amx_assembly\shellcode>
//#tryinclude "..\..\amx_assembly\shellcode"
//#tryinclude "..\..\..\amx_assembly\shellcode"
//#tryinclude "shellcode"
//#tryinclude <shellcode>
//#if !defined SHELLCODE_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude "..\..\amx\stack_dump"
//#tryinclude <amx_assembly\stack_dump>
//#tryinclude "..\..\amx_assembly\stack_dump"
//#tryinclude "..\..\..\amx_assembly\stack_dump"
//#tryinclude "stack_dump"
//#tryinclude <stack_dump>
//#if !defined STACK_DUMP_INC
//	#define AMX_INCLUDING_FAILED
//#endif

//#tryinclude "..\..\amx\stack_trace"
//#tryinclude <amx_assembly\stack_trace>
//#tryinclude "..\..\amx_assembly\stack_trace"
//#tryinclude "..\..\..\amx_assembly\stack_trace"
//#tryinclude "stack_trace"
//#tryinclude <stack_trace>
//#if !defined STACK_TRACE_INC
//	#define AMX_INCLUDING_FAILED
//#endif

#if defined AMX_INCLUDING_FAILED
	#error Could not include "https://github.com/Zeex/amx_assembly" - ensure its files are in "include\amx_assembly\"
#elseif !defined CodeScanRunFast
	#error Please update "https://github.com/Zeex/amx_assembly" to the latest version.
#endif

#tryinclude "..\..\md-sort\md-sort"
#tryinclude <md-sort\md-sort>
#tryinclude "..\..\md-sort-master\md-sort"
#tryinclude <md-sort-master\md-sort>
#tryinclude "md-sort"
#tryinclude <md-sort>
#if !defined _INC_md_sort
	#error Could not include "https://github.com/oscar-broman/md-sort" - ensure its files are in "include\md-sort\"
#elseif !defined ResetDeepArray_Entry
	#error Please update "https://github.com/oscar-broman/md-sort" to the latest version.
#endif

#tryinclude "..\..\code-parse\code-parse"
#tryinclude <code-parse\code-parse>
#tryinclude "..\..\code-parse.inc\code-parse"
#tryinclude <code-parse.inc\code-parse>
#tryinclude "..\..\code-parse.inc-master\code-parse"
#tryinclude <code-parse.inc-master\code-parse>
#tryinclude "code-parse"
#tryinclude <code-parse>
#if !defined _INC_code_parse_inc
	#error Could not include "https://github.com/Y-Less/code-parse.inc" - ensure its files are in "include\code-parse\"
#endif

#tryinclude "..\..\indirection\indirection"
#tryinclude <indirection\indirection>
#tryinclude "..\..\indirection-master\indirection"
#tryinclude <indirection-master\indirection>
#tryinclude "indirection"
#tryinclude <indirection>
#if !defined _INC_indirection
	#error Could not include "https://github.com/Y-Less/indirection" - ensure its files are in "include\indirection\"
#elseif !defined Indirect_Init
	#error Please update "https://github.com/Y-Less/indirection" to the latest version.
#endif

// "y_thirdpartyinclude_tests" is NOT included here when tests are active, because it complicates
// dependency orders massively!

public OnCodeInit()
{
	AddressofResolve();
	Indirect_Init();
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

