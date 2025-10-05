
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree <T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;		//find_by_order() / order_of_key()
	
template <class Key, class Value, class Hash = hash <Key> >
using __fast_unordered_map = gp_hash_table<Key, Value, Hash>;
