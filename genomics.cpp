#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <cmath>
#include "codons.hpp"
using namespace std;

string read_genome(ifstream &fasta)
{
	string line, genome="";
	
	while(!fasta.eof()) {
		while(getline(fasta, line)) {
			genome += line; } }
	
	return genome;
}

float calc_GC_content(string genome)
{
	int GC_count=0;
	for (int i=0; i<genome.size(); i++) {
		if (genome[i] == 'G' || genome[i] == 'C') {
			GC_count++; } }

	float GC_content = ((float)GC_count / genome.size()) * 100;

	return GC_content;
}

vector<float> analyze_genome(string genome)
{
	vector<float> genome_stats;

	// genome length
	genome_stats.push_back(genome.size());

	// GC_content
	genome_stats.push_back(calc_GC_content(genome));	

	return genome_stats;
}

vector<int> find_longest_homopolymer(string genome)
{
	int cnt=1, max_length=0, coord;
	for (int i=1; i<genome.size(); i++) {
		if (genome[i] == genome[i-1]) {
			cnt++; }
		else {
			cnt=1; }
		if (cnt > max_length) {
			max_length = cnt;
			coord = (i+1) - max_length; } }

	vector<int> longest_homopolymer;
	longest_homopolymer.push_back(max_length);
	longest_homopolymer.push_back(coord);

	return longest_homopolymer;
}

struct GENE {
	string description;
	int start_coord;
	int end_coord;
	string strand;
	string gene_name;
	string gene_ID;
};

vector<GENE> read_gene(ifstream &prot_table)
{
	string line, field;
	vector<GENE> genes;

	int i=0;
	while (!prot_table.eof()) {
		while(getline(prot_table, line)) {
			genes.push_back(GENE());
			vector<string> temp;
			stringstream ss(line);
			while(getline(ss, field, '\t')) {
				temp.push_back(field); }		
			genes[i].description = temp[0];
			genes[i].start_coord = stoi(temp[1]);
               	        genes[i].end_coord = stoi(temp[2]);
               		genes[i].strand = temp[3];
			genes[i].gene_name = temp[7];
			genes[i].gene_ID = temp[8];
			i++; } }

	return genes;
}

float calc_stdev(vector<float> &vals, float mean, int num_vals)
{
	float diff_sq, sum_diff_sq=0, stdev;

	for (int i=0; i<num_vals; i++) {
		diff_sq = pow(vals[i]-mean,2);
		sum_diff_sq += diff_sq; }
	stdev = sqrt(sum_diff_sq / (num_vals));

	return stdev;
}

vector<string> calc_gene_stats(vector<GENE> genes)
{
	vector<string> gene_stats;
	vector<float> gene_sizes;
	int num_genes = genes.size();
	int size, sum_gene_sizes=0,  min=num_genes, max=0;
	float mean, stdev;	

	for (int i=0; i<num_genes; i++) {
		size = (genes[i].end_coord - genes[i].start_coord) + 1;
		gene_sizes.push_back(size);
		sum_gene_sizes += size;
		if (size < min) min = size;
		if (size > max) max = size; }
	mean = (float)sum_gene_sizes / num_genes;
	stdev = calc_stdev(gene_sizes, mean, num_genes);

	gene_stats.push_back(to_string(min));
	gene_stats.push_back(to_string(max));
	gene_stats.push_back(to_string(mean));
	gene_stats.push_back(to_string(stdev));
	gene_stats.push_back(to_string(sum_gene_sizes));

	return gene_stats;
}

vector<string> calc_intergenic_region_stats(vector<GENE> genes)
{
	vector<string> intergenic_region_stats;
	float mean;
	int num_regions = genes.size()-1;
	int size, sum_region_sizes, smallest=num_regions, small_pos, largest=0, large_pos;

	for (int i=0; i<num_regions; i++) {
		size = (genes[i+1].start_coord - genes[i].end_coord) - 1;
		sum_region_sizes += size;
		if (size < smallest) {
			smallest = size;
			small_pos = i; }
		if (size > largest) {
			largest = size;
			large_pos = i; } }
	mean = (float)sum_region_sizes / num_regions;

	intergenic_region_stats.push_back(to_string(mean));
	intergenic_region_stats.push_back(to_string(smallest));
	intergenic_region_stats.push_back(to_string(small_pos));
	intergenic_region_stats.push_back(to_string(largest));
	intergenic_region_stats.push_back(to_string(large_pos));
	
	return intergenic_region_stats;
}

