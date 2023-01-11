// function declaration of baum_welch_algo
#ifndef BAUM_WELCH_ALGO_H
#define BAUM_WELCH_ALGO_H

void calculate_xi(long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double beta[2][7], long double xi[4][6]);
void update_initial_prob(long double initial_prob[2], long double gamma[2][7]);
void update_transition_prob(long double transition_prob[2][2], long double gamma[2][7], long double xi[4][6]);
void update_emission_prob(long double emission_prob[2][2], long double gamma[2][7], int observed_seq[7]);
void baum_welch_algo(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7], long double alpha[2][7], long double beta[2][7], long double gamma[2][7], long double xi[4][6], int iteration);

#endif