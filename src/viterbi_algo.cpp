// function definition of viterbi_algo
#include "viterbi_algo.h"
#include <iostream>
#include <iomanip>
using namespace std;

void viterbi_decoding(int viterbi_state_sequence[]){

    // print out the result of viterbi decoding
    cout << "\nViterbi Decoding:" << endl;

    cout << right << setw(10) << "Time  ";
    for (int i {1}; i <= 7; ++i){
        cout << left << setw(10) << i; 
    }
    cout << endl;
    
    cout << right << setw(10) << "State  ";
    for (int i {0}; i < 7; ++i){
        cout << left << setw(6) << "state " << left << setw(4) << viterbi_state_sequence[i];
    }
    cout << endl;
}

void print_viterbi(long double viterbi_table[2][7]){
    cout << "\nViterbi:" << endl;

    cout << right << setw(10) << "Time  ";
    for (int i {1}; i <= 7; ++i){
        cout << left << setw(12) << i;
    }
    cout << endl;

    for (int i {0}; i < 2; ++i){
        cout << right << setw(7) << "State " << i << "  ";
        for (int j {0}; j < 7; ++j){
            cout << left << setw(12) << viterbi_table[i][j];
        }
        cout << endl;
    }
}

void print_viterbi_path(int viterbi_path[2][7]){
    cout << "\nViterbi Path:" << endl;

    cout << right << setw(10) << "Time  ";
    for (int i {1}; i <= 7; ++i){
        cout << left << setw(10) << i;
    }
    cout << endl;

    for (int i {0}; i < 2; ++i){
        cout << right << setw(7) << "State " << i << "  ";
        for (int j {0}; j < 7; ++j){
            if (viterbi_path[i][j] == -1){
                cout << left << setw(10) << "none";
            }
            else{
                cout << left << setw(6) << "state " << left << setw(4) << viterbi_path[i][j];
            }
        }
        cout << endl;
    }
}

void viterbi(long double initial_prob[2], long double transition_prob[2][2], long double emission_prob[2][2], int observed_seq[7]){
    
    long double viterbi_table[2][7] = {0};
    int viterbi_path[2][7] = {0};

    viterbi_path[0][0] = viterbi_path[1][0] = -1;

    for (int i {0}; i <= 1; ++i){
        viterbi_table[i][0] = initial_prob[i] * emission_prob[i][observed_seq[0]];
    }

    for (int i {1}; i <= 6; ++i){

        long double from_state_0 = viterbi_table[0][i-1]*transition_prob[0][0];
        long double from_state_1 = viterbi_table[1][i-1]*transition_prob[1][0];
        viterbi_table[0][i] = emission_prob[0][observed_seq[i]] * max({from_state_0, from_state_1});
        if (max({from_state_0, from_state_1}) == from_state_0){
            viterbi_path[0][i] = 0;
        }
        else{
            viterbi_path[0][i] = 1;
        }

        from_state_0 = viterbi_table[0][i-1]*transition_prob[0][1];
        from_state_1 = viterbi_table[1][i-1]*transition_prob[1][1];
        viterbi_table[1][i] = emission_prob[1][observed_seq[i]] * max({from_state_0, from_state_1});
        if (max({from_state_0, from_state_1}) == from_state_0){
            viterbi_path[1][i] = 0;
        }
        else{
            viterbi_path[1][i] = 1;
        }
    }

    int viterbi_state_sequence[7] = {-1};

    // trace back the viterbi path
    if (max({viterbi_table[0][6], viterbi_table[1][6]}) == viterbi_table[0][6]){
        viterbi_state_sequence[6] = 0;
        viterbi_state_sequence[5] = viterbi_path[0][6];
    }
    else if (max({viterbi_table[0][6], viterbi_table[1][6]}) == viterbi_table[1][6]){
        viterbi_state_sequence[6] = 1;
        viterbi_state_sequence[5] = viterbi_path[1][6];
    }

    for (int i {5}; i > 0; --i){
        if (viterbi_path[viterbi_state_sequence[i]][i] == 0){
            viterbi_state_sequence[i-1] = 0;
        }
        else if (viterbi_path[viterbi_state_sequence[i]][i] == 1){
            viterbi_state_sequence[i-1] = 1;
        }
        else{
            cout << "error" << endl;
        }
    }

    // print results
    print_viterbi(viterbi_table);
    print_viterbi_path(viterbi_path);
    viterbi_decoding(viterbi_state_sequence);
}
