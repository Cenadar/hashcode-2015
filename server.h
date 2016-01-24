#ifndef SERVER_H
#define SERVER_H

using namespace std;

struct Server {
 public:
  int slots;
  int capacity;

  Server(int slots, int capacity): slots(slots), capacity(capacity) {
  }

  /*Server(const Server &s){
    this->capacity = s.capacity;
    this->slots = s.slots;
  }*/
};

#endif
