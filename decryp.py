import math




lookup_table = {'A' : 'Z', 'B' : 'Y', 'C' : 'X', 'D' : 'W', 'E' : 'V',
        'F' : 'U', 'G' : 'T', 'H' : 'S', 'I' : 'R', 'J' : 'Q',
        'K' : 'P', 'L' : 'O', 'M' : 'N', 'N' : 'M', 'O' : 'L',
        'P' : 'K', 'Q' : 'J', 'R' : 'I', 'S' : 'H', 'T' : 'G',
        'U' : 'F', 'V' : 'E', 'W' : 'D', 'X' : 'C', 'Y' : 'B', 'Z' : 'A',

        'a' : 'z', 'b' : 'y', 'c' : 'x', 'd' : 'w', 'e' : 'v',
        'f' : 'u', 'g' : 't', 'h' : 's', 'i' : 'r', 'j' : 'q',
        'k' : 'p', 'l' : 'o', 'm' : 'n', 'n' : 'm', 'o' : 'l',
        'p' : 'k', 'q' : 'j', 'r' : 'i', 's' : 'h', 't' : 'g',
        'u' : 'f', 'v' : 'e', 'w' : 'd', 'x' : 'c', 'y' : 'b', 'z' : 'a'}


            
def shift(text,s):
    result = ""
 
    # traverse text
    for i in range(len(text)):
        char = text[i]
 
        # Encrypt uppercase characters
        if (char.isupper()):
            result += chr((ord(char) - s-65) % 26 + 65)
 
        # Encrypt lowercase characters
        else:
            result += chr((ord(char) - s - 97) % 26 + 97)
 
    return result

def caesar(text,s):
    result = ""
 
    # traverse text
    for i in range(len(text)):
        char = text[i]
 
        # Encrypt uppercase characters
        if (char.isupper()):
            result += chr((ord(char) - s-65) % 26 + 65)
 
        # Encrypt lowercase characters
        else:
            result += chr((ord(char) - s - 97) % 26 + 97)
 
    return result

def rot13(text,s=13):
    result = ""
    # traverse text
    for i in range(len(text)):
        char = text[i]
 
        # Encrypt uppercase characters
        if (char.isupper()):
            result += chr((ord(char) - s-65) % 26 + 65)
 
        # Encrypt lowercase characters
        else:
            result += chr((ord(char) - s - 97) % 26 + 97)
 
    return result

def atbash(message):
    cipher = ''
    for letter in message:
        # checks for space
        if(letter != ' '):
            #adds the corresponding letter from the lookup_table
            cipher += lookup_table[letter]
        else:
            # adds space
            cipher += ' '
 
    return cipher


def route(cipher, key):
    msg = ""
    # track key indices
  
    # track msg indices
    k_indx = 0
    msg_indx = 0
    msg_len = float(len(cipher))
    msg_lst = list(cipher)
  
    # calculate column of the matrix
    col = key
      
    # calculate maximum row of the matrix
    row = int(math.ceil(msg_len / col))
  
    # convert key into list and sort 
    # alphabetically so we can access 
    # each character by its alphabetical position.
  
    # create an empty matrix to 
    # store deciphered message
    dec_cipher = []
    for _ in range(row):
        dec_cipher += [[None] * col]
  
    # Arrange the matrix column wise according 
    # to permutation order by adding into new matrix
    for i in range(col):
        curr_idx = i
  
        for j in range(row):
            dec_cipher[j][curr_idx] = msg_lst[msg_indx]
            msg_indx += 1
        
  
    # convert decrypted msg matrix into a string
    try:
        msg = ''.join(sum(dec_cipher, []))
    except TypeError:
        raise TypeError("This program cannot","handle repeating words.")
  
    null_count = msg.count('_')
    
  
    if null_count > 0:
        return msg[: -null_count]
    return msg




def selection(algo):
    if(algo=="Shift" ):
        n=int(input("Enter the shift count for Shift:"))
        enc=shift(input_str,n)
    elif(algo=="Caesar"):
        n=int(input("Enter the shift count for Caesar:"))
        enc=caesar(input_str,n)
    elif(algo=="Rot13"):
        enc=rot13(input_str)
    elif(algo=="AtBash"):
        enc=atbash(input_str)
    elif(algo=="Route"):
        key=int(input("Enter key int value : "))
        enc=route(input_str, key)
    return enc

if __name__== "__main__":
    while(1):
        input_str=input("Enter the encrypted string:")
        layer=int(input("Enter the no of layers:(1-5)"))
        list_of_algo=["Shift","Caesar","Rot13","AtBash","Route"]

        print("\n",list_of_algo,"[0,1,2,3,4]\n")

        if(layer==1):
            x = int(input("Enter your algo choice : "))
            type_algo=list_of_algo[x]
            encr_str=selection(type_algo)
            input_str=encr_str
            print(input_str)


        if(layer==2):
            x = list(map(int, input("layer option for 2 : ").split()))
            for i in range(0,2):
                type_algo=list_of_algo[x[i]]
                encr_str=selection(type_algo)
                input_str=encr_str
            print(input_str)

        elif(layer==3):
            x = list(map(int, input("layer option for 3 : ").split()))
            for i in range(0,3):
                type_algo=list_of_algo[x[i]]
                encr_str=selection(type_algo)
                input_str=encr_str
            print(input_str)

        elif(layer==4):
            x = list(map(int, input("layer option for 4 : ").split()))
            for i in range(0,4):
                type_algo=list_of_algo[x[i]]
                encr_str=selection(type_algo)
                input_str=encr_str
            print(input_str)

        elif(layer==5):
            x = list(map(int, input("layer option for 5 : ").split()))
            for i in range(0,5):
                type_algo=list_of_algo[x[i]]
                encr_str=selection(type_algo)
                input_str=encr_str
            print(input_str)
        k=int(input("Do you want to continue ? enter 0 or 1 : "))
        if(k == 0):
            exit()
