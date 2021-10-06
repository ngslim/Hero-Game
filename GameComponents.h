#pragma once

#include "Console.h"
#include <iostream>
#include <vector>

using namespace std;

class Element
{
private:
	string name = ""; //ten nguyen to
	string genInteract = ""; //ten nguyen to tuong sinh
	string overcomeInteract = ""; //ten nguyen to tuong khac
	int colorCode = ColorCode_Default; //ma mau
public:
	Element();
	Element(string, string, string, int);
	~Element();

	string getName();
	string getGenInteract();
	string getOvercomeInteract();
	int getColorCode();

	void setName(string);
	void setGenInteract(string);
	void setOvercomeInteract(string);
};

class ElementSystem	//element interaction system
{
private:
	vector<Element> _list;
public:
	ElementSystem();
	~ElementSystem();

	string getGenInteractor(string _name); //lay ten nguyen to tuong sinh cua nguyen to _name
	string getOvercomeInteractor(string _name); //lay ten nguyen to tuong khac cua nguyen to _name
	int getSize(); //lay so luong nguyen to
	string getName(int index); //lay ten nguyen to theo index
	int getColorCode(string _name); //lay ma mau nguyen to _name
};

extern ElementSystem ES;

class Environment
{
private:
	string name = "";
public:

};


class Hero
{
private:
	float health = 0; //mau
	float atk = 0; //sat thuong tren don danh
	float def = 0; //phong thu tren don danh
	float as = 0; //toc do danh
	string name = ""; //ten
	string attr = ""; //he (nguyen to)
	
public:
	Hero();
	Hero(string, string, float, float, float, float);
	~Hero();

	string getName();
	string getAttribute();
	float getHealth();
	float getAtk();
	float getDef();
	float getAs();

	void setName(string);
	void setAttribute(string);
	void setHealth(float);
	void setAtk(float);
	void setDef(float);
	void setAs(float);

	void info(); //hien thi thong tin hero

	void interaction(Hero& target); //tuong tac he giua hero
	friend float duel(Hero& hero1, Hero& hero2, float time); //thuc hien viec dau giua 2 hero
};

class Team
{
private:
	string name = ""; //ten team
	vector<Hero> _list; //danh sach hero trong team
public:
	Team();
	Team(string);
	~Team();

	string getName();
	void setName(string);

	int getSize(); //lay kich thuoc team

	Hero& operator[](int); //lay hero theo index

	bool isDefeated(); //kiem tra toan bo thanh vien cua team da bi ha guc

	void add(const Hero& _hero); //them hero vao team

	void prematchInteractions(); //tuong tac giua cac hero trong team truoc tran dau
};

class Match
{
private:
	Team team1;
	Team team2;
	string time; //thoi gian
	string env; //moi truong
	int res = 0; //ket qua
public:
	Match();
	Match(string, Team&, Team&, string, int);
	~Match();

	Team& getTeam1();
	Team& getTeam2();

	void setTime(string);
	void setEnv(string);
	void setRes(int);
	
	string getTime();
	string getEnv();
	int getRes();
};
