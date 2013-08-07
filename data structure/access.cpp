//记得随手down啊……亲……
//debug时记得优先检查up/down/select

inline void rot(int id,int tp)
{
    static int k;
    k=pre[id];
    nxt[k][tp^1]=nxt[id][tp];
    if(nxt[id][tp])
        pre[nxt[id][tp]]=k;
    if(pre[k])
        nxt[pre[k]][k==nxt[pre[k]][1]]=id;
    pre[id]=pre[k];
    nxt[id][tp]=k;
    pre[k]=id;
    up(k);
    up(id);
}

inline void down(int id) //记得随手down啊……亲……
{
    static int i;
    if(rev[id])
    {
        rev[id]=false;
        std::swap(nxt[id][0],nxt[id][1]);
        for(i=0;i<2;++i)
            if(nxt[id][i])
                rev[nxt[id][i]]^=true;
    }
}

int freshen(int id)
{
    int re(id);
    if(pre[id])
        re=freshen(pre[id]);
    down(id);
    return re;
}

inline void splay(int id)//记得随手down啊……亲……
{
    static int rt;
    if(id!=(rt=freshen(id)))
        for(std::swap(fa[id],fa[rt]);pre[id];rot(id,id==nxt[pre[id]][0]));
    /* another faster methond:
    if(id!=rt)
    {
        std::swap(fa[id],fa[rt]);
        do
        {
            rt=pre[id];
            if(pre[rt])
            {
                k=(nxt[pre[rt]][0]==rt);
                if(nxt[rt][k]==id)
                    rot(id,k^1);
                else
                    rot(rt,k);
                rot(id,k);
            }
            else
                rot(id,id==nxt[rt][0]);
        }
        while(pre[id]);
    }
    */
}
