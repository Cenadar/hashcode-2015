#ifndef POOL_INITIALIZER_H
#define POOL_INITIALIZER_H

#include <vector>

#include "server_assign.h"

using namespace std;

class PoolInitializer {
  vector<ServerAssign> &servers_;

  PoolInitializer(vector<ServerAssign> &servers) : servers_(servers) {
  }

  int calculate() {
    return -1;
  }

 public:
  static int calc(vector<ServerAssign> &servers) {
    PoolInitializer initializer(servers);
    return initializer.calculate();
  }
};

#endif
