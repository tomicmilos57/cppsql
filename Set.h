#ifndef Set_h
#define Set_h
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
class Set{
	public:
		void set(std::vector<std::vector<std::string>*> table, int row, const std::vector<std::string> columnName){
			for(auto pair : pairs){
				int i = 0;
				for(; i < columnName.size(); i++){//finding the index of a column
					if(columnName[i] == pair->columnName) break;
				}
				if(i == columnName.size()) throw std::string("Cannot find the column");
				(*table[i])[row] = pair->value;
			}
		}
		void print(){
			//std::for_each(pairs.begin(), pairs.end(), [](ChangeTo c){std::cout << c.columnName << " " << c.value << std::endl;});
			for(ChangeTo* c : pairs){
				std::cout << c->columnName << " " << c->value << std::endl;
			}
		}
		struct ChangeTo{
			std::string columnName;
			std::string value;
		};
		void push_back(ChangeTo* change){
			pairs.push_back(change);
		}
	private:
		std::vector<ChangeTo*> pairs;
};

#endif
