#pragma once

#include <vector>
#include <string>


namespace BGE {

	class BGE_FileReader {
	public:
		static std::string showContents(const char*);
		static void modeFilteredContent(std::string&, int);
		static void extensionFilteredContent(std::string&,const std::vector<std::string>&);
		static std::vector<std::string>readContent(const std::string&);
	};
}