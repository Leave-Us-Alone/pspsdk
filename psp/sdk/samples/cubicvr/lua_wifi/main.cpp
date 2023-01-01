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

#include "resourceManager.h"
#include "scriptingSystem.h"

int done = 0;

PSP_MODULE_INFO("CONTROLTEST", 0, 1, 1);							// Define the module info section
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);			// Define the main thread's attribute value (optional)
#define printf	pspDebugScreenPrintf								// Define printf, just to make typing easier

void dump_threadstatus(void);


/* Exit callback */
int exit_callback(int arg1, int arg2, void *common)
{
	done = 1;
	return 0;
}

/* Callback thread */
int CallbackThread(SceSize args, void *argp)
{
	int cbid;

	cbid = sceKernelCreateCallback("Exit Callback", exit_callback, NULL);
	sceKernelRegisterExitCallback(cbid);
	sceKernelSleepThreadCB();

	return 0;
}

/* Sets up the callback thread and returns its thread id */
int SetupCallbacks(void)
{
	int thid = 0;

	thid = sceKernelCreateThread("update_thread", CallbackThread, 0x11, 0xFA0, 0, 0);
	if(thid >= 0)
	{
		sceKernelStartThread(thid, 0, 0);
	}

	return thid;
}


SceCtrlData pad;
	
int main(int argc, char** argv)
{
	int result;
	
	pspDebugScreenInit();
	SetupCallbacks();

	ResourceSetHomeDirectory(string(argv[0]));
	
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
	
	while(!done)
	{
		sceDisplayWaitVblankStart();	
		
		sceCtrlReadBufferPositive(&pad, 1); 
		pspDebugScreenSetXY(0, 1);
		printf("Settings:\n");
	}
	
	Script script("input.lua");
	while(!done)
	{
		sceDisplayWaitVblankStart();	
		
		sceCtrlReadBufferPositive(&pad, 1); 
		
		//pspDebugScreenSetXY(0, 6);		
		//printf("Exe Path = %s", baseContentDirectoryPath.c_str());		
		
		
		pspDebugScreenSetXY(0, 1);
		result = script.RunCommand("print('Lua Driven PSP Gamepad Reader');");
		result = script.RunCommand("print('-----------------------------');");
				
		pspDebugScreenSetXY(0, 3);
		printf("Analog X = %d ", pad.Lx);
		printf("Analog Y = %d \n", pad.Ly);
		
		pspDebugScreenSetXY(0, 6);	
		result = script.RunScript();
	}

	script.CloseScript();
		
	sceKernelExitGame();
	return 0;
}

int lua_gamepadButtonDown(lua_State *L)
{
	if (lua_gettop(L) != 1) 	return luaL_error(L, "wrong number of arguments");
	
	string button(lua_tostring(L, 1));
	
	int valid = 0;
	
	if(button == "CIRCLE")			if (pad.Buttons & PSP_CTRL_CIRCLE)			valid = 1;
	if(button == "SQUARE")			if (pad.Buttons & PSP_CTRL_SQUARE)			valid = 1;
	if(button == "TRIANGLE")		if (pad.Buttons & PSP_CTRL_TRIANGLE)		valid = 1;
	if(button == "CROSS")			if (pad.Buttons & PSP_CTRL_CROSS)			valid = 1;
		
	if(button == "LSHOULDER")		if (pad.Buttons & PSP_CTRL_LTRIGGER)		valid = 1;
	if(button == "RSHOULDER")		if (pad.Buttons & PSP_CTRL_RTRIGGER)		valid = 1;
	
	if(button == "UP")				if (pad.Buttons & PSP_CTRL_UP)				valid = 1;
	if(button == "DOWN")			if (pad.Buttons & PSP_CTRL_DOWN)			valid = 1;
	if(button == "LEFT")			if (pad.Buttons & PSP_CTRL_LEFT)			valid = 1;
	if(button == "RIGHT")			if (pad.Buttons & PSP_CTRL_RIGHT)			valid = 1;
	
	if(button == "START")			if (pad.Buttons & PSP_CTRL_START)			valid = 1;
	if(button == "SELECT")			if (pad.Buttons & PSP_CTRL_SELECT)			valid = 1;
		
	
	lua_pushnumber(L, valid);
	
		
	return 1;
}

int lua_waitVblankStart(lua_State *L)
{
	if (lua_gettop(L) != 0) return luaL_error(L, "wrong number of arguments");
	sceDisplayWaitVblankStart();
	return 0;
}

// print all arguments, converted to strings
int lua_print(lua_State *L)
{
	int argc = lua_gettop(L);
	int n;
	for (n=1; n <= argc; n++) printf("%s\n", lua_tostring(L, n));
	return 0;
}
