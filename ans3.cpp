#include <bits/stdc++.h>
using namespace std;
typedef struct node
{
	node *arr[26];
	int flag;
}node;
node* nodecha(){
	node *temp=(node*)malloc(sizeof(node));
	for(int i=0;i<26;i++)
	{
		temp->arr[i]=NULL;
	}
	temp->flag=0;
	return temp;
}
void rep(string a,node *root)
{
	node *temp=root;
	int i=0,v=1;
	for(i=0;i<a.length();i++)
	{
		if(temp->arr[a[i]-'a']!=NULL)
			temp=temp->arr[a[i]-'a'];
		else
			break;
	}
	int y=temp->flag;
	int l=a.length()-i;
	for(int j=i;j<a.length();j++)
	{
		temp->arr[a[j]-'a']=nodecha();
		temp=temp->arr[a[j]-'a'];
		if(v<=(l+1)/2)
		{
			temp->flag=y+v;
		}
		else
			temp->flag=y+l-v+2;
		cout<<temp->flag;
		v++;
	}
}

void  insert(string a,node *root)
{
	node *temp=root;
	int y=1;
	for(int i=0;i<a.length();i++)
	{
		if(temp->arr[a[i]-'a']==NULL)
		{
			temp->arr[a[i]-'a']=nodecha();
			temp=temp->arr[a[i]-'a'];
			if(i+1<=(a.length()+1)/2)
			{
				temp->flag=y;
				y++;
			}
			else
			{
				temp->flag=a.length()-i+1 ;
			}


		}
		else
		{
			rep(a,root);
			break;
		}
	}
}
int min(int a,int b)
{
	return a<=b? a : b;
}
string a[200009],b[200009];//remember bada karna he
void search(string a,node *root)
{
	node *temp=root;
	int ans;
	for(int i=0;i<a.length();i++)
	{
		if(temp->arr[a[i]-'a']==NULL)
		{
			ans=temp->flag+a.length()-i;
			cout<<ans<<endl;
			return;
		}
		temp=temp->arr[a[i]-'a'];
	}
	ans=temp->flag;
	cout<<ans<<endl;
	return;
}


int main(){
	int i,j,n,m;
	cin>>m>>n;
	for(int i=0;i<m;i++)
	{
		cin>>a[i];
	}
	for(int i=0;i<n;i++)
	{
		cin>>b[i];
	}
	node *root=nodecha();
	for(int i=0;i<m;i++)
	{
		insert(a[i],root);
	}
	for(int i=0;i<n;i++)
	{
		search(b[i],root);
	}
	return 0;
}
