#pragma once

int ParseInt(std::string str);
std::vector<std::string> Split(std::string str, char splitter);
std::string UpstreamBytes(float bytes);
std::string UpstreamBytes(float bytes, int precision);
float BytesToMB(int64_t bytes);
std::string space_string_len(int i, int len);
std::string space_string(int i);