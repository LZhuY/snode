/*
 * lunar.h
 *
 *  Created on: Nov 2, 2011
 *      Author: siney
 */
#ifndef LUNAR_H
#define LUNAR_H

#include "lua.hpp"
#include <utility>
#include <string.h>
#include <ctype.h>
#include <type_traits>
#include "log.h"
#include "buf.h"
#include "typetrait.h"

class LAr;

namespace Lua {
    struct OptArg
    {
    };

    static constexpr OptArg opt;

    struct lstring
    {
        const char *str;
        size_t len;

        lstring() : str(NULL), len(0)
        {
        }

        explicit lstring(const char *s)
        {
            str = s;
            len = strlen(s);
        }

        operator const char*()
        {
            return str;
        }

        operator char*()
        {
            return (char*)str;
        }

        operator const unsigned char*()
        {
            return (const unsigned char*)str;
        }

        operator void*()
        {
            return (void*)str;
        }
    };

    struct ltableornil
    {
        int index;
        bool nil;

        ltableornil() : nil(true) {}

        operator int()
        {
            return index;
        }
    };

    struct ltable
    {
        int index;

        operator int()
        {
            return index;
        }
    };

    struct lfunction
    {
        int index;

        operator int()
        {
            return index;
        }
    };

    struct lfunctionref
    {
        lfunctionref() : ref(LUA_NOREF) {}

        int ref;
        
        operator int()
        {
            return ref;
        }
    };

    template<typename T,
        typename std::enable_if<std::is_integral<T>{}, int>::type=0>
    void peek(lua_State *L, int index, T &v)
    {
        v = (T)luaL_checkinteger(L, index);
    }

    template<typename T,
        typename std::enable_if<std::is_floating_point<T>{}, int>::type=0>
    void peek(lua_State *L, int index, T &v)
    {
        v = (T)luaL_checknumber(L, index);
    }

    inline void peek(lua_State *L, int index, bool &v)
    {
        luaL_checktype(L, index, LUA_TBOOLEAN);
        v = lua_toboolean(L, index) == 1;
    }

    inline void peek(lua_State *L, int index, ltable &v)
    {
        luaL_checktype(L, index, LUA_TTABLE);
        v.index = index;
    }

    inline void peek(lua_State *L, int index, ltableornil &v)
    {
        int ty = lua_type(L, index);
        if (ty != LUA_TNIL) {
            luaL_checktype(L, index, LUA_TTABLE);
            v.index = index;
            v.nil = false;
        }
    }

    inline void peek(lua_State *L, int index, lfunction &v)
    {
        luaL_checktype(L, index, LUA_TFUNCTION);
        v.index = index;
    }

    inline void peek(lua_State *L, int index, lfunctionref &v)
    {
        luaL_checktype(L, index, LUA_TFUNCTION);
        lua_pushvalue(L, index);
        v.ref = luaL_ref(L, LUA_REGISTRYINDEX);
    }

    inline void peek(lua_State *L, int index, lstring &v)
    {
        v.str = luaL_checklstring(L, index, &(v.len));
    }

    inline void peek(lua_State *L, int index, void* &v)
    {
        luaL_checktype(L, index, LUA_TUSERDATA);
        v = lua_touserdata(L, index);
    }

    inline void peek(lua_State *L, int index, char* &v)
    {
        luaL_checktype(L, index, LUA_TLIGHTUSERDATA);
        v = (char*)lua_topointer(L, index);
    }

    void peek(lua_State *L, int index, Buf &v);
    void peek(lua_State *L, int index, LAr* &v);

    inline void peek(lua_State *L, int index, const OptArg &v)
    {
    }

    template<typename T>
    void argPeek(lua_State *L, int index, int top, std::false_type, T& t)
    {
        if (index > top)
        {
            luaL_error(L, "function expected %d arguments at least", index);
        }
        else
        {
            peek(L, index, t);
        }
    }

    template<typename T>
    void argPeek(lua_State *L, int index, int top, std::true_type, T& t)
    {
        if (index <= top)
        {
            peek(L, index, t);
        }
    }

    inline void incrParseIndex(std::true_type, int &index)
    {
        
    }

    inline void incrParseIndex(std::false_type, int &index)
    {
        ++index;
    }

    template<typename T>
    void doArgParse(lua_State *L, int index, int top, std::true_type opt, T& t)
    {
        argPeek(L, index, top, opt, t);
    }

    template<typename T>
    void doArgParse(lua_State *L, int index, int top, std::false_type opt, T& t)
    {
        argPeek(L, index, top, opt, t);
    }

