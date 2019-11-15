#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <iomanip>
#include "matrix.hpp"
using namespace std;

int main(int argc, char** argv)
{
    if (argc < 2) {
        cout << "Please enter a file name containing a list of coordinates." << endl;
        exit(0); }

    ifstream file;
    file.open(argv[1]);

    RotMat rot2D(30);
    vector<vector<pair<float, float> > > points;

    string point, coordinate;
    while (getline(file, point)) {
        istringstream ss(point);
        vector<float> temp;
        while (ss >> coordinate) {
            temp.push_back(stof(coordinate)); }
        RotMat point2D(temp[0], temp[1]);

        vector<pair<float, float> > hourlyPoint;
        /*for (int i=0; i<12; i++) {
            point2D.print();
            Matrix newPoint = prod(point2D, rot2D);
            newPoint.print();
            Matrix point2D = newPoint;
            point2D.print(); }
        cout << endl;*/
        Matrix hour1  = prod(point2D, rot2D); hourlyPoint.push_back(make_pair( hour1.getVal(0,0),  hour1.getVal(0,1)));
        Matrix hour2  = prod(hour1,   rot2D); hourlyPoint.push_back(make_pair( hour2.getVal(0,0),  hour2.getVal(0,1)));
        Matrix hour3  = prod(hour2,   rot2D); hourlyPoint.push_back(make_pair( hour3.getVal(0,0),  hour3.getVal(0,1)));
        Matrix hour4  = prod(hour3,   rot2D); hourlyPoint.push_back(make_pair( hour4.getVal(0,0),  hour4.getVal(0,1)));
        Matrix hour5  = prod(hour4,   rot2D); hourlyPoint.push_back(make_pair( hour5.getVal(0,0),  hour5.getVal(0,1)));
        Matrix hour6  = prod(hour5,   rot2D); hourlyPoint.push_back(make_pair( hour6.getVal(0,0),  hour6.getVal(0,1)));
        Matrix hour7  = prod(hour6,   rot2D); hourlyPoint.push_back(make_pair( hour7.getVal(0,0),  hour7.getVal(0,1)));
        Matrix hour8  = prod(hour7,   rot2D); hourlyPoint.push_back(make_pair( hour8.getVal(0,0),  hour8.getVal(0,1)));
        Matrix hour9  = prod(hour8,   rot2D); hourlyPoint.push_back(make_pair( hour9.getVal(0,0),  hour9.getVal(0,1)));
        Matrix hour10 = prod(hour9,   rot2D); hourlyPoint.push_back(make_pair(hour10.getVal(0,0), hour10.getVal(0,1)));
        Matrix hour11 = prod(hour10,  rot2D); hourlyPoint.push_back(make_pair(hour11.getVal(0,0), hour11.getVal(0,1)));
        Matrix hour12 = prod(hour11,  rot2D); hourlyPoint.push_back(make_pair(hour12.getVal(0,0), hour12.getVal(0,1)));

        points.push_back(hourlyPoint); }

        for (int i=0; i<12; i++) {
            cout << "----------------" << endl;
            cout << "Hour " << i+1 << ':' << endl;
            for (int j=0; j<points.size(); j++) {
                cout << fixed << setprecision(3) << setw(7) << points[j][i].first << ' ';
                cout << fixed << setprecision(3) << setw(7) << points[j][i].second << endl; } }
        cout << "----------------" << endl;
}
