#include <windows.h>
#include <iostream>
#include "Header.h"
using namespace std;

HDC hdc;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
void check_coll(Tower*& cur, Obstacle* arr_obs[], Tower* matrix[4][2]);
bool checkCollision(Tower* cur, Obstacle* arr_obs[], int& collidedIndex);

HWND GetConsoleWindow() {
	WCHAR str[128];
	WCHAR title[] = L"Console Window";

	GetConsoleTitle(str, sizeof(str) / sizeof(str[0])); // Получить текущий заголовок окна
	SetConsoleTitle(title); // Установить новый заголовок окна
	Sleep(100); // Ждем изменения заголовка окна (100 мс)

	HWND hwnd = FindWindow(NULL, title); // Определяем дескриптор окна

	SetConsoleTitle(str); // Возвращаем прежний заголовок

	return hwnd; // Вернуть дескриптор окна
}

bool checkCollision(Tower* cur, Obstacle* arr_obs[], int& collidedIndex) {
	for (int j = 0; j < 2; ++j) {
		if (arr_obs[j]->isVisible()) { // если объект видимый
			if (cur->get().end_X > arr_obs[j]->get().start_X // проверка коллизии
				&& cur->get().start_X < arr_obs[j]->get().end_X
				&& cur->get().end_Y > arr_obs[j]->get().start_Y
				&& cur->get().start_Y < arr_obs[j]->get().end_Y) {
				collidedIndex = j;
				return true;
			}
		}
	}
	return false;
}

void check_coll(Tower*& cur, Obstacle* arr_obs[], Tower* matrix[4][2]) {
	int recent_y = cur->GetY(), recent_x = cur->GetX();
	int collidedIndex;

	if (checkCollision(cur, arr_obs, collidedIndex)) {
		if (matrix[cur->GetIndex()][collidedIndex] == nullptr) {
			cur->MoveTo(recent_x, recent_y);
		}
		else {
			cur->Hide();
			arr_obs[collidedIndex]->Hide();
			matrix[cur->GetIndex()][collidedIndex]->MoveTo(cur->GetX(), cur->GetY());
			cur = matrix[cur->GetIndex()][collidedIndex];
			cur->Show();
		}
	}
	else {
		recent_x = cur->GetX();
		recent_y = cur->GetY();
	}
}

int main()
{
	int x0 = 500; // координаты объекта
	int y0 = 300;
	int width0 = 200; // ширина и высота объекта
	int height0 = 400;
	int wheel0 = 50;
	int collideRam = 0;
	int collideHuman = 0;
	HWND hwnd = GetConsoleWindow(); // получение дескриптора окна

	Tower ATower(x0 - 200, y0+200, width0, height0);
	Point APoint(x0, y0);
	Human AHuman(x0 + 400, y0);
	Ram ARam(x0 + 200, y0, width0, height0, wheel0);
	BrokenTower ABrokenTower(x0+500, y0, width0, height0);
	RepairedTower ARepairedTower(x0, y0, width0, height0);
	TowerWithLegs ATowerWithLegs(x0, y0, width0, height0);


	Tower* arr_tower[4]; // состояния башни
	arr_tower[0] = &ATower; // обычная башня
	arr_tower[1] = &ABrokenTower; // сломанная башня
	arr_tower[2] = &ARepairedTower; // восстановленная башня
	arr_tower[3] = &ATowerWithLegs; // башня с ногами

	Obstacle* arr_obs[3]; // коллизии
	arr_obs[0] = &ARam; // таран
	arr_obs[1] = &AHuman; // человек

	Tower* matrix[4][2] = {			//Таран					//Человек
		/*Tower*/					{arr_tower[1],				0,},
		/*Broken_Tower*/			{0,						arr_tower[3]},
		/*Repaired_Tower*/			{arr_tower[1],			arr_tower[0]},
		/*TowerWithLegs*/			{arr_tower[0],			arr_tower[2] }
	};

	Tower* curTower = &ATower;

	if (hwnd != NULL)
	{
		hdc = GetWindowDC(hwnd); // получение контекста
		if (hdc != 0)
		{
			while (!KEY_DOWN(VK_ESCAPE))
			{
				if (KEY_DOWN(51))
				{
					APoint.Show();
				}
				if (KEY_DOWN(54))
				{
					ARam.Show();
				}
				if (KEY_DOWN(52))
				{
					APoint.Hide();
				}
				if (KEY_DOWN(53))
				{
					AHuman.Show();
				}
				if (KEY_DOWN(65))
				{
					APoint.MoveTo(APoint.GetX() - 1, APoint.GetY());
					Sleep(1);
				}
				if (KEY_DOWN(83))
				{
					APoint.MoveTo(APoint.GetX(), APoint.GetY() + 1);
					Sleep(1);
				}
				if (KEY_DOWN(68))
				{
					APoint.MoveTo(APoint.GetX() + 1, APoint.GetY());
					Sleep(1);
				}
				if (KEY_DOWN(87))
				{
					APoint.MoveTo(APoint.GetX(), APoint.GetY() - 1);
					Sleep(1);
				}

				if (KEY_DOWN(49))
				{
					curTower->Show();
				}
				if (KEY_DOWN(50))
				{
					curTower->Hide();
				}
				if (KEY_DOWN(37))
				{
					curTower->MoveTo(curTower->GetX() - 1, curTower->GetY());
					check_coll(curTower, arr_obs, matrix);
				}
				if (KEY_DOWN(38))
				{
					curTower->MoveTo(curTower->GetX(), curTower->GetY() - 1);
					check_coll(curTower, arr_obs, matrix);
				}
				if (KEY_DOWN(39))
				{
					curTower->MoveTo(curTower->GetX() + 1, curTower->GetY());
					check_coll(curTower, arr_obs, matrix);
				}
				if (KEY_DOWN(40))
				{
					curTower->MoveTo(curTower->GetX(), curTower->GetY() + 1);
					check_coll(curTower, arr_obs, matrix);
				}
			}
		}
	}
	ReleaseDC(hwnd, hdc);
	return 0;
}