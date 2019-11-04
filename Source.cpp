#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include<stdlib.h>
#include<sstream>
#include<vector>
#include<algorithm>
#pragma warning(disable : 4996)

using namespace std;
int main() {
	vector<string> data;
	
	cout << "! Opening data file... ./Data.CS.SFSU.txt\n";
	ifstream fin("Data.CS.SFSU.txt");

	cout << "! Loading data...\n";
	
	string s;
	while (getline(fin, s)) {
		data.push_back(s);
	}
	
	cout << "! Loading completed...\n";
	fin.close();
	cout << "! Closing data file... ./Data.CS.SFSU.txt\n";
	cout << "-----DICTIONARY 340 C++-----\n";

	vector<string> keywords;
	
	for (vector<string>::iterator itr = data.begin(); itr != data.end(); itr++)
	{
		string keyword;
		string pos;
		string def;
		string temp;
		string temp2;
		for (int i = 0; i < (*itr).length(); i++)
		{
			char c = (*itr)[i];

			if (c != '|')
				temp.push_back(c);
			
			if (c == '|') {
				keywords.push_back(temp);
				//cout << temp << endl;
				break;
				
			}
		}
	
	}

	/*for (vector<string>::iterator itr = keywords.begin(); itr != keywords.end(); itr++)
	{
		cout << *itr << endl;
	}*/


	string input;
	
	while (true)
	{
		
		cout << endl<<"Search: ";
		getline(cin, input);
		for (int i = 0; i < input.length(); i++)
		{
			input[i] = tolower(input[i]);
		}
		//cout << endl << "|" << endl;
		if (input == "!q")
		{
			cout << "-----THANK YOU-----" << endl;
			break;
		}
		stringstream ss{ input };
		string keyinput;
		string filter1;
		string filter2;
		ss >> keyinput>>filter1>>filter2;
		
		bool wordmatch = false;
		bool posmatch = false;
		int count = 0;
		
		for (int i = 0; i < data.size(); i++)
		{
			
			if (keyinput == keywords[i])
			{
				wordmatch = true;
				
				string key = keywords[i];
				string partofspeech;
				string def;
				vector<string>pos;
				vector<string>definitions;
				vector<string>finalresult;
				vector<string>onefilter;
				vector<string>twofilter;
				
				bool add = false;
				for (int j = 0; j < data[i].length(); j++)
				{
					char t = data[i].at(j);
					if (t == '.') { partofspeech = ""; }
					if (t == ' ' && add) { 
						add = false; 	
							pos.push_back(partofspeech);	
					}
						
					if (add){
						partofspeech.push_back(t); 
					}
					if (t == '|') { add = true; }
				}
				bool add2 = false;
				for (int j = 0; j <data[i].length(); j++)
				{
					char t = data[i].at(j);
					
					if (t == '|' && add2)
					{
						definitions.push_back(def);
						add2 = false;
						def = "";
					}
					if (t == '.' && add2 && j==data[i].length()-1 ) {
							definitions.push_back(def);
							add2 = false;
							def = "";
					}
					if (add2 && t!='|') { def.push_back(t); }
                    if (t == '>') { add2 = true; j++; }
				}
				for (int i = 0; i < pos.size(); i++)
				{

					if (filter1 != "" && pos[i] == filter1) {

						string s = key + "[" + pos[i] + "]:" + definitions[i];
						onefilter.push_back(s);
						posmatch = true;
					}
					if (filter1 == "" || filter1 == "distinct")
					{


						string s = key + "[" + pos[i] + "]:" + definitions[i];

						finalresult.push_back(s);
					}

				}
				sort(onefilter.begin(), onefilter.end());
				sort(finalresult.begin(), finalresult.end());
				if (filter1 != "") 
				{
					if (filter1 == "distinct")
					{
						vector<string>::iterator ip;
						ip = unique(finalresult.begin(), finalresult.end());
						finalresult.resize(distance(finalresult.begin(), ip));
						cout << endl << "|" << endl;
						for (int i = 0; i < finalresult.size(); i++)
						{

							cout << "  " << finalresult[i] << endl;

						}
					}
					if (filter2 == "")
					{
						cout << endl << "|" << endl;
						for (int i = 0; i < onefilter.size(); i++)
						{

							cout << "  " << onefilter[i] << endl;

						}
					}
					else if (filter2 == "distinct")
					{
						vector<string>::iterator ip;
						ip = unique(onefilter.begin(), onefilter.end());
						onefilter.resize(distance(onefilter.begin(), ip));
						cout << endl << "|" << endl;
						for (int i = 0; i < onefilter.size(); i++)
						{

							cout << "  " << onefilter[i] << endl;

						}
					}
					if(posmatch)
					cout << "|" << endl;
				}
                else if (filter1 == "")
				{
					if (filter2 == "") {
						cout << endl << "|" << endl;
						for (int i = 0; i < finalresult.size(); i++)
						{
							cout << "  " << finalresult[i] << endl;

						}
						cout << "|" << endl;
					}
					else if (filter2 == "distinct")
					{
						vector<string>::iterator ip;
						ip = unique(finalresult.begin(), finalresult.end());
						finalresult.resize(distance(finalresult.begin(), ip));
						cout << endl << "|" << endl;
						for (int i = 0; i < finalresult.size(); i++)
						{

							cout << "  " << finalresult[i] << endl;

						}
						cout << "|" << endl;
					}
				}
			}
			count++;
             if(count==data.size())
			{
				if (!wordmatch)
					cout <<endl<<"|"<<endl<<"<not found!>" << endl << "|"<<endl;
				else if(!posmatch && filter1 != "" && filter1 != "distinct" && filter1 != "noun" && filter1 != "verb" && filter1 != "adjective" && filter1 != "preposition" && filter1 != "adverb" &&
					filter1 != "conjunction" && filter1 != "interjection" && filter1 != "pronoun")
					{
					cout << "<2nd arguement must be a part of speeech or distinct>" << endl << "|"<<endl;
				    }
				else if(!posmatch && filter1!="" && filter1!="distinct" )
					cout << "<not found>" << endl << "|"<<endl;
			}	
		}	 
	}
		return 0;
}