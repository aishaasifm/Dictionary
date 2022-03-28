/*
 *
 * File: Dictionary.cpp
 * By: Aisha Asif & Michael Chang 
 * Date: 05/14/2022
 *
 * Description: this code allows the user to search up a word and print out the part of speech and definitions.
 *  you are also able to revers how the definiions are printed and search it by the noun.
 *
 */

#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
#include<sstream>
using namespace std;

bool isanum(string&);
vector<string> textEnty (string&);
 
class Libary {           // this class allows the user to separet the text file into three sections the word, pos and definistions.                                                                   
    private:
        string words;
        string speech;
        string definition;

    public:
        Libary(string word, string pos, string def) {
            words = word;
            speech = pos;
            definition = def;
        }
        string getWord() {
            return words;
        }
        string getPos() {
            return speech;
        }
        string getDef() {
            return definition;
        }
        void setWord(string data) {
            words = data;
        }
        void setPos(string data) {
            speech = data;
        }
        void setDef(string data) {
            definition = data;
        }
        string toString() {              // a tostring tha puts all three parameters in to one string that shows the word, pos and definition.                                               
            string text = words;                                                               
            if(isanum(text) == true) {
                for(auto& data: text) {
                    data = toupper(data);
                }
            }
            text[0] = toupper(text[0]);// this capatalizes the first word of the string
            return text + " [" + speech + "] : " +definition;
        }
        bool operator > (const Libary& str) const {                                         
            return (speech < str.speech);
        }
        bool operator==(const Libary& str) const {                                         
            if(speech != str.speech || definition != str.definition) {
                return false;
            }
            return true;
        }       
};

vector<string> Keywordss;
vector<Libary> sort(vector<Libary> lib, vector<string> words);
void search(vector<Libary> lib, vector<string> words);
vector<Libary> part_of_speech(string, vector<Libary>);
vector<Libary> distinct (vector<Libary>);
vector<Libary> reverse (vector<Libary>);
vector<string> pos = {"noun", "verb", "adjective", "adverb", "pronoun", "preposition", "conjunction", "interjection"};

int main(){
    bool opened(true);
    string opened_file("./Data.CS.SFSU.txt");
    ifstream fileHandle(opened_file);
    vector<Libary> lib;
    vector<string> words;

   lib =  sort(lib, words);
   words = Keywordss;
    cout << "! Closing data file..." << opened_file<< endl;
    fileHandle.close();
    cout << "====== Libary 340 C++ ===== " << endl;
    cout << "------ Keywords: " << words.size() << endl; // tells user the number of keywords
    cout << "------ Definitions: " << lib.size() << endl << endl; // tells users the number of definitions
    
    search(lib, words);
   
    return 0;
}

bool isanum(string& str) {    /// checks the string for any numbers that were inputed                                       
    return any_of(str.begin(), str.end(), ::isdigit); 
}

vector<string> textEnty (string& str) {  // makes the entries made and seperates them                                             
    vector<string> entry;
    string pull;
    stringstream seperate(str);
    while (getline(seperate, pull, ' ')){
		entry.push_back(pull);
	}
 
    return entry;
}

vector<Libary> part_of_speech(string partsOfSpeech, vector<Libary> data) {  // allows the user to search only one type of Part of speech and returns that part of speech    
    vector<Libary> pos;
    for(Libary i : data) {                                                                     
        if(i.getPos() == partsOfSpeech) {                                              
            pos.push_back(i);
        }
    }
    return pos;
}

vector<Libary> distinct (vector<Libary> data) {   // gets rid of the multiples of the same deffintion and only shows one output for the multiples                               
    vector<Libary> doup = data;
    bool multi(false);
    if(doup.size() > 1){
        doup.erase(unique(doup.begin(), doup.end()), doup.end());

    }
    return doup;
}

vector<Libary> reverse(vector<Libary> data) {     //reverses the order definitions from bottom to top                                  
    vector<Libary> reverse;
    for(int i = data.size() - 1 ; i >= 0; i--) {                                                 
        reverse.push_back(data[i]);                                                                
    }
    return reverse;
}

