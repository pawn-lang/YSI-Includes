#if defined _INC_y_dumpamx
	#endinput
#endif
#define _INC_y_dumpamx

/**
 * <library
 *   name="y_dumpamx"
 *   version="1.0"
 *   license="(c) 2022 YSI contibutors, licensed under MPL 1.1"
 *   summary="Generate a new AMX from the current state of code."
 * >
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     <p>This library allows you to dump the current state of the AMX to a
 *     file.  If this dumping is done by defining <c>YSI_YES_MODE_CACHE</c>,
 *     then the file will be generated after <c>OnCodeInit</c> is complete, with
 *     all YSI constructs pre-compiled and included in the resulting file.  The
 *     new code will also start up and resume from the point after the dump was
 *     completed.</p>
 *   </remarks>
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

/// <p/>

#include "..\..\YSI_Core\y_utils"
#include "..\..\YSI_Server\y_thirdpartyinclude"

#define DUMP_AMX_BLOCK_CELLS (12)
#define DUMP_AMX_BLOCK_BYTES (DUMP_AMX_BLOCK_CELLS * 4)

/*-------------------------------------------------------------------------*//**
 * <library>y_dumpamx</library>
 * <param name="file">A handle to the file to write to.</param>
 * <param name="data">A buffer for encoding data in to.</param>
 * <param name="offset">The current position in the file.</param>
 * <param name="compact">Should compact encoding be used.</param>
 * <remarks>
 *   Dump the data segment (<c>DAT</c>) to the file.  The <c>data</c> buffer is
 *   used for temporary encoding in case the segments being written do not align
 *   exactly to cell boundaries once compacted.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:DumpAMX_WriteAMXData(File:file, data[], &offset, compact)
{
	new hdr[AMX_HDR];
	GetAmxHeader(hdr);

	new dat = 0;
	new end = hdr[AMX_HDR_HEA] - hdr[AMX_HDR_DAT];

	while (dat < end)
	{
		DumpAMX_WriteEncoded(file, data, offset, compact, ReadAmxMemory(dat));
		dat += 4;
	}

	return true;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_dumpamx</library>
 * <param name="file">A handle to the file to write to.</param>
 * <param name="data">A buffer for encoding data in to.</param>
 * <param name="offset">The current position in the file.</param>
 * <param name="compact">Should compact encoding be used.</param>
 * <remarks>
 *   Write the AMX header to the file.  This basically just copies the header in
 *   its entirety, with only a small bit of customisation for natives to not also
 *   store their pointers.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:DumpAMX_WriteAMXHeader(File:file, data[], &offset, compact)
{
	#pragma unused compact

	new plain_amxhdr[AMX_HDR_CELLS];
	GetRawAmxHeader(plain_amxhdr);

	// Write the header with masked flags.
	plain_amxhdr[2] &= 0xFFFF0006;
	fblockwrite(file, plain_amxhdr, 56 / 4);

	// Write the rest of the header without native function addresses.
	new dat = plain_amxhdr[AMX_HDR_OFFSET_DAT / 4];

	if (dat & 0x03)
	{
		// `dat` should always be 4-byte aligned.
		return false;
	}

	new start = 0;
	new end = 0;

	// YSI plays with the public function table start so don't use it directly.
	// amx_assembly had this value wrong for a while.
	start = /*AMX_HDR_BYTES*/ 56 - dat;

	for (end = plain_amxhdr[AMX_HDR_OFFSET_NATIVES / 4] - dat; start < end; start += 8)
	{
		data[0] = ReadAmxMemory(start + 0);
		data[1] = ReadAmxMemory(start + 4);
		fblockwrite(file, data, 2);
	}

	// Write the natives without their resolved address.
	data[0] = 0;
	for (end = plain_amxhdr[AMX_HDR_OFFSET_LIBRARIES / 4] - dat; start < end; start += 8)
	{
		data[1] = ReadAmxMemory(start + 4);
		fblockwrite(file, data, 2);
	}

	// The first half of the header is guaranteed to be a multiple of 4 bytes long, i.e. an exact
	// number of cells.  The second half isn't.
	for (end = (plain_amxhdr[AMX_HDR_OFFSET_COD / 4] & ~0x07) - dat; start < end; start += 8)
	{
		data[0] = ReadAmxMemory(start + 0);
		data[1] = ReadAmxMemory(start + 4);
		fblockwrite(file, data, 2);
	}

	// Straggling bytes.
	offset = plain_amxhdr[AMX_HDR_OFFSET_COD / 4] - dat - start;

	data[0] = ReadAmxMemory(start + 0);
	data[1] = ReadAmxMemory(start + 4);

	return true;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_dumpamx</library>
 * <param name="c">The cell to encode.</param>
 * <param name="buffer">The array in which to write the encoding.</param>
 * <remarks>
 *   Ported directly from the compiler, this encodes cells by first converting
 *   them to five bytes, then ignoring any leading zeros.  This results is a
 *   slightly smaller storage size for the vast majority of data.
 * </remarks>
 *//*------------------------------------------------------------------------**/

