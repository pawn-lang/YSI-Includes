/*
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

#if defined MAX_REQUESTS
    #if !defined MAX_Y_REQUESTS
        #define MAX_Y_REQUESTS (MAX_REQUESTS)
    #endif
#elseif !defined MAX_Y_REQUESTS
    #define MAX_Y_REQUESTS (128)
#endif

static stock
    Func:YSI_g_sRequestCallbackData[MAX_Y_REQUESTS]<iisi>,
    Func:YSI_g_sRequestCallbackJson[MAX_Y_REQUESTS]<iii>;

stock Request:RequestCallback(RequestsClient:id, const path[], E_HTTP_METHOD:method, Func:callback<iisi>, body[] = "", Headers:headers = Headers:-1)
{
    new Request:ret = Request(id, path, method, "OnGetRequestData", body, headers);

    if (IsValidRequest(ret))
    {
        Indirect_Claim(callback);
        YSI_g_sRequestCallbackData[_:ret] = callback;
    }
    return ret;
}

stock Request:RequestJSONCallback(RequestsClient:id, const path[], E_HTTP_METHOD:method, Func:callback<iii>, Node:json = Node:-1, Headers:headers = Headers:-1)
{
    new Request:ret = RequestJSON(id, path, method, "OnGetRequestJson", json, headers);

    if (IsValidRequest(ret))
    {
        Indirect_Claim(callback);
        YSI_g_sRequestCallbackJson[_:ret] = callback;
    }
    return ret;
}

forward OnGetRequestData(Request:id, E_HTTP_STATUS:status, data[], dataLen);
public OnGetRequestData(Request:id, E_HTTP_STATUS:status, data[], dataLen)
{
    new Func:callback<iisi> = YSI_g_sRequestCallbackData[_:id];

    YSI_g_sRequestCallbackData[_:id] = Func:0<iisi>;

    @.callback(_:id, _:status, data, dataLen);

    Indirect_Release(callback);

    return 0;
}

forward OnGetRequestJson(Request:id, E_HTTP_STATUS:status, Node:node);
public OnGetRequestJson(Request:id, E_HTTP_STATUS:status, Node:node)
{
    new Func:callback<iii> = YSI_g_sRequestCallbackJson[_:id];

    YSI_g_sRequestCallbackJson[_:id] = Func:0<iii>;

    @.callback(_:id, _:status, _:node);

    Indirect_Release(callback);

    return 0;
}
