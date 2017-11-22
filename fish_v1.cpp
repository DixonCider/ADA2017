// incorrect version
#include <cstdio>
#include <iostream>
using namespace std;

unsigned long long fh[10001][1000] = {0};
int used[10001][1000] = {0};
int df[1000] = {0};
int val[1000] = {0};

int main()
{
    int i,j,k,T,N,K,add,loop;
    scanf("%d", &T);
    while(T--){
        scanf("%d %d", &N, &K);
        for(i=0;i<N;i++) scanf("%d %d", &val[i], &df[i]);
        // base case N = 0
        for(i=1;i<=val[0]/df[0]+1;i++){
            fh[i][0] = fh[i-1][0] + val[0] - df[0]*used[i-1][0];
            used[i][0] = i;
        }
        for(i=1;i<=K;i++){
            for(j=1;j<N;j++){
                add = val[j] - df[j]*used[i-1][j];
                if(add<0) add = 0;
                if(fh[i-1][j]+add>fh[i-1][j-1] && i>j){
                    fh[i][j] = fh[i-1][j]+add;
                    used[i][j] = used[i-1][j] + 1;
                }else{
                    fh[i][j] = fh[i-1][j-1];
                }
                if(j>=i) break;
            }
        }
        printf("%llu\n", fh[K][N-1]);
    }
    return 0;
}