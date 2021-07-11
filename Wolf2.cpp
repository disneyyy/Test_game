#include <iostream>
#include <stdlib.h>
#include <time.h>


using namespace std;
bool CheckGame(char [], int);
bool CheckGame2(char [], int);
bool CheckWolf(char [], int);
bool CheckHuman(char [], int);
bool CheckOther(char [], int);

bool isWolf(char);
bool isWitch(char);
bool isHunter(char);
bool isProphet(char);
bool isKnight(char);
bool isDead(char);

void PrintChar(char [], int);
void PrintLive(char [], int);
bool CheckLive(char [], char , int);
int HunterKill(char [], int);
void KnightKill(char [], int);
int main(){
	int n;
	int i, player[n], temp, pos;
	char name[10];
	int decision, decision2;
	int pSee;
	bool revive = true;
	bool poison = true;
	bool Knight = true;
	bool usePoison = true;
	
	cout<<"輸入遊玩人數（至少6人至多10人）：\n";
	cin>>n;
 	srand(time(NULL) );

 	player[0] = n;
 	for(i = 1; i < n; ++i)
  		player[i] = i;
  		
 	for(i = 0; i < n; ++i){//座位洗牌
 		pos=rand()%n;
 		temp=player[i];
 		player[i]=player[pos];
 		player[pos]=temp; 		
 	}
 	for(i = 0; i < n; ++i)//分配職業 
	 	switch(player[i]){
	 		case 1:
	 		case 4:
	 		case 8:
	 			name[i]='F';//狼 
	 			break;
	 		case 2:
	 		case 6:
	 		case 9:
	 			name[i]='M';//平民
				break;
			case 5:
				name[i]='W';//女巫 
				break;
			case 3:
				name[i]='P';//預言家 
				break;
			case 7:
				name[i]='H';//獵人 
				break;
			case 10:
				name[i]='K';//騎士 
				break; 
		}
 	PrintChar(name, n);

 	while(true){
 		cout<<"天黑請閉眼"<<endl;
 		system("pause");
 		system("cls");
 		//狼人 殺掉的人要讓預言家這輪還能測 
	 	while(true){
	 		cout<<"狼人請睜眼\n請問要殺哪位玩家？輸入該玩家號碼："<<endl;
			cin>>decision;
			if(isWolf(name[decision-1])||isDead(name[decision-1]))
				continue;
			cout<<"玩家"<<decision<<"遭到殺害"<<endl;
			system("pause");
			system("cls");
			break;
		}
		if(CheckGame2(name, n))
			return 0;
		//女巫 
		usePoison = true;
		decision2 = 0;
		//救 
		if(CheckLive(name, 'W', n)){
			//int decision2;
			if(revive){
				//int decision2;
				cout<<"女巫請睜眼\n玩家"<<decision<<"被殺了，請問你要救他嗎？是 1，否 0："<<endl;
				cin>>decision2;
				if(decision2==0){
					if(isHunter(name[decision-1])){ //獵人死亡 
						decision2=HunterKill(name, n);
						if(decision2!=0)
							name[decision2-1]=' ';
					}
					name[decision-1]=' ';
				}else{
					if(isWitch(name[decision-1])){ //女巫無法自救 
						name[decision-1]=' ';//
						poison = false;
						//revive = false;
					}
				 	revive = false;
				 	usePoison = false;
				}
				decision2 = 0;
			}else{//已經復活過人 
				if(isHunter(name[decision-1])){
					name[decision-1]=' ';
				if(CheckGame(name, n))
					return 0;
				decision2=HunterKill(name, n);
				if(decision2!=0)
					name[decision2-1]=' ';
				}
				name[decision-1]=' ';//
			}
		}else{//女巫已經死亡 
			//int decision2;
			if(isHunter(name[decision-1])){//獵人死亡 
				name[decision-1]=' ';
				if(CheckGame(name, n))
					return 0;
				decision2=HunterKill(name, n);
				if(decision2!=0)
					name[decision2-1]=' ';
			}
			name[decision-1]=' ';//
		}
		
		system("cls");
		
		//毒 獵人若在此時死亡則不能發動技能 
		while(poison && CheckLive(name, 'W', n) && usePoison){
			if(!revive)
				cout<<"女巫請睜眼\n";
	 		cout<<"請問您要對誰下毒？輸入該玩家號碼或輸入0不執行："<<endl;
		 	cin>>decision2;
		 	if(decision2!=0){
		 		if(isWitch(name[decision2-1])||isDead(name[decision2-1]))
		 			continue;
		 		//name[decision-1]='#';
				poison = false;	
			}
			system("cls"); 
			break;
		}
		
		if(CheckGame(name, n))
			return 0;
	 	

		//預言家 
		while(CheckLive(name, 'P', n)){
			cout<<"預言家請睜眼\n請問你要檢查誰的身分？輸入該玩家號碼："<<endl;
		 	cin>>pSee;
		 	if(isProphet(name[pSee-1])||isDead(name[pSee-1]))
		 		continue;
		 	if(isWolf(name[pSee-1]))
		 		cout<<"BAD"<<endl;
		 	else
		 		cout<<"GOOD"<<endl;
		 	system("pause");
			system("cls");
			break;
		}
		//name[decision-1]=' ';
	 	if(decision2!=0)
	 		name[decision2-1]=' ';
	 	
	 	if(CheckGame(name, n))
			return 0;
	 	//玩家狀態 
	 	PrintLive(name, n);

		//投票 
	 	//cout<<"請討論"<<endl;
	 	system("pause");
	 	system("cls");
	 	cout<<"天亮了\n請輸入大家票選的狼人，若要跳過則輸入-1";
	 	if(CheckLive(name, 'K', n)&&Knight)
			cout<<"，若騎士要發動技能請輸入0";
		cout<<"："<<endl;
	 	cin>>decision;
	 	system("cls");
	 	if(decision==0 && Knight && CheckLive(name, 'K', n)){
	 		KnightKill(name, n);//騎士
	 		Knight = false; 
			if(CheckGame(name, n))
				return 0;
			cout<<"請繼續票選狼人，若要跳過則輸入-1"<<endl;
			cin>>decision;
			system("cls");
		}
	 	if(decision==-1)
			;
		else{
			if(isHunter(name[decision-1])){
				int decision2;
				name[decision-1]=' ';
				if(CheckGame(name, n))
					return 0;
				decision2=HunterKill(name, n);
				if(decision2!=0)
					name[decision2-1]=' ';
				if(CheckGame(name, n))
					return 0;
			}
			name[decision-1]=' ';
		}
		if(CheckGame(name, n))
			return 0;
		//玩家狀態 
	 	PrintLive(name, n);
	 	system("pause");
	 	system("cls");
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
		if(a[i]=='K'||a[i]=='W'||a[i]=='P'||a[i]=='H')
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
bool CheckGame2(char name[], int n){
	int i = 0;
	for(i=0; i<n; i++){
		if(name[i]=='K'||name[i]=='P'||name[i]=='H'){
			return false;
		}
	}
	cout<<"Wolf Win"<<endl;
	return true;
}
void PrintChar(char a[], int n){
	int i;
	for(i=1; i<=n; i++){
 		//cin>>order;
 		cout<<"玩家"<<i<<"  "<<a[i-1]<<" ";
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
 			case 'K':
 				cout<<"騎士";
 				break;
		 }
		 cout<<endl;
 		//cout<<"F=狼人,M=平民,W=女巫,P=預言家,H=獵人,R=騎士"<<endl;
 		system("pause");
 		system("cls");
 	}
}
void PrintLive(char a[], int n){
	int i;
	for(i = 0; i < n; ++i)
 		if(a[i] == ' ')
 			cout<<"玩家"<<i+1<<" X"<<endl;
 		else
 			cout<<"玩家"<<i+1<<" O"<<endl;
}
bool CheckLive(char a[], char b, int n){
	int i;
	for(i=0;i<n;i++){
		if(a[i]==b)
			return true;
	}
	return false;
}
bool isWolf(char a){
	return a=='F';
}
bool isWitch(char a){
	return a=='W';
}
bool isHunter(char a){
	return a=='H';
}
bool isProphet(char a){
	return a=='P';
}
bool isKnight(char a){
	return a=='K';
}
bool isDead(char a){
	return a==' ';
}
int HunterKill(char a[], int n){
	int b;
	while(true){
		cout<<"獵人技能發動！請輸入要對誰開槍，若放棄則輸入0："<<endl;
		cin>>b;
		if(isHunter(a[b-1])||isDead(a[b-1]))
			continue;
		else
			break;
	}
	system("cls");
	return b;
}
void KnightKill(char name[], int n){
	int decision, i;
	while(true){
		cout<<"請選擇決鬥對象："<<endl;
		cin>>decision;
		if(isWolf(name[decision-1])){
			cout<<"Success"<<endl;
			name[decision-1]=' ';
			break;
		}else if(isKnight(name[decision-1])||isDead(name[decision-1]))
			continue;
		else{
			cout<<"Failed"<<endl;
			for(i=0; i<n; i++){
				if(isKnight(name[i]))
					name[i]=' ';
			}
			break;
		}
	}
}
