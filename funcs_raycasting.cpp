#ifndef FUNC_RAYCASTING_CPP
#define FUNC_RAYCASTING_CPP
#include "funcs_raycasting.hpp"

using namespace std;

Point compute_intersection_points(Point * origin, Point * target) {
    vector<Point> pts = vector<Point>();
    pts.push_back(*origin);
    Point p = Point();
    bool quit = false;
    bool intersect = false;

    Point dir = *target - *origin;

    while (!quit) {
        p = get_intersection_points(pts.back(), dir);
        // On vérifie que le point regardé est bien entre le carré vert et le carré rouge
        quit = !((p.getX() < origin->getX() && p.getX() > target->getX()) || ((p.getX() > origin->getX() && p.getX() < target->getX())));
        int x = p.getX();
        int y = p.getY();

        x /= GRID_W;
        y /= GRID_H;

        if (int(p.getX()) % GRID_W == 0)
            x = x - (dir.getX() < 0 ? 1 : 0);
        if (int(p.getY()) % GRID_H == 0)
            y = y - (dir.getY() < 0 ? 1 : 0);

        intersect = (map_array[y][x] != 0) ? true : false;

        if (intersect) {
            quit = true;
            pts.push_back(p);
        }
        if (!quit)
            pts.push_back(p);
    }

    if (intersect)
        return p;
}


// Donne les points d'intersection avec la grille (pas avec les blocs !!)
Point get_intersection_points(Point& point, Point& dir) {
    double dx, dy;

    dx = int(point.getX()) % GRID_W; // le pas unitaire en x
    if (dx == 0)
        dx = GRID_W;

    dy = int(point.getY()) % GRID_H; // le pas unitaire en y
    if (dy == 0)
        dy = GRID_H;

    if (dir.getX() > 0 && dx != GRID_W)
        dx = GRID_W - dx;

    if (dir.getY() > 0 && dy != GRID_H)
        dy = GRID_H - dy;

    double lx = dx * sqrt(1 + 1 / pow(dir.getSlope(), 2));
    double ly = dy * sqrt(1 + pow(dir.getSlope(), 2));

    dx = dx * ((dir.getX() < 0) ? -1 : 1);
    dy = dy * ((dir.getY() < 0) ? -1 : 1);

    Point intersect = Point(0, 0);

    if (lx < ly) {
        intersect.setX(point.getX() + dx);
        intersect.setY(point.getY() + dx / dir.getSlope());
    }
    else {
        intersect.setX(point.getX() + dy * dir.getSlope());
        intersect.setY(point.getY() + dy);
    }

    return intersect;
}

#endif