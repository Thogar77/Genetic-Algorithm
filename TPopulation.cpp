#include "TPopulation.h"
#include "TAlgorithm.h"

unsigned int TPopulation::count = 0;

double TPopulation::get_total_rate()
{
	return total_rate;
}

TPopulation::TPopulation(int pop_size) {
	TPopulation::count += 1;
	_id = TPopulation::count;
	this->candidates_count = pop_size;
	for (int i = 0; i < pop_size; i++) {
		this->Tcandidate.push_back(TCandidate());
	}
}

TPopulation::TPopulation(TPopulation* population)
{
	/*
	Creates a new population based on an existing one.
	Promotes candidates from the existing population and mutates them to create new candidates.
	*/

	TPopulation::count += 1;
	_id = TPopulation::count;
	this->candidates_count = population->get_candidates_count();

	vector<TCandidate*>promoted_candidates;
	vector<TCandidate*>new_candidates;
	int max = 100;
	int cross_threshold = 75;


	for (int i = 0; i < candidates_count/2; i++)
	{
		double random_num = rand() % (max + 1);
		if (random_num < cross_threshold) {
			//If random number is less than threshold, cross promoted candidates and mutate them
			vector<TCandidate> crossed_candidates = population->cross_promoted();

			Tcandidate.insert(Tcandidate.end(), crossed_candidates.begin(), crossed_candidates.end());
		}
		else {
			for(int k = 0; k < 2; k++) {
				//If random number is greater than threshold, promote candidate and mutate it
				TCandidate* promoted_candidate = population->promote_candidate();
				string mutated_genes = mutate(promoted_candidate->to_bitstring());
				promoted_candidate->from_bitstring(mutated_genes);

				Tcandidate.push_back(*promoted_candidate);
			}
		}
	}


}

TPopulation::~TPopulation()
{
	//cout << "Usunieto populacje nr: " << this->_id << endl;
}

vector<int> TPopulation::create_dataset(int data_size)
{
	/*
	Creates a dataset of size data_size by promoting candidates from the population.
	*/

	vector<int> new_dataset;
	for (int i = 0; i<data_size; i++)
	{
		new_dataset.push_back(promote_candidate()->get_id());
	}
	return new_dataset;
}

void TPopulation::show_histogram(vector<int> dataset)
{
	/*
	Prints a histogram of the dataset.
	Each candidate is represented by a bar, where the length of the bar is proportional to the percentage of times the candidate appeared in the dataset.
	Candidates are sorted by their percentage share in descending order.
	*/

	vector<std::pair<int, int>> dataset_vector;
	int dataset_size = dataset.size();
	for (int i = 0; i < candidates_count; i++)
	{
		int appeared_times = std::count(dataset.begin(), dataset.end(), Tcandidate[i].get_id());
		float percent_share = ((float)appeared_times / (float)dataset_size) * 100;
		dataset_vector.push_back(std::make_pair(i, percent_share));
	}

	std::sort(dataset_vector.begin(), dataset_vector.end(),
		[](const std::pair<int,int>& a, const std::pair<int,int>& b) {
			return a.second > b.second; // lub > dla malejąco
		});
	
	for (int k = 0; k < candidates_count; k++) {
		cout << "[";
		for (int i = 0; i < 20; i++)
		{
			if (dataset_vector[k].second / 5 > i) {
				cout << "-";
			}
			else {
				cout << " ";
			}

		}
		cout << "]";
		cout << "Candidate id :" << dataset_vector[k].first << " " << "  " << dataset_vector[k].second << "%" << endl;
	}
}

void TPopulation::calculate() {

	/*
	Calculates the rate of each candidate in the population.
	*/

	this->total_rate = 0;
	for (int i = 0; i < candidates_count; i++) {
		Tcandidate[i].rate();
		total_rate = total_rate + Tcandidate[i].get_candidate_mark();
		if (Tcandidate[i].get_candidate_mark() > best_val) {
			best_val = Tcandidate[i].get_candidate_mark();
			BestCandidate = Tcandidate[i];
		}
	}
}
void TPopulation::info(bool shortForm)
{
	/*
	Shows information about the population.
	When shortForm is true, it shows only the best candidate and total rate.
	When shortForm is false, it shows all candidates and their marks.
	*/

	if (!shortForm) 
	{
		cout << "======POPULATION======\n";
		cout << "Population ID: " << _id << "/" << this->count << endl;

		for (int i = 0; i < candidates_count; i++) {
			double curr_candidate_mark = Tcandidate[i].get_candidate_mark();
			cout << "==candidate#" << i << ": " << curr_candidate_mark << "\n";
		}
	}
	else 
	{
		cout << "== Population #" << _id << "  ||  " << "best val: " << best_val << " || "<< "Total rate: "<< total_rate<< endl;

	}
}

TCandidate TPopulation::get_best_candidate()
{	
	return BestCandidate;
}

TCandidate* TPopulation::promote_candidate()
{
	/*
	Roulette wheel selection is used to select a candidate based on its rate.
	Returns a pointer to the selected candidate.
	*/
	int min = 0;
	int max = this->total_rate;
	int comparision_val = 0;
	int  random_num = min + rand() % (max - min + 1);
	
	for (int i = 0; i < candidates_count; i++)
	{
		comparision_val = comparision_val + Tcandidate[i].get_candidate_mark();
		if (comparision_val >= random_num) {
			TCandidate* promoted_candidate = &Tcandidate[i];
			promoted_candidate->rate(false);
			//cout << " #" << i;
			return promoted_candidate;
		}

	}
	throw std::runtime_error("No candidate was promoted. Check the population data.");

}

vector<TCandidate> TPopulation::cross_promoted()
{
	/*
	Promotes two candidates and crosses them to create two new candidates.
	Mutates the new candidates and returns them in a vector.
	*/

	//Create a vector to hold the new candidates
	vector<TCandidate> new_candidates;

	//Promote two candidates
	TCandidate* parent1 = promote_candidate();
	TCandidate* parent2 = promote_candidate();

	
	TCandidate child1 = *parent1;
	TCandidate child2 = *parent2;

	int p1_bitsize = parent1->get_genes_bit_length();


	string new_gene1;
	string new_gene2;

	string genes1_bitstr;
	string genes2_bitstr;

	int random_num;

	genes1_bitstr = parent1->to_bitstring();
	genes2_bitstr = parent2->to_bitstring();

	random_num = rand() % (p1_bitsize);
	
	//Cross the genes at a random point
	new_gene1 = genes1_bitstr.substr(0, random_num) + genes2_bitstr.substr(random_num);
	new_gene2 = genes2_bitstr.substr(0, random_num) + genes1_bitstr.substr(random_num);

	//Mutate the new genes
	mutate(new_gene1);
	mutate(new_gene2);

	child1.from_bitstring(new_gene1);
	child2.from_bitstring(new_gene2);

	new_candidates.push_back(child1);
	new_candidates.push_back(child2);
	return new_candidates;

}


string TPopulation::mutate(string gene)
{
	/*
	Mutates a gene by flipping bits with a certain mutation chance.
	*/

	int mutation_chance = 5;
	int length = gene.length();

	for (int i = 0; i < length; i++) {
		double random_num = rand() % 100 + 1;

		if (random_num < mutation_chance)
		{
			gene[i] = (gene[i] == '0') ? '1' : '0';
		}
	}
	return gene;
}