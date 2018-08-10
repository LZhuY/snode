#ifndef HALL_LUA_H
#define HALL_LUA_H

extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "../base/lunar.h"

namespace SNODE{

	class HallLua{
		public:
			HallLua(){}
			~HallLua(){}

			const char HallLua::className[] = "HallLua";

			int CallRpc(lua_State* L);

			Lunar<HallLua>::RegType HallLua::methods[] = {
  				LUNAR_DECLARE_METHOD(HallLua, CallRpc),
  				{0,0}
			};
	};
}

#endif