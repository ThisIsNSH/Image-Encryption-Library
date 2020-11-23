import cipher
import numpy as np

matrix = np.random.rand(16,32,3)
# print(matrix)

grain=1

key="firstname.lastname@email.com-nameofuser-mobilenumber"

time=100000

pic = cipher.encrypt(matrix,key,time)
# print(pic)

pic2 = cipher.decrypt(pic,key,time)
# print(pic2)

print((matrix==pic2).all())