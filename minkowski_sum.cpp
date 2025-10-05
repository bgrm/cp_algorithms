vector <Point> minkowskiSum(vector <Point>& A, vector <Point>& B)
{
	vector <Point> res;
	int i0 = bottomLeftInd(A), j0 = bottomLeftInd(B), i = i0, j = j0;
	do
	{
		res.pb(A[i] + B[j]);
		int ni = (i + 1) % A.size(), nj = (j + 1) % B.size();
		long long ilo = (A[ni] - A[i]) % (B[nj] - B[j]);
		if (ilo >= 0)	j = nj;
		if (ilo <= 0)	i = ni;
	}
	while (i != i0 or j != j0);
	return res;
}
