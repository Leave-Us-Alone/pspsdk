#ifndef SCRIPTLUA_H
#define SCRIPTLUA_H

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

#include "ScriptLuaExports.h"

void ScriptLoad(char** argv);
void ScriptClose();

#endif
