// Lua test program by Frank Buss (aka Shine)

#include <CubicVR/Timer.h>
#include <CubicVR/Motion.h>
#include <CubicVR/Camera.h>
#include <CubicVR/Texture.h>
#include <CubicVR/Material.h>
#include <CubicVR/Object.h>
#include <CubicVR/Shader.h>
#include <CubicVR/UVMapper.h>

#include "main.h"
#include "Gamepad.h"
#include "ScriptLua.h"

PSP_MODULE_INFO("CubicVR", 0, 1, 1);

Camera myCamera = Camera(SCR_WIDTH, SCR_HEIGHT, 72, 0.5, 1000.0, CAMERA_TARGET);
unsigned int myTex;
Material* myMat;
Object myObj;
ObjectShader myShader;
Light myLight(0);

void makeBox(Object &boxObj, float box_size, Material* box_mat)
{
	float half_box = box_size/2.0;
	
	boxObj.addPoint(0,XYZ( half_box,-half_box, half_box));
	boxObj.addPoint(1,XYZ( half_box, half_box, half_box));
	boxObj.addPoint(2,XYZ(-half_box, half_box, half_box));
	boxObj.addPoint(3,XYZ(-half_box,-half_box, half_box));

	boxObj.addPoint(4,XYZ( half_box,-half_box, -half_box));
	boxObj.addPoint(5,XYZ( half_box, half_box, -half_box));
	boxObj.addPoint(6,XYZ(-half_box, half_box, -half_box));
	boxObj.addPoint(7,XYZ(-half_box,-half_box, -half_box));

	boxObj.addFace();
	boxObj.addFacePoint(0); boxObj.addFacePoint(1); boxObj.addFacePoint(2); 
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(2); boxObj.addFacePoint(3); boxObj.addFacePoint(0); 
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(7); boxObj.addFacePoint(6); boxObj.addFacePoint(5);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(5); boxObj.addFacePoint(4); boxObj.addFacePoint(7);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(0); boxObj.addFacePoint(5); boxObj.addFacePoint(1);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(5); boxObj.addFacePoint(0); boxObj.addFacePoint(4);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(1); boxObj.addFacePoint(6); boxObj.addFacePoint(2);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(6); boxObj.addFacePoint(1); boxObj.addFacePoint(5);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(2); boxObj.addFacePoint(7); boxObj.addFacePoint(3);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(7); boxObj.addFacePoint(2); boxObj.addFacePoint(6);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(3); boxObj.addFacePoint(4); boxObj.addFacePoint(0);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.addFace();
	boxObj.addFacePoint(4); boxObj.addFacePoint(3); boxObj.addFacePoint(7);
	boxObj.bindFaceMaterial(box_mat);

	boxObj.calcNormals();
}


/////////////////////////////////////////////////////////
// Motion Controller
ScePspFVector3 move = { 0.0f, 0.0f, -3.0f };
ScePspFVector3 rot  = { 0.0f, 0.0f, 0.0f };		// Define rotation structure (NEW)
Motion myMotion;
class myController : public Controllable
{
public:
	void control(int controllerId, int motionId, float value)
	{
		//printf("ctl: %d, mot: %d\t\t val: %f\n", controllerId, motionId, value);
		if(controllerId == CONTROLLER_POSITION)
		{
			if(motionId == MOTION_X) move.x = value;
			if(motionId == MOTION_Y) move.y = value;
		}

		if(controllerId == CONTROLLER_ROTATION)
		{
			if(motionId == MOTION_X) rot.x = value;
			if(motionId == MOTION_Y) rot.y = value;
		}
	}
} ctrlObj;
// END Motion Controller

//#define CAMERA_CONTROLLER_FOV 100
//#define CAMERA_MOTION_FOV 100

/////////////////////////////////////////////////////////

#include "PSPGraphics.h"

void App_Initialize();
void App_Shutdown();
void App_Render();

void DrawScene();

Timer timerTest;

