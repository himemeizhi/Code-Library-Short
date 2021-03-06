template<class Tp>class sbt
{
    public:
        inline void init()
        {
            rt=cnt=l[0]=r[0]=sz[0]=0;
        }
        inline void ins(const Tp &a)
        {
            ins(rt,a);
        }
        inline void del(const Tp &a)
        {
            del(rt,a);
        }
        inline Tp pred(const Tp &a)
        {
            return pred(rt,a);
        }
        inline Tp succ(const Tp &a)
        {
            return succ(rt,a);
        }
        inline void delsmall(const Tp &a)
        {
            dels(rt,a);
        }
        inline Tp delsel(int a)
        {
            return delsel(rt,a);
        }
    private:
        int cnt,rt,l[MAXX],r[MAXX],sz[MAXX];
        Tp val[MAXX];
        inline void rro(int &pos)
        {
            int k(l[pos]);
            l[pos]=r[k];
            r[k]=pos;
            sz[k]=sz[pos];
            sz[pos]=sz[l[pos]]+sz[r[pos]]+1;
            pos=k;
        }
        inline void lro(int &pos)
        {
            int k(r[pos]);
            r[pos]=l[k];
            l[k]=pos;
            sz[k]=sz[pos];
            sz[pos]=sz[l[pos]]+sz[r[pos]]+1;
            pos=k;
        }
        inline void mt(int &pos,bool flag)
        {
            if(!pos)
                return;
            if(flag)
                if(sz[r[r[pos]]]>sz[l[pos]])
                    lro(pos);
                else
                    if(sz[l[r[pos]]]>sz[l[pos]])
                    {
                        rro(r[pos]);
                        lro(pos);
                    }
                    else
                        return;
            else
                if(sz[l[l[pos]]]>sz[r[pos]])
                    rro(pos);
                else
                    if(sz[r[l[pos]]]>sz[r[pos]])
                    {
                        lro(l[pos]);
                        rro(pos);
                    }
                    else
                        return;
            mt(l[pos],false);
            mt(r[pos],true);
            mt(pos,false);
            mt(pos,true);
        }
        void ins(int &pos,const Tp &a)
        {
            if(pos)
            {
                ++sz[pos];
                if(a<val[pos])
                    ins(l[pos],a);
                else
                    ins(r[pos],a);
                mt(pos,a>=val[pos]);
                return;
            }
            pos=++cnt;
            l[pos]=r[pos]=0;
            val[pos]=a;
            sz[pos]=1;
        }
        Tp del(int &pos,const Tp &a)
        {
            --sz[pos];
            if(val[pos]==a || (a<val[pos] && !l[pos]) || (a>val[pos] && !r[pos]))
            {
                Tp ret(val[pos]);
                if(!l[pos] || !r[pos])
                    pos=l[pos]+r[pos];
                else
                    val[pos]=del(l[pos],val[pos]+1);
                return ret;
            }
            else
                if(a<val[pos])
                    return del(l[pos],a);
                else
                    return del(r[pos],a);
        }
        void dels(int &pos,const Tp &v)
        {
            if(!pos)
                return;
            if(val[pos]<v)
            {
                pos=r[pos];
                dels(pos,v);
                return;
            }
            dels(l[pos],v);
            sz[pos]=1+sz[l[pos]]+sz[r[pos]];
        }
        Tp delsel(int &pos,int k)
        {
            --sz[pos];
            if(sz[l[pos]]+1==k)
            {
                Tp re(val[pos]);
                if(!l[pos] || !r[pos])
                    pos=l[pos]+r[pos];
                else
                    val[pos]=del(l[pos],val[pos]+1);
                return re;
            }
            if(k>sz[l[pos]])
                return delsel(r[pos],k-1-sz[l[pos]]);
            return delsel(l[pos],k);
        }
};
