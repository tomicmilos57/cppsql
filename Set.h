#ifndef Set_h
#define Set_h
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
class Set{
	public:
		void set(std::vector<std::vector<std::string>>& table, int row, const std::vector<std::string> columnName);
		void print();
		struct ChangeTo{
			std::string columnName;
			std::string value;
		};
		void push_back(ChangeTo* change);
		static Set read_set(int& i, std::string delim, const std::vector<std::string>& tokens, bool last);
	private:
		std::vector<ChangeTo*> pairs;
		static std::string lower(std::string str);
};

#endif
