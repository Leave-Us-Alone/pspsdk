#include <pspkernel.h>
#include <pspdebug.h>
#include <pspctrl.h>			// PSP Gamepad Controller

#include "Gamepad.h"

Gamepad::Gamepad()
{
}

Gamepad::~Gamepad()
{
}

unsigned int Gamepad::Buttons()
{
	return pad.Buttons;
}
		
unsigned char Gamepad::AnalogX()
{
	return pad.Lx;
}

unsigned char Gamepad::AnalogY()
{
	return pad.Ly;
}

bool Gamepad::ButtonDown(unsigned int buttons)
{
	if(pad.Buttons & buttons)		return true;
	return false;
}

bool Gamepad::ButtonUp(unsigned int buttons)
{
	if(pad.Buttons & buttons)		return false;
	return true;
}

bool Gamepad::Poll()
{
	sceCtrlReadBufferPositive(&pad, 1);
	
	if(pad.Buttons != lastpad.Buttons)
	{
		lastpad.Buttons = pad.Buttons;
		return true;
	}
	
	return false;
}
