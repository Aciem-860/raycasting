#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Point.hpp"

#define DIR_LENGTH 1000

#pragma once

class Player
{
public:
	Player(double, double, int);
	~Player();

	Point* get_pos();
	Point* get_dir();
	Point* get_fov();
	int get_alpha();

	void move(Point&);
	void rotate(int);

private:
	void update(); // permet de mettre à jour toutes les données

	Point* _position; // position du joueur
	Point* _direction; // direction de la vue
	Point* _fov; // FoV : toujours perpendiculaire à direction
	int _alpha; // angle d'inclinaison par rapport l'horizontal (sens trigo.)
	double _rot[2][2];
};

#endif