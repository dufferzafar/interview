/**
 * Came in Sprinklr's test?
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



/*
Given a n*m grid, 1 means obstacle, 2 means starting point, 0 means empty space.
Find the shortest path to any of the boundary.
*/
void escape_from_grid() {
    coor at;
    scanf("%d%d",&n,&m);
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            scanf("%d",&a[i][j]);
            if (a[i][j] == 2) {
                at.x = i; at.y = j;
            }
        }
    }

    memset(v,0,sizeof(v));
    queue<pair<coor,int> > q;
    q.push(make_pair(at,0));
    v[at.x][at.y] = 1;

    int ans = -1;
    while (!q.empty()) {
        at = q.front().first;
        int step = q.front().second;
        q.pop();

        if (at.x == 0 || at.x == n-1 || at.y == 0 || at.y == m-1) {
            ans = step;
            break;
        }

        for (int d=0; d<4; d++) {
            coor nat;
            nat.x = at.x+dx[d]; nat.y = at.y+dy[d];
            if (v[nat.x][nat.y] == 0 && a[nat.x][nat.y] != 1) {
                v[nat.x][nat.y] = 1;
                q.push(make_pair(nat,step+1));
            }
        }
    }

    printf("%d\n",ans);
}