int main(int argc, char** argv)
{
	sceRtcGetCurrentTick( &fpsTickLast );
	tickResolution = sceRtcGetTickResolution();

	float nearClip = 0.01f;
	float farClip = 2000.0f;
	
	myCamera.setTarget(XYZ(0,0,0));
	
	Gamepad gamepad;


	myMotion.bind(myCamera);
	myMotion.setBehavior(myCamera,CONTROLLER_POSITION,MOTION_X,ENV_BEH_REPEAT,ENV_BEH_REPEAT);
	myMotion.setBehavior(myCamera,CONTROLLER_POSITION,MOTION_Y,ENV_BEH_REPEAT,ENV_BEH_REPEAT);
	myMotion.setBehavior(myCamera,CONTROLLER_POSITION,MOTION_Z,ENV_BEH_REPEAT,ENV_BEH_REPEAT);
	myMotion.setBehavior(myCamera,CAMERA_CONTROLLER_FOV,CAMERA_MOTION_FOV,ENV_BEH_REPEAT,ENV_BEH_REPEAT);
	
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_X,0,-2);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Y,0,0);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Z,0,-2);
	myMotion.setKey(myCamera,CAMERA_CONTROLLER_FOV,CAMERA_MOTION_FOV,0,72);

	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_X,5,2.5);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Y,5,2.5);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Z,5,-2.5);
	myMotion.setKey(myCamera,CAMERA_CONTROLLER_FOV,CAMERA_MOTION_FOV,5,60);

	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_X,10,1.4);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Y,10,1);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Z,10,1.4);
	myMotion.setKey(myCamera,CAMERA_CONTROLLER_FOV,CAMERA_MOTION_FOV,10,140);


	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_X,15,-1.8);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Y,15,-3);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Z,15,2);
	myMotion.setKey(myCamera,CAMERA_CONTROLLER_FOV,CAMERA_MOTION_FOV,15,100);

	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_X,20,-2);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Y,20,0);
	myMotion.setKey(myCamera,CONTROLLER_POSITION,MOTION_Z,20,-2);
	myMotion.setKey(myCamera,CAMERA_CONTROLLER_FOV,CAMERA_MOTION_FOV,20,72);

	
	App_Initialize();
		
	// Do LUA
	ScriptLoad(argv);
		
	timerTest.start();
	
	float nextUpdate = 0;
	
	while(1)
	{
	
		timerTest.update();

		myMotion.evaluate(timerTest.getSeconds());

		App_Render();

		//printf("-=-=-=- [TIME INDEX: %.2f] -=-=-=", timerTest.getSeconds());
		
		/*if(timerTest.getSeconds() > nextUpdate)
		{
			nextUpdate = timerTest.getSeconds() + 0.25;
			printf("\n\n-=-=-=- [TIME INDEX: %.2f] -=-=-=\n\n", timerTest.getSeconds());
		}*/
		
		if(gamepad.Poll())
		{
			if(gamepad.ButtonDown(PSP_CTRL_START))
			{
				break;
			}
		}		
	}
			

	ScriptClose();

	
	App_Shutdown();

	return 0;
}

void App_Initialize()
{
	dList = malloc( 262144 );
	fbp0  = 0;
 
	sceKernelDcacheWritebackAll();
	
	///////////////////////////////////////////////////
	// Load Resources
	///////////////////////////////////////////////////
/*	if( !texture.LoadTGA( "textures/crate.tga" ) )
	{
		printf("Texture load: Failed!\n");
		//sceKernelExitGame();
	}
	texture.Swizzle();*/

	myMat = new Material();
	myTex = Texture::create("textures/crate.tga");
	myMat->bindTexture(myTex);

	makeBox(myObj,2,myMat);

	UVMapper test_map;
	test_map.setProjection(UV_PROJECTION_CUBIC);
	test_map.setScale(XYZ(2,2,2));
	test_map.apply(myObj,myMat);	

	myObj.cache(true);	
	
	///////////////////////////////////////////////////
	// END Load Resources
	///////////////////////////////////////////////////
	
	InitGU();
	SetupProjection();
	
	pspDebugScreenInit();
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
 	
 	//myCamera.setup();
 	
	sceGuClearColor( GU_COLOR( 0.0f, 0.0f, 0.0f, 1.0f ) ); 
	sceGuClearDepth(0);	
}

void App_Shutdown()
{
	// Free Memory
	//free( dList );
	//free( fbp0 );
	//sceGuTerm();			// Terminating the Graphics System
 
	sceKernelExitGame();
}

void App_Render()
{
	DrawScene();
	DebugScreen();
			
	//sceDisplayWaitVblankStart();
	//pspDebugScreenClear();				
	fbp0 = sceGuSwapBuffers();
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
	sceGuStart( GU_DIRECT, dList );
	
	sceGuViewport( 2048, 2048, SCR_WIDTH, SCR_HEIGHT);

	myLight.setup();
	myLight.position = myCamera.position;
	
	myCamera.setup();
	

	// clear screen
	sceGuClear(GU_COLOR_BUFFER_BIT|GU_DEPTH_BUFFER_BIT);
	sceGumMatrixMode(GU_MODEL);
		
	sceGumLoadIdentity();		// Reset the Matrix
	
	// Texture
//	sceGuTexFilter( GU_LINEAR, GU_LINEAR );	
 //	sceGuTexImage( 0, texture.Width(), texture.Height(), texture.Width(), texture.Image() );
 
//	Material::use(myMat);
//	Texture::use(myTex);
	
	// Draw Quad
//	sceGumDrawArray( GU_TRIANGLES, GU_TEXTURE_32BITF|GU_COLOR_8888|GU_NORMAL_32BITF|GU_VERTEX_32BITF|GU_TRANSFORM_3D, 3*12, 0, cube );						// Draw the Cube (NEW)
	
	myShader.render(myObj);

	
	sceGuFinish();
	//sceGuSync(0,0);	 
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
	pspDebugScreenPrintf( "%f %f %f %d", myCamera.position.x, myCamera.position.y, myCamera.position.z , myCamera.type);
}
