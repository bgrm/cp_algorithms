namespace Euler
{
	bool vis[maxN];
	vector <int> res;

	void dfs(int v)
	{
		while (!G[v].empty())
		{
			int e = G[v].back();
			G[v].pop_back();
			if (!vis[e])
			{
				vis[e] = true;
				dfs(oth(e, v));
			}
		}
		res.pb(v);
	}
}