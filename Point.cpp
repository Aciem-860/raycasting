#include "Point.h"
#include "SDL2/SDL.h"
#include <iostream>
#include <cmath>

using namespace std;

Point::Point(Sint32 x, Sint32 y) : _x(x), _y(y) { }

Point::~Point() { }

Sint32 Point::getX() const {
	return _x;
}

Sint32 Point::getY() const {
	return _y;
}

Sint32 Point::getLength() const {
	return _length;
}

double Point::getSlope() const {
	return _slope;
}

void Point::computeLength() {
	_length = sqrt(_x * _x + _y * _y);
}

void Point::computeSlope() {
	double x = _x;
	double y = _y;
	if (_y != 0)
		_slope = x / y;
}

void Point::setX(Sint32 x) {
	_x = x;
	computeLength();
	computeSlope();
}

void Point::setY(Sint32 y) {
	_y = y;
	computeLength();
	computeSlope();
}

Point& Point::operator+=(Point const& p) {
	setX(getX() + p.getX());
	setY(getY() + p.getY());
	return *this;
}

Point& Point::operator-=(Point const& p) {
	setX(getX() - p.getX());
	setY(getY() - p.getY());
	return *this;
}


bool operator==(Point const& p1, Point const& p2) {
	return (p1.getX() == p2.getX() && p2.getY() == p2.getY());
}

Point operator+(Point const& p1, Point const& p2) {
	Point p3 = Point(p1);
	p3 += p2;
	return p3;
}

Point operator-(Point const& p1, Point const& p2) {
	Point p3 = Point(p1);
	p3 -= p2;
	return p3;
}