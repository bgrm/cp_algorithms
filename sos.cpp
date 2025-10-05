void SOS(int* S, int n)
{	
	FOR(i, 0, n) FOR(m, 0, 1<<n)
		if (ithBit(m, i))
			S[m] += S[m ^ 1<<i];
} 
