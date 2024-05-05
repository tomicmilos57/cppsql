#ifndef Where_h
#define Where_h

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
class Where{
	public:
		bool conditionTrue(std::vector<std::vector<std::string>> table, int row, const std::vector<std::string> columnName);
		static Where read_where(int& i, const std::vector<std::string>& tokens, bool last);
		void print();
		class Condition{
			public:
				std::string columnName;
				std::string value;
				virtual bool match(std::string originalValue) = 0;
		};
		class Equals : public Condition{
			public:
				bool match(std::string originalValue) override{
					return originalValue == value;
				}
		};
		class NotEqual : public Condition{
			public:
				bool match(std::string originalValue) override{
					return originalValue != value;
				}
		};
		void push_back(Condition* c){
			pairs.push_back(c);
		}
	private: 
		std::vector<Condition*> pairs;
		static std::string lower(std::string str);
};

#endif
