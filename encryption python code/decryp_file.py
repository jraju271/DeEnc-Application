import math
import string
string_mod = string.printable
letter = [x for x in string_mod[:]]

def cal(a):
    for i in range(len(letter)):
        if(letter[i]==a):
            return i
    return 0

            
def shift(text,s=13):

    cipher = ''
    for lot in text:
        x = cal(lot)
        #print(x,"\n")
        if(cal ==0):
            cipher+=lot
        else:
            cipher = cipher + (letter[(x-s)%100])
 
    return cipher



def atbash(message):
    cipher = ''
    for lot in message:
        x = cal(lot)
        #print(x,"\n")
        if(cal ==0):
            cipher+=lot
        else:
            cipher = cipher + (letter[len(letter)-x])
 
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
        raise TypeError("This program cannot",
                        "handle repeating words.")
  
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
        enc=shift(input_str,n)
    elif(algo=="Rot13"):
        enc=shift(input_str)
    elif(algo=="AtBash"):
        enc=atbash(input_str)
    elif(algo=="Route"):
        key=int(input("Enter key int value : "))
        enc=route(input_str, key)
    return enc

if __name__== "__main__":
    while(1):
        file = input("Enter file name:")
        f = open(file,"r")

        input_str=f.read()
        f.close()
        layer=int(input("Enter the no of layers:(1-5)"))
        list_of_algo=["Shift","Caesar","Rot13","AtBash","Route"]

        print("\n",list_of_algo,"[0,1,2,3,4]\n")
    
        x = list(map(int, input("layer option in order for layer {} : ".format(layer)).split()))
        for i in range(0,layer):
            type_algo=list_of_algo[x[i]]
            encr_str=selection(type_algo)
            input_str=encr_str
        print(input_str)
        f = open(file,"w",encoding="utf-8")

        input_str=f.write(input_str)
        f.close()

        k=int(input("Do you want to exit ? enter 0 or 1 : "))
        if(k == 0):
            exit()
