#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <tuple>
#include <string>
#include <sstream>
using namespace std;

regex ID("[TDRCE](0|[1-9]\d{0,9})");
regex TYPE("([A-Z]|[0-9])[a-zA-Z0-9,-\/]+");
regex NODE("[0-9][1-9]{0,9}");

void err(string line, int i) {
	cout << "Error in line " << i << ": " << line << endl;
}

bool ifCorrect(vector<string> tokens) {
	return tokens.size() >= 4 &&
		regex_match(tokens.at(0), ID) &&
		regex_match(tokens.at(1), TYPE) &&
		regex_match(tokens.at(2), NODE) &&
		regex_match(tokens.at(3), NODE) &&
		(tokens.at(0)[0] = 'T' && tokens.size() == 5) || tokens.size() == 4;
}

tuple<string, string, int, int, int> readLine(string line) {
	istringstream iss(line);
	vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>());

	if (regex_match(tokens.at(0), ID)) {

	}
}

void writeResults (unordered_map<string, string *> map) {

}

void checkConnections (unordered_set<string> nodeSet, bool ifConnectedToMass) {

}

void populateMap (unordered_map<pair<char, string>, vector<string>> partMap, tuple<string, string, int, int, int> data) {

}

int main() {
	unordered_set<string> idSet, nodeSet;
	unordered_map<pair<char, string>, vector<string>> partMap;
	bool ifConnectedToMass = false;

	//check if the line is empty before passing to readLine
	string temp;
	getline(cin, temp);
	readLine(temp);
}
