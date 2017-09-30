import pygame
import socket

pygame.init()
pygame.joystick.init()
x=pygame.joystick.get_count()
numaxes=0
numbut=0
numhats=0 

if x==0: 
    print "Joystick not connected"
else:
    print "Connected"
    
for i in range(x):
    joystick=pygame.joystick.Joystick(i)
    joystick.init()
    numaxes=joystick.get_numaxes()
    numbut=joystick.get_numbuttons()
    numhats=joystick.get_numhats()

transmit=socket.socket()
   #h=socket.gethostbyaddr('192.168.0.3')
#print h
host = '192.168.1.7'
port = 23

try:
    transmit.connect((host,port))
except Exception:
    print "Couldn't connect to LAN to UART"
    exit(0) 
    
valaxis=[2048,2048,13,2]
axis = [0]*numaxes
button=[0]*numbut
hats=[0]*numhats
mode='Rover'

def robotic_arm(): 
    print "Insert code here"

while True:
    for event in pygame.event.get():
        if event == pygame.QUIT:
            pygame.quit()

        for i in range(0,numaxes):
            axis[i]=joystick.get_axis(i)
            axis[i]=int(axis[i]*1024)
            valaxis[i]=axis[i]+2048;

        if(axis[1]>2048):
            valaxis[1]=valaxis[1]*(-1)
            valaxis[1]=valaxis[1]+4096  
        elif(axis[1]<2048):
            valaxis[1]=valaxis[1]*(-1)
            valaxis[1]=valaxis[1]+4096
                                                                                
        valaxis[2]=(float(valaxis[2])/1024)
        valaxis[2]=int(valaxis[2]*13)

        if(valaxis[3]>3000):
            valaxis[3]=3
        elif(valaxis[3]<1300):
            valaxis[3]=1
        else:
            valaxis[3]=2
            
        for i in range(0,numbut):            
            button[i]=joystick.get_button(i) 

        for i in range(0, numhats):
            hats[i]=joystick.get_hat(i)

        if (button[0]==1)and(mode=='Arm'):
            mode = 'Rover'
        elif (button[0]==1)and(mode=='Rover'):
            mode = 'Arm'

    if mode=='Rover':
        value='a'+str(valaxis[0])+str(valaxis[1])+str(valaxis[2])+str(valaxis[3])
        transmit.send(value)
        print value
    else:
        #print button  
        
        if((valaxis[0]>1900)and(valaxis[0]<2200)and(valaxis[1]>1900)and(valaxis[1]<2200)):
            #swivel
            if(button[2]==1):
                value='rs'+str(valaxis[2])
                transmit.send(value)
                print value
            elif(button[3]==1):
                value='rS'+str(valaxis[2])
                transmit.send(value)
                print value
            #pitch
            if(button[4]==1):
                value='rp'
                transmit.send(value)
                print value
            elif(button[5]==1):
                value='rP'
                transmit.send(value)
                print value
            #gripper
            if(hats[0][1] == 1):
                value='rg'
                transmit.send(value)
                print value
            elif(hats[0][1] == (-1)):
                value='rG'
                transmit.send(value)
                print value
            #actuator
            if(button[6]==1):
                value='rb'
                transmit.send(value)
                print value
            elif(button[7]==1):
                value='rB'
                transmit.send(value)
                print value
            #DC Servo
            if(button[8]==1):
                value='rT'+str(valaxis[2])
                transmit.send(value)
                print value
            elif(button[9]==1):
                value='rt'+str(valaxis[2])
                transmit.send(value)
                print value
            #roll
            if(button[10]==1):
                value='rq'+str(valaxis[2])
                transmit.send(value)
                print value
            elif(button[11]==1):
                value='rQ'+str(valaxis[2])
                transmit.send(value)
                print value
            else
            	value="rc"
            	transmit.send(value)
            	print value     
