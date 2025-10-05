struct MinDist
{	Punkt temp1[maxN], temp2[maxN];
	int bins(int n, Punkt* T, int bord)
	{
		int begin = -1, end = n;
		while (end - begin > 1)
		{
			int mid = (begin + end) / 2;
			bord < T[mid].x ? end = mid : begin = mid;
		}
		return end;
	}
	bool cmp1(const Punkt& A, const Punkt& B)
	{	return A.x == B.x ? A.y > B.y : A.x < B.x;	}
	bool cmp2(const Punkt& A, const Punkt& B)
	{	return A.y == B.y ? A.x < B.x : A.y > B.y;	}
	
	long long go(int n, Punkt* T)
	{
		long long res = INF;
		if (n < 6)
		{
			FOR(i, 0, n) FOR(j, i+1, n)	remin(res, T[i].dist(T[j]));
			return res;
		}
		int n1 = n / 2, n2 = n - n1;
		Punkt* T1 = T, *T2 = T + n1;
		res = min(go(n1, T1), go(n2, T2));
		long long d = sqrt(res);
		long long x1 = T1[n1 - 1].x, x2 = T2[0].x;

		int begin = bins(n1, T1, (x1 + x2) / 2 - d);
		FOR(i, begin, n1)	temp1[i - begin] = T1[i];
		n1 -= begin;
		sort(temp1, temp1 + n1, cmp2);

		int end = bins(n2, T2, (x1 + x2 - 1) / 2 + d), k = 0;
		FOR(i, 0, end)	temp2[i] = T2[i];
		n2 = end;
		sort(temp2, temp2 + n2, cmp2);
		FOR(i, 0, n1)
		{
			while (k < n2 and temp2[k].y - temp1[i].y > d)	k++;
			FOR(j, 0, min(5, n2-k))
				res = min(res, temp1[i].dist(temp2[finger + j]));
		}
		return res;
	}
};
