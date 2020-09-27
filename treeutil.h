#pragma once

#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

#include "scan.h"

std::reverse_iterator<std::vector<Item>::const_iterator> tree_find(const std::vector<Item>& tree, fs::path rel_path);