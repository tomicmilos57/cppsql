#ifndef Where_h
#define Where_h

#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
class Table;
class Where{
	public:
		virtual bool conditionTrue(std::vector<std::vector<std::string>> table, int row, const std::vector<std::string> columnName)const;
		virtual bool conditionTrue(std::vector<std::string> const & row, std::vector<std::string> const & columnName)const;
		void insertCondition(std::string col1, std::string sign, std::string col2);
		static Where read_where(int& i, const std::vector<std::string>& tokens, bool last);
		virtual void print();
		class Condition{
			public:
				std::string columnName;
				std::string value;
				virtual bool match(std::string originalValue) = 0;
				virtual bool match_eachother(std::string originalValue1, std::string originalValue2) = 0;
				virtual ~Condition(){};
		};
		class Equals : public Condition{
			public:
				bool match(std::string originalValue) override{
					return originalValue == value;
				}
				bool match_eachother(std::string originalValue1, std::string originalValue2) override{
					return originalValue1 == originalValue2;
				}
		};
		class NotEqual : public Condition{
			public:
				bool match(std::string originalValue) override{
					return originalValue != value;
				}
				bool match_eachother(std::string originalValue1, std::string originalValue2) override{
					return originalValue1 != originalValue2;
				}
		};
		void push_back(Condition* c){
			pairs.push_back(c);
		}
	private: 
		std::vector<Condition*> pairs;
		static std::string lower(std::string str);
		void dealocate();
};

class TrueWhere : public Where{
	bool conditionTrue(std::vector<std::vector<std::string>> table, int row, const std::vector<std::string> columnName)const override{return true;}
	void print()override{std::cout << "TRUE" << std::endl;}
};
#endif
