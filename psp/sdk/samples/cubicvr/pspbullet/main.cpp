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
#include <CubicVR/SceneObjects/RigidSceneObject.h>
#include <btBulletDynamicsCommon.h>

using namespace std;

Timer myTimer;

#include "resourceManager.h"
#include "scriptingSystem.h"
       
int done = 0;

PSP_MODULE_INFO("CONTROLTEST", 0, 1, 1);							// Define the module info section
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_USER | THREAD_ATTR_VFPU);			// Define the main thread's attribute value (optional)
#define printf	pspDebugScreenPrintf								// Define printf, just to make typing easier

void dump_threadstatus(void);

btRigidBody *boxBody;

//btTransform trans;

CollisionMap boxCollision;
btCollisionShape *boxCollisionShape;

//keep track of the shapes, we release memory at exit.
//make sure to re-use collision shapes among rigid bodies whenever possible!
btAlignedObjectArray<btCollisionShape*> collisionShapes;

btDiscreteDynamicsWorld* dynamicsWorld;
//keep track of the shapes, we release memory at exit.
//make sure to re-use collision shapes among rigid bodies whenever possible!
//btAlignedObjectArray<btCollisionShape*> collisionShapes;

void CreateWorld();
void CreateGround();
void InitPhysics();
int main(int argc, char** argv); 

btDefaultCollisionConstructionInfo *pspCollisionConstruct;
           
// struct	btDefaultCollisionConstructionInfo
// {
// 	btStackAlloc*		m_stackAlloc;
// 	btPoolAllocator*	m_persistentManifoldPool;
// 	btPoolAllocator*	m_collisionAlgorithmPool;
// 	int					m_defaultMaxPersistentManifoldPoolSize;
// 	int					m_defaultMaxCollisionAlgorithmPoolSize;
// 	int					m_defaultStackAllocatorSize;
// 
// 	btDefaultCollisionConstructionInfo()
// 		:m_stackAlloc(0),
// 		m_persistentManifoldPool(0),
// 		m_collisionAlgorithmPool(0),
// 		m_defaultMaxPersistentManifoldPoolSize(65535),
// 		m_defaultMaxCollisionAlgorithmPoolSize(65535),
// 		m_defaultStackAllocatorSize(1*1024*1024)
// 	{
// 	}
// };
//       
void CreateWorld()
{	              
	pspCollisionConstruct = new btDefaultCollisionConstructionInfo(); 
	pspCollisionConstruct->m_defaultMaxPersistentManifoldPoolSize = 16384;
	pspCollisionConstruct->m_defaultMaxCollisionAlgorithmPoolSize = 16384;
	pspCollisionConstruct->m_defaultStackAllocatorSize = (2*1024*1024);

	printf("Program start.\n");

	printf("Creating world...\n");
	
// 	///collision configuration contains default setup for memory, collision setup. Advanced users can create their own configuration.
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration(*pspCollisionConstruct);
// 	
// 	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	btCollisionDispatcher* dispatcher = new	btCollisionDispatcher(collisionConfiguration);
// 
// //	dispatcher->registerCollisionCreateFunc(SPHERE_SHAPE_PROXYTYPE,SPHERE_SHAPE_PROXYTYPE, new btSphereSphereCollisionAlgorithm::CreateFunc);
// //	dispatcher->registerCollisionCreateFunc(TRIANGLE_MESH_SHAPE_PROXYTYPE,TRIANGLE_MESH_SHAPE_PROXYTYPE, new btCompoundCollisionAlgorithm::CreateFunc);
// //	dispatcher->registerCollisionCreateFunc(FAST_CONCAVE_MESH_PROXYTYPE,FAST_CONCAVE_MESH_PROXYTYPE, new btSphereSphereCollisionAlgorithm::CreateFunc);
// //	dispatcher->registerCollisionCreateFunc(CONVEX_SHAPE_PROXYTYPE,CONVEX_SHAPE_PROXYTYPE, new btSphereSphereCollisionAlgorithm::CreateFunc);
// 
// 	///the maximum size of the collision world. Make sure objects stay within these boundaries
// 	///Don't make the world AABB size too large, it will harm simulation quality and performance
 	btVector3 worldAabbMin(-10000,-10000,-10000);
 	btVector3 worldAabbMax(10000,10000,10000);
 	int	maxProxies = 1024;
 	btAxisSweep3* overlappingPairCache = new btAxisSweep3(worldAabbMin,worldAabbMax,maxProxies);
// 
// 	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
 	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;
// 
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0,-10,0));                                 
	
	printf("Dynamics world created!\n");
}

void InitPhysics()
{
	CreateWorld();
	CreateGround();
}


