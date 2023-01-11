#ifndef UTILS_H
#define UTILS_H

void print_probability(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2]);
void print_prob_of_observed_seq(long double alpha[2][7]);
void print_alpha(long double alpha[2][7]);
void print_beta(long double beta[2][7]);
void print_gamma(long double gamma[2][7]);

#endif