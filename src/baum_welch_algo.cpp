// function definition of baum_welch_algo
#include "baum_welch_algo.h"
#include "forward_algo.h"
#include "forward_backward_algo.h"
#include <iostream>
using namespace std;

void update_initial_prob(long double initial_prob[2], long double gamma[2][7]){
    initial_prob[0] = gamma[0][0];
    initial_prob[1] = gamma[1][0];
}

void update_transition_prob(long double transition_prob[2][2], long double gamma[2][7], long double xi[4][6]){
    int row {0};
    for (int i {0}; i <= 1; ++i){
        long double denomiator {0};
        for (int t {0}; t < 6; ++t){
            denomiator += gamma[i][t];
        }

        for (int j {0}; j <= 1; ++j){
            long double numerator {0};
            for (int t {0}; t < 6; ++t){
                numerator += xi[row][t];
            }
            transition_prob[i][j] = numerator/denomiator;

            row += 1;
        }
    }
}

void update_emission_prob(long double emission_prob[2][2], long double gamma[2][7], int observed_seq[7]){
    int count {0};
    for (int i {0}; i <= 1; ++i){
        long double denomiator {0};
        for (int t {0}; t < 7; ++t){
            denomiator += gamma[i][t];
        }

        for (int j {0}; j <= 1; ++j){
            // the probability that state i emit j
            long double numerator {0};
            for (int t {0}; t < 7; ++t){
                count %= 2;
                if (observed_seq[t] == count){
                    numerator += gamma[i][t];
                }
            }
            emission_prob[i][j] = numerator/denomiator;
            ++count;
        }
    }
}

void calculate_xi(long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double beta[2][7], long double xi[4][6]){
    int row {0};
    for (int t {0}; t < 6; ++t){
        for (int i {0}; i <= 1; ++i){
            for (int j {0}; j <= 1; ++j){
                xi[row][t] = (alpha[i][t] * transition_prob[i][j] * emission_prob[j][observed_seq[t+1]] * beta[j][t+1])/
                                (alpha[0][t] * transition_prob[0][0] * emission_prob[0][observed_seq[t+1]] * beta[0][t+1] +
                                alpha[0][t] * transition_prob[0][1] * emission_prob[1][observed_seq[t+1]] * beta[1][t+1] +
                                alpha[1][t] * transition_prob[1][0] * emission_prob[0][observed_seq[t+1]] * beta[0][t+1] +
                                alpha[1][t] * transition_prob[1][1] * emission_prob[1][observed_seq[t+1]] * beta[1][t+1]);
                ++row;
            }
        }
        row = 0;
    }
}

void baum_welch_algo(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double beta[2][7], long double gamma[2][7], long double xi[4][6], int iteration){
    
    for (int i {0}; i < iteration; ++i){

        forward_algo(initial_prob, transition_prob, emission_prob, observed_seq, alpha);
        forward_backward_algo(initial_prob, transition_prob, emission_prob, observed_seq, alpha, beta, gamma);

        // calculate xi
        calculate_xi(transition_prob, emission_prob, observed_seq, alpha, beta, xi);

        // update initial probability
        update_initial_prob(initial_prob, gamma);

        // update transition probability
        update_transition_prob(transition_prob, gamma, xi);

        // update emission probability
        update_emission_prob(emission_prob, gamma, observed_seq);
    }
}