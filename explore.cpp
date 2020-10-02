#include "explore.h"

#include <vector>
#include <filesystem>

#include <iostream>
#include "termcolor/termcolor.hpp"

#include "print.h"
#include "treeutil.h"




void explore(const std::vector<kn_item>& tree) {
	namespace tc = termcolor;

	const fs::path root_cwd = fs::current_path();

	std::wstring message;
	enum{INFO=0, WARN, ERR} message_type;

	decltype(tree.cbegin()) root;

	while (true) {
		const fs::path cwd = fs::current_path();
		const fs::path rel_cwd = cwd.lexically_relative(root_cwd);
		std::cout << tc::yellow;
		std::wcout << "cwd: " << cwd << "\n" << std::endl;
		std::cout << tc::reset;

		root = tree_find(tree, rel_cwd);
		tree_print(tree, root);

		std::cout << tc::green << "\n\nType the name of folder to go inside or \"..\" to go back.";
		std::cout << "\nType \":quit\" or \":exit\" to quit the program." << tc::reset << std::endl;

		if (!message.empty()) {
			std::cout << "\n" << tc::grey;
			switch (message_type){
			case INFO: std::cout << tc::on_cyan << "INFO";  break;
			case WARN: std::cout << tc::on_yellow << "WARNING";  break;
			case ERR: std::cout << tc::on_red << "ERROR";  break;
			}
			std::wcout << ":  " << message.c_str();
			std::cout << tc::reset << std::endl;
			message.clear();
			message_type = INFO;
		}

		std::cout << tc::yellow << "\ndire>" << tc::reset;
		fflush(stdout);

		char cmd[255];
		//std::wcin >> cmd;
		std::cin.getline(cmd, sizeof(cmd));

		std::cout << std::endl;

		if (!strcmp(cmd, ":exit") || !strcmp(cmd, ":quit")) {
			break;
		}
		else if(!strcmp(cmd, "..")){
			if (rel_cwd.empty() || rel_cwd == ".") {
				message_type = WARN;
				message = L"You cannot go back beyond the directory where you started the scan.";
			}
			else {
				fs::current_path("..");
			}
		}
		else {
			const auto old_root = root;
			root = tree_find(tree, rel_cwd / cmd);
			if (root == tree.crend() || root->sub == 0) {
				message_type = ERR;
				message = L"Couldn't find the directory \"";
				message.append(cwd / cmd);
				message.append(L"\" in the generated tree (doesn't exist or access is not permitted)");
				root = old_root;
			}
			else {
				fs::current_path(cmd); //CHANGE THIS!!!
				//fs::current_path(root->name);
			}
		}
	}
}