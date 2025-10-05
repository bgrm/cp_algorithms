template <typename TT>
struct CartNode
{
	CartNode *fat, *left, *right;
	TT val;

	CartNode (CartNode* a=0, CartNode* b=0, CartNode* c=0, TT d=0)
	: fat(a), left(b), right(c), val(d)	{};

	static CartNode* newNode(bool init = false);

	CartNode* add(TT x)
	{
		CartNode *v = this, *r = v->right, *ret = newNode();
		while (v and v->val > x)
			r = v, v = v->fat;
		*ret = CartNode(v, r, NULL, x);
		if (r)
			r->fat = ret;
		if (v)
			v->right = ret;
		return ret;	
	}
	static CartNode* create(vector <TT>& T)
	{
		CartNode* v = newNode(true);
		*v = {NULL, NULL, NULL, T[0]};
		FOR(i, 1, SZ(T))
			v = v->add(T[i]);
		while (v->fat)
			v = v->fat;
		return v;
	}
};
using Node = CartNode <int>;
Node MEM[maxN];
int cnt;

template <typename TT>
CartNode<TT>* CartNode<TT>::newNode(bool init)
{
    if (init) cnt = 0;
    return MEM + cnt++;
}