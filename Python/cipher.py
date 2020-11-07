import numpy as np
from Crypto.Cipher import AES
import base64

def encrypt(grain, image, key, time):

    # row X column X 3

    temp = np.array(image)
    temp1 = temp.copy()
    pic1 = temp.copy()

    base64 = base64.b64encode(AES.new(key, AES.MODE_EAX))

    # column transposition

    len1 = base64.len()
    len2 = temp.shape[1]

    if (len2 < len1):
        base64 = base64[0: len2]
    elif (len2 > len1):
        s = base64
        for i in range(0,len2/len1):
            s += base64
        base64 = s[0, len2]
    

    hash_set = {}
    int_max = temp.shape[1] / grain

    ch=[]
    b="" 
    for i in base64:
        b=b+str(ord(i))
    chl=list(b)
    for i in chl:
        ch.append(int(i))
    for i in range(0,ch.len()):
        sb1 = ""
        for j in range(i,ch.len()):
            sb1 += ch[j]
            k = int(sb1)
            if (k < int_max):
                if (k in hash_set):
                    break
                else:
                    hash_set.add(k)
            else:
                while (k >= int_max or (k >= 0 and (k in hash_set))):
                    k -= 1
                if (k>=0 and k not in hash_set) :
                    hash_set.add(k)
                break

        if (hash_set.len() == int_max):
            break
        

    for i in range(0, temp.shape[1] / grain):
        hash_set.add(i)

    col = 0
    for k in hash_set:
        num = k * grain
        for i in range(0, grain):
            for j in range(0, temp.shape[0]):
                px_red = temp[j][num + i][0]
                px_green = temp[j][num + i][1]
                px_blue = temp[j][num + i][2]

                temp1[j][col][0] = px_red
                temp1[j][col][1] = px_green
                temp1[j][col][2] = px_blue
            col+=1

    # row transposition

    len1 = base64.len()
    len2 = temp.shape[0]

    if (len2 < len1):
        base64 = base64[0: len2]
    elif (len2 > len1):
        s = base64
        for i in range(0,len2/len1):
            s += base64
        base64 = s[0, len2]

    hash_set = {}
    int_max = temp.shape[0] / grain

    ch=[]
    b="" 
    for i in base64:
        b=b+str(ord(i))
    chl=list(b)
    for i in chl:
        ch.append(int(i))

    for i in range(0,ch.len()):
        sb1 = ""
        for j in range(i,ch.len()):
            sb1 += ch[j]
            k = int(sb1)
            if (k < int_max):
                if (k in hash_set):
                    break
                else:
                    hash_set.add(k)
            else:
                while (k >= int_max or (k >= 0 and (k in hash_set))):
                    k -= 1
                if (k>=0 and k not in hash_set) :
                    hash_set.add(k)
                break

        if (hash_set.len() == int_max):
            break
        

    for i in range(0, temp.shape[0] / grain):
        hash_set.add(i)

    row = 0
    for k in hash_set:
        num = k * grain
        for i in range(0, grain):
            for j in range(0, temp.shape[1]):
                px_red = temp1[num + i][j][0]
                px_green = temp1[num + i][j][1]
                px_blue = temp1[num + i][j][2]

                pic1[row][j][0] = px_red
                pic1[row][j][1] = px_green
                pic1[row][j][2] = px_blue

            row+=1

    return pic1

def decrypt(grain, image, key,time):

    # row X column X 3

    temp = np.array(image)
    temp1 = temp.copy()
    pic2 = temp.copy()

    base64 = base64.b64encode(AES.new(key, AES.MODE_EAX))

# row transposition

    len1 = base64.len()
    len2 = temp.shape[0]

    if (len2 < len1):
        base64 = base64[0: len2]
    elif (len2 > len1):
        s = base64
        for i in range(0,len2/len1):
            s += base64
        base64 = s[0, len2]

    hash_set = {}
    int_max = temp.shape[0] / grain

    ch=[]
    b="" 
    for i in base64:
        b=b+str(ord(i))
    chl=list(b)
    for i in chl:
        ch.append(int(i))

    for i in range(0,ch.len()):
        sb1 = ""
        for j in range(i,ch.len()):
            sb1 += ch[j]
            k = int(sb1)
            if (k < int_max):
                if (k in hash_set):
                    break
                else:
                    hash_set.add(k)
            else:
                while (k >= int_max or (k >= 0 and (k in hash_set))):
                    k -= 1
                if (k>=0 and k not in hash_set) :
                    hash_set.add(k)
                break

        if (hash_set.len() == int_max):
            break
        

    for i in range(0, temp.shape[0] / grain):
        hash_set.add(i)

    row = 0
    for k in hash_set:
        num = k * grain
        for i in range(0, grain):
            for j in range(0, temp.shape[1]):
                px_red = temp[row][j][0]
                px_green = temp[row][j][1]
                px_blue = temp[row][j][2]

                temp1[num + i][j][0] = px_red
                temp1[num + i][j][1] = px_green
                temp1[num + i][j][2] = px_blue

            row+=1

    # column transposition

    len1 = base64.len()
    len2 = temp.shape[1]

    if (len2 < len1):
        base64 = base64[0: len2]
    elif (len2 > len1):
        s = base64
        for i in range(0,len2/len1):
            s += base64
        base64 = s[0, len2]
    

    hash_set = {}
    int_max = temp.shape[1] / grain

    ch=[]
    b="" 
    for i in base64:
        b=b+str(ord(i))
    chl=list(b)
    for i in chl:
        ch.append(int(i)) 

    for i in range(0,ch.len()):
        sb1 = ""
        for j in range(i,ch.len()):
            sb1 += ch[j]
            k = int(sb1)
            if (k < int_max):
                if (k in hash_set):
                    break
                else:
                    hash_set.add(k)
            else:
                while (k >= int_max or (k >= 0 and (k in hash_set))):
                    k -= 1
                if (k>=0 and k not in hash_set) :
                    hash_set.add(k)
                break

        if (hash_set.len() == int_max):
            break
        

    for i in range(0, temp.shape[1] / grain):
        hash_set.add(i)

    col = 0
    for k in hash_set:
        num = k * grain
        for i in range(0, grain):
            for j in range(0, temp.shape[0]):
                px_red = temp1[j][col][0]
                px_green = temp1[j][col][1]
                px_blue = temp1[j][col][2]

                pic2[j][num + i][0] = px_red
                pic2[j][num + i][1] = px_green
                pic2[j][num + i][2] = px_blue
            col+=1

    return pic2