#ifndef SERVER_ASSIGN_H
#define SERVER_ASSIGN_H

using namespace std;

class ServerAssign {
 public:
  int rowNo;
  int slotNo;
  int poolNo;
  bool isAllocated;

  ServerAssign(int rowNo, int slotNo, int poolNo) {
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
