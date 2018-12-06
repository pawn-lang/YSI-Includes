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

stock Map(Func:cb<i>, const arr[], dest[], al = sizeof (arr), dl = sizeof (dest))
{
	for (new len = min(al, dl), i; i != len; ++i)
	{
		dest[i] = @.cb(arr[i]);
	}
}
#define Map({%0}%1) LAMBDA_i<Map>{%0}(%1)

stock Map_(Func:cb<i>, const arr[], len = sizeof (arr))
{
	for (new i; i != len; ++i)
	{
		@.cb(arr[i]);
	}
}
#define Map_({%0}%1) LAMBDA_i<Map_>{%0}(%1)

stock MapIdx(Func:cb<ii>, const arr[], dest[], al = sizeof (arr), dl = sizeof (dest))
{
	for (new len = min(al, dl), i; i != len; ++i)
	{
		dest[i] = @.cb(i, arr[i]);
	}
}
#define MapIdx({%0}%1) LAMBDA_ii<MapIdx>{%0}(%1)

stock MapIdx_(Func:cb<ii>, const arr[], len = sizeof (arr))
{
	for (new i; i != len; ++i)
	{
		@.cb(i, arr[i]);
	}
}
#define MapIdx_({%0}%1) LAMBDA_ii<MapIdx_>{%0}(%1)

stock ZipWith(Func:cb<ii>, const l[], const r[], dest[], ls = sizeof (l), rs = sizeof (r), ds = sizeof (dest))
{
	for (new len = min(ds, min(ls, rs)), i; i != len; ++i)
	{
		dest[i] = @.cb(l[i], r[i]);
	}
}
#define ZipWith({%0}%1) LAMBDA_ii<ZipWith>{%0}(%1)

stock ZipWith_(Func:cb<ii>, const l[], const r[], ls = sizeof (l), rs = sizeof (r))
{
	for (new len = min(ls, rs), i; i != len; ++i)
	{
		@.cb(l[i], r[i]);
	}
}
#define ZipWith_({%0}%1) LAMBDA_ii<ZipWith_>{%0}(%1)

stock ZipWith3(Func:cb<iii>, const l[], const m[], const r[], dest[], ls = sizeof (l), ms = sizeof (m), rs = sizeof (r), ds = sizeof (dest))
{
	for (new len = min(min(ms, ds), min(ls, rs)), i; i != len; ++i)
	{
		dest[i] = @.cb(l[i], m[i], r[i]);
	}
}
#define ZipWith3({%0}%1) LAMBDA_iii<ZipWith3>{%0}(%1)

stock ZipWith3_(Func:cb<iii>, const l[], const m[], const r[], ls = sizeof (l), ms = sizeof (m), rs = sizeof (r))
{
	for (new len = min(ms, min(ls, rs)), i; i != len; ++i)
	{
		@.cb(l[i], m[i], r[i]);
	}
}
#define ZipWith3_({%0}%1) LAMBDA_iii<ZipWith3_>{%0}(%1)

stock ZipWithIdx(Func:cb<iii>, const l[], const r[], dest[], ls = sizeof (l), rs = sizeof (r), ds = sizeof (dest))
{
	for (new len = min(ds, min(ls, rs)), i; i != len; ++i)
	{
		dest[i] = @.cb(i, l[i], r[i]);
	}
}
#define ZipWithIdx({%0}%1) LAMBDA_iii<ZipWithIdx>{%0}(%1)

stock ZipWithIdx_(Func:cb<iii>, const l[], const r[], ls = sizeof (l), rs = sizeof (r))
{
	for (new len = min(ls, rs), i; i != len; ++i)
	{
		@.cb(i, l[i], r[i]);
	}
}
#define ZipWithIdx_({%0}%1) LAMBDA_iii<ZipWithIdx_>{%0}(%1)

