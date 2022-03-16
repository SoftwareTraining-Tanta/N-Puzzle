//      بِسْمِ اللَّـهِ الرَّحْمَـٰنِ الرَّحِيم

#include <bits/stdc++.h>
using namespace std;

class puzzle {
private:
    int n = 4;
    long long count_valid_puzzle;
    vector<int> curr;
    int pos;
    vector<vector<int>> valid_puzzles;
    map<vector<int>, bool> existing_puzzle;
    int cnt_valid = 0;

    static void preprocess() {
        srand(time(nullptr));
    }

    static long long factorial(int x) {
        long long ans = 1;
        long long mod = 1e18 - 3;
        for (int i = x; i > 0; --i)
            ans *= i, ans %= mod;
        return ans;
    }

    vector<char> possible_moves(vector<int> &grid) {
        int empty_cell = find(grid.begin(), grid.end(), 0) - grid.begin();
        vector<char> actions;
        if (empty_cell % n != 0) // move left
            actions.push_back('<');
        if (empty_cell >= n) // move up
            actions.push_back('^');
        if (empty_cell % n != n - 1) // move right
            actions.push_back('>');
        if (empty_cell < n * (n - 1)) // move down
            actions.push_back('v');
        return actions;
    }

    void move(vector<int> &grid, char action) {
        int empty_cell = (int) (find(grid.begin(), grid.end(), 0) - grid.begin());
        if (action == 'v')
            swap(grid[empty_cell], grid[empty_cell + n]);
        else if (action == '>')
            swap(grid[empty_cell], grid[empty_cell + 1]);
        else if (action == '<')
            swap(grid[empty_cell], grid[empty_cell - 1]);
        else if (action == '^')
            swap(grid[empty_cell], grid[empty_cell - n]);
    }

    bool valid_action(char action, vector<char> &possible_moves) {
        auto it = find(possible_moves.begin(), possible_moves.end(), action);
        if (it == possible_moves.end())
            return false;
        return true;
    }

    char select_action(vector<char> &available_actions) {
        char selected_action = 'N';
        while (selected_action == 'N') {
            cout << "available moves: ";
            for (char action: available_actions)
                cout << action << "  ";
            cout << '\n';
            cin >> selected_action;
            for (char curr_action: available_actions) {
                if (selected_action == curr_action)
                    return selected_action;
            }
            selected_action = 'N';
        }
    }

public:
    puzzle(int n) {
        preprocess();
        this->n = n;
        count_valid_puzzle = factorial(n * n) / 2;
        curr = get_solution();
        pos = 0;
        valid_puzzles.clear();
        existing_puzzle.clear();
        cnt_valid = 0;
    }
    
    void generate() {
        if (existing_puzzle[curr])
            return;
        existing_puzzle[curr] = true;
        valid_puzzles.push_back(curr);
        cnt_valid++;
        if (cnt_valid > 1000 or cnt_valid > count_valid_puzzle) // generate up to 1000
            return;
        if (pos < n * (n - 1)) { // move down
            swap(curr[pos], curr[pos + n]);
            pos += n;
            generate();
            pos -= n;
            swap(curr[pos], curr[pos + n]);
        }
        if (pos % n != n - 1) { // move right
            swap(curr[pos], curr[pos + 1]);
            pos += 1;
            generate();
            pos -= 1;
            swap(curr[pos], curr[pos + 1]);
        }
        if (pos % n != 0) { // move left
            swap(curr[pos], curr[pos - 1]);
            pos -= 1;
            generate();
            pos += 1;
            swap(curr[pos], curr[pos - 1]);
        }
        if (pos >= n) { // move up
            swap(curr[pos], curr[pos - n]);
            pos -= n;
            generate();
            pos += n;
            swap(curr[pos], curr[pos - n]);
        }
    }

    vector<int> get_solution() {
        vector<int> grid;
        for (int i = 0; i < n * n; ++i)
            grid.push_back(i);
        return grid;
    }

    vector<int> get_random_puzzle() {
        if (valid_puzzles.size() != 0) { // not generated
            return valid_puzzles[rand() % valid_puzzles.size()];
        } else {
            valid_puzzles.clear();
            existing_puzzle.clear();
            vector<int> sol = get_solution();
            curr = sol;
            generate();
            return valid_puzzles[rand() % valid_puzzles.size()];
        }
    }

    void print_puzzle(vector<int> &grid) {
        int sz = int(sqrt(grid.size()));
        for (int i = 0; i < grid.size(); ++i) {
            if (i % sz == 0)
                cout << "\n| ";
            if (grid[i] == 0)
                cout << "  | ";
            else
                cout << grid[i] << " | ";
        }
        cout << '\n';
    }


    bool correct(vector<int> &grid) {
        int empty_cell = (int) (find(grid.begin(), grid.end(), 0) - grid.begin());
        if (empty_cell == 0) {
            for (int i = 0; i < grid.size(); i++) {
                if (grid[i] != i)
                    return false;
            }
            return true;
        } else if (empty_cell == grid.size() - 1) {
            for (int i = 0; i < grid.size() - 1; i++) {
                if (grid[i] != i + 1)
                    return false;
            }
            return true;
        } else {
            return false;
        }
    }
    
    void play() {
        vector<int> grid = get_random_puzzle();
        while (correct(grid))
            grid = get_random_puzzle();
        while (true) {
            print_puzzle(grid);
            vector<char> available_actions = possible_moves(grid);
            char selected_action = select_action(available_actions);
            move(grid, selected_action);
            if (correct(grid)) {
                print_puzzle(grid);
                cout << "Winner Winner Chicken Dinner :)\n";
                break;
            }
        }
    }

    void print_valid() {
        cout << "Number of valid puzzles of length " << n << " * " << n << " is: "
             << count_valid_puzzle << '\n';
        if (count_valid_puzzle > valid_puzzles.size()) {
            cout << "Only a piece of valid puzzles are printed\n";
        }
        for (vector<int> v: valid_puzzles) {
            cout << "[";
            for (int i = 0; i < v.size() - 1; ++i) {
                cout << v[i] << ", ";
            }
            cout << v[v.size() - 1] << "]\n";
        }
    }
};

int main() {
    freopen("output.txt", "w", stdout);
    puzzle x(2);
    x.generate();
    x.print_valid();
}
