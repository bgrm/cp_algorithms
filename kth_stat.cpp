struct Tree
{
    struct Node
	{
		pair <int, int> val;
		int FNLonLeft, FNLonRight, LNBonLeft, LNBonRight;
	}
	T[maxLogN + 1][maxN];
    pair <int, int> sorted[maxN];

    void fill(int d, int a, int b)
    {
        if (b - a == 1)
        {
            T[d][a].val = sorted[a];
            return;
        }
        int mid = (a + b) / 2, lowerCtr = 0, nolowCtr = 0;

        FOR(i, a, b)
        {
            Node& v = T[d - 1][i];

            v.FNLonLeft = a + lowerCtr;
            v.FNLonRight = mid + nolowCtr;

            v.val < sorted[mid] ? T[d][a + lowerCtr++].val = v.val : T[d][mid + nolowCtr++].val = v.val;

            v.LNBonLeft = a + lowerCtr - 1;
            v.LNBonRight = mid + nolowCtr - 1;
        }

        fill(d + 1, a, mid);
        fill(d + 1, mid, b);
    }

    void init(int* t, int n)
    {
        FOR(i, 0, n)
            T[0][i].val = sorted[i] = {t[i], i};
        sort(sorted, sorted + n);
        fill(1, 0, n);
    }
    int kthStat(int a, int b, int k)
    {
    	for (int d=0; a!=b; d++)
        {
            int am = T[d][b].LNBonLeft - T[d][a].FNLonLeft + 1;

            if (am < k)
            {
                k -= am;
                a = T[d][a].FNLonRight;
                b = T[d][b].LNBonRight;
            }
            else
            {
                a = T[d][a].FNLonLeft;
                b = T[d][b].LNBonLeft;
            }
        }
        return T[d][a].val.ft;
    }
};
