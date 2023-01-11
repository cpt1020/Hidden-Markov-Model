#include "utils.h"
#include <iomanip>
#include <iostream>
using namespace std;

void print_probability(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2]){

    cout << "\nInitial Probability:" << endl;
    for (int i {0}; i < 2; ++i){
        cout << "State " << i << ": " << initial_prob[i] << endl;
    }

    cout << "\nTransition Probability:" << endl;
    cout << "          " << left << setw(12) << "State 0" << left << setw(12) << "State 1" << endl;
    for (int i {0}; i < 2; ++i){
        cout << "State " << i << "   ";
        for (int j {0}; j < 2; ++j){
            cout << left << setw(12) << transition_prob[i][j];
        }
        cout << endl;
    }

    cout << "\nEmission Probability:" << endl;
    cout << "          " << left << setw(12) << "0" << left << setw(12) << "1" << endl;
    for (int i {0}; i < 2; ++i){
        cout << "State " << i << "   ";
        for (int j {0}; j < 2; ++j){
            cout << left << setw(12) << emission_prob[i][j];
        }
        cout << endl;
    }
}

void print_prob_of_observed_seq(long double alpha[2][7]){
    cout << "\nThe probability of the observed sequence is " << (alpha[0][6]+alpha[1][6]) << endl;
}

void print_alpha(long double alpha[2][7]){
    cout << "\nAlpha:" << endl;
    cout << right << setw(10) << "Time  ";
    for (int i {1}; i <= 7; ++i){
        cout << left << setw(12) << i;
    }
    cout << endl;

    for (int i {0}; i < 2; ++i){
        cout << right << setw(7) << "State " << i << "  ";
        for (int j {0}; j < 7; ++j){
            cout << left << setw(12) << alpha[i][j];
        }
        cout << endl;
    }
}

void print_beta(long double beta[2][7]){
    cout << "\nBeta:" << endl;
    cout << right << setw(10) << "Time  ";
    for (int i {1}; i <= 7; ++i){
        cout << left << setw(12) << i;
    }
    cout << endl;

    for (int i {0}; i < 2; ++i){
        cout << right << setw(7) << "State " << i << "  ";
        for (int j {0}; j < 7; ++j){
            cout << left << setw(12) << beta[i][j];
        }
        cout << endl;
    }
}

void print_gamma(long double gamma[2][7]){
    cout << "\nGamma:" << endl;
    cout << right << setw(10) << "Time  ";
    for (int i {1}; i <= 7; ++i){
        cout << left << setw(12) << i;
    }
    cout << endl;

    for (int i {0}; i < 2; ++i){
        cout << right << setw(7) << "State " << i << "  ";
        for (int j {0}; j < 7; ++j){
            cout << left << setw(12) << gamma[i][j];
        }
        cout << endl;
    }
}