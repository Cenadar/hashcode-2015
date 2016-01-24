#ifndef ANNEALER_H
#define ANNEALER_H

#include <vector>
#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <math.h>

#include "server_assign.h"

using namespace std;



class Annealer {

  int numServers;
  int numPools;
  int numRows;
  // TODO: change const
  const int inf = 1000000000;

  vector<vector<ServerAssign> > &current;
  vector<vector<ServerAssign> > next;
  double temperature;

  int getEstimate(const vector<vector<ServerAssign> > &current){
    int gc = inf;
    for(int i = 0; i < numPools; i++){
      int max_in_row = 0;
      int total_sum = 0;
      for(int j = 0; j < numRows; j++ ){
        int row_sum_for_pool = 0;
        for(int k = 0; k < current[j].size(); k++){
          if (current[j][k].poolNo == i){
            row_sum_for_pool += current[j][k].capacity;
          }
        }
        total_sum += row_sum_for_pool;
        max_in_row = max(max_in_row, row_sum_for_pool);
      }
      gc = min(gc, total_sum - max_in_row);
    }

    return -gc;
  }

  void computeNext(const vector<vector<ServerAssign> > &current, vector<vector<ServerAssign> > &next) {
    //copy(current, next);
    next = current;

    int k = 1;
    if(temperature > 20){
      k = 10;
    }else{
      k = 1;
    }

    while(k--){
      int rand_row = (int)( ( numRows-1 ) * (1.0*rand()/RAND_MAX));
      int rand_row_size = next[rand_row].size();

      int i1 = (int)( ( rand_row_size - 1 ) * (1.0*rand()/RAND_MAX));
      int i2 = (int)( ( rand_row_size - 1 ) * (1.0*rand()/RAND_MAX));

      if (next[rand_row][i1].poolNo != next[rand_row][i2].poolNo){
         int temp = next[rand_row][i1].poolNo;
         next[rand_row][i1].poolNo = next[rand_row][i2].poolNo;
         next[rand_row][i2].poolNo = temp;
      }


    }
  }

  /*void copy(const vector<vector<ServerAssign> > &src, vector<vector<ServerAssign> > &dest){
    dest.clear();
    dest.resize(src.size());
    for(int i = 0; i < src.size(); i++){
      for(int j = 0; j < src[i].size(); j++){
        dest[i].pb(src[i][j]);
      }
    }
  }*/

  public:
  Annealer(vector<vector<ServerAssign> > &poolMap, int number_of_pools) : current(poolMap) {
    // Init current map

    numPools = number_of_pools;
    numRows = current.size();
  }

  int startAnnealing() {
     int iteration = -1;
      //the probability
      double proba;
      double alpha =0.99999;
      temperature = 0.1;
      double epsilon = 0.01;
      int delta;

      int guaranteed_capacity = getEstimate(current);

      //while the temperature did not reach epsilon
      while(temperature > epsilon)
      {
          iteration++;

          //get the next random permutation
          computeNext(current,next);
          //compute the guaranteed_capacity of the new permuted configuration
          delta = getEstimate(next) - guaranteed_capacity;
          //if the new guaranteed_capacity is better accept it and assign it
          if(delta<0)
          {
              //assign(current,next);
              //memcpy(current, next, sizeof(current));
              current = next;
              guaranteed_capacity = delta + guaranteed_capacity;
          }
          else
          {
              proba = (1.0*rand()/RAND_MAX);
              //if the new guaranteed_capacity is worse accept
              //it but with a probability level
              //if the probability is less than
              //E to the power -delta/temperature.
              //otherwise the old value is kept
              if(proba < exp(-delta/temperature))
              {
                  //assign(current,next);
                  current = next;
                  //memcpy(current, nextt, sizeof(current));
                  guaranteed_capacity = delta + guaranteed_capacity;
              }
          }

          if(guaranteed_capacity == 0){
            return guaranteed_capacity;
          }
          //cooling process on every iteration
          temperature *=alpha;
          //print every 400 iterations
          //if (iteration%400==0)
          //cout<<guaranteed_capacity<< endl;
      }

    return -guaranteed_capacity;
  }
};

#endif
