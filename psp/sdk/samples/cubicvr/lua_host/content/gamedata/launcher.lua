function DisplayMenuItem(name, display, button, luaFile)
	print(display .. " - " .. name);
	if ButtonDown(button) == 1 then
		RunScript(luaFile);
	end	
end


print("CubicVR PSP Demo Launcher\n");

DisplayMenuItem("Gamepad Test", "Cross ", "CROSS", "gamepad.lua");

-- DisplayMenuItem("Gamepad Analog Test", "Cross ", "CROSS", "analog.lua");
-- DisplayMenuItem("Gamepad Buttons Test", "Square", "SQUARE", "button.lua");
-- DisplayMenuItem("Gamepad Test", "Circle", "CIRCLE", "gamepad.lua");