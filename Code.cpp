#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;


void Trim(string& s)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s[i] == ' ' && s[i + 1] == ' ')
		{
			s.erase(i, 1);
			i--;
		}
	}
}

void EditNewLineCharacter(string& s)
{
	for (int i = 0 ; i<s.length() ;i++)
	{
		if (s[i] == '\n')
		{
			s[i]= ' ';
		}

		if (s[i] == ';' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' 
			|| s[i] == '>' || s[i] == '<' || s[i] == '(' || s[i] == ')' )
		{
			s.insert(i+1," ");
			s.insert(i," ");
			i+=2;
		}
		if(s[i] == '=')
		{
			if(s[i-1] == ':')
			{
				s.insert(i+1," ");
				s.insert(i-1," ");
				i+=2;
			}
			else
			{
				s.insert(i+1," ");
				s.insert(i," ");
				i+=2;
			}
		}
	}
}

void RemoveComments(string& s)
{
	int end ;
	for (int i = 0 ; i<s.length() ;i++)
	{
		if(s[i] == '{')
		{
			end = i;
			while(s[end] != '}')
			{
				end++;
			}
			s.erase(i ,end-i+1);
			i--;
		}
		
	}
}

void split(string &s , vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, ' ')) {
        elems.push_back(item);
    }
}


bool checkReservedWord(string word)
{
	string ReservedWords[8] ={"if" ,"then","else","end","repeat","until" ,"read","write"};
	for(int i = 0 ; i<8; i++)
	{
		if(word == ReservedWords[i])
			return 1 ;
	}
	return 0 ;
}

string checkSpecialSymbols(string word)
{
	if(word == "+")
		return "Plus";

	else if (word == "-")
		return "Minus";

	else if (word == "*")
		return "Asterisk";

	else if (word == "/")
		return "Slash";

	else if (word == "=")
		return "Equal sign";

	else if (word == ">")
		return "Greater than";

	else if (word == "<")
		return "Less than";

	else if (word == "(")
		return "Minus";

	else if (word == ")")
		return "Minus";

	else if (word == ";")
		return "Semicolon";

	else if (word == ":=")
		return "assign";

	else
		return "none";
}

bool IsNumber(string word)
{
	int i =0 ;
	while(isdigit(word[i])) 
		i++;
	if (i>0)
		return 1;
	return 0;
}

int main()
{
	vector<string> words ;
	ifstream ip ("input.txt");
	ofstream op ("output.csv");
	string txtIp((istreambuf_iterator<char>(ip)),istreambuf_iterator<char>());
	RemoveComments(txtIp);
	EditNewLineCharacter(txtIp);
	Trim(txtIp);
	split(txtIp,words);
	op <<"Token Value ,Token Type ,Details \n" ;
	for(int i =0 ; i<words.size() ;i++)
	{		
		if(checkReservedWord(words[i]))
			op << words[i] <<", Reserved Word \n" ;

		else if(checkSpecialSymbols(words[i]) != "none")
			op << words[i] <<", Special Symbol, "<< checkSpecialSymbols(words[i]) << endl;

		else if (IsNumber(words[i]))
			op << words[i] << ", Number \n" ;
		else
			op << words[i] << ", Identifier \n";

	}
	cout<<"Check output.csv \n";
	system("pause");
	return 0;
}