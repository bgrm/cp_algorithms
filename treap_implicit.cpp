namespace TIK // TreapImplicitKeys
{
	using NodeData_t = int;
	std::mt19937 gen(std::random_device{}());

	struct Node
	{
		#define GET_MEMB(ptr, memb)			((ptr) ? (ptr)->memb : 0)
		#define ASGN_MEMB(ptr, memb, val)	{ if (ptr) (ptr)->memb = (val); }
		#define CALL_METH(ptr, meth)		{ if (ptr) (ptr)->meth; }
	private:
		void updateSon(Node** sonSlot, Node* newSon)
		{
			if (GET_MEMB(*sonSlot, parent) == this)
				ASGN_MEMB(*sonSlot, parent, nullptr);

			ASGN_MEMB(newSon, parent, this);
			*sonSlot = newSon;
			post();
		}
	public:
		Node(const NodeData_t& val = 0, Node* a = nullptr, Node* b = nullptr)
		: value(val)
		, left(a)
		, right(b)
		, rank(gen())
		{
			post();
		}

		void setLeft(Node* newSon)	{	updateSon(&left, newSon);	}
		void setRight(Node* newSon)	{	updateSon(&right, newSon);	}
		void revert()				{	rev ^= true;	}

		void pre()
		{
			if (rev)
			{
				std::swap(left, right);
				if (left) left->revert();
				if (right) right->revert();
				rev = false;
			}
		}
		void post()
		{
			size = GET_MEMB(left, size) + GET_MEMB(right, size) + 1;
			sum = GET_MEMB(left, sum) + GET_MEMB(right, sum) + value;
		}

		NodeData_t value = 0, sum = 0;
		Node *left = nullptr, *right = nullptr, *parent = nullptr;
		const int rank;
		int size = 1;
		bool rev = false;
	};

	std::vector <Node> MEM;
	template <typename... Args>
	Node* newNode(Args... args)
	{
		if (MEM.empty())
			MEM.reserve(maxN);

		MEM.emplace_back(args...);
		return &(MEM.back());
	}

	std::pair <Node*, Node*> splitBySize(Node* v, int leftSplitSize)
	{
		if (v == nullptr)
			return { nullptr, nullptr };

		v->pre();
		int leftsSize = GET_MEMB(v->left, size);

		if (leftSplitSize <= leftsSize)
		{
			auto [low, gre] = splitBySize(v->left, leftSplitSize);
			v->setLeft(gre);
			return { low, v };
		}
		else
		{
			auto [low, gre] = splitBySize(v->right, leftSplitSize - leftsSize - 1);
			v->setRight(low);
			return { v, gre };
		}
	}

	Node* merge(Node* left, Node* right)
	{
		if (left == nullptr or right == nullptr)
			return left ? left : right;

		if (left->rank < right->rank)
		{
			left->pre();
			Node* newSon = merge(left->right, right);
			left->setRight(newSon);
			return left;
		}
		else
		{
			right->pre();
			Node* newSon = merge(left, right->left);
			right->setLeft(newSon);
			return right;
		}
	}

	Node* merge(const std::vector <Node*>& T)
	{
		Node* sum = nullptr;
		for (auto v : T)
			sum = merge(sum, v);
		return sum;
	}

	Node* kth(Node* v, int k) // 0-based
	{
		if (v == nullptr)
			return nullptr;
		v->pre();

		int leftsSize = GET_MEMB(v->left, size);
		if (leftsSize == k)
			return v;
		return k < leftsSize ? kth(v->left, k) : kth(v->right, k - 1 - leftsSize);		
	}

	Node* insert(Node* v, int k, const NodeData_t& x)
	{
		auto [a, b] = splitBySize(v, k);
		return merge({a, newNode(x), b});
	}

	Node* first(Node* v)
	{
		if (v)
			while (v->pre(), v->left)
				v = v->left;
		return v;
	}

	bool isRightSon(Node* v)
	{
		return v and v->parent and v->parent->right == v;
	}

	Node* next(Node* v)
	{
		if (v == nullptr)
			return nullptr;

		if (v->pre(), v->right)
			return first(v->right);
		else
		{
			while (isRightSon(v))
				v = v->parent;
			return v->parent;
		}
	}

	Node* erase(Node* v, int k)
	{
		if (v == nullptr or k >= v->size)
			return v;
		v->pre();

		auto [a, b] = splitBySize(v, k);
		auto [_elem, c] = splitBySize(b, 1);
		return merge(a, c);
	}

	void revert(Node* v)
	{
		if (v)
			v->revert();
	}

	Node* create(std::vector <NodeData_t>& values)
	{
		Node* v = nullptr;
		for (const auto& val : values)
			v = merge(v, newNode(val));
		return v;
	}

	template <int N>
	auto splitByPos(Node* v, const std::array <int, N>& P)
	{
		std::array <Node*, N+1> ret;
		auto it = ret.rbegin();

		for (int p : P | std::views::reverse)
			tie(v, *it++) = splitBySize(v, p);

		*it = v;
		return ret;
	}
	
	template <int N>
	auto splitByLen(Node* v, const std::array <int, N>& P)
	{
		std::array <Node*, N+1> ret;
		auto it = ret.begin();

		for (int p : P)
			tie(*it++, v) = splitBySize(v, p);

		*it = v;
		return ret;
	}
}
