#ifndef Query_Insert_h
#define Query_Insert_h

#include "Query.h"
#include <regex>
class Query_Insert : public Query {
	private:
		std::string tableName;
		std::vector<std::string> where_to_insert;
		std::vector<std::string> what_to_insert;
	public:
		Query_Insert(std::string query){
			std::regex reg("^\\s*[Ii][Nn][Ss][Ee][Rr][Tt]\\s*[Ii][Nn][Tt][Oo]\\s*(\\w+)\\s*\\(([^\\)]*)\\)\\s*[Vv][Aa][Ll][Uu][Ee][Ss]\\s*\\(([^\\)]*)\\);?$");
			if ( regex_match(query, reg) ){
				std::smatch m;
				regex_search(query, m, reg);

				//std::cout << "Table name " << m.str(1) << " " << std::endl;
				tableName = m.str(1);
				std::string temp = m.str(2);
				std::replace(temp.begin(), temp.end(), ',', ' ');
				std::regex subreg("(\\w+)");
				std::smatch submatch;
				while (regex_search(temp, submatch, subreg)){
					where_to_insert.push_back(submatch.str(1));
					temp = submatch.suffix();
				}
				temp = m.str(3);
				std::replace(temp.begin(), temp.end(), ',', ' ');
				while (regex_search(temp, submatch, subreg)){
					what_to_insert.push_back(submatch.str(1));
					temp = submatch.suffix();
				}
			}
		}
		void execute(std::vector<Table> *tables){
			Table* tablePointer = nullptr;
			for(Table& table : *tables){
				if(table.getName() == tableName){tablePointer = &table; break;}
			}
			if(tablePointer == nullptr) throw "There isn't table with name: " + tableName;
			try{tablePointer->insert_into(where_to_insert,what_to_insert);}
			catch(char const* errormessage) {std::cout << errormessage << std::endl;}
		}

};


#endif
