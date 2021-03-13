#include <iostream>
#include <fstream>
#include <string>
//#include <string.h>
#include <map>
#include <set>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <locale>
#include <windows.h>
#include <ctype.h>



using namespace std;

int fin = 0;
list <string> blah;

class SingleWord {
private:
	string m_word;
public:
	SingleWord() {
		this->m_word = " ";
	}
	SingleWord(string word) {
		this->m_word = word;
	}
	void toLower() {
		if (this->m_word[0] >= 'А' && this->m_word[0] <= 'Я') {
			this->m_word[0] = this->m_word[0] + 32;
		}
	}
	string getWord() {
		return this->m_word;
	}
	string getRev() {
		string back = this->m_word;
		int len = back.length();
		int n = len - 1;
		for (int i = 0; i < (len / 2); i++) {
			swap(back[i], back[n]);
			n = n - 1;
		}
		return back;
	}
	istream& operator >> (istream& in) {
		in >> this->m_word;
		return in;
	}
	ostream& operator << (ostream& out) {
		out << this->m_word;
		return out;
	}
	//needed for sorting
	bool operator < (const SingleWord& word) { 
		return (this->m_word < word.m_word);
	}
	//needed for removing duplicates
	bool operator == (const SingleWord& word) {
		return (this->m_word == word.m_word);
	}

	//checks if the word itself is a palindrome
	bool isPal() {
		int N = this->getWord().length();
		int i = 0;
		for (i; i <= N / 2; i++) {
			if (this->getWord()[i] != this->getWord()[N - 1 - i]) {
				return false;
			}
		}
		return true;
	}
	//checks if two words create a palindromic phrase (first is the same as the second spelled backwords)
	bool isMirror(SingleWord& word) {
		int N = this->getWord().length();
		int i = 0;
		for (i; i < N; i++) {
			if (this->getWord()[N-1-i] != word.getWord()[i]) {
				return false;
			}
		}
		return true;
	}
};

class Dictionary {
private:
	list <SingleWord> allwords;
	//multimap <char, SingleWord> dict;
	map <char, list <SingleWord>> lmap;
public:
	Dictionary(const string& filename) {
		ifstream infile;
		infile.open(filename);
		if (!infile.good()) {
			throw runtime_error("File not found.");
		}
		else {
			while (!infile.eof()) {
				SingleWord word;
				word >> infile;
				//this->allwords.push_back(word);
				//this->dict.insert(make_pair(word.getWord().at(0), word));
				word.toLower();
				char firstlet = word.getWord().at(0);
				this->lmap[firstlet].push_back(word);
			}
			//this->allwords.sort();
			map<char, list<SingleWord>>::iterator iter;
			for (iter = this->lmap.begin(); iter != this->lmap.end(); ++iter) {
				iter->second.sort();
				iter->second.unique();
			}
		}
		infile.close();
	};
	/*
	list <SingleWord> getAllwords() {
		return this->allwords;
	}
	*/
	map <char, list <SingleWord>> getMap() {
		return this->lmap;
	}
	list <SingleWord> getMapList(char key) {
		return this->lmap[key];
	}
	/*
	void MMap() {
		multimap<char, SingleWord>::iterator iter;
		for (iter = this->dict.begin(); iter != this->dict.end(); ++iter) {
			cout << "letter: " << iter->first << " word: ";
			iter->second << cout << endl;
		}
	}
	*/
	void LMap() {
		map<char, list<SingleWord>>::iterator iter;
		for (iter = this->lmap.begin(); iter != this->lmap.end(); ++iter) {
			cout << "letter: " << iter->first << endl;
			list<SingleWord>::const_iterator itr = iter->second.begin();
			for (itr; itr != iter->second.end(); ++itr) {
				SingleWord newword = *itr;
				newword << cout << endl;
			}
			cout << endl;
		}
	}
	/*
	istream& operator >> (istream& in) {
		SingleWord newword;
		newword >> in;
		return in;
	}
	*/
	/*
	ostream& operator << (ostream& out) {
		list<SingleWord>::const_iterator itr = this->allwords.begin();
		for (itr; itr != this->allwords.end(); ++itr) {
			SingleWord newword = *itr;
			newword << cout << endl;
		}
		return out;
	}
	*/
	/*
	//vector of all 1-word palindromes from list
	vector <SingleWord> getOneWord() {
		vector <SingleWord> Palindromes;
		list <SingleWord>::iterator it = this->allwords.begin();
		for (it; it != this->allwords.end(); it++) {
			SingleWord oneword = *it;
			if (oneword.isPal()) Palindromes.push_back(oneword);	
		}
		return Palindromes;
	}
	*/
	//vector of all 1-word palindromes from map
	vector <SingleWord> getPal() {
		vector <SingleWord> Palindromes;
		map<char, list<SingleWord>>::iterator iter;
		for (iter = this->lmap.begin(); iter != this->lmap.end(); ++iter) {
			list <SingleWord>::iterator it = iter->second.begin();
			for (it; it != iter->second.end(); it++) {
				SingleWord oneword = *it;
				if (oneword.isPal()) Palindromes.push_back(oneword);
			}
		}
		return Palindromes;
	}

