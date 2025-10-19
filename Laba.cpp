#include "Header.h"

extern HDC hdc;

Location::Location(int InitX, int InitY)
{
	x = InitX;
	y = InitY;
};

Location::~Location()
{
};

int Location::GetX()
{
	return x;
};

int Location::GetY()
{
	return y;
};

Point::Point(int InitX, int InitY) :Location(InitX, InitY)
{
	Region();
};

Point::~Point()
{
};

void Point::SetX(int X)
{
	x = X;
};

void Point::SetY(int Y)
{
	y = Y;
}

void Point::Show()
{
	visible = true;
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, Pen);
	SetPixel(hdc, x, y, RGB(255, 0, 0));		//черный
	SetPixel(hdc, x + 1, y, RGB(255, 0, 0));	// 4 точки для удобства
	SetPixel(hdc, x, y + 1, RGB(255, 0, 0));
	SetPixel(hdc, x + 1, y + 1, RGB(255, 0, 0));
	DeleteObject(Pen);
};

void Point::Hide()
{
	visible = false;
	SetPixel(hdc, x, y, RGB(255, 255, 255));		//белый
	SetPixel(hdc, x + 1, y, RGB(255, 255, 255));	// 4 точки для удобства
	SetPixel(hdc, x, y + 1, RGB(255, 255, 255));
	SetPixel(hdc, x + 1, y + 1, RGB(255, 255, 255));
};

bool Point::isVisible() // проверка точки на видимость
{
	return visible;
};

void Point::MoveTo(int NewX, int NewY) // передвинуть точку
{
	Hide();
	x = NewX;
	y = NewY;
	Region();
	Show();
};

void Point::Region()
{
	heat_box.start_X = x;
	heat_box.end_X = x + 1;
	heat_box.start_Y = y;
	heat_box.end_Y = y + 1;
};
Tower::Tower(int InitX, int InitY, int InitW, int InitH) : Point(InitX, InitY)
{
	width = InitW;
	height = InitH;
	isBroken = false;
	index = 0;
};

Tower::~Tower()
{
};

void Tower::ShowRoof()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // черный цвет
	SelectObject(hdc, Pen);
	POINT vertices[3]; // массив для хранения точек
	vertices[0].x = x + width / 2; // определение координат точек
	vertices[0].y = y - height / 2;
	vertices[1].x = x;
	vertices[1].y = y - height;
	vertices[2].x = x - width / 2;
	vertices[2].y = y - height / 2;
	Polygon(hdc, vertices, 3); // отрисовка крыши башни
	DeleteObject(Pen);
}
void Tower::ShowBody()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 2; // задание координат
	int top = y - height / 2;
	int right = x + width / 2;
	int bottom = y + height / 2;
	Rectangle(hdc, left, top, right, bottom); // отрисовка прямоугольника
	DeleteObject(Pen);
}
void Tower::ShowDoor()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 4; // координаты двери
	int top = y - height / 16 + height / 8;
	int right = x + width / 4;
	int bottom = y + height / 2;
	Rectangle(hdc, left, top, right, bottom); // отрисовка двери
	MoveToEx(hdc, x + width / 6, (top + bottom) / 2, NULL); // двигаемся в координаты ручки
	LineTo(hdc, x + width / 12, (top + bottom) / 2); // отрисовка ручки двери
	DeleteObject(Pen);
}
void Tower::ShowWindow()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 6;
	int top = y - height / 8 - height / 4;
	int right = x + width / 6;
	int bottom = y + height / 8 - height / 4;
	Rectangle(hdc, left, top, right, bottom); // отрисовка прямоугольника
	DeleteObject(Pen);
}

