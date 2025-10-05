namespace SuffixArray
{
	int temp[maxN], inds[maxN], C[maxN], T[maxN * 4], *R, *P;

	bool cmp(int i, int j)
	{
		while (P[i] == P[j]) i++, j++;
		return P[i] < P[j];
	}
	void brut(int n, int* T, int* res)
	{
		iota(res, res + n, 0);	P = T;
		sort(res, res + n, cmp);
	}
	int cntSort(int n, int* T, int k)
	{
		int m = 0;
		if (k == 0)
		{
			for (int i=0; i<n; i+=3)	temp[m++] = i;
			for (int i=1; i<n; i+=3)	temp[m++] = i;
		}
		else for (int i=2; i<n; i+=3)	temp[m++] = i;
		FORD(j, 2-k, -1)
		{
			FOR(i, 0, m)
			{
				int ind = temp[i];
				int v = j & k ? R[ind + 1] : T[ind + j];
				C[v]++;
			}
			for (int i = 1; C[i-1] != m; i++)	C[i] += C[i-1];
			FORD(i, m-1, -1)
			{
				int ind = temp[i];
				int v = j & k ? R[ind + 1] : T[ind + j];
				inds[--C[v]] = ind;
			}
			fill(C, C + n+1, 0);
			if (j != 0)	copy(inds, inds + m, temp);
		}
		return m;
	}
	inline bool differ(int* T, int i, int j)
	{	return T[i+2]^T[j+2] | T[i+1]^T[j+1] | T[i]^T[j];	}
	
	inline int newInd(int i, int p)
	{	return i / 3 + i % 3 * p;	}
	
	void calcRanks(int* sa, int n, int d=0)
	{	FOR(i, 0, n)	R[sa[i]] = i+d;	}
	bool cmpMerge(int i, int j)
	{
		for (; true; i++, j++)
		{
			if (P[i] != P[j])				return P[i] < P[j];
			if (i % 3 != 2 and j % 3 != 2)	return R[i] < R[j];
		}
	}
	void ks(int n, int* T, int* res)
	{
		if (n < 6)
		{	brut(n, T, res);	return;	}
		int m = cntSort(n, T, 0), p = (n + 2)/3 + 1, ctr = 2;
		int *A = T + n+2, *S = res + n/3;
		A[p-1] = 1, A[m+1] = A[m+2] = 0;
		FOR(i, 0, m)
		{
			if (i != 0 and differ(T, inds[i-1], inds[i]))	ctr++;
			A[newInd(inds[i], p)] = ctr;
		}
		ks(m + 1, A, S - 1);
		FOR(i, 0, m)
			S[i] = S[i] < p ? S[i] * 3 : (S[i] - p) * 3 + 1;
		calcRanks(S, m, 1); 		R[n] = 0;
		int k = cntSort(n, T, 1);	P = T;
		merge(S, S+m, inds, inds+k, res, cmpMerge);
	}
	void run(char* Tin, int n, int* sa, int* lcp, int* ranks)
	{	
		R = ranks;
		FOR(i, 0, n)	T[i] = (int)Tin[i] + 1;
		T[n] = T[n+1] = 0;
		n < 256 ? brut(n, T, sa) : ks(n, T, sa);
		calcRanks(sa, n);
		for (int i=0, q=0; i<n; i++)
		{
			if (R[i] == n - 1)	continue;
			int j = sa[R[i] + 1];
			while (T[i + q] == T[j + q])	q++;
			lcp[R[i]] = q;
			if (q != 0)	q--;
		}
	}
}
