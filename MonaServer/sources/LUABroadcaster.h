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

#include "Script.h"
#include "Broadcaster.h"

class LUABroadcaster {
public:

	static void Init(lua_State *pState, Broadcaster& broadcaster);
	static int Get(lua_State *pState);
	static int Set(lua_State *pState);
	static int Item(lua_State *pState);

	static void AddServer(lua_State* pState, Broadcaster& broadcaster, const std::string& address, int indexServer);
	static void RemoveServer(lua_State* pState, Broadcaster& broadcaster, const std::string& address);

protected:
	static int Broadcast(lua_State *pState);
};
