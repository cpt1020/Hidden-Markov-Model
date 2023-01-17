#include <iostream>
#include <string.h>
#include <cstdlib>
#include "src/forward_algo.h"
#include "src/forward_backward_algo.h"
#include "src/baum_welch_algo.h"
#include "src/scaling.h"
#include "src/viterbi_algo.h"
#include "src/utils.h"
using namespace std;

int main(int argc, char* argv[]){

    int observed_seq[7] = {0, 0, 1, 1, 1, 1, 0};
    long double initial_prob[2] = {0.5, 0.5};
    long double transition_prob[2][2] = {{0.8, 0.2}, {0.2, 0.8}};
    long double emission_prob[2][2] = {{0.9, 0.1}, {0.2, 0.8}};
    
    // declare alpha, beta, gamma, and xi, and initialze all values to 0
    long double alpha[2][7] = {0};
    long double beta[2][7] = {0};
    long double gamma[2][7] = {0};
    long double xi[4][6] = {0};

    // iteration for Baum-Welch
    int iteration {0};

    if (strcmp(argv[1], "viterbi") == 0){
        viterbi(initial_prob, transition_prob, emission_prob, observed_seq);
    }
    else if (strcmp(argv[1], "forward") == 0){
        // run forward algorithm
        forward_algo(initial_prob, transition_prob, emission_prob, observed_seq, alpha);

        // print results
        print_prob_of_observed_seq(alpha);
        print_alpha(alpha);
    }
    else if (strcmp(argv[1], "forward-backward") == 0){
        // run forward-backward algorithm
        forward_algo(initial_prob, transition_prob, emission_prob, observed_seq, alpha);
        forward_backward_algo(initial_prob, transition_prob, emission_prob, observed_seq, alpha, beta, gamma);
        posterior_decoding(gamma);

        // print results
        print_alpha(alpha);
        print_beta(beta);
        print_gamma(gamma);
    }
    else if (strcmp(argv[1], "baum-welch") == 0){
        try {
            if (argc == 2){
                throw 1;
            }
        }
        catch (int &ex){
            cerr << "please enter iteration for Baum-Welch" << endl;
        }
        iteration = atoi(argv[2]);

        // run Baum-Welch algorithm
        baum_welch_algo(initial_prob, transition_prob, emission_prob, observed_seq, alpha, beta, gamma, xi, iteration);
        
        // print results
        print_probability(initial_prob, transition_prob, emission_prob);
        forward_algo(initial_prob, transition_prob, emission_prob, observed_seq, alpha);
        print_prob_of_observed_seq_BW(alpha);
    }
    else if (strcmp(argv[1], "scaling") == 0){
        try {
            if (argc == 2){
                throw 1;
            }
        }
        catch (int &ex){
            cerr << "please enter iteration for scaled Baum-Welch" << endl;
        }
        iteration = atoi(argv[2]);

        // run scaled Baum-Welch algorithm
        scaling(initial_prob, transition_prob, emission_prob, observed_seq, alpha, beta, gamma, xi, iteration);
        
    }
    else{
        cout << "please enter valid argument" << endl;
    }    


    return 0;
}