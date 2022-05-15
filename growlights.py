#!/usr/bin/env python3
import serial
import time
#import keyboard
from datetime import datetime

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyUSB0', 9600, timeout=1)
    ser.reset_input_buffer()
    print(datetime.now().strftime("%H:%M:%S"))

    print(datetime.now().hour)


    while True:
        #ser.write(b"Hello from Raspberry Pi!\n")
        if((datetime.now().hour<21)and (datetime.now().hour>6)):
            ser.write(b"true\n");
            #print("true")
        else:
            ser.write(b"false\n");
            
            #print("false")
        #print(datetime.now().hour)
        line = ser.readline().decode('utf-8').rstrip()
        print(line)
        time.sleep(1)
