/*----------------------------------------------------------------------------*-
					===========================
					Y Sever Includes - MD5 Core
					===========================
Description:
	Provides an implementation of the MD5 hashing algorithmfor PAWN, either for
	efficient and progressive hashing of chunks of data or just a straight hash
	of a single string.
Legal:
	The algorithm is due to Ron Rivest.  This code was
	written by Colin Plumb in 1993, no copyright is claimed.
	This code is in the public domain; do with it what you wish.
	
	Equivalent code is available from RSA Data Security, Inc.
	This code has been tested against that, and is equivalent,
	except that you don't need to include two pages of legalese
	with every copy.
	
	Converted to PAWN by Alex "Y_Less" Cole.
Version:
	0.1
Changelog:
	26/12/07:
		First version.
Functions:
	Public:
		-
	Core:
		-
	Stock:
		MD5_Hash - Takes a string and returns a 16 cell hash.
		MD5_Init - Initialises a hash structure.
		MD5_Update - Appends data to the hash in progress.
		MD5_Copy - Custom pack function.
		MD5_Final - Finalises a hash.
		MD5_File - Hashes a file incrementally.
		MD5_Data - Hashes binary data, not just strings.
	Static:
		MD5_Transform - Does the data mixing.
	Inline:
		MD5_Step - Does a single hash step.
	API:
		-
Callbacks:
	-
Definitions:
	-
Enums:
	E_MD5_CONTEXT - Data structure for an in progress hashing.
Macros:
	MD5_F1 - First hash part.
	MD5_F2 - Second hash part.
	MD5_F3 - Third hash part.
	MD5_F4 - Fourth hash part.
Tags:
	-
Variables:
	Global:
		-
	Static:
		-
Commands:
	-
Compile options:
	-
-*----------------------------------------------------------------------------*/

enum E_MD5_CONTEXT
{
	E_MD5_CONTEXT_BUF[4],
	E_MD5_CONTEXT_BITS[2],
	E_MD5_CONTEXT_IN[64 char]
}

#define MD5_F1(%1,%2,%3) (%3 ^ (%1 & (%2 ^ %3)))
#define MD5_F2(%1,%2,%3) MD5_F1(%3, %1, %2)
#define MD5_F3(%1,%2,%3) (%1 ^ %2 ^ %3)
#define MD5_F4(%1,%2,%3) (%2 ^ (%1 | ~%3))

/*----------------------------------------------------------------------------*-
Function:
	MD5_Hash
Params:
	str[] - String to hash.
Return:
	String representation of the hash.
Notes:
	The simplest way to hash a string, simply pass a string and get a 4 cell
	hash returned.
-*----------------------------------------------------------------------------*/

stock MD5_Hash(str[])
{
	new
		md5Data[E_MD5_CONTEXT],
		done,
		digest[33],
		len = strlen(str);
	MD5_Init(md5Data);
	len -= 64;
	while (done < len)
	{
		MD5_Update(md5Data, str[done], 64);
		done += 64;
	}
	len = (len + 64) - done;
	if (len)
	{
		MD5_Update(md5Data, str[done], len);
	}
	digest = MD5_Final(md5Data, true);
	return digest;
}

/*----------------------------------------------------------------------------*-
Function:
	MD5_Data
Params:
	data[] - Binary data to hash.
	len - Length of data to hash.
Return:
	String representation of the hash.
Notes:
	Hashes binary data, not just strings.
-*----------------------------------------------------------------------------*/

stock MD5_Data(data[], len)
{
	new
		md5Data[E_MD5_CONTEXT],
		done,
		digest[33];
	MD5_Init(md5Data);
	len -= 64;
	while (done < len)
	{
		MD5_Update(md5Data, data[done], 64);
		done += 64;
	}
	len = (len + 64) - done;
	if (len)
	{
		MD5_Update(md5Data, data[done], len);
	}
	digest = MD5_Final(md5Data, true);
	return digest;
}

/*----------------------------------------------------------------------------*-
Function:
	MD5_File
Params:
	filename[] - File to hash.
Return:
	-
Notes:
	Hashes the file incrementally, not in one huge chunk.
-*----------------------------------------------------------------------------*/

stock MD5_File(filename[])
{
	
	new
		digest[33],
		File:fHnd = fopen(filename, io_read);
	if (fHnd)
	{
		new
			md5Data[E_MD5_CONTEXT],
			data[64],
			len;
		MD5_Init(md5Data);
		MD5_File_loop:
		len = fblockread(fHnd, data);
		if (len)
		{
			MD5_Update(md5Data, data, len);
			goto MD5_File_loop;
		}
		digest = MD5_Final(md5Data, true);
		fclose(fHnd);
	}
	return digest;
}

