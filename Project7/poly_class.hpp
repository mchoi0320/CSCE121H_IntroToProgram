#include <tuple>
#include <vector>
#include <string>
using namespace std;

class Term {
    float coefficient;
    int exponent;

    public:
        Term(string term);
        Term(float c, int e);
        bool operator==(const Term& t);
        bool operator<(const Term& t);
        pair<float, int> parse_term(string term);
        float find_coefficient(string term);
        int find_exponent(string term);
        void set_coefficient(float c);
        void set_exponent(int e);
        float get_coefficient();
        int get_exponent();
        void print(int i);
};

class Poly {
    vector<Term> poly;

    public:
        Poly();
        Poly(string expr);
        Poly(const Poly& old);
        void parse_expr(string expr);
        void add_term(Term t);
        //void remove_term(Term t);
        void remove_zeros();
        void descend_sort();
        vector<Term> get_poly();
        float eval(float x);
        Poly add(Poly p);
        Poly multiply(Poly p);
        Poly derive();
        float newton_raphson(float guess);
        float root();
        void print();
};