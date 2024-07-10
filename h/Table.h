#ifndef Table_h
#define Table_h

#include "Where.h"
#include "Set.h"
#include <fstream>
#include <iomanip>//needed for stringstream
#include <iostream>
#include <string>
#include <vector>
class Table{
	private:
		std::string name;
		std::vector<std::string> columns_name;
		std::vector<std::vector<std::string>> table;
		int size = 0;
	public:
		Table(std::string name, std::vector<std::string> const & columns_name);
		Table(std::ifstream& os);//for reading savefile
		Table(Table const & t1, Table const & t2, std::string abbr1, std::string abbr2, Where const & viewWhere);//for inner join
		std::string getName()const{return name;}
		void save(std::ofstream& os)const;
		void save_sql(std::ofstream& os)const;
		void print_Table() const;
		void insert_into(std::vector<std::string> const & where_to_insert, std::vector<std::string> const & what_to_insert);
		void update(Set& set, Where& where);
		void select(std::vector<std::string> const & columnsToSelect, Where const & where) const;
		static void innerjoin(Table const & Table1, Table const & Table2, std::vector<std::string> const & columns,
				std::string abbreviation1, std::string abbreviation2, Where& viewWhere, Where& where);
		void _delete(Where const & where);
		/*
		   ~Table(){
		   std::for_each(this->columns_name.begin(), this->columns_name.end(),[this](std::string s){
		   delete this->table[s];
		   });
		   }*/
	private:
		static void print_columns(std::ostream& os, std::vector<std::string>const & columns_name, std::string const & name);
};
#endif