stock ZipWith3Idx(Func:cb<iiii>, const l[], const m[], const r[], dest[], ls = sizeof (l), ms = sizeof (m), rs = sizeof (r), ds = sizeof (dest))
{
	for (new len = min(min(ms, ds), min(ls, rs)), i; i != len; ++i)
	{
		dest[i] = @.cb(i, l[i], m[i], r[i]);
	}
}
#define ZipWith3Idx({%0}%1) LAMBDA_iiii<ZipWith3Idx>{%0}(%1)

stock ZipWith3Idx_(Func:cb<iiii>, const l[], const m[], const r[], ls = sizeof (l), ms = sizeof (m), rs = sizeof (r))
{
	for (new len = min(ms, min(ls, rs)), i; i != len; ++i)
	{
		@.cb(i, l[i], m[i], r[i]);
	}
}
#define ZipWith3Idx_({%0}%1) LAMBDA_iiii<ZipWith3Idx_>{%0}(%1)

stock FoldLIdx(Func:cb<iii>, n, const arr[], len = sizeof (arr))
{
	new
		cur = n;
	for (new i = 0; i != len; ++i)
	{
		cur = @.cb(i, cur, arr[i]);
	}
	return cur;
}
#define FoldLIdx({%0}%1) LAMBDA_iii<FoldLIdx>{%0}(%1)

stock ScanLIdx(Func:cb<iii>, n, const arr[], dest[], al = sizeof (arr), dl = sizeof (dest))
{
	if (!dl) return 0;
	new
		len = min(al, dl - 1),
		i = -1,
		cur = n;
	while (++i != len)
	{
		dest[i] = cur,
		cur = @.cb(i, cur, arr[i]);
	}
	dest[i] = cur;
	return 1;
}
#define ScanLIdx({%0}%1) LAMBDA_iii<ScanLIdx>{%0}(%1)

stock FoldRIdx(Func:cb<iii>, const arr[], n, len = sizeof (arr))
{
	new
		cur = n;
	while (len--)
	{
		cur = @.cb(i, arr[len], cur);
	}
	return cur;
}
#define FoldRIdx({%0}%1) LAMBDA_iii<FoldRIdx>{%0}(%1)

stock ScanRIdx(Func:cb<iii>, n, const arr[], dest[], al = sizeof (arr), dl = sizeof (dest))
{
	if (!dl) return 0;
	new
		len = min(al, dl - 1),
		cur = n;
	dest[len] = cur;
	while (len--)
	{
		dest[len] = cur = @.cb(i, arr[len], cur);
	}
	return 1;
}
#define ScanRIdx({%0}%1) LAMBDA_iii<ScanRIdx>{%0}(%1)

stock FoldL1Idx(Func:cb<iii>, const arr[], len = sizeof (arr))
{
	assert(len > 0);
	new
		cur = arr[0];
	for (new i = 1; i != len; ++i)
	{
		cur = @.cb(i, cur, arr[i]);
	}
	return cur;
}
#define FoldL1Idx({%0}%1) LAMBDA_iii<FoldL1Idx>{%0}(%1)

stock FoldR1Idx(Func:cb<iii>, const arr[], len = sizeof (arr))
{
	assert(len > 0);
	new
		cur = arr[--len];
	while (len--)
	{
		cur = @.cb(i, arr[len], cur);
	}
	return cur;
}
#define FoldR1Idx({%0}%1) LAMBDA_iii<FoldR1Idx>{%0}(%1)

stock FoldL(Func:cb<ii>, n, const arr[], len = sizeof (arr))
{
	new
		cur = n;
	for (new i = 0; i != len; ++i)
	{
		cur = @.cb(cur, arr[i]);
	}
	return cur;
}
#define FoldL({%0}%1) LAMBDA_ii<FoldL>{%0}(%1)

stock ScanL(Func:cb<ii>, n, const arr[], dest[], al = sizeof (arr), dl = sizeof (dest))
{
	if (!dl) return 0;
	new
		len = min(al, dl - 1),
		i = -1,
		cur = n;
	while (++i != len)
	{
		dest[i] = cur,
		cur = @.cb(cur, arr[i]);
	}
	dest[i] = cur;
	return 1;
}
#define ScanL({%0}%1) LAMBDA_ii<ScanL>{%0}(%1)

