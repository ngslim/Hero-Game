#include "GameComponents.h"

Element::Element()
{
}

Element::Element(string _name, string _generation, string _overcomer, int _colorCode)
{
	name = _name;
	genInteract = _generation;
	overcomeInteract = _overcomer;
	colorCode = _colorCode;
}

Element::~Element()
{
}

string Element::getName()
{
	return name;
}

string Element::getGenInteract()
{
	return genInteract;
}

string Element::getOvercomeInteract()
{
	return overcomeInteract;
}

int Element::getColorCode()
{
	return colorCode;
}

void Element::setName(string _name)
{
	name = _name;
}

void Element::setGenInteract(string _generation)
{
	genInteract = _generation;
}

void Element::setOvercomeInteract(string _overcomer)
{
	overcomeInteract = _overcomer;
}


ElementSystem::ElementSystem()
{
	//danh sach cac he (nguyen to) mac dinh
	_list.push_back(Element("Wood", "Fire", "Earth", ColorCode_Green));
	_list.push_back(Element("Fire", "Earth", "Metal", ColorCode_Red));
	_list.push_back(Element("Earth", "Metal", "Water", ColorCode_DarkYellow));
	_list.push_back(Element("Metal", "Water", "Wood", ColorCode_Yellow));
	_list.push_back(Element("Water", "Wood", "Fire", ColorCode_Blue));
}

ElementSystem::~ElementSystem()
{
}

string ElementSystem::getGenInteractor(string _name)
{
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].getName() == _name)
		{
			return _list[i].getGenInteract();
		}
	}
	return "";
}

string ElementSystem::getOvercomeInteractor(string _name)
{
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].getName() == _name)
		{
			return _list[i].getOvercomeInteract();
		}
	}
	return "";
}

int ElementSystem::getSize()
{
	return _list.size();
}

string ElementSystem::getName(int index)
{
	return _list[index].getName();
}

int ElementSystem::getColorCode(string _name)
{
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].getName() == _name)
		{
			return _list[i].getColorCode();
		}
	}
	return ColorCode_Default;
}

ElementSystem ES;

Hero::Hero()
{
}

Hero::Hero(string _name, string _attr, float _health, float _atk, float _def, float _as)
{
	name = _name;
	attr = _attr;
	health = _health;
	atk = _atk;
	def = _def;
	as = _as;
}

Hero::~Hero()
{
}

string Hero::getName()
{
	return name;
}

string Hero::getAttribute()
{
	return attr;
}

float Hero::getHealth()
{
	return health;
}

float Hero::getAtk()
{
	return atk;
}

float Hero::getDef()
{
	return def;
}

float Hero::getAs()
{
	return as;
}

void Hero::setName(string _name)
{
	name = _name;
}

void Hero::setAttribute(string _attr)
{
	attr = _attr;
}

void Hero::setHealth(float _health)
{
	health = _health;
}

void Hero::setAtk(float _atk)
{
	atk = _atk;
}

void Hero::setDef(float _def)
{
	def = _def;
}

void Hero::setAs(float _as)
{
	as = _as;
}

void Hero::info()
{
	if (health == 0)
	{
		setTextColor(ColorCode_Grey);
		cout << name << ' '<< attr << ' ' << "HP: " << health << " ATK: " << atk << " DEF: " << def << " AS: " << as << endl;
		setTextColor(ColorCode_Default);
	}
	else
	{
		cout << name << ' ';
		setTextColor(ES.getColorCode(attr));
		cout << attr << ' ';
		setTextColor(ColorCode_Default);
		cout << "HP: " << health << " ATK: " << atk << " DEF: " << def << " AS: " << as << endl;
	}
}

void Hero::interaction(Hero& target)
{
	//genInteraction: health +15%
	float healthGIScale = 0.15f;
	//overcomeInteraction: attack speed -10%
	float asOIScale = -0.1f;

	if (ES.getGenInteractor(attr) == target.getAttribute())
	{
		target.setHealth(target.getHealth() * (1 + healthGIScale));
	}

	if (ES.getOvercomeInteractor(attr) == target.getAttribute())
	{
		target.setAs(target.getAs() * (1 + asOIScale));
	}
}

