-- A simple test script
print("CubicVR - Lua Testbed", "Press cross for exit")

lastPad = 0
while true do
	waitVblankStart();
	pad = ctrlRead()
	if lastPad ~= pad then
		lastPad = pad
		if isCtrlCircle(pad) then
			print("circle pressed")
		elseif isCtrlCross(pad) then
			break
		end
	end
end