stock FoldR(Func:cb<ii>, const arr[], n, len = sizeof (arr))
{
	new
		cur = n;
	while (len--)
	{
		cur = @.cb(arr[len], cur);
	}
	return cur;
}
#define FoldR({%0}%1) LAMBDA_ii<FoldR>{%0}(%1)

stock ScanR(Func:cb<ii>, n, const arr[], dest[], al = sizeof (arr), dl = sizeof (dest))
{
	if (!dl) return 0;
	new
		len = min(al, dl - 1),
		cur = n;
	dest[len] = cur;
	while (len--)
	{
		dest[len] = cur = @.cb(arr[len], cur);
	}
	return 1;
}
#define ScanR({%0}%1) LAMBDA_ii<ScanR>{%0}(%1)

stock FoldL1(Func:cb<ii>, const arr[], len = sizeof (arr))
{
	assert(len > 0);
	new
		cur = arr[0];
	for (new i = 1; i != len; ++i)
	{
		cur = @.cb(cur, arr[i]);
	}
	return cur;
}
#define FoldL1({%0}%1) LAMBDA_ii<FoldL1>{%0}(%1)

stock FoldR1(Func:cb<ii>, const arr[], len = sizeof (arr))
{
	assert(len > 0);
	new
		cur = arr[--len];
	while (len--)
	{
		cur = @.cb(arr[len], cur);
	}
	return cur;
}
#define FoldR1({%0}%1) LAMBDA_ii<FoldR1>{%0}(%1)

stock bool:And(bool:arr[], len = sizeof (arr))
{
	while (len--)
	{
		if (!arr[len]) return false;
	}
	return true;
}

stock bool:Or(bool:arr[], len = sizeof (arr))
{
	while (len--)
	{
		if (arr[len]) return true;
	}
	return false;
}

stock bool:All(Func:cb<i>, const arr[], len = sizeof (arr))
{
	for (new i; i != len; ++i)
	{
		if (!@.cb(arr[i])) return false;
	}
	return true;
}
#define All({%0}%1) LAMBDA_i<All>{%0}(%1)

stock bool:Any(Func:cb<i>, const arr[], len = sizeof (arr))
{
	for (new i; i != len; ++i)
	{
		if (@.cb(arr[i])) return true;
	}
	return false;
}
#define Any({%0}%1) LAMBDA_i<Any>{%0}(%1)

stock bool:AllIdx(Func:cb<ii>, const arr[], len = sizeof (arr))
{
	for (new i; i != len; ++i)
	{
		if (!@.cb(i, arr[i])) return false;
	}
	return true;
}
#define AllIdx({%0}%1) LAMBDA_ii<AllIdx>{%0}(%1)

stock bool:AnyIdx(Func:cb<ii>, const arr[], len = sizeof (arr))
{
	for (new i; i != len; ++i)
	{
		if (@.cb(i, arr[i])) return true;
	}
	return false;
}
#define AnyIdx({%0}%1) LAMBDA_ii<AnyIdx>{%0}(%1)

stock Reverse(const arr[], len = sizeof (arr))
{
	new
		temp;
	for (new i = 0; j = len - 1; i < j; ++i, --j)
	{
		temp   = arr[i],
		arr[i] = arr[j],
		arr[j] = temp;
	}
	return 1;
}

stock bool:Elem(n, const arr[], len = sizeof (arr))
{
	while (len--)
	{
		if (arr[len] == n) return true;
	}
	return false;
}

stock bool:NotElem(n, const arr[], len = sizeof (arr))
{
	while (len--)
	{
		if (arr[len] == n) return false;
	}
	return true;
}

#define Just(%0) (YSI_gJust=_:%0,1)
#define Nothing  (0)

