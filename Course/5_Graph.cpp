#include <iostream>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

void f0(int n, const vector< pair< int, int >> &edges) {
	// data
	vector< vector< int >> graph(n);
	// build
	for (const auto& e : edges) {
		graph[e.first].emplace_back(e.second);
	}
	// iterate
	cout << "using vector\n";
	for (int u = 0; u < n; ++u) {
		cout << u << " ->";
		for (const auto& v : graph[u]) {
			cout << ' ' << v;
		}
		cout << '\n';
	}
	cout << '\n';
}

void f1(int n, const vector< pair< int, int >> &edges) {
	// data
	struct LinkedListNode {
		int id;
		int next;
	};
	vector< LinkedListNode > nodes(edges.size());
	vector< int > head(n, -1);
	// build
	for (int i = 0; i < static_cast< int >(edges.size()); ++i) {
		nodes[i].id = edges[i].second;
		nodes[i].next = head[edges[i].first];
		head[edges[i].first] = i;
	}
	// iterate
	cout << "using linked list\n";
	for (int u = 0; u < n; ++u) {
		cout << u << " ->";
		for (int i = head[u]; i != -1; i = nodes[i].next) {
			cout << ' ' << nodes[i].id;
		}
		cout << '\n';
	}
	cout << '\n';
}

void f2(int n, const vector< pair< int, int >> &edges) {
	// data
	vector< int > outdegree(n);
	vector< int > prefix(n + 1);
	vector< int > vertices(edges.size());
	// build
	for (const auto& e : edges) {
		++outdegree[e.first];
	}
	partial_sum(outdegree.begin(), outdegree.end(), next(prefix.begin()));
	for (const auto& e : edges) {
		vertices[prefix[e.first] + --outdegree[e.first]] = e.second;
	}
	// iterate
	cout << "using prefix sum\n";
	for (int u = 0; u < n; ++u) {
		cout << u << " ->";
		for (int i = prefix[u]; i < prefix[u + 1]; ++i) {
			cout << ' ' << vertices[i];
		}
		cout << '\n';
	}
	cout << '\n';
}

int main() {
	constexpr int n = 5;
	const vector< pair< int, int >> edges =
	{ {0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 4}, {3, 2}, {4, 3} };

	f0(n, edges);
	f1(n, edges);
	f2(n, edges);
}