#if !defined CHAIN_ORDER
	#define CHAIN_ORDER() 0
#endif

#define CHAIN_HOOK(%0) forward @CO_%0();public @CO_%0(){return CHAIN_ORDER()+1;}

#define CHAIN_NEXT(%0) @CO_%0

static stock _PreHook_IncludeStates() <_ALS : _ALS_x0, _ALS : _ALS_x1, _ALS : _ALS_x2, _ALS : _ALS_x3>
{
}

static stock _PreHook_IncludeStates() <_ALS : _ALS_go>
{
}

#define CHAIN_FORWARD:%0_%2(%1)=%3; \
	forward %0_%2(%1); \
	public %0_%2(%1) <_ALS : _ALS_x0, _ALS : _ALS_x1> { return (%3); } \
	public %0_%2(%1) <> { return (%3); }

#define CHAIN_PUBLIC:%0(%1) %0(%1) <_ALS : _ALS_go>

