#include<bits/stdc++.h>
#define SIZE 1000
typedef long long ll;
using namespace std;

// Takes string to be encoded as input 
// and its length and returns encoded string 
char* base64Encoder(char input_str[], int len_str) 
{ 
	// Character set of base64 encoding scheme 
	char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"; 
	
	// Resultant string 
	char *res_str = (char *) malloc(SIZE * sizeof(char)); 
	
	int index, no_of_bits = 0, padding = 0, val = 0, count = 0, temp; 
	int i, j, k = 0; 
	
	// Loop takes 3 characters at a time from 
	// input_str and stores it in val 
	for (i = 0; i < len_str; i += 3) 
		{ 
			val = 0, count = 0, no_of_bits = 0; 

			for (j = i; j < len_str && j <= i + 2; j++) 
			{ 
				// binary data of input_str is stored in val 
				val = val << 8; 
				
				// (A + 0 = A) stores character in val 
				val = val | input_str[j]; 
				
				// calculates how many time loop 
				// ran if "MEN" -> 3 otherwise "ON" -> 2 
				count++; 
			
			} 

			no_of_bits = count * 8; 

			// calculates how many "=" to append after res_str. 
			padding = no_of_bits % 3; 

			// extracts all bits from val (6 at a time) 
			// and find the value of each block 
			while (no_of_bits != 0) 
			{ 
				// retrieve the value of each block 
				if (no_of_bits >= 6) 
				{ 
					temp = no_of_bits - 6; 
					
					// binary of 63 is (111111) f 
					index = (val >> temp) & 63; 
					no_of_bits -= 6;		 
				} 
				else
				{ 
					temp = 6 - no_of_bits; 
					
					// append zeros to right if bits are less than 6 
					index = (val << temp) & 63; 
					no_of_bits = 0; 
				} 
				res_str[k++] = char_set[index]; 
			} 
	} 

	// padding is done here 
	for (i = 1; i <= padding; i++) 
	{ 
		res_str[k++] = '='; 
	} 

	res_str[k] = '\0;'; 

	return res_str; 

} 
int* encrypt(ll grain)
{
	char key[1000];
	cout<<"Enter key";
	cin>>key;
	ll row,column,isize;
	string base64;
	cout<<"Enter row,column";
	cin>>row>>column;
	isize=row*column*3;
	ll temp[row][column][3],temp1[row][column][3],pic1[row][column][3];
	ifstream fin("c:\\test\\arr_data.txt");
	int layer=0;
	while(layer<3)
	{
	  	for ( int i = 0; i < row; i++ )
	  	{
	    	for ( int j = 0; j < column; j++ )
	    	{ 
	    	  fin >> temp[i][j][layer];
	    	}
	  	}
	  	layer++;
    }
    memcpy(temp1, temp, isize*sizeof(int));
    memcpy(pic1, temp, isize*sizeof(int));
	int len_str=strlen(key); 
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
	string ch[lenn];
	for(int i=0;i<lenn;i++)
	{
		ch[i]=base64[i];	
	} 
	for(int i=0;i<lenn;i++)
	{
		string sb1;
		for(int j=i;j<lenn;j++)
		{
			sb1.append(ch[j]);
		    stringstream geek(sb1); 
		    int k;
		    geek<<k;
		    if(k<int_max)
		    {
		    	if(s1.count(k))
		    	break;
		    	else
		    	s1.insert(k);
			}
			else
			{
				while(k>=int_max||(k>=0 && s1.count(k)))
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
				ll px_red=temp[k][num+j][0];
				ll px_green=temp[k][num+j][1];
				ll px_blue=temp[k][num+j][2];
				
				temp1[k][col][0] = px_red;
                temp1[k][col][1] = px_green;
                temp1[k][col][2] = px_blue;
			}
			col++;
		}
		itr++;
	}
	
	//row transposition
	
	if(row<len1)
	base64=base64.substr(0,row);
	else if(row>len1)
	{
		string s=base64;
		for(int i=0;i<row/len1;i++)
		s=s+base64;
		base64=s.substr(0,row);
	}
	
    set <int, greater <int> > s2 ;
	set <int, greater <int> > :: iterator itr1;  
	int_max=row/grain;
	lenn=base64.size();
	string ch1[lenn];
	for(int i=0;i<lenn;i++)
	{
		ch1[i]=base64[i];	
	} 
	for(int i=0;i<lenn;i++)
	{
		string sb1;
		for(int j=i;j<lenn;j++)
		{
		    sb1.append(ch1[j]);
		    stringstream geek(sb1);
		    int k;
		    geek<<k;
		    if(k<int_max)
		    {
		    	if(s2.count(k))
		    	break;
		    	else
		    	s2.insert(k);
			}
			else
			{
				while(k>=int_max||(k>=0 && s2.count(k)))
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
			for(int k=0;k<row;k++)
			{
				ll px_red=temp1[k][num+j][0];
				ll px_green=temp1[k][num+j][1];
				ll px_blue=temp1[k][num+j][2];
				
				pic1[k][roww][0] = px_red;
                pic1[k][roww][1] = px_green;
                pic1[k][roww][2] = px_blue;
			}
			roww++;
		}
		itr1++;
	}
	ofstream myfile ("encrypted.txt");
	if (myfile.is_open())
	  {
	   int x=0;
		while(x<3)
		{
		  	for ( int i = 0; i < row; i++ )
		  	{
		    	for ( int j = 0; j < column; j++ )
		    	{ 
		    	  myfile << pic1[row][column][x] << " " ;
		    	}
		  	}
		  	x++;
	    }
	    myfile.close();
	  }
  	else cout << "Unable to open file";
	
}

int* decrypt(ll grain)
{
	char key[1000];
	cout<<"Enter key";
	cin>>key;
	ll row,column,isize;
	string base64;
	cout<<"Enter row,column";
	cin>>row>>column;
	isize=row*column*3;
	ll temp[row][column][3],temp1[row][column][3],pic2[row][column][3];
	ifstream fin("c:\\test\\arr_data.txt");
	int layer=0;
	while(layer<3)
	{
	  	for ( int i = 0; i < row; i++ )
	  	{
	    	for ( int j = 0; j < column; j++ )
	    	{ 
	    	  fin >> temp[i][j][layer];
	    	}
	  	}
	  	layer++;
    }
    memcpy(temp1, temp, isize*sizeof(int));
    memcpy(pic2, temp, isize*sizeof(int));
    int len_str=strlen(key); 
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
	ll int_max=row/grain;
	ll lenn=base64.size();
	string ch2[lenn];
	for(int i=0;i<lenn;i++)
	{
		ch2[i]=base64[i];	
	} 
	for(int i=0;i<lenn;i++)
	{
		string sb1;
		for(int j=i;j<lenn;j++)
		{
			sb1.append(ch2[j]);
		    stringstream geek(sb1);
		    int k;
		    geek<<k;
		    if(k<int_max)
		    {
		    	if(s3.count(k))
		    	break;
		    	else
		    	s3.insert(k);
			}
			else
			{
				while(k>=int_max||(k>=0 && s3.count(k)))
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
				ll px_red=temp[roww][k][0];
				ll px_green=temp[roww][k][1];
				ll px_blue=temp[roww][k][2];
				
				temp1[num+j][k][0] = px_red;
                temp1[num+j][k][1] = px_green;
                temp1[num+j][k][2] = px_blue;
			}
			roww++;
		}
		itr2++;
	}
	
	//column transposition
	
	if(column<len1)
	base64=base64.substr(0,column);
	else if(column>len1)
	{
		string s=base64;
		for(int i=0;i<column/len1;i++)
		s=s+base64;
		base64=s.substr(0,column);
	}
	
	set <int, greater <int> > s4 ;
	set <int, greater <int> > :: iterator itr3; 
	int_max=column/grain;
	lenn=base64.size();
	ll ch3[lenn];
	for(int i=0;i<lenn;i++)
	{
		ch3[i]=base64[i];	
	} 
	for(int i=0;i<lenn;i++)
	{
		string sb1;
		for(int j=i;j<lenn;j++)
		{
			sb1.append(ch2[j]);
		    stringstream geek(sb1);
		    int k;
		    geek<<k;
		    if(k<int_max)
		    {
		    	if(s4.count(k))
		    	break;
		    	else
		    	s4.insert(k);
			}
			else
			{
				while(k>=int_max||(k>=0 && s4.count(k)))
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
				ll px_red=temp1[k][col][0];
				ll px_green=temp1[k][col][1];
				ll px_blue=temp1[k][col][2];
				
				pic2[k][num+j][0] = px_red;
                pic2[k][num+j][1] = px_green;
                pic2[k][num+j][2] = px_blue;
			}
			col++;
		}
		itr3++;
	}
	ofstream myfile ("decrypted.txt");
	if (myfile.is_open())
	  {
	   int x=0;
		while(x<3)
		{
		  	for ( int i = 0; i < row; i++ )
		  	{
		    	for ( int j = 0; j < column; j++ )
		    	{ 
		    	  myfile << pic2[row][column][x] << " " ;
		    	}
		  	}
		  	x++;
	    }
	    myfile.close();
	  }
  	else cout << "Unable to open file";
}

int main()
{
	ll grain;
	cout<<"Grain";
	cin>>grain;
	encrypt(grain);
	decrypt(grain);
}
