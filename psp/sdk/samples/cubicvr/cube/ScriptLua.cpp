#include "ScriptLua.h"

lua_State *L;
char* scriptFilename;

void ScriptLoad(char** argv)
{
	// script file must be in the same directory where the program started
	const char* scriptName = "script.lua";
	scriptFilename = (char*) malloc(strlen(argv[0]) + strlen(scriptName));
	strcpy(scriptFilename, argv[0]);
	char* end = strrchr(scriptFilename, '/');
	end++;
	*end = 0;
	strcat(scriptFilename, scriptName);

	// init Lua and load all libraries
	L = lua_open();
	luaL_openlibs(L);
	
	// register our own functions
	lua_register(L, "print", lua_print);
	//lua_register(L, "waitVblankStart", lua_waitVblankStart);

	// load script
	int status = luaL_loadfile(L, scriptFilename);
	
	// call script
	if (status == 0) status = lua_pcall(L, 0, LUA_MULTRET, 0);
	
	// show error, if any
	if (status != 0) {
		printf("error: %s\n", lua_tostring(L, -1));
		lua_pop(L, 1);  // remove error message
	}
}

void ScriptClose()
{
	// cleanup
	lua_close(L);
	free(scriptFilename);
}
