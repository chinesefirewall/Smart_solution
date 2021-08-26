#!/usr/bin/python3
# source: http://www.binarytides.com/python-socket-programming-tutorial/
#
# full threaded socket server example in python
# file: nutilahendused-2020-socket-server.py

import socket
import sys
import time
import random

from _thread import *  # low level threading library

import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
    
command = 0
def seven_seg():
    global command
    def number(n):
        t = 1
        if n==0:        #0
            # 16,18,22,36,13,15,37
            GPIO.output(16, GPIO.LOW)
            GPIO.output(18, GPIO.LOW)
            GPIO.output(22, GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(13, GPIO.LOW)
            GPIO.output(15, GPIO.LOW)
            time.sleep(t)
            GPIO.output(16, GPIO.HIGH)
            GPIO.output(18, GPIO.HIGH)
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(15, GPIO.HIGH)
            
        if n==1:    #1
            GPIO.output(22, GPIO.LOW)
            GPIO.output(36,GPIO.LOW) 
            time.sleep(t)
            GPIO.output(22,GPIO.HIGH)
            GPIO.output(36,GPIO.HIGH)

        if n==2:       #2
            GPIO.output(13, GPIO.LOW)
            GPIO.output(36,GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(16,GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            time.sleep(t)
            GPIO.output(16, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(37, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            
            
        if n==3:        #3
            GPIO.output(13, GPIO.LOW)
            GPIO.output(36,GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            time.sleep(t)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(36,GPIO.HIGH)
            GPIO.output(37, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            
            
        if n==4:        #4
            GPIO.output(15, GPIO.LOW)
            GPIO.output(37,GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            time.sleep(t)
            GPIO.output(15, GPIO.HIGH)
            GPIO.output(37,GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
            
            
        if n==5:        #5
            GPIO.output(13, GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            time.sleep(t)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            
            
        if n==6:        #6
            GPIO.output(13, GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(16,GPIO.LOW)
            time.sleep(t)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(16,GPIO.HIGH)
            
            
        if n==7:        #7
            GPIO.output(13, GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(22,GPIO.LOW)
            time.sleep(t)
            GPIO.output(13, GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(22,GPIO.HIGH)
          
            
        if n==8:        #8
            GPIO.output(22, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37,GPIO.LOW)
            GPIO.output(16, GPIO.LOW)
            time.sleep(t)
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37,GPIO.HIGH)
            GPIO.output(16, GPIO.HIGH)
           
            
        if n==9:        #9
            GPIO.output(22, GPIO.LOW)
            GPIO.output(18,GPIO.LOW)
            GPIO.output(36, GPIO.LOW)
            GPIO.output(13,GPIO.LOW)
            GPIO.output(15,GPIO.LOW)
            GPIO.output(37,GPIO.LOW)
            time.sleep(t)
            GPIO.output(22, GPIO.HIGH)
            GPIO.output(18,GPIO.HIGH)
            GPIO.output(36, GPIO.HIGH)
            GPIO.output(13,GPIO.HIGH)
            GPIO.output(15,GPIO.HIGH)
            GPIO.output(37,GPIO.HIGH)    
        
            
            
        

    pins = [16,18,22,36,13,15,37]
    GPIO.setup(pins, GPIO.OUT)
    GPIO.output(pins, GPIO.HIGH)
#     GPIO.setup(pins, GPIO.OUT, initial=GPIO.HIGH)
    
    

    i = 0
    time.sleep(1)
    while True:
        if command == 'start':
            number(i)
            i=i+1
            if i == 10:
                i = 0
        if command == 'reverse':
            
            number(i)
            i=i-1
            if i<0:
                i = 9
        
        if command == 'random':
            i = random.randint(0,9)
            number(i)
            
        if command == 'restore':
            number(i)
            i=i+1
            if i == 10:
                i = 0           
        print(i)
while True:
    command = input("Enter command: ")
    seven_seg()


    