vector<Libary> sort(vector<Libary> lib, vector<string> words){
  bool opened(true);
    string opened_file("./Data.CS.SFSU.txt");
    ifstream fileHandle(opened_file);
    vector<Libary> libb = lib;
    vector<string> text = words;
  while( opened){
       ifstream fin(opened_file);
        string line;
        if(fileHandle.is_open()){
            cout << "! Opening data file... " << opened_file << endl;
            cout << "! Loading data..." << endl;

            while(getline(fileHandle, line)){   //goes through the library vector and sees how many keywords are there and also how many definitions
                int spliter(line.find_first_of("|"));   // by looking at the | that seperates the word from the nouns and the -=>> that seperartes the definistions from the nouns 
                int pointer(line.find_first_of("-=>>"));
                string word(line.substr(0, spliter));
                text.push_back(word);
                string pos;
                string def;
                line.erase(0, spliter+1 );
                bool runs = true;
                while(runs){
                    spliter = line.find_first_of("|");
                    pointer = line.find_first_of("-=>>");
                    if(spliter == -1){
                        pos = line.substr(0, pointer - 1);
                        line.erase(0, pointer + 5);
                        def = line;
                        Libary pull(word, pos, def);
                        libb.push_back(pull); // puts all the inputs from the txt into vectors and separates them.
                        break;
                    }else{
                        pos = line.substr(0, pointer - 1);
                        line.erase(0, pointer + 5);
                        spliter = line.find_first_of("|");
                        def = line.substr(0, spliter);
                        line.erase(0, spliter + 1);
                        Libary pull(word, pos, def);
                        libb.push_back(pull);
                        
                    } 
                }
             
            }
             break;
        }else{
            cout << "<!>ERROR<!> ===> File could not be opened." << endl;
            cout << "<!>ERROR<!> ===> Provided file path:" << opened_file <<endl;
            cout << "<!>Enter the CORRECT data file path:";
            cin >> opened_file;
        }
    }
  Keywordss = text;
  return libb ;
}


