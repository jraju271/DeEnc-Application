layer=int(input("Enter the no of layers:(1-5)"))
input_str=input("Enter the input string:")
list_of_algo=["Shift","Caesar","Rot13","AtBash","Route"]


            
def shift(input_str,count):
    alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
    new_message = ''
    for letter in input_str:
        letter = letter.lower() 
        if letter.isalpha():
            shift_pos = alphabet.index(letter) + count
            new_pos = alphabet[shift_pos]
            new_message += new_pos
        elif ' ' or '/t' or '/n' in letter: 
            new_message += letter
        elif letter.isnumeric(): 
            new_message += letter
        else:
            return "An error took place in recording the message. Check input.\n"
        return new_message

def caesar(input_str,count):
    alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
    new_message = ''
    for letter in input_str:
        letter = letter.lower() 
        if letter.isalpha():
            shift_pos = alphabet.index(letter) + count
            new_pos = alphabet[shift_pos]
            new_message += new_pos
        elif ' ' or '/t' or '/n' in letter: 
            new_message += letter
        elif letter.isnumeric(): 
            new_message += letter
        else:
            return "An error took place in recording the message. Check input.\n"
        return new_message

def rot13(input_str):
    count=13
    alphabet = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
    new_message = ''
    for letter in input_str:
        letter = letter.lower() 
        if letter.isalpha():
            shift_pos = alphabet.index(letter) + count
            new_pos = alphabet[shift_pos]
            new_message += new_pos
        elif ' ' or '/t' or '/n' in letter: 
            new_message += letter
        elif letter.isnumeric(): 
            new_message += letter
        else:
            return "An error took place in recording the message. Check input.\n"
        return new_message


def selection(algo):
    if(algo=="Shift"):
        n=int(input("Enter the shift count:"))
        enc=shift(input_str,n)
    elif(algo=="Caesar"):
        n=int(input("Enter the shift count:"))
        enc=caesar(input_str,n)
    elif(algo=="Rot13"):
        enc=rot13(input_str)
    elif(algo=="AtBash"):
        enc=atbash(input_str)
    elif(algo=="Route"):
        enc=route(input_str)
    return enc

if(layer==1):
    for i in range(0,3):
        type_algo=list_of_algo[i]
        encr_str=selection(type_algo)
        input_str=encr_str
'''elif(layer==2):
    for i in range(0,5):
        for j in range(i,5):'''