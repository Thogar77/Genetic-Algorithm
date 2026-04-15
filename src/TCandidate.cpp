#include "TCandidate.h"

unsigned int TCandidate::count_id = 0;
TCandidate::TCandidate() {
	TCandidate::count_id += 1;
	this->_id = TCandidate::count_id;
	TParam tail_length{ "Tail Length",0,100,1};
	TParam height{ "Height" ,0,10,1};
	genes.push_back(tail_length);
	genes.push_back(height);
	rate();
}

TCandidate::TCandidate(double gene0, double gene1)
{
	TCandidate::count_id += 1;
	this->_id = TCandidate::count_id;
	TParam tail_length{ "Tail Length",0,100,1,gene0 };
	TParam height{ "Height" ,0,10,1,gene1 };
	genes.push_back(tail_length);
	genes.push_back(height);
	rate();
}

TCandidate::~TCandidate()
{
	/*
	Destructor for TCandidate class.
	Currently does not perform any specific cleanup actions.
	*/

	//cout << "Destructor called for candidate with ID: " << _id << endl;
}

void TCandidate::info()
{
	/*
	Shows the information of the candidate, including its ID, genes, and rating.
	*/

	cout << "Genes count: " << genes.size() << endl;

	cout << genes[0].get_name() << " value: " << genes[0].get_val() << endl;
	cout << genes[1].get_name() << " value: " << genes[1].get_val() << "\n\n";
	cout << "rate: " << get_candidate_mark() << endl;
	cout <<"\n\n";


}

TParam TCandidate::get_gen(unsigned int iterator)
{
	if (iterator <= genes.size()) {
		return genes[iterator];
	}
}


void TCandidate::rate(bool out)
{

	/*
	Calculates the rating of the candidate based on its genes.
	Might output the calculated rating if `out` is true.
	*/

	double rating = (genes[0].get_val() * genes[0].get_val()) + genes[1].get_val();
	if (out) { cout << "Rated Value: " << rating << endl; };
	this->mark = rating;
	for(int i = 0;i < genes.size(); i++)
	{
		genes_lengths.push_back(genes[i].bit_length());
	}
}

std::string TCandidate::to_bitstring() const
{	
	/*
	Returns a string representation of the candidate's genes in binary format.
	*/

	string result;
	for (const TParam& gene : genes)
	{
		result += gene.to_bitstring();
}
	return result;
}

void TCandidate::from_bitstring(const std::string& bitstr) {
	
	/*
	Splits the bitstring into segments according to the lengths of the genes,
	then initializes each gene with its corresponding segment,
	and calculates the rate of the candidate.
	*/

	int gene_count = genes.size();
	int cut_length = 0;
	for (int i = 0; i < gene_count; ++i) {

		std::string segment = bitstr.substr(cut_length, genes_lengths[i]);
		genes[i].from_bitstring(segment);
		cut_length += genes[i].bit_length();
	
	}
	rate();
}

int TCandidate::get_genes_bit_length() const
{
	/*
	Returns the total bit length of all genes in the candidate.
	*/

	int total_length = 0;
	for (const TParam& gene : genes)
	{
		int comparison_length = gene.bit_length();
			total_length += comparison_length;
	}
	return total_length;
}


