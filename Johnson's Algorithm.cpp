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

*Author Deepak Mehrotra (StealthX2k20)

*Finding all Simple Cycles in a Directed Graph using Johnson's Algorithm

*Time Complexity O(E + V) * (c + 1) where c is the number of cycles in the directed graph

*Space Complexity O(E + V + s) where s is the sum of length of all cycles in the graph

*References : https://github.com/mission-peace/interview/blob/master/src/com/interview/graph/AllCyclesInDirectedGraphJohnson.java

**/

mii node_num;
map < loi, vii > comp_num;

void dfs(vii graph[], loi root, loi vis[], stack <loi> &stk)
{
    vis[root] = 1;
    rep(i, graph[root].size())
    {
         if(!vis[graph[root][i]])
       dfs(graph, graph[root][i], vis, stk);
    }

    stk.push(root);
    return;
}

void tour(vii graph[], loi root, loi vis[], vii &scc)
{
    vis[root] = 1;
    scc.pb(root);
    rep(i, graph[root].size())
    {
        if(!vis[graph[root][i]])
         tour(graph, graph[root][i], vis, scc);
    }

    return;
}

//Kosaraju's Algorithm for finding SCC in a directed graph
void Kosaraju(vii graph[], vii rgraph[], loi n, loi m, vector < vii > &SCC)
{
    stack < loi > stk;
    loi node;
    loi vis[n];
    memset(vis, 0, sizeof(vis));
   
    rep(i, n)
    {
        if(!vis[i])
        {
            dfs(graph, i, vis, stk);
        }
    }

    memset(vis, 0, sizeof(vis));
    vii scc;

    loi cur = 0;

    while(!stk.empty())
    {
       node = stk.top();
       stk.pop();

       if(!vis[node])
       {
          scc.clear();
          tour(rgraph, node, vis, scc);
          sort(all(scc));
          SCC.pb(scc);

          rep(i, scc.size())
              node_num[scc[i]] = cur;

          comp_num[cur++] = scc;
       }
    }

    return;
}

void unlock_all(sii &st, mii &mp, loi root)
{
    if(mp.find(root) == mp.end() or mp[root] == -1)
    {  
        if(st.find(root) != st.end())
        st.erase(st.find(root));
        return;
    }

    unlock_all(st, mp, mp[root]);
    st.erase(st.find(root));
    mp[root] = -1;
    return;
}

//Johnson's Algorithm for Cycle counting in a Directed Graph
void cycleDFS(vii graph[], loi root, loi vis[], stack <loi> &stk, sii &st, mii &mp, loi start, loi &cnt)
{
    stk.push(root);
    st.insert(root);

    rep(i, graph[root].size())
    {
       if(graph[root][i] != start and st.find(graph[root][i]) == st.end())
       {
         cycleDFS(graph, graph[root][i], vis, stk, st, mp, start, cnt);
       }

       else if(graph[root][i] == start)
       {
           cnt++;
           stack <loi> stk1;
           stk1 = stk;

           while(!stk1.empty())
           vis[stk1.top()] = cnt, stk1.pop();
       }

       else mp[graph[root][i]] = root;
    }
   
   stk.pop();

   if(vis[root])
      unlock_all(st, mp, root);
    
   return;
}

int main()
{
    loi n, m, u, v, node, vertx;
    
    //n -> number of vertices
    //m -> number of edges
    
    cin >> n >> m;
    vii graph[n], rgraph[n];
    rep(i, m)
    {
        cin >> u >> v;
        u--, v--;
        graph[u].pb(v);
        rgraph[v].pb(u); // this reverse graph is being made to find the SCCs of the directed graph using Kosaraju's Algorithm
    }

    vector < vii > SCC;
    
    // This is used to store the nodes in a storngly-connected-component
    vii scc;

    Kosaraju(graph, rgraph, n, m, SCC);
    
    loi cnt = 0;
    
    vii dummy[n]; // This is used to store the subgraph of the vertices belonging to the same strongly connected component
    
    loi vis[n];
    
    stack <loi> stk;
    sii st;
    mii mp;

    rep(i, n)
    {
      node = i;
      scc = comp_num[node_num[node]];
      
      if(scc.size() == 1) continue;

      rep(j, scc.size())
      {
          vertx = scc[j];
          rep(k, graph[vertx].size())
          {
               if(binary_search(all(scc), graph[vertx][k]))
               dummy[vertx].pb(graph[vertx][k]);
          }
      }
      
      while(!stk.empty()) stk.pop();
      st.clear();
      
      memset(vis, 0, sizeof(vis));
      cycleDFS(dummy, node, vis, stk, st, mp, node, cnt);
      
      rep(j, n) dummy[j].clear();
      
      rep(j, n)
      {
         if(j == node) continue;

          rep(k, graph[j].size())
          {
           if(graph[j][k] != node)
           {
            dummy[j].pb(graph[j][k]);
           }
          }
      }

      rep(j, n) graph[j] = dummy[j];

      SCC.clear();
      node_num.clear();
      comp_num.clear();

      rep(j, n) rgraph[j].clear();

      rep(j, n)
      {
          rep(k, graph[j].size())
          {
              rgraph[graph[j][k]].pb(j);
          }
      }

      Kosaraju(graph, rgraph, n, m, SCC);

      rep(j, n) dummy[j].clear();
    }
    
    cout << "Total cycles are : " << cnt << "\n"; 

    return 0;
}
