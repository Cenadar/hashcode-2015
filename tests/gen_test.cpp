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

using namespace std;

const int SERVER_GEN_RAND = 0;
const int SERVER_GEN_BIG = 1;
const int SERVER_GEN_SMALL = 2;

int gen_rand(int l, int r) {
    return ((int)(r - l) * (1.0 * rand() / RAND_MAX)) + l;
}

int table[1010][1010] = {};
void run(string fileName,
         int R, int S,
         int minBadSlots, int maxBadSlots, int maxSlotsLength,
         int minPoolsNum, int maxPoolsNum,
         int minServersNum, int maxServersNum,
         int serverGenType = SERVER_GEN_RAND,
         int servProcent = 0) {

    FILE *outf = fopen(fileName.c_str(), "w");
    /**
     R​(1 ≤ R ≤ 1000) ​denotes the number of rows in the data center,
     S​(1 ≤ S ≤ 1000) denotes the number of slots in each row of the data center,
     U​(0 ≤ U ≤ R × S) denotes the number of unavailable slots,
     P​(1 ≤ P ≤ 1000) denotes the number of pools to be created,
     M​(1 ≤ M ≤ R × S) denotes the number of servers to be allocated;
    */

    memset(table, 0, sizeof table);
    int servers = gen_rand(minServersNum, min(maxServersNum, R * S));
    int pools = gen_rand(minPoolsNum, maxPoolsNum);
    int badSlots = gen_rand(minBadSlots, min(maxBadSlots, R * S));

    fprintf(outf, "%d %d %d %d %d\n", R, S, badSlots, pools, servers);

    while(badSlots > 0) {
        int row = gen_rand(0, R);
        int col = gen_rand(0, S);
        int len = gen_rand(1, maxSlotsLength);

        for (int i=0; i<len; i++) {
            if (!table[row][col+i]) {
                fprintf(outf, "%d %d\n", row, col + i);
                table[row][col+i] = true;
                badSlots--;
            }

            if (!badSlots) break;
        }
    }

    if (serverGenType == SERVER_GEN_RAND) {
        for (int i=0; i<servers; i++) {
            int sz = gen_rand(1, S);
            int capacity = gen_rand(1, 1000);
            fprintf(outf, "%d %d\n", sz, capacity);
        }
    }
    else if (serverGenType == SERVER_GEN_BIG) {
        int k = servers * servProcent / 100;
        for (int i=0; i<k; i++) {
            int sz = gen_rand(S / 2, S);
            int capacity = gen_rand(500, 1000);
        }
        servers -= k;

        while(servers > 0) {
            int sz = gen_rand(1, S);
            int capacity = max(
                                1,
                                (1000 * sz / S) + (rand() & 1 ? -1 : 1) * gen_rand(1, 50)
                            );
            fprintf(outf, "%d %d\n", sz, capacity);
            servers--;
        }
    }
    else if (serverGenType == SERVER_GEN_SMALL) {
        int k = servers * servProcent / 100;
        for (int i=0; i<k; i++) {
            int sz = gen_rand(1, min(S, 20));
            int capacity = gen_rand(1, 40);
        }
        servers -= k;

        while(servers > 0) {
            int sz = gen_rand(1, S);
            int capacity = max(
                                1,
                                (1000 * sz / S) + (rand() & 1 ? -1 : 1) * gen_rand(1, 50)
                            );
            fprintf(outf, "%d %d\n", sz, capacity);
            servers--;
        }
    }

    fclose(outf);

    return;
}

