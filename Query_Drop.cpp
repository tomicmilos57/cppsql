#include "Query_Drop.h"
Query_Drop::Query_Drop(std::vector<std::string> tokens) : Query(tokens){
	if(!(lower(tokens.at(0)) == "drop" && lower(tokens.at(1)) == "table" && tokens.size() == 3)) throw std::string("Wrong Fromat");
	tableName = tokens.at(2);
}
void Query_Drop::execute(std::vector<Table> *tables){
	for(auto it = tables->begin(); it != tables->end(); ++it){
		if((*it).getName() == tableName){
			tables->erase(it);
			return;
		}
	}
	throw std::string("Nothing to remove");
}

