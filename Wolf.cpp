#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;
bool CheckGame(char name[], int n);
bool CheckWolf(char a[], int n);
bool CheckHuman(char a[], int n);
bool CheckOther(char a[], int n);
void PrintChar(char a[], int n); 
bool CheckChar(char , char);
int HunterKill();
int Rkill();

int main(){
	int n;
	int i, people[n], temp, pos;
	char name[10];
	int decision;
	bool revive = true;
	bool poison = true;
	
	cout<<"How many people play?";
	cin>>n;

 	srand(time(NULL) );

 	people[0] = n;
 	for(i = 1; i < n; ++i)
  		people[i] = i;
  		
 	for(i = 0; i < n; ++i){//座位洗牌
 		pos=rand()%n;
 		temp=people[i];
 		people[i]=people[pos];
 		people[pos]=temp; 		
 	} 
 	for(i = 0; i < n; ++i)//分配職業 
 		if(people[i]==1 ||people[i]==4 ||people[i]==8)
 			name[i]='F';
 		else if(people[i]==2 ||people[i]==5 ||people[i]==9)
 			name[i]='M';
 		else if(people[i]==6)
 			name[i]='W';
 		else if(people[i]==3)
 			name[i]='P';
 		else if(people[i]==7)
 			name[i]='H';
 		else if(people[i]==10)
 			name[i]='R';
 		
 	PrintChar(name, n);
 	

 	while(true){
 		//狼人 
	 	while(true){
	 		cout<<"Who do you want to kill?"<<endl;
			cin>>decision;
			if(CheckChar(name[decision-1], 'F'))
				continue;
			cout<<"No."<<decision<<"is killed."<<endl;
			system("pause");
			system("cls");
			break;
		 }
		
		//女巫 
		//救 
		if(revive){
			int decision2;
			cout<<"Do you want to save this person? Enter 1 for YES or Enter 0 for NO"<<endl;
			cin>>decision2;
			if(decision2==0){
				name[decision-1]=' ';
				if(CheckChar(name[decision-1],'H'))
					HunterKill();
		 	}else{
		 		revive = false;	
			 }
		 	system("cls");
		}
		if(CheckGame(name, n))
				break;
		
	 	//毒
		 if(poison){
		 	while(true){
		 		cout<<"Do you want to poison someone? Enter the number or 0 for NO"<<endl;
			 	cin>>decision;
			 	if(CheckChar(name[decision-1],'W'))
					continue;
			 	if(decision!=0){
			 		name[decision-1]=' ';
					poison = false;	
				 }
				system("cls"); 
				break;
			 }
		 } 
	 	
		if(CheckGame(name, n))
			break;

		//預言家 
		while(true){
			cout<<"Who do you want to check?"<<endl;
		 	cin>>decision;
		 	if(CheckChar(name[decision-1],'P'))
		 		continue;
		 	if(name[decision-1]=='F')
		 		cout<<"BAD"<<endl;
		 	else
		 		cout<<"GOOD"<<endl;
		 	system("pause");
			system("cls");
			break;
		}
	 	
	 	
	 	//玩家狀態 
	 	for(i = 0; i < n; ++i)
	 		if(name[i] == ' ')
	 			cout<<"NO. "<<i+1<<" is dead."<<endl;
	 		else
	 			cout<<"NO. "<<i+1<<" survived."<<endl;
	 	
	 	if(CheckGame(name, n))
			break;
			
		//投票 
	 	cout<<"Please discuss one by one."<<endl;
	 	cout<<"Who do you want to vote? Enter the number or 100 for NO"<<endl;
	 	cin>>decision;
	 	system("cls");
	 	if(decision!=100)
	 		name[decision-1]=' '; 
	 		for(i = 0; i < n; ++i)
	 		if(name[i] == ' ')
	 			cout<<"NO."<<i+1<<" was dead."<<endl;
	 		else
	 			cout<<"NO."<<i+1<<" survived."<<endl;
		if(CheckGame(name, n))
			break;
	}
 	
 		

 		
 
}
bool CheckWolf(char a[], int n){
	int i;
	for(i=0;i<n;i++){
		if(a[i]=='F')
			return false;
	}
	return true;
}
bool CheckHuman(char a[], int n){
	int i;
	for(i=0;i<n;i++){
		if(a[i]=='M')
			return false;
	}
	return true;
}
bool CheckOther(char a[], int n){
	int i;
	for(i=0;i<n;i++){
		if(a[i]=='R'||a[i]=='W'||a[i]=='P'||a[i]=='H')
			return false;
	}
	return true;
}
bool CheckGame(char name[], int n){
	if(CheckWolf(name, n)){
		cout<<"Human Win"<<endl;
		return true;
	}
	if(CheckHuman(name, n) || CheckOther(name, n)){
		cout<<"Wolf Win"<<endl;
		return true;
	}
	return false;
} 
void PrintChar(char a[], int n){
	int i;
	for(i=1; i<=n; i++){
 		//cin>>order;
 		cout<<"NO. "<<i<<"  "<<a[i-1]<<" ";
 		switch(a[i-1]){
 			case 'F':
 				cout<<"狼人";
 				break;
 			case 'M':
 				cout<<"平民";
 				break;
 			case 'W':
 				cout<<"女巫";
 				break;
 			case 'P':
 				cout<<"預言家";
 				break;
 			case 'H':
 				cout<<"獵人";
 				break;
 			case 'R':
 				cout<<"騎士";
 				break;
		 }
		 cout<<endl;
 		//cout<<"F=狼人,M=平民,W=女巫,P=預言家,H=獵人,R=騎士"<<endl;
 		system("pause");
 		system("cls");
 	}
}
bool CheckChar(char a, char b){
	if(a==b)
		return true;
	else
		return false;
}