void search(vector<Libary> lib, vector<string> words){
    bool runs(true);
    int count(0);
    
    vector<string> text = words;
    while(runs){
        string user_entry;
        vector<string> entry;
        bool pos(false);
        bool pas(false);
        count++; // increases the number count for the search as more words are searched the count increaeses 
        sort(lib.begin(), lib.end(), greater<Libary>());
        cout << "Search [" << count << "] :";

        getline(cin, user_entry);   
                                                                   
        for(auto& c: user_entry){                                                                        
            c = tolower(c);
        }
        entry = textEnty(user_entry);                                                       

        cout << "      |" << endl;
        if(entry[0] == "!help" || entry[0] == "" ) {  // helps the user with the params that are need to find specific words             
            cout << "      PARAMETER HOW-TO, please enter:" << "\n"
                << "      1. A search key -then 2. An optional part of speech -then" << "\n" 
                << "      3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
           pas = true;
        } else if(entry[0] == "!q" || entry[0] == "!Q") {                                    
            cout << endl << "-----THANK YOU-----" << endl;
            break;
        }
        

        vector<Libary> pull = lib;                                                         
        if(entry.size() == 1) {   

            if (find(text.begin(), text.end(), entry[0]) != text.end()) {                  
                for(Libary i : pull){                                                     
                    if(i.getWord() == entry[0]) {
                        cout << "   " <<  i.toString() << "\n";
                    }
                }
            }else{
              if(pas == false ){//letts the user know if the word they types is not there
                cout << "      <NOT FOUND> To be considered for the next release. Thank you." << endl;
                cout << "      |" <<endl;
                cout << "      |" <<endl;
                cout << "      PARAMETER HOW-TO, please enter:" << "\n"
                << "      1. A search key -then 2. An optional part of speech -then" << "\n" 
                << "      3. An optional 'distinct' -then 4. An optional 'reverse'" << endl;
              }
                
            }
        }
        if(entry.size() == 2){ // call the  parameter weather it be either the part of speech or reverse or distinct 
            if(entry[1] == "distinct"){// checks to see if the user inputs distinct as a pram
                pull = distinct(pull);
            }
            if( entry[1] == "reverse"){// checks to see if the user inputs reverse as a pram
                pull = reverse(pull);
            }
            if(find(entry.begin(), entry.end(), entry[1]) != entry.end() && entry[1] != "distinct" && entry[1] != "reverse"){
                pos = true;
                pull = part_of_speech(entry[1], pull);
            }
            if(entry[1] != "distinct" && entry[1] != "reverse" && pos == false){
                cout << "      <The entered 2nd parameter " << "'" << entry[1] << "' is NOT a part of speech.>" << endl;
                cout << "      <The entered 2nd parameter " << "'" << entry[1] << "' is NOT 'distinct'.>" << endl;
                cout << "      <The entered 2nd parameter " << "'" << entry[1] << "' is NOT 'reverse'.>" << endl;
                cout << "      <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
            }
            for(Libary i: pull){
                if(i.getWord() == entry[0]){
                    cout << "      " << i.toString() << "\n";
                }
            }
        }
        if(entry.size() == 3){  // allows the user to call both the pos and the reverse or the distinct 
            if(entry[2] == "distinct" || entry[1] == "distinct"){
                pull = distinct(pull);
            }
            if( entry[2] == "reverse" || entry[1] == "reverse"){
                pull = reverse(pull);
            }
            if(find(entry.begin(), entry.end(), entry[1]) != entry.end() && entry[1] != "distinct" && entry[1] != "reverse"){
                pos = true;
                pull = part_of_speech(entry[1], pull);
            }if(entry[1] != "distinct" && entry[1] != "reverse" && pos == false){
                cout << "      <The entered 2nd parameter " << "'" << entry[1] << "' is NOT a part of speech.>" << endl;
                cout << "      <The entered 2nd parameter " << "'" << entry[1] << "' is NOT 'distinct'.>" << endl;
                cout << "      <The entered 2nd parameter " << "'" << entry[1] << "' is NOT 'reverse'.>" << endl;
                cout << "      <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
            }if (entry[2] != "distinct" && entry[2] != "reverse"){
               cout << "      <The entered 3rd parameter " << "'" << entry[2] << "' is NOT 'distinct'.>" << endl;
                cout << "      <The entered 3rd parameter " << "'" << entry[2] << "' is NOT 'reverse'.>" << endl;
                cout << "      <The 3rd parameter should be 'distinct' or 'reverse'.> " << endl;
            }
            
            for(Libary i: pull){
                if(i.getWord() == entry[0]){
                    cout << "      " << i.toString() << "\n";
                }
            }
        }
        if(entry.size() == 4 ){ // allows the user to call both the pos and the reverse or the distinct  and the last param as reverse 
            if(entry[1] == "distinct" || entry[2] == "distinct"){
                pull = distinct(pull);
            }
            if( entry[1] == "reverse" || entry[2] == "reverse" || entry[3] == "reverse"){
                pull = reverse(pull);
            }
            if(find(entry.begin(), entry.end(), entry[1]) != entry.end() && entry[1] != "distinct" && entry[1] != "reverse"){
                pos = true;
                pull = part_of_speech(entry[1], pull);
            }if(entry[1] != "distinct" && entry[1] != "reverse" && pos == false){
                cout << "      <The entered 2nd parameter " << "'" << entry[1] << "' is NOT a part of speech.>" << endl;
                cout << "      <The entered 2nd parameter " << "'" << entry[1] << "' is NOT 'distinct'.>" << endl;
                cout << "      <The entered 2nd parameter " << "'" << entry[1] << "' is NOT 'reverse'.>" << endl;
                cout << "      <The 2nd parameter should be a part of speech or 'distinct' or 'reverse'.>" << endl;
            }if (entry[2] != "distinct" && entry[2] != "reverse"){
               cout << "      <The entered 3rd parameter " << "'" << entry[2] << "' is NOT 'distinct'.>" << endl;
                cout << "      <The entered 3rd parameter " << "'" << entry[2] << "' is NOT 'reverse'.>" << endl;
                cout << "      <The 3rd parameter should be 'distinct' or 'reverse'.> " << endl;
            }if(entry[3] != "reverse"){
                cout << "      <The entered 4th parameter " << "'" << entry[3] << "' is NOT 'reverse'.>" << endl;
                cout << "      <The 4th parameter should be 'reverse'.> " << endl;
            }
            for(Libary i: pull){
                if(i.getWord() == entry[0]){
                    cout << "      " << i.toString() << "\n";
                }
            }
        }
        cout << "      |" << endl;
    }
}