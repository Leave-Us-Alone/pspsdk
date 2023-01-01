#include "scriptingSystem.h"

string StringToUpper(string strToConvert)
{//change each element of the string to upper case
   for(unsigned int i=0;i<strToConvert.length();i++)
   {
      strToConvert[i] = toupper(strToConvert[i]);
   }
   return strToConvert;//return the converted string
}

string StringToLower(string strToConvert)
{//change each element of the string to lower case
   for(unsigned int i=0;i<strToConvert.length();i++)
   {
      strToConvert[i] = tolower(strToConvert[i]);
   }
   return strToConvert;//return the converted string
}

Script::Script()
{	
	// init Lua and load all libraries
	L = lua_open();	
	LoadLibraries();
}

Script::Script(string scriptName)
{
	// init Lua and load all libraries
	L = lua_open();
	LoadLibraries();
	
	LoadScript(scriptName);	
}

Script::~Script()
{
	CloseScript();
}


void Script::CloseScript()
{
	if(L)		lua_close(L);
}

void Script::LoadLibraries()
{
	luaL_openlibs(L);
		
	// register our own functions
	lua_register(L, "print", 					lua_print);
	lua_register(L, "printf", 					lua_print);
	lua_register(L, "waitVblankStart", 			lua_waitVblankStart);
	lua_register(L, "ButtonDown", 				lua_gamepadButtonDown);	
	lua_register(L, "AnalogX",					lua_gamepadAnalogX);
	lua_register(L, "AnalogY",					lua_gamepadAnalogY);
	lua_register(L, "RunScript",				lua_runscript);
}

int Script::LoadScript(string scriptName)
{
	FILE * pFile;
		
	pFile = fopen (ResourceFilename(scriptName).c_str() , "rb");
	if(pFile != NULL)
	{
		fseek (pFile , 0 , SEEK_END);
		mScriptFile.size = ftell (pFile);
		rewind (pFile);
		
		mScriptFile.buffer = (char*) malloc (mScriptFile.size);
		if(mScriptFile.buffer != NULL)
		{
			fread(mScriptFile.buffer, 1, mScriptFile.size, pFile);
		}
	}
	fclose(pFile);
	
	return 1;
}

int Script::Execute()
{
	if(L)
	{
		// show error, if any
		if (lua_pcall(L, 0, LUA_MULTRET, 0) != 0)
		{
			printf("error: %s\n", lua_tostring(L, -1));
			lua_pop(L, 1);  // remove error message
			
			return 0;
		}
		
		return 1;
	}
	
	return 0;
}

int Script::RunCommand(char *command)
{
	int status = luaL_loadstring(L, command);
	
	if(status == 0 && L)		return Execute();
	else
	{
		printf("CUBIC ERROR:\tScript Failed!\n");
	}	
	
	return 0;
}

int Script::RunScript()
{			
	return RunCommand(mScriptFile.buffer);
}
