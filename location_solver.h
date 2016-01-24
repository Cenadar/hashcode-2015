#ifndef LOCATION_SOLVER_H_INCLUDED
#define LOCATION_SOLVER_H_INCLUDED

#include <algorithm>
#include <set>

using namespace std;

const int TESTS_FUNCTION = 1;

double coef[20];

double value(Server const & a) {
    return 1.0 * coef[0] * a.capacity / a.slots;
}

bool compFunc(const Server & a, const Server & b) {
    return value(a) > value(b);
}


struct Interval {
    int start;
    int length;
    Interval(int _start, int _length) :
        start(_start), length(_length) {}

    void out() {
        printf("[%d %d]\n", length, start);
    }
};

struct IntervalRow {
    Interval interval;
    int row;
    IntervalRow(Interval interval, int row) :
        interval(interval), row(row) {}

    void out() const {
        printf("[%d %d] [%d]\n", interval.length, interval.start, row);
    }
};

bool compIntervalRow(const IntervalRow & a, const IntervalRow & b) {
    return a.interval.length > b.interval.length;
}



class LocationSolver {
private:
    int R, S, U, P, M, a, b;
    vector<pair<int, int> > unavailableSlots;
    vector<Server> servers;

    void out(vector<int> & a, string msg) {
        cout << msg << endl;
        for (int i = 0; i < a.size(); i++) {
            printf("[%d] ", a[i]);
        }
        cout << endl;
    }

    void getFreeForRow(int row, vector<Interval> & free, vector<int> & unavailable) {
        sort(unavailable.begin(), unavailable.end());
        out(unavailable, "unavailable");

        int pos = 0;
        int start = 0;
        int cntUnavailable = unavailable.size();

        while (pos < cntUnavailable && unavailable[pos] == start) {
            start++;
            pos++;
        }

        while (pos < cntUnavailable) {
            int x = unavailable[pos];
            int len = x - start;
            if (len > 0) {
                free.push_back(Interval(start, len));
                start = x + 1;
            }
            pos++;
        }

        if (start < S)
            free.push_back(Interval(start, S - start));


        cout << "Free intervals" << endl;
        for (auto & inter : free) {
            inter.out();
        }

    }

    void getFreePositionRows(vector<vector<Interval> > & free) {
        free.resize(R);

        vector<vector<int> > unavailable;
        unavailable.resize(R);
        for (auto & p : unavailableSlots) {
            int row = p.first;
            int col = p.second;
            unavailable[row].push_back(col);
        }

        for (int i = 0; i < R; i++) {
            getFreeForRow(i, free[i], unavailable[i]);
        }
    }

    void initForSort(int seed) {
        srand(seed);

        int a, b;
        a = rand();
        b = rand();
        //coef[0] = 1.0 * a / b;
        coef[0] = 1.0;
    }

public:
    LocationSolver(
            int _R,
            int _S,
            int _U,
            int _P,
            int _M,
            vector<pair<int, int> > & _unavailableSlots,
            vector<Server> & _servers) {
        this->R = _R;
        this->S = _S;
        this->U = _U;
        this->P = _P;
        this->M = _M;
        this->unavailableSlots = _unavailableSlots;
        this->servers = _servers;
    }



    vector<vector<ServerAssign> > solve() {


        vector<vector<ServerAssign> > location;

        vector<vector<Interval> > free;
        getFreePositionRows(free);

        for (int test = 0; test < TESTS_FUNCTION; test++) {
            printf("TEST [%d]\n", test);

            initForSort(123);
            sort(begin(servers), end(servers), compFunc);
            for (auto & s : servers) {
                printf("[%d\t%d\t%lf]\n", s.capacity, s.slots, value(s));
            }

            // Intervals
            multiset<IntervalRow, bool(*)(const IntervalRow& lhs, const IntervalRow& rhs)>
                intervals(&compIntervalRow);

            for (int i = 0; i < free.size(); i++) {
                for (int j = 0; j < free[i].size(); j++) {
                    intervals.insert( IntervalRow(free[i][j], i) );
                }
            }

            cout << "Free intervals sorted" << endl;
            for (auto & inter : intervals) {
                inter.out();
            }

            // Servers
            multiset<Server, bool(*)(const Server& lhs, const Server& rhs)>
                nonAssignServers(&compFunc);

            for (auto & s: servers) {
                nonAssignServers.insert(s);
            }
            cout << "Servers sorted" << endl;
            for (auto & s : servers) {
                printf("[%d\t%d\t%lf]\n", s.capacity, s.slots, value(s));
            }

            vector<vector<ServerAssign> > answer;
            answer.resize(R);

            while(true) {
                if (intervals.empty() || nonAssignServers.empty()) {
                    break;
                }

                auto itInterval = intervals.begin();
                cout << "Intervals for processing" << endl;
                itInterval->out();

                auto itServer = nonAssignServers.begin();

                if (itInterval->interval.length >= itServer->slots) {
                    int row = itInterval->row;

                    // Add server
                    answer[row].push_back( ServerAssign(
                                                row,
                                                itInterval->interval.start,
                                                -1,
                                                itServer->capacity,
                                                itServer->slots)
                    );

                    int len = itInterval->interval.length - itServer->slots;
                    if (len > 0) {
                        IntervalRow ir = IntervalRow(
                            Interval(itInterval->interval.start + itServer->slots, len), row
                        );
                        intervals.erase(itInterval);
                        intervals.insert(ir);
                    }
                    else {
                        intervals.erase(itInterval);
                    }
                    printf("+++ [%d %d]\n", itServer->capacity, itServer->slots);

                }
                nonAssignServers.erase(itServer);
            }




        }


        return location;
    }
};

#endif // LOCATION_SOLVER_H_INCLUDED
