#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxn=81*100;
int ans;
int a[10][10],x[maxn],y[maxn],num[maxn];

namespace DLX{
    #define rep(i,e,u) for(int i=e[u];i!=u;i=e[i])
    #define maxs 10000
    int sz;
    int X[maxs],Y[maxs],U[maxs],D[maxs],L[maxs],R[maxs];
    vector<int> cnt;
    void init(int m){
        sz=m;
        for(int i=0;i<=m;i++)
            U[i]=D[i]=i,L[i]=i-1,R[i]=i+1;
        L[0]=m,R[m]=0;cnt.resize(m+1,0);
    }
    void add_row(int r,vector<int> &vec){
        if(!vec.size()) return;
        int p=sz+1;
        for(int c:vec)
            X[++sz]=r,Y[sz]=c,U[sz]=U[c],D[sz]=c,L[sz]=sz-1,R[sz]=sz+1,
            D[U[c]]=sz,U[c]=sz,++cnt[c];
        R[sz]=p,L[p]=sz;
    }
    void erase(int c){
        L[R[c]]=L[c],R[L[c]]=R[c];
        rep(i,D,c) rep(j,R,i) --cnt[Y[j]],U[D[j]]=U[j],D[U[j]]=D[j];
    }
    void restore(int c){
        rep(i,U,c) rep(j,L,i) ++cnt[Y[j]],U[D[j]]=D[U[j]]=j;
        L[R[c]]=c,R[L[c]]=c;
    }
    bool dfs(vector<int> &ret){
        if(!R[0]) return true;
        int c=R[0];
        rep(i,R,0) if(cnt[i]<cnt[c]) c=i;
        erase(c);
        rep(i,D,c){
            ret.push_back(X[i]);
            rep(j,R,i) erase(Y[j]);
            if(dfs(ret)) return true;
            rep(j,L,i) restore(Y[j]);
            ret.pop_back();
        }restore(c);
        return false;
    }
    bool solve(vector<int> &ret){
        return dfs(ret);
    }
    #undef maxs
    #undef rep
}

vector<int> vec;

int main(){
#ifdef LOCAL
    freopen("in.in","r",stdin);
    freopen("out.out","w",stdout);
#endif
    DLX::init(81*4);
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			scanf("%d",&a[i][j]);
		}
	}
	for(int i=1;i<=9;i++){
		for(int j=1;j<=9;j++){
			if(!a[i][j]){
				for(int d=1;d<=9;d++){
					vec.clear();
					vec.push_back((i-1)*9+j);
					vec.push_back(81+(i-1)*9+d);
					vec.push_back(2*81+(j-1)*9+d);
					vec.push_back(3*81+((i-1)/3*3+(j-1)/3)*9+d);
                    int id=(i-1)*81+(j-1)*9+d;
                    x[id]=i,y[id]=j,num[id]=d;
					DLX::add_row(id,vec);
				}
			}else{
				int d=a[i][j];vec.clear();
				vec.push_back((i-1)*9+j);
				vec.push_back(81+(i-1)*9+d);
				vec.push_back(2*81+(j-1)*9+d);
				vec.push_back(3*81+((i-1)/3*3+(j-1)/3)*9+d);
                int id=(i-1)*81+(j-1)*9+d;
                x[id]=i,y[id]=j,num[id]=d;
				DLX::add_row(id,vec);
			}
		}
	}
	vec.clear();
	if(!DLX::solve(vec)){
        puts("No Solution!");return 0;
    }
    for(int k=0;k<vec.size();k++){
        a[x[vec[k]]][y[vec[k]]]=num[vec[k]];
    }
    for(int i=1;i<=9;i++){
        for(int j=1;j<=9;j++){
            printf("%d ",a[i][j]);
        }puts("");
    }
}
