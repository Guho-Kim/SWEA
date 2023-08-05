#include <iostream>
#include <cstring>
#include <vector>
using namespace std;

vector<char> vec;

class Trie {
    static constexpr size_t M = 26;
    static constexpr char OFFSET = 'a';

    struct TrieNode {
        int child[M];
        bool is_terminal;

        TrieNode() {
            memset(child, -1, sizeof(int) * M);
            is_terminal = false;
        }
    };

    vector<TrieNode> nodes;

public:
    Trie() : nodes(1) {}

    void init() {
        nodes.resize(1);
        nodes[0] = TrieNode();
    }

    void insert(const string& str) {
        int node_id = 0;
        for (const auto& c : str) {
            if (nodes[node_id].child[c - OFFSET] == -1) {
                nodes[node_id].child[c - OFFSET] = nodes.size();
                nodes.emplace_back();
            }
            node_id = nodes[node_id].child[c - OFFSET];
        }
        nodes[node_id].is_terminal = true;
    }

    void remove(const string& str) {
        int node_id = 0;
        for (const auto& c : str) {
            if (nodes[node_id].child[c - OFFSET] == -1) {
                return;
            }
            node_id = nodes[node_id].child[c - OFFSET];
        }
        nodes[node_id].is_terminal = false;
    }

    bool find(const string& str) const {
        int node_id = 0;
        for (const auto& c : str) {
            if (nodes[node_id].child[c - OFFSET] == -1) {
                return false;
            }
            node_id = nodes[node_id].child[c - OFFSET];
        }
        return nodes[node_id].is_terminal;
    }
	string getKthWord(int K) {
		int node_id = 0;
		string kthWord = "";
		findKthWordDFS(node_id, "", K, kthWord);
		return kthWord;
	}
	void findKthWordDFS(int node_id, string currentWord, int& K, string& kthWord) {
		if (K == 0) return;

		if (nodes[node_id].is_terminal) {
			K--;
			if (K == 0) {
				kthWord = currentWord;
				return;
			}
		}

		for (int i = 0; i < M; i++) {
			int child_id = nodes[node_id].child[i];
			if (child_id != -1) {
				char ch = i + OFFSET;
				findKthWordDFS(child_id, currentWord + ch, K, kthWord);
			}
		}
	}

};

Trie trie;

void solve() {
    int K;
    cin >> K;
    string str;
    cin >> str;

    trie.init();
    for (int i = str.size() - 1; i >= 0; i--) trie.insert(str.substr(i));
    cout << trie.getKthWord(K);
}

int main(int argc, char** argv) {
    ios::sync_with_stdio(0);  // cin.tie();
    int test_case, T;
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case) {
        cout << '#' << test_case << ' ';
        solve();
        cout << '\n';
    }
    return 0;
}
