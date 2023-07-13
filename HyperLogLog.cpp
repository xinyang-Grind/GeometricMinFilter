#include<bits/stdc++.h>
#include "GeneralUtil.h"
using namespace std;
const int MAX_VALUE=2147483647;
class HyperLogLog
{
	public:
		int HLLSize;
		int m;
		int maxRegisterValue;
		double alpha;
		vector<vector<int> > HLLMatrix;
		
		HyperLogLog(int m,int size)
		{
			HLLSize=size;
			this->m=m;
			maxRegisterValue=(int)(pow(2,size)-1);
		//	HLLMatrix=new ;//ÉùÃ÷Ò»¸öbitset
			vector<int> T;
			for(int i=0;i<=size-1;i++) T.push_back(0); 
			for(int i=0;i<m;i++)
			{
				HLLMatrix.push_back(T);   //new BitSet(size)
			}
			alpha=getAlpha(m);
		}
		
		int getBitSetValue(vector<int> b) 
		{
    		int res = 0;
    		for (int i = 0; i < b.size(); i++) 
			{
      			if(b[i]) res += pow(2, i);
    		}
    		return res;
  		}

  		int getValue() 
		{
    		return getValue(HLLMatrix);
 		}
 		
  		int getValue(vector<vector<int> > sketch) 
		{
    		double result = 0.0;
    		int zeros = 0;
    		int len = sketch.size();
    		for (int i = 0; i < len; i++) 
			{
      			if (getBitSetValue(sketch[i]) == 0) zeros++;
      			result += pow(2, -1.0 * getBitSetValue(sketch[i]));
    		}
    		result = alpha * len * len / result;
    		if (result <= 5.0 / 2.0 * len) 
			{ // small flows
      			result = 1.0 * len * log(1.0 * len / max(zeros, 1));
    		} 
			else if (result > MAX_VALUE / 30.0) 
			{
      			result = -1.0 * MAX_VALUE * log(1 - result / MAX_VALUE);
    		}
    		return int(result);
  		}

  		void setBitSetValue(int index, int value) 
		{
    		int i = 0;
    		while (value != 0 && i < HLLSize)
			{
	      		if ((value & 1) != 0) 
				{
	        		HLLMatrix[index][i]=1;
	      		} 
				else 
				{
	        		HLLMatrix[index][i]=0;
	     	 	}
	      		value = value >> 1;
	      		i++;
    		}
  		}
  		
  		double getAlpha(int m) 
		{	
    		double a;
    		if (m == 16) 
			{
      			a = 0.673;
    		} 
			else if (m == 32) 
			{
      			a = 0.697;
    		} 
			else if (m == 64) 
			{
      			a = 0.709;
    		} 
			else 
			{
      			a = 0.7213 / (1 + 1.079 / m);
    		}
    		return a;
  		}
		
  		int getValueSegment(int flowID,vector<int> s, int w)
		{
    		int ms = s.size();
    		vector<vector<int> > sketch;
    		for (int j = 0; j < ms; j++) 
			{
      			int i = j * w + (intHash(FNVHash1(flowID) ^ s[j]) % w + w) % w;
      			sketch[j] = HLLMatrix[i];
    		}
    		int result = getValue(sketch);
    		return result;
  		}

  		void encodeSegment(long flowID, long elementID, vector<int> s, int w) 
		{
    		int ms = s.size();
    		int j = ((FNVHash1(flowID ^ elementID)) % ms + ms) % ms;
		    int k = (intHash(FNVHash1(flowID) ^ s[j]) % w + w) % w;
		
		    int i = j * w + k;
		    int hash_val = FNVHash1(elementID);
		
		    int leadingZeros = numberOfLeadingZeros(hash_val) + 1;
		    leadingZeros = min(leadingZeros, maxRegisterValue);
		    int pp = getBitSetValue(HLLMatrix[i]);
		    
		    if (pp < leadingZeros) 
			{
		      setBitSetValue(i, leadingZeros);
		    }
		}

  		HyperLogLog join(HyperLogLog hll, int w, int i) 
		{
    		for (int j = 0; j < w; j++) 
			{
      			if (getBitSetValue(HLLMatrix[i]) < getBitSetValue(hll.HLLMatrix[i * w + j]))
        		HLLMatrix[i] = hll.HLLMatrix[i * w + j];
    		}
  		}
};
