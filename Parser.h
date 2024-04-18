#ifndef Parser_h
#define Parser_h
#include "Query_Create.h"
#include "Query_Insert.h"
class Parser{
	public:
		Query* parse(std::string query){
			std::regex regex("^\\s*(\\w+).*");
			if ( regex_match(query, regex) ){
				//std::cout << "Query matches regex \n";
				std::smatch m;
				regex_search(query, m, regex);

				std::string operation = lower(m.str(1));
				//std::cout << lower(m.str(1)) << std::endl;
				if(lower(m.str(1)) == "create")return new Query_Create(query);
				if(lower(m.str(1)) == "insert")return new Query_Insert(query);
			}else{std::cout << "Query DOESN'T match regex \n";}
			return nullptr;//throw exception
		}

	private:
		std::string lower(std::string str){
			for(int i = 0; i < str.size(); i++){
				str[i] = std::tolower(str[i]);
			}
			return str;
		}
};
#endif
