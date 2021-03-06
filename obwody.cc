#include <iostream>
#include <regex>
#include <map>
#include <vector>
#include <set>
#include <tuple>
#include <string>
#include <sstream>

using namespace std;

namespace {
	struct cmpByOrder;

	typedef map<string, string, cmpByOrder> oMap;
	typedef map<pair<char, string>, set<string, cmpByOrder>> pMap;
	typedef tuple<string, string, int, int, int> dataTuple;

	regex ID("[TDRCE](0|[1-9]\\d{0,8})");
	regex TYPE("([A-Z]|[0-9])[a-zA-Z0-9,\\/-]*");
	regex NODE("0|([1-9][0-9]{0,8})");

	// Used by cmpByOrder to compare elements
	int operatorHelper(char c) {
		switch (c) {
		case 'T': return 0;
		case 'D': return 1;
		case 'R': return 2;
		case 'C': return 3;
		case 'E': return 4;
		default: return -1;
		}
	}

	// Comparator used by oMap and pMap implementing required sorting order
	struct cmpByOrder {
		bool operator() (string a, string b) const {
			int x1 = operatorHelper(a[0]), x2 = operatorHelper(b[0]);

			if (x1 < x2)
				return true;
			else if (x1 > x2)
				return false;
			else if (a.length() < b.length())
				return true;
			else if (a.length() > b.length())
				return false;
			else
				return a < b;
		}
	};

	// Prints out an error
	void err (string line, int i) {
		cerr << "Error in line " << i << ": " << line << endl;
	}

	// Checks if given tokens are correct representations of required data
	bool ifCorrect (vector<string> tokens) {
		bool ifCorrect = true;
		ifCorrect &= tokens.size() >= 4;
		if (ifCorrect) {
			ifCorrect &= regex_match(tokens.at(0), ID);
			ifCorrect &= regex_match(tokens.at(1), TYPE);
			ifCorrect &= regex_match(tokens.at(2), NODE);
			ifCorrect &= regex_match(tokens.at(3), NODE);
			switch (tokens.size()) {
			case 4:
				ifCorrect &= tokens.at(0)[0] != 'T' && tokens.at(2) != tokens.at(3);
				break;
			case 5:
				ifCorrect &= tokens.at(0)[0] == 'T' && (tokens.at(2) != tokens.at(3) || tokens.at(3) != tokens.at(4));
				break;
			default:
				ifCorrect = false;
			}
		}
		return ifCorrect;
	}

	// Extracts data from string
	// Returns ("", "", -1, -1, -1) tuple if data is incorrect
	dataTuple readLine (string line) {
		istringstream iss(line);
		vector<string> tokens(istream_iterator<string>{iss}, istream_iterator<string>());

		if (ifCorrect(tokens)) {
			int last;
			if (tokens.size() == 4)
				last = -1;
			else
				last = stoi(tokens.at(4));
			return dataTuple(tokens.at(0), tokens.at(1), stoi(tokens.at(2)), stoi(tokens.at(3)), last);
		}
		else
			return dataTuple("", "", -1, -1, -1);
	}

	// Prints out the program results using partMap and orderMap
	void writeResults (pMap partMap, oMap orderMap) {
		pMap::iterator t;

		for (oMap::iterator it = orderMap.begin(); it != orderMap.end(); it++) {
			t = partMap.find(make_pair((it->first)[0], it->second));
			for (set<string, cmpByOrder>::iterator i = (t->second).begin(); i != (t->second).end(); i++) {
				if (i != (t->second).begin())
					cout << ", ";
				cout << *i;
				if (i != (t->second).begin())
					orderMap.erase(*i);
			}
			cout << ": " << (t->first).second << endl;
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

	// Registers a connection to the node
	void connect (set<int> *unconnectedNodeSet, set<int> *connectedNodeSet, int node) {
		if (!connectedNodeSet->count(node)) {
			if (unconnectedNodeSet->count(node)) {
				unconnectedNodeSet->erase(node);
				connectedNodeSet->insert(node);
			}
			else
				unconnectedNodeSet->insert(node);
		}
	}

	// Copies the data into partMap
	void populateMap (pMap *partMap, dataTuple data) {
		pair<char, string> key = make_pair(get<0>(data)[0], get<1>(data));
		pMap::iterator it = partMap->find(key);

		if (it == partMap->end()) {
			set<string, cmpByOrder> value;
			value.insert(get<0>(data));
			partMap->insert(make_pair(key, value));
		}
		else
			(it->second).insert(get<0>(data));
	}
}

int main() {
	set<string> idSet;
	set<int> unconnectedNodeSet, connectedNodeSet;
	pMap partMap;
	oMap orderMap;
	dataTuple data;
	bool ifConnectedToMass = false;
	string input;
	int licz = 1;

	while (getline(cin, input)) {
		if (input != "") {
			data = readLine(input);
			if (get<0>(data) == "" || idSet.find(get<0>(data)) != idSet.end()) {
				err(input, licz);
			}
			else {
				idSet.insert(get<0>(data));
				orderMap.insert(make_pair(get<0>(data), get<1>(data)));

				if ((get<2>(data) == 0) || (get<3>(data) == 0) || (get<4>(data) == 0))
					ifConnectedToMass = true;

				connect(&unconnectedNodeSet, &connectedNodeSet, get<2>(data));

				if (get<3>(data) != get<2>(data))
					connect(&unconnectedNodeSet, &connectedNodeSet, get<3>(data));

				if ((get<4>(data) != -1) && (get<4>(data) != get<2>(data)) && (get<4>(data) != get<3>(data)))
					connect(&unconnectedNodeSet, &connectedNodeSet, get<4>(data));

				populateMap(&partMap, data);
			}
		}
		licz++;
	}
	checkConnections(unconnectedNodeSet, ifConnectedToMass);
	writeResults(partMap, orderMap);
}
