#include<bits/stdc++.h>
using namespace std;

int numberOfLeadingZeros(int x)
{
	int X;
	int base=2;
	int cnt=0;
	for(;;)
	{
		if(base>x) break;
		cnt++;
		base*=2;
	}
	return 32-cnt+1;
}
int MM()
{
	return -1;
}
int FNVHash1(long key)
{
    key = (~key) + (key << 18); // key = (key << 18) - key - 1;
    key = key ^ (key >> 31);
    key = key * 21; // key = (key + (key << 2)) + (key << 4);
    key = key ^ (key >> 11);
    key = key + (key << 6);
    key = key ^ (key >> 22);
    return key;
}

int intHash(int key) 
{
    key += ~(key << 15);
    key ^= (key >> 10);
    key += (key << 3);
    key ^= (key >> 6);
    key += ~(key << 11);
    key ^= (key >> 16);
    return key;
}
