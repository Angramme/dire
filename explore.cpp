#include "explore.h"

#include <vector>
#include <filesystem>

#include <iostream>
#include "termcolor/termcolor.hpp"

#include "print.h"
#include "treeutil.h"


void explore(const Tree& tree) {
	namespace tc = termcolor;

	const fs::path root_cwd = fs::current_path();

	std::wstring message;
	enum{INFO=0, WARN, ERR} message_type;

	decltype(tree.cbegin()) root = tree.cbegin();

	while (true) {
		const fs::path cwd = fs::current_path();
		const fs::path rel_cwd = cwd.lexically_relative(root_cwd);
		std::cout << tc::yellow << "cwd: " << tc::reset << tc::bold;
		std::wcout << cwd << "\n" << std::endl;
		std::cout << tc::reset;

		tree_print(tree, root);

		std::cout << tc::green << "\n\nType the name of folder to go inside or \"..\" to go back. Type :help to list all commands.";
		//std::cout << "\nType \":quit\" or \":exit\" to quit the program." << tc::reset << std::endl;

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

		std::cout << "\n\n\n\n\n" << std::endl;

		//if (!strcmp(cmd, ":exit") || !strcmp(cmd, ":quit")) {
			
		if(cmd[0] == ':'){
			const auto* cmds = cmd + 1;
			if (!strcmp(cmds, "exit") || !strcmp(cmds, "quit")) { break; }
			else if (!strcmp(cmds, "help")) { 
				message_type = INFO;
				message = L"\nuse \":help\" to print this help message"
						  L"\nuse \":exit\" or \":quit\" to quit the application"
					;
			} else{
				message_type = ERR;
				message = L"This command does not exist, please use \":help\" to see the list of available commands.";
			}
		}
		else if(!strcmp(cmd, "..")){
			if (rel_cwd.empty() || rel_cwd == ".") {
				message_type = WARN;
				message = L"You cannot go back beyond the directory where you started the scan.";
			}
			else {
				fs::current_path("..");
				root = tree_find(tree, fs::current_path().lexically_relative(root_cwd));
			}
		}
		else {
			const auto old_root = root;
			root = tree_find(tree, rel_cwd / cmd);
			if (root == tree.cend() || root->sub_count == 0) {
				message_type = ERR;
				message = L"Couldn't find the directory \"";
				message.append(cwd / cmd);
				message.append(L"\" in the generated tree (doesn't exist or access is not permitted)");
				root = old_root;
			}
			else {
				//fs::current_path(cmd); //CHANGE THIS!!!
				fs::current_path(root->name);
			}
		}
	}
}