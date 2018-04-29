#include<bits/stdc++.h>
using namespace std;
long long int speed;
typedef  struct trie
{
    struct trie* ar[26];
    int flag;
    int pry;
} trie;
trie* root=NULL;
string a[2000006];
trie* create()
{
  trie* temp=(trie*)malloc(sizeof(trie));
  temp->flag=0;
  for (int i = 0; i < 26; ++i)
  {
    temp->ar[i]=NULL;
  }
  temp->pry=0;
  return temp;
}
void insert(string str,int n,int pr)
{
  trie* temp=root;
  int y=1;
    for (int i = 0; i < n; ++i)
    {
        if(temp->ar[str[i]-'a']==NULL)
        {
          temp->ar[str[i]-'a']=create();
          temp=temp->ar[str[i]-'a'];
    			if((i+1)<=(n+1)/2)
          {
    				temp->flag=y;
    				++y;
    			}
    			else
    			{
    				temp->flag=n-i+1 ;
    			}
        }
        else
        {
          trie *temp2=root;
        	int v=1,i;
        	for(i=0;i<n;++i)
          {
          if(temp2->ar[str[i]-'a']==NULL)   break;
        		temp2=temp2->ar[str[i]-'a'];
        	}
        	int var=temp2->flag;
        	int l=n-i;
        	for(int j=i;j<n;++j)
        	{
        		temp2->ar[str[j]-'a']=create();
        		temp2=temp2->ar[str[j]-'a'];
        		if(v<=(l+1)/2)  temp2->flag=var+v;
        		else  temp2->flag=var+l-v+2;
        		++v;
        	}

          break;
        }
        // temp=temp->ar[str[i]-'a'];
    }
}
void srch(string str,int n,int pr)
{
  trie* temp=root;
    for (int i = 0; i < n; ++i)
    {
        if(temp->ar[str[i]-'a']==NULL)
        {
          speed=n+temp->flag-i;
    			cout<<speed<<"\n";
    			return;
        }
        temp=temp->ar[str[i]-'a'];
      }
    speed=temp->flag;
    cout<<speed<<"\n";
    temp->pry=pr;
}

int main()
{
  root=create();
  int m,n;
  cin>>m>>n;
  for (int i = 1; i <=m; i++)
  {
    cin>>a[i];
    insert(a[i],a[i].length(),i);
  }
  // string ma="maki";
  // srch(ma,5,"making");
  for (int i = 0; i < n; i++)
  {
    speed=0;
    string str;cin>>str;
    {
      srch(str,str.length(),i+1);
    }
  }
  return 0;
}
