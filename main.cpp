#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>

#include "server.h"
#include "server_assign.h"
#include "location_solver.h"

using namespace std;

int gc(vector<Server> servers, vector<ServerAssign> res) {
  ;
}

int main() {
  freopen("input.txt","r",stdin);
  //freopen("output.txt","w",stdout);
  int R, S, U, P, M, a, b;
  /**
   R​(1 ≤ R ≤ 1000) ​denotes the number of rows in the data center,
   S​(1 ≤ S ≤ 1000) denotes the number of slots in each row of the data center,
   U​(0 ≤ U ≤ R × S) denotes the number of unavailable slots,
   P​(1 ≤ P ≤ 1000) denotes the number of pools to be created,
   M​(1 ≤ M ≤ R × S) denotes the number of servers to be allocated;
  */
  cin >> R >> S >> U >> P >> M;

  vector<pair<int, int> > unavailableSlots;
  for (int i=0; i<U; i++) {
      cin >> a >> b;
      unavailableSlots.push_back(make_pair(a, b));
  }

  vector<Server> servers;
  for (int i=0; i<M; i++) {
      cin >> a >> b;
      servers.push_back(Server(a, b));
  }

    LocationSolver * pSolver = new  LocationSolver(
            R,
            S,
            U,
            P,
            M,
            unavailableSlots,
            servers);

    pSolver->solve();


  vector<ServerAssign> res;
  /*
      0 1 0
      1 0 1
      1 3 0
      0 4 1
      x
  */
/*  res.push_back(ServerAssign(0, 1, 0));
  res.push_back(ServerAssign(1, 0, 1));
  res.push_back(ServerAssign(1, 3, 0));
  res.push_back(ServerAssign(0, 4, 1));
  res.push_back(ServerAssign());
*/
  // check total capacity

  return 0;
}
