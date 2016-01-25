//
//  main.c
//  CMPUT313_Assignment1
//
//  Created by ZhangShuming on 16/1/22.
//  Copyright © 2016年 ZhangShuming. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "simulator.h"

//b 50 1000 4000 0.001 50 1000 5000000 ['5', '24', '24', '70', '83', '53']


int main(int argc, const char * argv[]) {
    char M;         // the error model used: "I" for Independent, "B" for Burst
    int A;          // the feedback time
    int K;          // the number of blocks. F must be a multiple of K
    int F;          // the size of a frame
    float e;        // the probability of a bit in error
    int B;          // burst length. 0 for the independent model
    int N;          // non-burst length. 0 for the independent model
    int R;          // the length of the simulation (in bit time units)
    int T;          // the number of trials
    int i;
    srand(time(NULL));

    
    scanf("%c %d %d %d %f %d %d %d [\'%d\'", &M, &A, &K, &F, &e, &B, &N, &R, &T);
    int trial[T];
    for (i = 0; i < T; i++) scanf(", '%d'", &trial[i]);
    

    printInputParameters(M, A, K, F, e, B, N, R, T, trial);
    
    // Determine the error model
    int independent;
    if (M == 'i' || M == 'I') {
        independent = 1;
    } else if ((M == 'b' || M == 'B')) {
        independent = 0;
        e = e * (N + B) / B;
    } else {
        puts("Error: Unexisted Error Model");
        exit(-1);
    }
    
    
    int BlockLength = calcLengthOfBlock(F, K);
    int Clock = 0, re_tx, CorrectFrame = 0, TotalFrame = 0, tx = 0;
    // Start the simulation loop
    while (Clock < R) {
        re_tx = 0;
        for (i = 0; i < K; i++) {
            if (generateRandomErrors(BlockLength, e, independent, tx, B, N) > 1) re_tx = 1;
            tx += BlockLength;

        }
        if (re_tx == 0) CorrectFrame++;
        TotalFrame++;
        Clock += BlockLength * K + A;
    }

    
    printf("The number of correctly received frames is %d \n", CorrectFrame);
    printf("The number of total transmissions is %d \n", TotalFrame);

    return 0;
}

// Print the input parameters
void printInputParameters(char M, int A, int K, int F, float e, int B, int N, int R, int T, int trial[]) {
    int i;
    puts("SIMULATION STARTS");
    printf("M = %c\n", M);
    printf("A = %d\n", A);
    printf("K = %d\n", K);
    printf("F = %d\n", F);
    printf("e = %g\n", e);
    printf("B = %d\n", B);
    printf("N = %d\n", N);
    printf("R = %d\n", R);
    
    printf("T = ['%d'", T);
    for (i = 0; i < T; i++) {
        printf(", '%d'", trial[i]);
    }
    printf("]\n");
}

// Calculate the length of block after adding HSBC bits
int calcLengthOfBlock(int F, int K) {
    int r = 0, i = 1;
    if (F%K != 0) {
        puts("Error: F is not a multiple of K");
        exit(-1);
    }
    int originalBlock = F/K;
    while (originalBlock != 0) {
        if ((i & (i-1)) == 0) r++;
        else originalBlock--;
        i++;
    }
    
    return F/K + r;
}

// Generate the number of errors in a block
int generateRandomErrors(int BlockLength, float e, int independent, int tx, int B, int N) {
    float x;
    int i, numError = 0;
    for (i = 1; i <= BlockLength; i++) {
        if (independent == 1 || (independent == 0 && (tx+i)%(B+N) < B)) {
            x = (float)rand()/(float)RAND_MAX;
            if (x <= e) numError++;
        }
    }
    return numError;
}
