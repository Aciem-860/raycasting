#include "Point.h"
#include "SDL2/SDL.h"
#include <iostream>
#include <cmath>

using namespace std;

Point::Point(double x, double y) : _x(x), _y(y) {
	computeLength();
	computeSlope();
}

Point::~Point() { }

double Point::getX() const {
	return _x;
}

double Point::getY() const {
	return _y;
}

double Point::getLength() const {
	return _length;
}

double Point::getSlope() const {
	return _slope;
}

void Point::computeLength() {
	_length = sqrt(_x * _x + _y * _y);
}

void Point::computeSlope() {
	if (_y != 0)
		_slope = _x / _y;
}

void Point::setX(double x) {
	_x = x;
	computeLength();
	computeSlope();
}

void Point::setY(double y) {
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