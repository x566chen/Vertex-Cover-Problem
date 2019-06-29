// defined std::unique_ptr
#include <memory>
// defines Var and Lit
#include "minisat/core/SolverTypes.h"
// defines Solver
#include "minisat/core/Solver.h"
#include "minisat/mtl/Vec.h"

// defined std::cout
#include <iostream>
#include <sstream>
#include <vector>
#include <set>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

class Graph {
private:
    int size;
    vector<bool> visited;

    int add_edge(int x, int y) {
        if (x >= size || y >= size)
            return -1;
        g[x].insert(y);
        g[y].insert(x);
        return 0;
    }

    void reset_visited() {
        visited.clear();
        visited.resize(size, false);
    }

public:
    vector<set<int>> g;
    int status = 0; //0--initial state, 1--v number added, 2--edges added
    void init(int num) {
        size = num;
        g.clear();
        g.resize(size);
        reset_visited();
    }

    int add_edge(vector<int> edges_pair) {
        g.clear();
        g.resize(size);
        for (unsigned i = 0; i < edges_pair.size(); i += 2) {
            if (add_edge(edges_pair[i], edges_pair[i + 1]) == -1)
                return -1;
        }
        return 0;
    }

    vector<int> shortest_path(int start, int end) {
        vector<int> ret;
        if (start >= size || end >= size)
            return ret;
        queue<vector<int>> q;
        vector<int> inv(1, start);
        q.push(inv);
        visited[start] = true;
        while (!q.empty()) {
            auto path = q.front();
            q.pop();
            auto node = path.back();
            if (node == end)
                return path;
            for (auto x : g[node]) {
                if (visited[x] == false) {
                    vector<int> new_path(path);
                    new_path.push_back(x);
                    visited[x] = true;
                    q.push(new_path);
                }
            }
        }
        return ret;
    }
};

class VertexCover {
private:
    Graph g;
    int v_num;
    unique_ptr<Minisat::Solver> solver;
    vector<int> res;

public:
    void init(Graph _g) {
        g = _g;
        v_num = g.g.size();
        solver = unique_ptr<Minisat::Solver> (new Minisat::Solver());
    }

    bool check(int k) {
        res.clear();
        solver.reset(new Minisat::Solver());
        vector<vector<Minisat::Lit>> lits(v_num);
        for (int i = 0; i < v_num; i++) {
            for (int j = 0; j < k; j++) {
                Minisat::Lit literal;
                literal = Minisat::mkLit(solver->newVar());
                lits[i].push_back(literal);
            }
        }
        // At least one vertex is the ith vertex in the vertex cover
        for (int i = 0; i < k; i++) {
            Minisat::vec<Minisat::Lit> tmp(v_num);
            for (int j = 0; j < v_num; j++) {
                tmp[j] = lits[j][i];
            }
            solver->addClause(tmp);
        }

        //No one vertex can appear twice in a vertex cover
        if (k > 1) {
            for (int i = 0; i < v_num; i++) {
                for (int j = 0; j < k - 1; j++) {
                    for (int m = j + 1; m < k; m++) {
                        solver->addClause(~lits[i][j], ~lits[i][m]);
                    }
                }
            }
        }

        //No more than one vertex appears in the mth position of the vertex cover
        if (v_num > 1) {
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < v_num - 1; j++) {
                    for (int m = j + 1; m < v_num; m++) {
                        solver->addClause(~lits[j][i], ~lits[m][i]);
                    }
                }
            }
        }

        //Every edge is incident to at least one vertex in the vertex cover
        for (int i = 0; i < v_num; i++) {
            for (auto iter = g.g[i].begin(); iter != g.g[i].end(); iter++) {
                Minisat::vec<Minisat::Lit> tmp;
                for (int j = 0; j < k; j++) {
                    tmp.push(lits[i][j]);
                    tmp.push(lits[*iter][j]);
                }
                solver->addClause(tmp);
            }
        }

        if (solver->solve()) {
            res.resize(k);
            for (int i = 0; i < v_num; i++) {
                for (int j = 0; j < k; j++) {
                    if (solver->modelValue(lits[i][j]) == Minisat::l_True) {
                        res[j] = i;
                        break;
                    }
                }
            }
            return true;
        }
        else
            return false;
    }

    void print_res() {
        if (!res.empty()) {
            sort(res.begin(), res.end());
            for (unsigned i = 0; i < res.size(); i++)
                cout<<res[i]<<" ";
            cout<<endl;
        }
        return;
    }
};

int main() {
    Graph g;
    VertexCover vc;
    // read from stdin until EOF
    while (!cin.eof()) {
        // read a line of input until EOL and store in a string
        string line;
        getline(cin, line);

        // create an input stream based on the line
        // we will use the input stream to parse the line
        istringstream input(line);

        // if there are characters in the input line
        if (!input.eof()) {
            char command;
            input >> command;

            if (input.fail())
                continue;
            if (command == 'V') {
                if (!input.eof()) {
                    int num;
                    input >> num;
                    if (input.fail())
                        cerr << "Error: a number should follow the V command\n";
                    else {
                        g.init(num);
                        g.status = 1;
                    }
                } else
                    cerr << "Error: a number should follow the V command\n";
            } else if (command == 'E') {
                if (g.status != 1) {
                    cerr << "Error: edges should be added after the V command\n";
                    continue;
                }
                vector<int> edges_pair;
                if (!input.eof()) {
                    char s;
                    int num;
                    input >> s;
                    input >> s;
                    input >> num;
                    if (!input.fail()) {
                        edges_pair.push_back(num);
                        while (!input.eof()) {
                            input >> s;
                            input >> num;
                            if (input.fail())
                                break;
                            edges_pair.push_back(num);
                            input >> s;
                            input >> s;
                            input >> s;
                            // if eof bail out
                            if (input.eof())
                                break;
                            input >> num;
                            if (input.fail())
                                break;
                            edges_pair.push_back(num);
                        }
                    }
                }
                if (edges_pair.size() % 2 != 0) {
                    cerr << "Error: check the edges pairs\n";
                    continue;
                }
                if (g.add_edge(edges_pair) == -1)
                    cerr << "Error: the vertex id in edges is invalid\n";
                else {
                    vc.init(g);
                    if (!vc.check(0)) {
                        for (unsigned k = 1; k <= g.g.size(); k++) {
                            if (vc.check(k)) {
                                vc.print_res();
                                break;
                            }
                        }
                    }
                }      
            }
            else {
                cerr << "Error: the command should be V or E\n";
            }
        }
    }
    return 0;
}