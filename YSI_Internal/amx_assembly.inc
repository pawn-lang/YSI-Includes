// If the files only exist in one place, they will only be included once because
// of using "#tryinclude".  If they happen to exist in two places, their own
// internal include guards (or the compiler's one) will prevent their multiple
// inclusions.  I don't know why I ever made YSI use its own internal version...

#tryinclude "..\amx\amx"
#tryinclude <amx_assembly\amx>
#tryinclude "..\amx_assembly\amx"
#tryinclude "..\..\amx_assembly\amx"
#if !defined AMX_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\amx_base"
#tryinclude <amx_assembly\amx_base>
#tryinclude "..\amx_assembly\amx_base"
#tryinclude "..\..\amx_assembly\amx_base"
#if !defined AMX_BASE_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\amx_header"
#tryinclude <amx_assembly\amx_header>
#tryinclude "..\amx_assembly\amx_header"
#tryinclude "..\..\amx_assembly\amx_header"
#if !defined AMX_HEADER_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\amx_memory"
#tryinclude <amx_assembly\amx_memory>
#tryinclude "..\amx_assembly\amx_memory"
#tryinclude "..\..\amx_assembly\amx_memory"
#if !defined AMX_MEMORY_INC
	#define AMX_INCLUDING_FAILED
#endif
#if !defined deref
	#error Please update "https://github.com/Zeex/amx_assembly" to get "deref()"
#endif

#tryinclude "..\amx\asm"
#tryinclude <amx_assembly\asm>
#tryinclude "..\amx_assembly\asm"
#tryinclude "..\..\amx_assembly\asm"
#if !defined ASM_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\asm_macros"
#tryinclude <amx_assembly\asm_macros>
#tryinclude "..\amx_assembly\asm_macros"
#tryinclude "..\..\amx_assembly\asm_macros"
#if !defined ASM_MACROS_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\codescan"
#tryinclude <amx_assembly\codescan>
#tryinclude "..\amx_assembly\codescan"
#tryinclude "..\..\amx_assembly\codescan"
#if !defined CODESCAN_INC
	#error Please update "https://github.com/Zeex/amx_assembly" to get "codescan.inc"
#endif

#tryinclude "..\amx\disasm"
#tryinclude <amx_assembly\disasm>
#tryinclude "..\amx_assembly\disasm"
#tryinclude "..\..\amx_assembly\disasm"
#if !defined DISASM_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\dynamic_call"
#tryinclude <amx_assembly\dynamic_call>
#tryinclude "..\amx_assembly\dynamic_call"
#tryinclude "..\..\amx_assembly\dynamic_call"
#if !defined DYNAMIC_CALL_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\frame_info"
#tryinclude <amx_assembly\frame_info>
#tryinclude "..\amx_assembly\frame_info"
#tryinclude "..\..\amx_assembly\frame_info"
#if !defined FRAME_INFO_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\heap_alloc"
#tryinclude <amx_assembly\heap_alloc>
#tryinclude "..\amx_assembly\heap_alloc"
#tryinclude "..\..\amx_assembly\heap_alloc"
#if !defined HEAP_ALLOC_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\opcode"
#tryinclude <amx_assembly\opcode>
#tryinclude "..\amx_assembly\opcode"
#tryinclude "..\..\amx_assembly\opcode"
#if !defined OPCODE_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\os"
#tryinclude <amx_assembly\os>
#tryinclude "..\amx_assembly\os"
#tryinclude "..\..\amx_assembly\os"
#if !defined OS_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\phys_memory"
#tryinclude <amx_assembly\phys_memory>
#tryinclude "..\amx_assembly\phys_memory"
#tryinclude "..\..\amx_assembly\phys_memory"
#if !defined PHYS_MEMORY_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\profiler"
#tryinclude <amx_assembly\profiler>
#tryinclude "..\amx_assembly\profiler"
#tryinclude "..\..\amx_assembly\profiler"
#if !defined PROFILER_INC
	#define AMX_INCLUDING_FAILED
#endif

//#tryinclude "..\amx\shellcode"
//#tryinclude <amx_assembly\shellcode>
//#tryinclude "..\amx_assembly\shellcode"
//#tryinclude "..\..\amx_assembly\shellcode"
//#if !defined SHELLCODE_INC
//	#define AMX_INCLUDING_FAILED
//#endif

#tryinclude "..\amx\stack_dump"
#tryinclude <amx_assembly\stack_dump>
#tryinclude "..\amx_assembly\stack_dump"
#tryinclude "..\..\amx_assembly\stack_dump"
#if !defined STACK_DUMP_INC
	#define AMX_INCLUDING_FAILED
#endif

#tryinclude "..\amx\stack_trace"
#tryinclude <amx_assembly\stack_trace>
#tryinclude "..\amx_assembly\stack_trace"
#tryinclude "..\..\amx_assembly\stack_trace"
#if !defined STACK_TRACE_INC
	#define AMX_INCLUDING_FAILED
#endif

#if defined AMX_INCLUDING_FAILED
	#error Could not include "https://github.com/Zeex/amx_assembly" - ensure it is in <amx> or <amx_assembly>
#endif

