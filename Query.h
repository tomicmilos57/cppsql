#ifndef Query_h
#define Query_h

#include "Table.h"
#include <vector>
class Query{
	public:
		Query(){
		}
		void virtual execute(std::vector<Table> *tables){}
};
#endif
