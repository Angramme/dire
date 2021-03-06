#pragma once

#include <filesystem> 
namespace fs = std::filesystem;
#include <string>

struct kn_item;

using filesize = decltype(std::declval<fs::directory_entry>().file_size());
using Tree = std::vector<kn_item>;

void cmd_scan(int argc, char** argv);


struct un_item {
	size_t mirror_i;
	size_t parent_i;
	fs::path full_path;
	bool visited = false;
};
//
//struct un_item_ref {
//	un_item& self;
//	Tree& vec;
//
//	un_item_ref() = delete;
//	un_item_ref(un_item& s, Tree& vec)
//		: self(s), vec(vec)
//	{}
//
//	Tree::iterator operator->();
//	Tree::iterator parent();
//};

struct kn_item {
	size_t sub_list_i;
	size_t sub_count;

	filesize disk_size;
	fs::path name;

	bool access_denied;

	size_t known_sub_count = 0; // count of elements with fully known properties i.e. size, count of sub-elements etc...
};



//struct uFolder {
//	unsigned int ksub; //known sub items
//	unsigned int rsub; //total known sub items including sub folders
//	filesize disk_size;
//	fs::path name;
//
//	fs::directory_iterator iter; //current sub item being examined
//	bool access_denied;
//
//	uFolder(const fs::path& name, const fs::directory_iterator& iter)
//		: ksub(0), rsub(0), disk_size(0), name(name), iter(iter), access_denied(false)
//	{}
//
//	uFolder(const unsigned int& ksub, const unsigned int& rsub, const filesize& disk_size, const fs::path& name, const fs::directory_iterator& iter, const bool& access_denied)
//		: ksub(ksub), rsub(rsub), disk_size(disk_size), name(name), iter(iter), access_denied(access_denied)
//	{}
//};
//
//struct Item {
//	unsigned int sub; //sub element count
//	unsigned int rsub; //recursive sub element count
//	filesize disk_size;
//	fs::path name;
//	//std::string name;
//	bool access_denied;
//
//	Item(const unsigned int& sub, const unsigned int& rsub, const filesize& disk_size, const fs::path& name)
//		: sub(sub), rsub(rsub), disk_size(disk_size), name(name), access_denied(false)
//	{}
//
//	Item(const unsigned int& sub, const unsigned int& rsub, const filesize& disk_size, const fs::path& name, const bool& access_denied)
//		: sub(sub), rsub(rsub), disk_size(disk_size), name(name), access_denied(access_denied)
//	{}
//};