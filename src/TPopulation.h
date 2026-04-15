#pragma once
#include <iostream>
#include <vector>
#include<algorithm>
#include <bitset>
#include "TCandidate.h"

using namespace std;

class TPopulation {
private:
	static unsigned int count;
	unsigned int _id;
	unsigned int candidates_count;
	vector<TCandidate> Tcandidate;
	TCandidate BestCandidate;
	double total_rate = 0;
	double best_val = 0;


public:
	TPopulation(int pop_size);
	TPopulation(TPopulation* population);
	~TPopulation();

	vector<int> create_dataset(int data_size);
	void show_histogram(vector<int> dataset);
	double get_total_rate();
	void calculate();
	void info(bool shortForm = true);
	TCandidate get_best_candidate();
	unsigned int get_count() { return count; };
	unsigned int get_candidates_count() { return candidates_count; };
	TCandidate* promote_candidate();
	vector<TCandidate> cross_promoted();
	string mutate(string gene);
private:

};