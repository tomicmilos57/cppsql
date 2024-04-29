#ifndef Query_Insert_h
#define Query_Insert_h

#include "Query.h"
#include <algorithm>
#include <regex>
class Query_Insert : public Query {
	private:
		std::string tableName;
		std::vector<std::string> where_to_insert;
		std::vector<std::string> what_to_insert;
	public:
		Query_Insert(std::vector<std::string> tokens_) : Query(tokens_){
			if(!(lower(tokens[0]) == "insert" && lower(tokens[1]) == "into")
					&& std::find_if(
						begin(tokens),
						end(tokens),
						[this](std::string obj){return obj == lower("values");}) 
					!= end(tokens))
				throw std::string("Wrong Fromat");
			tableName = tokens[2];
			int i = 3;
			for(; lower(tokens[i]) != "values"; i++){
				where_to_insert.push_back(tokens[i]);
			}
			i++;
			for(; i < tokens.size(); i++){
				what_to_insert.push_back(tokens[i]);
			}
			if(what_to_insert.size() != where_to_insert.size()) throw std::string("Wrong number of elements");
		}
		void execute(std::vector<Table> *tables){
			Table* tablePointer = nullptr;
			for(Table& table : *tables){
				if(table.getName() == tableName){tablePointer = &table; break;}
			}
			if(tablePointer == nullptr) throw "There isn't table with that name ";
			tablePointer->insert_into(where_to_insert,what_to_insert);
			//try{tablePointer->insert_into(where_to_insert,what_to_insert);}
			//catch(char const* errormessage) {std::cout << errormessage << std::endl;}
		}

};


#endif
