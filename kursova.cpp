#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <stdlib.h>
#include <sstream>
#include <iomanip>
#include <string>
#include <time.h>
#define size1 13   //обмеження к-сті гравців
#define size2 7    //обмеження к-сті клубів
using namespace std;

const char* lin_e1 = "_________________________________________________________________________________________________________";
const char* line1 = "---------------------------------------------------------------------------------------------------------";
const char* lin_e = "_________________________________________________________________________________________________________________________________________________________________";
const char* line = "-----------------------------------------------------------------------------------------------------------------------------------------------------------------";
const char* header="          Name          |      Nationality      |             Club              |      Age      |    Position   |  Weight (kg)  |  Height (sm)  |  Price (mill) |";
const char* headercl="        Name            |         City          |   Conference  |        Division       | Budget (mill) |";
const char* hedtr="      Name      |         From    ->       To           |  Price(mill)  |              Date              |";

class Club
{
public:
	void Show_Club();
private:
	string club_conference;
	string club_division;
	string club_city;
	
	void Add_Club();
protected:
	string club_name;
	string club_budget;
	
	friend class Function;
	friend class Admin;
};

class Player : public Club
{
private:
	string name;
	string name1;
	string nationality;
	string position;
	string age;
	string weight;
	string height;
	
protected:
	string price;
	void Set_Data();
	void Delete_Player();
	void Edit_Player();
public:
	void Search_Player(Player player[], string Player::*where, string what, int variant);
	void Get_Data();
	
	friend class Function;
	friend class Admin;
	
};

class Function
{
public:
	void Search_Data();
	void Sort_Data();
	void Transfer();
	void view_transfer();
	
private:
	void Delete_All_Data_Player();
	void Delete_All_Data_Club();
	
	friend class Admin;
};

class User 
{
private:
public:
	void User_Menu();
	
	friend class Admin;
};

