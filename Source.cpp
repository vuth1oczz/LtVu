#include <iostream>
#include <utility>
#include<vector>
#include <queue>
const double INF = 1e9;
#define MAX_SIZE 8
bool visited[100];
int parents[1000];
struct location {
	int posx;
	int posy;
	int value;
	location() {};
	location(int x, int y) : posx(x), posy(y), value(0) {}
	void in() {
		std::cout << "(" << posx << "," << posy << ")";
	}
	bool operator != (const location& other) const {
		return posx != other.posx || posy != other.posy;
	}
	void nhap() { 
		std::cin >> posx;
		std::cin >> posy;
	}
};
int vi_tri(location loc) {
	int x = loc.posx * MAX_SIZE + loc.posy;
	return  x;
}
location dia_chi(int u) {
	location loc ;
	loc.posx = u / MAX_SIZE;
	loc.posy = u % MAX_SIZE;
	return loc;
}
void danh_sach_ke(std::vector<std::vector<std::pair<int,double>>> &adj) {
	adj.resize(MAX_SIZE * MAX_SIZE);
	int cnt = 0;
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE;j++) {
			location loc1 = { i - 1, j - 1 }; std::pair<int, double> LOC1 = { vi_tri(loc1), 1.41 };
			location loc2 = { i-1, j};
			location loc3 = { i - 1, j+1 };
			location loc4 = { i, j - 1 };
			location loc5 = { i , j + 1 };
			location loc6 = { i + 1, j - 1 };
			location loc7 = { i +1, j  };
			location loc8 = { i + 1, j + 1 };
			
			if (loc1.posx >= 0 && loc1.posy >= 0) adj[cnt].push_back({ vi_tri(loc1), 1.41 });
			if (loc2.posx >= 0) adj[cnt].push_back({vi_tri(loc2), 1});
			if (loc3.posx >= 0 && loc3.posy < MAX_SIZE) adj[cnt].push_back({vi_tri(loc3),1.41});
			if (loc4.posy >= 0) adj[cnt].push_back({vi_tri(loc4), 1});
			if (loc5.posy < MAX_SIZE) adj[cnt].push_back({ vi_tri(loc5),1 });
			if (loc6.posx < MAX_SIZE && loc6.posy >= 0) adj[cnt].push_back({vi_tri(loc6), 1.41});
			if (loc7.posx < MAX_SIZE ) adj[cnt].push_back({vi_tri(loc7), 1});
			if (loc8.posx < MAX_SIZE && loc8.posy < MAX_SIZE) adj[cnt].push_back({vi_tri(loc8), 1.41});


			cnt++;
		}
	}
}
//void dfs(location source, const std::vector<std::vector<int>> &adj) {
//	int u = vi_tri(source);
//	//std::cout << u << " ";
//	if (!visited[u]) {
//		visited[u] = true;
//		
//		for (int v : adj[u]) {
//			if (!visited[v]) {
//				parents[v] = u;
//				dfs(dia_chi(v), adj);
//			}
//		}
//	}
//
//}
void bfs(location source, const std::vector<std::vector<std::pair<int,double>>>& adj) {
	std::queue<std::pair<int,double>> q;
	int u = vi_tri(source);
	q.push({u,0});
	//visited[u] = true;
	while (!q.empty()) {
		std::pair<int,double> v = q.front();
		q.pop();
		for (std::pair<int,double> x : adj[v.first]) {
			if (!visited[x.first]) {
				q.push({x.first, x.second});
				parents[x.first] = v.first;
				visited[x.first] = true;
			}
		}
	}

}
void pathBFS(location source, location target, const std::vector<std::vector<std::pair<int,double>>> &adj) {
	int s = vi_tri(source);
	int t = vi_tri(target);
	memset(visited, false, sizeof(visited));
	memset(parents, 0, sizeof(parents));
	bfs(source, adj);
	if (!visited[t]) {
		std::cout << " Khong co duong di! ";
	}
	else { 
		std::cout << "Path with BFS: ";
		std::vector<int> nodePath;
		std::vector<location> path;
		while ( t != s) {
			path.push_back(dia_chi(t));
			nodePath.push_back(t);
			t = parents[t];
		}
		path.push_back(dia_chi(s));
		nodePath.push_back(s);
		reverse(path.begin(), path.end());
		/*for (location x : path) {
			x.in(); std::cout << " -> ";
		}*/
		reverse(nodePath.begin(), nodePath.end());
		//std::cout << std::endl;
		for (int x : nodePath) {
			std::cout << "->" << x;
		}
	}
}
//void pathDFS(location source, location target, const std::vector<std::vector<int>>& adj) {
//	int s = vi_tri(source);
//	int t = vi_tri(target);
//	memset(visited, false, sizeof(visited));
//	memset(parents, 0, sizeof(parents));
//	dfs(source, adj);
//	if (!visited[t]) {
//		std::cout << " Khong co duong di! ";
//	}
//	else {
//		std::cout << "\nPath with DFS: ";
//		std::vector<int> nodePath;
//		std::vector<location> path;
//		while (t != s) {
//			path.push_back(dia_chi(t));
//			nodePath.push_back(t);
//			t = parents[t];
//		}
//		path.push_back(dia_chi(s));
//		nodePath.push_back(s);
//		reverse(path.begin(), path.end());
//		/*for (location x : path) {
//			x.in(); std::cout << " -> ";
//		}*/
//		reverse(nodePath.begin(), nodePath.end());
//		//std::cout << std::endl;
//		for (int x : nodePath) {
//			std::cout << "->" << x;
//		}
//	}
//}
void dijiktra(location source, const std::vector<std::vector<std::pair<int, double>>>& adj) {
	std::vector<long long> dis(MAX_SIZE*MAX_SIZE + 1, INF);
	int s = vi_tri(source);
	dis[vi_tri(source)] = 0;
	std::priority_queue <std::pair<int, double>, std::vector<std::pair<int, double>>, std::greater<std::pair<int, double>>> q;
	q.push({ s,0 });
	while (!q.empty()) {
		std::pair<int, double> top = q.top();
		q.pop();
		int u = top.first;
		double kc = top.second;
		if (kc > dis[u]) continue;
		for (std::pair<int, double> it : adj[u]) {
			int v = it.first;
			double w = it.second;
			if (dis[v] > dis[u] + w) {
				visited[v] = true;
				dis[v] = dis[u] + w;
				q.push({ v, dis[v] });
				parents[v] = u;
			}
		}
	}
}
void pathDijiktra(location source, location target, std::vector<std::vector<std::pair<int, double>>>& adj) {
	int s = vi_tri(source);
	int t = vi_tri(target);
	memset(visited, false, sizeof(visited));
	memset(parents, 0, sizeof(parents));
	dijiktra(source, adj);
	if (!visited[t]) std::cout << "Khong co duong di";
	else {
		std::cout << "Path wiht Dijjiktra: ";
		std::vector<int> nodePath;
		while (t != s) {
			nodePath.push_back(t);
			t = parents[t];
		}
		nodePath.push_back(s);
		reverse(nodePath.begin(), nodePath.end());
		for (int i : nodePath) {
			std::cout << "->" << i;
		}
	}
}


void xoa_phan_tu(std::vector<std::pair<int,double>> &v, int x)  {
	for (int i = 0; i< v.size(); i++){
		if (x == v[i].first) {
			v.erase(v.begin() + i);
		}
	}
}
void obstacle( std::vector<std::vector<std::pair<int,double>>> &adj) {
	int numObstacle;
	std::cout << "Nhap so vat can:";
	std::cin >> numObstacle;
	if (numObstacle) {
		std::cout << "Nhap toa do vat can:\n";
	}
	while (numObstacle--) {
		location obstacle;
		obstacle.nhap();
		int u = vi_tri(obstacle);
		for (std::pair<int,double> v : adj[u]) {
			xoa_phan_tu(adj[v.first], u);
		}
	}
	

}
int main() {
	std::vector<std::vector<std::pair<int,double>>> adj;
	danh_sach_ke(adj);
	//dfs({ 0,0 }, adj);
	location source, target;
	std::cout << "Source: ";
	source.nhap();
	std::cout << "Target:";
	target.nhap();
	obstacle(adj);
	pathBFS(source, target, adj );
	std::cout << std::endl;
	//pathDFS(source, target, adj);
	pathDijiktra(source, target, adj);

	return 0;
}