/*
Copyright 2014 Mona
mathieu.poux[a]gmail.com
jammetthomas[a]gmail.com

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License received along this program for more
details (or else see http://www.gnu.org/licenses/).

This file is a part of Mona.
*/

#pragma once

#include "Mona/Mona.h"
#include "Mona/MemoryReader.h"
#include "Mona/MemoryWriter.h"
#include "Mona/Time.h"
#include "Mona/Buffer.h"
#include <openssl/aes.h>
#include <math.h>

namespace Mona {

#define RTMFP_SYMETRIC_KEY (UInt8*)"Adobe Systems 02"
#define RTMFP_MIN_PACKET_SIZE	12
#define RTMFP_MAX_PACKET_LENGTH 1192
#define RTMFP_TIMESTAMP_SCALE	4
#define RTMFP_PACKET_SEND_SIZE	1215

class RTMFPEngine : virtual Object {
public:
	enum Direction {
		DECRYPT=0,
		ENCRYPT
	};
	enum Type {
		DEFAULT=0,
		EMPTY,
		SYMMETRIC
	};
	RTMFPEngine();
	RTMFPEngine(const UInt8* key,Direction direction);
	RTMFPEngine(const RTMFPEngine& other);
	RTMFPEngine(const RTMFPEngine& other,Type type);

	RTMFPEngine&  operator=(const RTMFPEngine& other);
	RTMFPEngine	next(Type type) { return RTMFPEngine(*this, type); }
	RTMFPEngine	next() { return RTMFPEngine(*this); }
	void		process(const UInt8* in,UInt8* out,UInt32 size);

	const Type	type;
private:
	static RTMFPEngine	_DefaultDecrypt;
	static RTMFPEngine	_DefaultEncrypt;

	Direction	_direction;
	AES_KEY		_key;
	
};


class RTMFP : virtual Static {
public:
	static UInt32				Unpack(MemoryReader& packet);
	static void					Pack(MemoryWriter& packet,UInt32 farId);

	static bool					ReadCRC(MemoryReader& packet);
	static void					WriteCRC(MemoryWriter& packet);
	static bool					Decode(Exception& ex,RTMFPEngine& aesDecrypt,MemoryReader& packet);
	static void					Encode(RTMFPEngine& aesEncrypt,MemoryWriter& packet);
	

	static void					ComputeAsymetricKeys(const Buffer<UInt8>& sharedSecret,
														const UInt8* initiatorNonce,UInt16 initNonceSize,
														const UInt8* responderNonce,UInt16 respNonceSize,
														 UInt8* requestKey,
														 UInt8* responseKey);

	static UInt16				TimeNow() { return Time(Mona::Time()); }
	static UInt16				Time(Int64 timeVal) { return (UInt32)round(timeVal / (1000.0*RTMFP_TIMESTAMP_SCALE)); }

private:
	static UInt16				CheckSum(MemoryReader& packet);
};

}  // namespace Mona