/*----------------------------------------------------------------------------*-
Function:
	MD5_Init
Params:
	ctx[E_MD5_CONTEXT] - Hash data.
Return:
	-
Notes:
	Sets up the data for hashing.
-*----------------------------------------------------------------------------*/

stock MD5_Init(ctx[E_MD5_CONTEXT])
{
	ctx[E_MD5_CONTEXT_BUF][0] = 0x67452301;
	ctx[E_MD5_CONTEXT_BUF][1] = 0xEFCDAB89;
	ctx[E_MD5_CONTEXT_BUF][2] = 0x98BADCFE;
	ctx[E_MD5_CONTEXT_BUF][3] = 0x10325476;
	ctx[E_MD5_CONTEXT_BITS][0] = 0;
	ctx[E_MD5_CONTEXT_BITS][1] = 0;
}

/*----------------------------------------------------------------------------*-
Function:
	MD5_Update
Params:
	ctx[E_MD5_CONTEXT] - Hash data.
	data[] - String to append.
	len - Length of string to append.
Return:
	-
Notes:
	Adds data to the current hash.
-*----------------------------------------------------------------------------*/

stock MD5_Update(ctx[E_MD5_CONTEXT], data[], len)
{
	new
		t = ctx[E_MD5_CONTEXT_BITS][0],
		s,
		buf = 0;
	if ((ctx[E_MD5_CONTEXT_BITS][0] = t + (len << 3)) < t)
	{
		ctx[E_MD5_CONTEXT_BITS][1]++;
	}
	ctx[E_MD5_CONTEXT_BITS][1] += len >>> 29;
	t = (t >>> 3) & 0x3F;
	if (t)
	{
		s = 64 - t;
		if (len < s)
		{
			MD5_Copy(ctx[E_MD5_CONTEXT_IN], data, t, len);
			return;
		}
		MD5_Copy(ctx[E_MD5_CONTEXT_IN], data, t, s);
		MD5_Transform(ctx[E_MD5_CONTEXT_BUF], ctx[E_MD5_CONTEXT_IN]);
		buf += s;
		len -= s;
	}
	while (len >= 64)
	{
		MD5_Copy(ctx[E_MD5_CONTEXT_IN], data[buf], 0, 64);
		MD5_Transform(ctx[E_MD5_CONTEXT_BUF], ctx[E_MD5_CONTEXT_IN]);
		buf += 64;
		len -= 64;
	}
	MD5_Copy(ctx[E_MD5_CONTEXT_IN], data[buf], 0, len);
}

/*----------------------------------------------------------------------------*-
Function:
	MD5_Copy
Params:
	dest[] - Packed destination array.
	src[] - Unpacked source array.
	start - Start BYTE in the dest array.
	len - Length of data to copy.
Return:
	-
Notes:
	Custom strpack implementation allowing offset starts.
-*----------------------------------------------------------------------------*/

stock MD5_Copy(dest[], src[], start, len)
{
	new
		i = start >>> 2,
		j = 0,
		ch;
	while (j < len)
	{
		ch = src[j++] & 0xFF;
		switch (start++ & 0x03)
		{
			case 0:
			{
				dest[i] = ch;
			}
			case 1:
			{
				dest[i] |= ch << 8;
			}
			case 2:
			{
				dest[i] |= ch << 16;
			}
			case 3:
			{
				dest[i++] |= ch << 24;
			}
		}
	}
}

/*----------------------------------------------------------------------------*-
Function:
	MD5_Final
Params:
	ctx[E_MD5_CONTEXT] - Hash data.
	string - Wehter or not to create a string version of the hash.
Return:
	-
Notes:
	Terminates the pending data, appends the length and finishes hashing.
-*----------------------------------------------------------------------------*/

