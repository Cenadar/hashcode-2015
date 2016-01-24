#ifndef SERVER_ASSIGN_H
#define SERVER_ASSIGN_H

using namespace std;

class ServerAssign {
 public:
  int rowNo;
  int slotNo;
  int slots;
  int poolNo;
  int capacity;
  bool isAllocated;

  ServerAssign(int rowNo, int slotNo, int poolNo, int capacity, int slots) {
    this->rowNo = rowNo;
    this->slotNo = slotNo;
    this->poolNo = poolNo;
    this->isAllocated = true;
    this->capacity= capacity;
    this->slots = slots;
  }

  ServerAssign() {
    this->isAllocated = false;
  }
};

#endif
