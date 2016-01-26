#pragma once

#include <string>
#include <regex>

void replace(std::string&, const std::string&, const std::string&);

std::string trim(const std::string&);

std::string ltrim(const std::string&);

std::string rtrim(const std::string&);

std::string remove_spaces(const std::string&);

bool sanitize_url(const std::string&, const std::string& = "");

std::string str_pad(const std::string&, const size_t, const char=' ', const bool=true);
