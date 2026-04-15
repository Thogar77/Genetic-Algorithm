#include <iostream>
#include"TPopulation.h"
#include "TParam.h"
#include "TAlgorithm.h"
#include<cstdlib>
#include<time.h>

using namespace std;

int main()
{

	srand(time(0));

	TAlgorithm algorithm(14, 20, 5); // 10 candidates, max 10 populations, min improvement 5%	
	algorithm.run();


	return 0;
}