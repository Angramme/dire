#include "print.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>

#include "strutil.h"

#include "termcolor/termcolor.hpp"

std::string pretty_size(const decltype(kn_item::disk_size)& size_bytes) {
	double size = size_bytes;
	unsigned int i = 0;
	while (size > 1000.0) {
		i++;
		size /= 1000.0;
	}
	const char* types[] = { "b", "kB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB" }; // a bit optimistic :)

	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << size;
	stream << " " << types[i];
	return stream.str();
}

void tree_print(const std::vector<kn_item>& tree,
	const std::vector<kn_item>::const_iterator& root) {
	std::multimap<decltype(kn_item::disk_size), const kn_item*> sorted;
	auto it = root + 1;
	for (int i = 0; i < root->sub_count; i++, it++) {
		sorted.insert(std::make_pair(it->disk_size, &(*it)));
	}

	namespace tc = termcolor;

	std::cout << tc::cyan << tc::bold;
	std::cout << "Relative  Size        Name                " << tc::reset << std::endl;
	std::cout << "--------  ----------  --------------------" << std::endl;

	for (auto it = sorted.rbegin(); it != sorted.rend(); it++) {
		const auto& item = it->second;
		/*wprintf(L"%6.1f%%   %10s   %.20s\n",
			(float)item->disk_size / root->disk_size*100.0,
			item->access_denied ? L"ERROR" : pretty_size(item->disk_size).c_str(),
			item->name.c_str());*/

		printf("%6.1f%%   %10s   %.20s\n",
			(float)item->disk_size / root->disk_size*100.0,
			item->access_denied ? "ERROR" : pretty_size(item->disk_size).c_str(),
			wstr_convert(item->name).c_str());
	}
}