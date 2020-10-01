#include <iostream>
#include <stack>
#include <vector>

#include "termcolor/termcolor.hpp"

#include "scan.h"
#include "explore.h"



kn_item* un_item::operator->() {
	return mirror;
}



void cmd_scan(int argc, char** argv) {
	fs::path cwd = fs::current_path();

	/*std::stack<uFolder> unknown;
	std::vector<Item> tree;*/
	
	//unknown.push({cwd.stem(), fs::directory_iterator(cwd)});

	std::stack<un_item> unknown;
	std::vector<kn_item> tree;

	tree.push_back({ 1, 0, 0, cwd.stem(), false });
	unknown.push({ &*tree.end(), nullptr, fs::directory_iterator(cwd) });

	while (!unknown.empty()) {
		auto& cur = unknown.top();

		while (cur.iter != fs::end(cur.iter))
		{
			cur->sub_list_i = tree.size();

			std::error_code err;
			if (!cur.iter->exists(err) && !err) {
				cur.iter++;
			}
			else if (cur.iter->is_directory(err) && !err) {
				tree.push_back({ 0, 0, 0, cur.iter->path().stem(), false });
				unknown.push({ &*tree.end(), cur.mirror, fs::directory_iterator(cur.iter->path()) });
				cur->sub_count++;
			}
			else if(cur.iter->is_regular_file()) {
				tree.push_back({ 0, 0, cur.iter->file_size(), cur.iter->path().stem(), false });
				// this file is fully determined!
				cur->sub_count++;
				cur.known_sub_count++;
				cur->disk_size += tree.end()->disk_size;
			}

			if (err) {
				tree.push_back({ 0, 0, 0, cur.iter->path().stem(), true });
				cur->sub_count++;
				cur.known_sub_count++;
				/// cur->disk_size += tree.end()->disk_size;
			}
		}

		if (cur.iter == fs::end(cur.iter) && cur.known_sub_count == cur->sub_count) {
			// this directory is fully known!!!
			cur.parent->disk_size += cur->disk_size;
			
			unknown.pop();
		}



		
		/*auto& parent = unknown.top();

		if (parent.iter == fs::end(parent.iter)) {
			tree.push_back(Item(parent.ksub, parent.rsub, parent.disk_size, parent.name, parent.access_denied));
			const auto size = parent.disk_size;
			const auto rsub = parent.rsub;
			unknown.pop();
			if (unknown.empty())break;
			auto& dparent = unknown.top();
			dparent.disk_size += size;
			dparent.iter++;
			dparent.ksub++;
			dparent.rsub += rsub + 1;
		}
		else {
			auto& cur = *parent.iter;

			std::error_code err;
			if(!cur.exists(err) && !err) {
				parent.iter++;
			}
			else if (cur.is_regular_file(err) && !err) {
				const auto disk_size = cur.file_size();
				parent.disk_size += disk_size;
				tree.push_back(Item(0, 0, disk_size, cur.path().filename()));
				parent.iter++;
				parent.ksub++;
				parent.rsub++;
			}
			else if (cur.is_directory(err) && !err) {
				fs::directory_iterator niter(cur.path(), err);
				if(!err) unknown.push(uFolder(cur.path().stem(), niter));
			}
			if (err) {
				tree.push_back(Item(0, 0, 0, cur.path().stem(), true));
				parent.iter++;
				parent.ksub++;
				parent.rsub++;
			}
		}*/
	}

	explore(tree);

	/*for (auto& p : tree) {
		wprintf(L"sub: %i rsub: %i n: %s s: %i err: %d\n", p.sub, p.rsub, p.name.c_str(), p.disk_size, p.access_denied);
	}*/
}


