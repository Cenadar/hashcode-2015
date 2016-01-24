#ifndef POOL_H
#define POOL_H

#include <vector>
#include <set>
#include <iostream>

#include "server_assign.h"

using namespace std;

struct Pool {
  int id_;
  int row_count_;
  int total_cap_;
  int mx_;
  vector<int> row_val_;
  multiset<int> vals_;

  Pool(int id, int row_count) : id_(id), row_count_(row_count), row_val_(row_count) {
    total_cap_ = 0;
    mx_ = 0;
    vals_.insert(row_val_.begin(), row_val_.end());
  }

  void AddServer(ServerAssign &server) {
    server.poolNo = id_;

    int row_id = server.rowNo;
    vals_.erase(vals_.find(row_val_[row_id]));
    row_val_[row_id] += server.capacity;
    total_cap_ += server.capacity;
    vals_.insert(row_val_[row_id]);
    mx_ = *vals_.rbegin();
  }

  int gc() const {
    return total_cap_ - mx_;
  }

  bool operator<(const Pool& other) const {
    return gc() < other.gc();
  }
};

#endif
