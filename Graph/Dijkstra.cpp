#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
#include <vector>

#define MAXN 1010

std::vector< std::vector<std::pair<int, int> > > g(MAXN);
int dist[MAXN][MAXN];
int n, m;

void dijkstra(int index) {
	for (int i = 0; i < n; ++i) dist[index][i] = 1e9;
	dist[index][index] = 0;

	bool visited[MAXN] = { 0 };

	std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>> > pq;
	pq.push(std::make_pair(0, index));

	while (!pq.empty()) {
		int cur = pq.top().second;
		pq.pop();

		if (visited[cur])
			continue;
		
		visited[cur] = true;

		for (std::pair<int, int> v : g[cur]) {
			int nxt = v.first;
			int w = v.second;
			if (dist[index][cur] + w < dist[index][nxt]) {
				dist[index][nxt] = dist[index][cur] + w;
				pq.push(std::make_pair(dist[index][nxt], nxt));
			}
		}
	}
}

int main() {
	std::cin >> n >> m;

	for (int i = 0; i < m; ++i) {
		int x, y, w;
		std::cin >> x >> y >> w;
		--x; --y;

		g[x].push_back(std::make_pair(y, w));
		g[y].push_back(std::make_pair(x, w));
	}

	for (int i = 0; i < n; ++i) {
		dijkstra(i);
	}
}