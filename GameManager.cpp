#include "GameManager.h"

vector<Hero> HL;
vector<string> randomName = { "Ti", "Teo", "vuatrochoi", "beheo98", "pepsi", "batuoc9999" };
vector<Match> LOG;

MainMenu mainMenu;
EditMenu editMenu;
LogMenu logMenu;
ConfirmMenu confirmMenu;
HeroMenu heroMenu;
TeamMenu teamMenu;

int environmentCode = 0; //ma moi truong cho tung tran dau
						 //voi moi tran dau thi ma nay se thay doi ngau nhien

int DEFAULT_OFFSET_X = 5; //toa do x mac dinh hien thi
int DEFAULT_OFFSET_Y = 1; //toa do y mac dinh hien thi

string username1 = "";
string username2 = "";

/*
offsetX: toa do x cua dong dau tien cua menu sau dong tieu de (neu co)
offsetY: toa do y cua dong dau tien cua menu sau dong tieu de (neu co)

subOffsetX, subOffsetY la toa do du phong cho truong hop co nhieu thong tin tieu de can hien thi
*/


void GameManager::loadData(string _source)
{
	HL.clear();

	ifstream file;
	file.open(_source);
	
	if(!file.is_open())
	{
		cout << "Invalid file" << endl;
	}

	string line;
	string temp;

	int count = 0;

	while (!file.eof())
	{
		Hero newHero;
		getline(file, line);
		
		if (line.length() == 0)
		{
			break;
		}

		int pos = line.find_first_of(';');
		temp = line.substr(0, pos);
		newHero.setName(temp);
		line = line.substr(pos + 1);

		pos = line.find_first_of(';');
		temp = line.substr(0, pos);
		newHero.setAttribute(temp);
		line = line.substr(pos + 1);

		pos = line.find_first_of(';');
		temp = line.substr(0, pos);
		newHero.setHealth(stof(temp));
		line = line.substr(pos + 1);

		pos = line.find_first_of(';');
		temp = line.substr(0, pos);
		newHero.setAtk(stof(temp));
		line = line.substr(pos + 1);

		pos = line.find_first_of(';');
		temp = line.substr(0, pos);
		newHero.setDef(stof(temp));
		line = line.substr(pos + 1);

		newHero.setAs(stof(line));

		HL.push_back(newHero);
	}

	file.close();
}

void GameManager::saveData(string _source)
{
	ofstream file;
	file.open(_source);

	if (!file.is_open())
	{
		cout << "Invalid file" << endl;
	}

	for (int i = 0; i < HL.size(); i++)
	{
		file << HL[i].getName() << ';';
		file << HL[i].getAttribute() << ';';
		file << HL[i].getHealth() << ';';
		file << HL[i].getAtk() << ';';
		file << HL[i].getDef() << ';';
		file << HL[i].getAs()  << endl;
	}

	file.close();
}

void GameManager::pressAnyKeyToContinue()
{
	int spacing = 20; //khoang cach giua vi tri mac dinh va dong thong bao
	
	int offsetX = DEFAULT_OFFSET_X;
	int offsetY = DEFAULT_OFFSET_Y + spacing;
	
	gotoXY(offsetX, offsetY);
	system("pause");
}

void GameManager::printInstructor()
{
	int spacing = 20; //khoang cach mac dinh giua vi tri mac dinh va dong thong bao

	int offsetX = DEFAULT_OFFSET_X;
	int offsetY = DEFAULT_OFFSET_Y + spacing;

	gotoXY(offsetX, offsetY);
	cout << "Use arrow keys or WASD to move, use ENTER to select.";
}

void GameManager::login()
{
	string name;
choose_name:
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Enter your username: ";
	getline(cin, name);

	int c = confirmMenu.func("Do you want to use this name: " + name + "?");

	if (c == 1)
	{
		goto choose_name;
	}

	username1 = name;
}


