
import serial

class serialHandler():


	def __init__(self):

		self.buttonsValues = ["0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0"]
		self.buttonLocks = [False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False]
		self.joystickXvalue = 0
		self.joystickYvalue = 0
		self.updateMethodCallCounter = 0
		self.ser = serial.Serial ('COM3')
		self.baudrate = 115200
		self.line = ""
		self.counter = 0
	

	def initComunication(self):

		self.ser.baudrate = self.baudrate
		self.ser.close()
		self.ser.open()



	def readData(self):
	
		self.line = str(self.ser.readline().strip())
		
	
	def readButtonsValues(self):
		
		i = 2
		j = 0
		
		while i < 23:
		 
			self.buttonsValues[j] = self.line[i]

			i = i + 1
			j = j + 1
		
		
	def readJoytickValues(self):

		#X value:

		i = 24
		joystickXvalueInString = ""

		while self.line[i] != " ":

			joystickXvalueInString = joystickXvalueInString + self.line[i]
			i = i + 1

		#Y value:	

		joystickYvalueInString = ""

		while i < len(self.line)-1:#-1 is beacause the last char of the line is "'" and we don't want it to not get errors

			joystickYvalueInString = joystickYvalueInString + self.line[i]
			i = i + 1	
			


		self.joystickXvalue = int(joystickXvalueInString)
		self.joystickYvalue = int(joystickYvalueInString)

	def removeAllButtonsLocks(self):
		
		i = 0
		while i < 21:

			self.buttonLocks[i] = False	
			i = i + 1

		self.counter = self.counter + 1		

		print("Removed all button locks " + str(self.counter))	
	
	def update(self):

		self.readData()
		self.readButtonsValues()
		self.readJoytickValues()
		self.updateMethodCallCounter = self.updateMethodCallCounter + 1
		if self.updateMethodCallCounter == 100:
			self.removeAllButtonsLocks()
			self.updateMethodCallCounter = 0


	
	def getButtonNum(self, numButton):

		
		output = "0"

		if self.buttonsValues[numButton] == "1":
			print("Button is pressed")
		
			if self.buttonLocks[numButton] == False:
							
				output = self.buttonsValues[numButton]
				
				self.buttonLocks[numButton] = True

		counter = 0

		return output


				


	def getJoystickX(self):
		
		return self.joystickXvalue 


	def getJoystickY(self):
		
		return self.joystickYvalue 	 


				 	
		
#000000000000000000000 2222 2222


	


	












