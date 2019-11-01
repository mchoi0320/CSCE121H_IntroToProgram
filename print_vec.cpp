#include <iostream>
#include <vector>
#include <string>
#include "print_vec.hpp"
using namespace std;

void print_vec_str(vector<string> vec)
{
	for (int i=0; i<vec.size(); i++) {
		cout << vec[i] << endl; }
}