void GameManager::loadLog(string _source)
{
	ifstream file;
	file.open(_source);

	if (!file.is_open())
	{
		cout << "Invalid file" << endl;
	}

	string line;
	string temp;

	while (!file.eof())
	{
		Match newMatch;
		
		getline(file, line);

		if (line.length() == 0)
		{
			break;
		}

		int pos = line.find_first_of('|');

		temp = line.substr(0, pos);
		newMatch.setTime(temp);
		line = line.substr(pos + 1);

		pos = line.find_first_of('|');
		temp = line.substr(0, pos);
		newMatch.setRes(stoi(temp));
		line = line.substr(pos + 1);

		newMatch.setEnv(line);

		getline(file, line);
		newMatch.getTeam1().setName(line);

		for (int i = 0; i < TEAM_SIZE; i++)
		{
			Hero newHero;
			getline(file, line);

			int pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setName(temp);
			line = line.substr(pos + 1);

			pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setAttribute(temp);
			line = line.substr(pos + 1);

			pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setHealth(stof(temp));
			line = line.substr(pos + 1);

			pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setAtk(stof(temp));
			line = line.substr(pos + 1);

			pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setDef(stof(temp));
			line = line.substr(pos + 1);

			newHero.setAs(stof(line));

			newMatch.getTeam1().add(newHero);
		}

		getline(file, line);
		newMatch.getTeam2().setName(line);

		for (int i = 0; i < TEAM_SIZE; i++)
		{
			Hero newHero;
			getline(file, line);

			int pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setName(temp);
			line = line.substr(pos + 1);

			pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setAttribute(temp);
			line = line.substr(pos + 1);

			pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setHealth(stof(temp));
			line = line.substr(pos + 1);

			pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setAtk(stof(temp));
			line = line.substr(pos + 1);

			pos = line.find_first_of(';');
			temp = line.substr(0, pos);
			newHero.setDef(stof(temp));
			line = line.substr(pos + 1);

			newHero.setAs(stof(line));

			newMatch.getTeam2().add(newHero);
		}

		LOG.push_back(newMatch);
	}

	file.close();
}

void GameManager::addLog(string _source, Match match)
{
	ofstream file;
	file.open(_source, fstream::app);
	
	if(!file.is_open())
	{
		cout << "Invalid file" << endl;
	}

	//LUU TRAN DAU VAO LOG

	//luu <thoi gian|ket qua|moi truong>
	file << match.getTime() << '|' << match.getRes() << '|' << match.getEnv() << endl;
	//ten team 1
	file << match.getTeam1().getName() << endl;
	//danh sach team 1
	for (int i = 0; i < match.getTeam1().getSize(); i++)
	{
		file << match.getTeam1()[i].getName() << ';';
		file << match.getTeam1()[i].getAttribute() << ';';
		file << match.getTeam1()[i].getHealth() << ';';
		file << match.getTeam1()[i].getAtk() << ';';
		file << match.getTeam1()[i].getDef() << ';';
		file << match.getTeam1()[i].getAs() << endl;
	}
	//ten team2
	file << match.getTeam2().getName() << endl;
	//danh sach team 2
	for (int i = 0; i < match.getTeam2().getSize(); i++)
	{
		file << match.getTeam2()[i].getName() << ';';
		file << match.getTeam2()[i].getAttribute() << ';';
		file << match.getTeam2()[i].getHealth() << ';';
		file << match.getTeam2()[i].getAtk() << ';';
		file << match.getTeam2()[i].getDef() << ';';
		file << match.getTeam2()[i].getAs() << endl;
	}

	file.close();
}

void GameManager::PVEMenu()
{
	int c;
	
	//USER 1 CHON TEAM
choose_team:
	Team team1 = teamMenu.func(username1);

	//xac nhan su dung team da chon
	c = confirmMenu.func(team1);

	if (c == 1)
	{
		goto choose_team;
	}

	team1.setName(username1);
	
	//SINH TEAM NGAU NHIEN CUA NPC
	Team team2 = CombatSystem::generateRandomTeam(TEAM_SIZE);

	//XU LY TRAN DAU
	int res = CombatSystem::match(team1, team2, NPC_TIME);

	//hien thi ket qua tran dau
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	if (res == -1)
	{
		cout << "Timed out - Draw";
	}
	if (res == 0)
	{
		cout << "Draw";
	}
	if (res == 1)
	{
		cout << team1.getName() << " won!!!";
	}
	if (res == 2)
	{
		cout << team2.getName() << " won!!!";
	}

	//LUU TRAN DAU VAO LOG
	time_t now = time(0);
	string time(ctime(&now));

	time = time.substr(0, time.size() - 1);

	Match newMatch(time, team1, team2, ES.getName(environmentCode), res);

	addLog(LOG_FILE,newMatch);

	LOG.push_back(newMatch);

	pressAnyKeyToContinue();
}

