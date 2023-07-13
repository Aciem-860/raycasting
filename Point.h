#include "SDL2/SDL.h"

#pragma once
class Point
{
public:
	Point(Sint32, Sint32);
	~Point();
	Sint32 getX() const;
	Sint32 getY() const;
	Sint32 getLength() const;
	double getSlope() const;
	void setX(Sint32);
	void setY(Sint32);
	Point& operator+=(Point const&);
	Point& operator-=(Point const&);

private:
	// Méthodes
	void computeLength();
	void computeSlope();

	// Attributs
	Sint32 _x;
	Sint32 _y;
	Sint32 _length;
	double _slope;
};

bool operator==(Point const&, Point const&);
Point operator+(Point const&, Point const&);
Point operator-(Point const&, Point const&);