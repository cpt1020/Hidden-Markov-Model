// function definition of forward_backward_algo
#include "forward_backward_algo.h"
#include <iostream>
#include <iomanip>
using namespace std;

void calculate_gamma(long double alpha[2][7], long double beta[2][7], long double gamma[2][7]){
    for (int i {0}; i <= 1; ++i){
        for (int j {0}; j < 7; ++j){
            gamma[i][j] = (alpha[i][j] * beta[i][j])/(alpha[0][j] * beta[0][j] + alpha[1][j] * beta[1][j]);
        }
    }
}

void forward_backward_algo(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double beta[2][7], long double gamma[2][7]){

    // initialize the last beta value to 1
    beta[0][6] = beta[1][6] = 1;

    // calculate the remaining beta
    for (int i {5}; i >=0; --i){
        beta[0][i] = transition_prob[0][0] * emission_prob[0][observed_seq[i+1]] * beta[0][i+1] +
                     transition_prob[0][1] * emission_prob[1][observed_seq[i+1]] * beta[1][i+1];
        beta[1][i] = transition_prob[1][0] * emission_prob[0][observed_seq[i+1]] * beta[0][i+1] +
                     transition_prob[1][1] * emission_prob[1][observed_seq[i+1]] * beta[1][i+1];
    }

    // calculate gamma
    calculate_gamma(alpha, beta, gamma);
}

void posterior_decoding(long double gamma[2][7]){

    // print out the result of posterior decoding
    cout << "\nPosterior Decoding:" << endl;

    cout << right << setw(8) << "Time  ";
    for (int i {1}; i <= 7; ++i){
        cout << left << setw(10) << i; 
    }
    cout << endl;
    
    cout << right << setw(8) << "State  ";
    for (int i {0}; i < 7; ++i){
        if (max({gamma[0][i], gamma[1][i]}) == gamma[0][i]){
            cout << left << setw(10) << "state 0";
        }
        else if (max({gamma[0][i], gamma[1][i]}) == gamma[1][i]){
            cout << left << setw(10) << "state 1";
        }
    }
    cout << endl;
}