void GameManager::PVPMenu()
{
	string name;
	int c;

	//USER 2 NHAP TEN
choose_name:
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Enter user 2's name: ";
	getline(cin, name);

	//xac nhan su dung ten da nhap
	c = confirmMenu.func("Do you want to use this name: " + name + "?");

	if (c == 1)
	{
		goto choose_name;
	}

	username2 = name;
	
	//USER 1 CHON TEAM
	Team team1;
choose_team_1:
	team1 = teamMenu.func(username1);

	//xac nhan su dung team da chon
	c = confirmMenu.func(team1);

	if (c == 1)
	{
		goto choose_team_1;
	}

	team1.setName(username1);

	//USER 2 CHON TEAM
	Team team2;
choose_team_2:
	team2 = teamMenu.func(username2);

	//xac nhan xu dung team da chon
	c = confirmMenu.func(team2);

	if (c == 1)
	{
		goto choose_team_2;
	}

	team2.setName(username2);

	//CHON THOI GIAN TOI DA CUA TRAN DAU
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Choose max battle time:";

	int offsetX = 10;
	int offsetY = 3;
	
	//danh sach thoi gian toi da
	vector<float> options = { 1000,2000,5000 };

	for (size_t i = 0; i < options.size(); i++)
	{
		gotoXY(offsetX + 5, offsetY + 2 * i);
		cout << options[i];
	}

	gotoXY(offsetX, offsetY);
	int i = 0;
	
	//xu ly dieu khien di chuyen va lua chon
	while (true)
	{
		char c = _getch();

		if (c == KEY_ENTER)
		{
			break;
		}

		if (c == KEY_DOWN || c == 's')
		{
			if (i == options.size() - 1)
			{
				i = 0;
			}
			else
			{
				i++;
			}
		}

		if (c == KEY_UP || c == 'w')
		{
			if (i == 0)
			{
				i = options.size() - 1;
			}
			else
			{
				i--;
			}
		}
		gotoXY(offsetX, offsetY + 2 * i);
	}

	float battleTime = options[i];

	//XU LY TRAN DAU
	int res = CombatSystem::match(team1, team2, battleTime);
	
	//hien thi ket qua tran dau
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	if (res == -1)
	{
		cout << "Timed out - Draw";
	}
	if (res == 0)
	{
		cout << "Draw";
	}
	if (res == 1) 
	{
		cout << team1.getName() << " won!!!";
	}
	if (res == 2)
	{
		cout << team2.getName() << " won!!!";
	}

	//LUU THONG TIN TRAN DAU VAO LOG		
	time_t now = time(0);
	string time(ctime(&now));

	time = time.substr(0, time.size() - 1);

	Match newMatch(time, team1, team2, ES.getName(environmentCode), res);

	addLog(LOG_FILE, newMatch);

	LOG.push_back(newMatch);

	pressAnyKeyToContinue();
}

void GameManager::displayCombatInfo(Team& team1, Team& team2, string env)
{
	int offsetX = 5;
	int offsetY = 7;

	int spacingBetweenTeam = 60; //khoang cach giua danh sach 2 team
	int spacingBetweenTeamAndName = -2; //khoang cach giua danh sach team va ten team
	int spacingBetweenTeamAndEnv = -4; //khoang cach giua danh sach team va moi truong

	system("CLS");

	//in thong tin moi truong
	gotoXY(offsetX, offsetY + spacingBetweenTeamAndEnv);
	cout << "Environment: ";
	setTextColor(ES.getColorCode(env));
	cout << env;
	setTextColor(ColorCode_Default);

	//in ten team 1
	gotoXY(offsetX, offsetY + spacingBetweenTeamAndName);
	cout << team1.getName();
	
	//in ten team 2
	gotoXY(offsetX + spacingBetweenTeam, offsetY + spacingBetweenTeamAndName);
	cout << team2.getName();

	//in dach sach team 1
	for (int i = 0; i < team1.getSize(); i++)
	{
		gotoXY(offsetX, offsetY + i);
		team1[i].info();
	}
	 
	//in danh sach team 2
	for (int i = 0; i < team2.getSize(); i++)
	{
		gotoXY(offsetX + spacingBetweenTeam, offsetY + i);
		team2[i].info();
	}

	gotoXY(0, 0);
}

void CombatSystem::prematchInteractions(Team& team1, Team& team2)
{
	//TEAM 1 VA 2 TINH TOAN TUONG TAC GIUA CAC THANH VIEN TRUOC TRAN DAU
	team1.prematchInteractions();
	team2.prematchInteractions();

	//SINH MOI TRUONG NGAY NHHIEN
	srand((unsigned int)time(NULL));
	environmentCode = rand() % ES.getSize();

	string env = ES.getName(environmentCode);
	
	//tuong tac tuong sinh (genInteraction - GI): health +5%, attack speed -10%
	float env_healthGIScale = 0.05f;
	float env_asGIScale = -0.1f;

	//tuong tac tuong khac (overcomeInteraction - OI): health -3%
	float env_healthOIScale = -0.03f;

	//TINH TOAN CAC TUONG TAC MOI TRUONG

	//team 1
	for (int i = 0; i < team1.getSize(); i++)
	{
		if (ES.getGenInteractor(env) == team1[i].getAttribute())
		{
			team1[i].setHealth(team1[i].getHealth() * (1 + env_healthGIScale));
			team1[i].setAs(team1[i].getAs() * (1 + env_asGIScale));
		}

		if (ES.getOvercomeInteractor(env) == team1[i].getAttribute())
		{
			team1[i].setHealth(team1[i].getHealth() * (1 + env_healthOIScale));
		}
	}

	//team 2
	for (int i = 0; i < team2.getSize(); i++)
	{
		if (ES.getGenInteractor(env) == team2[i].getAttribute())
		{
			team2[i].setHealth(team2[i].getHealth() * (1 + env_healthGIScale));
			team2[i].setAs(team2[i].getAs() * (1 + env_asGIScale));
		}

		if (ES.getOvercomeInteractor(env) == team2[i].getAttribute())
		{
			team2[i].setHealth(team2[i].getHealth() * (1 + env_healthOIScale));
		}
	}
}

