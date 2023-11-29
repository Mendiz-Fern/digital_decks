import serial
ser = serial.Serial('/dev/ttyACM0', 115200)

inp1_num = 0
inp2_num = 0

## THIS HERE IS THE CODE TO READ A CARD AND SEND AN ACK##
# while(inp1_num == 0 and inp2_num == 0):
#     inp1 = ser.read()
#     inp2 = ser.read()
#     inp1_num = ord(inp1)
#     inp2_num = ord(inp2)
# print(f"Read back: {str(inp1_num)} and {str(inp2_num)}")

# print('Writing 0xF001 to ESP (ACK)')
# ser.write((chr(0xF0)).encode('charmap'))
# ser.write((chr(0x01)).encode('charmap'))

# THIS HERE IS THE CODE TO SEND 4 CARDS ##
print('Writing 0xFF00 to ESP (CARD_RECIEVE_BEGIN)')
ser.write((chr(0xFF)).encode('charmap'))
ser.write((chr(0x00)).encode('charmap'))

print('Writing 0x041B to ESP (BLUE_SKIP)')
ser.write((chr(0x04)).encode('charmap'))
ser.write((chr(0x1B)).encode('charmap'))

# print('Writing 0x0405 to ESP (WILD)')
# ser.write((chr(0x04)).encode('charmap'))
# ser.write((chr(0x05)).encode('charmap'))

# print('Writing 0x040C to ESP (RED_REVERSE)')
# ser.write((chr(0x04)).encode('charmap'))
# ser.write((chr(0x0C)).encode('charmap'))

# print('Writing 0x0418 to ESP (BLUE_0)')
# ser.write((chr(0x04)).encode('charmap'))
# ser.write((chr(0x18)).encode('charmap'))

print('Writing 0xFF01 to ESP (CARD_RECIEVE_END)')
ser.write((chr(0xFF)).encode('charmap'))
ser.write((chr(0x01)).encode('charmap'))


## THIS CODE HERE SHOULD TELL THE CONTROLLER THAT THE GAME IS OVER ##
# print('Writing 0xFFFF to ESP (GAME_OVER)')
# ser.write((chr(0xFF)).encode('charmap'))
# ser.write((chr(0xFF)).encode('charmap'))


## THIS CODE HERE SHOULD ASK THE CONTROLLER HOW MANY CARDS ITS GOTS AND GET AN ANSWER ##
# print('Writing 0xFECC to ESP (CARDS_LEFT)')
# ser.write((chr(0xFE)).encode('charmap'))
# ser.write((chr(0xCC)).encode('charmap'))

# inp1 = ser.read()
# inp2 = ser.read()
# inp1_num = ord(inp1)
# inp2_num = ord(inp2)
# print(f"Read back: {str(inp1_num)} and {str(inp2_num)}\n")

## THIS CODE HERE SHOULD ASK THE CONTROLLER FOR A COLOR AND GET AN ANSWER ##
# print('Writing 0x0260 to ESP (WANT_COLOR)')
# ser.write((chr(0x02)).encode('charmap'))
# ser.write((chr(0x60)).encode('charmap'))

# inp1 = ser.read()
# inp2 = ser.read()
# inp1_num = ord(inp1)
# inp2_num = ord(inp2)
# print(f"Read back: {str(inp1_num)} and {str(inp2_num)}")

# while True:
#     inp = ser.read()
#     input_number = ord(inp)
#     print("Read input back: " + str(input_number))

