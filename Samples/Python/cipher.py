import numpy as np
import hashlib 
import time 

def encrypt(image, key, duration):

    # row X column X 3
    temp = np.array(image)
    temp1 = temp.copy()
    pic1 = temp.copy()

    duration = int(round(time.time() * 1000)) / duration
    
    # key generation 
    base64 = hashlib.sha256(key+str(duration).encode()).hexdigest().upper()
    len1 = (temp.shape[1]//16)*16
    column_key = [x for x in range(0,temp.shape[1])]

    counter = 0
    for i in range(0,len1, 16):
        temp_key = base64[counter:counter+16] + "1A0B95C4D37286EF"
        temp_set = []
        temp_index = 0

        # fisher-yates algo
        for j in range(i,i+16): 

            # pick only unique 0-9A-F values 
            while temp_key[temp_index] in temp_set:
                temp_index+=1
            temp_set.append(temp_key[temp_index])
            
            # hex to decimal 
            index = int(temp_key[temp_index], 16)
            
            # swap
            column_key[j],column_key[i+index] = column_key[i+index],column_key[j] 

        counter += 16
        if counter == 256:
            counter = 0
            base64 = hashlib.sha256((base64).encode()).hexdigest().upper()

    # column transposition
    col = 0
    for k in column_key:
        for j in range(0, temp.shape[0]):
            temp1[j][col] = temp[j][k]
        col+=1

    # key generation 
    base64 = hashlib.sha256(key+str(duration).encode()).hexdigest().upper()
    len1 = (temp.shape[0]//16)*16
    row_key = [x for x in range(0,temp.shape[0])]

    counter = 0
    for i in range(0,len1, 16):
        temp_key = base64[counter:counter+16] + "1A0B95C4D37286EF"
        temp_set = []
        temp_index = 0

        # fisher-yates algo
        for j in range(i,i+16): 

            # pick only unique 0-9A-F values 
            while temp_key[temp_index] in temp_set:
                temp_index+=1
            temp_set.append(temp_key[temp_index])
            
            # hex to decimal 
            index = int(temp_key[temp_index], 16)
            
            # swap
            row_key[j],row_key[i+index] = row_key[i+index],row_key[j] 

        counter += 16
        if counter == 256:
            counter = 0
            base64 = hashlib.sha256((base64).encode()).hexdigest().upper()

    # row transposition
    row = 0
    for k in row_key:
        for j in range(0, temp.shape[1]):
            pic1[row][j] = temp1[k][j]
        row+=1

    return pic1

def decrypt(image, key, duration):

    # row X column X 3
    temp = np.array(image)
    temp1 = temp.copy()
    pic1 = temp.copy()

    duration = int(round(time.time() * 1000)) / duration

    # key generation 
    base64 = hashlib.sha256(key+str(duration).encode()).hexdigest().upper()
    len1 = (temp.shape[0]//16)*16
    row_key = [x for x in range(0,temp.shape[0])]

    counter = 0
    for i in range(0,len1, 16):
        temp_key = base64[counter:counter+16] + "1A0B95C4D37286EF"
        temp_set = []
        temp_index = 0

        # fisher-yates algo
        for j in range(i,i+16): 

            # pick only unique 0-9A-F values 
            while temp_key[temp_index] in temp_set:
                temp_index+=1
            temp_set.append(temp_key[temp_index])
            
            # hex to decimal 
            index = int(temp_key[temp_index], 16)
            
            # swap
            row_key[j],row_key[i+index] = row_key[i+index],row_key[j] 

        counter += 16
        if counter == 256:
            counter = 0
            base64 = hashlib.sha256((base64).encode()).hexdigest().upper()

    # row transposition
    row = 0
    for k in row_key:
        for j in range(0, temp.shape[1]):
            temp1[k][j] = temp[row][j]
        row+=1

    # key generation 
    base64 = hashlib.sha256(key+str(duration).encode()).hexdigest().upper()
    len1 = (temp.shape[1]//16)*16
    column_key = [x for x in range(0,temp.shape[1])]

    counter = 0
    for i in range(0,len1, 16):
        temp_key = base64[counter:counter+16] + "1A0B95C4D37286EF"
        temp_set = []
        temp_index = 0

        # fisher-yates algo
        for j in range(i,i+16): 

            # pick only unique 0-9A-F values 
            while temp_key[temp_index] in temp_set:
                temp_index+=1
            temp_set.append(temp_key[temp_index])
            
            # hex to decimal 
            index = int(temp_key[temp_index], 16)
            
            # swap
            column_key[j],column_key[i+index] = column_key[i+index],column_key[j] 

        counter += 16
        if counter == 256:
            counter = 0
            base64 = hashlib.sha256((base64).encode()).hexdigest().upper()

    # column transposition
    col = 0
    for k in column_key:
        for j in range(0, temp.shape[0]):
            pic1[j][k] = temp1[j][col]
        col+=1

    return pic1