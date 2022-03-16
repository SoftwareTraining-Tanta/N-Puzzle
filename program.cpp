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
};
