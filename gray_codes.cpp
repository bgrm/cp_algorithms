void GrayCodes(int n, int* T)
{
	int q = 1, b = -1;
	FOR(i, 0, 1<<n)
	{
		if (i+1 == q)	q *= 2, T[i] = ++b;
		else 			T[i] = T[i - q/2];
	}
};