#define ENC_MAX 5
static stock DumpAMX_EncodeBytes(c, buffer[ENC_MAX])
{
	// Ported from the main compiler to ensure compatibility.
	buffer[4] = c & 0x7F,          // Store 7 bits.
	buffer[3] = (c >>> 7) & 0x7F,  // Store 7 bits.
	buffer[2] = (c >>> 14) & 0x7F, // Store 7 bits.
	buffer[1] = (c >>> 21) & 0x7F, // Store 7 bits.
	buffer[0] = (c >>> 28);        // Store 4 bits.

	new index = -1;

	// Skip leading zeros.
	while (index < ENC_MAX - 2 && buffer[index + 1] == 0 && (buffer[index + 2] & 0x40) == 0)
		++index;

	// Skip leading -1s.
	if (index == -1 && buffer[0] == 0x0F && (buffer[1] & 0x40) != 0)
		++index;

	while (index < ENC_MAX - 2 && buffer[index + 1] == 0x7F && (buffer[index + 2] & 0x40) != 0)
		++index;

	c = ++index;
	while (index < ENC_MAX - 1)
		buffer[index++] |= 0x80;

	return c;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_dumpamx</library>
 * <param name="file">A handle to the file to write to.</param>
 * <param name="data">A buffer for encoding data in to.</param>
 * <param name="offset">The current position in the file.</param>
 * <param name="compact">Should compact encoding be used.</param>
 * <param name="c">The cell to write.</param>
 * <remarks>
 *   Take a single cell, encode it, store the encoding in the buffer, then write
 *   the buffer to the file if it is full.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock DumpAMX_WriteEncoded(File:file, data[], &offset, compact, c)
{
	if (compact)
	{
		new buffer[ENC_MAX];
		new index = DumpAMX_EncodeBytes(c, buffer);
		while (index < ENC_MAX)
		{
			data{offset ^ 0x03} = buffer[index++];
			if (++offset == DUMP_AMX_BLOCK_BYTES)
			{
				// Write the whole cell.
				fblockwrite(file, data, DUMP_AMX_BLOCK_CELLS);
				offset = 0;
			}
		}
	}
	else while (compact++ != 4)
	{
		data{offset ^ 0x03} = c & 0xFF;
		if (++offset == DUMP_AMX_BLOCK_BYTES)
		{
			// Write the whole cell.
			fblockwrite(file, data, DUMP_AMX_BLOCK_CELLS);
			offset = 0;
		}
		c >>>= 8;
	}
}

/*-------------------------------------------------------------------------*//**
 * <library>y_dumpamx</library>
 * <param name="file">A handle to the file to write to.</param>
 * <param name="data">A buffer for encoding data in to.</param>
 * <param name="offset">The current position in the file.</param>
 * <param name="compact">Should compact encoding be used.</param>
 * <remarks>
 *   Dump the code segment (<c>COD</c>) to the file.  Does basic code
 *   decompilation to extract parameters and convert absolute addresses (resolved
 *   when the AMX is loaded) back to the relative addresses stored in the AMX.
 *   Also converts any <c>SYSREQ.D</c> opcodes back to <c>SYSREQ.C</c>.
 * </remarks>
 *//*------------------------------------------------------------------------**/

static stock bool:DumpAMX_WriteAMXCode(File:file, data[], &offset, compact)
{
	new ctx[DisasmContext];
	DisasmInit(ctx);
	
	new base = 0;
	{
		new hdr[AMX_HDR];
		GetAmxHeader(hdr);
		base = GetAmxBaseAddress() + hdr[AMX_HDR_COD];
	}

	while (DisasmGetNextIp(ctx) < ctx[DisasmContext_end_ip])
	{
		if (!DisasmDecodeInsn(ctx))
		{
			new cip = DisasmGetNextIp(ctx);
			DumpAMX_WriteEncoded(file, data, offset, compact, ReadAmxMemory(cip));
			//fblockwrite(file, data, 1);
			continue;
		}

		new Opcode:opcode = DisasmGetOpcode(ctx);

		switch (opcode)
		{
			case OP_CASETBL:
			{
				new num = DisasmGetNumOperands(ctx);
				new rel_addr = DisasmGetOperand(ctx, 1) - base;
				DumpAMX_WriteEncoded(file, data, offset, compact, _:opcode);
				DumpAMX_WriteEncoded(file, data, offset, compact, num);
				DumpAMX_WriteEncoded(file, data, offset, compact, rel_addr);
				for (new i = 1; i <= num; i++)
				{
					new val = DisasmGetOperand(ctx, i * 2);
					rel_addr = DisasmGetOperand(ctx, i * 2 + 1) - base;
					DumpAMX_WriteEncoded(file, data, offset, compact, val);
					DumpAMX_WriteEncoded(file, data, offset, compact, rel_addr);
				}
			}
			case OP_SYSREQ_D:
			{
				// Convert back to SYSREQ.C
				new address = DisasmGetOperand(ctx);
				new index = GetNativeIndexFromAddress(address);
				DumpAMX_WriteEncoded(file, data, offset, compact, _:OP_SYSREQ_C);
				DumpAMX_WriteEncoded(file, data, offset, compact, index);
			}
			default:
			{
				DumpAMX_WriteEncoded(file, data, offset, compact, _:opcode);
				new n = DisasmGetNumOperands(ctx);
				for (new i = 0; i < n; i++)
				{
					DumpAMX_WriteEncoded(file, data, offset, compact, DisasmGetOperandReloc(ctx, i));
				}
			}
		}
	}

	return true;
}
#undef ENC_MAX

/*-------------------------------------------------------------------------*//**
 * <library>y_dumpamx</library>
 * <param name="filename">The name of the output file.</param>
 * <remarks>
 *   Dump the currently running AMX to a file.  Although the AMX has surely just
 *   been loaded <em>from</em> a file, this isn't pointless as a lot of code can
 *   be (and is, with YSI) modified on initial load.  Thus this feature can do
 *   the generation once, and store the result in to a new file that can be
 *   loaded repeatedly.  Of course this is still pointless if your code changes
 *   frequently, as the saving is quite slow and would need to be done after
 *   every compile.  If a script is only likely to be loaded once after a
 *   compile, with subsequent loads being for a new version, these is no
 *   advantage to using this caching.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock bool:DumpAMX_Write(const filename[])
{
	new File:file = fopen(filename, io_write);
	if (file)
	{
		new
			data[DUMP_AMX_BLOCK_CELLS],
			offset = 0,
			compact = 0;

		{
			new hdr[AMX_HDR];
			GetAmxHeader(hdr);
			compact = hdr[AMX_HDR_FLAGS] & 2;
		}

		DumpAMX_WriteAMXHeader(file, data, offset, compact);
		DumpAMX_WriteAMXCode(file, data, offset, compact);
		DumpAMX_WriteAMXData(file, data, offset, compact);

		compact = (offset + 3) / 4;
		if (compact)
		{
			fblockwrite(file, data, compact);
		}

		// Write the new length at the start.
		fseek(file, 0, seek_start);
		data[0] = flength(file) - (compact * 4 - offset);
		fblockwrite(file, data, 1);
		fclose(file);
		return true;
	}
	return false;
}

/*-------------------------------------------------------------------------*//**
 * <library>y_dumpamx</library>
 * <remarks>
 *   Just a symbol that can be detected to prove that this library was included.
 * </remarks>
 *//*------------------------------------------------------------------------**/

stock DumpAMX_Included_() {}

