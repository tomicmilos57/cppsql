#include "Query_Create.h"
#include "Query_Insert.h"
#include <vector>

class Parser{
	public:
		Query* parse(std::vector<std::string> tokens){
			if(lower(tokens[0]) == "create")return new Query_Create(tokens);
			if(lower(tokens[0]) == "insert")return new Query_Insert(tokens);
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

