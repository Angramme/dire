#pragma once
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

std::string wstr_convert(fs::path string_to_convert);