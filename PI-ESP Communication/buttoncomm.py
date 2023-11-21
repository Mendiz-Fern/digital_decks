import serial
ser = serial.Serial('/dev/ttyACM0', 115200)
print('Reading')
while True:
	inp = ser.read()
	input_number = ord(inp)
	print("Button GPIO - " + str(input_number))
