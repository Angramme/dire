#pragma once

#include <filesystem> 
namespace fs = std::filesystem;
#include <string>

using filesize = decltype(std::declval<fs::directory_entry>().file_size());

void cmd_scan(int argc, char** argv);


struct kn_item;
struct un_item {
	kn_item* mirror;
	kn_item* parent;

	fs::directory_iterator iter;

	unsigned int known_sub_count = 0; // count of elements with fully known properties i.e. size, count of sub-elements etc...
	
	kn_item* operator->();
};

struct kn_item {
	size_t sub_list_i;
	unsigned int sub_count;

	filesize disk_size;
	fs::path name;

	bool access_denied;
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