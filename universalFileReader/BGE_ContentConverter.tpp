#include <array>
#include <string>
#include <iostream>
#include <sstream>

namespace BGE {
    template<typename T, int rows, int columns>
    std::array<T, columns> BGE_ContentConverter<T, rows, columns>::BGE_stringToNumerical(const std::string& content) {
        std::array<T, columns> convertedValuesArray{};

        int mode;
        if (std::is_same<T, int>::value) {
            mode = 0;
        }
        else if (std::is_same <T, long>::value) {
            mode = 1;
        }
        else if (std::is_same<T, long long>::value) {
            mode = 2;
        }
        else if (std::is_same<T, float>::value) {
            mode = 3;
        }
        else if (std::is_same<T, double>::value) {
            mode = 4;
        }
        else if (std::is_same<T, long double>::value) {
            mode = 5;
        }
        else {
            std::cerr << "Given type is not supported" << std::endl;
            return convertedValuesArray;
        }

        std::string tempRowString;
        std::stringstream contentStream(content);
        int counter = 0;
        
        while (std::getline(contentStream, tempRowString, '\n')) {
            std::stringstream rowStream(tempRowString);
            std::string tempNumberString;
            while (std::getline(rowStream, tempNumberString, ' ')) {
                switch (mode) {
                case 0:
                    convertedValuesArray[counter] = std::stoi(tempNumberString);
                    break;
                case 1:
                    convertedValuesArray[counter] = std::stol(tempNumberString);
                    break;
                case 2:
                    convertedValuesArray[counter] = std::stoll(tempNumberString);
                    break;
                case 3:
                    convertedValuesArray[counter] = std::stof(tempNumberString);
                    break;
                case 4:
                    convertedValuesArray[counter] = std::stod(tempNumberString);
                    break;
                case 5:
                    convertedValuesArray[counter] = std::stold(tempNumberString);
                    break;
                }
                counter++;
            }
        }
        return convertedValuesArray;
    }

    template<typename T, int rows, int columns>
    std::array<std::array<T, columns>, rows> BGE_ContentConverter<T, rows, columns>::BGE_convertAll(const std::vector<std::string>& contentsList) {
        std::array<std::array<T, columns>, rows> listOfListsOfNumbers{};
        int i{ 0 };
        for (const std::string& content : contentsList) {
            listOfListsOfNumbers[i] = BGE_ContentConverter<T, rows, columns>::BGE_stringToNumerical(content);
            i++;
        }
        return listOfListsOfNumbers;
    }
}