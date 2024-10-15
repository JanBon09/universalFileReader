#pragma once

#include <vector>
#include <string>

namespace BGE {
	static class BGE_FileReader {
	public:
		static std::string showContents(const char*);
		static void modeFilteredContent(std::string&, int);
		static void extensionFilteredContent(std::string&, std::vector<std::string>);
		static std::vector<std::string>readContent(std::string);
	};
}