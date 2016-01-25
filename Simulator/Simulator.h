//
//  simulator.h
//  Simulator
//
//  Created by ZhangShuming on 16/1/25.
//  Copyright © 2016年 ZhangShuming. All rights reserved.
//

#ifndef simulator_h
#define simulator_h


#endif /* simulator_h */

void printInputParameters(char M, int A, int K, int F, float e, int B, int N, int R, int T, int trial[]);
int calcLengthOfBlock(int F, int K);
int generateRandomErrors(int BlockLength, float e, int independent, int burst, int B, int N);