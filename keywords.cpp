#include <iostream>
#include <iomanip>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include "char_check.hpp"
using namespace std;

vector<string> wordsInDoc(ifstream &file)
{
    vector<string> words;
    string word;
    while (file >> word) {
        int i, len = word.size();
        for (i=0; i<len; i++) {
            word[i] = tolower(word[i]);
            if (isNotLetter(word[i])) {
                word.erase(i, 1);
                len = word.size();
                i--; } }
        if (word != "") words.push_back(word); }

    return words;
}

vector<pair<int, string> > reverseSort(unordered_map<string, int>& map)
{
    vector<pair<int, string> > reverseSorted;

    for (auto pair : map) {
        reverseSorted.emplace_back(pair.second, pair.first); }
    
    sort(reverseSorted.begin(), reverseSorted.end());
    
    for (int i=0; i<reverseSorted.size()/2; i++) {
        pair<int, string> temp = reverseSorted[i];
        reverseSorted[i] = reverseSorted[(reverseSorted.size()-1)-i];
        reverseSorted[(reverseSorted.size()-1)-i] = temp; }

    return reverseSorted; 
}

struct ANALYSIS {
    string word;
    int numInDoc;
    float freqInDoc;
    int numInAll;
    float freqInAll;
    float expected;
    float ratio;

    bool operator() (ANALYSIS i, ANALYSIS j) { return (i.ratio > j.ratio); }
} sortByRatio;

#define PC 5
vector<ANALYSIS> analyzeDoc(vector<string> docWords, vector<string>combinedDocWords, unordered_map<string, int> wordCntDoc, unordered_map<string, int> wordCntAll)
{
    vector<ANALYSIS> wordsAnalysis;

    int i=0;
    for (auto pair : wordCntDoc) {
        wordsAnalysis.push_back({});
        wordsAnalysis[i].word = pair.first;
        wordsAnalysis[i].numInDoc = pair.second;
        wordsAnalysis[i].numInAll = wordCntAll[pair.first];
        int wordsInDoc = docWords.size();
        int wordsInAll = combinedDocWords.size();
 
        float freqInDoc = (float)wordsAnalysis[i].numInDoc / wordsInDoc;
        wordsAnalysis[i].freqInDoc = freqInDoc;

        float freqInAll = (float)wordsAnalysis[i].numInAll / wordsInAll;
        wordsAnalysis[i].freqInAll = freqInAll;

        float expect = wordsInDoc * freqInAll;
        wordsAnalysis[i].expected = expect;
        
        float enrich = (wordsAnalysis[i].numInDoc + PC) / (expect + PC);
        wordsAnalysis[i].ratio = enrich;

        i++; }
    
    return wordsAnalysis;
}

#define N 50
int main(int argc, char** argv)
{
    if (argc > 1 && argc < 4) {
        ifstream combinedDoc;
        combinedDoc.open(argv[1]);
        vector<string> combinedDocWords = wordsInDoc(combinedDoc);
        
        unordered_map<string, int> wordCntAll;
        for (auto x : combinedDocWords) {
            if (wordCntAll.count(x) > 0) {
                wordCntAll[x]++; }
            else {
                wordCntAll[x] = 1; } }

        vector<pair<int, string> > wordCntAllSorted = reverseSort(wordCntAll);
        
        if (argc == 2) {
            cout << endl;
            for (int i=0; i<N; i++) {
                cout << wordCntAllSorted[i].first << ' ' << wordCntAllSorted[i].second << endl; }
            cout << endl; }

        if (argc == 3) {
            ifstream doc;
            doc.open(argv[2]); 
            vector<string> docWords = wordsInDoc(doc);

            unordered_map<string, int> wordCntDoc;
            for (auto x : docWords) {
                if (wordCntDoc.count(x) > 0) {
                    wordCntDoc[x]++; }
                else {
                    wordCntDoc[x] = 1; } }

            cout << endl;
            cout << left;
            cout << setw(18) << "WORD";
            cout << setw(12) << "num(doc)";
            cout << setw(15) << "freq(doc)";
            cout << setw(12) << "num(all)";
            cout << setw(14) << "freq(all)";
            cout << setw(13) << "expected";
            cout << "ratio" << endl;

            cout << setw(18) << "----------";
            cout << setw(12) << "--------";
            cout << setw(15) << "---------";
            cout << setw(12) << "--------";
            cout << setw(14) << "---------";
            cout << setw(12) << "--------";
            cout << "------" << endl;

            vector<ANALYSIS> wordsAnalysis = analyzeDoc(docWords, combinedDocWords, wordCntDoc, wordCntAll);
            sort(wordsAnalysis.begin(), wordsAnalysis.end(), sortByRatio);
            for (int i=0; i<N; i++) {
                cout << setw(20) << wordsAnalysis[i].word;
                cout << setw(10) << wordsAnalysis[i].numInDoc;
                cout << fixed << setprecision(6) << setw(17) << wordsAnalysis[i].freqInDoc;
                cout << setw(10) << wordsAnalysis[i].numInAll;
                cout << fixed << setprecision(6) << setw(16) << wordsAnalysis[i].freqInAll;
                cout << fixed << setprecision(1) << setw(10) << wordsAnalysis[i].expected;
                cout << fixed << setprecision(4) << wordsAnalysis[i].ratio << endl; }
            cout << endl; } }
    
    else {
        cout << "\nPlease enter:" << endl;
        cout << "\n\t1) file name of concatenated documents and" << endl;
        cout << "\t2) file name of a particular document (optional)" << endl;
        cout << "\ninto the command line.\n" << endl; }
}
