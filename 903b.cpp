#include <bits/stdc++.h>
using namespace std;
int main(){
	int h1,a1,c1;
	string a[10000];
	int h2,a2;
	int counter=0;
	cin>>h1>>a1>>c1;
	cin>>h2>>a2;
	while(h2>0){
		if(h2<=a1){
			a[counter]="STRIKE";
			counter++;
			break;
		}
       if(h1-a2>0){
       	h1=h1-a2;
       	h2=h2-a1;
      a[counter]="STRIKE";
       	counter++;
       }
       else
       {
       	h1=h1+c1-a2;
        a[counter]="HEAL";
        counter++;
       }
}
cout<<counter<<endl;
for(int i=0;i<counter;i++){
	cout<<a[i]<<"\n";
}
return 0;
}
