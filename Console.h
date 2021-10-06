#pragma once

#include <stdio.h>
#include <conio.h>
#include <Windows.h>

//ma mau
#define ColorCode_Black			0
#define ColorCode_DarkBlue		1
#define ColorCode_DarkGreen		2
#define ColorCode_DarkCyan		3
#define ColorCode_DarkRed		4
#define ColorCode_DarkPink		5
#define ColorCode_DarkYellow	6
#define ColorCode_DarkWhite		7
#define ColorCode_Grey			8
#define ColorCode_Blue			9
#define ColorCode_Green			10
#define ColorCode_Cyan			11
#define ColorCode_Red			12
#define ColorCode_Pink			13
#define ColorCode_Yellow		14
#define ColorCode_White			15

#define ColorCode_Default		7

//ma cac phim
#define KEY_UP		72
#define KEY_DOWN	80
#define KEY_LEFT	75
#define KEY_RIGHT	77
#define KEY_ENTER	13

//di den toa do (x, y)
void gotoXY(int x, int y);
//doi mau chu
void setTextColor(int _color);
//khoa kich thuoc cua console
void setFixedConsoleSize();