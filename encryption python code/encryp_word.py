import math
import string
string_mod = string.printable
letter = [x for x in string_mod[:]]


def cal(a):
    for i in range(len(letter)):
        if(letter[i]==a):
            return i
    return 0
        
def shift(text,s =13):

    cipher = ''
    for lot in text:
        x = cal(lot)
        #print(x,"\n")
        if(cal ==0):
            cipher+=lot
        else:
            cipher = cipher + (letter[(x+s)%100])
 
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

def route(msg, key):
    cipher = ""
  
    # track key indices
    k_indx = 0
  
    msg_len = float(len(msg))
    msg_lst = list(msg)
  
    # calculate column of the matrix
    col = key
      
    # calculate maximum row of the matrix
    row = int(math.ceil(msg_len / col))
  
    # add the padding character '_' in empty
    # the empty cell of the matix 
    fill_null = int((row * col) - msg_len)
    msg_lst.extend('_' * fill_null)
  
    # create Matrix and insert message and 
    # padding characters row-wise 
    matrix = [msg_lst[i: i + col] 
              for i in range(0, len(msg_lst), col)]
  
    # read matrix column-wise using key
    for i in range(col):
        curr_idx = i
        cipher += ''.join([row[curr_idx]         # for list comprehension see the first part after the second part
                          for row in matrix])
  
    return cipher




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
        #print(letter)
        #$file = input("Enter file name:")
        #f = open(file,"r")

        #input_str=f.read()
        #f.close()
        word_list=input("Enter 20 words with space separated:").split(" ")
        #word_list = list(int(i) for i in input("Enter the list items separated by space ").strip().split())
        encrypted_wlist=[]

        #input_str=input("Enter the string : ")
        
        list_of_algo=["Shift","Caesar","Rot13","AtBash","Route"]
        for i in range(0,len(word_list)):
            input_str=word_list[i]
            layer=int(input("Enter the no of layers:(1-5)"))
            print("\n",list_of_algo,"[0,1,2,3,4]\n")
            x = list(map(int, input("layer option in respective order layer {} : ".format(layer)).split()))
            for j in range(0,layer):
                type_algo=list_of_algo[x[j]]
                encr_str=selection(type_algo)
                input_str=encr_str
            encrypted_wlist.append(input_str)

        print(encrypted_wlist)
        #f = open(file,"w")

        #input_str=f.write(input_str)
        #f.close()


        k=int(input("Do you want to exit ? enter 0 or 1 : "))
        if(k == 0):
            exit()