void Tower::HideRoof()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // черный цвет
	SelectObject(hdc, Pen);
	POINT vertices[3]; // массив для хранения точек
	vertices[0].x = x + width / 2; // определение координат точек
	vertices[0].y = y - height / 2;
	vertices[1].x = x;
	vertices[1].y = y - height;
	vertices[2].x = x - width / 2;
	vertices[2].y = y - height / 2;
	Polygon(hdc, vertices, 3); // отрисовка крыши башни
	DeleteObject(Pen);
}
void Tower::HideBody()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 2; // задание координат
	int top = y - height / 2;
	int right = x + width / 2;
	int bottom = y + height / 2;
	Rectangle(hdc, left, top, right, bottom); // отрисовка прямоугольника
	DeleteObject(Pen);
}
void Tower::HideDoor()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 4; // координаты двери
	int top = y - height / 16 + height / 8;
	int right = x + width / 4;
	int bottom = y + height / 2;
	Rectangle(hdc, left, top, right, bottom); // отрисовка двери
	MoveToEx(hdc, x + width / 6, (top + bottom) / 2, NULL); // двигаемся в координаты ручки
	LineTo(hdc, x + width / 12, (top + bottom) / 2); // отрисовка ручки двери
	DeleteObject(Pen);
}
void Tower::HideWindow()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 6;
	int top = y - height / 8 - height / 4;
	int right = x + width / 6;
	int bottom = y + height / 8 - height / 4;
	Rectangle(hdc, left, top, right, bottom); // отрисовка прямоугольника
	DeleteObject(Pen);
}

void Tower::Show()
{
	visible = true;
	ShowBody();
	ShowDoor();
	ShowWindow();
	ShowRoof();
};

void Tower::Hide()
{
	visible = false;
	HideBody();
	HideDoor();
	HideWindow();
	HideRoof();
};

int Tower::GetIndex()
{
	return index;
};

void Tower::Region()
{
	heat_box.start_X = x - width / 2;
	heat_box.end_X = x + width / 2;
	heat_box.start_Y = y - height / 2;
	heat_box.end_Y = y + height / 2;
};

Obstacle::Obstacle(int InitX, int InitY) : Point(InitX, InitY)
{
};

Obstacle::~Obstacle()
{
};

Human::Human(int InitX, int InitY) : Obstacle(InitX, InitY)
{
}

Human::~Human()
{
};

void Human::Show()
{
	visible = true;
	int headRadius = 15;
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, x, y + 5, NULL);
	LineTo(hdc, x, y + 30);

	MoveToEx(hdc, x, y + 5, NULL);
	LineTo(hdc, x - 15, y + 20);

	MoveToEx(hdc, x, y + 5, NULL);
	LineTo(hdc, x + 15, y + 20);

	MoveToEx(hdc, x, y + 30, NULL);
	LineTo(hdc, x - 10, y + 40);

	MoveToEx(hdc, x, y + 30, NULL);
	LineTo(hdc, x + 10, y + 40);

	Ellipse(hdc, x + headRadius, y + headRadius - 10, x - headRadius, y - headRadius - 10);

	MoveToEx(hdc, x - headRadius / 3, y - headRadius, NULL);
	LineTo(hdc, x - headRadius / 4, y - headRadius - 2);

	MoveToEx(hdc, x + headRadius / 3, y - headRadius, NULL);
	LineTo(hdc, x + headRadius / 4, y - headRadius - 2);

	MoveToEx(hdc, x - headRadius / 4, y - 3, NULL);
	LineTo(hdc, x + headRadius / 4, y - 3);

	DeleteObject(Pen);
};

void Human::Hide()
{
	visible = false;
	int headRadius = 15;
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);
	MoveToEx(hdc, x, y + 5, NULL);
	LineTo(hdc, x, y + 30);

	MoveToEx(hdc, x, y + 5, NULL);
	LineTo(hdc, x - 15, y + 20);

	MoveToEx(hdc, x, y + 5, NULL);
	LineTo(hdc, x + 15, y + 20);

	MoveToEx(hdc, x, y + 30, NULL);
	LineTo(hdc, x - 10, y + 40);

	MoveToEx(hdc, x, y + 30, NULL);
	LineTo(hdc, x + 10, y + 40);

	Ellipse(hdc, x + headRadius, y + headRadius - 10, x - headRadius, y - headRadius - 10);

	MoveToEx(hdc, x - headRadius / 3, y - headRadius, NULL);
	LineTo(hdc, x - headRadius / 4, y - headRadius - 2);

	MoveToEx(hdc, x + headRadius / 3, y - headRadius, NULL);
	LineTo(hdc, x + headRadius / 4, y - headRadius - 2);

	MoveToEx(hdc, x - headRadius / 4, y - 3, NULL);
	LineTo(hdc, x + headRadius / 4, y - 3);

	DeleteObject(Pen);
};

