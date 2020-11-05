#include<bits/stdc++.h>
#define SIZE 1000
typedef long long ll;
using namespace std;
char* base64Encoder(char input_str[], int len_str) 
{ 
	char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 
	char *res_str = (char *) malloc(SIZE * sizeof(char)); 
	
	int index, no_of_bits = 0, padding = 0, val = 0, count = 0, temp; 
	int i, j, k = 0; 

	for (i = 0; i < len_str; i += 3) 
		{ 
			val = 0, count = 0, no_of_bits = 0; 

			for (j = i; j < len_str && j <= i + 2; j++) 
			{ 
				val = val << 8;
				val = val | input_str[j]; 
				count++; 
			
			} 

			no_of_bits = count * 8; 
			padding = no_of_bits % 3; 
			while (no_of_bits != 0) 
			{ 
				if (no_of_bits >= 6) 
				{ 
					temp = no_of_bits - 6; 
					index = (val >> temp) & 63; 
					no_of_bits -= 6;		 
				} 
				else
				{ 
					temp = 6 - no_of_bits;  
					index = (val << temp) & 63; 
					no_of_bits = 0; 
				} 
				res_str[k++] = char_set[index]; 
			} 
	} 
	for (i = 1; i <= padding; i++) 
	{ 
		res_str[k++] = '='; 
	} 

	res_str[k] = '\0'; 

	return res_str; 

} 
int temp[5][4][3];
int* encrypt(int* matrix,char *key1,char *key2,int grain)
{
	char key[1000];
	ll row=5,column=4,isize;
	int len_str=0;
	for(; (*key1)!='\0';len_str++)
	{
		key[len_str]=*key1;
		key1++;
	}
	string base64;
	isize=row*column*3;
	int temp1[row][column][3];
	  	for ( int i = 0; i < row; i++ )
	  	{
	    	for ( int j = 0; j < column; j++ )
	    	{ 
	    	for(int layer=0;layer<3;layer++)
	    	{
	    	temp[i][j][layer]=*matrix;
	    	temp1[i][j][layer]=	temp[i][j][layer];
	    	matrix++;
	    	}}
	  	}
	base64=base64Encoder(key, len_str); 
	//column transposition
	int len1=base64.size();
	if(column<len1)
	base64=base64.substr(0,column);
	else if(column>len1)
	{
		string s=base64;
		for(int i=0;i<column/len1;i++)
		s=s+base64;
		base64=s.substr(0,column);
	}
	set <int, greater <int> > s1 ;
	set <int, greater <int> > :: iterator itr; 
	int int_max=column/grain;
	ll lenn=base64.size();
	int ch[lenn];
	for(int i=0;i<lenn;i++)
	{
		ch[i]=base64[i];	
	} 
	for(int i=0;i<lenn;i++)
	{
		stringstream sb1;
		for(int j=i;j<lenn;j++)
		{
			sb1<<ch[j];
		    int k;
		    sb1>>k;
		    if(k<int_max)
		    {
		    	if(s1.count(k)>0)
		    	break;
		    	else
		    	s1.insert(k);
			}
			else
			{
				while(k>=int_max||(k>=0 && (s1.count(k)>0)))
				k--;
				if(k>=0 && s1.count(k)==0)
				s1.insert(k);
				break;
			}
		}
		if(s1.size()==int_max)
		break;
	}
	for(int i=0;i<int_max;i++)
	{
		s1.insert(i);
	}
	int col=0;
	itr=s1.begin();
	for(int i=0;i<s1.size();i++)
	{
		int num=grain*(*(itr));
		for(int j=0;j<grain;j++)
		{
			for(int k=0;k<row;k++)
			{
				int px_red=temp[k][num+j][0];
				int px_green=temp[k][num+j][1];
				int px_blue=temp[k][num+j][2];
				
				temp1[k][col][0] = px_red;
                temp1[k][col][1] = px_green;
                temp1[k][col][2] = px_blue;
			}
			col++;
		}
		itr++;
	}
	
	//row transposition
	
	if(row<lenn)
	base64=base64.substr(0,row);
	else if(row>lenn)
	{
		string s=base64;
		for(int i=0;i<row/lenn;i++)
		s=s+base64;
		base64=s.substr(0,row);
	}
	
    set <int, greater <int> > s2 ;
	set <int, greater <int> > :: iterator itr1;  
	int_max=row/grain;
	lenn=base64.size();
	int ch1[lenn];
	for(int i=0;i<lenn;i++)
	{
		ch1[i]=base64[i];	
	} 
	for(int i=0;i<lenn;i++)
	{
		stringstream sb1;
		for(int j=i;j<lenn;j++)
		{
			sb1<<ch1[j];
		    int k;
		    sb1>>k;
		    if(k<int_max)
		    {
		    	if(s2.count(k)>0)
		    	break;
		    	else
		    	s2.insert(k);
			}
			else
			{
				while(k>=int_max||(k>=0 && s2.count(k)>0))
				k--;
				if(k>=0 && s2.count(k)==0)
				s2.insert(k);
				break;
			}
		}
		if(s2.size()==int_max)
		break;
	}
	for(int i=0;i<int_max;i++)
	{
		s2.insert(i);
	}
	int roww=0;
	itr1=s2.begin();
	for(int i=0;i<s2.size();i++)
	{
		int num=grain*(*(itr1));
		for(int j=0;j<grain;j++)
		{
			for(int k=0;k<column;k++)
			{
				int px_red=temp1[num+j][k][0];
				int px_green=temp1[num+j][k][1];
				int px_blue=temp1[num+j][k][2];
				
				temp[roww][k][0] = px_red;
                temp[roww][k][1] = px_green;
                temp[roww][k][2] = px_blue;
			}
			roww++;	
		}
		itr1++;
	}
  	return &temp[0][0][0];
	
}
int pic[5][4][3];
int* decrypt(int* matrix,char *key1,char *key2,ll grain)
{
	char key[1000];
	ll row=5,column=4,isize;
	int len_str=0;
	for(; (*key1)!='\0';len_str++)
	{
		key[len_str]=*key1;
		key1++;
	}
	string base64;
	isize=row*column*3;
	int pic1[row][column][3];
	for ( int i = 0; i < row; i++ )
	{
	    for ( int j = 0; j < column; j++ )
	    {
			for(int layer=0;layer<3;layer++)
			{
	    	pic[i][j][layer]=*matrix;
	    	pic1[i][j][layer]=	pic[i][j][layer];
	    	matrix++;
	    	}
		}
	}
	
	base64=base64Encoder(key, len_str); 
	
	//row transposition
	int len1=base64.size();
	if(row<len1)
	base64=base64.substr(0,row);
	else if(row>len1)
	{
		string s=base64;
		for(int i=0;i<row/len1;i++)
		s=s+base64;
		base64=s.substr(0,row);
	}
	set <int, greater <int> > s3 ;
	set <int, greater <int> > :: iterator itr2; 
	int int_max=row/grain;
	int lenn=base64.size();
	int ch2[lenn];
	for(int i=0;i<lenn;i++)
	{
		ch2[i]=base64[i];	
	} 
	for(int i=0;i<lenn;i++)
	{
		stringstream sb1;
		for(int j=i;j<lenn;j++)
		{
			sb1<<ch2[j];
		    int k;
		    sb1>>k;
		    if(k<int_max)
		    {
		    	if(s3.count(k)>0)
		    	break;
		    	else
		    	s3.insert(k);
			}
			else
			{
				while(k>=int_max||(k>=0 && s3.count(k)>0))
				k--;
				if(k>=0 && s3.count(k)==0)
				s3.insert(k);
				break;
			}
		}
		if(s3.size()==int_max)
		break;
	}
	for(int i=0;i<int_max;i++)
	{
		s3.insert(i);
	}
	int roww=0;
	itr2=s3.begin();
	for(int i=0;i<s3.size();i++)
	{
		int num=grain*(*(itr2));
		for(int j=0;j<grain;j++)
		{
			for(int k=0;k<row;k++)
			{
				int px_red=pic[roww][k][0];
				int px_green=pic[roww][k][1];
				int px_blue=pic[roww][k][2];
				
				pic1[num+j][k][0] = px_red;
                pic1[num+j][k][1] = px_green;
                pic1[num+j][k][2] = px_blue;
			}
			roww++;
		}
		itr2++;
	}
	
	//column transposition
	
	if(column<lenn)
	base64=base64.substr(0,column);
	else if(column>len1)
	{
		string s=base64;
		for(int i=0;i<column/lenn;i++)
		s=s+base64;
		base64=s.substr(0,column);
	}
	
	set <int, greater <int> > s4 ;
	set <int, greater <int> > :: iterator itr3; 
	int_max=column/grain;
	lenn=base64.size();
	int ch3[lenn];
	for(int i=0;i<lenn;i++)
	{
		ch3[i]=base64[i];	
	} 
	for(int i=0;i<lenn;i++)
	{
		stringstream sb1;
		for(int j=i;j<lenn;j++)
		{
			sb1<<ch3[j];
		    int k;
		    sb1>>k;
		    if(k<int_max)
		    {
		    	if(s4.count(k)>0)
		    	break;
		    	else
		    	s4.insert(k);
			}
			else
			{
				while(k>=int_max||(k>=0 && s4.count(k)>0))
				k--;
				if(k>=0 && s4.count(k)==0)
				s4.insert(k);
				break;
			}
		}
		if(s4.size()==int_max)
		break;
	}
	for(int i=0;i<int_max;i++)
	{
		s4.insert(i);
	}
	int col=0;
	itr3=s4.begin();
	for(int i=0;i<s4.size();i++)
	{
		int num=grain*(*(itr3));
		for(int j=0;j<grain;j++)
		{
			for(int k=0;k<row;k++)
			{
				int px_red=pic1[k][num+j][0];
				int px_green=pic1[k][num+j][1];
				int px_blue=pic1[k][num+j][2];
				
				pic[k][col][0] = px_red;
                pic[k][col][1] = px_green;
                pic[k][col][2] = px_blue;
			}
				col++;
		}
		itr3++;
	}
  	return &pic[0][0][0];
}



