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
vector< queue<int> >bfsQ;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int row,column,eCnt=0,pCnt=0;
	//input
	cin >> row >> column;
	for(int i=0;i<row;++i) 
		for(int j=0;j<column;++j){
			cin >> ary[i][j];
			dist[i][j] = INT_MAX;
			if(ary[i][j]=='E'){
				bfsQ.push_back(queue<int>());
				bfsQ[eCnt].push(i*column + j);
				++eCnt;
				dist[i][j] = 0;
			}
			else if(ary[i][j]=='P'){
				pIndex[pCnt] = i*column + j;
				++pCnt;
			}
		}
	// index = i*column + j
	for(int i=0;i<eCnt;i++){
		memset(visited, 0, sizeof(visited));	//reset visited
		visited[bfsQ[i].front()/column][bfsQ[i].front()%column] = 1;
		while(!bfsQ[i].empty()){
			int px = bfsQ[i].front()/column;
			int py = bfsQ[i].front()%column;
			int d = dist[px][py];
			bfsQ[i].pop();

			// in border + not visited + better distance		
			if(px-1>=0 && visited[px-1][py]==0 && dist[px-1][py]>d){
				visited[px-1][py] = 1;
				dist[px-1][py] = d + 1;
				bfsQ[i].push((px-1)*column+py);
			}
			if(px+1<column && visited[px+1][py]==0 && dist[px+1][py]>d){
				visited[px+1][py] = 1;
				dist[px+1][py] = d + 1;
				bfsQ[i].push((px+1)*column+py);
			}
			if(py-1>=0 && visited[px][py-1]==0 && dist[px][py-1]>d){
				visited[px][py-1] = 1;
				dist[px][py-1] = d + 1;
				bfsQ[i].push(px*column+py-1);
			}
			if(py+1<row && visited[px][py+1]==0 && dist[px][py+1]>d){
				visited[px][py+1] = 1;
				dist[px][py+1] = d + 1;
				bfsQ[i].push(px*column+py+1);
			}
		}
	}
	for(int i=0;i<pCnt;i++)	cout << dist[pIndex[i]/column][pIndex[i]%column] << "\n";
}