    template<typename T, typename... Args>
    void doArgParse(lua_State *L, int index, int top, std::true_type opt, T& t, Args&... args)
    {
        argPeek(L, index, top, opt, t);
        incrParseIndex(std::is_same<typename std::decay<T>::type, OptArg>(), index);
        doArgParse(L, index, top, opt, args...);
    }

    template<typename T, typename... Args>
    void doArgParse(lua_State *L, int index, int top, std::false_type opt, T& t, Args&... args)
    {
        argPeek(L, index, top, std::is_same<typename std::decay<T>::type, OptArg>(), t);
        incrParseIndex(std::is_same<typename std::decay<T>::type, OptArg>(), index);
        doArgParse(L, index, top, std::is_same<typename std::decay<T>::type, OptArg>(), args...);
    }

    template<typename T, typename... Args>
    void argParse(lua_State *L, T& t)
    {
        int top = lua_gettop(L);
        doArgParse(L, 1, top, std::is_same<typename std::decay<T>::type, OptArg>(), t);
    }

    template<typename T, typename... Args>
    void argParse(lua_State *L, T& t, Args&... args)
    {
        int top = lua_gettop(L);
        doArgParse(L, 1, top, std::is_same<typename std::decay<T>::type, OptArg>(), t, args...);
    }

    template<typename T, 
        typename std::enable_if<std::is_integral<T>{}, int>::type=0>
    void push(lua_State *L, const T v)
    {
        lua_pushinteger(L, v);
    }

    template<typename T, 
        typename std::enable_if<std::is_floating_point<T>{}, int>::type=0>
    void push(lua_State *L, const T v)
    {
        lua_pushnumber(L, v);
    }

    inline void push(lua_State *L, const bool v)
    {
        lua_pushboolean(L, (int)v);
    }

    inline void push(lua_State *L, const char *v)
    {
        lua_pushstring(L, v);
    }

    void push(lua_State *L, const Buf &v);
    void push(lua_State *L, const Buf *v);

    inline void push(lua_State *L, const std::string &v)
    {
        lua_pushlstring(L, v.data(), v.size());
    }

    inline void pushAll(lua_State *L)
    {
    }

    template<typename T>
    void pushAll(lua_State *L, T t)
    {
        push(L, t);
    }

    template<typename T, typename... Args>
    void pushAll(lua_State *L, T t, Args... args)
    {
        push(L, t);
        pushAll(L, args...);
    }

    template<typename... Args>
    int returnValue(lua_State *L, Args... args)
    {
        size_t size = sizeof...(args);
        pushAll(L, args...);

        return size;
    }

