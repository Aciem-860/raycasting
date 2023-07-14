#include "SDL2/SDL.h"

#pragma once
class Point
{
public:
	Point(double, double);
	~Point();
	double getX() const;
	double getY() const;
	double getLength() const;
	double getSlope() const;
	void setX(double);
	void setY(double);
	Point& operator+=(Point const&);
	Point& operator-=(Point const&);

private:
	// Méthodes
	void computeLength();
	void computeSlope();

	// Attributs
	double _x;
	double _y;
	double _length;
	double _slope;
};

bool operator==(Point const&, Point const&);
Point operator+(Point const&, Point const&);
Point operator-(Point const&, Point const&);