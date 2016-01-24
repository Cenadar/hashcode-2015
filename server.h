#ifndef SERVER_H
#define SERVER_H

using namespace std;

class Server {
 public:
  int capacity;
  int slots;

  Server(int slots, int capacity): slots(slots), capacity(capacity) {
  }
};

#endif
