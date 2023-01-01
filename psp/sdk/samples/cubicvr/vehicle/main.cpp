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

#include <CubicVR/Object.h>
#include <CubicVR/Shader.h>
#include <CubicVR/Material.h>
#include <CubicVR/UVMapper.h>
#include <CubicVR/Timer.h>
#include <CubicVR/Scene.h>
#include <CubicVR/objectLWO.h>
#include <CubicVR/sceneLWS.h>
#include <CubicVR/SceneObjects/Landscape.h>
#include <btBulletDynamicsCommon.h>

#include <CubicVR/RigidScene.h>
#include <CubicVR/SceneObjects/RigidSceneObject.h>
#include <CubicVR/SceneObjects/RigidBox.h>
#include <CubicVR/SceneObjects/Vehicle.h>

using namespace std;

Timer myTimer;

#include "resourceManager.h"
#include "scriptingSystem.h"
       
int done = 0;

PSP_MODULE_INFO("CONTROLTEST", 0, 1, 1);							// Define the module info section
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);			// Define the main thread's attribute value (optional)
#define printf	pspDebugScreenPrintf								// Define printf, just to make typing easier
//#define RGB(r, g, b) ((r)|((g)<<8)|((b)<<16))

#define BUF_WIDTH (512)
#define SCR_WIDTH (480)
#define SCR_HEIGHT (272)

void *dList;							// display List, used by sceGUStart
void *sceneList;			 
void *fbp0;								// frame buffer

void dump_threadstatus(void);

Camera camera(SCR_WIDTH, SCR_HEIGHT, 72, 1.0, 1000.0, CAMERA_TARGET);
Light light(0);      

RigidScene scene;

Object groundObject;
RigidBox ground(groundObject);

Object boxObject;
RigidBox dropBox(boxObject);      
Vehicle *car;

Object meshObj;
Object meshCollisionObj;
Object wheelObj;

RigidSceneObject carObj(meshObj,meshCollisionObj);

void InitScene();
void DrawScene( void );
void UpdatePhysics();
int main(int argc, char** argv); 

          

void DrawScene( void )
{
	sceGuClearColor( GU_COLOR( 0.0f, 0.0f, 0.0f, 1.0f ) ); 
	sceGuClearDepth(0);	

	sceGuStart( GU_DIRECT, sceneList );
	
	sceGuViewport( 2048, 2048, SCR_WIDTH, SCR_HEIGHT);

	// clear screen
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
                
	camera.target = carObj.getPosition();

	scene.render();
	
	sceGuFinish();
	sceGuSync(0,0);
}



void InitScene()
{          
	// load the box object
	loadLWO(boxObject,"box.lwo");     
	boxObject.cache(true);

	loadLWO(groundObject,"ground_box.lwo");     
	groundObject.cache(true);
	
	loadLWO(meshObj,"car.lwo");
   	meshObj.cache(true);
	// 
	// loadLWO(wheelObj,"box.lwo");
	// wheelObj.cache(true);

	loadLWO(meshCollisionObj,"car_cmap.lwo");
	meshCollisionObj.cache(true);
	                      
	// set up a camera
	camera.position = XYZ(14,5,14);
	camera.target = XYZ(0,4,0); 
	camera.setFOV(60);
	scene.bind(camera);   

    // bind a default light
	light.position = XYZ(5,3,5);   
	
	light.setAmbient(RGB(0.4f,0.4f,0.4f));
	light.setDiffuse(RGB(0.7f,0.7f,0.7f));
	light.setSpecular(RGB(0.4f,0.4f,0.4f)); 
	light.setConstantAttenuation(0.01f);
	light.setLinearAttenuation(0.01f);
	light.setQuadraticAttenuation(0.001f);
	
	scene.bind(light);

	// make the ground
	ground.setScale(XYZ(60,1,60));
	ground.setPosition(XYZ(0,-0.5,0));
	// keep it static
	ground.setMass(0); 
	scene.bind(ground);
	                    
	// //	create a dynamics dropping box
	// dropBox.controller().position = XYZ(0,40,0);
	// dropBox.controller().scale = XYZ(5,5,5);
	// dropBox.controller().rotation = XYZ(36,0,20);
	// dropBox.setMass(40);	
	// scene.bind(dropBox);         
		

	carObj.setPosition(XYZ(0,40,0));
	carObj.setRotation(XYZ(36,0,20));
	scene.bind(carObj);
	
	car = new Vehicle(meshObj,meshCollisionObj);
	car->setPosition(XYZ(0,5,0));
	scene.bind(*car);

//	scene.bind(carObj);
	
}


void UpdatePhysics()
{
	float lus = myTimer.lastUpdateSeconds();

//	camera.trackTarget(lus*2.0,2.5);
	
/*
	float mvSpd = (brushSize);
	float xmv = keyPressed[GLUT_KEY_LEFT]?-mvSpd:0 + keyPressed[GLUT_KEY_RIGHT]?mvSpd:0;
	float ymv = keyPressed[GLUT_KEY_UP]?-mvSpd:0 + keyPressed[GLUT_KEY_DOWN]?mvSpd:0;

	camera.moveViewRelative(targetObj->controller().position,xmv*lus,ymv*lus);
*/

	if (!myTimer.paused()) scene.getDynamicsWorld()->stepSimulation(lus, 7);
}



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
       


