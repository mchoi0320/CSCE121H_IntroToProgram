#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

struct COORD {
	string city;
	float lat;
	float lon;
	vector<float> distances;
	float closest_dist;
	string closest_city;
	float farthest_dist;
	string farthest_city;
};

float deg_to_rad(float angle)
{
	angle = angle * (M_PI / 180);
	return angle;
}

float calc_dist(float lat1, float lon1, float lat2, float lon2)
{
	lat1 = deg_to_rad(lat1); lat2 = deg_to_rad(lat2);
	lon1 = deg_to_rad(lon1); lon2 = deg_to_rad(lon2);
	int R = 3961;

	float dlat = lat2 - lat1, dlon = lon2 - lon1;

	float dist = 2 * R * asin(sqrt(pow(sin(dlat/2),2) + cos(lat1) * cos(lat2) * pow(sin(dlon/2),2)));

	return dist;
}

/* int validate_input_city(string input_city, vector<COORD> cities)
{
	bool search = true;
	int i=0, input_city_pos;
	while (search && i<cities.size()) {
		if (input_city == cities[i].city) {
			input_city_pos = i;
			search = false; }
	i++; }
	
	cout << input_city_pos << '\n';
	cout << i << '\n';
	
	if (i > 52 && input_city_pos != 52) {
		cout << "Please enter a valid city name: ";
		cin >> input_city; cout << '\n';
		validate_input_city(input_city, cities); }
		
	return input_city_pos;
} */


