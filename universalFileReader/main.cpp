#include "BGE_FileReader.hpp"

#include <filesystem>
#include <iostream>

int main() {
	const char* path = "C:\\Studia_Projekty\\OpenGL_Libraries";
	std::string paths;

	paths = BGE::BGE_FileReader::showContents(path);

	std::cout << paths << std::endl;

	BGE::BGE_FileReader::modeFilteredContent(paths, 0);

	std::cout << paths << std::endl;

	std::vector<std::string> extension{ ".vert", ".frag" };

	BGE::BGE_FileReader::extensionFilteredContent(paths, extension);

	std::cout << paths << std::endl;

	std::vector<std::string> contents = BGE::BGE_FileReader::readContent(paths);

	for (const std::string& content : contents) {
		std::cout << content << std::endl;
	}

	return 0;
}