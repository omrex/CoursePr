#include <iostream>
#include <fstream>
#include <string>
//#include <string.h>
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
	istream& operator >> (istream& in) {
		in >> this->m_word;
		return in;
	}
	ostream& operator << (ostream& out) {
		out << this->m_word;
		return out;
	}
	bool operator < (const SingleWord& word) {
		return (this->m_word < word.m_word);
	}
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
				this->allwords.push_back(word);
			}
			this->allwords.sort();
		}
		infile.close();
	};
	list <SingleWord> getAllwords() {
		return this->allwords;
	}
	istream& operator >> (istream& in) {
		SingleWord newword;
		newword >> in;
		return in;
	}
	ostream& operator << (ostream& out) {
		list<SingleWord>::const_iterator itr = this->allwords.begin();
		for (itr; itr != this->allwords.end(); ++itr) {
			SingleWord newword = *itr;
			newword << cout << endl;
		}
		return out;
	}
	vector <SingleWord> getVector() {
		vector <SingleWord> Palindromes;
		list <SingleWord>::iterator it = this->allwords.begin();
		for (it; it != this->allwords.end(); it++) {
			SingleWord oneword = *it;
			if (oneword.isPal()) Palindromes.push_back(oneword);	
		}
		return Palindromes;
	}
	vector <pair<SingleWord, SingleWord>> getMirrors() {
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
};

int main() {

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	
	try {
		Dictionary two("bgdict.txt");
		int all = 0;
		for (auto i : two.getVector()) {
			i <<  cout;
			cout << endl;
			all++;
		}
		cout << endl << "All words are: " << all;

	}
	catch (runtime_error e) {
		cout << "Error: " << e.what() << endl;
	}
	
	return 0;
}