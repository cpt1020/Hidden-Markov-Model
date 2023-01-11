// function definition of forward_algo
#include "forward_algo.h"
#include <iostream>
using namespace std;

void forward_algo(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7]){

    // initialize the first 2 alpha values
    alpha[0][0] = initial_prob[0] * emission_prob[0][observed_seq[0]];
    alpha[1][0] = initial_prob[1] * emission_prob[1][observed_seq[0]];

    // calculate the remaining alpha values
    for (int i {1}; i < 7; ++i){
        alpha[0][i] = (alpha[0][i-1] * transition_prob[0][0] + alpha[1][i-1] * transition_prob[1][0]) * emission_prob[0][observed_seq[i]];
        alpha[1][i] = (alpha[0][i-1] * transition_prob[0][1] + alpha[1][i-1] * transition_prob[1][1]) * emission_prob[1][observed_seq[i]];
    }
}