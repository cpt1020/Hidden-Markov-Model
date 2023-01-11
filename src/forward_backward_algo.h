// function declaration of forward_backward_algo
#ifndef FORWARD_BACKWARD_ALGO_H
#define FORWARD_BACKWARD_ALGO_H

void calculate_gamma(long double alpha[2][7], long double beta[2][7], long double gamma[2][7]);
void forward_backward_algo(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double beta[2][7], long double gamma[2][7]);
void posterior_decoding(long double gamma[2][7]);

#endif