float duel(Hero& hero1, Hero& hero2, float time)
{
	//TINH TOAN TRUOC TRAN DAU
	//tuong tac tuong sinh (elementAdvantages - GI): attack +10%
	float atkGIScale = 0.1f;
	//tuong tac tuong khac (elementDisadvantages - OI): defense -50%
	float defOIScale = -0.5f;

	//o day ta lay atk va def cua tung hero de tranh lam thay doi gia tri khi chung doi dau voi hero khac
	float atk1 = hero1.getAtk();
	float atk2 = hero2.getAtk();

	float def1 = hero1.getDef();
	float def2 = hero2.getDef();
	
	//tinh toan chi so tuong tac giua 2 hero dang dau voi nhau
	if (ES.getOvercomeInteractor(hero1.getAttribute()) == hero2.getAttribute())
	{
		atk1 = atk1 * (1 + atkGIScale);
		def2 = def2 * (1 + defOIScale);
	}

	if (ES.getOvercomeInteractor(hero2.getAttribute()) == hero1.getAttribute())
	{
		atk2 = atk2 * (1 + atkGIScale);
		def1 = def1 * (1 + defOIScale);
	}

	//TINH TOAN KET QUA TRAN DAU
	//sat thuong gay ra cua hero 1 va 2 len doi thu moi don danh
	float hero1DamageDeal = atk1 - def2; 
	float hero2DamageDeal = atk2 - def1;

	//so don danh de ket lieu doi thu cua hero 1 va 2
	int numberOfHits1;
	int numberOfHits2; 
	
	if (hero1DamageDeal < 0)
	{
		hero1DamageDeal = 0;
		numberOfHits1 = 999;
	}
	else
	{
		numberOfHits1 = ceil(hero2.getHealth() / hero1DamageDeal);
	}

	if (hero2DamageDeal < 0)
	{
		hero2DamageDeal = 0;
		numberOfHits2 = 999;
	}
	else
	{
		numberOfHits2 = ceil(hero1.getHealth() / hero2DamageDeal);
	}

	//thoi gian de hero 1 va 2 ha guc doi thu
	float timeTake1 = numberOfHits1 * hero1.getAs();
	float timeTake2 = numberOfHits2 * hero2.getAs();

	//xu ly ket qua
	float timeTake = 0;	//thoi gian cua tran dau

	if (time <= timeTake1 && time <= timeTake2)
	{
		timeTake = time;
		hero2.setHealth(hero2.getHealth() - floor(timeTake / hero1.getAs()) * hero1DamageDeal);
		hero1.setHealth(hero1.getHealth() - floor(timeTake / hero2.getAs()) * hero2DamageDeal);
		return timeTake;
	}

	if (timeTake1 > timeTake2)
	{
		hero1.setHealth(0);
		hero2.setHealth(hero2.getHealth() - floor(timeTake2 / hero1.getAs()) * hero1DamageDeal);
		timeTake = timeTake2;
	}
	else if (timeTake1 < timeTake2)
	{
		hero2.setHealth(0);
		hero1.setHealth(hero1.getHealth() - floor(timeTake1 / hero2.getAs()) * hero2DamageDeal);
		timeTake = timeTake1;
	}
	else //hai hero hoa nhau (deu bi ha guc)
	{
		hero1.setHealth(0);
		hero2.setHealth(0);
		timeTake = timeTake1;
	}

	return timeTake;
}

Team::Team()
{
}

Team::Team(string _name)
{
	name = _name;
}

Team::~Team()
{
}

string Team::getName()
{
	return name;
}

int Team::getSize()
{
	return _list.size();
}

Hero& Team::operator[](int _index)
{
	return _list[_index];
}

void Team::setName(string _name)
{
	name = _name;
}

bool Team::isDefeated()
{
	for (int i = 0; i < _list.size(); i++)
	{
		if (_list[i].getHealth() != 0)
		{
			return false;
		}
	}
	
	return true;
}

void Team::add(const Hero& _hero)
{
	_list.push_back(_hero);
}

void Team::prematchInteractions()
{
	for (int i = 0; i < _list.size(); i++)
	{
		for (int j = 0; j < _list.size(); j++)
		{
			if (j != i)
			{
				_list[i].interaction(_list[j]);
			}
		}
	}
}

Match::Match()
{
}

Match::Match(string _time, Team& _team1, Team& _team2, string _env, int _res)
{
	time = _time;
	team1 = _team1;
	team2 = _team2;
	env = _env;
	res = _res;
}

Match::~Match()
{
}

Team& Match::getTeam1()
{
	return team1;
}

Team& Match::getTeam2()
{
	return team2;
}

void Match::setTime(string _time)
{
	time = _time;
}

void Match::setEnv(string _env)
{
	env = _env;
}

void Match::setRes(int _res)
{
	res = _res;
}

string Match::getTime()
{
	return time;
}

string Match::getEnv()
{
	return env;
}

int Match::getRes()
{
	return res;
}