void CreateGround()
{
	///create a few basic rigid bodies
	btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(72.5),btScalar(0.5),btScalar(72.5)));

	//collisionShapes.push_back(groundShape);

	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,-0.5,0));

	{
		btScalar mass(0.);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			groundShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);

		//add the body to the dynamics world
		dynamicsWorld->addRigidBody(body);
	}
}                                                 

void CreateRigidBody(XYZ position, XYZ rotation, XYZ size)
{
	//create a dynamic rigidbody

	btCollisionShape* colShape = new btBoxShape(btVector3(size.x / 2.0, size.y / 2.0, size.z / 2.0));
	//btCollisionShape* colShape = new btSphereShape(btScalar(1.));
	collisionShapes.push_back(colShape);

	/// Create Dynamic Objects
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar	mass(1.f);

	//rigidbody is dynamic if and only if mass is non zero, otherwise static
	bool isDynamic = (mass != 0.f);

	btVector3 localInertia(0,0,0);
	if (isDynamic)
		colShape->calculateLocalInertia(mass,localInertia);

	startTransform.setOrigin(btVector3(position.x, position.y, position.z));
	
	btQuaternion rot;
	rot.setEuler(rotation.x,rotation.y,rotation.z);
	
	startTransform.setRotation(rot);

	//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,colShape,localInertia);
	boxBody = new btRigidBody(rbInfo);

	dynamicsWorld->addRigidBody(boxBody);
}


void UpdatePhysics()
{
	float lus = myTimer.lastUpdateSeconds();
	
/*
	float mvSpd = (brushSize);
	float xmv = keyPressed[GLUT_KEY_LEFT]?-mvSpd:0 + keyPressed[GLUT_KEY_RIGHT]?mvSpd:0;
	float ymv = keyPressed[GLUT_KEY_UP]?-mvSpd:0 + keyPressed[GLUT_KEY_DOWN]?mvSpd:0;

	myCamera.moveViewRelative(targetObj->controller().position,xmv*lus,ymv*lus);
*/
	

	if (!myTimer.paused()) dynamicsWorld->stepSimulation(myTimer.lastUpdateSeconds(), 7);
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


SceCtrlData pad;
	
int main(int argc, char** argv)
{
	int result;
	btTransform trans;
   
	pspDebugScreenInit();
	SetupCallbacks();

	ResourceSetHomeDirectory(string(argv[0]));

	InitPhysics();
	CreateRigidBody(XYZ(0,150,0),XYZ(0,0,0),XYZ(1,1,1));
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
 	//  

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
	
	
	sceCtrlSetSamplingCycle(0);
	sceCtrlSetSamplingMode(PSP_CTRL_MODE_ANALOG);
          
	myTimer.start();

	while(!done)
	{
		sceCtrlReadBufferPositive(&pad, 1); 
		if((pad.Buttons & PSP_CTRL_LTRIGGER) && (pad.Buttons & PSP_CTRL_RTRIGGER) && (pad.Buttons & PSP_CTRL_START))			done = 1;
				
		//pspDebugScreenSetXY(0, 6);		
		//printf("Exe Path = %s", baseContentDirectoryPath.c_str());		
		
		//pspDebugScreenSetXY(0, 1);
	//	result = script.RunCommand("print('Manual LUA command: print');");	
	//	pspDebugScreenSetXY(0, 3);	
	//	result = script.RunScript();
	
		
	//	pspDebugScreenSetXY(0, 12);
	                  
		myTimer.update();
		UpdatePhysics();
	
		pspDebugScreenSetXY(0,1);
		
	    printf("Num Physics: %d\n",dynamicsWorld->getNumCollisionObjects());
		// print positions of all objects
   		for (int j=dynamicsWorld->getNumCollisionObjects()-1; j>=0 ;j--)
   		{
   			btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
   			btRigidBody* body = btRigidBody::upcast(obj);
   			if (body && body->getMotionState())
   			{
   			        body->getMotionState()->getWorldTransform(trans);
   		
   			        printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
   			}
   		}              

	
	  // printf("Num Physics: %d",dynamicsWorld->getNumCollisionObjects());
		//print positions of all objects
		// for (int j=dynamicsWorld->getNumCollisionObjects()-1; j>=0 ;j--)
		// {
		// 	btCollisionObject* obj = dynamicsWorld->getCollisionObjectArray()[j];
		// 	btRigidBody* body = btRigidBody::upcast(obj);
		// 	if (body && body->getMotionState())
		// 	{
		// 	        body->getMotionState()->getWorldTransform(trans);
		// 
		// 	        printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
		// 	}
		// }

	
		//pspDebugScreenSetXY(0, 2);
		//printf("Analog X = %d ", pad.Lx);
		//printf("Analog Y = %d \n", pad.Ly);
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
