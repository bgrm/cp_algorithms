pair <Point, Point> crcLineInter(const Crc& C, Point a, Point b)
{
	a -= C.pt, b -= C.pt;
	double dx = b.x - a.x, dy = b.y - a.y;
	double d2 = kw(dx) + kw(dy), ilo = a % b;
	double w = d2 * kw(C.r) - kw(ilo);
	if (w < -E)
		return {{INF, INF}, {INF, INF}};
	w = sqrt(max(w, 0.0));
	a.x = ilo * dy + w * dx;
	b.x = ilo * dy - w * dx;
	if (dy < 0)		swap(a.x, b.x);
	a.y = -ilo * dx + w * fabs(dy);
	b.y = -ilo * dx - w * fabs(dy);
	a *= 1.0/d2;	a += C.pt;
	b *= 1.0/d2;	b += C.pt;
	return {a, b};
}
