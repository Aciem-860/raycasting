#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "Player.h"
#include <cstdio>
#include <iostream>

using namespace std;

Player::Player(double x, double y, int fov) {
	_position = new Point(x, y);
	_direction = new Point(DIR_LENGTH, 0);
	_fov = new Point(0, fov);
	_alpha = 0;

	_rot[0][0] = 0;
	_rot[0][1] = 0;
	_rot[1][0] = 0;
	_rot[1][1] = 0;
}

Player::~Player() {
	delete _position;
	delete _direction;
	delete _fov;
}

Point* Player::get_pos() {
	return _position;
}

Point* Player::get_dir() {
	return _direction;
}

Point* Player::get_fov() {
	return _fov;
}

int Player::get_alpha() {
	return _alpha;
}

void Player::move(Point& dir) {
	//*_position += dir; // <-- Pour le mouvement au clavier
	_position->setX(dir.getX());
	_position->setY(dir.getY());
}

void Player::rotate(int alpha) {
	_alpha = alpha;
	update();
}

void Player::update() {
	double rad = _alpha * M_PI / 180;
	_rot[0][0] =  cos(rad);
	_rot[0][1] = -sin(rad);
	_rot[1][0] =  sin(rad);
	_rot[1][1] =  cos(rad);

	*_direction *= _rot;
	*_fov *= _rot;
}

#endif