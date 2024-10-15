#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <fstream>

#include "BGE_FileReader.hpp"

namespace BGE {
	std::string BGE_FileReader::showContents(const char* primaryPath) {
		std::string temporaryContentStorage;
		for(const auto& path : std::filesystem::directory_iterator(primaryPath)){
			temporaryContentStorage.append(path.path().string());
			temporaryContentStorage.push_back('\n');
		}

		return temporaryContentStorage;
	}

	void BGE_FileReader::modeFilteredContent(std::string& pathsList, int mode) {
		std::string filteredContents;
		std::stringstream pathsListStream;
		std::string tempPath;

		pathsListStream.str(pathsList);
		while (std::getline(pathsListStream, tempPath, '\n')) {
			switch (mode) {
			case 0:
				if (std::filesystem::is_regular_file(std::filesystem::status(std::filesystem::path(tempPath)))) {
					filteredContents.append(tempPath);
					filteredContents.push_back('\n');
				}
				break;
			case 1:
				if (std::filesystem::is_directory(std::filesystem::status(std::filesystem::path(tempPath)))) {
					filteredContents.append(tempPath);
					filteredContents.push_back('\n');
				}
				break;
			default:
				std::cerr << "Invalid mode" << std::endl;
				exit(EXIT_FAILURE);
				break;
			}
		}
		pathsList = filteredContents;
	}

	void BGE_FileReader::extensionFilteredContent(std::string& pathsList, std::vector<std::string> fileExtensions) {
		std::string filteredContents;
		std::stringstream pathsListStream;
		std::string tempPath;
		
		pathsListStream.str(pathsList);
		while (std::getline(pathsListStream, tempPath, '\n')) {
			bool fileExtensionsCompatible = false;
			for (const std::string& fileExtension : fileExtensions) {
				std::string extractedFileExtension = tempPath.substr(tempPath.length() - fileExtension.length(), fileExtension.length());
				if (extractedFileExtension == fileExtension) {
					fileExtensionsCompatible = true;
					break;
				}
			}
			if (fileExtensionsCompatible) {
				filteredContents.append(tempPath);
				filteredContents.push_back('\n');
			}
		}
		pathsList = filteredContents;
	}

	std::vector<std::string> BGE_FileReader::readContent(std::string pathsList) {
		std::vector<std::string> contentsArray;
		std::stringstream pathsListStream;
		std::string tempPath;

		pathsListStream.str(pathsList);
		while (std::getline(pathsListStream, tempPath, '\n')) {
			std::ifstream fin{ tempPath };
			if (!fin) {
				std::cerr << "Failed to read file" << std::endl;
				fin.close();
				exit(EXIT_FAILURE);
			}
			std::string tempString;
			std::string tempContent;
			while (std::getline(fin, tempString, '\n')) {
				tempContent.append(tempString);
				tempContent.push_back('\n');
			}
			fin.close();
			contentsArray.push_back(tempContent);
		}

		return contentsArray;
	}
}