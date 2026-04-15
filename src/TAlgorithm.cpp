#include "TAlgorithm.h"
#include <math.h>
#include <algorithm>
#include <numeric>






void TAlgorithm::safety_condition_check()
{
	/*
	Checks if the population is improving and if the population count is within limits.
	*/
	int pop_count = populations[0]->get_count();
	recent_values.push_back(improvement_check(populations));


	if (recent_values.size() > 5)
	{
		recent_values.erase(recent_values.begin());

		improve_condition = !all_of(recent_values.begin(), recent_values.end(), [](int x) { return x == 1; });

		if (!improve_condition) { cout << "Improvement condition triggered!" << endl; }
	}

	if (pop_count > max_population_count) { population_condition = false; 	cout << "Safety conditions triggered max pop count!" << endl;}

}

void TAlgorithm::look_for_all_time_best()
{
	for (auto& population : populations)
	{
		if (population->get_best_candidate().get_candidate_mark() > all_time_best_candidate.get_candidate_mark())
		{
			all_time_best_candidate = population->get_best_candidate();
			//cout << "All time best candidate: " << all_time_best.get_candidate_mark() << endl;
		}
	}
}

TAlgorithm::TAlgorithm(unsigned int candidates_count, unsigned int max_population_count, unsigned int min_improvement_proc, int improvement_size) {
	this->candidates_count = candidates_count;
	this->min_improvement_proc = min_improvement_proc;
	this->max_population_count = max_population_count;
}

void TAlgorithm::run()
{
	/*
	Runs the algorithm until the improvement condition is met or the population count exceeds the maximum limit.
	*/


	//Creating initial populations
	populations.push_back(new TPopulation(candidates_count));

	cout << "Population id: " << populations[0]->get_count() << endl;
	cout << "Best candidate: " << populations[0]->get_best_candidate().get_candidate_mark() << endl;
	cout << endl;


	while (safety_condition)
	{
		populations[0]->calculate();
		populations.push_back(new TPopulation(populations[0]));
		populations[1]->calculate();

		cout << "Population id: " << populations[0]->get_count() << endl;
		cout << "Best candidate: " << populations[0]->get_best_candidate().get_candidate_mark() << endl;	
		cout << endl;

		safety_condition_check();

		look_for_all_time_best();

		delete populations[0];
		populations[0] = nullptr;
		populations.erase(populations.begin());
		safety_condition = improve_condition && population_condition;
	}
	cout << "Algorithm finished!" << endl;
	cout << "All time best candidate: " << all_time_best_candidate.get_candidate_mark() << endl;
}

bool TAlgorithm::improvement_check(vector<TPopulation*>populations)
{
	/*
	Returns 1 if the improvement condition is met, otherwise returns 0.
	Checks the best candidate's mark in the last two populations and calculates the percentage difference.
	*/

	double val1 = populations[0]->get_best_candidate().get_candidate_mark();
	double val2 = populations[1]->get_best_candidate().get_candidate_mark();

	double proc_val = abs((val1 - val2) / (val2))*100;
	//cout << "proc val: " << proc_val << endl;
	return (proc_val < this->min_improvement_proc) ?  1 : 0;
}

