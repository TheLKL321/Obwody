#include <iostream>
#include <regex>
#include <map>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <sstream>

using namespace std;

#define pb push_back
#define st first
#define nd second
#define mp make_pair

regex ID("[TDRCE](0|[1-9]\\d{0,9})");
regex TYPE("([A-Z]|[0-9])[a-zA-Z0-9,-\\/]+");
regex NODE("[0-9][1-9]{0,9}");

struct cmpByPart {
    bool operator()(pair<char, string> a, pair<char, string> b) const {
			int x1 = -1, x2 = -1;
			switch (a.st) {
				case 'T' :
					x1 = 0;
					break;
				case 'D' :
					x1 = 1;
					break;
				case 'R' :
					x1 = 2;
					break;
				case 'C' :
					x1 = 3;
					break;
				case 'E' :
					x1 = 4;
					break;
				default: x1 = -1;
			}
			switch (b.st) {
				case 'T' :
					x2 = 0;
					break;
				case 'D' :
					x2 = 1;
					break;
				case 'R' :
					x2 = 2;
					break;
				case 'C' :
					x2 = 3;
					break;
				case 'E' :
					x2 = 4;
					break;
				default : x1 = -1;
			}
			if(x1 < x2) return true;
			else
				if (x1 > x2) return false;
				else
					return a.nd < b.nd;
    }
};

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

void writeResults (map<pair<char, string>, vector<string>, cmpByPart> partMap)
{
	for(map<pair<char, string>, vector<string>, cmpByPart>::iterator it = partMap.begin(); it != partMap.end(); it++)
	{
		size_t n = (it->nd).size();
		for(size_t i = 0; i < n; i++)
		{
			cout << (it->nd)[i];
			if(i == n-1)
				cout << ": ";
			else
				cout << ", ";
		}
		cout << (it->st).nd << endl;
	}
}

// Checks if any of declared nodes are unconnected and if so, prints according error
void checkConnections (set<int> nodeSet, bool ifConnectedToMass) {
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

void connect(set<int> *unconnectedNodeSet, set<int> *connectedNodeSet, int node)
{
	if(!connectedNodeSet->count(node))
	{
		if(unconnectedNodeSet->count(node))
		{
			unconnectedNodeSet->erase(node);
			connectedNodeSet->insert(node);
		}
		else
			unconnectedNodeSet->insert(node);
	}
}

void populateMap (map<pair<char, string>, vector<string>, cmpByPart> *partMap, tuple<string, string, int, int, int> data) {
	pair<char, string> key = mp(get<0>(data)[0], get<1>(data));
	map<pair<char, string>, vector<string>, cmpByPart>::iterator it = partMap->find(key);
	if(it == partMap->end()){
		vector<string> value;
		value.pb(get<0>(data));
		partMap->insert(mp(key,value));
	}
	else{
		(it->nd).pb(get<0>(data));
	}
}

int main() {
	set<string> idSet;
	set<int> unconnectedNodeSet;
	set<int> connectedNodeSet;
	map<pair<char, string>, vector<string>, cmpByPart> partMap;
	tuple<string, string, int, int, int> data;
	bool ifConnectedToMass = false;
	string input;
	int licz = 1;
	while(getline(cin, input)) {
		data = readLine(input);
		if(get<0>(data) == "" || idSet.find(get<0>(data)) != idSet.end()) {
			err(input, licz);
		}
		else {
			idSet.insert(get<0>(data));
			if((get<2>(data) == 0) || (get<3>(data) == 0) || (get<4>(data) == 0))
				ifConnectedToMass = true;
			connect(&unconnectedNodeSet, &connectedNodeSet, get<2>(data));
			if(get<3>(data) != get<2>(data))
				connect(&unconnectedNodeSet, &connectedNodeSet, get<3>(data));
			if ((get<4>(data) != -1) && (get<4>(data) != get<2>(data)) && (get<4>(data) != get<3>(data)))
				connect(&unconnectedNodeSet, &connectedNodeSet, get<4>(data));
			populateMap(&partMap, data);
		}
		licz++;
	}
	checkConnections(unconnectedNodeSet, ifConnectedToMass);
	writeResults(partMap);
}
