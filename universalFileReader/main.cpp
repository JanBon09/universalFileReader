#include "BGE_FileReader.hpp"
#include "BGE_ContentConverter.hpp"

#include <filesystem>
#include <iostream>
#include <array>
#include <chrono>

int main() {
	//Testing code

	auto start = std::chrono::high_resolution_clock::now();

	const char* path = "C:\\example";
	std::string paths;

	paths = BGE::BGE_FileReader::showContents(path);

	BGE::BGE_FileReader::modeFilteredContent(paths, 0);

	std::vector<std::string> extension{ ".txt" };

	BGE::BGE_FileReader::extensionFilteredContent(paths, extension);

	std::vector<std::string> contents = BGE::BGE_FileReader::readContent(paths);

	std::array<std::array<float, 12>, 2> ar{};
	ar = BGE::BGE_ContentConverter<float, 2, 12>::BGE_convertAll(contents);
	std::cout << ar.size() << std::endl;
	for (const auto& rows : ar) {
		for (const auto& element : rows) {
			std::cout << element << ' ';
		}
		std::cout << std::endl << std::endl;
	}

	auto end = std::chrono::high_resolution_clock::now();

	double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

	time_taken *= 1e-9;

	std::cout << "Time taken by program is: " << std::fixed << time_taken
		<< std::setprecision(9) << " sec" << std::endl;

	return 0;
}