void Human::Region()
{
	heat_box.start_X = x - 10;
	heat_box.end_X = x + 10;
	heat_box.start_Y = y + 20;
	heat_box.end_Y = y - 20;
};

Ram::Ram(int InitX, int InitY, int InitWidth, int InitHeight, int InitWheelRadius) : Obstacle(InitX, InitY) {
	width = InitWidth;
	height = InitHeight;
	wheelRadius = InitWheelRadius;
};

Ram::~Ram()
{
};

void Ram::Show() {
	visible = true;
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // Белый цвет
	SelectObject(hdc, Pen);
	Rectangle(hdc, x - width / 2, y + height / 2, x + width + width / 4, y + height / 4);
	DeleteObject(Pen);
	SelectObject(hdc, Pen);
	Ellipse(hdc, x - wheelRadius, y + height / 2 - wheelRadius, x, y + height / 2 + wheelRadius);
	SelectObject(hdc, Pen);
	Ellipse(hdc, x + width - wheelRadius, y + height / 2 - wheelRadius, x + width, y + height / 2 + wheelRadius);
	DeleteObject(Pen);
};

void Ram::Hide() {
	visible = false;
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // Белый цвет
	SelectObject(hdc, Pen);
	Rectangle(hdc, x - width / 2, y + height / 2, x + width + width / 4, y + height / 4);
	DeleteObject(Pen);
	SelectObject(hdc, Pen);
	Ellipse(hdc, x - wheelRadius, y + height / 2 - wheelRadius, x, y + height / 2 + wheelRadius);
	SelectObject(hdc, Pen);
	Ellipse(hdc, x + width - wheelRadius, y + height / 2 - wheelRadius, x + width, y + height / 2 + wheelRadius);
	DeleteObject(Pen);
};

void Ram::Region()
{
	heat_box.start_X = x - width;
	heat_box.end_X = x + width;
	heat_box.start_Y = y - height / 2;
	heat_box.end_Y = y + height / 2;
};

BrokenTower::BrokenTower(int InitX, int InitY, int InitW, int InitH) :Tower(InitX, InitY, InitW, InitH)
{
	isBroken = true;
	index = 1;
};

BrokenTower::~BrokenTower()
{
};

void BrokenTower::ShowBody()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
	SelectObject(hdc, Pen);
	int left = x - width / 2; // задание координат
	int top = y - height / 2;
	int right = x + width / 2;
	int bottom = y + height / 2;
	MoveToEx(hdc, x + width / 2, y - height / 2, NULL);
	LineTo(hdc, left, top);
	LineTo(hdc, left, bottom);
	LineTo(hdc, right, bottom);
	MoveToEx(hdc, x + width / 2, y - height / 2, NULL);
	LineTo(hdc, x + width / 4, y + height / 8);
	LineTo(hdc, right, bottom);
	DeleteObject(Pen);
}

void BrokenTower::HideBody()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255));
	SelectObject(hdc, Pen);
	int left = x - width / 2; // задание координат
	int top = y - height / 2;
	int right = x + width / 2;
	int bottom = y + height / 2;
	MoveToEx(hdc, x + width / 2, y - height / 2, NULL);
	LineTo(hdc, left, top);
	LineTo(hdc, left, bottom);
	LineTo(hdc, right, bottom);
	MoveToEx(hdc, x + width / 2, y - height / 2, NULL);
	LineTo(hdc, x + width / 4, y + height / 8);
	LineTo(hdc, right, bottom);
	DeleteObject(Pen);
}

void BrokenTower::Show()
{
	visible = true;
	ShowDoor();
	ShowWindow();
	ShowRoof();
	ShowBody();
};

