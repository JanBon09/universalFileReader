#pragma once 

#include <string>
#include <vector>

namespace BGE{
	template<typename T, int rows, int columns>
	class BGE_ContentConverter {
	public:
		static std::array<T, columns> BGE_stringToNumerical(const std::string&);
		static std::array<std::array<T, columns>, rows> BGE_convertAll(const std::vector<std::string>&);
	};
}
#include "BGE_ContentConverter.tpp"