	//vector of all 2-word palindromes from map
	vector <pair<SingleWord, SingleWord>> getTwoPal() {
		vector <pair<SingleWord, SingleWord>> Mirrors;
		map<char, list<SingleWord>>::iterator iter;
		for (iter = this->lmap.begin(); iter != this->lmap.end(); ++iter) {
			list <SingleWord>::iterator it = iter->second.begin();
			for (it; it != iter->second.end(); it++) {
				SingleWord oneword = *it;
				if (!oneword.isPal()) {
					int N = oneword.getWord().length();
					char last = oneword.getWord().at(N - 1);
					SingleWord twoword(oneword.getRev());
					if (lmap.count(last) != 0) {
						list <SingleWord>::iterator itr = find(begin(this->lmap[last]), end(this->lmap[last]), twoword);
						if (itr != this->lmap[last].end())
						{
							// It does not point to end, it means element exists in list
							Mirrors.push_back({ oneword,twoword });
						}
					}
				}
			}
		}
		return Mirrors;
	}
	

	bool legitWord(string word) {
		int N = word.length();
		char first = word[0];
		SingleWord twoword(word);
		//check if such a map exists by using count
		if (lmap.count(first) != 0) {
			list <SingleWord>::iterator it = find(begin(this->lmap[first]), end(this->lmap[first]), twoword);
			if (it != this->lmap[first].end())
			{
				// It does not point to end, it means element exists in list
				return true;
			}
		}
		return false;
	}
	vector <pair<SingleWord, SingleWord>> getTwoPals(SingleWord oneword) {
				vector <pair<SingleWord, SingleWord>> Mirrors;
				int N = oneword.getWord().length();
				char last = oneword.getWord().at(N - 1);
				SingleWord twoword(oneword.getRev());
				if (lmap.count(last) != 0) {
					list <SingleWord>::iterator it = find(begin(this->lmap[last]), end(this->lmap[last]), twoword);
					if (it != this->lmap[last].end())
					{
						// It does not point to end, it means element exists in list
						Mirrors.push_back({ oneword,twoword });
					}
					
				}
		return Mirrors;
	}
	vector <pair<SingleWord, SingleWord>> getTwoPals(char key) {
		vector <pair<SingleWord, SingleWord>> Mirrors;
		list <SingleWord>::iterator it = lmap[key].begin();
		for (it; it != lmap[key].end(); it++) {
			SingleWord oneword = *it;
			if (!oneword.isPal()) {
				int N = oneword.getWord().length();
				char last = oneword.getWord().at(N - 1);
				SingleWord twoword(oneword.getRev());
				if (lmap.count(last) != 0) {
					list <SingleWord>::iterator itr = find(begin(this->lmap[last]), end(this->lmap[last]), twoword);
					if (itr != this->lmap[last].end())
					{
						// It does not point to end, it means element exists in list
						Mirrors.push_back({ oneword,twoword });
					}
				}
			}
		}

		return Mirrors;
	}
	/*
	//vector of all 2-word palindromes
	vector <pair<SingleWord, SingleWord>> getTwoWord() {
		vector <pair<SingleWord, SingleWord>> Mirrors;
		list <SingleWord>::iterator it = this->allwords.begin();	
		for (it; it != this->allwords.end(); it++) {
			SingleWord oneword = *it;
			int N = oneword.getWord().length();
			list <SingleWord>::iterator itr = find_if(begin(this->allwords), end(this->allwords), 
				[&]( SingleWord v) { return v.getWord()[0]==oneword.getWord()[N-1]; });

			for (itr; itr != this->allwords.end(); itr++) {
				SingleWord secondword = *itr;
				if (oneword.isMirror(secondword)) Mirrors.push_back({oneword,secondword});
			}
		}
		return Mirrors;
	}
	*/
	
};

