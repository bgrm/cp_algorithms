void cntZ(char* T, int n, int* Z)
{
	int a = 0, b = 0;
	FOR(i, 1, n)
	{
		if (i <= b)
			Z[i] = min(Z[i - a], b - i + 1);
		while (i + Z[i]<n and T[i + Z[i]] == T[Z[i]])
			Z[i]++;
		if (i + Z[i] - 1 > b)
			a = i, b = i + Z[i] - 1;
	}
}

