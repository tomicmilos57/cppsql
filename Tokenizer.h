#ifndef Tokenizer_h
#define Tokenizer_h
#include "Query_Create.h"
#include "Query_Insert.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>


class Tokenizer{
	public:
		std::vector<std::string> tokenize(const std::string& query) {
			if(query == "") throw std::string("Empty Query");
			std::vector<std::string> tokens;
			std::istringstream iss(query);
			std::string token;
			while (iss >> token) {
				std::string cleanedToken;
				for (char c : token) {
					if (c == '(' || c == ')' || c == ',' || c == ';') {
						if (!cleanedToken.empty()) {
							tokens.push_back(cleanedToken);
							cleanedToken.clear();
						}
						tokens.push_back(std::string(1, c));
					} else {
						cleanedToken += c;
					}
				}
				if (!cleanedToken.empty()) {
					tokens.push_back(cleanedToken);
				}
			}
			return tokens;
		}
};
#endif
