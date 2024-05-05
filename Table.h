#ifndef Table_h
#define Table_h

#include "Where.h"
#include "Set.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <map>
class Table{
	private:
		std::string name;
		std::vector<std::string> columns_name;
		std::vector<std::vector<std::string>> table;
		int size = 0;
	public:
		Table(std::string name, std::vector<std::string>& columns_name);

		std::string getName(){return name;}
		void save(std::ofstream& os);
		Table(std::ifstream& os);
		void print_Table();
		void insert_into(std::vector<std::string> where_to_insert, std::vector<std::string> what_to_insert);
		void update(Set& set, Where& where);
		void select(std::vector<std::string> columnsToSelect, Where& where) const;
		void _delete(Where& where);
		/*
		   ~Table(){
		   std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
		   delete this->table[s];
		   });
		   }*/
};
#endif
