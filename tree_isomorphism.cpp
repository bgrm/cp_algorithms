struct Tree_isomorphism
{
    vector <int> bucket[maxN], presLetters[maxN],
						seqsOfLen[maxN], emptys;
    int temp[maxN][2];
    void posSort(vector <int>* T, int n, vector <int>& res)
    {
        int maxLen = 0, tempSize = 0, M = n;
        FOR(i, 0, n)
        {
            FOR(j, 0, T[i].size())
            {
                temp[tempSize][0] = j;
                temp[tempSize++][1] = T[i][j];
                M = max(M, T[i][j]);
            }
            int len = T[i].size() - 1;
            maxLen = max(len, maxLen);
            len == -1 ? emptys.pb(i) : seqsOfLen[len].pb(i);
        }
        M = max(M, maxLen);
        for (int s=1; s>=0; s--)
        {
            FOR(i, 0, tempSize)
            {
                int key = temp[i][s];
                int val = temp[i][s ^ 1];
                bucket[key].pb(val);
            }
            for (int i=0, k=0; i<=M; i++)
            {
                for (int a : bucket[i])
                {
                    temp[k][s] = i;
                    temp[k++][s ^ 1] = a;
                }
                bucket[i].resize(0);
            }
        }
        FOR(i, 0, tempSize)
            if (i == 0 or temp[i][0] != temp[i - 1][0] or
								temp[i][1] != temp[i - 1][1])
                presLetters[temp[i][0]].pb(temp[i][1]);
        res.resize(0);
        for (int len=maxLen; len>=0; len--)
        {
            for (int id : seqsOfLen[len])	bucket[T[id][len]].pb(id);  
            for (int id : res)				bucket[T[id][len]].pb(id);
            res.resize(0);
            for (int letter : presLetters[len])
            {
                res.insert(res.end(), ALL(bucket[letter]));
                bucket[letter].resize(0);
            } 
            presLetters[len].resize(0);
            seqsOfLen[len].resize(0);
        }
        res.insert(res.begin(), ALL(emptys));
        emptys.resize(0);
    }
    int id[2][maxN], sz[maxN];
    vector <int> L[2][maxN], vsOnDist[2][maxN], tempSeq[maxN], order0, order1, *G; 
    void clear(int n)
    {
        FOR(i, 0, n+1) FOR(s, 0, 2)
            L[s][i].resize(0), vsOnDist[s][i].resize(0);
        order0.resize(0); order1.resize(0);
    }
    void newCentroid(int a, int u, int v, vector <int>* g, bool ins)
    {
        int tab[2]; tab[0] = u, tab[1] = v;
        FOR(d, 0, 2)
        {
            int curr = tab[d], other = tab[d ^ 1];
            for (int& w : g[curr])
                if (w == other or w == a)
                {	w = ins ? a : other; break;	}
        }
        ins ? g[a].pb(u), g[a].pb(v) : g[a].resize(0);
    }
    int dfsCents(int v, int fath)
    {
        sz[v] = 1;
        for (int u : G[v])	if (u != fath)	sz[v] += dfsCents(u, v);
        return sz[v];
    }
    void getCentroids(vector <int>* g, int n, vector <int>& res)
    {
        G = g;	dfsCents(1, 0);
        for (int v=1; v<=n and res.size()<2; v++)
        {
            bool isCentroid = sz[v] >= n / 2;
            for (int u : g[v])
                if (n / 2 < sz[u] and sz[u] < sz[v])
					isCentroid = false;         
            if (isCentroid)	res.pb(v);
        }
    }
    vector <int>* tab;
    void dfsVsOnDist(int v, int father, int d)
    {
        tab[d].pb(v);
        for (int u : G[v])
            if (u != father)  dfsVsOnDist(u, v, d + 1);
    }
    void toDigits(int a, vector <int>& t)
    {
        if (a == 0) t.pb(0);
        for (; a != 0; a /= 10)	t.pb(a % 10);
    }
    int fold(vector <int>& t)
    {
        int res = 0;
        for (int i=t.size()-1; i>=0; i--)
            res = res * 10 + t[i];
        return res;
    }
    bool checkIsomorphism(vector <int>* g0, vector <int>* g1, int n)
    {
        if (n < 3)  return true;
        bool res = false;
        vector <int> cents[2];
        getCentroids(g0, n, cents[0]);
        getCentroids(g1, n, cents[1]);
        if (cents[0].size() != cents[1].size())	return false;
        int roots[2];
        bool newVertex = false;
        if (cents[0].size() == 1)
        {
            roots[0] = cents[0][0];
            roots[1] = cents[1][0];
        }
        else
        {
            roots[0] = roots[1] = ++n;
            newCentroid(n, cents[0][0], cents[0][1], g0, true);
            newCentroid(n, cents[1][0], cents[1][1], g1, true);
            newVertex = true;
        }
        G = g0, tab = vsOnDist[0];
        dfsVsOnDist(roots[0], 0, 0);
        G = g1, tab = vsOnDist[1];
        dfsVsOnDist(roots[1], 0, 0);       
        int maxD = 0;
        FOR(i, 1, n+1)
            if (!vsOnDist[0][i].empty() or !vsOnDist[1][i].empty())
                maxD = i;
            else break;
        fill(id[0] + 1, id[0] + n + 1, -1);
        fill(id[1] + 1, id[1] + n + 1, -1);
        for (int d=maxD; d>=0; d--)
        {
            int levelSize = vsOnDist[0][d].size();
            if (levelSize != vsOnDist[1][d].size())	goto End;
            FOR(s, 0, 2)
            {
                G = (s == 0 ? g0 : g1);
                vector <int>& level = vsOnDist[s][d];
                vector <int>* currL = L[s];
                int* currId = id[s];
                FOR(i, 0, levelSize)
                {
                    int v = level[i], tempSize = 0;
                    for (int u : G[v])
                        if (currId[u] != -1)
                          toDigits(currId[u], tempSeq[tempSize++]);
                    posSort(tempSeq, tempSize, order0);
                    for (int ind : order0)
                    {
                        currL[i].pb(fold(tempSeq[ind]));
                        tempSeq[ind].resize(0);
                    }
                    order0.resize(0);
                }
            }
            posSort(L[0], levelSize, order0);
            posSort(L[1], levelSize, order1);
            int newIdsCtr = 0;
            vector <int>& lev0 = vsOnDist[0][d];
            vector <int>& lev1 = vsOnDist[1][d];
            FOR(i, 0, levelSize)
            {
                int ind0 = order0[i];
                int ind1 = order1[i];
                if (L[0][ind0] != L[1][ind1])	goto End;
                int prevInd = i == 0 ? -1 : order0[i - 1];
                if (i > 0 and L[0][prevInd] != L[0][ind0])
                    newIdsCtr++;
                int v0 = lev0[ind0];
                int v1 = lev1[ind1];
                id[0][v0] = id[1][v1] = newIdsCtr;
            }
            FOR(i, 0, levelSize) FOR(s, 0, 2)	L[s][i].resize(0);   
            order0.resize(0); order1.resize(0);
        }
        res = true;	End:
        if (newVertex)
        {
            newCentroid(n, cents[0][0], cents[0][1], g0, false);
            newCentroid(n, cents[1][0], cents[1][1], g1, false);
        }
        clear(n);	return res;
    }
};
