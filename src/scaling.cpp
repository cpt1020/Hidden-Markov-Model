// function definition of scaling
#include "scaling.h"
#include "baum_welch_algo.h"
#include "forward_backward_algo.h"
#include <math.h>
#include <iostream>
using namespace std;

void scaling(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double beta[2][7], long double gamma[2][7], long double xi[4][6], int iteration){
    
    long double alpha_hat[2][7] = {0};
    long double beta_hat[2][7]  = {0};
    long double scaling_factor[7] = {0};

    for (int i {0}; i < iteration; ++i){

        // initialize the first 2 alpha values
        alpha[0][0] = initial_prob[0] * emission_prob[0][0];
        alpha[1][0] = initial_prob[1] * emission_prob[1][0];

        // calculate scaling factor 1
        scaling_factor[0] = 1 / (alpha[0][0]+ alpha[1][0]);

        // calculate alpha_hat at time = 1
        alpha_hat[0][0] = alpha[0][0] / (alpha[0][0]+ alpha[1][0]);
        alpha_hat[1][0] = alpha[1][0] / (alpha[0][0]+ alpha[1][0]);

        // calculate the remaining alpha, alpha_hat, and scaling factor
        for (int i {1}; i < 7; ++i){
            alpha[0][i] = (alpha_hat[0][i-1] * transition_prob[0][0] + alpha_hat[1][i-1] * transition_prob[1][0]) * emission_prob[0][observed_seq[i]];
            alpha[1][i] = (alpha_hat[0][i-1] * transition_prob[0][1] + alpha_hat[1][i-1] * transition_prob[1][1]) * emission_prob[1][observed_seq[i]];
            scaling_factor[i] = 1 / (alpha[0][i]+ alpha[1][i]);
            alpha_hat[0][i] = alpha[0][i] / (alpha[0][i]+ alpha[1][i]);
            alpha_hat[1][i] = alpha[1][i] / (alpha[0][i]+ alpha[1][i]);
        }

        // initialize the last beta value
        beta[0][6] = beta[1][6] = 1;
        beta_hat[0][6] = beta[0][6] * scaling_factor[6];
        beta_hat[1][6] = beta[1][6] * scaling_factor[6];

        // calculate beta and beta_hat
        for (int i {5}; i >=0; --i){
            beta[0][i] = transition_prob[0][0] * emission_prob[0][observed_seq[i+1]] * beta_hat[0][i+1] +
                        transition_prob[0][1] * emission_prob[1][observed_seq[i+1]] * beta_hat[1][i+1];
            beta[1][i] = transition_prob[1][0] * emission_prob[0][observed_seq[i+1]] * beta_hat[0][i+1] +
                        transition_prob[1][1] * emission_prob[1][observed_seq[i+1]] * beta_hat[1][i+1];
            beta_hat[0][i] = beta[0][i] * scaling_factor[i];
            beta_hat[1][i] = beta[1][i] * scaling_factor[i];
        }

        // gamma probability
        calculate_gamma(alpha_hat, beta_hat, gamma);

        // xi
        calculate_xi(transition_prob, emission_prob, observed_seq, alpha_hat, beta_hat, xi);

        // update new initial probability
        update_initial_prob(initial_prob, gamma);

        // update new transition probability
        update_transition_prob(transition_prob, gamma, xi);

        // update new emission probability
        update_emission_prob(emission_prob, gamma, observed_seq);
    }

    long double log_scaling_factor_sum {0};
    for (int i {0}; i < 7; ++i){
        log_scaling_factor_sum += log10(scaling_factor[i]);
    }

    cout << "\nThe log base 10 probability of the observed sequence is " << -(log_scaling_factor_sum) << endl;
    cout << "The probability is " << pow(10, (-log_scaling_factor_sum)) << endl;
}