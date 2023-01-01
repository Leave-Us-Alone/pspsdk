#pragma once
/*
    This file is part of CubicVR.

    CubicVR is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    CubicVR is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with CubicVR; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
    
    
    Source (c) 2009 by Derek Doucett unless otherwise specified
    To contact me, e-mail to ddoucett@cubicproductions.com
    http://www.cubicproductions.com
*/


#include <stdio.h>

#include <CubicVR/cvr_defines.h>
#include <CubicVR/Motion.h>

#define GAMEPAD_RUMBLE			100
#define RUMBLE_LEFT				101
#define RUMBLE_RIGHT			102

#ifdef _WIN32
	#define WIN32_LEAN_AND_MEAN
	#include "windows.h"
	#include <XInput.h>                       // Defines XBOX controller API
	#pragma comment(lib, "XInput.lib")        // Library containing necessary 360
											  // functions 
#endif

#ifdef __APPLE__
	#include <IOKit/hid/IOHIDUsageTables.h>
	#include "HID_Utilities_External.h"
#endif

#ifdef ARCH_PSP
	#include <psptypes.h>
	#include <pspctrl.h>
#endif

#ifdef ARCH_DC
	#include <kos.h>
#endif

#include "Gamepad_Mapping.h"

#define GAMEPAD_LEFT		0
#define GAMEPAD_RIGHT		1

class IMPEXP Gamepad : public Controllable
{
public:
	Gamepad();
	~Gamepad();
	
	bool Button(int btn);
	void Update();
	
	float X_Axis();
	float X_Axis(int stick);
	float Y_Axis();	
	float Y_Axis(int stick);	
		
	float Left_Trigger();
	float Right_Trigger();

	void Vibrate(float leftMotor, float rightMotor);
	
	void control(int controllerId, int motionId, float value);
	
//////////////////////////////////////////////////////////////////////////////////////
// Private Functions
//////////////////////////////////////////////////////////////////////////////////////
private:
	float Axis(int axi, int which);	

	void Tune();	
	void Set_Y_Axis_Inverted(int v);	
	int Y_Axis_Inverted();
		
//////////////////////////////////////////////////////////////////////////////////////
// Private Variables
//////////////////////////////////////////////////////////////////////////////////////
private:
	bool				bRightStickInverted;	// Y-Axis Inverted?
	
//////////////////////////////////////////////////////////////////////////////////////
// Private Variables Gamepad Setup for platform
//////////////////////////////////////////////////////////////////////////////////////
private:
	int rumbleLeft;									// Rumble Left
	int rumbleRight;								// Rumble Right

	#ifdef __APPLE__
		bool 				setMacDevice();
		pRecDevice 			mDevice;				// Darwin Device
	#endif
	
	#ifdef _WIN32
		DWORD				mConnected;				// Used to store if a controller is connected
		XINPUT_STATE		mState;					// Data type that stores all the current states of a controller.
		XINPUT_VIBRATION	mVibration;				// Vibration State
	#endif
	
	#ifdef ARCH_PSP
		SceCtrlData 		pad;					// PSP Datastruct for controller info
	#endif
	
	#ifdef ARCH_DC
		uint8				c;						// Dremacast controller number
		cont_cond_t 		pad;					// DC Datastruct for controller info
	#endif
};
