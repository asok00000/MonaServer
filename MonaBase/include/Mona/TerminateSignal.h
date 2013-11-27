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
#include "Mona/Event.h"
#if defined(_WIN32)
#include "Windows.h"
#endif

namespace Mona {


class TerminateSignal : virtual Object {
public:
	TerminateSignal();
	virtual void wait();
	void set() { _Terminate.set(); }
protected:
    static Event			_Terminate;
#if defined(_WIN32)
	static BOOL __stdcall	ConsoleCtrlHandler(DWORD ctrlType);
#else
	sigset_t				_signalSet;
#endif
};




} // namespace Mona