void print_homopolymer_occurrence(string genome, vector<GENE> genes)
{
        vector<int> longest_homopolymer = find_longest_homopolymer(genome);
        int homopolymer_length = longest_homopolymer[0], homopolymer_start = longest_homopolymer[1];

        cout << "Longest homopolymer: ";
        for (int i=homopolymer_start; i<homopolymer_start+homopolymer_length; i++) {
                cout << genome[i]; }
        cout << " (len=" << homopolymer_length << " bp) at coord " << homopolymer_start << ", ";

	bool search = true; int i=0;
	string occurrence; int pos;
	while (search) {
		if (homopolymer_start >= genes[i].start_coord && homopolymer_start <= genes[i].end_coord) {
			occurrence = "in";
			pos = i;
			search = false; }
		if (homopolymer_start > genes[i].end_coord && homopolymer_start < genes[i+1].start_coord) {
			occurrence = "after";
			pos = i;
			search = false; }
		i++; }

	cout << occurrence << ' ' << genes[pos].gene_ID << '/' << genes[pos].gene_name << '\n';
}

string reverse_complement(string gene_seq)
{	
	string rev_comp_gene = gene_seq;

	// reverse the order of the gene sequence
	char temp;
	for (int i=0; i<rev_comp_gene.size()/2; i++) {
		temp = rev_comp_gene[i];
		rev_comp_gene[i] = rev_comp_gene[rev_comp_gene.size()-i-1];
		rev_comp_gene[rev_comp_gene.size()-i-1] = temp; }
		
	// get the complement
	for (int i=0; i<rev_comp_gene.size(); i++) {
		if (rev_comp_gene[i] == 'A') rev_comp_gene[i] = 'T';
		else if (rev_comp_gene[i] == 'T') rev_comp_gene[i] = 'A';
		else if (rev_comp_gene[i] == 'G') rev_comp_gene[i] = 'C';
		else if (rev_comp_gene[i] == 'C') rev_comp_gene[i] = 'G'; }
		 
	return rev_comp_gene;
}

string translation(string gene_seq)
{
	string codon, amino_acid_seq;
	for (int i=0; i<gene_seq.size()/3; i++) {
		codon = gene_seq.substr(i*3, 3);
		amino_acid_seq += aa(codon); }
	
	return amino_acid_seq;
}

void print_seq(string input_gene, vector<GENE> genes, string genome)
{
	bool search = true;
	int i=0, gene_pos=-1;
	//for (int i=0; i<genes.size(); i++) {
		while (i<genes.size() && search) {
			if (input_gene == genes[i].gene_name || input_gene == genes[i].gene_ID) {
				gene_pos = i;
				search = false; }
			i++; }

	if (gene_pos > -1) {
		int gene_start = genes[gene_pos].start_coord-1;
		int gene_end = genes[gene_pos].end_coord-1;
		int gene_length = (gene_end - gene_start) + 1;
		
		string gene_seq = genome.substr(gene_start, gene_length);
		
		if (genes[gene_pos].strand == "-") {
			gene_seq = reverse_complement(gene_seq); }
		
		int gene_seq_length = gene_seq.size();
		int gene_seq_lines = ceil((float)gene_seq_length / 50);
		
		cout << "\nGene sequence of " << input_gene << ":\n";
		for (int i=0; i<gene_seq_lines; i++) {
			cout << setw(10) << (i*50)+1 << ' ' << gene_seq.substr(i*50, 50) << '\n'; }
	
		string amino_acid_seq = translation(gene_seq);
		
		int aa_seq_length = amino_acid_seq.size();
		int aa_seq_lines = ceil((float)aa_seq_length / 50);
		
		cout << "\nAmino acid translation:\n";
		for (int i=0; i<aa_seq_lines; i++) {
			cout << setw(10) << (i*50)+1 << ' ' << amino_acid_seq.substr(i*50, 50) << '\n'; } }
	else {
		cout << "\n[No information to display for " << input_gene << ". | Reason: nonexistent gene]\n"; }
}


