#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
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
#include <regex>



using namespace std;


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
		if (this->m_word[0] >= '�' && this->m_word[0] <= '�') {
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
			if (this->getWord()[N - 1 - i] != word.getWord()[i]) {
				return false;
			}
		}
		return true;
	}
};

class Dictionary {
private:
	list <SingleWord> allwords;

	map <char, list <SingleWord>> lmap;
	map <char, list <SingleWord>> revmap;

	string art =
		"@@@@@@@   @@@@    @@@@@ @@   @@ @@   @@      @@ @@@@@@   @@@@@  @@   @@ @@   @@\n"
		"@@   @@     @@   @@  @@ @@  @@@ @@   @@   @@@@@ @@   @@ @@   @@ @@@ @@@ @@  @@@\n"
		"@@   @@  @@@@@   @@  @@ @@ @ @@ @@@@@@@  @@  @@ @@@@@@  @@   @@ @@ @ @@ @@ @ @@\n"
		"@@   @@ @@  @@   @@  @@ @@@  @@ @@   @@ @@   @@ @@      @@   @@ @@   @@ @@@  @@\n"
		"@@   @@  @@@@@@ @@   @@ @@   @@ @@   @@  @@@@@  @@       @@@@@  @@   @@ @@   @@\n";
public:
	Dictionary(const string& filename) {
		ifstream infile;
		infile.open(filename);
		if (!infile.good()) {
			throw runtime_error("File not found.");
		}
		else {
			int dot = 0;
			int slow = 0;
			while (!infile.eof()) {
				SingleWord word;
				word >> infile;
				//this->allwords.push_back(word);
				//this->dict.insert(make_pair(word.getWord().at(0), word));
				word.toLower();
				char firstlet = word.getWord().at(0);
				this->lmap[firstlet].push_back(word);
				word = word.getRev();
				firstlet = word.getWord().at(0);
				this->revmap[firstlet].push_back(word);
				dot++;
				if (dot == 2500) {
					dot = 0;
					if (slow < art.length())cout << art.at(slow);
					slow++;
				}
			}
			//this->allwords.sort();
			map<char, list<SingleWord>>::iterator iter;
			for (iter = this->lmap.begin(); iter != this->lmap.end(); ++iter) {
				iter->second.sort();
				iter->second.unique();
			}
			for (iter = this->revmap.begin(); iter != this->revmap.end(); ++iter) {
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

	int fin = 0;
	vector<string> mypal;
	int fin2 = 0;

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

	void RevMap() {
		map<char, list<SingleWord>>::iterator iter;
		for (iter = this->revmap.begin(); iter != this->revmap.end(); ++iter) {
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
	void finishWord(string begword) {
		char first = begword.at(0);
		int L = begword.length();
		if (lmap.count(first) != 0) {
			list <SingleWord>::iterator it = find_if(begin(this->lmap[first]), end(this->lmap[first]),
				[&](SingleWord v) { return v.getWord().substr(0, L) == begword; });
			list <SingleWord>::iterator itr = find_if_not(it, end(this->lmap[first]),
				[&](SingleWord v) { return v.getWord().substr(0, L) == begword; });
			if (it != this->lmap[first].end()) {
				// It does not point to end, it means at least one element exists in the list

				for (it; it != itr; it++) {
					SingleWord word = *it;
					word << cout << endl;
				}
			}
			else cout << endl << "���� ���� ��������� �: " << begword;
		}
		else cout << endl << "���� ���� ��������� �: " << first;
	}
	void startWord(string begword) {
		SingleWord beg(begword);
		begword = beg.getRev();
		char first = begword.at(0);
		int L = begword.length();
		if (revmap.count(first) != 0) {
			list <SingleWord>::iterator it = find_if(begin(this->revmap[first]), end(this->revmap[first]),
				[&](SingleWord v) { return v.getWord().substr(0, L) == begword; });
			list <SingleWord>::iterator itr = find_if_not(it, end(this->revmap[first]),
				[&](SingleWord v) { return v.getWord().substr(0, L) == begword; });
			if (it != this->revmap[first].end()) {
				// It does not point to end, it means at least one element exists in the list

				for (it; it != itr; it++) {
					SingleWord word = *it;
					cout << word.getRev() << endl;
				}
			}
			else cout << endl << "���� ���� ���������� �: " << beg.getWord();
		}
		else cout << endl << "���� ���� ���������� �: " << first;
	}

	void startWordextra(string begword) {
		SingleWord beg(begword);
		begword = beg.getRev();
		char first = begword.at(0);
		int L = begword.length();
		if (revmap.count(first) != 0) {
			list <SingleWord>::iterator it = find_if(begin(this->revmap[first]), end(this->revmap[first]),
				[&](SingleWord v) { return v.getWord().substr(0, L) == begword; });
			list <SingleWord>::iterator itr = find_if_not(it, end(this->revmap[first]),
				[&](SingleWord v) { return v.getWord().substr(0, L) == begword; });
			if (it != this->revmap[first].end()) {
				// It does not point to end, it means at least one element exists in the list
				cout << endl << "��� ���� ���������� �: " << beg.getWord() << " ����� ������ � ���������";
				for (it; it != itr; it++) {
					SingleWord word = *it;
					SingleWord partOfWord(word.getWord().substr(L)); //get the rest of the word (word minus the input)
					if (partOfWord.getWord().size() > 0 && partOfWord.isPal()) {
						cout << endl << word.getRev();
						//return word.getRev();
					}
				}
			}
			else cout << endl << "���� ���� ���������� �: " << beg.getWord() << " ����� ������ � ���������";
		}
		else cout << endl << "���� ���� ���������� �: " << first << " ����� ������ � ���������";
	}

	bool canYouAdd(string begword) {
		char first = begword.at(0);
		int L = begword.length();
		if (lmap.count(first) != 0) {
			list <SingleWord>::iterator it = find_if(begin(this->lmap[first]), end(this->lmap[first]),
				[&](SingleWord v) { return v.getWord().substr(0, L) == begword; });
			if (it != this->lmap[first].end())
			{
				// It does not point to end, it means at least one element exists in the list
				return true;
			}
			else return false;
		}
		else return false;
	}

	bool canYouFinish(string begword) {
		SingleWord beg(begword);
		begword = beg.getRev();
		char first = begword.at(0);
		int L = begword.length();
		if (revmap.count(first) != 0) {
			list <SingleWord>::iterator it = find_if(begin(this->revmap[first]), end(this->revmap[first]),
				[&](SingleWord v) { return v.getWord().substr(0, L) == begword; });
			if (it != this->revmap[first].end())
			{
				// It does not point to end, it means at least one element exists in the list
				return true;
			}
			else return false;
		}
		else return false;
	}

	string space(int s) {
		string a = "";
		while (s > 0) {
			a += " ";
			s--;
		}
		return a;
	}

	string func2(int j, string word, string phr, list <string> *wordO) {
		//i is number of chars that need to be substr
		int i = 1;
		//position of char + number of chars should not be more than the length of the word +1
		while (i + j <= word.length()) {
			//check if the substr is not a word	
			if (!legitWord(word.substr(j, i))) {
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
						//cout << endl << word.substr(j, i) << "***";
						phr = word.substr(j, i) + "*";
					}
					else {
						//cout << endl << space(j + 4);// << "end: ";
						//cout << word.substr(j, i) << "***";
						phr += " ";
						phr += word.substr(j, i) + "*";
					}
					//cout << "\t " << phr << "***. ";// << word.substr(j, i);// << " j=" << j; final
					//fin will take the value of j
					fin = j;
					//cout<< " fin=" << fin;
					if (canYouAdd(word.substr(j, i))) {
						wordO->push_back(phr);
					}
					//else cout << "\t���� ���� ��������� ���� => ���������� �����" << endl;
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
				if (j == 0) {
					//cout << endl;
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

					//cout << endl << space(j + 4);
					phr += " ";
					phr += word.substr(j, i);
					/*
					if (i + j == word.length()) {
						cout << "endd: ";
					}
					*/
				}
				//print the word
				//cout << word.substr(j, i);
				if (i + j != word.length()) {}//cout << " So far: " << phr << " j=" << j; }
				else {
					wordO->push_back(phr);
					//cout << " \t Fin: " << phr << ".";// << " j=" << j;
					fin = j;
					//cout << " fin: " << fin;
				}
				//check the substr starting with the char after the previous substr
				func2(j + i, word, phr, wordO);
				i++;
			}
		}
		return phr;
	}


	string minusfunc2(int j, string word, string phr, list <string> *wordO) {
		//i is number of chars that need to be substr
		//cout << endl<<"j= "<< j ;
		int i = 1;
		//position of char should not be less than 0
		while (j >= 0) {
			//cout << endl << " fin2 =" << fin2 << " j =" << j << " i =" << i;
			//check if the substr is not a word	
			if (!legitWord(word.substr(j, i))) {
				//if we get to the first character of the string � the end of the iter
				if (j == 0) {
					//indicate it's the beginning of the word (the end of iter) and decrease the position j so it can exit the while cycle		
					//cout << endl;
					if (fin2 > 0) {//== j + i
						regex e("^(\\s*\\S+){1}");   // matches words beginning by " x"
						phr = regex_replace(phr, e, "");
						//cout << endl << "phr af d:" << phr << ".";
						fin2 = 0;
					}
					//cout <<endl << space(j+4)<< "**" << word.substr(j, i);
					//if (i == word.length()) { phr = "*" + word.substr(j, i); }
					//else {
					phr.insert(0, "*" + word.substr(j, i));
					//}
						//cout << "\t\t\t:" << phr;// << "." << " ����" << " fin2 = " << fin2 << " j = " << j << " i = " << i;
					if (canYouFinish(word.substr(j, i))) {
						wordO->push_back(phr);
					}
					//else cout << "\t���� ���� ��������� ���� => ���������� �����" << endl;
					fin2 = 1;
					j--;
				}
				//move the position j to the left and increase i - number of char to be checked
				else {
					//cout << endl << space(j + 4) << word.substr(j, i);// << " �� � ���� � �� � ���� j= " << j << " i= " << i;
					i++;
					j--;
				}
			}
			//if the substr is a word
			else {
				//if it starts with the last letter of the word, start on a new line 
				//cout << endl << fin2 << " " << j << " phr upto:" << phr<<".";
					//if the previous final phrase required a bigger than the current recursion, delete last word of the string


				if (fin2 > 0) {//== j + i
					regex e("^(\\s*\\S+){1}");   // matches words beginning by "sub"
					phr = regex_replace(phr, e, "");
					//cout << endl << "phr af d:" << phr<<".";
					fin2 = 0;
				}


				//print the substr
				//cout << endl << space(j + 8) << word.substr(j, i);// << " � ���� fin2=" << fin2 << " j=" << j << " i=" << i;
				//is j at the beginning of the word
				if (j == 0) {
					phr.insert(0, word.substr(j, i));
					fin2 = 1;
					//cout << "\t\t\t:" << phr  ;// ". ����";
					wordO->push_back(phr);

				}
				else {
					phr.insert(0, " " + word.substr(j, i));
				}



				//fin2 = i + j;
				//fin2 = j;
				//check the substr starting with the char before the previous substr
				minusfunc2(j - 1, word, phr, wordO);
				j--;
				i++;

			}
		}
		return phr;
	}



	bool createpal(string myword) {
		SingleWord clword(myword);
		string helping = "";
		list <string> wordO;
		if (mypal.size() == 1) { //check if that's the first word of the palindromic phrase
			for (int count = 0; count < myword.length(); count++) {//checks if input word ends with palindrome of any length
				SingleWord lastpart(clword.getWord().substr(count));
				if (lastpart.isPal()) {
					SingleWord clword2(clword.getWord().substr(0, count));
					func2(0, clword2.getRev(), helping, &wordO);
				}
			}
			//txt functions to add
			/*
			for (int count = myword.length(); count > 0; count--) {
				cout << endl << "new for loop";
				startWordextra(clword.getRev().substr(0, count));
				cout << " =>left: "<< clword.getRev().substr(count) <<endl;
			}
			*/
		}

		int flag = 0;
		func2(0, clword.getRev(), helping, &wordO);

		if (!wordO.empty()) {
			cout << endl << "���������� ��:" << endl;
			int count = 0;
			for (auto i : wordO) {
				cout << count + 1 << ". " << i << endl;
				count++;
			}
			int option;
			do {
				cout << endl << "��� ������� ������������?: ";
				cin >> option;
			} while (option > count);
			list<string>::iterator it = wordO.begin();
			// Advance the iterator by n positions,
			advance(it, option - 1);
			// Now iterator it points to nth element
			mypal.push_back(*it);
			cout << endl << "����������� ����� �: " << endl;
			for (auto j : mypal) {
				cout << j << " ";
			}
			//clear the options
			wordO.clear();
			//check if last char of last elem is a *
			if (mypal.back().at(mypal.back().length() - 1) == '*') {
				const auto pos = mypal.back().find_last_of(" \t\n");
				string unfinished = mypal.back().substr(pos + 1, mypal.back().length() - mypal.back().substr(0, pos + 1).length() - 1);
				cout << endl << endl << "��� �� �������� " << unfinished << "*?" << endl;
				cout << "��������� 1 �� �� ���������� ���� ��������� � " << unfinished << endl;
				cout << "��������� 2 �� �� �������� ������" << endl;
				cout << "��������� 0 �� �� �� ������� ��� �������� ����" << endl;
				char cha;
				do {
					cout << endl << "������ ���� ����� �� ���������: ";
					cin >> cha;
					switch (cha) {
					case '1': {
						string mychars;
						if (unfinished.length() < 3) {
							do {
								cout << "������ " << 3 - unfinished.length() << " ��� ������ �����: " << unfinished;
								cin >> mychars;
							} while (unfinished.length() + mychars.length() < 3);
						}
						mychars = unfinished + mychars;
						finishWord(mychars);
						break;
					}
					case '2': {
						string myword;
						cout << "������ ����: " << unfinished;
						cin >> myword;
						//vector<string>::iterator itr = mypal.begin(); --old not sure what I needed it for
						//mypal.insert(itr, myword);
						if (!legitWord(unfinished + myword)) cout << endl << "���������� ���� � ���������!" << endl;
						else {
							// maybe a solution for adding the end part to the word
							mypal.back() = mypal.back().substr(0, pos + 1) + unfinished + myword;
							rightwordcreatepal(myword);
							cha = '0';//to exit the do while cycle
						}
						break;
					}
					case '0': {
						break;
					}
					default:
						cout << "��������� �����" << endl;

					}
				} while (cha != '0');
			}
			cout << endl;
			return true;
		}
		else {
			cout << endl << "�� ���� �� �� ������� ��������� � ���� ���� ����";
			mypal.erase(mypal.begin(), mypal.begin() + 1);
		}
		return false;
	}



	bool rightwordcreatepal(string myword) {
		SingleWord clword(myword);
		string helping = "";
		list <string> Wordo;
		int flag = 0;
		int start = myword.length() - 1;
		minusfunc2(start, clword.getRev(), helping, &Wordo);

		if (!Wordo.empty()) {
			cout << endl << "���������� ��:" << endl;
			int count = 0;
			for (auto i : Wordo) {
				cout << count + 1 << ". " << i << endl;
				count++;
			}
			cout << endl;
			
			int option;
			do {
				cout << endl << "��� ������� ������������?: ";
				cin >> option;
			} while (option > count);
			list<string>::iterator it = Wordo.begin();
			// Advance the iterator by n positions,
			advance(it, option - 1);
			// Now iterator it points to nth element
			//mypal.push_back(*it);
			vector<string>::iterator itr = mypal.begin();
			mypal.insert(itr, *it);
			cout << endl << "����������� ����� �: " << endl;
			for (auto j : mypal) {
				cout << j << " ";
			}
			cout << endl;

			Wordo.clear();
			if (mypal.front().at(0) == '*') {
				const auto pos = mypal.front().find(" \t\n");
				string unfinished = mypal.front().substr(1, pos);
				cout << endl << endl << "��� �� �������� *" << unfinished << "?" << endl;
				cout << "��������� 1 �� �� ���������� ���� ���������� �� " << unfinished << endl;
				cout << "��������� 2 �� �� �������� ������" << endl;
				cout << "��������� 0 �� �� �� ������� ��� �������� ����" << endl;
				char cha;
				do {
					cout << endl << "������ ���� ����� �� ���������: ";
					cin >> cha;
					switch (cha) {
					case '1': {
						string mychars;
						if (unfinished.length() < 3) {
							do {
								cout << "������ " << 3 - unfinished.length() << " ��� ������ ����� ����� " << unfinished << ":" << endl;
								cin >> mychars;
								if (!mychars.ends_with(unfinished)) cout << "���������� ����� �� ��������� � " << unfinished << "!";
								else {
									//mychars = mychars + unfinished;
									startWord(mychars);
								}
							} while (unfinished.length() + mychars.length() < 3);
						}

						break;
					}
					case '2': {
						string myword;
						cout << "������ ����, ���������� �� " << unfinished << ": ";
						cin >> myword;
						//vector<string>::iterator itr = mypal.begin(); --old not sure what I needed it for
						//mypal.insert(itr, myword);
						if (!myword.ends_with(unfinished)) cout << "���������� ���� �� �������� �� " << unfinished << "!";
						else {
							if (!legitWord(myword)) cout << endl << "���������� ���� � ���������!" << endl;
							else {
								auto end = myword.find(unfinished);
								myword = myword.substr(0, end);
								// maybe a solution for adding the first part to the word
								mypal.front().erase(0, 1);
								mypal.front() = mypal.front().insert(0, myword);
								createpal(myword);
								cha = '0';//to exit the do while cycle
							}
						}
						break;
					}
					case '0': {
						break;
					}
					default:
						cout << "��������� �����" << endl;

					}
				} while (cha != '0');
			}
			
			return true;
		}
		else {
			cout << endl << "�� ���� �� �� ������� ��������� � ���� ���� �����";
			mypal.pop_back(); //delete the word from the user
		}
		//}
		return false;
	}


};


void submenu4()
{
	cout << endl;
	cout << "��������� 1 �� �� �������� ���� ������" << endl;
	cout << "��������� 2 �� �� �������� ���� �������" << endl;
	cout << "��������� 0 �� �� �� ������� ��� �������� ����" << endl;
}

void menu()
{
	cout << "��������� 1 �� �� ���������� ������ ���� ����������" << endl;
	cout << "��������� 2 �� �� ��������� ���� ��������� ���� ����������" << endl;
	cout << "��������� 3 �� �� ���������� ������ ��������� ����, ��������� � ��������� �����" << endl;
	cout << "��������� 4 �� �� ��������� ��������� �������" << endl;
	cout << "��������� 5 �� �� �������� ����, ��������� � ��������� �����" << endl;
	cout << "��������� 6 �� �� ��������� ��������� ������" << endl;
	cout << "��������� 7 �� �� �������� ����, ���������� � ��������� �����" << endl;
	cout << "��������� 8 �� �� �������� ����, ���������� � ��������� �����, ����� ������ � ���������" << endl;
	cout << "��������� 9 �� �� �� �������� ����, ����� �������� �� ���������� ����, �� �������� � ���������" << endl;
	cout << "��������� 0 �� �� ��������� ����������" << endl;
}


void select(char choice, Dictionary mydict)
{
	// Display the result 
	switch (choice) {
	case '1': {
		cout << "������������ ��: " << "\n";
		int all = 0;
		for (auto i : mydict.getPal()) {
			i << cout;
			all++;
			cout << endl;
		}
		cout << endl << "��� ����: " << all << endl;
		break;
	}
	case '2': {
		string myword;
		cout << "������ ����: ";
		cin >> myword;
		SingleWord clword(myword);
		if (!mydict.legitWord(myword)) cout << endl << "���������� ���� � ���������" << endl;
		else {
			vector <pair<SingleWord, SingleWord>> result = mydict.getTwoPals(myword);
			if (!result.empty()) {
				for (auto i : result) {
					i.first << cout << " ";
					i.second << cout;
					cout << endl;
				}
			}
			else cout << endl << clword.getRev() << " �� � ����" << endl;
		}
		break;
	}
	case '3': {
		char myword;
		cout << "������ �����: ";
		cin >> myword;
		for (auto i : mydict.getTwoPals(myword)) {
			i.first << cout << " ";
			i.second << cout;
			cout << endl;
		}
		break;
	}
	case '4': {
		//cout << "����� ������ �� ���������?: ";
		string myword;
		cout << "������ ����: ";
		cin >> myword;
		if (!mydict.legitWord(myword)) cout << endl << "���������� ���� � ���������!" << endl;
		else {
			vector<string>::iterator itr = mydict.mypal.begin();
			mydict.mypal.insert(itr, myword);
			if (mydict.createpal(myword)) {
				submenu4();
				char cha;
				do {
					cout << endl << "������ ����� �� �������: ";
					cin >> cha;
					switch (cha) {
					case '1': {
						cout << "������ ����: ";
						cin >> myword;
						if (!mydict.legitWord(myword)) cout << endl << "���������� ���� � ���������!" << endl;
						else {
							vector<string>::iterator itr = mydict.mypal.begin();
							mydict.mypal.insert(itr, myword);
							mydict.createpal(myword);
						}
						break;
					}
					case '2': {
						cout << "������ ����: ";
						cin >> myword;
						//vector<string>::iterator itr = mypal.begin();
						//mypal.insert(itr, myword);
						if (!mydict.legitWord(myword)) cout << endl << "���������� ���� � ���������!" << endl;
						else {
							mydict.mypal.push_back(myword);
							mydict.rightwordcreatepal(myword);
						}
						break;
					}
					case '3': {
						cout << "3" << endl;
						break;
					}
					case '0': {
						break;
					}
					default:
						cout << "��������� �����" << endl;

					}
				} while (cha != '0');
			}
		}
		//wordO.clear();
		break;
	}
	case '5': {
		string mychars;
		do {
			cout << "������ ��� ��� ������ ������� ����� �� ������: ";
			cin >> mychars;
		} while (mychars.length() < 2);
		mydict.finishWord(mychars);

		break;
	}
	case '6': {
		string myword;
		cout << "������ ����: ";
		cin >> myword;
		if (!mydict.legitWord(myword)) cout << endl << "���������� ���� � ���������!" << endl;
		else {
			mydict.mypal.push_back(myword);
			mydict.rightwordcreatepal(myword);
		}
		break;
	}
	case '7': {
		string mychars;
		cout << "������ ��� ��� ������ ������ ����� �� ������: ";
		cin >> mychars;
		if (mychars.length() < 2) {
			cout << "������ ������ ����� �� ������: ";
			break;
		}
		mydict.startWord(mychars);

		break;
	}
	case '8': {
		string mychars;
		cout << "������ ��� ��� ������ ������ ����� �� ������: ";
		cin >> mychars;
		if (mychars.length() < 2) {
			cout << "������ ������ ����� �� ������: ";
			break;
		}
		mydict.startWordextra(mychars);

		break;
	}

	case '9': {
		string myword;
		cout << "������ ������: ";
		cin >> myword;
		SingleWord clword(myword);
		string options;
		list <string> wordO;
		for (int count = myword.length(); count > 0; count--) {
			cout << endl << "new for loop";
			mydict.startWordextra(clword.getRev().substr(0, count));
			cout << " =>������� �� �������: " << clword.getRev().substr(count) << endl;
			if (clword.getRev().substr(count).length() > 0) {
				mydict.func2(0, clword.getRev().substr(count), options, &wordO);
				if (!wordO.empty()) {
					cout << endl << "���������� ��:" << endl;
					int count = 0;
					for (auto i : wordO) {
						cout << count + 1 << ". " << i << endl;
						count++;
					}
					wordO.clear();
				}
			}
		}

		break;
	}

	case '0': {
		cout << "�� ���� �����!" << endl;
		break;
	}
	default:
		cout << "��������� �����" << endl;
	}
}



int main() {

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	try {
		Dictionary two("d.txt");

		menu();
		// Enter the choice 
		char ch;
		do {
			cout << endl << "������ ����� �� ������ ����: ";
			cin >> ch;
			select(ch, two);
		} while (ch != '0');

	}
	catch (runtime_error e) {
		cout << "Error: " << e.what() << endl;
	}


	return 0;
}