#include "Query_Create.h"
#include "Query_Insert.h"
#include "Query_Drop.h"
#include "Query_Update.h"
#include "Query_Select.h"
#include "Query_Delete.h"
#include <stdexcept>
#include <vector>

class Parser{
	public:
		Query* parse(std::vector<std::string> tokens){
			Query* query;
			try{
			if(lower(tokens[0]) == "create")return query = new Query_Create(tokens);
			if(lower(tokens[0]) == "insert")return query =new Query_Insert(tokens);
			if(lower(tokens[0]) == "drop")return query =new Query_Drop(tokens);
			if(lower(tokens[0]) == "update")return query =new Query_Update(tokens);
			if(lower(tokens[0]) == "select")return query =new Query_Select(tokens);
			if(lower(tokens[0]) == "delete")return query =new Query_Delete(tokens);
			}catch(const std::out_of_range& e){
				std::cout << "Can't pass the query" << std::endl;
				//delete query;
			}
			throw std::string("Unknown Instruction");
		}

	private:
		std::string lower(std::string str){
			for(int i = 0; i < str.size(); i++){
				str[i] = std::tolower(str[i]);
			}
			return str;
		}
};