int main() {
    srand(time(NULL));

    run("test_0.txt", // (very simple)
        5, 5, // row, col - (1 ≤ R ≤ 1000)
        3, 6, 2, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        2, 4, // pools - (1 ≤ P ≤ 1000)
        1, 10 // servers - (1 ≤ M ≤ R × S)
    );

    run("test_1.txt", // (simple)
        100, 100, // row, col - (1 ≤ R ≤ 1000)
        50, 100, 5, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        5, 10, // pools - (1 ≤ P ≤ 1000)
        10, 100 // servers - (1 ≤ M ≤ R × S)
    );

    run("test_2.txt", // (big table)
        1000, 1000, // row, col - (1 ≤ R ≤ 1000)
        50, 100, 5, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        5, 10, // pools - (1 ≤ P ≤ 1000)
        10, 100 // servers - (1 ≤ M ≤ R × S)
    );

    run("test_3.txt", // (1000SZ - rand)
        1000, 1000, // row, col - (1 ≤ R ≤ 1000)
        1000, 1000, 25, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        800, 1000, // pools - (1 ≤ P ≤ 1000)
        100000, 1000000 // servers - (1 ≤ M ≤ R × S)
    );

    run("test_4.txt", // (1000SZ - no bad slots
        1000, 1000, // row, col - (1 ≤ R ≤ 1000)
        0, 0, 25, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        800, 1000, // pools - (1 ≤ P ≤ 1000)
        100000, 1000000 // servers - (1 ≤ M ≤ R × S)
    );

    run("test_5.txt", // (1000SZ - many servers)
        1000, 1000, // row, col - (1 ≤ R ≤ 1000)
        100, 100, 1, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        1000, 1000, // pools - (1 ≤ P ≤ 1000)
        1000000, 1000000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_SMALL,
        80
    );

    run("test_6.txt", // (1000SZ - exists big servers - 20%)
        1000, 1000, // row, col - (1 ≤ R ≤ 1000)
        1000, 1000, 25, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        800, 1000, // pools - (1 ≤ P ≤ 1000)
        100000, 1000000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_BIG, 20 // 20% of big servers(sz: S/2 - S), capacity (500 - 1000)
    );

    run("test_6.txt", // (1000SZ - exists big servers - 50%)
        1000, 1000, // row, col - (1 ≤ R ≤ 1000)
        1000, 1000, 25, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        800, 1000, // pools - (1 ≤ P ≤ 1000)
        100000, 1000000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_BIG, 50 // 50% of big servers(sz: S/2 - S), capacity (500 - 1000)
    );

    run("test_7.txt", // (1000SZ - exists small servers - 50%)
        1000, 1000, // row, col - (1 ≤ R ≤ 1000)
        1000, 1000, 25, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        800, 1000, // pools - (1 ≤ P ≤ 1000)
        100000, 1000000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_SMALL, 50 // 50% of small servers(sz: 1 - 20), capacity (1 - 50)
    );

    run("test_8.txt", // (500SZ - rand)
        500, 500, // row, col - (1 ≤ R ≤ 1000)
        500, 1000, 10, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        250, 500, // pools - (1 ≤ P ≤ 1000)
        100000, 200000 // servers - (1 ≤ M ≤ R × S)
    );

    run("test_9.txt", // (500SZ - no bad slots)
        500, 500, // row, col - (1 ≤ R ≤ 1000)
        0, 0, 25, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        250, 500, // pools - (1 ≤ P ≤ 1000)
        100000, 200000 // servers - (1 ≤ M ≤ R × S)
    );

    run("test_10.txt", // (500SZ - many servers)
        500, 500, // row, col - (1 ≤ R ≤ 1000)
        50, 50, 1, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        500, 500, // pools - (1 ≤ P ≤ 1000)
        250000, 250000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_SMALL,
        80
    );

    run("test_11.txt", // (500SZ - exists big servers - 20%)
        500, 500, // row, col - (1 ≤ R ≤ 1000)
        500, 500, 25, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        250, 500, // pools - (1 ≤ P ≤ 1000)
        100000, 200000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_BIG, 25 // 25% of big servers(sz: S/2 - S), capacity (500 - 1000)
    );

    run("test_12.txt", // (500SZ - exists big servers - 50%)
        500, 500, // row, col - (1 ≤ R ≤ 1000)
        500, 1000, 25, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        250, 500, // pools - (1 ≤ P ≤ 1000)
        100000, 200000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_BIG, 50 // 50% of big servers(sz: S/2 - S), capacity (500 - 1000)
    );

    run("test_13.txt", // (500SZ - exists small servers - 50%)
        500, 500, // row, col - (1 ≤ R ≤ 1000)
        500, 1000, 12, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        250, 500, // pools - (1 ≤ P ≤ 1000)
        100000, 200000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_SMALL, 50 // 50% of small servers(sz: 1 - 20), capacity (1 - 50)
    );

    run("test_14.txt", // (1000SZ - many bad slots)
        1000, 1000, // row, col - (1 ≤ R ≤ 1000)
        500000, 750000, 50, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        250, 500, // pools - (1 ≤ P ≤ 1000)
        100000, 200000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_SMALL, 50 // 50% of small servers(sz: 1 - 20), capacity (1 - 50)
    );

    run("test_15.txt", // (500SZ - many bad slots)
        500, 500, // row, col - (1 ≤ R ≤ 1000)
        200000, 250000, 50, // bad slots, length of slots - (0 ≤ U ≤ R × S)
        250, 500, // pools - (1 ≤ P ≤ 1000)
        100000, 200000, // servers - (1 ≤ M ≤ R × S)
        SERVER_GEN_SMALL, 50 // 50% of small servers(sz: 1 - 20), capacity (1 - 50)
    );

    return 0;
}

