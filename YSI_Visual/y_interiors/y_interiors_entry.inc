/*

 _    _________________  ___ ________   __
| |  |_   _| ___ \ ___ \/ _ \| ___ \ \ / /
| |    | | | |_/ / |_/ / /_\ \ |_/ /\ V / 
| |    | | | ___ \    /|  _  |    /  \ /  
| |____| |_| |_/ / |\ \| | | | |\ \  | |  
\_____|___/\____/\_| \_\_| |_|_| \_| \_/  
                                          
                                          
  _____ _   _ _____________   __          
 |  ___| \ | |_   _| ___ \ \ / /          
 | |__ |  \| | | | | |_/ /\ V /           
 |  __|| . ` | | | |    /  \ /            
 | |___| |\  | | | | |\ \  | |            
 \____/\_| \_/ \_/ \_| \_| \_/            
                                          
                                          

*/

#if !defined _INC_y_hooks
	#tryinclude "y_hooks"
#endif
#if !defined _INC_y_hooks
	#tryinclude "YSI_Coding\y_hooks"
#endif
#if !defined _INC_y_hooks
	#tryinclude "YSI\YSI_Coding\y_hooks"
#endif
#if !defined _INC_y_hooks
	#tryinclude <YSI_Coding\y_hooks>
#endif
#if !defined _INC_y_hooks
	#tryinclude <YSI\YSI_Coding\y_hooks>
#endif
#if !defined _INC_y_hooks
	#error Could not find y_hooks
#endif

#include "y_interiors_impl"