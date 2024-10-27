#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <fstream>
#include <type_traits>

#include "BGE_FileReader.hpp"

namespace BGE {
	//Main method to list every file and directory in given path
	std::string BGE_FileReader::showContents(const char* primaryPath) {
		std::string temporaryContentStorage;
		for (const auto& path : std::filesystem::directory_iterator(primaryPath)) {
			temporaryContentStorage.append(path.path().string());
			temporaryContentStorage.push_back('\n');
		}

		return temporaryContentStorage;
	}

	//Filtering listed files and directories by mode
	//Mode = 0 - Only regular files
	//Mode = 1 - Only directories
	void BGE_FileReader::modeFilteredContent(std::string& pathsList, int mode) {
		std::string filteredContents;			//Variable for holding filtered paths
		std::stringstream pathsListStream;		//Variable for temporarly holding pathsList in stream
		std::string tempPath;					//Variable for holding value from first std::getline()

		pathsListStream.str(pathsList);
		//Go through every listed file, and filter it based on mode 
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

	//Filtering listed files by file extensions
	void BGE_FileReader::extensionFilteredContent(std::string& pathsList,const std::vector<std::string>& fileExtensions) {
		std::string filteredContents;
		std::stringstream pathsListStream;
		std::string tempPath;

		pathsListStream.str(pathsList);
		//Go through every every listed file, check if its file extension match any given file extension in std::vector of std::string
		//and filter it based on that
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

	//Reading content of every listed file and returning it as vector of string 
	//Every file content is 1 string 
	std::vector<std::string> BGE_FileReader::readContent(const std::string& pathsList) {
		std::vector<std::string> contentsArray;
		std::stringstream pathsListStream;
		std::string tempPath;

		pathsListStream.str(pathsList);
		// Go through every listed file in pathsList, open it, read it and save it to std::vector of std::strings 
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