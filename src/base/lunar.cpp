/*
 * lunar.cpp
 *
 *  Created on: Nov 2, 2011
 *      Author: siney
 */
#include "lunar.h"
#include "celltype.h"
#include "lar.h"
#include "net.h"
#include "luasvr.h"

#include <string.h>
#include <assert.h>

namespace Lua
{
    void push(lua_State *L, Buf &v)
    {
        LAr* lar = new LAr(std::move(v));
        Lua::Lunar<LAr >::push(L, lar, true);
    }

    void push(lua_State *L, const Buf *v)
    {
        if (v == NULL)
        {
            lua_pushnil(L);
        }
        else
        {
            push(L, (Buf&)*v);
        }
    }

    void peek(lua_State *L, int index, Buf &v)
    {
        LAr* ar = Lua::Lunar<LAr>::check(L, index);
        v.clonefrom(ar);
    }

    void peek(lua_State *L, int index, LAr* &v)
    {
        LAr *ar = Lua::Lunar<LAr>::check(L, index);
        v = ar;
    }
}

