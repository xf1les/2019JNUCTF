from time import *
import sys

with open('flag.txt','r') as f:
    flag = f.read()

def name():
    sys.stdout.write("My name is Xp0int\n\n")

def email():
    sys.stdout.write("My email is xp0intjnu@gmail.com\n\n")

def addr():
    sys.stdout.write("My addr is XXXXXXX JNU\n\n")

def secret():
    sys.stdout.write("You wanna know my secret? I won't tell you. Guess it:")
    sys.stdout.flush()
    input_flag = raw_input()
    length = len(input_flag)
    if(length == 0):
        sys.stdout.write("I told you ,i won't tell you!\n\n")
        return False
    if(length > len(flag)):
        sys.stdout.write("I don't have so many secrets.\n\n")
        return False
    if input_flag.lower() == "exit":
        exit(1)
    for i in range(length):
        if input_flag[i] != flag[i]:
            sys.stdout.write("Oops!\n\n")
            return False
    return True


for i in range(0x10000):
    sys.stdout.write("I wanna give you sth\n")
    sys.stdout.write("1.My name\n2.My email\n3.My addr\n4.My secret\n")
    sys.stdout.write("Now choose what yout wanna know:");
    sys.stdout.flush()
    input_choice = raw_input()
    if input_choice == '1':
        name()
    elif input_choice == '2':
        email()
    elif input_choice == '3':
        addr()
    elif input_choice == '4':
        secret()
    else:
        print("Excuse me??? What you want to do ?!!\n")
