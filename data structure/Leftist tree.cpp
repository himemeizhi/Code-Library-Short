int merge(int a,int b)
{
    if(!a)
        return b;
    if(!b)
        return a;
    if(val[a]<val[b]) // max-heap
        std::swap(a,b);
    if(rand()&1)
        r[a]=merge(r[a],b);
    else
        l[a]=merge(l[a],b);
    fa[l[a]]=fa[r[a]]=a; // set a as father of its sons
    return a;
}
