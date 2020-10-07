#pragma once

#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

#include "scan.h"

Tree::const_iterator tree_find(const Tree& tree, fs::path rel_path);