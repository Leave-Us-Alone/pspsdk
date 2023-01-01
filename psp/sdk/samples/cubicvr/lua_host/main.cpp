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

#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

void *dList;							// display List, used by sceGUStart
void *sceneList;							// display List, used by sceGUStart
void *fbp0;								// frame buffer


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

class RuntimeProgram
{
public:
	RuntimeProgram(string luaScriptFilename, string baseDir, SceCtrlData pad, int hostApp = 0)
	{
		mMainApplication = hostApp;
		
		//dList = malloc( 262144 );
		//sceneList = malloc( 262144 );
		//fbp0  = 0;

		pspDebugScreenInit();
		SetupCallbacks();

		mPad = pad;
		sceCtrlSetSamplingCycle(0);
		sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

		ResourceSetHomeDirectory(baseDir);
		
		mScript = new Script(luaScriptFilename);
	}
	
	~RuntimeProgram()
	{
		mScript->CloseScript();
		//delete mScript;
	}
	
	int UpdateInput()
	{
		sceCtrlReadBufferPositive(&mPad, 1);

		// Left Shoulder + Right Shoulder + Start = Developers Exit Shortcut
		if((mPad.Buttons & PSP_CTRL_LTRIGGER) && (mPad.Buttons & PSP_CTRL_RTRIGGER) && (mPad.Buttons & PSP_CTRL_START))
		{
			while((mPad.Buttons & PSP_CTRL_LTRIGGER) && (mPad.Buttons & PSP_CTRL_RTRIGGER) && (mPad.Buttons & PSP_CTRL_START))
			{
				sceCtrlReadBufferPositive(&mPad, 1);				
			}
			
			if(mMainApplication)
			{
				// todo: Add confirm message on exiting main application
			}
			
			return 0;
		}
		
		return 1;
	}
	
	void Render()
	{
		
	}
	
	int Run()
	{
		if(!UpdateInput())		return 0;
	
		sceDisplayWaitVblankStart();
		//pspDebugScreenSetOffset( (int)fbp0 );
		
		pspDebugScreenClear();
		
		pspDebugScreenSetXY(0, 1);		
		mScript->RunScript();

		return 1;
	}
	
private:
	SceCtrlData mPad;
	Script *mScript;
	bool mMainApplication;
};

SceCtrlData pad;

string baseDir;
int main(int argc, char** argv)
{	
	baseDir = string(argv[0]);
	dList = malloc( 262144 );
	sceneList = malloc( 262144 );
	fbp0  = 0;
	
	RuntimeProgram 	*game = new RuntimeProgram("launcher.lua", baseDir, pad, 1);
	
	while(game->Run())
	{
		sceCtrlReadBufferPositive(&pad, 1);	
	}
		
	printf("Made it to exit.\n");
	sceKernelExitGame();
	return 0;
}

int lua_runscript(lua_State *L)
{
	RuntimeProgram 	*game = new RuntimeProgram(lua_tostring(L, 1), baseDir, pad, 0);
	
	while(game->Run());
	
	printf("Finished running application.\n");
}
	
void read_gamepad()
{
	sceCtrlReadBufferPositive(&pad, 1);	
}

int lua_gamepadAnalogX(lua_State *L)
{
	read_gamepad();
	lua_pushnumber(L, (int)pad.Lx);
	
	return 1;	
}

int lua_gamepadAnalogY(lua_State *L)
{
	read_gamepad();
	lua_pushnumber(L, (int)pad.Ly);
	
	return 1;
}

int lua_gamepadButtonDown(lua_State *L)
{
	if (lua_gettop(L) != 1) 	return luaL_error(L, "wrong number of arguments");
	
	read_gamepad();
	
	string button(lua_tostring(L, 1));
	StringToUpper(button);
	
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
