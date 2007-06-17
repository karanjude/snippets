#include "stdafx.h"
#include <map>
#include <algorithm>
#include <vector>
#include <queue>
#include <sstream>
#include <string>
#include <cctype>

#include <utility.cpp>

using namespace std;

class SymbolFrequency{
	
	vector<map<char,int>> tables;
	map<char,int> text_table;

	map<char,int> build_table(string table_string){
		map<char,int> table;
		for(int i = 0; i < table_string.length(); i++){
			char _char = table_string[i++];
			int ten = table_string[i++] - '0';
			int unit = table_string[i] - '0';
			int percent = 10 * ten + unit;
			table.insert(make_pair(_char,percent));
		}
		return table;
	}

	void build_tables(vector<string> frequencies){
		for(int i = 0; i < frequencies.size(); i++){
			map<char,int> table = build_table(frequencies[i]);
			tables.push_back(table);
		}
	}
	
	int find_actual_count(string s,char c){
		int r = 0;
		for(int i = 0;i < s.length();i++){
			if(s.at(i) == c)
				r++;
		}
		return r;
	}

	void build_text_table(string text){
		for(int i = 0; i < text.length(); i++){
			if(text_table.count(text[i]) == 0){
				text_table.insert(make_pair(text[i], find_actual_count(text,text[i])));
			}
		}
	}

	double find_actual_frequency(char c){
		double result = 0.0;
		if(text_table.count(c)){
			result = text_table.find(c)->second;
		}
		return result;
	}

	double find_deviation(int lang_index , string text){
		map<char,int>::iterator ii ;
		double sum = 0.0;
		double expected = 0.0;
		double actual = 0.0;
		double deviation = 0.0;
		for(ii = tables[lang_index].begin();ii != tables[lang_index].end(); ii++){
			char _char = ii->first;
			expected = (double) (text.length()) * ((double)ii->second / (double)100);
			actual = find_actual_frequency(_char);
			deviation = expected - actual;
			deviation = deviation * deviation;
			sum += deviation;
		}
		for(ii = text_table.begin(); ii != text_table.end();ii++){
			if(tables[lang_index].count(ii->first) == 0){
				expected = 0.0;
				actual = ii->second;
				deviation = expected - actual;
				deviation = deviation * deviation;
				sum += deviation;
			}
		}

		return sum;
	}


	string trim_string_off_white_spaces(vector<string> text){
		string result = "";
		for(int i = 0;i < text.size(); i++){
			string s = "";
			for(int j = 0;j < text[i].length(); j++){
				if(!isspace(text[i].at(j)))
					s += tolower(text[i].at(j));
			}
			result += s;
		}
		return result;
	}

	void initialize(){
		tables.clear();
		text_table.clear();
	}
public:
	double language(vector <string> frequencies, vector <string> text){
		initialize();
		string s = trim_string_off_white_spaces(text);	
		build_tables(frequencies);
		build_text_table(s);
		double deviation = 10000000;
		for(int i = 0; i < frequencies.size();i++)
			deviation = min(deviation,find_deviation(i,s));
		return deviation;
	}
};

int _tmain(int argc, _TCHAR* argv[]){
	SymbolFrequency s;

	string f[] =  {"a30b30c40","a20b40c40"} ;
	string t[] = {"aa bbbb cccc"};
	are_equal_with_print<double>(0.0, s.language(to_vector<string,2>(f),to_vector<string,1>(t)));

	string f1[] =  {"a30b30c40","a20b40c40"};
	string t1[] = {"aaa bbbb ccc"};
	are_equal_with_print<double>(2.0, s.language(to_vector<string,2>(f1),to_vector<string,1>(t1)));

	string f2[] =  {"a10b10c10d10e10f50"};
	string t2[] = {"abcde g"};
	are_equal_with_print<double>(10.8, s.language(to_vector<string,1>(f2),to_vector<string,1>(t2)));

	string f3[] =  {"a09b01c03d05e20g01h01i08l06n08o06r07s09t08u07x01"
,"a14b02c05d06e15g01h01i07l05n07o10r08s09t05u04x01"};
	string t3[] = {"this text is in english" 
,"the letter counts should be close to"
,"that in the table"};
	are_equal_with_print<double>(130.6578, s.language(to_vector<string,2>(f3),to_vector<string,3>(t3)));

string f4[] =  
	{"a09b01c03d05e20g01h01i08l06n08o06r07s09t08u07x01"
,"a14b02c05d06e15g01h01i07l05n07o10r08s09t05u04x01"};
	string t4[] = {"en esta es una oracion en castellano"
,"las ocurrencias de cada letra"
,"deberian ser cercanas a las dadas en la tabla"};
	are_equal_with_print<double>(114.9472, s.language(to_vector<string,2>(f4),to_vector<string,3>(t4)));

	string f5[] =  
	{"z99y01", "z99y01", "z99y01", "z99y01", "z99y01", 
 "z99y01", "z99y01", "z99y01", "z99y01", "z99y01"};
	string t5[] ={"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",
 "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};
	are_equal_with_print<double>(495050.0, s.language(to_vector<string,10>(f5),to_vector<string,10>(t5)));


	int ii;
	cin >> ii;
	return 0;
}