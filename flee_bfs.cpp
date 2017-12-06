#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <string.h>
#include <climits>
using namespace std;

char ary[3000][3000] = {0};
int dist[3000][3000] = {0};
int pIndex[100000] = {0};
bool visited[3000][3000] = {0};
queue<int> bfsQ;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int row,column,pCnt=0;
	//input
	cin >> row >> column;
	for(int i=0;i<row;++i) 
		for(int j=0;j<column;++j){
			cin >> ary[i][j];
			dist[i][j] = INT_MAX;
			if(ary[i][j]=='E'){
				bfsQ.push(i*column + j);
				dist[i][j] = 0;
			}
			else if(ary[i][j]=='P'){
				pIndex[pCnt] = i*column + j;
				++pCnt;
			}
		}
	// index = i*column + j
	visited[bfsQ.front()/column][bfsQ.front()%column] = 1;
	while(!bfsQ.empty()){
		int px = bfsQ.front()/column;
		int py = bfsQ.front()%column;
		int d = dist[px][py];
		bfsQ.pop();

		// in border + not visited + better distance		
		if(px-1>=0 && visited[px-1][py]==0 && ary[px-1][py]!='F' && dist[px-1][py]>d){
			visited[px-1][py] = 1;
			dist[px-1][py] = d + 1;
			bfsQ.push((px-1)*column+py);
		}
		if(px+1<column && visited[px+1][py]==0 && ary[px+1][py]!='F' && dist[px+1][py]>d){
			visited[px+1][py] = 1;
			dist[px+1][py] = d + 1;
			bfsQ.push((px+1)*column+py);
		}
		if(py-1>=0 && visited[px][py-1]==0 && ary[px][py-1]!='F' && dist[px][py-1]>d){
			visited[px][py-1] = 1;
			dist[px][py-1] = d + 1;
			bfsQ.push(px*column+py-1);
		}
		if(py+1<row && visited[px][py+1]==0 && ary[px][py+1]!='F' && dist[px][py+1]>d){
			visited[px][py+1] = 1;
			dist[px][py+1] = d + 1;
			bfsQ.push(px*column+py+1);
		}
	}
	for(int i=0;i<pCnt;i++){
		if(dist[pIndex[i]/column][pIndex[i]%column] != INT_MAX) cout << dist[pIndex[i]/column][pIndex[i]%column];
		else cout << "Died";
		cout << "\n";
	}
}
