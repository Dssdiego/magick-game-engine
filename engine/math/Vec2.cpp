//
// Created by Diego Santos Seabra on 23/05/20.
//

#include "Vec2.h"

Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

void Vec2::print()
{
    printf("Vec2(x: %f, y: %f)", this->x, this->y);
}
