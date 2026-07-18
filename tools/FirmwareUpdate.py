import struct   #This library is to pack integers into 4 bytes or whichever bytes needed
import zlib     #For CRC32 Calculation
import serial   # THis library is for the transport of data from host <--> STM via UART

magic = bytes([0x69])       #here the [] is important, without it python assumes it as a regular integer and sets 0x69 or 105 bytes of zeros


#This application.bin seems to be a problem, gonna investigate from this point tomorrow
#with open('../app/Application.bin', 'rb') as f:
#    firmware = f.read()
firmware = bytes([0xAB, 0xCD, 0xBE, 0xEF])
length = len(firmware)
length_bytes = struct.pack('<I',length)

crc32 = zlib.crc32(firmware)            #CRC Calculation for the firmware
crc32_bytes = struct.pack('<I', crc32)  #Packing the crc32 into a structure of 4 byte words since it is an integer and needs to be converted as raw bytes to be sent

#final Message appending
final = magic + length_bytes + firmware + crc32_bytes


port = serial.serial_for_url('socket://localhost:3456') #This line says open a socket at 3456 ; socket tells us this is a TCP socket connection and Not a USBtty0 connection
port.write(final)           # this is for the writing of data via the serial port we just create
port.close()