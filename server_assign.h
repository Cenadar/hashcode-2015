#ifndef SERVER_ASSIGN_H
#define SERVER_ASSIGN_H

using namespace std;

class ServerAssign {
 public:
  int capacity;
  int rowNo;
  int slotNo;
  int poolNo;
  bool isAllocated;

  ServerAssign(int rowNo, int slotNo, int poolNo, int _capacity) {
    this->capacity = _capacity;
    this->rowNo = rowNo;
    this->slotNo = slotNo;
    this->poolNo = poolNo;
    this->isAllocated = true;
  }

  ServerAssign() {
    this->isAllocated = false;
  }

};

#endif
