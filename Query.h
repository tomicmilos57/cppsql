#ifndef Query_h
#define Query_h

#include "Table.h"
#include <vector>
class Query{
	protected: 
		std::vector<std::string> tokens;
	public:
		Query(std::vector<std::string> tokens) : tokens(tokens){}
		void virtual execute(std::vector<Table> *tables){}
	protected:
		std::string lower(std::string str){
			for(int i = 0; i < str.size(); i++){
				str[i] = std::tolower(str[i]);
			}
			return str;
		}

};
#endif
