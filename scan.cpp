#include <stack>
#include <vector>

#include "termcolor/termcolor.hpp"

#include "scan.h"
#include "explore.h"


void cmd_scan(int argc, char** argv) {
	fs::path cwd = fs::current_path();

	std::stack<un_item> unknown;
	std::vector<kn_item> tree;
	
	tree.push_back({ 1, 0, 0, cwd.stem(), false });
	unknown.push({ tree.size()-1, UINT32_MAX, cwd, false });

	while (!unknown.empty()) {
		auto& cur = unknown.top();
#define cur_mirror tree[cur.mirror_i]
#define cur_parent tree[cur.parent_i]

		if (!cur.visited) {
			cur.visited = true;
			cur_mirror.sub_list_i = tree.size();
			auto cur_iter = fs::directory_iterator(cur.full_path);
			while (cur_iter != fs::end(cur_iter))
			{
				std::error_code err;
				if (!cur_iter->exists(err) && !err) { /*pass*/ }
				else if (cur_iter->is_directory(err) && !err) {
					cur_mirror.sub_count++;
					unknown.push({ tree.size(), cur.mirror_i, cur_iter->path(), false });
					tree.push_back({ 0, 0, 0, cur_iter->path().stem(), false });
				}
				else if(cur_iter->is_regular_file(err) && !err) {
					cur_mirror.sub_count++;
					cur_mirror.known_sub_count++;
					cur_mirror.disk_size += cur_iter->file_size();
					tree.push_back({ 0, 0, cur_iter->file_size(), cur_iter->path().filename(), false });
				}else if (err) {
					cur_mirror.sub_count++;
					cur_mirror.known_sub_count++;
					tree.push_back({ 0, 0, 0, cur_iter->path().stem(), true });
				}
				cur_iter++;
			}
		}else if (cur_mirror.known_sub_count == cur_mirror.sub_count) {
			// this directory is fully known!!!
			if (cur.parent_i < tree.size()) {
				cur_parent.disk_size += cur_mirror.disk_size;
				cur_parent.known_sub_count++;
			}
			unknown.pop();
		}

#undef cur_mirror
#undef cur_parent
	}

	explore(tree);
}


