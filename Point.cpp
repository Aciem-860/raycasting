#ifndef POINT_CPP
#define POINT_CPP

#include "Point.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Point::Point() : _x(0), _y(0) {
	computeLength();
	computeSlope();
}

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

Point& Point::operator*=(double const mat[2][2]) {
	double x = getX();
	double y = getY();

	setX(x * mat[0][0] + y * mat[0][1]);
	setY(x * mat[1][0] + y * mat[1][1]);

	return *this;
}

Point& Point::operator*=(double const& scalar) {
	setX(scalar * getX());
	setY(scalar * getY());

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

Point operator*(Point const& p, double const rot[2][2]) {
	Point _p = Point(p);
	_p *= rot;
	return _p;
}

Point operator*(double const& scalar, Point const & p) {
	Point _p = Point(p);
	_p *= scalar;
	return _p;
}

#endif