int CombatSystem::match(Team& team1, Team& team2, float MAXTIME)
{
	float totalTime = 0; //tong thoi gian cua tran dau

	//TUONG TAC TRUOC TRAN DAU
	prematchInteractions(team1, team2);

	//XU LY TRAN DAU
	int i1 = 0; //index hero hien dang chien dau cua team 1
	int i2 = 0; //index hero hien dang chien dau cua team 2

	GameManager::displayCombatInfo(team1, team2, ES.getName(environmentCode));

	Sleep(REFRESH_RATE);

	while (true)
	{
		float timeTake = duel(team1[i1], team2[i2], MAXTIME - totalTime);
		totalTime += timeTake;

		GameManager::displayCombatInfo(team1, team2, ES.getName(environmentCode));

		Sleep(REFRESH_RATE);

		if (team1[i1].getHealth() == 0)
		{
			i1++;
		}

		if (team2[i2].getHealth() == 0)
		{
			i2++;
		}

		//dieu kien ket thu tran dau

		if (!team1.isDefeated() && !team2.isDefeated() && totalTime >= MAXTIME)
		{
			return -1; //het thoi gian
		}

		if (team1.isDefeated() && team2.isDefeated())
		{
			return 0; //ca 2 team deu bi ha guc
		}

		if (!team1.isDefeated() && team2.isDefeated())
		{
			return 1; //team 1 thang
		}

		if (team1.isDefeated() && !team2.isDefeated())
		{
			return 2; //team 2 thang
		}
	}
}

Team CombatSystem::generateRandomTeam(int memberCount)
{
	Team newTeam;

	srand((unsigned int)time(NULL));
	int rng = rand() % randomName.size();
	newTeam.setName(randomName[rng]);

	for (int i = 0; i < memberCount; i++)
	{
		rng = rand() % HL.size();
		
		newTeam.add(HL[rng]);
	}

	return newTeam;
}

int Menu::handleInput()
{
	gotoXY(offsetX, offsetY);
	int i = 0;

	//XU LY
	//xu ly dieu khien di chuyen va lua chon
	while (true)
	{
		char c = _getch();

		if (c == KEY_ENTER)
		{
			break;
		}

		if (c == KEY_DOWN || c == 's')
		{
			if (i == options.size() - 1)
			{
				i = 0;
			}
			else
			{
				i++;
			}
		}

		if (c == KEY_UP || c == 'w')
		{
			if (i == 0)
			{
				i = options.size() - 1;
			}
			else
			{
				i--;
			}
		}
		gotoXY(offsetX, offsetY + i);
	}

	return i;
}

MainMenu::MainMenu()
{
	options.push_back("Player vs. Computer");
	options.push_back("Player vs. Player");
	options.push_back("Edit hero list");
	options.push_back("View match log");
	options.push_back("Exit");
}

MainMenu::~MainMenu()
{
}

void MainMenu::display()
{
	system("CLS");

	//HIEN THI MENU

	GameManager::printInstructor();

	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Welcome, " << username1 << "!!!";

	//toa do x, y chua dong hero game
	int textArtX = DEFAULT_OFFSET_X;
	int textArtY = DEFAULT_OFFSET_Y + 2;

	gotoXY(textArtX, textArtY);
	cout << " _                                    ";
	gotoXY(textArtX, textArtY + 1);
	cout << "| |_ ___ ___ ___    ___ ___ _____ ___ ";
	gotoXY(textArtX, textArtY + 2);
	cout << "|   | -_|  _| . |  | . | .'|     | -_|";
	gotoXY(textArtX, textArtY + 3);
	cout << "|_|_|___|_| |___|  |_  |__,|_|_|_|___|";
	gotoXY(textArtX, textArtY + 4);
	cout << "                   |___|              ";

	//khoang cach giua toa do dau tien cua dong tieu de va main menu
	int spacing = 5;

	offsetX = textArtX;
	offsetY = textArtY + spacing + 1;

	//in cac lua chon cua main mernu
	for (int i = 0; i < options.size(); i++)
	{
		gotoXY(offsetX, offsetY + i);
		cout << i + 1 << ". ";
		gotoXY(offsetX + 5, offsetY + i);
		cout << options[i];
	}
}

