# -*- coding: utf-8 -*-
"""
The v2 version of the server program in python

@author: Virág Gábor
"""
#imports
from getpass import getpass
from datetime import datetime
import os

#variables
run_program=True # True = run false = stop
state_line=[True , True , True , True , True , True , True , True , True]
u_name=''
u_pw=''

#functions

def line_status(state_line):
    
    f=open('logs.txt','r')
    for line in f:
        sv=line.split('\t')
        if sv[0]=='LOGIN':
            state_line[int(sv[2])-1]=False          
        
        elif sv[0]=='LOGOUT':
            state_line[int(sv[2])-1]=True
        
def clear_screen():
    os.system('clear')
    printlines('menu')
    
def logs(u_name,line,status):
    dt = datetime.now()
    timestamp = datetime.timestamp(dt)
    date_time = datetime.fromtimestamp(timestamp)
    str_date_time = date_time.strftime("%H:%M:%S %d-%m-%Y\n")
    f=open("logs.txt","a")
    if status=='LOGIN':
        f.write('LOGIN\t'+u_name+'\t'+line+'\t'+str_date_time)
    elif status=='LOGOUT':
        f.write('LOGOUT\t'+u_name+'\t'+line+'\t'+str_date_time)
    elif status=='FAILED LOGIN':
        f.write('FAILED LOGIN\t'+u_name+'\t\t'+str_date_time)
    else:
        print('ERROR')    
    
    f.close()

def login():
    login_run=True
    global u_name
    global u_pw
    key=[1,-4,9,14,-1] #eltolás értéke
    i=0
    login_succ=0
    print("///////////////////////\n/Terminal Server Login/\n///////////////////////")
    while login_run: 
        u_name= input("Username: ")
        u_pw= getpass("Password: ")
        with open("login_new.txt", "r", encoding="utf-8") as f:    
            for line in f:
                line=line.replace(line[len(line)-1],'')
                i=0
                z=''
                for x in line:
                    y=0
                    if x==' ':
                        z=z+' '
                    else:
                        if i==5:
                           i=0
                        y = ord(x) - key[i]
                        i=i+1
                        z=z+chr(y)
                data=z.split()
                if data[0]==u_name and data[1]==u_pw:
                    login_succ=1
                
            f.seek(0)
        if login_succ==1:
            print("Successful login!")
            login_run=False            
        else:
            print('Failed login attempt! Try again!')
            logs(u_name,'line','FAILED LOGIN')
        f.close()

def printlines(label):
    if label=='menu':
        i=1
        print('--------------------------')
        print('-    Terminal Server     -')
        print('--------------------------')
        print('\n----------------------')
        while i!=10:
            print(i,' - Connect to Line',i)
            i=i+1
        print('----------------------')
        print('10  - Show empty lines')
        print('11  - Connect to the Remote Power Supplier')
        print('12  - History')
        print('13  - Cleaning screen')
        print('14  - Help')
        print('15  - Close Program')
    
    elif label=='help':
        print('Help is on the way')
    
    elif label=='apc':
        print('------------')
        print('-APC config-')
        print('------------')
        print('Choose outlet <1-8>')
        print('9 - Outlet status')
        print('10 - Back')


def commands(x):
    if x>=1 and x<10: #connect to line 1-10
        if state_line[x-1]==True:
            state_line[x-1]=False
            print('Connecting to Line ',x) 
            logs(u_name,str(x),'LOGIN')
            sv='sudo minicom line'+str(x)
            print(sv) 
            #os.system(sv)
            logs(u_name,str(x),'LOGOUT')
            state_line[x-1]=True
        else:
            print('This line is taken try another!')
    
    if x==10: #show empty lines
        sv=0
        y=1
        print('-----------------------\n-     Empty lines     -\n-----------------------\n')
        for i in state_line:
            if i==True:
                print('Line',y,'is empty')
                sv=1
            y=y+1
        if sv==0:
            print('There is no empty line at the moment try again later!')
    
    elif x==11:  #apc handler
        printlines('apc')
        apc_run=True
        apc_command=True
        apc_event=True
        outlet_value=0
        while apc_run:
            
            while apc_command:                
                apc_command_input=int(input('Enter your input: '))
                if apc_command_input<1 or apc_command_input>10:
                    print('Invalid input!')
                else:
                    if apc_command_input==10:
                        apc_command=False
                        apc_run=False
                        apc_event=False
                        clear_screen()
                        #printlines('menu')
                    elif apc_command_input==9:
                        #os.system('apc --status')
                        print('Status')
                    else:                        
                        apc_command=False
                        apc_event=True
                        outlet_value=apc_command_input
                        print('------------------------')
                        print('Your chosen outlet: ',outlet_value)
                        print('------------------------')
                        print('1 - Power on')
                        print('2 - Power off')
                        print('3 - Reboot device')
                        print('4 - Back')
            
            
            while apc_event:                
                apc_event_input=int(input('Enter your input: '))
                if apc_event_input<1 or apc_event_input>5:
                    print('Invalid input')
                else:
                    if apc_event_input==4:
                        apc_event=False
                        apc_command=True
                        #system clear
                        printlines('apc')
                    
                    elif apc_event_input==3: #reboot
                        sv='apc --reboot '+str(outlet_value)
                        #os.system(sv)
                        print(sv)
                    
                    elif apc_event_input==2: #off
                        sv='apc --off '+str(outlet_value)
                        #os.system(sv)
                        print(sv)
                    
                    elif apc_event_input==1: #on
                        sv='apc --on '+str(outlet_value)
                        #os.system(sv)
                        print(sv)
                    
                        
    elif x==12: #history
        f=open('logs.txt','r')
        print('-----------\n',u_name,'earlier sessions\n-----------')
        for line in f:
            line=line.replace(line[len(line)-1],'')
            fields=line.split('\t')
            if fields[0]=='LOGIN':
                if fields[1]==u_name:
                    print('line'+str(fields[2]),fields[3])
        f.close()
        
    elif x==13: #clear screen
        #clear_screen()
        printlines('menu')
    
    elif x==14: #print help
        printlines('help')
    
    elif x==15: #exit program
        x=0
        
    return x
        
if __name__ == "__main__":
    line_status(state_line)
    login()
    printlines('menu')
    
    while run_program:
        x=int(input('Enter your input: '))  
        if x<1 or x>16:
            print('Invalid input')
        else:
            x=commands(x)
        
        if x==0:
            run_program=False