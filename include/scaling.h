// function declaration of scaling
#ifndef SCALING_H
#define SCALING_H

void scaling(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double beta[2][7], long double gamma[2][7], long double xi[4][6], int iteration);

#endif