int MainMenu::func()
{
	display();
	int i = handleInput();

	if (i == 0)
	{
		GameManager::PVEMenu();
	}

	if (i == 1)
	{
		GameManager::PVPMenu();
	}

	if (i == 2)
	{
		editMenu.func();
	}

	if (i == 3)
	{
		logMenu.func();
	}

	if (i == 4)
	{
		int c = confirmMenu.func("Do you want to exit?");
		if (c == 0)
		{
			exit(0);
		}
	}
}

ConfirmMenu::ConfirmMenu()
{
	options.push_back("Yes");
	options.push_back("No");
}

ConfirmMenu::~ConfirmMenu()
{
}

void ConfirmMenu::display()
{
}

int ConfirmMenu::func()
{
	return 0;
}

void ConfirmMenu::display(string _msg)
{
	//HIEN THI MENU
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << _msg;

	offsetX = 10;
	offsetY = 3;

	//in cac lua chon
	for (int i = 0; i < options.size(); i++)
	{
		gotoXY(offsetX + 5, offsetY + 2 * i);
		cout << options[i];
	}
}

int ConfirmMenu::handleInput()
{
	gotoXY(offsetX, offsetY);
	int i = 0;

	//XU LY
	//xu ly dieu khien di chuyen va lua chon
	while (true)
	{
		char c = _getch();

		if (c == KEY_ENTER)
		{
			break;
		}

		if (c == KEY_DOWN || c == 's')
		{
			if (i == options.size() - 1)
			{
				i = 0;
			}
			else
			{
				i++;
			}
		}

		if (c == KEY_UP || c == 'w')
		{
			if (i == 0)
			{
				i = options.size() - 1;
			}
			else
			{
				i--;
			}
		}
		gotoXY(offsetX, offsetY + 2 * i);
	}

	//tra ve 0: yes, 1: no
	return i;
}

int ConfirmMenu::func(string _msg)
{
	display(_msg);
	return handleInput();
}

void ConfirmMenu::display(string _msg, Hero& hero)
{
	//HIEN THI MENU
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << _msg;

	offsetX = 10;
	offsetY = 3;

	//in thong tin hero de xac nhan
	gotoXY(offsetX, offsetY);
	hero.info();

	offsetY = offsetY + 2;

	//in cac lua chon
	for (int i = 0; i < options.size(); i++)
	{
		gotoXY(offsetX + 5, offsetY + 2 * i);
		cout << options[i];
	}
}

int ConfirmMenu::func(string _msg, Hero& hero)
{
	display(_msg, hero);
	return handleInput();
}

void ConfirmMenu::display(Team& team)
{
	//HIEN THI MENU
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Do you want to use this team: " << team.getName();

	offsetX = 10;
	offsetY = 3;

	//in dach sach hero trong team de xac nhan
	for (int i = 0; i < team.getSize(); i++)
	{
		gotoXY(offsetX, offsetY + i);
		team[i].info();
	}

	offsetY = offsetY + team.getSize() + 1;

	//in cac lua chon
	for (int i = 0; i < options.size(); i++)
	{
		gotoXY(offsetX + 5, offsetY + 2 * i);
		cout << options[i];
	}
}

int ConfirmMenu::func(Team& team)
{
	display(team);
	return handleInput();
}

LogMenu::LogMenu()
{
}

LogMenu::~LogMenu()
{
}

void LogMenu::display()
{
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Choose the match you want to review: ";

	offsetX = 10;
	offsetY = 5;

	gotoXY(offsetX + 5, offsetY + EXIT);
	cout << "Return to main menu";

	//in danh sach cac tran dau duoc luu trong log
	for (int i = 0; i < LOG.size(); i++)
	{
		gotoXY(offsetX, offsetY + i);
		cout << i + 1 << ". ";
		gotoXY(offsetX + 5, offsetY + i);
		cout << LOG[i].getTime() << " | ";
		gotoXY(offsetX + 32, offsetY + i);
		cout << LOG[i].getTeam1().getName() << " vs. " << LOG[i].getTeam2().getName();
	}
}

int LogMenu::handleInput()
{
	gotoXY(offsetX, offsetY);
	int i = 0;

	while (true)
	{
		char c = _getch();

		if (c == KEY_ENTER)
		{
			break;
		}

		if (c == KEY_DOWN || c == 's')
		{
			if (i == LOG.size() - 1)
			{
				i = EXIT;
			}
			else if (i == EXIT)
			{
				i = 0;
			}
			else
			{
				i++;
			}
		}

		if (c == KEY_UP || c == 'w')
		{
			if (i == 0)
			{
				i = EXIT;
			}
			else if (i == EXIT)
			{
				i = LOG.size() - 1;
			}
			else
			{
				i--;
			}
		}

		gotoXY(offsetX, offsetY + i);
	}

	return i;
}

