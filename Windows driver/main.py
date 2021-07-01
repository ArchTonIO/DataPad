
from dataPadHandler import serialHandler
import pyautogui
import time

def reMap(value, minInput, maxInput, minOutput, maxOutput):

	value = maxInput if value > maxInput else value
	value = minInput if value < minInput else value

	inputSpan = maxInput - minInput
	outputSpan = maxOutput - minOutput

	scaledThrust = float(value - minInput) / float(inputSpan)

	return minOutput + (scaledThrust * outputSpan)

def main():

	#try:

	dataPadHandler = serialHandler()
	dataPadHandler.initComunication()
	firstCommandList = ["Delete\n", "Point\n", "Polyline\n", "PlanarSrf\n", "ExtrudeCrv\n", "Join\n", "Split\n", "Group\n", "Move\n", "Rotate3D\n", "BooleanUnion\n", "FilletEdge\n", "MakeHole\n", "Offset\n", "DupEdge\n", "Centermark\n", "Align\n", "Undo\n", "Copy\n", "\n"]
	secondCommandList = ["", "", "Circle\n", "EdgeSrf\n", "ExtrudeSrf\n", "Explode\n", "Trim\n", "Ungroup\n", "Distance\n", "Rotate\n", "BooleanDifference\n", "Fillet\n", "RoundHole\n", "Divide\n", "DupFaceBorder\n", "Length\n", "", "Redo\n", "", "Paste\n", ""]	
	
	minJoystickInputValue = 30
	maxJoystickInputValue = 4020

	
	maxCursorSpeed = 5
	cursorActivationTreshold = 1.5
	
	pyautogui.PAUSE = 0
	pyautogui.FAILSAFE = False

	while True:

		dataPadHandler.update()
		
		lastXvalue = dataPadHandler.getJoystickX()
		lastYvalue = dataPadHandler.getJoystickY()

		xValue = reMap(lastXvalue, minJoystickInputValue, maxJoystickInputValue, maxCursorSpeed, -maxCursorSpeed)
		yValue = reMap(lastYvalue, minJoystickInputValue, maxJoystickInputValue, -maxCursorSpeed, maxCursorSpeed)

		if -cursorActivationTreshold < xValue < cursorActivationTreshold:
			xValue = 0
		
		if -cursorActivationTreshold < yValue < cursorActivationTreshold:
			yValue = 0
	

		#if dataPadHandler.getButtonNum(0) == "1":
			
		#	pyautogui.keyDown('shiftright')
		#	time.sleep(0.3)
		#else:
			
		#	pyautogui.keyUp('shiftright')	
		
	
	
		pyautogui.moveRel(xValue, yValue, duration = 0)
		



        
        
		i = 0

		while i < 20: 

			if dataPadHandler.getButtonNum(i) == "1":

				if dataPadHandler.getButtonNum(20) == "1":

					pyautogui.typewrite(secondCommandList[i], interval = 0)
					
					

				else:

					pyautogui.typewrite(firstCommandList[i], interval = 0)
					
					
			i = i + 1

	#except:
		#main()	

main()			
