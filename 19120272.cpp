#include <iostream>
#include "GameComponents.h"
#include "GameManager.h"
#include "Console.h"

using namespace std;

int main()
{
	setFixedConsoleSize();
	GameManager::loadLog(LOG_FILE);
	
	GameManager::login();

	while (true)
	{
		GameManager::loadData(LIST_HERO);
		mainMenu.func();
	}

	return 0;
}
