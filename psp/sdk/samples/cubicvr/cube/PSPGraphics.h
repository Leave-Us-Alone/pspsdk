typedef struct {
	float u, v;            // Texture Coordinates
	unsigned int color;    // Color value
	float nx, ny, nz;      // Normal values (NEW)
	float x, y, z;         // Position values
} Vertex;

Vertex __attribute__((aligned(16))) cube[3*12] = 
{
	{ 0, 1, color, 0.0f, 1.0f, 0.0f,-1.0f, 1.0f,-1.0f },	// Top
	{ 1, 1, color, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,-1.0f },
	{ 0, 0, color, 0.0f, 1.0f, 0.0f,-1.0f, 1.0f, 1.0f },
 
	{ 0, 0, color, 0.0f, 1.0f, 0.0f,-1.0f, 1.0f, 1.0f },
	{ 1, 1, color, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,-1.0f },
	{ 1, 0, color, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f },
 
	{ 0, 1, color, 0.0f,-1.0f, 0.0f,-1.0f,-1.0f, 1.0f },	// Bottom
	{ 1, 1, color, 0.0f,-1.0f, 0.0f, 1.0f,-1.0f, 1.0f },
	{ 0, 0, color, 0.0f,-1.0f, 0.0f,-1.0f,-1.0f,-1.0f },
 
	{ 0, 0, color, 0.0f,-1.0f, 0.0f,-1.0f,-1.0f,-1.0f },
	{ 1, 1, color, 0.0f,-1.0f, 0.0f, 1.0f,-1.0f, 1.0f },
	{ 1, 0, color, 0.0f,-1.0f, 0.0f, 1.0f,-1.0f,-1.0f },
 
	{ 0, 1, color, 0.0f, 0.0f, 1.0f,-1.0f, 1.0f, 1.0f },	// Front
	{ 1, 1, color, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f },
	{ 0, 0, color, 0.0f, 0.0f, 1.0f,-1.0f,-1.0f, 1.0f },
 
	{ 0, 0, color, 0.0f, 0.0f, 1.0f,-1.0f,-1.0f, 1.0f },
	{ 1, 1, color, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f },
	{ 1, 0, color, 0.0f, 0.0f, 1.0f, 1.0f,-1.0f, 1.0f },
 
	{ 0, 1, color, 0.0f, 0.0f,-1.0f,-1.0f,-1.0f,-1.0f },	// Back
	{ 1, 1, color, 0.0f, 0.0f,-1.0f, 1.0f,-1.0f,-1.0f },
	{ 0, 0, color, 0.0f, 0.0f,-1.0f,-1.0f, 1.0f,-1.0f },
 
	{ 0, 0, color, 0.0f, 0.0f,-1.0f,-1.0f, 1.0f,-1.0f },
	{ 1, 1, color, 0.0f, 0.0f,-1.0f, 1.0f,-1.0f,-1.0f },
	{ 1, 0, color, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f,-1.0f },
 
	{ 0, 1, color,-1.0f, 0.0f, 0.0f,-1.0f, 1.0f,-1.0f },	// Left
	{ 1, 1, color,-1.0f, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f },
	{ 0, 0, color,-1.0f, 0.0f, 0.0f,-1.0f,-1.0f,-1.0f },
 
	{ 0, 0, color,-1.0f, 0.0f, 0.0f,-1.0f,-1.0f,-1.0f },
	{ 1, 1, color,-1.0f, 0.0f, 0.0f,-1.0f, 1.0f, 1.0f },
	{ 1, 0, color,-1.0f, 0.0f, 0.0f,-1.0f,-1.0f, 1.0f },
 
	{ 0, 1, color, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },	// Right
	{ 1, 1, color, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,-1.0f },
	{ 0, 0, color, 1.0f, 0.0f, 0.0f, 1.0f,-1.0f, 1.0f },
 
	{ 0, 0, color, 1.0f, 0.0f, 0.0f, 1.0f,-1.0f, 1.0f },
	{ 1, 1, color, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,-1.0f },
	{ 1, 0, color, 1.0f, 0.0f, 0.0f, 1.0f,-1.0f,-1.0f }
 
};



	


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