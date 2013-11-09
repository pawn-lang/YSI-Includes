import System.IO (hPutStrLn, stdout, withFile, IOMode(..))
import Text.Printf (printf)

-- The default master value.
standard = 0

h << s = hPutStrLn h s
infixr 0 <<

gen n m = do
	generatePop n
	generatePush n m

-- Generate _pop_master.inc
generatePop n = withFile "_pop_master.inc" WriteMode (\ f -> do
--generatePop n = flip ($) stdout (\ f -> do
		-- Header.
		f << "#undef _inc__pop_master"
		f << ""
		f << "#if _YSIM_PUSH_INDEX < 1"
		f << "\t#define MASTER " ++ show standard
		f << "\t#endinput"
		-- Main body.
		mapM_ (\ n' -> do
				f << "#elseif _YSIM_PUSH_INDEX == " ++ show (n' + 1)
				f << "\t#define MASTER _YSIM_STACK_SLOT_" ++ show n'
				f << "\t#undef _YSIM_PUSH_INDEX"
				f << "\t#define _YSIM_PUSH_INDEX " ++ show n'
				f << "\t#endinput"
			) [0 .. n - 1]
		-- Footer.
		f << "#endif"
		f << "#error y_master MASTER stack impossibility."
		f << ""
		--f << ""
	)

generateOnePush n m = withFile ("stack\\_stack_push_" ++ printf "%03d" n ++ ".inc") WriteMode (\ f -> do
--generateOnePush n m = flip ($) stdout (\ f -> do
		-- Header.
		f << "#undef _inc__stack_push_" ++ printf "%03d" n
		f << ""
		let slot = "_YSIM_STACK_SLOT_" ++ show n --s'
		f << "#undef _YSIM_PUSH_INDEX"
		f << "#define _YSIM_PUSH_INDEX " ++ show (n + 1)
		f << "#if defined " ++ slot
		f << "\t#undef " ++ slot
		f << "#endif"
		f << "#if     _MASTER == 0"
		f << "\t#define " ++ slot ++ " 0"
		f << "\t#endinput"
		mapM_ (\ master -> do
				f << "#elseif _MASTER == " ++ show master
				f << "\t#define " ++ slot ++ " " ++ show master
				f << "\t#endinput"
			) [1 .. m - 1]
		f << "#endif"
		f << ""
		--f << ""
	)

generatePush n m = withFile "_push_master.inc" WriteMode (\ f -> do
--generatePush n m = flip ($) stdout (\ f -> do
		-- Header.
		f << "#undef _inc__push_master"
		f << ""
		f << "#if _YSIM_PUSH_INDEX < 1"
		f << "\t#include \"stack\\_stack_push_000\""
		f << "\t#endinput"
		generateOnePush (0 :: Int) m
		-- Main body.
		mapM_ (\ n' -> do
				f << "#elseif _YSIM_PUSH_INDEX == " ++ show n'
				f << "\t#include \"stack\\_stack_push_" ++ printf "%03d" n' ++ "\""
				f << "\t#endinput"
				generateOnePush n' m
			) [1 .. n - 1]
		-- Footer.
		f << "#endif"
		f << "#error y_master MASTER stack overflow."
		f << ""
		--f << ""
	)

-- ddd

	-- f << "#define _MASTER 0"
	-- f << "#define YSIM_STORED_SETTINGS        YSIM_RECALL_0"
	-- f << "#if defined _YCM_a@"
	-- f << "\t#define YSIM_DEFINED"
	-- f << "#else"
	-- f << "\t#define _YCM_a@"
	-- f << "\t// Save the settings."
	-- f << "\t#include \"_resolve\""
	-- f << "\t#if !YSIM_HAS_MASTER"
	-- f << "\t\t#define YSIM_RECALL_0 0"
	-- f << "\t#elseif _YSIM_IS_CLIENT"
	-- f << "\t\t#define YSIM_RECALL_0 1"
	-- f << "\t#elseif _YSIM_IS_SERVER"
	-- f << "\t\t#define YSIM_RECALL_0 2"
	-- f << "\t#elseif _YSIM_IS_CLOUD"
	-- f << "\t\t#define YSIM_RECALL_0 3"
	-- f << "\t#elseif _YSIM_IS_STUB"
	-- f << "\t\t#define YSIM_RECALL_0 4"
	-- f << "\t#else"
	-- f << "\t\t#error Undefined master type on 0"
	-- f << "\t#endif"
	-- f << "#endif"
	-- f << "#define _YCM a@"
	-- f << "#define MAKE_YCM<%0...%1> %0a@%1"
	-- f << "#define _YCM@ _YCM_ga@"



zipM_ :: (Monad m) => (a -> b -> m c) -> [a] -> [b] -> m ()
zipM_ f a b = mapM_ (uncurry f) (zip a b)

generateImpl' = withFile "_impl" WriteMode (\ f -> zipM_ (generateImpl f) names [0 .. ])
generateImpl f name num = flip ($) f (\ f -> do
		if (num `mod` 16 == 0)
			then
				((f << "\t\t\t#elseif MASTER < " ++ show (((num `div` 16) + 1) * 16)) >>
				(f << "\t\t\t\t#if MASTER == " ++ show num))
			else f << "\t\t\t\t#elseif MASTER == " ++ show num
		--f << "\t\t\t\t#elseif _MASTER == " ++ show num
		f << "\t\t\t\t\t#if defined " ++ name ++ "OnScriptInit"
		f << "\t\t\t\t\t\t" ++ name ++ "OnScriptInit();"
		f << "\t\t\t\t\t#endif"
		f << "\t\t\t\t\t#define OnMasterSystemInit " ++ name ++ "OnScriptInit"
		if ((num + 1) `mod` 16 == 0)
			then f << "\t\t\t\t#endif"
			else return ()
	)

-- names = ["a@", "b@", "c@", "d@", "e@", "f@", "g@", "h@", "i@", "j@", "k@", "l@", "m@", "n@", "o@", "p@", "q@", "r@", "s@", "t@", "u@", "v@", "w@", "x@", "y@", "z@", 
 -- "A@", "B@", "C@", "D@", "E@", "F@", "G@", "H@", "I@", "J@", "K@", "L@", "M@", "N@", "O@", "P@", "Q@", "R@", "S@", "T@", "U@", "V@", "W@", "X@", "Y@", "Z@", 
 -- "@a", "@b", "@c", "@d", "@e", "@f", "@g", "@h", "@i", "@j", "@k", "@l", "@m", "@n", "@o", "@p", "@q", "@r", "@s", "@t", "@u", "@v", "@w", "@x", "@y", "@z", 
 -- "@A", "@B", "@C", "@D", "@E", "@F", "@G", "@H", "@I", "@J", "@K", "@L", "@M", "@N", "@O", "@P", "@Q", "@R", "@S", "@T", "@U", "@V", "@W", "@X", "@Y", "@Z", 
 -- "@0", "@1", "@2", "@3", "@4", "@5", "@6", "@7", "@8", "@9", "@@", "@_", "_@"]

names = ["@a", "@b", "@c", "@d", "@e", "@f", "@g", "@h", "@i", "@j", "@k", "@l", "@m", "@n", "@o", "@p", "@q", "@r", "@s", "@t", "@u", "@v", "@w", "@x", "@y", "@z", 
 "@A", "@B", "@C", "@D", "@E", "@F", "@G", "@H", "@I", "@J", "@K", "@L", "@M", "@N", "@O", "@P", "@Q", "@R", "@S", "@T", "@U", "@V", "@W", "@X", "@Y", "@Z", 
 "@0", "@1", "@2", "@3", "@4", "@5", "@6", "@7", "@8", "@9", "@@", "@_"]

generateSetup' = withFile "_setup_master" WriteMode (\ f -> zipM_ (generateSetup f) names [0 .. ])
generateSetup f name num = flip ($) f (\ f -> do
		if (num `mod` 16 == 0)
			then f << "#if MASTER == " ++ show num
			else f << "#elseif MASTER == " ++ show num
		f << "\t#define _MASTER " ++ show num
		f << "\t#define YSIM_STORED_SETTINGS YSIM_RECALL_" ++ show num
		f << "\t#if defined _YCM_" ++ name
		f << "\t\t#define YSIM_DEFINED"
		f << "\t#else"
		f << "\t\t#define _YCM_" ++ name
		f << "\t\t// Save the settings."
		f << "\t\t#include \"_resolve\""
		f << "\t\t#if !YSIM_HAS_MASTER"
		f << "\t\t\t#define YSIM_RECALL_" ++ show num ++ " 0"
		f << "\t\t#elseif _YSIM_IS_CLIENT"
		f << "\t\t\t#define YSIM_RECALL_" ++ show num ++ " 1"
		f << "\t\t#elseif _YSIM_IS_SERVER"
		f << "\t\t\t#define YSIM_RECALL_" ++ show num ++ " 2"
		f << "\t\t#elseif _YSIM_IS_CLOUD"
		f << "\t\t\t#define YSIM_RECALL_" ++ show num ++ " 3"
		f << "\t\t#elseif _YSIM_IS_STUB"
		f << "\t\t\t#define YSIM_RECALL_" ++ show num ++ " 4"
		f << "\t\t#else"
		f << "\t\t\t#error Undefined master type on " ++ show num
		f << "\t\t#endif"
		f << "\t#endif"
		f << "\t#define _YCM " ++ name
		f << "\t#define MAKE_YCM<%0...%1> %0" ++ name ++ "%1"
		f << "\t#define _YCM@ _YCM_g" ++ name
		f << "\t#endinput"
		if ((num + 1) `mod` 16 == 0)
			then f << "#endif"
			else return ()
	)

