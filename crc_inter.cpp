vector <Point> crcInter(const Crc& Ci, const Crc& Cj)
{
	long long dx = Ci.x - Cj.x, dy = Ci.y - Cj.y, d2 = kw(dx) + kw(dy);
	double D = sqrt(d2);
	double X = (d2 + kw(Cj.r) - kw(Ci.r)) / (2.0 * D);
	double Y = sqrt(kw(Cj.r) - kw(X));
	vector <Point> res({Point(X, Y), Point(X, -Y)});
	double c = dx / D, s = dy / D;
	FOR(k, 0, 2)
		res[k] = Point(res[k] % Point(s,c), res[k] % Point(-c,s)) + Cj.pt;
	return res;
}
