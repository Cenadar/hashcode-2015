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

using namespace std;

const int TEST = 16;

string to_str(int v) {
    stringstream ss;
    ss << v;
    return ss.str();
}

int main() {
    freopen("results.txt","w",stdout);

    for (int i=0; i<TEST; i++) {
        clock_t tm = clock();
        string inFile = "test_" + to_str(i) + ".txt" + (i < 10 ? " " : "");
        int result = rand();

        ;

        tm = clock() - tm;
        printf("%s        %9d        (%f seconds)\n", inFile.c_str(), result, ((float)tm)/CLOCKS_PER_SEC);
        fflush(stdout);
    }

    return 0;
}
