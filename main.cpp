#include "config.h"
#include <iostream>
#include <locale>
#include <string>

#include "scan.h"


struct subcmd
{
	char name[20];
	std::string description;
	void (*func)(int argc, char** argv);
};

void cmd_help(int argc, char** argv);

const subcmd cmds[] = {
	{"help", "prints help message", &cmd_help},
	{"scan", "scans recursively from cwd downwards and creates a traversable tree structure", &cmd_scan}
};
subcmd* get_cmd(char* name) {
	subcmd* cmd = const_cast<subcmd*>(cmds);
	while (strncmp(cmd->name, name, strlen(name)) || cmd->name[strlen(name)] != 0) {
		cmd += 1;
		if (cmd - cmds > sizeof(cmds)) return nullptr;
	}
	return cmd;
}

int main(int argc, char** argv){
	std::locale::global(std::locale{ "" });

	std::cout << "dire v" << dire_VERSION_MAJOR << "." << dire_VERSION_MINOR 
		<< "(C) Kacper Ozieblowski 2020 \n" << std::endl;

	if (argc < 2) {
		cmd_help(argc, argv);
	}
	else {
		subcmd* cmd = get_cmd(argv[1]);
		if (cmd) {
			cmd->func(argc, argv);
		}
		else {
			std::cout << "Could not find the command!\n" << std::endl;
			cmd_help(1, argv);
		}
	}

	//cmd_scan(argc, argv);

    return 1;
}

void cmd_help(int argc, char** argv) {
	if (argc < 3) {
		std::cout << "dire usage: " << std::endl;
		for (int i = 0; i < sizeof(cmds) / sizeof(subcmd); i++) {
			std::cout << "  - " << cmds[i].name << " : \n     " << cmds[i].description << "\n";
		}
	}
	else {
		subcmd* cmd = get_cmd(argv[2]);
		if (cmd) {
			std::cout << cmd->name << " : \n    " << cmd->description;
		}
		else {
			std::cout << "Could not find the command!\n" << std::endl;
			cmd_help(1, argv);
		}
	}
}