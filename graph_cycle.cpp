namespace Cycle
{
	bool after, vis[maxN];
	int root, parent[maxN];

	bool dfs(int v, int fat)
	{
        if (vis[v])
        {
            root = v;
            return true;
        }
		vis[v] = true;
        bool ret = false;
		for (int u : G[v]) if (u != fat and dfs(u, v))
		{
            if (!after)
                parent[u] = v;
            if (v == root)
                after = true;
            ret = true;
            break;
		}
		return ret;
	}
}