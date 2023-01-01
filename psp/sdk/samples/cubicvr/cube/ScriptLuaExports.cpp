#include "ScriptLuaExports.h"

/*
int lua_waitVblankStart(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "wrong number of arguments");
	sceDisplayWaitVblankStart();
	return 0;
}
*/

// print all arguments, converted to strings
int lua_print(lua_State *L)
{
	int argc = lua_gettop(L);
	int n;
	for (n=1; n <= argc; n++) printf("%s\n", lua_tostring(L, n));
	return 0;
}
