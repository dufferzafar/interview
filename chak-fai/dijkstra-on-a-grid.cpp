/*
Dijkstra: In a 2-D grid, given a start point at (0,0) and end point at (n-1,m-1). Also each cell has a positive cost.
Find the minimum cost to go from start to end.
*/

#include<bits/stdc++.h>
using namespace std;

struct coor {
    int x,y;
    bool operator < (const coor &a) const {
        return a.x < x;
    }
};

int n,m,a[105][105],v[105][105];
int dx[]={1,0,-1,0},dy[]={0,1,0,-1};


void dijkstra() {
    scanf("%d%d",&n,&m);
    int g[n][m];
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            scanf("%d",&g[i][j]);
        }
    }

    int dp[n][m];

    memset(dp,62,sizeof(dp));
    priority_queue<pair<int,coor> > pq;
    int cost = 0;
    coor at; at.x = 0; at.y = 0;
    dp[at.x][at.y] = g[at.x][at.y];
    pq.push(make_pair(-dp[at.x][at.y], at));

    while (!pq.empty()) {
        at = pq.top().second;
        cost = -pq.top().first;
        pq.pop();
        if (at.x == n-1 && at.y == m-1) {
            break;
        }
        for (int d=0; d<4; d++) {
            coor nat;
            nat.x = at.x+dx[d]; nat.y = at.y+dy[d];
            if (nat.x >= 0 && nat.x < n && nat.y >= 0 && nat.y < m) {
                if (cost + g[nat.x][nat.y] < dp[nat.x][nat.y]) {
                    dp[nat.x][nat.y] = cost + g[nat.x][nat.y];
                    pq.push(make_pair(-dp[nat.x][nat.y], nat));
                }
            }
        }
    }
    printf("%d\n",cost);
}


int main() {

}
