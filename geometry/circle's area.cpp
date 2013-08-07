//去重
{
    for (int i = 0; i < n; i++)
    {
        scanf("%lf%lf%lf",&c[i].c.x,&c[i].c.y,&c[i].r);
        del[i] = false;
    }
    for (int i = 0; i < n; i++)
        if (del[i] == false)
        {
            if (c[i].r == 0.0)
                del[i] = true;
            for (int j = 0; j < n; j++)
                if (i != j)
                    if (del[j] == false)
                        if (cmp(Point(c[i].c,c[j].c).Len()+c[i].r,c[j].r) <= 0)
                            del[i] = true;
        }
    tn = n;
    n = 0;
    for (int i = 0; i < tn; i++)
        if (del[i] == false)
            c[n++] = c[i];
}

//ans[i]表示被覆盖i次的面积
const double pi = acos(-1.0);
const double eps = 1e-8;
struct Point
{
    double x,y;
    Point(){}
    Point(double _x,double _y)
    {
        x = _x;
        y = _y;
    }
    double Length()
    {
        return sqrt(x*x+y*y);
    }
};
struct Circle
{
    Point c;
    double r;
};
struct Event
{
    double tim;
    int typ;
    Event(){}
    Event(double _tim,int _typ)
    {
        tim = _tim;
        typ = _typ;
    }
};

int cmp(const double& a,const double& b)
{
    if (fabs(a-b) < eps)    return 0;
    if (a < b)  return -1;
    return 1;
}

bool Eventcmp(const Event& a,const Event& b)
{
    return cmp(a.tim,b.tim) < 0;
}

double Area(double theta,double r)
{
    return 0.5*r*r*(theta-sin(theta));
}

double xmult(Point a,Point b)
{
    return a.x*b.y-a.y*b.x;
}

int n,cur,tote;
Circle c[1000];
double ans[1001],pre[1001],AB,AC,BC,theta,fai,a0,a1;
Event e[4000];
Point lab;

int main()
{
    while (scanf("%d",&n) != EOF)
    {
        for (int i = 0;i < n;i++)
            scanf("%lf%lf%lf",&c[i].c.x,&c[i].c.y,&c[i].r);
        for (int i = 1;i <= n;i++)
            ans[i] = 0.0;
        for (int i = 0;i < n;i++)
        {
            tote = 0;
            e[tote++] = Event(-pi,1);
            e[tote++] = Event(pi,-1);
            for (int j = 0;j < n;j++)
                if (j != i)
                {
                    lab = Point(c[j].c.x-c[i].c.x,c[j].c.y-c[i].c.y);
                    AB = lab.Length();
                    AC = c[i].r;
                    BC = c[j].r;
                    if (cmp(AB+AC,BC) <= 0)
                    {
                        e[tote++] = Event(-pi,1);
                        e[tote++] = Event(pi,-1);
                        continue;
                    }
                    if (cmp(AB+BC,AC) <= 0) continue;
                    if (cmp(AB,AC+BC) > 0)  continue;
                    theta = atan2(lab.y,lab.x);
                    fai = acos((AC*AC+AB*AB-BC*BC)/(2.0*AC*AB));
                    a0 = theta-fai;
                    if (cmp(a0,-pi) < 0)    a0 += 2*pi;
                    a1 = theta+fai;
                    if (cmp(a1,pi) > 0)  a1 -= 2*pi;
                    if (cmp(a0,a1) > 0)
                    {
                        e[tote++] = Event(a0,1);
                        e[tote++] = Event(pi,-1);
                        e[tote++] = Event(-pi,1);
                        e[tote++] = Event(a1,-1);
                    }
                    else
                    {
                        e[tote++] = Event(a0,1);
                        e[tote++] = Event(a1,-1);
                    }
                }
            sort(e,e+tote,Eventcmp);
            cur = 0;
            for (int j = 0;j < tote;j++)
            {
                if (cur != 0 && cmp(e[j].tim,pre[cur]) != 0)
                {
                    ans[cur] += Area(e[j].tim-pre[cur],c[i].r);
                    ans[cur] += xmult(Point(c[i].c.x+c[i].r*cos(pre[cur]),c[i].c.y+c[i].r*sin(pre[cur])),
                            Point(c[i].c.x+c[i].r*cos(e[j].tim),c[i].c.y+c[i].r*sin(e[j].tim)))/2.0;
                }
                cur += e[j].typ;
                pre[cur] = e[j].tim;
            }
        }
        for (int i = 1;i < n;i++)
            ans[i] -= ans[i+1];
        for (int i = 1;i <= n;i++)
            printf("[%d] = %.3f\n",i,ans[i]);
    }
    return 0;
}
