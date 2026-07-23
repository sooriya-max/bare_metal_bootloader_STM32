import struct   #This library is to pack integers into 4 bytes or whichever bytes needed
import zlib     #For CRC32 Calculation
import serial   # THis library is for the transport of data from host <--> STM via UART
import time 
import ecdsa    #This is for signing theprivate key ourself
import hashlib  #THis is to hash the firmware ourself instead of letting python do it
magic = bytes([0x69])       #here the [] is important, without it python assumes it as a regular integer and sets 0x69 or 105 bytes of zeros


#This application.bin seems to be a problem, gonna investigate from this point tomorrow
with open('../app/Application.bin', 'rb') as f:
    firmware = f.read()
#firmware = bytes([0xAB, 0xCD, 0xBE, 0xEF])
length = len(firmware)
length_bytes = struct.pack('<I',length)

crc32 = zlib.crc32(firmware) & 0xffffffff         #CRC Calculation for the firmware
crc32_bytes = struct.pack('<I', crc32)            #Packing the crc32 into a structure of 4 byte words since it is an integer and needs to be converted as raw bytes to be sent

#Obtaining the Private key and then storing it in signature variable
with open('private_key.pem', 'rb') as f:
    pem_data = f.read()
sk = ecdsa.SigningKey.from_pem(pem_data)
# signature = sk.sign(firmware) ##This hashes diffently that my boootloaader, so using the below hashing and digesting techniques to compensate for it

hash = hashlib.sha256(firmware).digest() 
signature = sk.sign_digest(hash)



#final Message appending
final = magic + length_bytes + firmware + crc32_bytes + signature


port = serial.serial_for_url('socket://localhost:3456') #This line says open a socket at 3456 ; socket tells us this is a TCP socket connection and Not a USBtty0 connection


# #Debug Lines
print(f"length = {length}")
print(f"crc32  = {hex(crc32)}")
print(f"first 4 bytes = {firmware[:4].hex()}")
print(f"last 4 bytes  = {firmware[-4:].hex()}")
# #Debug Lines End


#port.write(final)           # this is for the writing of data via the serial port we just create
for byte in final:
    port.write(bytes([byte]))
    time.sleep(0.0001)           #1ms Delay

port.close()