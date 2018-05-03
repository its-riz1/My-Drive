#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define pb push_back
const ll d=1e9+7;
struct mat
{
	ll _11_;
	ll _12_;
	ll _21_;
	ll _22_;	
};
mat seg_t[400010];
ll mak[100010][4];
void make_segt(ll index,ll s,ll e)
{
	if(s>e)
		return;
	if(s==e)
	{
		seg_t[index]._11_=mak[s][0];
		seg_t[index]._12_=mak[s][1];
		seg_t[index]._21_=mak[s][2];
		seg_t[index]._22_=mak[s][3];
		return;
	}
	make_segt(2*index+1,s,(s+e)/2);
	make_segt(2*index+2,(s+e)/2+1,e);
	seg_t[index]._11_=((((((seg_t[2*index+1]._11_)%d)*((seg_t[2*index+2]._11_))%d))%d+((((seg_t[2*index+1]._12_)%d)*((seg_t[2*index+2]._21_))%d))%d)%d);
	seg_t[index]._12_=((((((seg_t[2*index+1]._11_)%d)*((seg_t[2*index+2]._12_))%d))%d+((((seg_t[2*index+1]._12_)%d)*((seg_t[2*index+2]._22_))%d))%d)%d);
	seg_t[index]._21_=((((((seg_t[2*index+1]._21_)%d)*((seg_t[2*index+2]._11_))%d))%d+((((seg_t[2*index+1]._22_)%d)*((seg_t[2*index+2]._21_))%d))%d)%d);
	seg_t[index]._22_=((((((seg_t[2*index+1]._21_)%d)*((seg_t[2*index+2]._12_))%d))%d+((((seg_t[2*index+1]._22_)%d)*((seg_t[2*index+2]._22_))%d))%d)%d);
}
mat query(ll l,ll r,ll sl,ll sr,ll index)
{
	// cout<<sl<<" "<<sr<<" ||||||||||||||||| "<<l<<" "<<r<<"\n";
	if(r<sl || sr<l)
	{
		mat m;
		m._11_=1	;
		m._12_=0;
		m._21_=0;
		m._22_=1;
		// cout<<"-------- "<<sl<<" "<<sr<<" -------\n";
		return m;
	}
	if(l<=sl && sr<=r)
	{
		mat m;
		m._11_=seg_t[index]._11_;
		m._12_=seg_t[index]._12_;
		m._21_=seg_t[index]._21_;
		m._22_=seg_t[index]._22_;
		return m; 
	}
	// cout<<sl<<" ....... "<<(sl+sr)/2<<endl;
	mat q1=query(l,r,sl,(sl+sr)/2,2*index+1);
	// cout<<q1._11_<<" "<<q1._12_<<" "<<q1._21_<<" "<<q1._22_<<endl;
	// cout<<(sl+sr)/2+1<<" //// "<<sr<<endl;
	mat q2=query(l,r,(sl+sr)/2+1,sr,2*index+2);
	// cout<<sl<<" "<<sr<<" ||||||||||||||||| "<<l<<" "<<r<<"\n";
	// cout<<q1._11_<<" "<<q1._12_<<" "<<q1._21_<<" "<<q1._22_<<endl;
	// cout<<q2._11_<<" "<<q2._12_<<" "<<q2._21_<<" "<<q2._22_<<endl;
	mat q;
	q._11_=((((q1._11_%d)*(q2._11_%d))%d)+(((q1._12_%d)*(q2._21_%d))%d))%d;
	q._12_=((((q1._11_%d)*(q2._12_%d))%d)+(((q1._12_%d)*(q2._22_%d))%d))%d;
	q._21_=((((q1._21_%d)*(q2._11_%d))%d)+(((q1._22_%d)*(q2._21_%d))%d))%d;
	q._22_=((((q1._21_%d)*(q2._12_%d))%d)+(((q1._22_%d)*(q2._22_%d))%d))%d;
	// cout<<q._11_<<" "<<q._12_<<" "<<q._21_<<" "<<q._22_<<endl;
	return q;
}
void update(ll sl,ll sr,mat v,ll s_index,ll index)
{
	if(index<sl || index>sr || sl>sr)
		return;
	if(sl==sr)
	{
		seg_t[index]._11_=v._11_;
		seg_t[index]._12_=v._12_;
		seg_t[index]._21_=v._21_;
		seg_t[index]._22_=v._22_;
		return;
	}
	update(sl,(sl+sr)/2,v,2*s_index+1,index);
	update((sl+sr)/2+1,sr,v,2*s_index+2,index);
	seg_t[index]._11_=((((((seg_t[2*index+1]._11_)%d)*((seg_t[2*index+2]._11_))%d))%d+((((seg_t[2*index+1]._12_)%d)*((seg_t[2*index+2]._21_))%d))%d)%d);
	seg_t[index]._12_=((((((seg_t[2*index+1]._11_)%d)*((seg_t[2*index+2]._12_))%d))%d+((((seg_t[2*index+1]._12_)%d)*((seg_t[2*index+2]._22_))%d))%d)%d);
	seg_t[index]._21_=((((((seg_t[2*index+1]._21_)%d)*((seg_t[2*index+2]._11_))%d))%d+((((seg_t[2*index+1]._22_)%d)*((seg_t[2*index+2]._21_))%d))%d)%d);
	seg_t[index]._22_=((((((seg_t[2*index+1]._21_)%d)*((seg_t[2*index+2]._12_))%d))%d+((((seg_t[2*index+1]._22_)%d)*((seg_t[2*index+2]._22_))%d))%d)%d);	
}
int main()
{
	ll n,i,q,qt,l,r;
	cin>>n;
	for(i=0;i<n;i++)
		cin>>mak[i][0]>>mak[i][1]>>mak[i][2]>>mak[i][3];
	make_segt(0,0,n-1);
	// for(i=0;i<=12;i++)
	// 	cout<<i<<">>>>> "<<seg_t[i]._11_<<" "<<seg_t[i]._12_<<" "<<seg_t[i]._21_<<" "<<seg_t[i]._22_<<endl;
	cin>>q;
	while(q--)
	{
		cin>>qt;
		if(qt==1)
		{
			cin>>l>>r;
			l--;
			r--;
			mat m=query(l,r,0,n-1,0	);
			cout<<m._11_<<" "<<m._12_<<" "<<m._21_<<" "<<m._22_<<endl;
		}
		else
		{
			mat u;
			cin>>l>>u._11_>>u._12_>>u._21_>>u._22_;
			update(0,n-1,u,0,l);
		}
	}
	return 0;
}