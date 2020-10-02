#include "treeutil.h"
#include "strutil.h"

std::vector<kn_item>::const_iterator tree_find(const std::vector<kn_item>& tree, fs::path rel_path) {
	rel_path = rel_path.make_preferred().lexically_normal();
	if (rel_path == "." || rel_path == "") return tree.cbegin();

	auto cur = tree.crbegin();

	for (const auto& cur_path : rel_path) {
		// find next
		const unsigned int tot_count = cur->sub_count;
		cur = tree.crbegin() + cur->sub_list_i;
		unsigned int i = 0;
		while (!cur_path.compare(cur->name)) {
			cur++;
			if (++i >= tot_count) return tree.cend();
		}
	}


	/*for (const auto& cur_path : rel_path) {
		const unsigned int i_max = cur->sub;
		unsigned int i = 0;
		cur++;
		while (wstr_convert(cur->name) != cur_path) {
			cur += cur->rsub + 1;
			if (++i >= i_max) return tree.crend();
		}
	}
	return cur;*/
}