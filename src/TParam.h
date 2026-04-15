#pragma once
#include <string>
#include <bitset>

class TParam {

private:
	std::string name;
	double x_start, x_end, dx;
	int val_id;

public:
	TParam(double x_start, double x_end, double dx);
	TParam(double x_start, double x_end, double dx, double val);
	TParam(std::string name, double x_start, double x_end, double dx);
	TParam(std::string name, double x_start, double x_end, double dx, double val);


	void set_name(std::string name) { this->name = name; }
	std::string get_name() { return name; }

	void set_range(double x_start, double x_end, double dx);

	void set_rand_val();
	void set_val(double val) { val_id = get_val_id(val); }
	double get_val() { return x_start + val_id * dx; }

	std::string to_bitstring() const;
	void from_bitstring(const std::string &bitstr);
	int bit_length() const;

	void info();

private:
	int get_val_id(double val);

};