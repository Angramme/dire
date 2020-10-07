#include "treeutil.h"
#include "strutil.h"

Tree::const_iterator tree_find(const Tree& tree, fs::path rel_path) {
	rel_path = rel_path.make_preferred().lexically_normal();
	if (rel_path == "." || rel_path == "") return tree.cbegin();

	auto cur = tree.cbegin();

	for (const auto& cur_path : rel_path) {
		const unsigned int tot_count = cur->sub_count;
		cur = tree.cbegin() + cur->sub_list_i;
		unsigned int i = 0;
		while (cur_path != cur->name) {
			cur++;
			if (++i >= tot_count) return tree.cend();
		}
	}

	return cur;
}