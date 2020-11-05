#include<bits/stdc++.h>
#include "enpix in c++.cpp"
#define SIZE 1000
typedef long long ll;
using namespace std;

int main()
{
    int matrix[5][4][3]={ { { 196, 232, 84 },{ 99, 253, 238 },{ 128, 135, 2 },{ 80, 144, 145 } },
						{ { 215, 44, 211 },{ 99, 209, 251 }, { 196, 128, 255 },{ 24, 43, 168 } },
  						{ { 22, 128, 20 },{ 143, 38, 215 },{ 68, 156, 104 },{ 161, 51, 154 } },
  						{ { 150, 81, 140 }, { 78, 126, 130 },{ 253, 34, 9 },{ 56, 66, 135 } },
  						{ { 191, 137, 175 },{ 118, 143, 221 },{ 13, 121, 212 },{ 95, 103, 35 } } };
	int *x=&matrix[0][0][0];
	cout<<*(x+45);			   
	int grain;
	char key1[1000],key2[1000];
	cout<<"Enter Grain Size";
	cin>>grain;
	cout<<"Enter key1 and key2"<<"\n";
	cin>>key1;
	cin>>key2;
	int *image1=encrypt(&matrix[0][0][0],key1,key2,grain);
	int *image2=decrypt(image1,key1,key2,grain);
	for(int x=0;x<5;x++)
	{
		for ( int i = 0; i < 4; i++ )
		{
		    for ( int j = 0; j < 3; j++ )
		    { 
		    	cout << *image1<< " " ;
		    	image1++;
		   	}
		   	cout<<"\n";
		}
    }
    cout<<"\n";
    for(int x=0;x<5;x++)
	{
		for ( int i = 0; i < 4; i++ )
		{
		    for ( int j = 0; j < 3; j++ )
		    { 
		    	cout << *image2<< " " ;
		    	image2++;
		   	}
		   	cout<<"\n";
		}
    }
}