class Admin
{	
private:
 const string password="1488";
protected:
	void Menu();
public:
	void Authorization();
	
};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ôóíêö³ÿ âèäàëåííÿ ãðà
void Player::Delete_Player()
{
	Player player[size1];
	Player::Get_Data();
	int i,  tmp;
	string who, who1;
	
	
	ifstream file1("basket.txt", ios_base::in);																				// ç÷èòóâàííÿ
	while (!file1.eof())																									//äàíèõ ãðàâö³â  
	{																														//
		file1 >> player[i].name >> player[i].name1 >> player[i].nationality>> player[i].club_name >>player[i].age;			//
		file1 >> player[i].position >> player[i].weight >> player[i].height >> player[i].price;								//³ç ôàéëó
		i++;																												//
	}																														//
	file1.close();

	
	M1:	cout<<"\nEnter name of player or press [1] [space] [1] to exit: "<<endl; cin>>who; cin>>who1;
	if(who=="1") {return;}
	int max=0, k=0, MAX;
	max=i-1;
	MAX=i-1;
	for(i=0;i<=max;i++)
	{
		if((who==player[i].name)&&(who1==player[i].name1)) { tmp=i; break;}      // ïîøóê ãðàâöÿ ÿêîãî ïîòð³áíî âèäàëèòè
		if((who!=player[i].name)&&(who1!=player[i].name1))
		{
		k++;
		}
	}
	if((k-1)==max){cout<<"\nThis player is not exist! Please try again!\n"; goto M1;}
	
	ofstream txt("basket.txt", ios::trunc);
	txt.close();
	ofstream fil("basket.txt", ios::app);
	for (i = 0; i<=MAX; ++i)
	{
		
		if(tmp==i)
		{
			cout<<"\nDeleted!\n"; break;                                                   // çàïèñ äàíèõ ó ôàéë áåç "âèäàëåíîãî" ãðàâöÿ
		}
		else
		{
		fil << "\n"  << player[i].name << "\t" << player[i].name1 << "\t" << player[i].nationality;
		fil<<"\t" << player[i].club_name  <<"\t" << player[i].age << "\t" << player[i].position << "\t" << player[i].weight;
		fil << "\t" << player[i].height  << "\t" << player[i].price;
		}
	}
	fil.close();	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ðåäàãóâàííÿ ãðàâöÿ
void Player::Edit_Player()
{
	Player player[size1];
	Player::Get_Data();
	int i,  tmp;
	string who, who1;
	
	//ç÷èòóâàííÿ äàíèõ ³ç ôàéëó
	ifstream file1("basket.txt", ios_base::in);
	while (!file1.eof())
	{
		file1 >> player[i].name >> player[i].name1 >> player[i].nationality>> player[i].club_name >>player[i].age;
		file1 >> player[i].position >> player[i].weight >> player[i].height >> player[i].price;
		i++;
	}
	file1.close();
	
	
	//ïîøóê ãðàâöÿ â ÿêîãî òðåáà çì³íèòè äàí³
	M1:	cout<<"\nEnter name of player or press [1] [space] [1] to exit: "<<endl; cin>>who; cin>>who1;
	if(who=="1") {return;}
	int max=0, k=0, MAX;
	max=i-1;
	MAX=i-1;
	for(i=0;i<=max;i++)
	{
		if((who==player[i].name)&&(who1==player[i].name1)) { tmp=i; break;}                 
		if((who!=player[i].name)&&(who1!=player[i].name1))
		{
		k++;
		}
	}
	if((k-1)==max){cout<<"\nThis player is not exist! Please try again!\n"; goto M1;}
	
	// âèá³ð ³ ðåäàãóâàííÿ íåîáõ³äíîãî ïîëÿ
	cout<<"\nWhat field you want change?\n";
	cout<<"[1] Name;  [2] Surname;  [3] Nationality;  [4] Club;  [5] Age;  [6] Position;  [7] Weight;  [8] Height;  [9] Price;  [10] Exit\n ";
	int c;	cin>>c;
	switch(c)
	{
		case 1: { cout<<"Enter new name: "; cin>>player[tmp].name; break;}
		case 2: { cout<<"Enter new surname: "; cin>>player[tmp].name1; break;}
		case 3: { cout<<"Enter new nationality: "; cin>>player[tmp].nationality; break;}
		case 4: { cout<<"Enter new club: "; cin>>player[tmp].club_name; break;}
		case 5: { cout<<"Enter new age: "; cin>>player[tmp].age; break;}
		case 6: {  
M5:				  cout << "Enter new position: [1] Point guard (PG);  [2] Shooting guard (SG);  [3] Small forwrd (SF);";
				  cout<<"  [4] Power forward (PF);  [5] Center (C);\n"; int w;
				  cin>>w;
				  if((w<1)||(w>5)||(!cin))  { cin.clear(); cin.get(); system("cls"); cout << "   You entered incorect number!\n" << endl; goto M5; } 
				  switch(w)
				{
					case 1: player[tmp].position="PG"; break;
					case 2: player[tmp].position="SG"; break;
					case 3: player[tmp].position="SF"; break;
					case 4: player[tmp].position="PF"; break;
					case 5: player[tmp].position="C"; break;
				}
				break;}
		case 7: { cout<<"Enter new weight: "; cin>>player[tmp].weight; break;}
		case 8: { cout<<"Enter new height: "; cin>>player[tmp].height; break;}
		case 9: { cout<<"Enter new price: "; cin>>player[tmp].price; break;}
		case 10: {break;}
	}
	
	
	//çàïèñ îíîâëåíèõ äàíèõ ó ôàéë
	ofstream txt("basket.txt", ios::trunc);
	txt.close();
	ofstream fil("basket.txt", ios::app);
	for (i = 0; i<=MAX; ++i)
	{
		
		if(tmp==i)
		{
		fil << "\n"  << player[tmp].name << "\t" << player[tmp].name1 << "\t" << player[tmp].nationality;
		fil<<"\t" << player[tmp].club_name  <<"\t" << player[tmp].age << "\t" << player[tmp].position << "\t" << player[tmp].weight;
		fil << "\t" << player[tmp].height  << "\t" << player[tmp].price;
		}
		else
		{
		fil << "\n"  << player[i].name << "\t" << player[i].name1 << "\t" << player[i].nationality;
		fil<<"\t" << player[i].club_name  <<"\t" << player[i].age << "\t" << player[i].position << "\t" << player[i].weight;
		fil << "\t" << player[i].height  << "\t" << player[i].price;
		}
	}
	fil.close();
	cout<<"\nDone!\n";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ôóíêö³ÿ ùî ïîêóçàº âèêîíàí³  òðàíñôåðè
void Function::view_transfer()
{
	string who, who1, from, where, price, when_day, when_month, when_date, when_hour, when_year ;
	ifstream file("transfer.txt", ios_base::in);
	
	//ç÷èòóâàííÿ ³ âèâåäåííÿ íà åêðàí äàíèõ ³ç ôàéëó
	cout<<'\n'<<lin_e1<<'\n'<<hedtr<<'\n'<<lin_e1<<'\n';
	while(!file.eof())
	{
		file>>who>>who1>>from>>where>>price>>when_day>>when_month>>when_date>>when_hour>>when_year;
		
		if(file.eof()) break;
		
		
		cout<<who<<" "<<who1<<'\t'<<'|'<<'\t'<<from<<" -> "<<where<<'\t'<<'|'<<'\t'<<price<<'\t'<<'|'<<"\t"<<when_day<<' '<<when_month;
		cout<<' '<<when_date<<" "<<when_hour<<' '<<when_year<<" |"<<'\n';
		cout<<line1<<endl;
	}
	file.close();
}
 	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//ôóíêö³ÿ ùî âèêîíóº òðàíñôåð
void Function::Transfer()
{
	Player player[size1];
	Player function;
	Club club[size2];
	int i=0, j=0, tmp_player, tmp_club, MAX=0, MAX1=0, sum, sum1, SUM, SUM1, TMP; 
	string who, who1,  where, from;
	
	function.Get_Data();  //âèâåäåííÿ âñ³õ ãðàâö³â íà åêðàí
	
	//ç÷èòóâàííÿ äàíèõ ³ç ôàéëó
	ifstream file1("basket.txt", ios_base::in);
	while (!file1.eof())
	{
		file1 >> player[i].name >> player[i].name1 >> player[i].nationality>> player[i].club_name >>player[i].age;
		file1 >> player[i].position >> player[i].weight >> player[i].height >> player[i].price;
		i++;
	}
	file1.close();
	
	//ââåäåííÿ ³ìåí³ ãðàâöÿ 
M1:	cout<<"\nEnter name of player or press [1] [space] [1] to exit: "<<endl; cin>>who; cin>>who1;
	if(who=="1") {return;}
	int max=0, k=0;
	max=i-1;
	MAX=i-1;
	for(i=0;i<=max;i++)
	{
		if((who==player[i].name)&&(who1==player[i].name1)) { tmp_player=i; break;}  //ïîøóê ãðàâöÿ
		if((who!=player[i].name)&&(who1!=player[i].name1))
		{
		k++;
		}
	}
	if((k-1)==max){cout<<"\nThis player is not exist! Please try again!\n"; goto M1;}
	
	//ç÷èòóâàííÿ ³ç ôàéëó äàíèõ ïðî êëóáè
	ifstream file2("basclub.txt", ios_base::in);
		while(!file2.eof())
	{
		file2>>club[j].club_name>>club[j].club_city>>club[j].club_conference>>club[j].club_division>>club[j].club_budget;
		j++;
	}
	file2.close();	

	//ïîøóê ïåâíîãî êëóáó
M2:	cout<<"\nEnter name of club or press [1] to exit: "<<endl; cin>>where;
	if(where=="1") {return;}
	max=0, k=0;
	max=j-1;
	MAX1=j;
	for(j=0;j<=max;j++)
	{
		if(where==club[j].club_name) { tmp_club=j; break;}
		if(where!=club[j].club_name)
		{
		k++;
		}
	}
	if((k-1)==max){cout<<"\nThis club is not exist! Please try again!\n"; goto M2;}	
	
	//ïåðåâ³ðêà ÷è ãðàâåöü âæå çíàõîäèòüñÿ â öüîìó êëóá³
	if(where==player[tmp_player].club_name){cout<<"\nPlayer is in this club in this moment! Please enter another club!\n"; goto M2;}
	
	//ïåðåâ³ðêà ÷è â êëóáó äîñòàòíüî êîøò³â äëÿ çä³éñíåííÿ òðàíñôåð³â 
	if(club[tmp_club].club_budget<player[tmp_player].price) {cout<<"\nClub have not enough money!\n"; goto M1;}
	
	
	//ïåðåòâîðåííÿ string y int
	sum=atoi(club[tmp_club].club_budget.c_str());
	sum1=atoi(player[tmp_player].price.c_str());
	
	sum-=sum1; //â³äí³ìàííÿ êîøò³â ç ðàõóíêó êëóáó êóäè ïåðåõîäèòü ãðàâåöü
	
	for(j=0;j<=max;j++)
	{
		if(club[j].club_name==player[tmp_player].club_name)
		{
			SUM=atoi(club[j].club_budget.c_str());
			SUM1=atoi(player[tmp_player].price.c_str());
			SUM+=SUM1;          //äîäàâàííÿ êîøò³â äî áþäæåòó êëóáó çâ³äêè ïåðåõîäèòü ãðàâåöü
			TMP=j;
		}
	}
	
	from=player[tmp_player].club_name;
	player[tmp_player].club_name=club[tmp_club].club_name;   //çì³íà êëóáó
	
	
	//çàïèñ äàíèõ ó ôàéë
	ofstream txt("basket.txt", ios::trunc);
	txt.close();
	ofstream fil("basket.txt", ios::app);
	for (i = 0; i<=MAX; ++i)
	{
		
		if(tmp_player==i)
		{
		fil << "\n"  << player[i].name << "\t" << player[i].name1 << "\t" << player[i].nationality;
		fil<<"\t" << player[tmp_player].club_name  <<"\t" << player[i].age << "\t" << player[i].position << "\t" << player[i].weight;
		fil << "\t" << player[i].height  << "\t" << player[i].price;
		}
		else
		{
		fil << "\n"  << player[i].name << "\t" << player[i].name1 << "\t" << player[i].nationality;
		fil<<"\t" << player[i].club_name  <<"\t" << player[i].age << "\t" << player[i].position << "\t" << player[i].weight;
		fil << "\t" << player[i].height  << "\t" << player[i].price;
		}
	}
	fil.close();
	
	//çàïèñ äàíèõ ó ôàéë
	ofstream basket("basclub.txt", ios::trunc);
	basket.close();
	ofstream bask("basclub.txt", ios::app);
	for(j=0; j<MAX1; j++)
	{
		if(tmp_club==j)
		{
		bask<< "\n"<<club[j].club_name<<"\t"<<club[j].club_city<<"\t"<<club[j].club_conference;
		bask<<"\t"<<club[j].club_division<<"\t"<<sum;			
		}
		else if(TMP==j)
		{
		bask<< "\n"<<club[j].club_name<<"\t"<<club[j].club_city<<"\t"<<club[j].club_conference;
		bask<<"\t"<<club[j].club_division<<"\t"<<SUM;
		}
		else 
		{
		bask<< "\n"<<club[j].club_name<<"\t"<<club[j].club_city<<"\t"<<club[j].club_conference;
		bask<<"\t"<<club[j].club_division<<"\t"<<club[j].club_budget;
		}
	}
	bask.close();
	
	//âèçíà÷åííÿ äàòè ³ ÷àñó
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	string time= asctime(timeinfo);
	
	//çàïèñ äàíèõ ïðî òðàíñôåð
	ofstream transf("transfer.txt", ios::app);
	for(i=0;i<1;i++)
	{
		transf<<"\n"<<who<<"\t"<<who1<<"\t"<< from <<"\t"<<where<<"\t"<<player[tmp_player].price<<"\t"<<time;
	}
	transf.close();
	
	
	system("cls");
	cout<<"\nTransfer succesful!\n";
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ìåíþ êîðèñòóâà÷à
void User::User_Menu()
{
	Player player;
	Function function;
	Club club;
	Admin admin;
	int z;
	system("cls");

M1:	cout << "\n\t\t\t\t\t\tUSER\n\n\n   Press [1] to view players; \n   Press [2] to search players;  \n   Press [3] to view transfer;\n  ";
	cout<< " Press [4] to view clubs;\n   Press [5] to transfer;\n   Press [6] to exit to main menu;\n   Press [7] to exit;" << endl;
	cin >> z;
	cout << "\n";

	if ((z>7)||(z<1)||(!cin)) { cin.clear(); cin.get(); system("cls"); cout << "   You entered incorect number!\n" << endl; goto M1; } //ïåðåâ³ðêà íà êîðåêòí³ñòü âèáîðó
	switch (z)
	{
	case 1: player.Get_Data(); goto M1; break;
	case 2: function.Search_Data(); goto M1; break;
	case 3: function.view_transfer(); goto M1; break;
	case 4: club.Show_Club(); goto M1; break;
	case 5: function.Transfer(); goto M1; break;
	case 6: admin.Authorization(); goto M1; break;
	case 7: cout << "BYE"; exit(EXIT_SUCCESS); break;
	}
	return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ìåíþ àäì³íà
void Admin::Menu()
{
	Player player;
	Club club;
	Function function;
	int z;
	system("cls");

M1:	cout << "\n\t\t\t\t\t\tADMIN\n\n\n   Press [1] to add player; \n   Press [2] to view players; \n   Press [3] to search players;\n   Press [4] to edit players;";
	cout<<" \n   Press [5] to delete player; \n   Press [6] to delete data from file (player);\n   Press [7] to delete data from file (club);";
	cout<<" \n   Press [8] to add club;\n   Press [9] to view clubs;\n   Press [10] to exit to main menu;\n   Press [11] to exit;\n   ";
	cin >> z;
	cout << "\n";

	if ((z>11)||(z<1)||(!cin)) { cin.clear(); cin.get(); system("cls"); cout << "   You entered incorect number!\n" << endl; goto M1; }
	switch (z)
	{
	case 1: player.Set_Data(); goto M1; break;
	case 2: player.Get_Data(); goto M1; break;
	case 3: function.Search_Data(); goto M1; break;
	case 4: player.Edit_Player(); goto M1; break;
	case 5: player.Delete_Player(); goto M1; break;
	case 6: function.Delete_All_Data_Player();  goto M1; break;
	case 7: function.Delete_All_Data_Club();  goto M1; break;
	case 8: club.Add_Club(); goto M1; break;
	case 9: club.Show_Club();  goto M1; break;
	case 10: Admin::Authorization();  goto M1; break;
	case 11: cout << "BYE"; exit(EXIT_SUCCESS); break;
	}
	return ;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ìåíþ àâòîðèçàö³¿
void Admin::Authorization()
{
	User user;
	int choice;
	string pass;
	system("cls");
	
	
M1:	cout<<"\n   If you are Admin press [1];\n   If you are User press [2];\n\n   If you want to exit press [3];\n   ";
	cin>>choice;
	if((choice>3)||(choice<1)||(!cin)){cin.clear(); cin.get(); system("cls"); cout << "You entered incorect number!\n" << endl; goto M1;}
	if(choice==1)
	{
		cout<<"   Please enter the password: "; cin>>pass; //ïåðåâ³ðêà ïàðîëþ
		if(pass==Admin::password)
		{
			Admin::Menu();
		}
		else { cout<<"   Wrong password! Try again!\n\n"; goto M1;}
	}
	else if(choice == 2 )
	{
		user.User_Menu();
	}
	else if(choice==3)
	{
	  cout<<"   BYE!";	exit(EXIT_SUCCESS);
	}
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//äîäàâàííÿ íîâãî ãðàâöÿ
void Player::Set_Data()
{
	system("cls");
	
	Player player[size1];

	int i, MAX = 1, k;

//äîäàâàííÿ äàíèõ
	for (i = 0; i < MAX; i++)
	{
		cout << '\n' << "New player:" << '\n' << endl;
		cout << "Enter player name:" << endl;
		cin >> player[i].name;
		cin >> player[i].name1;
		cout << "Enter nationality of player:" << endl;
		cin >> player[i].nationality;
		cout<<"Enter player's club:"<<endl;
		cin>>player[i].club_name;
		cout << "Enter player's age:" << endl;
		cin >> player[i].age;
M1:		cout << "Enter player's position: [1] Point guard (PG);  [2] Shooting guard (SG);  [3] Small forwrd (SF);";
		cout<<"  [4] Power forward (PF);  [5] Center (C);\n";
		cin>>k;
		if((k<1)||(k>5)||(!cin))  { cin.clear(); cin.get(); system("cls"); cout << "   You entered incorect number!\n" << endl; goto M1; } 
		switch(k)
		{
			case 1: player[i].position="PG"; break;
			case 2: player[i].position="SG"; break;
			case 3: player[i].position="SF"; break;
			case 4: player[i].position="PF"; break;
			case 5: player[i].position="C"; break;
		}
		
		cout << "Enter player's weight:" << endl;
		cin >> player[i].weight;
		cout << "Enter player's height:" << endl;
		cin >> player[i].height;
		cout << "Enter player's price (millions):" << endl;
		cin >> player[i].price;
		cout << '\n' << '\n' << endl;
	}
	
	//çàïèñ äàíèõ ó ôàéë
	ofstream file1("basket.txt", ios::ate | ios::app);
	for (i = 0; i<MAX; ++i)
	{
		file1 << "\n"  << player[i].name << "\t" << player[i].name1 << "\t" << player[i].nationality;
		file1<<"\t" << player[i].club_name  <<"\t" << player[i].age << "\t" << player[i].position << "\t" << player[i].weight;
		file1 << "\t" << player[i].height  << "\t" << player[i].price;
	}
	file1.close();
	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


//âèâ³ä äàíèõ ïðî ãðàâö³â íà åêðàí
void Player::Get_Data()
{
	Player player[size1];
	system("cls");
	int max, i=0, n=1;
	ifstream file1("basket.txt", ios_base::in);
	cout <<lin_e <<'\n'<<header<<'\n'<<lin_e<<endl;
	while (!file1.eof())
	{

		file1 >> player[i].name >> player[i].name1 >> player[i].nationality>> player[i].club_name >>player[i].age;
		file1 >> player[i].position >> player[i].weight >> player[i].height >> player[i].price;

		cout<<n<<". "<< player[i].name << " " << player[i].name1<<setw(6)<<'\t'<< '|' << '\t' << player[i].nationality <<setw(7)<< '\t' << '|' << '\t';
		cout<< player[i].club_name <<setw(8)<< '\t' << '|' << '\t' << player[i].age << '\t' << '|' << '\t' << player[i].position << '\t' << '|' << '\t';
		cout << player[i].weight << '\t' << '|' << '\t' << player[i].height << '\t' << '|' << '\t';
		cout << player[i].price << '\t' << '|' << '\t' << endl;
		cout << line << endl;
		i++;
		n++;
	}

	file1.close();
	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ìåíþ ïîøóêó
void Function::Search_Data()
{ 
	system("cls");
	Player player[size1];
	Player function;
	string X;
	int z;
M1:	cout<<"Please enter on which value you want to search: \n[1] Name\n[2] Surname\n[3] Nationality\n[4] Club\n[5]";
	cout<<" Age\n[6] Position\n[7] Weight\n[8] Height\n[9] Price\n[10] Exit\n\n";   //ââåäåííÿ çíà÷åííÿ ïî ÿêîìó áóäå ïðîâîäèòèñü ïîøóê
	cin>>z;
	if ((z < 1)||(z > 10)||(!cin)) 
	{ cin.clear(); cin.get(); system("cls"); cout << "You entered incorect number!\n" << endl; goto M1; }
	switch(z)
	{
		case 1: {	cout<<"Enter name: "<<endl;
					cin>>X;
					function.Search_Player(player,&Player::name,X,1); //âèêëèê ôóíêö³¿ ïîøóêó ïåðøèé àðãóìåíò öå âêàçàííÿ ñòðóêòóðè, 
																	//äðóãèé - çà ÿêèì ïàðàìåòðîì ïðîâîäèòüñÿ ïîøóê, òðåò³é - øóêàíå çíà÷åííÿ,  
					break;}											//÷åòâåðòèé: 1 - øóêàíå çíà÷åííÿ áóêâåíå, 2 - öèôåðíå	
		case 2: {	cout<<"Enter surname: "<<endl;
					cin>>X;
					function.Search_Player(player,&Player::name1,X,1);
			break;}
		case 3: {	cout<<"Enter nationality: "<<endl;
					cin>>X;
					function.Search_Player(player,&Player::nationality,X,1);
			break;}
		case 4: {	cout<<"Enter club: "<<endl;
					cin>>X;
					function.Search_Player(player,&Player::club_name,X,1);
			break;}	
		case 5: {	
					function.Search_Player(player,&Player::age,X,2);
			break;}
		case 6: {	cout<<"Enter position: "<<endl;
					cin>>X;
					function.Search_Player(player,&Player::position,X,1);
			break;}
		case 7: {	
					function.Search_Player(player,&Player::weight,X,2);
			break;}
		case 8: {	
					function.Search_Player(player,&Player::height,X,2);
			break;}
		case 9:	{	
					function.Search_Player(player,&Player::price,X,2);
			break;}
		case 10: {return;
			break;}
	}
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ïîøóê
void Player::Search_Player(Player player[], string Player::*where, string what, int variant)
{
	int  i = 0, max, n=1, k=0;
	ifstream file("basket.txt");
	if (!file)
	{
		return;    //ïåððåâ³ðêà ÷è â³äêðèòèé ôàéë
	}
	else
		//ç÷èòóâàííÿ äàíèõ ³ç ôàéëó
		while (!file.eof())
		{
			file >>  player[i].name>>  player[i].name1>>  player[i].nationality >> player[i].club_name >>  player[i].age;
			file >>  player[i].position >>  player[i].weight >>  player[i].height >>   player[i].price;
			i++;
		}
		
		max = i;
	
		switch(variant)
		{
		case 1: {
			cout<<lin_e<<'\n'<<header<<'\n'<<lin_e<<endl;
		for (i = 0; i<max; i++)
			{
		
			if ( (player[i].*where) == what )  // ïîð³âíþâàííÿ ïàðàìåòðà ³ç øóêàíèì çíà÷åííÿì
				{
				cout <<n<<". " << player[i].name<< " " <<  player[i].name1 << setw(6)<<'\t' << '|' << '\t' <<  player[i].nationality <<setw(7)<< '\t' << '|' << '\t';
				cout<<  player[i].club_name << setw(8)<<'\t' << '|' << '\t' <<  player[i].age << '\t' << '|' << '\t' <<   player[i].position << '\t' << '|' << '\t';
				cout <<   player[i].weight << '\t' << '|' << '\t' << player[i].height << '\t' << '|' << '\t' <<  player[i].price << '\t' << '|' << '\t'<<endl;
				cout << line << endl;
				k++;
				n++;
				}

			} 
			if(k==0){ cout<<"\nPlayers not found!"<<endl;}	break;
		}
		case 2: {
			string first_limit, second_limit, tmp;
			cout<<"Enter first limit: "; cin>>first_limit;
			cout<<"Enter second limit: "; cin>>second_limit;
			
			if(first_limit>second_limit)
			
			{
			 tmp=first_limit;
			 first_limit=second_limit; //ïåðåñòàíîâêà ìåæ, â ðàç³ ÿêùî ïåðøå çíà÷åííÿ á³ëüøå äðóãîãî
			 second_limit=tmp;
		    }
			
			  cout<<lin_e<<'\n'<<header<<'\n'<<lin_e<<endl;
			  for (i = 0; i<max; i++)
			{
		
			if ( ((player[i].*where)>=first_limit) && ((player[i].*where)<=second_limit) )
				{
				cout <<n<<". "<< player[i].name<< " " <<  player[i].name1 <<  setw(6)<<'\t' << '|' << '\t' << player[i].nationality << setw(7)<< '\t' << '|' << '\t';
				cout<< player[i].club_name << setw(8)<< '\t' << '|' << '\t' << player[i].age << '\t' << '|' << '\t'<<  player[i].position << '\t' ;
				cout << '|' << '\t' <<   player[i].weight << '\t' << '|' << '\t' <<  player[i].height << '\t' << '|' << '\t' << player[i].price << '\t' << '|' << '\t'<<endl;
				cout << line << endl;
				k++;
				n++;
				}

			}
			  
		 	if(k==0){ cout<<"\nPlayers not found!\n"<<endl;}	break;
		}
		}
	
	file.close();
	return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ñòèðàííÿ âñ³õ äàíèõ ³ç ôàéëó
void Function::Delete_All_Data_Player()
{
	cout << "\nAre you sure? y/n\n";
	char x;
	cin >> x;
	cout << "\n";
	if (x == 'y')
	{
		ofstream file2("basket.txt", ios_base::trunc);
		file2.close();
	}
	else return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//ñòèðàííÿ âñ³õ äàíèõ ³ç ôàéëó
void Function::Delete_All_Data_Club()
{
	cout << "\nAre you sure? y/n\n";
	char x;
	cin >> x;
	cout << "\n";
	if (x == 'y')
	{
		ofstream file1("basclub.txt", ios_base::trunc);
		file1.close();
	}
	else return;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//äîäàâàííÿ êëóáó
void Club::Add_Club()
{
	system("cls");
	Club club[size2];
	int i, k, d, MAX=1;
	
	for(i=0; i < MAX; i++)
	{
		cout << "\nEnter club's name:\n";
		cin>>club[i].club_name;
		cout<< "\nEnter club's city:\n";
		cin>>club[i].club_city;
M1:		cout<<"\nEnter club's conference: [1] Western conference;  [2] Eastern conference;\n"; cin>>k;
		if((k<1)||(k>2)||(!cin))  { cin.clear(); cin.get(); system("cls"); cout << "   You entered incorect number!\n" << endl; goto M1; } 
		switch(k)
		{
				case 1: club[i].club_conference="Western"; break;
				case 2: club[i].club_conference="Eastern"; break;
		}
		if(k==1)
		{
M2:			cout<<"\nEnter club's division: [1] Northwest;  [2] Pacific;  [3] Southwest;\n"; cin>>d;
			if((d<1)||(d>3)||(!cin))  { cin.clear(); cin.get(); system("cls"); cout << "   You entered incorect number!\n" << endl; goto M2; } 
			switch(d)
			{
					case 1: club[i].club_division="Northwest"; break;
					case 2: club[i].club_division="Pacific"; break;
					case 3: club[i].club_division="Southwest"; break;
					
			}
		}
		else if(k==2)
		{
M3:			cout<<"\nEnter club's division: [1] Atlantic;  [2] Central;  [3] Southeast;\n"; cin>>d;
			if((d<1)||(d>3)||(!cin))  { cin.clear(); cin.get(); system("cls"); cout << "   You entered incorect number!\n" << endl; goto M3; } 
			switch(d)
			{
					case 1: club[i].club_division="Atlantic"; break;
					case 2: club[i].club_division="Central"; break;
					case 3: club[i].club_division="Southeast"; break;
					
			}	
		}
		cout<<"\nEnter club's budget:\n";
		cin>>club[i].club_budget;
	}
	ofstream file("basclub.txt", ios::ate | ios::app);
	for(i=0; i<MAX; i++)
	{
		file<< "\n"<<club[i].club_name<<"\t"<<club[i].club_city<<"\t"<<club[i].club_conference;
		file<<"\t"<<club[i].club_division<<"\t"<<club[i].club_budget;
	}
	file.close();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//âèâåäåííÿ ñïèñêó êëóá³â íà åêðàí
void Club::Show_Club()
{
	Club club[size2];
	int i=0, n=1;
	system("cls");
	ifstream file3("basclub.txt",ios_base::in);
	cout<<lin_e1<<'\n'<<headercl<<'\n'<<lin_e1<<endl;
	while(!file3.eof())
	{
		file3>>club[i].club_name>>club[i].club_city>>club[i].club_conference>>club[i].club_division>>club[i].club_budget;
		
		cout<<n<<". "<< club[i].club_name << setw(5)<<'\t' << '|' << '\t'<<club[i].club_city <<setw(4)<<'\t' << '|' << '\t'<< club[i].club_conference << '\t' << '|' << '\t';
		cout<< club[i].club_division <<setw(5) << '\t' << '|' << '\t'<< club[i].club_budget << '\t' << '|' << '\t'<<endl;
		cout << line1 << endl;
		i++;
		n++;
	}
	
	file3.close();
	return;
	
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

main()
{
	Admin ad;
	ad.Authorization();

}

