#include<bits/stdc++.h>
using namespace std;
#define loi long long
#define lod long double
#define doubel double
#define pb push_back
#define run ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define mod 1000000007
#define lim 5000000000000000000
#define in(ar, n) for(loi i = 0; i < n; i++) cin >> ar[i];
#define out(ar, n) for (loi i = 0; i < n; i++) cout << ar[i] << " "; cout << "\n";
#define rep(i, n) for(loi i = 0; i < n; i++)
#define rep1(i, n) for(loi i = 1; i <= n; i++)
#define rev(i, n) for(loi i = n - 1; ~i; i--)
#define rep3(i, l, r) for(loi i = l; i <= r; i++)
#define rev3(i, r, l) for(loi i = r; i >= l; i--)
#define rep4(i, r, l) for(loi i = r; i >= l; i--)
#define all(x) x.begin(), x.end ()
#define mkp make_pair
#define vii vector<loi>
#define mii map<loi, loi>
#define sii set<loi>
#define pii pair<loi, loi>
#define mxdepth 23 // FOR LCA til N = 1e6
#define mxn 2000001

/**
 * 
 * Author : Deepak Mehrotra (StealthX2k20)
 * 
 * Finding Single Source Shortest Path in an Unweighted Graph using BFS
 * 
 * Time Complexity : O(E + V) 
 * 
 * Space Complexity : O(E + V)
 *
 * Here I am taking example of undirected graph, we can do the same for the directed one.
 * 
 **/

void BFS(vii graph[], loi dist[], loi src, loi n, loi m)
{
    rep(i, n) dist[i] = INT_MAX;
    
    loi vis[n];
    memset(vis, 0, sizeof(vis));

    queue <loi> Q;

    //initialising values for the source vertex
    Q.push(src);
    dist[src] = 0;
    vis[src] = 1;
    
    loi cur, vert;

    while(!Q.empty())
    {
      cur = Q.front();
      Q.pop();
      
      rep(i, graph[cur].size())
      {
          vert = graph[cur][i];

          if(!vis[vert])
          {
              vis[vert] = 1;
              dist[vert] = 1ll + dist[cur];
              Q.push(vert);
          }
      }
    }

    return;
}

int main()
{
    loi n, m; // number of vertices, number of edges
    
    cin >> n >> m;

    vii graph[n];

    loi u, v;

    rep(i, m)
    {
        cin >> u >> v;
        u--, v--;
        graph[v].pb(u); // adding edges
        graph[u].pb(v); // adding edges
    }

    //let source vertex be 0
    loi dist[n];
    loi src = 0;

    BFS(graph, dist, src, n, m);

    rep(i, n)
    {
        cout << "Length of shortest path from vertex " << (src + 1) << " to vertex " << (i + 1) << " is " << dist[i] << "\n";
    }

    return 0;
}
