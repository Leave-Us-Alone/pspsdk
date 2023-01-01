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
    
    
    Source (c) 2003 by Charles J. Cliffe unless otherwise specified
    To contact me, e-mail or MSN to cj@cubicproductions.com or by ICQ#7188044
    http://www.cubicproductions.com
*/

#ifndef CUBICVR_GAMEPAD_360_H
#define CUBICVR_GAMEPAD_360_H


#ifdef WIN32

	#define WIN32_LEAN_AND_MEAN
	#include "windows.h"
	#include <XInput.h>

	namespace CubicVR
	{
			enum GamepadButtons		{	A				= XINPUT_GAMEPAD_A, 
										B				= XINPUT_GAMEPAD_B,
										X				= XINPUT_GAMEPAD_X,
										Y				= XINPUT_GAMEPAD_Y,
										LeftShoulder	= XINPUT_GAMEPAD_LEFT_SHOULDER,
										RightShoulder	= XINPUT_GAMEPAD_RIGHT_SHOULDER,
										LeftThumb		= XINPUT_GAMEPAD_LEFT_THUMB,
										RightThumb		= XINPUT_GAMEPAD_RIGHT_THUMB,
										Back			= XINPUT_GAMEPAD_BACK,
										Start			= XINPUT_GAMEPAD_START,
										DPad_Up			= XINPUT_GAMEPAD_DPAD_UP,
										DPad_Down		= XINPUT_GAMEPAD_DPAD_DOWN,
										DPad_Left		= XINPUT_GAMEPAD_DPAD_LEFT,
										DPad_Right		= XINPUT_GAMEPAD_DPAD_RIGHT };
			
			enum GamepadAxis		{	AxisHorizontal	= 0,
										AxisVertical	= 1 };
			enum GamepadSticks		{	StickLeft		= 0,
										StickRight		= 1 };
			enum GamepadTriggers	{	TriggerLeft		= 0,
										TriggerRight	= 1 };
			enum GamepadMotors		{	MotorLeft		= 0,
										MotorRight		= 1 };

			/**
			* The Gamepad class represents a mapping to an Xbox 360 controller.
			*
			* @author Derek Doucett
			*/
			class IMPEXP Gamepad
			{ 
				public:
					Gamepad();
					~Gamepad();
					
					void			Poll();
					
					int				Button_Pressed			(GamepadButtons buttons);
					int				Button_Held				(GamepadButtons buttons);

					float			Axis					(GamepadSticks  sticks, GamepadAxis direction);

					int				Trigger					(GamepadTriggers trigger);
					bool			Trigger_Pressed			(GamepadTriggers trigger);				

					bool			Inverted_Y				();

					//void			Rumble					(int leftMotor, int rightMotor);
					//int			Get_Rumble_Motor		(GamepadMotors motor);								

				private:
					bool			bRightStickInverted;	// Y-Axis Inverted?

					DWORD			dwResult;				// Used to store if a controller is connected
					XINPUT_STATE	state;					// Data type that stores all the current states
															// of a controller.
					XINPUT_VIBRATION vibration;				// Vibration State
			};
	}
#endif

#endif