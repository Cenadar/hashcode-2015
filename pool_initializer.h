#ifndef POOL_INITIALIZER_H
#define POOL_INITIALIZER_H

#include <vector>
#include <set>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <cassert>

#include "server_assign.h"
#include "pool.h"
#include "annealer.h"

using namespace std;

class PoolInitializer {
  vector<vector<ServerAssign>> &servers_;
  int P_;
  const int tries_;

  void clear() {
    for (auto& row : servers_) {
      for (auto& s : row) {
        s.poolNo = -1;
      }
    }
  }

  PoolInitializer(vector<vector<ServerAssign>> &servers, int P) : servers_(servers), P_(P), tries_(100) {
    clear();
  }

  int gen(int seed, int last_pools) {
    srand(seed);
    set<Pool> pools;
    for (int i = 0; i < P_; ++i) {
      pools.insert(Pool(i, servers_.size()));
    }

    vector<ServerAssign> q;
    sort(q.begin(), q.end());

    for (auto &server : q) {
      int pool_pos = rand() % last_pools;
      auto it = pools.begin();
      for (int i = 0; i < pool_pos; ++i) {
        ++it;
      }

      Pool pool = *it;
      pool.AddServer(server);
      pools.erase(it);
      pools.insert(pool);
    }

    Annealer annealer(servers_, P_);
    return annealer.startAnnealing();
  }

  int calculate(int last_pools) {
    last_pools = min(last_pools, P_);

    int best_seed = -1;
    int best_value = -1;
    for (int i = 0; i < tries_; ++i) {
      int val = gen(i, last_pools);
      if (best_value < val) {
        best_seed = i;
        best_value = val;
      }
    }

    int v = gen(best_seed, last_pools);
    assert(v == best_value);
    return servers_.size();
  }

 public:
  static int calc(vector<vector<ServerAssign>> &servers, int P) {
    PoolInitializer initializer(servers, P);
    return initializer.calculate(10);
  }
};

#endif