stock MD5_Final(ctx[E_MD5_CONTEXT], string = false)
{
	new
		count,
		index,
		digest[33];
	count = (ctx[E_MD5_CONTEXT_BITS][0] >>> 3) & 0x3F;
	if (!(count & 0x03))
	{
		ctx[E_MD5_CONTEXT_IN][count / 4] = 0;
	}
	ctx[E_MD5_CONTEXT_IN][count / 4] |= (0x80 << (8 * (count & 0x03)));
	index = (count / 4) + 1;
	count = 64 - 1 - count;
	if (count < 8)
	{
		while (index < 64 char)
		{
			ctx[E_MD5_CONTEXT_IN][index++] = 0;
		}
		MD5_Transform(ctx[E_MD5_CONTEXT_BUF], ctx[E_MD5_CONTEXT_IN]);
		index = 0;
		while (index < 56 char)
		{
			ctx[E_MD5_CONTEXT_IN][index++] = 0;
		}
	}
	else
	{
		while (index < 56 char)
		{
			ctx[E_MD5_CONTEXT_IN][index++] = 0;
		}
	}
	ctx[E_MD5_CONTEXT_IN][14] = ctx[E_MD5_CONTEXT_BITS][0];
	ctx[E_MD5_CONTEXT_IN][15] = ctx[E_MD5_CONTEXT_BITS][1];
	MD5_Transform(ctx[E_MD5_CONTEXT_BUF], ctx[E_MD5_CONTEXT_IN]);
	if (string)
	{
		index = 0;
		do
		{
			format(digest, sizeof (digest), "%s%02x", digest, (ctx[E_MD5_CONTEXT_BUF][index / 4] >> ((index & 0x03) * 8)) & 0xFF);
		}
		while (++index < 16);
	}
	return digest;
}

/*----------------------------------------------------------------------------*-
Function:
	MD5_Step
Params:
	func - Hash function to use.
	a - Data cell 1.
	b - Data cell 2.
	c - Data cell 3.
	d - Data cell 4.
	data - New input.
	s - Seed.
Return:
	-
Notes:
	Does a single hash step.
-*----------------------------------------------------------------------------*/

#define MD5_Step(%1,%2,%3,%4,%5,%6,%7) \
	%2 += %1(%3, %4, %5) + %6, %2 = %2 << %7 | %2 >>> (32 - %7), %2 += %3

/*----------------------------------------------------------------------------*-
Function:
	MD5_Transform
Params:
	buf[] - Current hash.
	in[] - New data.
Return:
	-
Notes:
	Does the hashing steps on the current data.
-*----------------------------------------------------------------------------*/

