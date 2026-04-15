#pragma once
#include "TPopulation.h"
#include <vector>

class TAlgorithm {
private:
	
	vector<TPopulation*>populations;
	vector<bool>recent_values;
	TCandidate all_time_best_candidate;

	unsigned int candidates_count;
	unsigned int max_population_count;
	unsigned int min_improvement_proc;
	double improvement_proc;
	bool improve_condition = true;
	bool population_condition = true;
	void safety_condition_check();
	bool safety_condition = improve_condition && population_condition;
	void look_for_all_time_best();
public:
	TAlgorithm(unsigned int candidates_count, unsigned int max_population_count, unsigned int min_improvement_proc ,int improvement_size = 5);
	void run();
	bool improvement_check(vector<TPopulation*>populations);
};