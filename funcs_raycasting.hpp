#ifndef FUNCS_RAYCASTING_HPP
#define FUNCS_RAYCASTING_HPP
#include <vector>
#include "global_vars.hpp"
#include "Point.hpp"
#include "funcs_gfx.hpp"
#pragma once

Point compute_intersection_points();
Point get_intersection_points(Point&, Point&);

#endif