int LogMenu::func()
{
	if (LOG.size() == 0) //log rong
	{
		system("CLS");
		gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
		cout << "Log is empty.";
		GameManager::pressAnyKeyToContinue();
		return 0;
	}
begin:
	display();
	int i = handleInput();

	if (i == EXIT)
	{
		return 0;
	}
	else
	{
		//hien thi thong tin tran dau
		GameManager::displayCombatInfo(LOG[i].getTeam1(), LOG[i].getTeam2(), LOG[i].getEnv());

		//hien thi ket qua tran dau
		gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
		if (LOG[i].getRes() == -1)
		{
			cout << "Timed out - Draw";
		}
		if (LOG[i].getRes() == 0)
		{
			cout << "Draw";
		}
		if (LOG[i].getRes() == 1)
		{
			cout << LOG[i].getTeam1().getName() << " won!!!";
		}
		if (LOG[i].getRes() == 2)
		{
			cout << LOG[i].getTeam2().getName() << " won!!!";
		}
		
		GameManager::pressAnyKeyToContinue();

		goto begin;
	}

	return 0;
}

HeroMenu::HeroMenu()
{
}

HeroMenu::~HeroMenu()
{
}

void HeroMenu::display()
{
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Choose the hero: ";

	offsetX = 10;
	offsetY = 5;

	//in dong return
	gotoXY(offsetX + 5, offsetY + EXIT);
	cout << "Return";

	//in dach sach hero
	for (int i = 0; i < HL.size(); i++)
	{
		gotoXY(offsetX, offsetY + i);
		cout << i + 1 << ". ";
		gotoXY(offsetX + 5, offsetY + i);
		HL[i].info();
	}
}

int HeroMenu::handleInput()
{
	gotoXY(offsetX, offsetY);
	int i = 0;

	//XU LY
	//xu ly dieu khien di chuyen va lua chon
	while (true)
	{
		char c = _getch();

		if (c == KEY_ENTER)
		{
			break;
		}

		if (c == KEY_DOWN || c == 's')
		{
			if (i == HL.size() - 1)
			{
				i = EXIT;
			}
			else if (i == EXIT)
			{
				i = 0;
			}
			else
			{
				i++;
			}
		}

		if (c == KEY_UP || c == 'w')
		{
			if (i == 0)
			{
				i = EXIT;
			}
			else if (i == EXIT)
			{
				i = HL.size() - 1;
			}
			else
			{
				i--;
			}
		}

		gotoXY(offsetX, offsetY + i);
	}

	return i;
}

int HeroMenu::func()
{
	display();
	return handleInput();
}

TeamMenu::TeamMenu()
{
}

TeamMenu::~TeamMenu()
{
}

void TeamMenu::display()
{
}

void TeamMenu::display(string _name)
{
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << _name << ", Choose the heroes for your team: ";

	int offsetX = 10;
	int offsetY = 3;

	subOffsetX = offsetX;
	subOffsetY = offsetY + TEAM_SIZE + 1;

	//in danh sach hero
	for (int i = 0; i < HL.size(); i++)
	{
		gotoXY(subOffsetX, subOffsetY + i);
		cout << i + 1 << ". ";
		gotoXY(subOffsetX + 5, subOffsetY + i);
		HL[i].info();
	}
}

int TeamMenu::handleInput()
{
	int i = 0;
	gotoXY(subOffsetX, subOffsetY + i);

	//XU LY
	//xu ly dieu khien di chuyen va lua chon
	while (true)
	{
		char c = _getch();
		if (c == KEY_ENTER)
		{
			break;
		}
		if (c == KEY_DOWN || c == 's')
		{
			if (i == HL.size() - 1)
			{
				i = 0;
			}
			else
			{
				i++;
			}
		}

		if (c == KEY_UP || c == 'w')
		{
			if (i == 0)
			{
				i = HL.size() - 1;
			}
			else
			{
				i--;
			}
		}

		gotoXY(subOffsetX, subOffsetY + i);
	}

	return i;
}

int TeamMenu::func()
{
	return 0;
}

Team TeamMenu::func(string _name)
{
	Team newTeam;

	display(_name);

choose_hero:
	int i = handleInput();

	newTeam.add(HL[i]);

	//in cac hero hien co trong team o phia tren danh sach
	for (int i = 0; i < newTeam.getSize(); i++)
	{
		gotoXY(offsetX, offsetY + i);
		newTeam[i].info();
	}

	if (newTeam.getSize() < TEAM_SIZE) //dieu khien dung
	{
		goto choose_hero;
	}

	return newTeam; //tra ve team lua chon
}

EditMenu::EditMenu()
{
	options.push_back("Add new hero");
	options.push_back("Edit existing hero");
	options.push_back("Remove existing hero");
}

EditMenu::~EditMenu()
{
}

