function DisplayButtonPressed(name)
	if ButtonDown(name) == 1 then
		print(name .. " pressed");
	else
		print(name .. " unpressed");
	end
end

print("Analog X: " .. AnalogX());
print("Analog Y: " .. AnalogY());

DisplayButtonPressed("START");
DisplayButtonPressed("SELECT");

DisplayButtonPressed("CIRCLE");
DisplayButtonPressed("SQUARE");
DisplayButtonPressed("CROSS");
DisplayButtonPressed("TRIANGLE");

DisplayButtonPressed("LEFT-SHOULDER");
DisplayButtonPressed("RIGHT-SHOULDER");

DisplayButtonPressed("UP");
DisplayButtonPressed("DOWN");
DisplayButtonPressed("LEFT");
DisplayButtonPressed("RIGHT");