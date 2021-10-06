#pragma once

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "GameComponents.h"
#include "Console.h"
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

#define LIST_HERO "ListHero.txt" //ten file luu danh sach hero
#define LOG_FILE "Log.txt" //ten file luu lich su dau

#define TEAM_SIZE 3 //kich thuoc team mac dinh
#define NPC_TIME 1000 //thoi gian dau mac dinh cua npc

#define REFRESH_RATE 800 //toc do refresh thong tin tran dau (800 ms)

#define EXIT -2 //ma thoat

extern vector<Hero> HL; //danh sach hero trong tro choi

extern vector<string> randomName; //mang ten cho npc
extern vector<Match> LOG; //lich su dau

extern string username1; //ten user 1
extern string username2; //ten user 2

class GameManager
{
public:
	static void loadData(string _source); //load danh sach hero
	static void saveData(string _source); //luu danh sach hero vao danh sach

	static void pressAnyKeyToContinue(); //tam dung de xem hien thi tren console
	static void printInstructor(); //in huong dan choi game

	static void login(); //dang nhap user 1

	static void loadLog(string _source); //load lich su tran danh
	static void addLog(string _source, Match match); //them tran danh moi vao file log

	static void PVEMenu(); //menu danh voi npc
	static void PVPMenu(); //menu danh voi user 2

	static void displayCombatInfo(Team& team1, Team& team2, string env); //hien thi thong tin tran dau
};

class CombatSystem
{
public:
	static void prematchInteractions(Team& team1, Team& team2); //tinh toan thay doi chi so truoc tran dau
	static int match(Team& team1, Team& team2, float MAXTIME); //ham chinh thuc hien viec dau giua 2 team

	static Team generateRandomTeam(int memberCount); //sinh team ngau nhien
};

class Menu
{
protected:
	vector<string> options;
	int offsetX = 10;
	int offsetY = 3;
	int subOffsetX = 0;
	int subOffsetY = 0;
public:
	virtual void display() = 0; //hien thi thong tin cua menu
	virtual int handleInput(); //xu ly du lieu nhap cua nguoi dung
	virtual int func() = 0; //ham chinh thuc hien chuc nang cua menu
};

class MainMenu : public Menu
{
public:
	MainMenu();
	~MainMenu();

	void display();
	int func();
};

extern MainMenu mainMenu;

//menu chon hero
class HeroMenu : public Menu
{
public:
	HeroMenu();
	~HeroMenu();

	void display();
	int handleInput();
	int func();
};

extern HeroMenu heroMenu;

//menu chon team
class TeamMenu : public Menu
{
public:
	TeamMenu();
	~TeamMenu();

	void display();
	void display(string _name);
	int handleInput();
	int func();

	Team func(string _name);
};

extern TeamMenu teamMenu;

//menu sua hero
class EditMenu : public Menu
{
public:
	EditMenu();
	~EditMenu();

	void display();
	int handleInput();
	int func();

	void addHeroMenu();
	void editHeroMenu();
	void removeHeroMenu();
};

extern EditMenu editMenu;

//menu xem log
class LogMenu : public Menu
{
public:
	LogMenu();
	~LogMenu();

	void display();
	int handleInput();
	int func();
};

extern LogMenu logMenu;

//menu xac thuc lua chon
class ConfirmMenu : public Menu
{
public:
	ConfirmMenu();
	~ConfirmMenu();

	void display();
	int func();

	void display(string _msg); //xac thuc voi thong diep _msg
	void display(string _msg, Hero& hero); //xac thuc hero
	void display(Team& team); //xac thuc team

	int handleInput();
	
	int func(string _msg); //xac thuc voi thong diep _msg
	int func(string _msg, Hero& hero); //xac thuc hero
	int func(Team& team); //xac thuc team
};

extern ConfirmMenu confirmMenu;




