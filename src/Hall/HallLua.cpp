#include "HallLua.h"

using namespace SNODE;

int HallLua::CallRpc(lua_State* L){
	int fid = luaL_checknumber(L, 1);
	int eid = luaL_checknumber(L, 1);
	int sid = luaL_checknumber(L, 1);
}