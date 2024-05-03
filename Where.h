#ifndef Where_h
#define Where_h

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
class Where{
	public:
		bool conditionTrue(std::vector<std::vector<std::string>*> table, int row, const std::vector<std::string> columnName){
			bool condition = true;
			for(auto pair : pairs){
				int i = 0;
				for(; i < columnName.size(); i++){//finding the index of a column
					if(columnName[i] == pair->columnName) break;
				}
				if(i == columnName.size()) throw std::string("Cannot find the column " + pair->columnName);
				if(!pair->match((*table[i])[row])){
					condition = false;
					break;
				}
			}
			return condition;
		}
		void print(){
			//std::for_each(pairs.begin(), pairs.end(), [](Condition* c){std::cout << c->columnName << " " << c->value << std::endl;});
			for(Condition* c : pairs){
				std::cout << c->columnName << " " << c->value << std::endl;
			}
		}
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
};

#endif
