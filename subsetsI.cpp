#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
using namespace std;

vector<vector<string> > get_subsets_iter(vector<string> inputs)
{
	vector<vector<string> > all_subsets = {{}};

	for (int i=0; i<inputs.size(); i++) {
		string input = inputs[i];
		vector<vector<string> > generated_subsets;
		
		for (vector<string> subset : all_subsets) {
			vector<string> new_subset;
			new_subset.insert(new_subset.end(), subset.begin(), subset.end());
			new_subset.push_back(input);
			generated_subsets.push_back(new_subset); }

		all_subsets.insert(all_subsets.end(), generated_subsets.begin(), generated_subsets.end()); }

	return all_subsets;
}

int main(int argc, char** argv)
{
	if (argc < 2) { cout << "Please enter a list of space-separated strings.\n"; exit(0); }
	
	vector<string> inputs;
	
	for (int i=1; i<argc; i++) {
		inputs.push_back(argv[i]); }

	vector<vector<string> > subsets = get_subsets_iter(inputs);

	for (int i=0; i<subsets.size(); i++) {
		for (int j=0; j<subsets[i].size(); j++) {
			cout << subsets[i][j] << " "; }
		cout << "\n"; }
}
