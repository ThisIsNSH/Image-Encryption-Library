#include<bits/stdc++.h>
#include "enpix in c++.cpp"
#define SIZE 1000
typedef long long ll;
using namespace std;

int main()
{
    int matrix[5][5][3]={{{20,100,0},{25,10,6},{30 ,20 ,25},{44,50,30},{57,60,150}},
	                   {{10,40,70},{12,0,25},{100,10,77},{120,76,0},{87.20,66}},
					   {{7,12,100},{44,13,44},{28,77,91},{140,85,99},{0,100,0}},
					   {{0,60,210},{1,10,11},{10,37,45},{70,100,80},{5,40,10}},
					   {{10,100,110},{20,10,120},{30,66,44},{40,200,240},{0,30,70}}};	
	int grain;
	char key1[1000],key2[1000];
	cout<<"Enter Grain Size";
	cin>>grain;
	cout<<"Enter key1 and key2"<<"\n";
	cin>>key1;
	cin>>key2;
	int *pic1=encrypt(&matrix[0][0][0],key1,key2,grain);
	int *pic2=decrypt(&matrix[0][0][0],key1,key2,grain);
	for(int x=0;x<5;x++)
	{
		for ( int i = 0; i < 5; i++ )
		{
		    for ( int j = 0; j < 3; j++ )
		    { 
		    	cout << *pic1<< " " ;
		    	pic1++;
		   	}
		   	cout<<"\n";
		}
    }
    cout<<"\n";
    for(int x=0;x<5;x++)
	{
		for ( int i = 0; i < 5; i++ )
		{
		    for ( int j = 0; j < 3; j++ )
		    { 
		    	cout << *pic2<< " " ;
		    	pic2++;
		   	}
		   	cout<<"\n";
		}
    }
}
