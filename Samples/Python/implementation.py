import enpix
import numpy as np

matrix = np.random.rand(341,763,3)
# print(matrix)

key="firstname.lastname@email.com-nameofuser-mobilenumber"

time=1000000

pic = enpix.encrypt(matrix,key,time)
# print(pic)

pic2 = enpix.decrypt(pic,key,time)
# print(pic2)

print((matrix==pic2).all())