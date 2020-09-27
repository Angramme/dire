#include "treeutil.h"
#include "strutil.h"

std::reverse_iterator<std::vector<Item>::const_iterator> tree_find(const std::vector<Item>& tree, fs::path rel_path) {
	rel_path = rel_path.make_preferred().lexically_normal();
	if (rel_path == "." || rel_path == "") return tree.crbegin();

	auto cur = tree.crbegin();

	for (const auto& cur_path : rel_path) {
		const unsigned int i_max = cur->sub;
		unsigned int i = 0;
		cur++;
		while (wstr_convert(cur->name) != cur_path) {
			cur += cur->rsub + 1;
			if (++i >= i_max) return tree.crend();
		}
	}
	return cur;
}