void EditMenu::display()
{
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Choose the function you want to use: ";

	offsetX = 10;
	offsetY = 5;

	gotoXY(offsetX + 5, offsetY + EXIT);
	cout << "Return to main menu";

		//in cac lua chon cua main mernu
	for (int i = 0; i < options.size(); i++)
	{
		gotoXY(offsetX, offsetY + i);
		cout << i + 1 << ". ";
		gotoXY(offsetX + 5, offsetY + i);
		cout << options[i];
	}
}

int EditMenu::handleInput()
{
	gotoXY(offsetX, offsetY);
	int i = 0;

	while (true)
	{
		char c = _getch();

		if (c == KEY_ENTER)
		{
			break;
		}

		if (c == KEY_DOWN || c == 's')
		{
			if (i == options.size() - 1)
			{
				i = EXIT;
			}
			else if (i == EXIT)
			{
				i = 0;
			}
			else
			{
				i++;
			}
		}

		if (c == KEY_UP || c == 'w')
		{
			if (i == 0)
			{
				i = EXIT;
			}
			else if (i == EXIT)
			{
				i = options.size() - 1;
			}
			else
			{
				i--;
			}
		}

		gotoXY(offsetX, offsetY + i);
	}

	return i;
}

int EditMenu::func()
{
begin:
	display();
	int i = handleInput();
	if (i == EXIT)
	{
		//lua chon luu cac thay doi va thoat
		int k = confirmMenu.func("Do you want to apply all the changes?");
		if (k == 0)
		{
			GameManager::saveData(LIST_HERO);
		}
		return 0;
	}
	else
	{
		//thuc hien cac menu con
		if (i == 0)
		{
			addHeroMenu();
		}
		if (i == 1)
		{
			editHeroMenu();
		}
		if (i == 2)
		{
			removeHeroMenu();
		}
		//quay tro ve menu editHero
		goto begin;
	}
}

void EditMenu::addHeroMenu()
{
	Hero newHero;

	//HIEN THI MENU
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Input the infomation of the new hero:";

	int offsetX = 10;
	int offsetY = 3;

	int spacing = 20;

	string temp;
	float temp2;

	//XU LY
	//nhap cac thong tin cua hero moi
	gotoXY(offsetX, offsetY);
	cout << "- Name:";
	gotoXY(offsetX + spacing, offsetY);
	getline(cin, temp);
	newHero.setName(temp);

	offsetY++;
	gotoXY(offsetX, offsetY);
	cout << "- Attribute:";
	gotoXY(offsetX + spacing, offsetY);
	cin >> temp;
	newHero.setAttribute(temp);

	offsetY++;
	gotoXY(offsetX, offsetY);
	cout << "- HP:";
	gotoXY(offsetX + spacing, offsetY);
	cin >> temp2;
	newHero.setHealth(temp2);

	offsetY++;
	gotoXY(offsetX, offsetY);
	cout << "- ATK:";
	gotoXY(offsetX + spacing, offsetY);
	cin >> temp2;
	newHero.setAtk(temp2);

	offsetY++;
	gotoXY(offsetX, offsetY);
	cout << "- DEF:";
	gotoXY(offsetX + spacing, offsetY);
	cin >> temp2;
	newHero.setDef(temp2);

	offsetY++;
	gotoXY(offsetX, offsetY);
	cout << "- AS:";
	gotoXY(offsetX + spacing, offsetY);
	cin >> temp2;
	newHero.setAs(temp2);

	cin.ignore();

	//xac nhan them hero
	int c = confirmMenu.func("Do you want to add this hero?", newHero);

	if (c == 1)
	{
		return;
	}
	else
	{
		HL.push_back(newHero);
	}
}

