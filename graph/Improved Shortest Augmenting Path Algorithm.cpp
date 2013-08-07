int source,sink;

inline long long go(const int N=sink)
{
    static int now,N,i;
    static long long min,mf;
    memset(gap,0,sizeof gap);
    memset(h,0,sizeof h);
    memcpy(w,edge,sizeof w);
    gap[0]=N;
    mf=0;

    pre[now=source]=-1;
    while(h[source]<N)
    {
rep:
        if(now==sink)
        {
            min=inf;
            for(i=pre[sink];i!=-1;i=pre[to[i^1]])
                if(min>=cap[i])
                {
                    min=cap[i];
                    now=to[i^1];
                }
            for(i=pre[sink];i!=-1;i=pre[to[i^1]])
            {
                cap[i]-=min;
                cap[i^1]+=min;
            }
            mf+=min;
        }
        for(int &i(w[now]);i!=-1;i=nxt[i])
            if(cap[i] && h[v]+1==h[now])
            {
                pre[now=v]=i;
                goto rep;
            }
        if(!--gap[h[now]])
            return mf;
        min=N;
        for(i=w[now]=edge[now];i!=-1;i=nxt[i])
            if(cap[i])
                min=std::min(min,(long long)h[v]);
        ++gap[h[now]=min+1];
        if(now!=source)
            now=to[pre[now]^1];
    }
    return mf;
}
