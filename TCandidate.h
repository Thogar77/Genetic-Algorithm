#pragma once
#include <iostream>
#include<vector>

#include "TParam.h"

using namespace std;

class TCandidate {
private:
	double mark = 0;
	vector<TParam> genes;
	vector<int> genes_lengths;
	int _id;
	
	static unsigned int count_id;
public:

	TCandidate();
	TCandidate(double gene0, double gene1);
	~TCandidate();
	void rate(bool out = false);
	void info();
	double get_candidate_mark() { return this->mark; }
	TParam get_gen(unsigned int iterator);
	vector<TParam> get_genes() { return this->genes; };
	int get_id() { return _id; };
	string to_bitstring() const;
	void from_bitstring(const std::string& bitstr);
	int get_genes_bit_length() const;

private:
};