int main(int argc, char** argv)
{
	if (argc < 2) {
		cout << "Please enter:\n\n";
		cout << "1) .fasta file\n";
		cout << "2) .prot_table file (optional)\n";
		cout << "3) desired gene name/ID (optional)\n\n";
		cout << "into the command line.\n";
		exit(0); }


	ifstream fasta;
	fasta.open(argv[1]);

	// read and output genome sequence
	string first_line; getline(fasta, first_line);
	string genome = read_genome(fasta);

	cout << "Reading: " << first_line.substr(1,first_line.size()-1) << "\n\n";	

	// calculate and output basic genome statistics (length, GC content)
	vector<float> genome_stats = analyze_genome(genome);
	int genome_length = genome_stats[0]; float GC_content = genome_stats[1];

	cout << "Length: " << genome_length << " bp\n";
	cout << fixed << setprecision(1) <<  "GC content: " << GC_content << "%\n";

	// find and output information about the longest homopolymer
	vector<int> longest_homopolymer = find_longest_homopolymer(genome);
	int homopolymer_length = longest_homopolymer[0], homopolymer_start = longest_homopolymer[1];

	cout << "Longest homopolymer: ";
	for (int i=homopolymer_start; i<homopolymer_start+homopolymer_length; i++) {
		cout << genome[i]; }
	cout << " (len=" << homopolymer_length << " bp) at coord " << homopolymer_start << "\n";


	if (argc > 2) {
		ifstream prot_table;
		prot_table.open(argv[2]);

		vector<GENE> genes;
		genes = read_gene(prot_table);

		// calculate and print gene statistics
		int num_genes = genes.size();
		cout << "\nNumber of genes: " << num_genes << "\n";

		vector<string> gene_stats = calc_gene_stats(genes);
		int min_gene_size = stoi(gene_stats[0]), max_gene_size = stoi(gene_stats[1]);
		float mean_gene_size = stof(gene_stats[2]), stdev_gene_size = stof(gene_stats[3]);
		cout << "Gene sizes: [" << min_gene_size << ", " << max_gene_size << "], mean=" << mean_gene_size << " bp, stdev=" << stdev_gene_size << "\n";

		int sum_gene_sizes = stoi(gene_stats[4]);
		float genome_frac = ((float)sum_gene_sizes / genome_length) * 100;
		cout << "Genome fraction: " << genome_frac << "%\n";
	
		// calculate and print intergenic region statistics
		vector<string> intergenic_region_stats = calc_intergenic_region_stats(genes);
		float mean_region_size = stof(intergenic_region_stats[0]);
		int smallest_region = stoi(intergenic_region_stats[1]), smallest_region_pos = stoi(intergenic_region_stats[2]);
		int largest_region = stoi(intergenic_region_stats[3]), largest_region_pos = stoi(intergenic_region_stats[4]);
	
		cout << "\nMean intergenic region size: " << mean_region_size << " bp\n";
		cout << "Smallest intergenic region: " << smallest_region << " bp (after " << genes[smallest_region_pos].gene_ID << '/' << genes[smallest_region_pos].gene_name << ")\n";
		cout << "Largest intergenic region: " << largest_region << " bp (after " << genes[largest_region_pos].gene_ID << '/' << genes[largest_region_pos].gene_name << ")\n";

		print_homopolymer_occurrence(genome, genes);


		if (argc > 3) {
			string input_gene = argv[3];
	
			// print gene sequence and its amino acid translation
			print_seq(input_gene, genes, genome); } }


	return 0;
}
