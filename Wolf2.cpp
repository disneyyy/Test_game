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
	
	cout<<"��J�C���H�ơ]�ܤ�6�H�ܦh10�H�^�G\n";
	cin>>n;
 	srand(time(NULL) );

 	player[0] = n;
 	for(i = 1; i < n; ++i)
  		player[i] = i;
  		
 	for(i = 0; i < n; ++i){//�y��~�P
 		pos=rand()%n;
 		temp=player[i];
 		player[i]=player[pos];
 		player[pos]=temp; 		
 	}
 	for(i = 0; i < n; ++i)//���t¾�~ 
	 	switch(player[i]){
	 		case 1:
	 		case 4:
	 		case 8:
	 			name[i]='F';//�T 
	 			break;
	 		case 2:
	 		case 6:
	 		case 9:
	 			name[i]='M';//����
				break;
			case 5:
				name[i]='W';//�k�� 
				break;
			case 3:
				name[i]='P';//�w���a 
				break;
			case 7:
				name[i]='H';//�y�H 
				break;
			case 10:
				name[i]='K';//�M�h 
				break; 
		}
 	PrintChar(name, n);

 	while(true){
 		cout<<"�Ѷ½г���"<<endl;
 		system("pause");
 		system("cls");
 		//�T�H �������H�n���w���a�o���ٯ�� 
	 	while(true){
	 		cout<<"�T�H�иC��\n�аݭn�����쪱�a�H��J�Ӫ��a���X�G"<<endl;
			cin>>decision;
			if(isWolf(name[decision-1])||isDead(name[decision-1]))
				continue;
			cout<<"���a"<<decision<<"�D����`"<<endl;
			system("pause");
			system("cls");
			break;
		}
		if(CheckGame2(name, n))
			return 0;
		//�k�� 
		usePoison = true;
		decision2 = 0;
		//�� 
		if(CheckLive(name, 'W', n)){
			//int decision2;
			if(revive){
				//int decision2;
				cout<<"�k�ŽиC��\n���a"<<decision<<"�Q���F�A�аݧA�n�ϥL�ܡH�O 1�A�_ 0�G"<<endl;
				cin>>decision2;
				if(decision2==0){
					if(isHunter(name[decision-1])){ //�y�H���` 
						decision2=HunterKill(name, n);
						if(decision2!=0)
							name[decision2-1]=' ';
					}
					name[decision-1]=' ';
				}else{
					if(isWitch(name[decision-1])){ //�k�ŵL�k�۱� 
						name[decision-1]=' ';//
						poison = false;
						//revive = false;
					}
				 	revive = false;
				 	usePoison = false;
				}
				decision2 = 0;
			}else{//�w�g�_���L�H 
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
		}else{//�k�Ťw�g���` 
			//int decision2;
			if(isHunter(name[decision-1])){//�y�H���` 
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
		
		//�r �y�H�Y�b���ɦ��`�h����o�ʧޯ� 
		while(poison && CheckLive(name, 'W', n) && usePoison){
			if(!revive)
				cout<<"�k�ŽиC��\n";
	 		cout<<"�аݱz�n��֤U�r�H��J�Ӫ��a���X�ο�J0������G"<<endl;
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
	 	

		//�w���a 
		while(CheckLive(name, 'P', n)){
			cout<<"�w���a�иC��\n�аݧA�n�ˬd�֪������H��J�Ӫ��a���X�G"<<endl;
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
	 	//���a���A 
	 	PrintLive(name, n);

		//�벼 
	 	//cout<<"�аQ��"<<endl;
	 	system("pause");
	 	system("cls");
	 	cout<<"�ѫG�F\n�п�J�j�a���諸�T�H�A�Y�n���L�h��J-1";
	 	if(CheckLive(name, 'K', n)&&Knight)
			cout<<"�A�Y�M�h�n�o�ʧޯ�п�J0";
		cout<<"�G"<<endl;
	 	cin>>decision;
	 	system("cls");
	 	if(decision==0 && Knight && CheckLive(name, 'K', n)){
	 		KnightKill(name, n);//�M�h
	 		Knight = false; 
			if(CheckGame(name, n))
				return 0;
			cout<<"���~�򲼿�T�H�A�Y�n���L�h��J-1"<<endl;
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
		//���a���A 
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
 		cout<<"���a"<<i<<"  "<<a[i-1]<<" ";
 		switch(a[i-1]){
 			case 'F':
 				cout<<"�T�H";
 				break;
 			case 'M':
 				cout<<"����";
 				break;
 			case 'W':
 				cout<<"�k��";
 				break;
 			case 'P':
 				cout<<"�w���a";
 				break;
 			case 'H':
 				cout<<"�y�H";
 				break;
 			case 'K':
 				cout<<"�M�h";
 				break;
		 }
		 cout<<endl;
 		//cout<<"F=�T�H,M=����,W=�k��,P=�w���a,H=�y�H,R=�M�h"<<endl;
 		system("pause");
 		system("cls");
 	}
}
void PrintLive(char a[], int n){
	int i;
	for(i = 0; i < n; ++i)
 		if(a[i] == ' ')
 			cout<<"���a"<<i+1<<" X"<<endl;
 		else
 			cout<<"���a"<<i+1<<" O"<<endl;
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
		cout<<"�y�H�ޯ�o�ʡI�п�J�n��ֶ}�j�A�Y���h��J0�G"<<endl;
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
		cout<<"�п�ܨM����H�G"<<endl;
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