void InitGU( void )
{
	dList = malloc( 262144 );
	sceneList = malloc( 262144 );
	fbp0  = 0;
 
	sceKernelDcacheWritebackAll();
 
   // Init GU
	sceGuInit();
	sceGuStart( GU_DIRECT, dList );

	// Set Buffers
	sceGuDrawBuffer( GU_PSM_8888, fbp0, BUF_WIDTH );
	sceGuDispBuffer( SCR_WIDTH, SCR_HEIGHT, (void*)0x88000, BUF_WIDTH);
	sceGuDepthBuffer( (void*)0x110000, BUF_WIDTH);

 	sceGuOffset( 2048 - (SCR_WIDTH/2), 2048 - (SCR_HEIGHT/2));
	sceGuDepthRange( 65535, 0);

	// Set Render States
	sceGuScissor( 0, 0, SCR_WIDTH, SCR_HEIGHT);
	sceGuEnable( GU_SCISSOR_TEST );
	sceGuDepthFunc( GU_GEQUAL );
	sceGuEnable( GU_DEPTH_TEST );
	sceGuFrontFace( GU_CW );
	sceGuEnable( GU_CULL_FACE );					
	sceGuShadeModel( GU_SMOOTH );
	sceGuEnable( GU_CLIP_PLANES );
	sceGuEnable( GU_TEXTURE_2D );
	sceGuEnable( GU_LIGHTING );
	sceGuEnable( GU_LIGHT0 );						// Enable Light 1 (NEW)

	// setup texture
	// 32-bit image, if we swizzled the texture will return true, otherwise false (NEW)
	sceGuTexMode( GU_PSM_8888, 0, 0, true );	
	sceGuTexFunc( GU_TFX_MODULATE, GU_TCC_RGB );	// Modulate the color of the image
	sceGuTexScale( 1.0f, 1.0f );					// No scaling
	sceGuTexOffset( 0.0f, 0.0f );

	sceGuFinish();
	sceGuSync(0,0);

	sceDisplayWaitVblankStart();
	sceGuDisplay(GU_TRUE);
	// finish
}



SceCtrlData pad;       
int pad_lock = 0;
	
int main(int argc, char** argv)
{
	int result;

	SetupCallbacks();

	InitGU();
   
	pspDebugScreenSetOffset( (int)fbp0 );

	pspDebugScreenInit();

	pspDebugScreenSetXY( 0, 0 );

	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);

	ResourceSetHomeDirectory(string(argv[0]));
    
	InitScene();      
	    
	printf(".. Press X ..\n");
	
	while (!(pad.Buttons & PSP_CTRL_CROSS))
	{
		sceCtrlReadBufferPositive(&pad, 1);  
	}

	//    while(!done)
	// {
	// 	sceCtrlReadBufferPositive(&pad, 1); 
	// 	if (pad.Buttons & PSP_CTRL_CIRCLE)		done = 1;
	// 	if (pad.Buttons & PSP_CTRL_SQUARE)
	// 	{
	// 		printf("Square button.\n");
	// 	}
	// }
	// printf("Program End.\n");
	// 
	// sceKernelExitGame();
	// return 0;
	
	Script script("input.lua");
	
          
	myTimer.start();     
	
	float lus;

	while(!done)
	{
		sceCtrlReadBufferPositive(&pad, 1); 
		if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER) && (pad.Buttons & PSP_CTRL_START))			done = 1;

		myTimer.update();
		
		lus = myTimer.lastUpdateSeconds();
		
		UpdatePhysics();
	
//		pspDebugScreenSetXY(0,1);
		
		DrawScene();
				
		//pspDebugScreenSetXY(0, 6);		
		//printf("Exe Path = %s", baseContentDirectoryPath.c_str());		
		
		//pspDebugScreenSetXY(0, 1);
		//	result = script.RunCommand("print('Manual LUA command: print');");	
		//	pspDebugScreenSetXY(0, 3);	
		//	result = script.RunScript();
	
	   // create a dynamics dropping box
	             
	
		if (pad.Buttons & PSP_CTRL_SQUARE && !pad_lock)
		{ 
			pad_lock = 1;
		}   
		else if (!(pad.Buttons & PSP_CTRL_SQUARE) && pad_lock )
		{
			RigidBox *myObj = new RigidBox(boxObject);

			myObj->setPosition(XYZ(0,40,0));
			myObj->setScale(XYZ(2,2,2));
			myObj->setRotation(XYZ(45,0,45));
			myObj->setMass(40);	

			scene.bind(*myObj); 
			
			pad_lock = 0;
		}
		


		//	pspDebugScreenSetXY(0, 12);
	                  
	    // printf("Num Physics: %d\n",dynamicsWorld->getNumCollisionObjects());
	    // 		// print positions of all objects
	    //    		for (int j=dynamicsWorld->getNumCollisionObjects()-1; j>=0 ;j--)
	    //    		{
	    //    			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
	    //    			btRigidBody* body = btRigidBody::upcast(obj);
	    //    			if (body && body->getMotionState())
	    //    			{
	    //    			        body->getMotionState()->getWorldTransform(trans);
	    //    		
	    //    			        printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
	    //    			}
	    //    		}              

 		pspDebugScreenSetOffset( (int)fbp0 );

		pspDebugScreenSetXY(0,1);
		pspDebugScreenPrintf( "drop box: %f %f %f", dropBox.getPosition().x, dropBox.getPosition().y, dropBox.getPosition().z);

		pspDebugScreenSetXY(0, 3);
		printf("Analog X = %d ", pad.Lx);
		printf("Analog Y = %d \n", pad.Ly);   
		
		sceDisplayWaitVblankStart();	
		fbp0 = sceGuSwapBuffers();          
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
