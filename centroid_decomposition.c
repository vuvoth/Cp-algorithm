/* 
 * Vu Vo Thanh 
 * Just a boy with 100 IQ
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_V 100001

typedef struct {
	int next, to;
} edge_type;


typedef struct {
	int V, E;
	int link[MAX_V];
	edge_type edges[MAX_V * 2];
} graph;


int n, m;
graph tree, centroid_tree;
int sub_size[MAX_V];
int mark[MAX_V];

void init_graph(graph *g, int V) {
	g->V = V;
	g->E = 0;
	for (int i = 1; i <= n; ++i)
		g->link[i] = -1;
}

void add_edge(graph *g, int u, int v) {
	int k = g->E++;
	g->edges[k].to = v;
	g->edges[k].next = g->link[u];
	g->link[u] = k;
}


void print_graph(graph *g, int v, int p) {
	printf("%d %d\n",p, v);;
	for (int id = g->link[v]; id != -1; id = g->edges[id].next) {
		int u = g->edges[id].to;
		if (u != p){
			print_graph(g, u, v);
		}
	}
}
void dfs(graph *g, int v, int p) {
	sub_size[v] = 1;
	for (int id = g->link[v]; id != -1; id = g->edges[id].next) {
		int u = g->edges[id].to;
		if (mark[u]) 
			continue;
		if (u != p){
			dfs(g, u, v);
			sub_size[v] += sub_size[u];
		}
	}
}

int centroid(graph *g, int v, int p, int sz) {
	for (int id = g->link[v]; id != -1; id = g->edges[id].next) {
		int u = g->edges[id].to;
		if (mark[u]) 
			continue;
		if (u != p && sub_size[u] > sz / 2) 
			return centroid(g, u, v, sz); 
	}
	return v;
}

int build(graph *g, int v, int p) {
	dfs(g, v, p);
	int cent = centroid(g, v, p, sub_size[v]);
	mark[cent] = 1;
	for (int id = g->link[cent]; id != -1; id = g->edges[id].next) {
		int u = g->edges[id].to;
		if (mark[u]) 
			continue;
		int cent_child = build(g, u, cent);
		add_edge(&centroid_tree, cent, cent_child);	
		add_edge(&centroid_tree, cent_child, cent);	
	}
	return cent;
}

void input() {
	scanf("%d%d", &n, &m);
	int u, v;
	init_graph(&tree, n);
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		add_edge(&tree, u, v);
		add_edge(&tree, v, u);
	}
}

int centroid_decomposition(graph *tree, graph *centroid_tree) {
	for (int i = 1; i <= tree->V; ++i) 
		mark[i] = 0;
	init_graph(centroid_tree, n);
	return build(tree, 1, 0);;
}
int main() {
	input();
	int head = centroid_decomposition(&tree, &centroid_tree);
	print_graph(&centroid_tree, head, 0);
	return 0;
}
