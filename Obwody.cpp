#include <iostream>
#include <regex>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <tuple>
using namespace std;

regex id("[TDRCE](0|[1-9]\d{0,9})");
regex type("([A-Z]|[0-9])[a-zA-Z0-9,-\/]+");
regex node("[0-9][1-9]{0,9}");

void err(string line, int i) {
	cout << "Error in line " << i << ": " << line << endl;
}

tuple<string, string, int, int, int> readLine(string line) {
	
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
}