void EditMenu::editHeroMenu()
{
	int i = heroMenu.func();

	if (i == EXIT)
	{
		return;
	}

begin:
	//HIEN THI MENU
	system("CLS");
	gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
	cout << "Choose the information you want to edit: ";

	int offsetX = 10;
	int offsetY = 5;

	gotoXY(offsetX + 5, offsetY + EXIT);
	cout << "Return";

	int spacing = 20;

	vector<string> options;
	//danh sach cac lua chon theo ten thong tin cua hero
	options.push_back("Name");
	options.push_back("Attribute");
	options.push_back("HP");
	options.push_back("ATK");
	options.push_back("DEF");
	options.push_back("AS");

	//hien thi cac thong tin cua hero duoc chon
	int tempOffsetY = offsetY;

	gotoXY(offsetX, tempOffsetY);
	cout << "- " << options[0];
	gotoXY(offsetX + spacing, tempOffsetY);
	cout << HL[i].getName();

	tempOffsetY++;
	gotoXY(offsetX, tempOffsetY);
	cout << "- " << options[1];
	gotoXY(offsetX + spacing, tempOffsetY);
	setTextColor(ES.getColorCode(HL[i].getAttribute()));
	cout << HL[i].getAttribute();
	setTextColor(ColorCode_Default);

	tempOffsetY++;
	gotoXY(offsetX, tempOffsetY);
	cout << "- " << options[2];
	gotoXY(offsetX + spacing, tempOffsetY);
	cout << HL[i].getHealth();

	tempOffsetY++;
	gotoXY(offsetX, tempOffsetY);
	cout << "- " << options[3];
	gotoXY(offsetX + spacing, tempOffsetY);
	cout << HL[i].getAtk();

	tempOffsetY++;
	gotoXY(offsetX, tempOffsetY);
	cout << "- " << options[4];
	gotoXY(offsetX + spacing, tempOffsetY);
	cout << HL[i].getDef();

	tempOffsetY++;
	gotoXY(offsetX, tempOffsetY);
	cout << "- " << options[5];
	gotoXY(offsetX + spacing, tempOffsetY);
	cout << HL[i].getAs();


	gotoXY(offsetX, offsetY);
	int j = 0;

	//XU LY
	//xu ly dieu khien di chuyen va lua chon
	while (true)
	{
		char c = _getch();

		if (c == KEY_ENTER)
		{
			break;
		}

		if (c == KEY_DOWN || c == 's')
		{
			if (j == options.size() - 1)
			{
				j = EXIT;
			}
			else if (j == EXIT)
			{
				j = 0;
			}
			else
			{
				j++;
			}
		}

		if (c == KEY_UP || c == 'w')
		{
			if (j == 0)
			{
				j = EXIT;
			}
			else if (j == EXIT)
			{
				j = options.size() - 1;
			}
			else
			{
				j--;
			}
		}

		gotoXY(offsetX, offsetY + j);
	}

	string temp;
	float temp2;

	//xu ly lua chon
	if (j == EXIT)
	{
		return;
	}
	else
	{
		system("CLS");
		//xu ly viec thay doi chi so duoc chon
		if (j == 0) //ten
		{
			gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
			cout << "- Input new Name: ";
			getline(cin, temp);

			int k = confirmMenu.func("Do you want to change the Hero's Name: " + HL[i].getName() + " -> " + temp + "?");
			if (k == 0)
			{
				HL[i].setName(temp);
			}
		}
		if (j == 1) //he (nguyen to)
		{
			gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
			cout << "- Input new Attribute: ";
			cin >> temp;

			int k = confirmMenu.func("Do you want to change the Hero's Attribute: " + HL[i].getAttribute() + " -> " + temp + "?");
			if (k == 0)
			{
				HL[i].setAttribute(temp);
			}
		}
		if (j == 2) //mau (HP)
		{
			gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
			cout << "- Input new HP: ";
			cin >> temp2;
			cin.ignore();

			int k = confirmMenu.func("Do you want to change the Hero's HP: " + to_string(HL[i].getHealth()) + " -> " + to_string(temp2) + "?");
			if (k == 0)
			{
				HL[i].setHealth(temp2);
			}

		}
		if (j == 3) //sat thuong tren don danh (ATK)
		{
			gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
			cout << "- Input new ATK: ";
			cin >> temp2;
			cin.ignore();

			int k = confirmMenu.func("Do you want to change the Hero's HP: " + to_string(HL[i].getAtk()) + " -> " + to_string(temp2) + "?");
			if (k == 0)
			{
				HL[i].setAtk(temp2);
			}
		}
		if (j == 4) //sat thuong giam tren don danh (DEF)
		{
			gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
			cout << "- Input new DEF: ";
			cin >> temp2;
			cin.ignore();

			int k = confirmMenu.func("Do you want to change the Hero's HP: " + to_string(HL[i].getDef()) + " -> " + to_string(temp2) + "?");
			if (k == 0)
			{
				HL[i].setDef(temp2);
			}
		}
		if (j == 5) //toc do danh (AS)
		{
			gotoXY(DEFAULT_OFFSET_X, DEFAULT_OFFSET_Y);
			cout << "- Input new AS: ";
			cin >> temp2;
			cin.ignore();

			int k = confirmMenu.func("Do you want to change the Hero's HP: " + to_string(HL[i].getAs()) + " -> " + to_string(temp2) + "?");
			if (k == 0)
			{
				HL[i].setAs(temp2);
			}
		}

		//quay ve menu sua hero
		goto begin;
	}
}

void EditMenu::removeHeroMenu()
{
	//lua chon hero
	int i = heroMenu.func();

	if (i == EXIT)
	{
		return;
	}

	//xac nhan xoa hero
	int k = confirmMenu.func("Do you really want to remove this hero?", HL[i]);
	if (k == 0)
	{
		HL.erase(HL.begin() + i);
	}
}