    /*! \class Lunar
      Binding the C++ class to lua,
      get more infomation to visit: http://lua-users.org/wiki/CppBindingWithLunar
      */
    template <typename T> class Lunar 
    {
        typedef struct { T *pT; } userdataType;
		public:
		typedef int (T::*mfp)(lua_State *L);
		typedef struct { const char *name; mfp mfunc; } RegType;

		static void Register(lua_State *L, const char* baseName = NULL) {
			lua_pushstring( L, T::className );
			lua_gettable( L, LUA_GLOBALSINDEX );
			if( lua_isnil(L, -1) )
			{
				lua_pop(L, 1);
				lua_newtable(L);
				lua_pushstring(L, T::className);
				lua_pushvalue(L, -2);
				// store method table in globals so that
				// scripts can add functions written in Lua.
				lua_settable(L, LUA_GLOBALSINDEX);
			}
			int methods = lua_gettop(L);

			luaL_newmetatable(L, T::className);
			int metatable = lua_gettop(L);

			// hide metatable from Lua getmetatable()
			lua_pushvalue(L, methods);
			set(L, metatable, "__metatable");

			lua_pushvalue(L, methods);
			set(L, metatable, "__index");

			lua_pushcfunction(L, tostring_T);
			set(L, metatable, "__tostring");

			lua_pushcfunction(L, gc_T);
			set(L, metatable, "__gc");

			lua_newtable(L);                // mt for method table
			lua_pushcfunction(L, new_T);
			lua_pushvalue(L, -1);           // dup new_T function
			set(L, methods, "new");         // add new_T to method table
			set(L, -3, "__call");           // mt.__call = new_T

			if( baseName ){
				lua_pushstring( L, baseName );
				lua_gettable( L, LUA_GLOBALSINDEX );    // get base_table
				if( lua_isnil(L, -1) )
				{
					lua_pop(L, 1);
					lua_newtable(L);
					lua_pushstring(L, baseName);
					lua_pushvalue(L, -2);
					lua_settable(L, LUA_GLOBALSINDEX);
				}
				set(L, -3, "__index");      // mt.__index = base_table
			}

			lua_setmetatable(L, methods);

			// fill method table with methods from class T
			for (int i = 0; T::methods[i].name; i++) {
				char name[128] = {0};
				//strcpy_s( name, 128, T::methods[i].name );
				strncpy( name, T::methods[i].name, 128 );
				*name = (char)tolower( *name );

				lua_pushstring(L, name);
				//lua_pushlightuserdata(L, (void*)l);
                lua_pushinteger(L, i);
				lua_pushcclosure(L, thunk, 1);
				lua_settable(L, methods);
			}

			const luaL_Reg * l = T::functions;
			for (; l->name; l++) {
				char name[128] = {0};
				strncpy( name, l->name, 128 );
				*name = (char)tolower( *name );
				lua_pushcfunction( L, l->func );
				lua_setfield( L, methods, name );
			}

			lua_pop(L, 2);  // drop metatable and method table
		}

		/*! call named lua method from userdata method table */
		static int call(lua_State *L, const char *method,
				int nargs=0, int nresults=LUA_MULTRET, int errfunc=0)
		{
			int base = lua_gettop(L) - nargs;  // userdata index
			if (!luaL_checkudata(L, base, T::className)) {
				lua_settop(L, base-1);           // drop userdata and args
				lua_pushfstring(L, "not a valid %s userdata", T::className);
				return -1;
			}

			lua_pushstring(L, method);         // method name
			lua_gettable(L, base);             // get method from userdata
			if (lua_isnil(L, -1)) {            // no method?
				lua_settop(L, base-1);         // drop userdata and args
				lua_pushfstring(L, "%s missing method '%s'", T::className, method);
				return -1;
			}
			lua_insert(L, base);               // put method under userdata, args

			int status = lua_pcall(L, 1+nargs, nresults, errfunc);  // call method
			if (status) {
				const char *msg = lua_tostring(L, -1);
				if (msg == NULL) msg = "(error with no message)";
				lua_pushfstring(L, "%s:%s status = %d\n%s",
						T::className, method, status, msg);
				lua_remove(L, base);           // remove old message
				return -1;
			}
			return lua_gettop(L) - base + 1;   // number of results
		}

		/*! push onto the Lua stack a userdata containing a pointer to T object */
		static int push(lua_State *L, T *obj, bool gc=false) {
			if (!obj) { lua_pushnil(L); return 0; }
			luaL_getmetatable(L, T::className);  // lookup metatable in Lua registry
			if (lua_isnil(L, -1)) luaL_error(L, "%s missing metatable", T::className);
			int mt = lua_gettop(L);
			subtable(L, mt, "userdata", "v");   
			userdataType *ud =
				static_cast<userdataType*>(pushuserdata(L, obj, sizeof(userdataType)));
			if (ud) {
				ud->pT = obj;  // store pointer to object in userdata
				lua_pushvalue(L, mt);
				lua_setmetatable(L, -2);
				if (gc == false) {
					lua_checkstack(L, 3);
					subtable(L, mt, "do not trash", "k");   
					lua_pushvalue(L, -2);
					lua_pushboolean(L, 1);
					lua_settable(L, -3);
					lua_pop(L, 1);
				}
			}
			lua_replace(L, mt);
			lua_settop(L, mt);
			return mt;  // index of userdata containing pointer to T object
		}

		/*! get userdata from Lua stack and return pointer to T object */
		static T *check(lua_State *L, int narg) {
			if(!lua_getmetatable(L, narg)) {
				luaL_typerror(L, narg, T::className);
				return NULL;
			}
			lua_pop(L, 1);

			userdataType *ud = static_cast<userdataType*>( lua_touserdata(L, narg) );
			if(!ud)
			{
				lua_getfield(L,narg,"__core");
				ud = static_cast<userdataType*>( lua_touserdata(L, -1) );
				lua_pop(L, 1);
				if(!ud)
				{
					luaL_error(L,"this a member function, need self ptr");
					return NULL;
				}
			}
			return ud->pT;  // pointer to T object
		}

        static T *check(lua_State *L, int narg,void* udata) {
            if(!lua_getmetatable(L, narg)) {
                luaL_typerror(L, narg, T::className);
                return NULL;
            }
            lua_pop(L, 1);

            userdataType *ud = static_cast<userdataType*>( udata );
            if(!ud)
            {
                lua_getfield(L,narg,"__core");
                ud = static_cast<userdataType*>( lua_touserdata(L, -1) );
                lua_pop(L, 1);
                if(!ud)
                {
                    luaL_error(L,"this a member function, need self ptr");
                    return NULL;
                }
            }
            return ud->pT;  // pointer to T object
        }

		private:
		Lunar();  // hide default constructor

		/*! member function dispatcher */
		static int thunk(lua_State *L) {
			// stack has userdata, followed by method args
			T *obj = check(L, 1);  // get 'self', or if you prefer, 'this'
			lua_remove(L, 1);  // remove self so member function args start at index 1
			// get member function from upvalue
			int i = (int)lua_tonumber(L, lua_upvalueindex(1)); // which function?
			return (obj->*(T::methods[i].mfunc))(L);  // call member function
		}

		/*! garbage collection metamethod */
		static int gc_T(lua_State *L) {
			if (luaL_getmetafield(L, 1, "do not trash")) {
				lua_pushvalue(L, 1);  // dup userdata
				lua_gettable(L, -2);
				if (!lua_isnil(L, -1)) return 0;  // do not delete object
			}
			userdataType *ud = static_cast<userdataType*>(lua_touserdata(L, 1));
			T *obj = ud->pT;
            if (obj) {
                //INFO("delete lua object %s",T::className);
                delete obj;  // call destructor for T objects
            }
			return 0;
		}

		// create a new T object and
		// push onto the Lua stack a userdata containing a pointer to T object
		static int new_T(lua_State *L) {
			lua_remove(L, 1);   // use classname:new(), instead of classname.new()
			T *obj = new T();  // call constructor for T objects
			push(L, obj, true); // gc_T will delete this object
			return 1;           // userdata containing pointer to T object
		}

		static int tostring_T (lua_State *L) {
			char buff[32];
			userdataType *ud = static_cast<userdataType*>(lua_touserdata(L, 1));
			T *obj = ud->pT;
			snprintf(buff, sizeof(buff), "%p", (void*)obj);
			lua_pushfstring(L, "%s (%s)", T::className, buff);
			return 1;
		}

		static void set(lua_State *L, int table_index, const char *key) {
			lua_pushstring(L, key);
			lua_insert(L, -2);  // swap value and key
			lua_settable(L, table_index);
		}

		static void weaktable(lua_State *L, const char *mode) {
			lua_newtable(L);
			lua_pushvalue(L, -1);  // table is its own metatable
			lua_setmetatable(L, -2);
			lua_pushliteral(L, "__mode");
			lua_pushstring(L, mode);
			lua_settable(L, -3);   // metatable.__mode = mode
		}

		static void subtable(lua_State *L, int tindex, const char *name, const char *mode) {
			lua_pushstring(L, name);
			lua_gettable(L, tindex);
			if (lua_isnil(L, -1)) {
				lua_pop(L, 1);
				lua_checkstack(L, 3);
				weaktable(L, mode);
				lua_pushstring(L, name);
				lua_pushvalue(L, -2);
				lua_settable(L, tindex);
			}
		}

		static void *pushuserdata(lua_State *L, void *key, size_t sz) {
			void *ud = 0;
			lua_pushlightuserdata(L, key);
			lua_gettable(L, -2);     // lookup[key]
			if (lua_isnil(L, -1)) {
				lua_pop(L, 1);         // drop nil
				lua_checkstack(L, 3);
				ud = lua_newuserdata(L, sz);  // create new userdata
				lua_pushlightuserdata(L, key);
				lua_pushvalue(L, -2);  // dup userdata
				lua_settable(L, -4);   // lookup[key] = userdata
			}
			return ud;
		}
	};

}

#define LUNAR_DECLARE_METHOD(Class, Name) {#Name, &Class::Name}

#define WHILE_TABLE(L) lua_pushnil(L); while( lua_next(L, -2) ) {
#define END_WHILE(L) lua_pop(L, 1); }

#define Class(class) #class

#define LUA_EXPORT(class) static const char className[]; \
		static Lua::Lunar<class>::RegType methods[]; \
		static luaL_reg functions[];

#define LUA_IMPL(class,name) const char class::className[] = #name; 
#define LUA_METD(class) Lua::Lunar<class>::RegType class::methods[] = {
#define LUA_METD_END  {NULL, NULL} };
#define LUA_FUNC(class) luaL_reg class::functions[] = {
#define LUA_FUNC_END     {NULL, NULL} };
#define L_FUNCTION(class, name) {#name, class::name},
#define L_METHOD(class, name) {#name, &class::name},

#define _L Lua::state::Instance()->get_handle()
#define lcall(args, rets) Lua::scriptCall(_L, args, rets)

#endif