string space(int s) {
	string a = "";
	while (s > 0) {
		a += " ";
		s--;
	}
	return a;
}
/*
//shows possible words to finish right side of palindrome
//j is the position from which to start substr
vector<list<SingleWord>> func(int j, string word, Dictionary dict, list <SingleWord>blahh) {
	vector <list<SingleWord>> choices;
	//i is number of chars that need to be substr
	int i = 1;
	//position of char + number of chars should not be more than the length of the word +1
	list <SingleWord> blahhh;
	while (i+j < word.length()+1) {
		//check if the substr is not a word	
		string currword = word.substr(j, i);
		SingleWord word1(currword);
		if (!dict.legitWord(currword)) {
			//if we get to the last character
			if (i + j == word.length()) {
				//indicate it's the end of the word and add a char so it can exit the while cycle
				word1.real = false;
				blahh.push_back(word1);
				//cout << endl << space(j+4)<<"end: "<< word.substr(j, i);
				i++;
			}
			//just add another char to the substr
			else i++;
		}
		//if the substr is a word
		else {
			//if it starts with the first letter of the word start on a new line
			//if (j == 0) cout << endl;
			//if it's a 2nd word put a tab and print it on a new line
			//else cout <<endl<< space(j+4);
			//print the word
			blahh.push_back(word1);
			//cout << word.substr(j, i);
			//check the substr starting with the char after the previous substr
			func(j + i, word, dict, blahh);
			i++;
		}
		choices.push_back(blahh);
	}
	return choices;

}
*/

//shows possible words to finish right side of palindrome
//j is the position from which to start substr
string func2(int j, string word, Dictionary dict,  string phr) {
	//i is number of chars that need to be substr
	int i = 1;
	//position of char + number of chars should not be more than the length of the word +1
	while (i + j <= word.length()) {
		//check if the substr is not a word	
		if (!dict.legitWord(word.substr(j, i))) {
			//if we get to the last character
			if (i + j == word.length()) {
				//indicate it's the end of the word and add a char so it can exit the while cycle
				    //if the recursion is bigger than the current j, delete the last word in the string			
					if (fin > j) {
						const auto pos = phr.find_last_of(" \t\n");
						phr = phr.substr(0, pos);
						//cout << endl << "phr af d: " << phr;
					}
					//if the whole word does not exist
					if (j == 0) {
						cout << endl << word.substr(j, i) << "*** ";
						phr = word.substr(j, i);
					}
					else {
						cout << endl << space(j + 4);// << "end: ";
						cout << word.substr(j, i)<<"*** ";
						phr += " ";
						phr += word.substr(j, i);
					}
					cout << "\t Fin: " << phr << "***.";// << " j=" << j;
					//fin will take the value of j
					fin = j;
					//cout<< " fin=" << fin;
				
				blah.push_back(phr);
				i++;
			}
			//just add another char to the substr
			else {
				i++;
			}
		}
		//if the substr is a word
		else {
			//if it starts with the first letter of the word start on a new line 
			if (j == 0) {cout << endl;
				phr = word.substr(j, i);
			}
			//if it's a inbetween word put a tab and print it on a new line
			else {
				//cout << endl << fin << " " << j << " phr upto: " << phr;
				//if the previous final phrase required a bigger than the current recursion, delete last word of the string
				if (fin > j) {
					const auto pos = phr.find_last_of(" \t\n");
					phr = phr.substr(0, pos);
					//cout << endl << "phr af d: " << phr;
				}		
				
				cout << endl << space(j + 4);
				phr += " ";
				phr += word.substr(j, i);
				/*
				if (i + j == word.length()) {
					cout << "endd: ";
				}
				*/
			}
			//print the word
			cout << word.substr(j, i);
			if (i + j != word.length()) {}//cout << " So far: " << phr << " j=" << j; }
			else{
				blah.push_back(phr);
				cout << " \t Fin: " << phr << ".";// << " j=" << j;
				fin = j;
				//cout << " fin: " << fin;
			}
			//check the substr starting with the char after the previous substr
			func2(j + i, word, dict, phr);			
			i++;
		}
	}
	return phr;



}

