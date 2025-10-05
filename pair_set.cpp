set <pair <int, int> > S;
 
bool contains(pair <int, int> p, int x)
{	return p.ft <= x and x <= p.sd;	}
 
auto getItCovering(int x)
{
	auto it = S.upper_bound({x, INF});
 
	if (it != S.begin() and contains(*prev(it), x))
		return prev(it);
	else
		return S.end();
}
 
void mrg(auto it)
{
	auto jt = next(it);
	
	if (jt != S.end() and it->sd + 1 == jt->ft)
	{
		pair <int, int> p { it->ft, jt->sd };
 
		S.erase(it);
		S.erase(jt);
		S.insert(p);
	}
}
 
void insert(int x)
{
	if (getItCovering(x) != S.end())
		return;
		
	auto it = S.insert({x, x}).ft;
	mrg(it);
 
	it = getItCovering(x);
	if (it != S.begin())
		mrg(prev(it));	
}