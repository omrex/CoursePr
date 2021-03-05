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
				this->lmap[word.getWord().at(0)].push_back(word);
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

	vector <pair<SingleWord, SingleWord>> getTwoPalz(char key) {
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

int main() {

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	try {
		Dictionary two("bgdict.txt");
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
		/*
		for (auto i : two.getPal()) {
			i << cout;
			cout << endl;
		}

		cout << endl << "проверка за лебед" << endl;
		SingleWord meh("лебед");
		for (auto i : two.getTwoPals(meh)) {
			i.first << cout << " ";
			i.second << cout;
			cout << endl;
		}
		cout << endl;
		*/
		cout << endl << "проверка за б" << endl;
		ofstream outFile("v_file.txt");
		// the important part
		for ( auto& e : two.getTwoPalz('в')) outFile << e.first.getWord()<<" "<<e.second.getWord()<< "\n";
		
		cout << "DOne";

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