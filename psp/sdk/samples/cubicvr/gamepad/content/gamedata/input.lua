print("input.lua : start\n");

if ButtonDown("CIRCLE") == 1 then
	print("Circle pressed!");
end

if ButtonDown("SQUARE") == 1 then
	print("Square pressed!");
end

if ButtonDown("CROSS") == 1 then
	print("Cross pressed!");
end

if ButtonDown("TRIANGLE") == 1 then
	print("Triangle pressed!");
end


if ButtonDown("LSHOULDER") == 1 then
	print("Left Shoulder pressed!");
end

if ButtonDown("RSHOULDER") == 1 then
	print("Right Shoulder pressed!");
end


if ButtonDown("UP") == 1 then
	print("Up pressed!");
elseif ButtonDown("DOWN") == 1 then
	print("Down pressed!");
end

if ButtonDown("LEFT") == 1 then
	print("Left pressed!");
elseif ButtonDown("RIGHT") == 1 then
	print("Right pressed!");
end



print("\ninput.lua : end");