int main(int argc, char** argv)
{
	if (argc < 2) { cout << "Please enter a file name (at minimum) into the command line.\n"; exit(0);}
	
	ifstream file;
	file.open(argv[1]);

	string line, data;
	vector<COORD> cities;
	int i=0;
	while (!file.eof()) {
		while (getline(file, line)) {
			cities.push_back(COORD());
			vector<string> temp;
			stringstream ss(line);
			while (ss >> data) {
				temp.push_back(data); }
			cities[i].city = temp[0];
			cities[i].lat = stof(temp[1]);
			cities[i].lon = stof(temp[2]);
			i++; } }

	// find the closest city to each and the distance between each of them
	float dist; int close_pos, far_pos; 
	for (int i=0; i<cities.size(); i++) {
		float min = 24901, max = 0; // set Earth's circumference as minimum
		for (int j=0; j<cities.size(); j++) {
			dist = calc_dist(cities[i].lat, cities[i].lon, cities[j].lat, cities[j].lon);
			cities[i].distances.push_back(dist);
			if (dist <= min && dist != 0) {
				min = dist;
				close_pos = j; }
			if (dist > max && dist != 0) {
				max = dist;
				far_pos = j; }
		cities[i].closest_dist = min; cities[i].closest_city = cities[close_pos].city;
		cities[i].farthest_dist = max; cities[i].farthest_city = cities[far_pos].city; } }
	
	// print closest and farthest cities of each city and the two closest and two farthest cities if user does not provide input other than a file name
	if (argc < 3) {
		for (int i=0; i<cities.size(); i++) {
			cout << left;
			cout << setw(18) << cities[i].city;
			cout << "closest=" << setw(15) << cities[i].closest_city;
			stringstream ss1;
			ss1 << '(' << fixed << setprecision(1) << cities[i].closest_dist << " mi)";
			cout << right;
			cout << setw(10) << ss1.str() << ", ";
			cout << left;
			cout << "farthest=" << setw(15) << cities[i].farthest_city;
			stringstream ss2;
			ss2 << '(' << fixed << setprecision(1) << cities[i].farthest_dist << " mi)";
			cout << right;
			cout << setw(10) << ss2.str() << '\n'; }
			
		cout << "--------------------------------------------------------------------------------\n";
		
		//vector<string> closest_cities; vector<string> farthest_cities;
		float min = 24901, max = 0;
		int closest_cities_city1_pos, farthest_cities_city1_pos;
		for (int i=0; i<cities.size(); i++) {
			if (cities[i].closest_dist < min) {
				min = cities[i].closest_dist;
				closest_cities_city1_pos = i; }
			if (cities[i].farthest_dist > max) {
				max = cities[i].farthest_dist;
				farthest_cities_city1_pos = i; } }
		
		int closest_cities_city2_pos, farthest_cities_city2_pos;
		for (int i=0; i<cities.size(); i++) {
			if (cities[i].closest_dist == cities[closest_cities_city1_pos].closest_dist && cities[i].city != cities[closest_cities_city1_pos].city) {
				closest_cities_city2_pos = i; }
			if (cities[i].farthest_dist == cities[farthest_cities_city1_pos].farthest_dist && cities[i].city != cities[farthest_cities_city1_pos].city) {
				farthest_cities_city2_pos = i; } }
					
		cout << "Closest cities:  " << cities[closest_cities_city1_pos].city << " and " << cities[closest_cities_city2_pos].city << ", ";
		cout << fixed << setprecision(1) << "dist=" << cities[closest_cities_city1_pos].closest_dist << " mi\n";
		cout << "Farthest cities: " << cities[farthest_cities_city1_pos].city << " and " << cities[farthest_cities_city2_pos].city << ", ";
		cout << fixed << setprecision(1) << "dist=" << cities[farthest_cities_city1_pos].farthest_dist << " mi\n";
		
/*  		for (int i=0; i<cities.size(); i++) {
			for (int j=0; j<cities.size(); j++) {
				if (cities[i].closest_city == cities[j].city && cities[j].closest_city == cities[i].city) {
					cout << "Closest cities: " << cities[i].city << " and " << cities[j].city << ", ";
					cout << "dist=" << cities[i].closest_dist << " mi\n"; }
				if (cities[i].farthest_city == cities[j].city && cities[j].farthest_city == cities[i].city) {
					cout << "Farthest cities: " << cities[i].city << " and " << cities[j].city << ", ";
					cout << "dist=" << cities[i].farthest_dist << " mi\n"; }
			}
		} */
	}

	// output N closest cities to city C if user inputs a city name and an integer value
	if (argc > 2) {
		
		string input_city = argv[2];
		//int input_city_pos = validate_input_city(input_city, cities);
		//input_city = cities[input_city_pos].city;

		// validate user-input integer value
		int input_num;
		if (argc < 4) {
			cout << "Please enter the number of closest cities you would like to view: "; //exit(0);
			cin >> input_num; cout << '\n'; }
		else {
			input_num = atoi(argv[3]); }
		
		while (input_num > cities.size()-1 || input_num < 1) {
			if (input_num == 0) { cout << "[No information to display]\n"; exit(0); }
			else {
				cout << "[There are " << cities.size()-1 << " cities available for display.]\n";
				cout << "Please enter a valid integer between 0 and " << cities.size()-1 << ": ";
				cin >> input_num; cout << '\n'; } }
		
		// search for input_city in cities until found and get its index
		bool search = true;
		int i=0, input_city_pos;
		while (search || i<cities.size()) {
			if (input_city == cities[i].city) {
				input_city_pos = i;
				search = false; }
		i++; }

		// sort the city-to-city distances of input_city in ascending order
		sort(cities[input_city_pos].distances.begin(), cities[input_city_pos].distances.end());

		// print the input_num closest cities to input_city
		for (int i=1; i<input_num+1; i++) {
			int j=0;
			while (j<cities.size()) {
				for (int k=0; k<cities[j].distances.size(); k++) {
					if (cities[input_city_pos].distances[i] == cities[j].distances[k] && cities[j].city != input_city) {
						cout << left << setw(15) << cities[j].city; } }
				j++; }
			stringstream ss;
			ss << '(' << fixed << setprecision(1) << cities[input_city_pos].distances[i] << " mi)";
			cout << right << setw(10) << ss.str() << '\n'; } }
}
