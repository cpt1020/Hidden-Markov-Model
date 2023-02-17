// function declaration of forward_algo
#ifndef FORWARD_ALGO_H
#define FORWARD_ALGO_H

void forward_algo(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7]);

#endif