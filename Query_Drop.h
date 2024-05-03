#ifndef Query_Drop_h
#define Query_Drop_h

#include "Query.h"
#include <algorithm>
#include <string>
#include <vector>
#include <iostream> //delete later
#include <regex>
class Query_Drop : public Query{
	private:
		std::string tableName;
	public:
		Query_Drop(std::vector<std::string> tokens) : Query(tokens){
			if(!(lower(tokens[0]) == "drop" && lower(tokens[1]) == "table" && tokens.size() == 3)) throw std::string("Wrong Fromat");
			tableName = tokens[2];
		}
		void execute(std::vector<Table> *tables){
			for(auto it = tables->begin(); it != tables->end(); ++it){
				if((*it).getName() == tableName){
					tables->erase(it);
					return;
				}
			}
			throw std::string("Nothing to remove");
			//tables[tableName].drop
		}
};
#endif
