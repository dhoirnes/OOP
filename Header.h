#pragma once

#include <Windows.h>
#include <iostream>

using namespace std;

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)

class Location
{
protected:
	int x;
	int y;
public:
	Location(int InitX, int InitY);
	~Location();
	int GetX();
	int GetY();
};

class Point : public Location
{
protected:
	bool visible;
	struct heatbox
	{
		int start_X, end_X, start_Y, end_Y;
	} heat_box;
public:
	Point(int InitX, int InitY);
	~Point();
	void SetX(int X);
	void SetY(int Y);
	virtual void Show();
	virtual void Hide();
	bool isVisible();
	void MoveTo(int NewX, int NewY);
	virtual void Region();
	const heatbox& get()
	{
		return heat_box;
	};
};

class InterfaceTower
{
	virtual void ShowRoof() = 0;
	virtual void ShowBody() = 0;
	virtual void ShowDoor() = 0;
	virtual void ShowWindow() = 0;

	virtual void HideRoof()	= 0;
	virtual void HideBody()	= 0;
	virtual void HideDoor() = 0;
	virtual void HideWindow() = 0;
	virtual int GetIndex() = 0;
	virtual void Region() = 0;
};

class Tower : public InterfaceTower, public Point
{
protected:
	int width;
	int height;
	bool isBroken;
	int index;
public:
	Tower(int InitX, int InitY, int InitW, int InitH);
	~Tower();
	virtual void Show();
	virtual void Hide();
	virtual int GetIndex();
	virtual void Region();
	virtual void ShowRoof();
	virtual void ShowBody();
	virtual void ShowDoor();
	virtual void ShowWindow();

	virtual void HideRoof();
	virtual void HideBody();
	virtual void HideDoor();
	virtual void HideWindow();
};

class Obstacle : public Point
{
public:
	Obstacle(int InitX, int InitY);
	~Obstacle();
	virtual void Show() = 0;
	virtual void Hide() = 0;
};

class Human : public Obstacle
{
protected:
public:
	Human(int InitX, int InitY);
	~Human();
	virtual void Show();
	virtual void Hide();
	virtual void Region();
};

class Ram : public Obstacle {
protected:
	int width;
	int height;
	int wheelRadius;
public:
	Ram(int InitX, int InitY, int InitWidth, int InitHeight, int InitWheelRadius);
	~Ram();
	virtual void Show();
	virtual void Hide();
	virtual void Region();
};

class BrokenTower : public Tower
{
public:
	BrokenTower(int InitX, int InitY, int InitW, int InitH);
	~BrokenTower();
	virtual void Show();
	virtual void Hide();
	virtual void Region();
	virtual void ShowBody();

	virtual void HideBody();
};

class RepairedTower : public Tower
{
public:
	RepairedTower(int InitX, int InitY, int InitW, int InitH);
	~RepairedTower();
	virtual void Show();
	virtual void Hide();
	virtual void Region();
	virtual void ShowBody();

	virtual void HideBody();
};

class TowerWithLegs : public Tower
{
public:
	TowerWithLegs(int InitX, int InitY, int InitW, int InitH);
	~TowerWithLegs();
	virtual void Show();
	virtual void Hide();
	virtual void Region();
	virtual void ShowBody();

	virtual void HideBody();
};