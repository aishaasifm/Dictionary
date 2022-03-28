/*
 *
 * File: Dictionary.cpp
 * By: Aisha Asif & Michael Chang 
 * Date: 05/14/2022
 *
 * Description: this code allows the user to use a credit card! 
 *
 */

#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

bool isvalidcc(const string&);

int main()
{
	//
	// PLEASE DO NOT CHANGE function main
	//
	vector<string> cardnumbers = {
		 "371449635398431", "4444444444444448", "4444424444444440", "4110144110144115",
		"4114360123456785", "4061724061724061", "5500005555555559", "5115915115915118",
		"5555555555555557", "6011016011016011", "372449635398431", "4444544444444448",
		"4444434444444440", "4110145110144115", "4124360123456785", "4062724061724061",
		"5501005555555559", "5125915115915118", "5556555555555557", "6011116011016011",
		 "372449635397431", "4444544444444448", "4444434444544440", "4110145110184115",
		"4124360123457785", "4062724061724061", "5541005555555559", "5125115115915118",
		"5556551555555557", "6011316011016011"
	};

	int i;
	vector<string>::iterator itr;

	for (i = 1, itr = cardnumbers.begin(); itr != cardnumbers.end(); ++itr, i++) {
		cout << setw(2)  << i << " " 
			 << setw(17) << *itr 
			 << ((isvalidcc(*itr)) ? " is valid" : " is not valid\n");
	}

	return 0;
}

//this will go through all of the list of vectors and look for values that are 4, 5, 6, 37

bool isvalidcc(const string& string){
	int oneDigit;
	int oddDigit;
	int total(0);
	if (string.length() < 13 || string.length() > 16){}
	if(!(string [0] == '4' || string [0] == '5' || string [0] == '6' || string.substr (0, 2) == "37")) 
	{  return false; }
oneDigit = doubleDigit(string);
oddDigit = unevenDigit(string);
total = oddDigit + oneDigit;

if(total%10 != 0)
{ return false;}
return true; 
}

int doubleDigit (string value){
	int total = 0; 
	for(int i =value.length() - 1; i >= 0; i -= 2){
		total += value[i] - '0';
	}
return total;
}

int unevenDigit(string value){
	int total = 0; 
	for (int i = value.length() - 2; i >= 0; i -= 2){
		int num = (value[i] - '0') * 2;
		if(num > 9){
			num = num/10 + num%10;
		}
		total += num;
	}
	return total;
}