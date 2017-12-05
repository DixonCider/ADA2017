#include <iostream>
#include <list>
#include <vector>
#include <utility>
#include <queue>
#define ULLMAX 18446744073709551615
using namespace std;

unsigned long long dist[300001] = {0};
class myComparator
{
public:
    int operator() (const int& p1, const int& p2)
    {
        return dist[p1] > dist[p2];
    }
};

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int n,m,s,t,tmp1,tmp2,tmp3;
	unsigned long long TOTAL_WEIGHT = 0;
	
	cin >> n >> m >> s >> t;	// n: # of nodes, m: # of edges, s to t
	s--;t--;
	vector< list< pair<int,int> > >Alist(n);
	
	for(int i=0;i<m;i++){
		cin >> tmp1 >> tmp2 >> tmp3;
		TOTAL_WEIGHT += tmp3;
		Alist[tmp1-1].push_back(make_pair(tmp2-1,tmp3));
		Alist[tmp2-1].push_back(make_pair(tmp1-1,tmp3));
	}

	bool isQ[300001] = {0};
	priority_queue<int, vector<int>, myComparator > pq;
	
	pq.push(s);
	isQ[s] = 1;
	for(int i=0;i<n;i++) if(i!=s) dist[i] = ULLMAX;
	
	while(!pq.empty()){
		int u = pq.top();
		pq.pop();
		list< pair<int, int> >::iterator itr = Alist[u].begin();		         
		while (itr != Alist[u].end()) {
			unsigned long long neW = dist[u] + (*itr).second;
			int v = (*itr).first;
			if(neW < dist[v]){
				dist[v] = neW;
				if(isQ[v]==0){
					isQ[v] = 1;
					pq.push(v);
				}
			}
			++itr;
		}
	}
	if(dist[t]>TOTAL_WEIGHT) cout << "-1";
	else cout << TOTAL_WEIGHT - dist[t];
	cout << endl;
}
