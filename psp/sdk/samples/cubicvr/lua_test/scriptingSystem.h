#include <psptypes.h>
#include <pspkernel.h>
#include <pspdebug.h>
#include <pspdisplay.h>
#include <pspgu.h>				// PSP GU
#include <pspgum.h>				// PSP GU Matrix
#include <psprtc.h>				// for the timer/fps functions
#include <pspctrl.h>

#include <stdlib.h>
#include <string.h>
#include <string>

using namespace std;

#include "lua.hpp"

#include "resourceManager.h"
#include "scriptingExports.h"

typedef struct luaMemFile
{
  char *buffer;
  size_t size;
} luaMemFile;

class Script
{
public:
	Script();
	Script(string scriptName);
	
	~Script();
	
	void LoadLibraries();
	
	int LoadScript(string scriptName);
	void CloseScript();
	
	int RunCommand(char *command);
	int RunScript();
	int Execute();
	
private:
	luaMemFile 	mScriptFile;	
	lua_State 	*L;
};