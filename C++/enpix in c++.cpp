#include<bits/stdc++.h>
#define SIZE 1000
typedef long long ll;
using namespace std;
char* base64Encoder(char str[], int len)
{
	char set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	char *ostr = (char *) malloc(SIZE * sizeof(char));

	int index, x = 0, pad = 0, y = 0, cnt = 0, z;
	int i, j, k = 0;

	for (i = 0; i < len; i += 3)
		{
			y = 0, cnt = 0, x = 0;
			for (j = i; j < len && j <= i + 2; j++)
			{
				y = y << 8;
				y = y | str[j];
				cnt++;

			}
			x = cnt * 8;
			pad = x % 3;
			while (x != 0)
			{
				if (x >= 6)
				{
					z = x - 6;
					index = (y >> z) & 63;
					x -= 6;
				}
				else
				{
					z = 6 - x;
					index = (y << z) & 63;
					x = 0;
				}
				ostr[k++] = set[index];
			}
	}
	for (i = 1; i <= pad; i++)
	{
		ostr[k++] = '=';
	}
	
	ostr[k] = '\0';
	return ostr;
}

int* encrypt(int* matrix,char *key1,ll key2,int grain,int *size)
{
	int *hi=matrix;
	char key[1000];
	ll row=*size,column=*(size+1),isize;
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
	    	temp1[i][j][layer]=	*matrix;
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
	int x=3*lenn;
	int ch[x];
	int i=0;
	for( int j=0;j<lenn;i++,j++)
	{
		ch[i]=base64[j];
		if(ch[i]>9 && ch[i]<100)
		{
			ch[i+1]=ch[i]%10;
			ch[i]=ch[i]/10;
			i++;
	    }
		else if (ch[i]>99)
		{
			ch[i+2]=ch[i]%10;
			ch[i]=ch[i]/10;
			ch[i+1]=ch[i]%10;
			ch[i]=ch[i]/10;
			i=i+2;
		}
	}
	int count=i;
	int array[count];
	int index=0;
	for(int i=0;i<count;i++)
	{
		stringstream sb1;
		for(int j=i;j<count;j++)
		{
			sb1<<ch[j];
		    int k;
		    sb1>>k;
		    if(k<int_max)
		    {
		    	if(s1.count(k)>0)
		    	break;
		    	else
		    	{
		    	s1.insert(k);
		    	array[index]=k;
		    	index++;
			}}
			else
			{
				while(k>=int_max||(k>=0 && (s1.count(k)>0)))
				k--;
				if(k>=0 && s1.count(k)==0)
				{
				s1.insert(k);
				array[index]=k;
				index++;
			}
				break;
			}
		}
		if(s1.size()==int_max)
		break;
	}

	for(int i=0;i<int_max;i++)
	{
		if(s1.count(i)==0)
		{
		array[index]=i;
		index++;
		}
		s1.insert(i);
	}
	
	int col=0;
	itr=s1.begin();
	for(int i=0;i<index;i++)
	{
		int num=grain*array[i];
		for(int j=0;j<grain;j++)
		{
			for(int k=0;k<row;k++)
			{
				int px_red=*(hi+k*(3*column)+(num+j)*3+0);
				int px_green=*(hi+k*(3*column)+(num+j)*3+1);
				int px_blue=*(hi+k*(3*column)+(num+j)*3+2);

				temp1[k][col][0] = px_red;
                temp1[k][col][1] = px_green;
                temp1[k][col][2] = px_blue;
			}
			col++;
		}
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
    int ch1[x];
    i=0;
	for( int j=0;j<lenn;i++,j++)
	{
		ch1[i]=base64[j];
		if(ch1[i]>9&&ch1[i]<100)
		{
		ch1[i+1]=ch1[i]%10;
		ch1[i]=ch1[i]/10;
		i++;
	}
	else if (ch1[i]>99)
	{
		ch1[i+2]=ch1[i]%10;
		ch1[i]=ch1[i]/10;
		ch1[i+1]=ch1[i]%10;
		ch1[i]=ch1[i]/10;
		i=i+2;
	}
	}
	count=i;
	int array1[count];
	index=0;
	for(int i=0;i<count;i++)
	{
		stringstream sb1;
		for(int j=i;j<count;j++)
		{
			sb1<<ch1[j];
		    int k;
		    sb1>>k;
		    if(k<int_max)
		    {
		    	if(s2.count(k)>0)
		    	break;
		    	else
		    	{
				array1[index]=k;
		    	index++;
		    	s2.insert(k);
		    }
			}
			else
			{
				while(k>=int_max||(k>=0 && s2.count(k)>0))
				k--;
				if(k>=0 && s2.count(k)==0)
				{
				s2.insert(k);
				array1[index]=k;
		    	index++;
			}
				break;
			}
		}
		if(s2.size()==int_max)
		break;
	}
	for(int i=0;i<int_max;i++)
	{
		if(s2.count(i)==0)
		{
		array1[index]=i;
		index++;
	}
		s2.insert(i);
	}
	
	int roww=0;
	itr1=s2.begin();
	for(int i=0;i<index;i++)
	{
		int num=grain*array1[i];
		for(int j=0;j<grain;j++)
		{
			for(int k=0;k<column;k++)
			{
				int px_red=temp1[num+j][k][0];
				int px_green=temp1[num+j][k][1];
				int px_blue=temp1[num+j][k][2];
				
				*(hi+roww*(3*column)+(k)*3+0)=px_red;
				*(hi+roww*(3*column)+(k)*3+1)=px_green;
				*(hi+roww*(3*column)+(k)*3+2)=px_blue;
			}
			roww++;
		}
	}
	
  	return hi;

}

int* decrypt(int* matrix,char *key1,ll key2,ll grain,int *size)
{
	char key[1000];
	ll row=*size,column=*(size+1),isize;
	int *hi=matrix;
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
	    	pic1[i][j][layer]=*matrix;
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
	ll lenn=base64.size();
	int x=3*lenn;
	int ch[x];
	int i=0;
	for( int j=0;j<lenn;i++,j++)
	{
		ch[i]=base64[j];
		if(ch[i]>9 && ch[i]<100)
		{
		ch[i+1]=ch[i]%10;
		ch[i]=ch[i]/10;
		i++;
	}
	else if (ch[i]>99)
	{
		ch[i+2]=ch[i]%10;
		ch[i]=ch[i]/10;
		ch[i+1]=ch[i]%10;
		ch[i]=ch[i]/10;
		i=i+2;
	}
	}
	int count=i;
 	int array[count];
	int index=0;
	for(int i=0;i<count;i++)
	{
		stringstream sb1;
		for(int j=i;j<count;j++)
		{
			sb1<<ch[j];
		    int k;
		    sb1>>k;
		    if(k<int_max)
		    {
		    	if(s3.count(k)>0)
		    	break;
		    	else
		    	{
		    	s3.insert(k);
				array[index]=k;
		    	index++;
		    }
			}
			else
			{
				while(k>=int_max||(k>=0 && (s3.count(k)>0)))
				k--;
				if(k>=0 && s3.count(k)==0)
				{
				s3.insert(k);
				array[index]=k;
		    	index++;
			}
				break;
			}
		}
		if(s3.size()==int_max)
		break;
	}
	for(int i=0;i<int_max;i++)
	{
		if(s3.count(i)==0)
		{
		array[index]=i;
		index++;
	}
		s3.insert(i);
	}

	int roww=0;
	itr2=s3.begin();
	for(int i=0;i<index;i++)
	{
		int num=grain*array[i];
		for(int j=0;j<grain;j++)
		{
			for(int k=0;k<column;k++)
			{
				int px_red=*(hi+roww*(3*column)+(k)*3+0);
				int px_green=*(hi+roww*(3*column)+(k)*3+1);
				int px_blue=*(hi+roww*(3*column)+(k)*3+2);

				pic1[num+j][k][0] = px_red;
                pic1[num+j][k][1] = px_green;
                pic1[num+j][k][2] = px_blue;
			}
			roww++;
		}
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
	x=3*lenn;
	int ch1[x];
	i=0;
	for(int j=0;j<lenn;i++,j++)
	{
		ch1[i]=base64[j];
		if(ch1[i]>9&&ch1[i]<100)
		{
		ch1[i+1]=ch1[i]%10;
		ch1[i]=ch1[i]/10;
		i++;
	}
	else if (ch1[i]>99)
	{
		ch1[i+2]=ch1[i]%10;
		ch1[i]=ch1[i]/10;
		ch1[i+1]=ch1[i]%10;
		ch1[i]=ch1[i]/10;
		i=i+2;
	}
	}
	count=i;
	int array1[count];
	index=0;
	for(int i=0;i<count;i++)
	{
		stringstream sb1;
		for(int j=i;j<count;j++)
		{
			sb1<<ch1[j];
		    int k;
		    sb1>>k;
		    if(k<int_max)
		    {
		    	if(s4.count(k)>0)
		    	break;
		    	else
		    	{
				array1[index]=k;
		    	index++;
		    	s4.insert(k);
		    }
			}
			else
			{
				while(k>=int_max||(k>=0 && s4.count(k)>0))
				k--;
				if(k>=0 && s4.count(k)==0)
				{
				array1[index]=k;
		    	index++;
				s4.insert(k);
			}
				break;
			}
		}
		if(s4.size()==int_max)
		break;
	}
	for(int i=0;i<int_max;i++)
	{
		if(s4.count(i)==0)
		{
		array1[index]=i;
		index++;
	}
		s4.insert(i);
	}
	
	int col=0;
	itr3=s4.begin();
	for(int i=0;i<index;i++)
	{
		int num=grain*array1[i];
		for(int j=0;j<grain;j++)
		{
			for(int k=0;k<row;k++)
			{
				int px_red=pic1[k][col][0];
				int px_green=pic1[k][col][1];
				int px_blue=pic1[k][col][2];
				
				*(hi+k*(3*column)+(num+j)*3+0)= px_red;
				*(hi+k*(3*column)+(num+j)*3+1)= px_green;
				*(hi+k*(3*column)+(num+j)*3+2)= px_blue;
			}
				col++;
		}
	}
  	return hi;
}



