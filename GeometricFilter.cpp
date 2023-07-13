#include<bits/stdc++.h>
#include"GeneralUtil.h"
using namespace std;

class GeometricFilter 
{
	public:
		
   	int RegisterSize; // unit size for each register
  	int m; // the number of registers in the Filter
   	int GeometrichashBits;
   	int mGeometric;
   	int maxRegisterValue;
	vector<bitset<32> >  RegisterArray;
	
	//初始化
	GeometricFilter(int m, int size, int Mbit, int num)
	{
	    RegisterSize = size;
	    this->m = m;
	    this->GeometrichashBits = Mbit;
	    this->mGeometric = num;
	    maxRegisterValue = (int) (pow(2, size) - 1);
	    for (int i = 0; i < m; i++) 
		{
	      RegisterArray.push_back(0);
	    }
    }

	//求出bitset的值 
   	int getBitSetValue(bitset<32>b) 
	{
    	int res = 0;
    	for (int i = 0; i < 32; i++) 
		{
      		if(b[i]) res += pow(2, i);
    	}
    	return res;
  	}

	//设置bitset的值 
   	void setBitSetValue(int index, int value) 
	{
    	int i = 0;
    	while (value != 0 && i < RegisterSize)
		{
      		if ((value & 1) != 0) 
			{
        		RegisterArray[index][i]=1;
      		} 	
			else 
			{
        		RegisterArray[index][i]=0;
      		}
      		value = value >> 1;
      		i++;
    	}
  	}

   	vector<bitset<32> > getestimate(long flowID, long elementID, int s[], int w)
	{
    //	int ms = s.size();
		vector<bitset<32> >  res
    	for(int i=0;i<mGeometric;i++) res[i].push_back(0);
    	for (int j = 0; j < mGeometric; j++) 
		{
      		w = this->m;
      		int k = (intHash(FNVHash1(flowID) ^ s[j]) % w + w) % w;
      		res[j] = getBitSetValue(RegisterArray[k]);
      		elementID = FNVHash1(elementID);
    	}
    	return res;
  	}

   	int getleadingzeros(int h[], int s[])
	{
    	int res = 1;
    	while (res < maxRegisterValue) 
		{
	      	int hh = 0;
	      	for (int l = 0; l < 10000; l++) 
			{
				if(h[l]==0) break;
	        	h[l] = intHash(h[l] ^ s[l]);
	        	if (l == 0) hh = h[l];
	        	else hh &= h[l];
	      	}
      		int cur = numberOfLeadingZeros(hh);
      		res += cur;
      		if (cur < 32) break;
    	}
    	return res;
  	}

   	void encodefilter(long flowID, long elementID,int s[], int s1[], int w) 
	{
    	for (int j = 0; j < mGeometric; j++) 
		{
      		w = this->m;
      		int k = (intHash(FNVHash1(flowID) ^ s[j]) % w + w) % w;
		    int hash_val = intHash(FNVHash1(elementID) ^ s[j]);
		    int Max=0;
		    for(int ok=0;ok<110000;ok++) if(!s1[ok]) {Max=ok;break;}
		    int hashvalue[Max];
      		for (int l = 0; l < Max; l++) 
			{
        		hashvalue[l] = hash_val;
      		}
		    int leadingZeros = getleadingzeros(hashvalue, s1);
		    leadingZeros = min(leadingZeros, maxRegisterValue);
		    int pp = getBitSetValue(RegisterArray[k]);
      		if (pp < leadingZeros) 
			{
        		setBitSetValue(k, leadingZeros);
      		}
    	}
  	}
};
