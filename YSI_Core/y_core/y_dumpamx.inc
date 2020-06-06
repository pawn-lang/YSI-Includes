/*
	
	Now also provides OnCodeInit, which comes before OnScriptInit and should
	mostly be used for @emit code generation and other assembly related stuff
	(since it is called by the JIT if that exists).
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

#define DUMP_AMX_BLOCK_CELLS (12)
#define DUMP_AMX_BLOCK_BYTES (DUMP_AMX_BLOCK_CELLS * 4)

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

#define ENC_MAX 5
static stock DumpAMX_EncodeBytes(c, buffer[ENC_MAX])
{
	// Ported from the main compiler to ensure compatibility.
	buffer[4] = c & 0x7F,          // Store 7 bits.
	buffer[3] = (c >>> 7) & 0x7F,  // Store 7 bits.
	buffer[2] = (c >>> 14) & 0x7F, // Store 7 bits.
	buffer[1] = (c >>> 21) & 0x7F, // Store 7 bits.
	buffer[0] = (c >>> 28);        // Store 7 bits.

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
	} else while (compact++ != 4)
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

stock DumpAMX_Included_() {}