void BrokenTower::Hide()
{
	visible = false;
	HideDoor();
	HideWindow();
	HideRoof();
	HideBody();
};

void BrokenTower::Region()
{
	heat_box.start_X = x - 100;
	heat_box.end_X = x + 100;
	heat_box.start_Y = y - 400;
	heat_box.end_Y = y + 200;
};

RepairedTower::RepairedTower(int InitX, int InitY, int InitW, int InitH) : Tower(InitX, InitY, InitW, InitH)
{
	isBroken = false;
	index = 2;
};

RepairedTower::~RepairedTower()
{
};

void RepairedTower::ShowBody()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 2; // задание координат
	int top = y - height / 2;
	int right = x + width / 2;
	int bottom = y + height / 2;
	Rectangle(hdc, left, top, right, bottom); // отрисовка прямоугольника
	Rectangle(hdc, right, top + height / 3, right + height / 3, bottom);
	Rectangle(hdc, right + width / 6, top + height / 2, right + height / 3 - width / 6, bottom - height / 8);
	DeleteObject(Pen);
}

void RepairedTower::HideBody()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 2; // задание координат
	int top = y - height / 2;
	int right = x + width / 2;
	int bottom = y + height / 2;
	Rectangle(hdc, left, top, right, bottom); // отрисовка прямоугольника
	Rectangle(hdc, right, top + height / 3, right + height / 3, bottom);
	Rectangle(hdc, right + width / 6, top + height / 2, right + height / 3 - width / 6, bottom - height / 8);
	DeleteObject(Pen);
}

void RepairedTower::Show()
{
	visible = true;
	ShowBody();
	ShowDoor();
	ShowWindow();
	ShowRoof();
};

void RepairedTower::Hide()
{
	visible = false;
	HideBody();
	HideDoor();
	HideWindow();
	HideRoof();

};

void RepairedTower::Region()
{
	heat_box.start_X = x - 100;
	heat_box.end_X = x + 100;
	heat_box.start_Y = y - 400;
	heat_box.end_Y = y + 200;
};

TowerWithLegs::TowerWithLegs(int InitX, int InitY, int InitW, int InitH) : Tower(InitX, InitY, InitW, InitH)
{
	isBroken = false;
	index = 3;
};

TowerWithLegs::~TowerWithLegs()
{
};

void TowerWithLegs::ShowBody()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 2; // задание координат
	int top = y - height / 2;
	int right = x + width / 2;
	int bottom = y + height / 2;
	Rectangle(hdc, left, top, right, bottom); // отрисовка прямоугольника
	MoveToEx(hdc, x - width / 4, y + height / 2, NULL);
	LineTo(hdc, x - width / 4, y + height);
	MoveToEx(hdc, x + width / 4, y + height / 2, NULL);
	LineTo(hdc, x + width / 4, y + height);
	DeleteObject(Pen);
}

void TowerWithLegs::HideBody()
{
	HPEN Pen = CreatePen(PS_SOLID, 2, RGB(255, 255, 255)); // черный цвет
	SelectObject(hdc, Pen);
	int left = x - width / 2; // задание координат
	int top = y - height / 2;
	int right = x + width / 2;
	int bottom = y + height / 2;
	Rectangle(hdc, left, top, right, bottom); // отрисовка прямоугольника
	MoveToEx(hdc, x - width / 4, y + height / 2, NULL);
	LineTo(hdc, x - width / 4, y + height);
	MoveToEx(hdc, x + width / 4, y + height / 2, NULL);
	LineTo(hdc, x + width / 4, y + height);
	DeleteObject(Pen);
}

void TowerWithLegs::Show()
{
	visible = true;
	ShowBody();
	ShowDoor();
	ShowWindow();
	ShowRoof();
};

void TowerWithLegs::Hide()
{
	visible = false;
	HideBody();
	HideDoor();
	HideWindow();
	HideRoof();
};

void TowerWithLegs::Region()
{
	heat_box.start_X = x - 100;
	heat_box.end_X = x + 100;
	heat_box.start_Y = y - 400;
	heat_box.end_Y = y + 200;
};
