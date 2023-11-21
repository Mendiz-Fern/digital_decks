import serial
ser = serial.Serial('/dev/ttyACM0', 115200)

print('Writing y and enter to ESP')
ser.write('y'.encode('ascii'))
ser.write('\r'.encode('ascii'))

while True:
    inp = ser.read()
    input_number = ord(inp)
    print("Read input back: " + str(input_number))

