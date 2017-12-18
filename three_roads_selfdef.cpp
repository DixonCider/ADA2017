#include <iostream>
#include <stack>
#include <string.h>
using namespace std;

int visited[100000] = {0};
stack<unsigned long long>dfs;

struct node {
	unsigned long long dest;
	struct node* next;
};
struct list {
	struct node* head;
};
node box[200000];
unsigned long long box_itr = 0;
class graph {
private:
	unsigned long long V;
	struct list* ary;
public:
	// constructor
	graph(unsigned long long V){
		this->V = V;
		ary = new list[V];
		for(unsigned long long i=0;i<V;i++) ary[i].head = NULL;
	}
	node* createNode(unsigned long long dest) {
		node* newNode = &box[box_itr];
		++box_itr;
		newNode->dest = dest;
		newNode->next = NULL;	// good practice
		return newNode;
	}
	void addEdge(unsigned long long src, unsigned long long dest){
		node* newNode = createNode(dest);
		newNode->next = ary[src].head; // append to head of adjacency list
		ary[src].head = newNode; // let newNode be head
		newNode = createNode(src);
		newNode->next = ary[dest].head;
		ary[dest].head = newNode;
	}
	node* nextNode(node* nowNode){
		node* next = nowNode->next;
		return next;
	}
	node* getHead(unsigned long long u){
		node* head = ary[u].head;
		return head;
	}
	void resetHead(unsigned long long v){
		for(unsigned long long i=0;i<v;i++) ary[i].head = NULL;
	}
};

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	unsigned long long T;
	graph Alist(100000);
	cin >> T;
	while(T--){
		unsigned long long TOTAL_ROAD = 0;
		unsigned long long N,M,U,V;
		box_itr = 0;
		// read data
		cin >> N >> M;
		// reset visited array
		memset(visited,0,N*sizeof(int));
		while(M--){
			cin >> U >> V;
			--U;--V;
			Alist.addEdge(U,V);
		}
		// traverse
		for(unsigned long long i=0;i<N;++i){
			if(visited[i]==0){
				unsigned long long even = 0,edge = 0,odd=0;
				bool isOddCycle = false;	// if odd cycle exist -> true
				// push in source node
				dfs.push(i);
				visited[i] = 1;
				while(!dfs.empty()){
					int u = dfs.top();
					dfs.pop();
					if(visited[u]==1) ++even;
					else ++odd;
					node* itr = Alist.getHead(u);
					while(itr!=NULL){
						++edge;
						if(visited[itr->dest]==0){
							dfs.push(itr->dest);
							visited[itr->dest] = -visited[u];
						}
						else if(visited[itr->dest]==visited[u]) isOddCycle = true;
						itr = itr->next;
					}
				}
				if(isOddCycle) TOTAL_ROAD += ((even+odd)*(even+odd-1)-edge)/2;
				else TOTAL_ROAD += even*odd-edge/2;
			}
		}
		cout << TOTAL_ROAD << "\n";
		Alist.resetHead(N);
	}
}
