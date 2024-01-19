#include <SDL2/SDL.h>

#ifndef VEC2_HPP
#define VEC2_HPP

namespace engine{

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Directions;

typedef enum {
    X = 0,
    Y = 1
} VECTOR_INDECIES;

class Vec2{
    public:
    long double vec[2];
    long double *x;
    long double *y;
    // in trying to make clean code, I made it disgusting
    Vec2(long double x, long double y){
        vec[X] = x;
        vec[Y] = y;
        this->x = &vec[X];
        this->y = &vec[Y];
    }
    long double& operator[](int index){
        return vec[index];
    }
    Vec2 operator+(Vec2 other){
        return Vec2(vec[X] + other.vec[X], vec[Y] + other.vec[Y]);
    }
    Vec2 operator-(Vec2 other){
        return Vec2(vec[X] - other.vec[X], vec[Y] - other.vec[Y]);
    }
    Vec2 operator*(long double other){
        return Vec2(vec[X] * other, vec[Y] * other);
    }
    Vec2 operator/(long double other){
        return Vec2(vec[X] / other, vec[Y] / other);
    }
    Vec2 operator+=(Vec2 other){
        vec[X] += other.vec[X];
        vec[Y] += other.vec[Y];
        return *this;
    }
    Vec2 operator-=(Vec2 other){
        vec[X] -= other.vec[X];
        vec[Y] -= other.vec[Y];
        return *this;
    }
    Vec2 operator*=(long double other){
        vec[X] *= other;
        vec[Y] *= other;
        return *this;
    }
    Vec2 operator/=(long double other){
        vec[X] /= other;
        vec[Y] /= other;
        return *this;
    }
    bool operator==(Vec2 other){
        return vec[X] == other.vec[X] && vec[Y] == other.vec[Y];
    }
}; 
}

#endif