void menu()
{
	cout << "Натиснете 1 за да разгледате всички думи палиндроми" << endl;
	cout << "Натиснете 2 за да проверите дали огледална дума съществува" << endl;
	cout << "Натиснете 3 за да разгледате всички огледални думи, започващи с конкретна буква" << endl;
	cout << "Натиснете 4 за да създадете палиндром" << endl;
	cout << "Натиснете 0 за да затворите програмата" << endl;
}


void select(char choice, Dictionary mydict)
{
	// Display the result 
	switch (choice) {
	case '1': {
		cout << "Палиндромите са: " << "\n";
		int all = 0;
		for (auto i : mydict.getPal()) {
			i << cout;
			all++;
			cout << endl;
		}
		cout << endl << "Общ брой: " << all << endl;
		break;
	}
	case '2': {
		string myword;
		cout << "Въведи дума: ";
		cin >> myword;
		SingleWord clword(myword);
		if (!mydict.legitWord(myword)) cout << endl << "Въведената дума е невалидна" << endl;
		else {
			vector <pair<SingleWord, SingleWord>> result = mydict.getTwoPals(myword);
			if (!result.empty()) {
				for (auto i : result) {
					i.first << cout << " ";
					i.second << cout;
					cout << endl;
				}
			}
			else cout << endl <<clword.getRev() <<" не е дума"<<endl;
		}
		break;
	}
	case '3': {
		char myword;
		cout << "Въведи буква: ";
		cin >> myword;
		for (auto i : mydict.getTwoPals(myword)) {
			i.first << cout << " ";
			i.second << cout;
			cout << endl;
		}
		break;
	}
	case '4': {

		string myword;
		cout << "Въведи дума: ";
		cin >> myword;
		SingleWord clword(myword);
		string helping = "";
		int flag = 0;
		func2(0, clword.getRev(), mydict, helping);

		cout << endl << "Вариантите са:" << endl;
		for (auto i : blah) {
			cout << i << endl;
		}
		blah.clear();
		break;
	}
	case '0': {
		cout << "До нови срещи!" << endl;
		break;
	}
	default:
		cout<<"Невалиден избор"<<endl;
	}
}

int main() {

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	cout << "Моля изчакайте, програмата да зареди." << endl;
	
	try {
		Dictionary two("d.txt");
		/*
		two << cout;
		int all = 0;
		for (auto i : two.getOneWord()) {
			i <<  cout;
			cout << endl;
			all++;
		}
		cout << endl << "All words are: " << all << endl;
		
		for (auto i : two.getTwoWord()) {
			i.first << cout <<" ";
			i.second << cout;
			cout << endl;
		}
		*/

		
		//two.MMap();
		//two.LMap();
		
		menu();
		// Enter the choice 
		char ch;
		do {
			cout << endl << "Въведи избор:" << endl;
			cin >> ch;
			select(ch, two);
		} while (ch != '0');
			

		/*
		cout << endl << "проверка за всичко" << endl;
		for (auto i : two.getTwoPal()) {
			i.first << cout << " ";
			i.second << cout;
			cout << endl;
		}
		*/
		
	}
	catch (runtime_error e) {
		cout << "Error: " << e.what() << endl;
	}
	

	return 0;
}