#ifndef SCRIPTLUAEXPORTS_H
#define SCRIPTLUAEXPORTS_H

#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

//int lua_waitVblankStart(lua_State *L);
int lua_print(lua_State *L);

#endif
