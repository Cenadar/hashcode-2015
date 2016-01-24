#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <cstring>
#include <climits>
#include <ctime>
#include <cmath>
#include <algorithm>
#include <string>
#include <cstring>
#include <cstdlib>
#include <string>
#include <sstream>

#include "server.h"
#include "server_assign.h"
#include "location_solver.h"


using namespace std;

const int TEST = 16;

string to_str(int v) {
    stringstream ss;
    ss << v;
    return ss.str();
}

int main() {
    //freopen("results.txt","w",stdout);

    for (int i=0; i<TEST; i++) {
        clock_t tm = clock();
        string inFile = "tests/test_" + to_str(i) + ".txt";
        int result = rand();

        //FILE *outf = fopen(inFile.c_str(), "r");
        //
        //fclose(outf);
        printf("***** %s\n", inFile.c_str());
        freopen(inFile.c_str(), "r", stdin);
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
        //printf("# %d %d %d %d %d\n", R, S, U, P, M);

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
        pSolver->solve(result);

        tm = clock() - tm;
        printf("%s        %9d        (%f seconds)\n", inFile.c_str(), result, ((float)tm)/CLOCKS_PER_SEC);
        fflush(stdout);
    }

    return 0;
}
