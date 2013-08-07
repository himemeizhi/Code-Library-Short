#include<cstdio>
#include<cstring>
#include<algorithm>

const int inf = 0x5fffffff;

int n,m,u,v,cost,dis[1001][1001],L;
int pre[1001],id[1001],visit[1001],in[1001];

void init(int n)
{
    L = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dis[i][j] = inf;
}

struct Edge
{
    int u,v,cost;
};

Edge e[1001*1001];


int zhuliu(int root,int n,int m,Edge e[])
{
    int res = 0,u,v;
    while (true)
    {
        for (int i = 0; i < n; i++)
            in[i] = inf;
        for (int i = 0; i < m; i++)
            if (e[i].u != e[i].v && e[i].cost < in[e[i].v])
            {
                pre[e[i].v] = e[i].u;
                in[e[i].v] = e[i].cost;
            }
        for (int i = 0; i < n; i++)
            if (i != root)
                if (in[i] == inf)   
                    return -1;
        int tn = 0;
        memset(id,-1,sizeof(id));
        memset(visit,-1,sizeof(visit));
        in[root] = 0;
        for (int i = 0; i < n; i++)
        {
            res += in[i];
            v = i;
            while (visit[v] != i && id[v] == -1 && v != root)
            {
                visit[v] = i;
                v = pre[v];
            }
            if(v != root && id[v] == -1)
            {
                for(int u = pre[v] ; u != v ; u = pre[u])
                    id[u] = tn;
                id[v] = tn++;
            }
        }
        if(tn == 0) break;
        for (int i = 0; i < n; i++)
            if (id[i] == -1)
                id[i] = tn++;
        for (int i = 0; i < m;)
        {
            int v = e[i].v;
            e[i].u = id[e[i].u];
            e[i].v = id[e[i].v];
            if (e[i].u != e[i].v)
                e[i++].cost -= in[v];
            else
                std::swap(e[i],e[--m]);
        }
        n = tn;
        root = id[root];
    }
    return res;
}

int main()
{
    while (scanf("%d%d",&n,&m) != EOF)
    {
        init(n);
        for (int i = 0; i < m; i++)
        {
            scanf("%d%d%d",&u,&v,&cost);
            if (u == v) continue;
            dis[u][v] = std::min(dis[u][v],cost);
        }
        L = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dis[i][j] != inf)
                {
                    e[L].u = i;
                    e[L].v = j;
                    e[L++].cost = dis[i][j];
                }
        printf("%d\n",zhuliu(0,n,L,e));
    }
    return 0;
}

