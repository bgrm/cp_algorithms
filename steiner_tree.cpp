namespace SteinerTree
{
	int dp[maxN][1 << maxT];
	int compute(int G[maxN][maxN], int n, int* terms, int t)
	{
		FOR(k, 0, n) FOR(i, 0, n) FOR(j, 0, n)
			remin(G[i][j], G[i][k] + G[k][j]);
		FOR(m, 1, 1<<t)
		{
			FOR(v, 0, n)
			{
				dp[v][m] = INF;
				for (int m2 = m-1 & m; m2 != 0; m2 = m2-1 & m)
					remin(dp[v][m], dp[v][m^m2] + dp[v][m2] - 1);
			}
			if (PPC(m) == 1)	dp[terms[CTZ(m)]][m] = 1;
			FOR(v, 0, n) FOR(u, 0, n)
				remin(dp[v][m], G[v][u] + dp[u][m]);			
		}
		return dp[terms[0]][(1<<t) - 1];
	}
}
