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
#include "Mona/TCPSender.h"
#include "Mona/AMFWriter.h"
#include "Mona/MemoryReader.h"
#include "Mona/RTMP/RTMP.h"


namespace Mona {

class RTMPSender : public TCPSender, virtual Object {
public:
	RTMPSender(const SocketAddress& address,const std::shared_ptr<RC4_KEY>& pEncryptKey);
	RTMPSender(const RTMPSender& sender);

	AMFWriter	writer;
	
	AMFWriter&	write(UInt32 id,AMF::ContentType type,UInt32 time=0,UInt32 streamId=0,MemoryReader* pData=NULL);
	
	const UInt8*		begin() { return writer.stream.data(); }
	UInt32				size() { return writer.stream.size(); }

private:
	bool				run(Exception& ex);
	void				pack(); // TODO remove??

	UInt32						_sizePos;
	UInt32						_chunkSize;
	RTMPChannel					_channel; // TODO not copied on RTMPSender(const RTMPSender& sender); ?
	std::shared_ptr<RC4_KEY>	_pEncryptKey;
	SocketAddress				_address;
};


} // namespace Mona
