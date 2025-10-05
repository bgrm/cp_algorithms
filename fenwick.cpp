struct Fenwick
{
	void updt(int i, long long val)
	{	for (i++; i<=ran; i+=(-i)&i)	T[i] += val;	}
	long long sum(int i)
	{
		long long ret = 0;
		for (; i!=0; i&=i-1)	ret+=T[i];
		return ret;
	}
};
