#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double
const int N=5005,mod=1e9+7,inf=0x3f3f3f3f;
char s[N];
int n,pw[N],val[N],f[N][N],mg[N][N],g[N][N],lcp[N][N];
int ask(int l,int r){return (val[r]-1ll*val[l-1]*pw[r-l+1]%mod+mod)%mod;}
bool check(int p,int q,int len){
	int sp=p-len+1,sq=q-len+1,ans=0;
	ans=lcp[sp][sq];
	if(ans>=len)return true;
	return s[sp+ans]<s[sq+ans];
}
signed main(){
	cin>>s+1;n=strlen(s+1);pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=pw[i-1]*2%mod;
	for(int i=1;i<=n;i++)val[i]=(val[i-1]*2%mod+(s[i]-'0'))%mod;
	for(int i=n;i>=1;i--)
		for(int j=n;j>=1;j--) 
			if(s[i]==s[j])lcp[i][j]=lcp[i+1][j+1]+1;
			else lcp[i][j]=0; 
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			if(j==1){f[i][j]=1;g[i][j]=1;continue;}
			if(s[j]=='0'){f[i][j]=f[i][j-1];g[i][j]=inf;continue;}
			int l=i-j+1;
			f[i][j]=(f[i][j]+f[j-1][j-1]-f[j-1][max(j-l,0)]+mod)%mod;
			g[i][j]=mg[j-1][min(max(j-l+1,1),j-1)]+1;
			if(j-1>=l&&s[j-l]!='0'&&check(j-1,i,l)){
				f[i][j]=((ll)f[i][j]+f[j-1][j-l]-f[j-1][j-l-1]+mod)%mod;
				g[i][j]=min(g[i][j],g[j-1][j-l]+1);
			}
			f[i][j]=(f[i][j-1]+f[i][j])%mod;
		}
		mg[i][i]=g[i][i];
		for(int j=i-1;j>=1;j--)mg[i][j]=min(mg[i][j+1],g[i][j]);
	}
	printf("%d\n",f[n][n]);
	double sum=1e20;int ans=0;
	for(int i=1;i<=n;i++){
		if((f[n][i]-f[n][i-1]+mod)%mod==0)continue;
		int cnt=g[n][i];
		double gr=0,p=1;
		for(int j=i;j<=n;j++,p*=0.5)
			if(s[j]=='1')gr=gr+p;
		double cur=log10(gr)+log10(2)*(n-i+1);
		if(n-i+1<=30)cur=cur+log10((double)cnt/(gr*(1<<n-i))+1);
		if(cur<sum)sum=cur,ans=(ask(i,n)+cnt)%mod;
	} 
	printf("%d\n",ans);
}
/*
大致思路：
我们维护两个dp方程
f[i][j]表示到了第i个点，[j,i]分成一段的方案数
g[i][j]表示到了第i个点，[j,i]分成一段的最少分段数
对f[i][j]维护前缀和，g[i][j]维护后缀min，方便转移 
第一问很简单,f[n][n]
对于第二问，答案就是k+v,v就是最后一段的值，k就是分段数
我们发现2^17>5000，k 最多就是5000
所以最后一段分在n-16之前一定不优，因为v增加的超过了k的最大值
不过实现是直接用log+long double比较
*/