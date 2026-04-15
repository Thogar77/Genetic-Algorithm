#include <iostream>
#include <math.h>
#include <cstdlib>

#include "TParam.h"
using namespace std;

TParam::TParam(double x_start, double x_end, double dx) 
{
	set_range(x_start, x_end, dx);
	name = "";
	val_id = 0;
	set_rand_val();
}

TParam::TParam(double x_start, double x_end, double dx, double val)
{
	set_range(x_start, x_end, dx);
	set_val(val);
	name = "";
}
TParam::TParam(std::string name, double x_start, double x_end, double dx) : TParam::TParam(x_start, x_end, dx) {
	set_name(name);
	set_rand_val();

}
TParam::TParam(std::string name, double x_start, double x_end, double dx, double val) : TParam::TParam(x_start, x_end, dx, val) {
	set_name(name);
}

void TParam::set_range(double x_start, double x_end, double dx)
{
	this->x_start = x_start;
	this->x_end = x_end;
	this->dx = dx;
}

int TParam::get_val_id(double val)
{

	if (val < x_start) return 0;
	else if (val > x_end)return(x_end - x_start) / dx;
	else 
	{
		double x = x_start;
		int _id = 0;

		while (fabs(x + _id * dx - val) > dx / 2)_id++;
		return _id;
	}
}

void TParam::set_rand_val()
{
	/*
	Sets a random value for the parameter within its defined range.
	*/

	int vals_count = fabs(x_end - x_start) / dx + 1;
	val_id = rand() % vals_count;
}

std::string TParam::to_bitstring() 
const
{
	/*
	Returns a string of bits representing the value of the parameter.
	The string length is determined by the max bit amount required to describe value.
	*/

	int temp_bitsize = bit_length();
	std::bitset <32> bits(val_id);

	return bits.to_string().substr(32 - temp_bitsize, temp_bitsize);
}

void TParam::from_bitstring(const std::string& bitstr)
{
	/*
	Reads a string of bits and sets the value of the parameter accordingly.
	*/

	if (static_cast<int>(std::bitset<32>(bitstr).to_ulong()) >= x_end) 
	{
		set_val(x_end);
	}
	else {
		val_id = static_cast<int>(std::bitset<32>(bitstr).to_ulong());
	}
}

int TParam::bit_length() const {

	/*
	Returns the number of bits needed to represent the parameter value.
	*/

	int values = round((x_end - x_start) / dx) + 1;
	int bits = 0;
	while ((1 << bits) < x_end) ++bits;
	return bits;
}


void TParam::info()
{
	/*
	Shows the information about the parameter, including its name, range, value, and ID.
	*/

	cout << "\n";
	cout << "===========================\n";
	cout << "==name: " << name << "\n";
	cout << "==range: [" << x_start << "; " << x_end << "; " << dx << "]\n";
	cout << "==value: " << get_val() << "\t (id: #" << val_id << ")\n";
	cout << "===========================\n";
}