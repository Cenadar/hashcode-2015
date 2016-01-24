#ifndef SERVER_H
#define SERVER_H

using namespace std;

struct Server {
 public:
  int capacity;
  int slots;

  Server(int slots, int capacity): slots(slots), capacity(capacity) {
  }

  /*Server(const Server &s){
    this->capacity = s.capacity;
    this->slots = s.slots;
  }*/
};

#endif