static stock MD5_Transform(buf[], in[])
{
	new
		a = buf[0],
		b = buf[1],
		c = buf[2],
		d = buf[3];
	#pragma tabsize 4
	MD5_Step(MD5_F1, a, b, c, d, in[0]  + 0xD76AA478, 7);
	MD5_Step(MD5_F1, d, a, b, c, in[1]  + 0xE8C7B756, 12);
	MD5_Step(MD5_F1, c, d, a, b, in[2]  + 0x242070DB, 17);
	MD5_Step(MD5_F1, b, c, d, a, in[3]  + 0xC1BDCEEE, 22);
	MD5_Step(MD5_F1, a, b, c, d, in[4]  + 0xF57C0FAF, 7);
	MD5_Step(MD5_F1, d, a, b, c, in[5]  + 0x4787C62A, 12);
	MD5_Step(MD5_F1, c, d, a, b, in[6]  + 0xA8304613, 17);
	MD5_Step(MD5_F1, b, c, d, a, in[7]  + 0xFD469501, 22);
	MD5_Step(MD5_F1, a, b, c, d, in[8]  + 0x698098D8, 7);
	MD5_Step(MD5_F1, d, a, b, c, in[9]  + 0x8B44F7AF, 12);
	MD5_Step(MD5_F1, c, d, a, b, in[10] + 0xFFFF5BB1, 17);
	MD5_Step(MD5_F1, b, c, d, a, in[11] + 0x895CD7BE, 22);
	MD5_Step(MD5_F1, a, b, c, d, in[12] + 0x6B901122, 7);
	MD5_Step(MD5_F1, d, a, b, c, in[13] + 0xFD987193, 12);
	MD5_Step(MD5_F1, c, d, a, b, in[14] + 0xA679438E, 17);
	MD5_Step(MD5_F1, b, c, d, a, in[15] + 0x49B40821, 22);
	MD5_Step(MD5_F2, a, b, c, d, in[1]  + 0xF61E2562, 5);
	MD5_Step(MD5_F2, d, a, b, c, in[6]  + 0xC040B340, 9);
	MD5_Step(MD5_F2, c, d, a, b, in[11] + 0x265E5A51, 14);
	MD5_Step(MD5_F2, b, c, d, a, in[0]  + 0xE9B6C7AA, 20);
	MD5_Step(MD5_F2, a, b, c, d, in[5]  + 0xD62F105D, 5);
	MD5_Step(MD5_F2, d, a, b, c, in[10] + 0x02441453, 9);
	MD5_Step(MD5_F2, c, d, a, b, in[15] + 0xD8A1E681, 14);
	MD5_Step(MD5_F2, b, c, d, a, in[4]  + 0xE7D3FBC8, 20);
	MD5_Step(MD5_F2, a, b, c, d, in[9]  + 0x21E1CDE6, 5);
	MD5_Step(MD5_F2, d, a, b, c, in[14] + 0xC33707D6, 9);
	MD5_Step(MD5_F2, c, d, a, b, in[3]  + 0xF4D50D87, 14);
	MD5_Step(MD5_F2, b, c, d, a, in[8]  + 0x455A14ED, 20);
	MD5_Step(MD5_F2, a, b, c, d, in[13] + 0xA9E3E905, 5);
	MD5_Step(MD5_F2, d, a, b, c, in[2]  + 0xFCEFA3F8, 9);
	MD5_Step(MD5_F2, c, d, a, b, in[7]  + 0x676F02D9, 14);
	MD5_Step(MD5_F2, b, c, d, a, in[12] + 0x8D2A4C8A, 20);
	MD5_Step(MD5_F3, a, b, c, d, in[5]  + 0xFFFA3942, 4);
	MD5_Step(MD5_F3, d, a, b, c, in[8]  + 0x8771F681, 11);
	MD5_Step(MD5_F3, c, d, a, b, in[11] + 0x6D9D6122, 16);
	MD5_Step(MD5_F3, b, c, d, a, in[14] + 0xFDE5380C, 23);
	MD5_Step(MD5_F3, a, b, c, d, in[1]  + 0xA4BEEA44, 4);
	MD5_Step(MD5_F3, d, a, b, c, in[4]  + 0x4BDECFA9, 11);
	MD5_Step(MD5_F3, c, d, a, b, in[7]  + 0xF6BB4B60, 16);
	MD5_Step(MD5_F3, b, c, d, a, in[10] + 0xBEBFBC70, 23);
	MD5_Step(MD5_F3, a, b, c, d, in[13] + 0x289B7EC6, 4);
	MD5_Step(MD5_F3, d, a, b, c, in[0]  + 0xEAA127FA, 11);
	MD5_Step(MD5_F3, c, d, a, b, in[3]  + 0xD4EF3085, 16);
	MD5_Step(MD5_F3, b, c, d, a, in[6]  + 0x04881D05, 23);
	MD5_Step(MD5_F3, a, b, c, d, in[9]  + 0xD9D4D039, 4);
	MD5_Step(MD5_F3, d, a, b, c, in[12] + 0xE6DB99E5, 11);
	MD5_Step(MD5_F3, c, d, a, b, in[15] + 0x1FA27CF8, 16);
	MD5_Step(MD5_F3, b, c, d, a, in[2]  + 0xC4AC5665, 23);
	MD5_Step(MD5_F4, a, b, c, d, in[0]  + 0xF4292244, 6);
	MD5_Step(MD5_F4, d, a, b, c, in[7]  + 0x432AFF97, 10);
	MD5_Step(MD5_F4, c, d, a, b, in[14] + 0xAB9423A7, 15);
	MD5_Step(MD5_F4, b, c, d, a, in[5]  + 0xFC93A039, 21);
	MD5_Step(MD5_F4, a, b, c, d, in[12] + 0x655B59C3, 6);
	MD5_Step(MD5_F4, d, a, b, c, in[3]  + 0x8F0CCC92, 10);
	MD5_Step(MD5_F4, c, d, a, b, in[10] + 0xFFEFF47D, 15);
	MD5_Step(MD5_F4, b, c, d, a, in[1]  + 0x85845DD1, 21);
	MD5_Step(MD5_F4, a, b, c, d, in[8]  + 0x6FA87E4F, 6);
	MD5_Step(MD5_F4, d, a, b, c, in[15] + 0xFE2CE6E0, 10);
	MD5_Step(MD5_F4, c, d, a, b, in[6]  + 0xA3014314, 15);
	MD5_Step(MD5_F4, b, c, d, a, in[13] + 0x4E0811A1, 21);
	MD5_Step(MD5_F4, a, b, c, d, in[4]  + 0xF7537E82, 6);
	MD5_Step(MD5_F4, d, a, b, c, in[11] + 0xBD3AF235, 10);
	MD5_Step(MD5_F4, c, d, a, b, in[2]  + 0x2AD7D2BB, 15);
	MD5_Step(MD5_F4, b, c, d, a, in[9]  + 0xEB86D391, 21);
	#pragma tabsize 4
	buf[0] += a;
	buf[1] += b;
	buf[2] += c;
	buf[3] += d;
}
