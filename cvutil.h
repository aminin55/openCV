#pragma once
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
using namespace std;

struct parameters {
	int num_x = 1;	// Кол-во знакомест по горизонтали             
	int num_y = 2;	// Кол-во знакомест по вертикали               
	double delta_x = 21.5; // Ширина одного знакоместа             
	double delta_y = 33.0; // Длина одного знакоместа                   
	int start_x = 28; // Откуда строим линиии по вертикали         
	int start_y = 23; // Откуда строим линии по горизонтали        
	vector<vector<bool>> positions;
};

void clear_spaces(string& s) {
	s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
}

bool parse_config(parameters& params, string filename) {
	map<string, double> kv;
	filename = filename.substr(0, filename.find(".")) + ".cfg";
	ifstream fin(filename.c_str());
	if (!fin.is_open()) {
		cerr << "Can't open " << filename << endl;
		return false;
	}
	std::string line;
	while (getline(fin, line)) {
		cout << endl << "$debug";
		clear_spaces(line);
		if (line[0] != '/' && !isdigit(line[0]) && line.size() > 1) {
			string key = line.substr(0, line.find("="));
			string value = line.substr(line.find("=") + 1);
			cout << '"' << key << "\" \"" << value << '"' << endl;
			kv[key] = stod(value);
		}
		else if (line[0] == '0' || line[0] == '1') {
			vector<bool> temp;
			for (auto s : line) {
				if (s == '0') temp.push_back(false);
				else if (s == '1') temp.push_back(true);
				else {
					cout << "Parse config error. Waiting for 0 or 1. Got" << s << endl;
					return false;
				}
				cout << temp.back();
			}
			params.positions.push_back(temp);
		}
	}
	fin.close();
	if (kv.count("delta_x"))
		params.delta_x = kv.at("delta_x");
	else
		return false;
	if (kv.count("delta_y"))
		params.delta_y = kv.at("delta_y");
	else
		return false;
	if (kv.count("start_x"))
		params.start_x = (int)kv.at("start_x");
	else
		return false;
	if (kv.count("start_y"))
		params.start_y = (int)kv.at("start_y");
	else
		return false;
	if (kv.count("num_x"))
		params.num_x = (int)kv.at("num_x");
	else
		return false;
	if (kv.count("num_y"))
		params.num_y = (int)kv.at("num_y");
	else
		return false;
	if ((int)params.positions.size() != params.num_y) {
		cout << params.positions.size() << " != " << params.num_y << endl;
		return false;
	}

	for (auto v : params.positions) {
		if ((int)v.size() != (int)params.num_x) {
			cout << v.size() << " != " << (int)params.num_x << endl;
			return false;
		}
	}
	return true;
}

