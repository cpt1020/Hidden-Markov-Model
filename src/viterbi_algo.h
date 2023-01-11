// function declaration of viterbi_algo
#ifndef VITERBI_ALGO_H
#define VITERBI_ALGO_H

void viterbi(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7]);

#endif