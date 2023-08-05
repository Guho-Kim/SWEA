// [SWEA] No 1256. [S/W 문제해결 응용] 6일차 - K번째 접미어

#include<iostream>
#include<cstring>
#include<vector>
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

	vector< TrieNode > nodes;

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

    string findKthSuffix(int K) {
        int node_id = 0;
        string kthSuffix;
        while (K > 0) {
            for (int i = 0; i < M; i++) {
                int child_id = nodes[node_id].child[i];
                if (child_id != -1) {
                    kthSuffix.push_back(i + OFFSET);
                    if (nodes[child_id].is_terminal) {
                        K--;
                        if (K == 0) break;
                    }
                    node_id = child_id;
                    break;
                }
            }
        }
        return kthSuffix;
    }
    
};

Trie trie;
void solve(){
    int K; cin>>K;    
    string str; cin>>str;

    trie.init();
    for(int i=str.size()-1; i>=0; i--){
        trie.insert(str.substr(i));
    }
    string result;
    cout<<trie.findKthSuffix(K);
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(0);//cin.tie();
	int test_case, T;cin>>T;
   
	for(test_case = 1; test_case <= T; ++test_case){
        cout<<'#'<<test_case<<' ';
        solve();
        cout<<'\n';
    	}
	return 0;
}