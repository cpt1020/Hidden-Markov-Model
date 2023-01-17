// function definition of scaling
#include "scaling.h"
#include "baum_welch_algo.h"
#include "forward_backward_algo.h"
#include "utils.h"
#include <math.h>
#include <iostream>
using namespace std;

void calculate_alpha_alpha_hat_scaling_factor(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double alpha_hat[2][7], long double scaling_factor[7]){
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
}

void calculate_beta_beta_hat(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double beta[2][7], long double beta_hat[2][7], long double scaling_factor[7]){
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
}

void print_log_base_10_prob(long double scaling_factor[7]){
    long double log_scaling_factor_sum {0};

    for (int i {0}; i < 7; ++i){
        log_scaling_factor_sum += log10(scaling_factor[i]);
    }
    
    cout << "\nThe log base 10 probability of the observed sequence under the new HMM is " << -(log_scaling_factor_sum) << endl;
    cout << "The probability is " << pow(10, (-log_scaling_factor_sum)) << endl;
}

void scaling(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double beta[2][7], long double gamma[2][7], long double xi[4][6], int iteration){
    
    long double alpha_hat[2][7] = {0};
    long double beta_hat[2][7]  = {0};
    long double scaling_factor[7] = {0};

    for (int i {0}; i < iteration; ++i){

        // alpha, alpha hat, scaling factor
        calculate_alpha_alpha_hat_scaling_factor(initial_prob, transition_prob, emission_prob, observed_seq, alpha, alpha_hat, scaling_factor);

        // beta, beta hat
        calculate_beta_beta_hat(initial_prob, transition_prob, emission_prob, observed_seq, beta, beta_hat, scaling_factor);

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

    // print results
    print_probability(initial_prob, transition_prob, emission_prob);
    calculate_alpha_alpha_hat_scaling_factor(initial_prob, transition_prob, emission_prob, observed_seq, alpha, alpha_hat, scaling_factor);
    print_log_base_10_prob(scaling_factor);
}