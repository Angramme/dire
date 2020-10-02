#pragma once

#include <vector>
#include <filesystem>
namespace fs = std::filesystem;

#include "scan.h"

std::vector<kn_item>::const_iterator tree_find(const std::vector<kn_item>& tree, fs::path rel_path);