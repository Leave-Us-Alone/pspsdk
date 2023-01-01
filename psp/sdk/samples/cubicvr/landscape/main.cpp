#include <CubicVR/Timer.h>
#include <CubicVR/Scene.h>
#include <CubicVR/sceneLWS.h>
#include <CubicVR/objectLWO.h>
#include <CubicVR/SceneObjects/Landscape.h>

#include "main.h"
#include "Gamepad.h"

// 1.50 Kernel Mode
// PSP_MODULE_INFO("CubicVR", 0, 1, 1);

// 3.xx
PSP_MODULE_INFO("CubicVR", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(PSP_THREAD_ATTR_USER);
PSP_HEAP_SIZE_KB(20480);

/////////////////////////////////////////////////////////

void camSetup( void );
void loadToolObjects( void );
void App_Initialize( void );
void App_Shutdown(void);
void App_Render(void);
void DrawScene( void );

Timer timerTest;
Scene myScene(SCR_WIDTH, SCR_HEIGHT);

bool record_mode = false;
int frame_counter = 0;

#define NUM_TOOLS 3

Object toolObjsR[NUM_TOOLS];
Object toolObjsL[NUM_TOOLS];

char *toolSetR[NUM_TOOLS] = 
{
	"tool_bump_raise.lwo", 
	"tool_gradual_raise.lwo",
	"tool_plateau_raise.lwo"
};

char *toolSetL[NUM_TOOLS] = 
{
	"tool_bump_lower.lwo",
	"tool_gradual_lower.lwo",
	"tool_plateau_lower.lwo"
};


Landscape *myLandscape;
SceneObject brushObj;
Light myLight(0);
Light myLight2(1);
Camera myCamera(SCR_WIDTH, SCR_HEIGHT);
float myCamDist = 10;
float myCamAngle = M_PI/4.0;
float brushSize = 3.0;
int overview_enabled = 0;
int active_tool = 1;


void loadToolObjects( void )
{
	int i;
	
	for (i = 0; i < NUM_TOOLS; i++)
	{
		printf("Loading tool %s\n",toolSetR[i]);
		loadLWO(toolObjsR[i],toolSetR[i]);
		toolObjsR[i].cache(true);
		printf("Loading tool %s\n",toolSetL[i]);
		loadLWO(toolObjsL[i],toolSetL[i]);
		toolObjsL[i].cache(true);
	}
}


void camSetup( void )
{
	if (overview_enabled)
	{
		myCamera.position = XYZ(20,40,10);
	}
	else
	{
		myCamera.trackTarget(0.5*timerTest.lastUpdateSeconds(),brushSize*1.15);
	}

	
	XYZ camTest;
	camTest = myCamera.position;
	
	float camLandscapeHeight = myLandscape->getHeightValue(camTest);
	float camTestVal;
		
	camTest.x += 1;
	camTest.z += 1;	
	camTestVal = myLandscape->getHeightValue(camTest); if (camTestVal > camLandscapeHeight) camLandscapeHeight = camTestVal;

	camTest.x -= 2;
	camTestVal = myLandscape->getHeightValue(camTest); if (camTestVal > camLandscapeHeight) camLandscapeHeight = camTestVal;

	camTest.z -= 2;
	camTestVal = myLandscape->getHeightValue(camTest); if (camTestVal > camLandscapeHeight) camLandscapeHeight = camTestVal;

	camTest.x += 2;
	camTestVal = myLandscape->getHeightValue(camTest); if (camTestVal > camLandscapeHeight) camLandscapeHeight = camTestVal;
	
	camLandscapeHeight+=2.0;
	
	if(myCamera.position.y < camLandscapeHeight) myCamera.position.y = camLandscapeHeight;

	brushObj.setPosition(myCamera.target);
	double ypos = myLandscape->getHeightValue(brushObj.getPosition());	
	myLandscape->orient(&brushObj,1,1,0);
	brushObj.getPosition().y = ypos+0.2;
	myCamera.target = brushObj.getPosition();
}



int main(int argc, char** argv)
{
	sceRtcGetCurrentTick( &fpsTickLast );
	tickResolution = sceRtcGetTickResolution();
	
	Gamepad gamepad;
	
	App_Initialize();
	
	timerTest.start();
	if (record_mode) timerTest.lockFramerate(30.0);	
	
	float nextUpdate = 0;
	
	while(1)
	{
		timerTest.update();

		App_Render();

		if(gamepad.Poll())
		{
			if(gamepad.ButtonDown(PSP_CTRL_CIRCLE))
			{
				myLandscape->function(LANDSCAPE_FUNC_WAVES,2,3,timerTest.getSeconds());
			}
						
			if(gamepad.ButtonDown(PSP_CTRL_TRIANGLE))
			{
				myLandscape->useBrush(active_tool,myCamera.target,2.0*timerTest.lastUpdateSeconds(),brushSize);
				brushObj.bind(toolObjsR[active_tool]);
			}


			if(gamepad.ButtonDown(PSP_CTRL_SQUARE))
			{
				myLandscape->useBrush(active_tool,myCamera.target,-2.0*timerTest.lastUpdateSeconds(),brushSize);
				brushObj.bind(toolObjsL[active_tool]);
			}

			
			if(fabs(gamepad.AnalogX()) > 0.1 || fabs(gamepad.AnalogY()) > 0.1)
			{
				myCamera.moveViewRelative(
											myCamera.target, 
											5.0*gamepad.AnalogX()*timerTest.lastUpdateSeconds(), 
											5.0*gamepad.AnalogY()*timerTest.lastUpdateSeconds()
										);
			}


			if(gamepad.ButtonDown(PSP_CTRL_UP))
			{
				brushSize += timerTest.lastUpdateSeconds();
			}

			if(gamepad.ButtonDown(PSP_CTRL_DOWN))
			{
				brushSize -= timerTest.lastUpdateSeconds();
			}


			if(gamepad.ButtonDown(PSP_CTRL_LEFT))
			{
				active_tool = (!active_tool)?(NUM_TOOLS-1):(active_tool-1); 
				brushObj.bind(toolObjsR[active_tool]);
				while (gamepad.Poll()) { if (!gamepad.ButtonDown(PSP_CTRL_LEFT)) break; }
			}

			if(gamepad.ButtonDown(PSP_CTRL_RIGHT))
			{
				active_tool = (active_tool+1)%NUM_TOOLS; 
				brushObj.bind(toolObjsR[active_tool]);
				while (gamepad.Poll()) { if (!gamepad.ButtonDown(PSP_CTRL_RIGHT)) break; }
			}


/*						
			if(gamepad.ButtonDown(PSP_CTRL_LEFT))
			{

			}

			if(gamepad.ButtonDown(PSP_CTRL_RIGHT))
			{

			}			
*/

		}		
	}

	App_Shutdown();

	return 0;
}

void App_Initialize( void )
{
	Gamepad gamepad;
	
	dList = malloc( 262144 );
	fbp0  = 0;
 
	sceKernelDcacheWritebackAll();
	pspDebugScreenInit();
	
	///////////////////////////////////////////////////
	// Load Resources
	///////////////////////////////////////////////////
	printf("Generating Landscape..\n");	
	
	Material *objMat = new Material();	
	unsigned int objTex = Texture::create("grass.tga","grass");
//	unsigned int objTex2 = Texture::create("env1.tga","refl");

	objMat->bindTexture(0,objTex,TEXTURE_DIFF);
//	objMat->bindTexture(1,objTex2);
//	objMat->layer[1].map_mode = MATERIAL_MAP_SPHERICAL;
	objMat->setMaxSmooth(60);

	myLandscape = new Landscape(50,35,35,1000.0,objMat);
	myLandscape->function(LANDSCAPE_FUNC_WAVES,2,3,0);
	
	myCamera.position = XYZ(50,50,50);
	myLight.rotation = XYZ(45,45,0);
	myLight.setType(LIGHT_DIRECTIONAL);

	myCamera.setType(CAMERA_TARGET);
	myCamera.target = XYZ(0,0,0);

	myScene.bind(myCamera);
	myScene.bind(myLight);
	myScene.bind(*myLandscape);
	
	loadToolObjects();
	
	brushObj.bind(toolObjsR[0]);
	myScene.bind(brushObj);
	brushObj.setPosition(XYZ(0,5,1));
	brushObj.setScale(XYZ(0.2*brushSize,0.2*brushSize,0.2*brushSize));

	
	///////////////////////////////////////////////////
	// END Load Resources
	///////////////////////////////////////////////////
	printf("\n\n--------------------------\n");
	printf("   Press X to start...\n");
	printf("--------------------------\n\n");
	
	while(!gamepad.ButtonDown(PSP_CTRL_CROSS))
	{
		gamepad.Poll();
	}
	
	InitGU();
	SetupProjection();
	SetupCallbacks();
}

void SetupProjection( void )
{
	// setup matrices for the triangle
	sceGumMatrixMode(GU_PROJECTION);
	sceGumLoadIdentity();
	sceGumPerspective( 75.0f, 16.0f/9.0f, 0.5f, 1000.0f);
 
    sceGumMatrixMode(GU_VIEW);
	sceGumLoadIdentity();
 	
	sceGuClearColor( GU_COLOR( 0.0f, 0.0f, 0.0f, 1.0f ) ); 
	sceGuClearDepth(0);	
}

void App_Shutdown(void)
{
	// Free Memory
	free( dList );
	free( fbp0 );
	
	sceGuTerm();			// Terminating the Graphics System
 
	sceKernelExitGame();
}

void App_Render(void)
{
	DrawScene();
	if (!record_mode) DebugScreen();
			
	sceDisplayWaitVblankStart();	
	fbp0 = sceGuSwapBuffers();

	if (record_mode) myScene.saveScreenshot("",fbp0,frame_counter++);	
}

void InitGU( void )
{
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


void DrawScene( void )
{
#warning Try taking out this display list at some point

	camSetup();

	sceGuStart( GU_DIRECT, dList );

	sceGuViewport( 2048, 2048, SCR_WIDTH, SCR_HEIGHT);	

	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGumMatrixMode(GU_MODEL);		
	sceGumLoadIdentity();	// Reset the Matrix

	brushObj.setScale(XYZ(0.2*brushSize,0.2*brushSize,0.2*brushSize));

	myScene.render();	// Render the scene
	
	sceGuFinish();
	sceGuSync(0,0);
}


void DebugScreen( void )
{
	fps++;
	sceRtcGetCurrentTick( &fpsTickNow );
	
	if( ((fpsTickNow - fpsTickLast)/((float)tickResolution)) >= 1.0f )
	{
		fpsTickLast = fpsTickNow;
		sprintf( fpsDisplay, "FPS: %i", fps );
		fps = 0;
	}
	pspDebugScreenSetOffset( (int)fbp0 );
	pspDebugScreenSetXY( 0, 0 );
	pspDebugScreenPrintf( fpsDisplay );
	
	
	pspDebugScreenSetXY( 0, 1 );
	pspDebugScreenPrintf( "%f", timerTest.getSeconds() );
	pspDebugScreenSetXY( 0, 2 );
	pspDebugScreenPrintf( "Brush Size: %f, Function: %d", brushSize,  active_tool);
	
	//pspDebugScreenSetXY( 0, 2 );
	//pspDebugScreenPrintf( "%f %f %f %d", myScene.cam->position.x, myScene.cam->position.y, myScene.cam->position.z, myScene.cam->type);
}


void FPS( void )
{
	fps++;
	sceRtcGetCurrentTick( &fpsTickNow );
	
	if( ((fpsTickNow - fpsTickLast)/((float)tickResolution)) >= 1.0f )
	{
		fpsTickLast = fpsTickNow;
		sprintf( fpsDisplay, "FPS: %i", fps );
		fps = 0;
	}
	pspDebugScreenSetOffset( (int)fbp0 );
	pspDebugScreenSetXY( 0, 0 );
	pspDebugScreenPrintf( fpsDisplay );
}

