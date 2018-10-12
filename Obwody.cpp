#include <iostream>
#include <regex>
#include <map>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <sstream>
using namespace std;

regex ID("[TDRCE](0|[1-9]\\d{0,9})");
regex TYPE("([A-Z]|[0-9])[a-zA-Z0-9,-\\/]+");
regex NODE("[0-9][1-9]{0,9}");

// Prints out an error
void err(string line, int i) {
	cerr << "Error in line " << i << ": " << line << endl;
}

// Checks if given tokens are correct representations of required data
bool ifCorrect(vector<string> tokens) {
	return tokens.size() >= 4 &&
		regex_match(tokens.at(0), ID) &&
		regex_match(tokens.at(1), TYPE) &&
		regex_match(tokens.at(2), NODE) &&
		regex_match(tokens.at(3), NODE) &&
		tokens.at(2) != tokens.at(3) &&
		(tokens.size() == 4 ||
			(tokens.at(0)[0] = 'T' &&
				tokens.size() == 5 &&
				tokens.at(4) != tokens.at(3) &&
				tokens.at(4) != tokens.at(2)));
}

// Extracts data from string, returns ("", "", -1, -1, -1) tuple if data is incorrect
tuple<string, string, int, int, int> readLine(string line) {
	istringstream iss(line);
	vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>());

	if (ifCorrect(tokens)) {
		int last;
		if (tokens.size() == 4)
			last = -1;
		else
			last = stoi(tokens.at(4));
		return tuple<string, string, int, int, int>(tokens.at(0), tokens.at(1), stoi(tokens.at(2)), stoi(tokens.at(3)), last);
	}
	else
		return tuple<string, string, int, int, int>("", "", -1, -1, -1);
}

void writeResults (map<string, string *> map) {

}

// Checks if any of declared nodes are unconnected and if so, prints according error
void checkConnections (set<string> nodeSet, bool ifConnectedToMass) {
	if (!ifConnectedToMass)
		nodeSet.insert(0);
	if (!nodeSet.empty()) {
		cerr << "Warning, unconnected node(s): ";
		size_t nodesLeft = nodeSet.size();
		for (auto node : nodeSet) {
			cerr << node;
			nodesLeft--;
			if (nodesLeft > 0)
				cerr << ", ";
			else
				cerr << endl;
		}
	}
}

void populateMap (map<pair<char, string>, vector<string>> partMap, tuple<string, string, int, int, int> data) {

}

int main() {
	set<string> idSet, nodeSet;
	map<pair<char, string>, vector<string>> partMap;
	bool ifConnectedToMass = false;

	// read with streams

	checkConnections(nodeSet, ifConnectedToMass);
}
