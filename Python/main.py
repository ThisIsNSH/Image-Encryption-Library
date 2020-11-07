# This python file will contain sample implementation of the cipher
import cipher
matrix=[ [ [ 196, 232, 84 ], [ 99, 253, 238 ],[ 128, 135, 2 ], [ 80, 144, 145 ] ],
         [ [ 215, 44, 211 ],[ 99, 209, 251 ], [ 196, 128, 255 ],[ 24, 43, 168 ] ],
         [ [ 22, 128, 20 ],[ 143, 38, 215 ],[ 68, 156, 104 ],[ 161, 51, 154 ] ],
        [ [ 150, 81, 140 ], [ 78, 126, 130 ],[ 253, 34, 9 ],[ 56, 66, 135 ] ],
        [ [ 191, 137, 175 ],[ 118, 143, 221 ],[ 13, 121, 212 ],[ 95, 103, 35 ] ] ]
grain=1
key="FirstnameLastnameEmailID@Something.com"
time=100000
pic=cipher.encrypt(grain,matrix,key,time)
print (pic)
pic2=cipher.decrypt(grain,pic,key,time)
print (pic2)
