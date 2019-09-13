#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main(int argc, char** argv)
{
	ifstream input;
	input.open(argv[1]);
	int val, sum=0, cnt=0;
	while (input >> val)
	{
		sum += val;
		cnt += 1;
	}
	cout << "Mean of " << cnt << " values is " << fixed << setprecision(1) << (float)sum/cnt << "."  << endl;
}
