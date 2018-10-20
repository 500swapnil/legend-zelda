#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y,float z, color_t color,float width, float height, float depth);
    glm::vec3 position;
    float rotation,rotationz;
    char power;
    float width,height,depth;
    void draw(glm::mat4 VP);
    void drawOcean(glm::mat4 VP);
    void set_position(float x, float y);
    double xspeed, yspeed, zspeed;
    void tick();

    bounding_box_t bounding_box();
public:
    VAO *object;
};

class Sail:public Ball {
public:
    Sail() {}
    Sail(float x, float y,float z);
};

class Rock:public Ball {
public:
    Rock() {}
    Rock(float x, float y,float z,color_t color,float height,float width);
};
class CannonBall:public Ball{
public:
    CannonBall() {}
    CannonBall(float x, float y,float z, color_t color,float width);
};

class Monster:public Ball{
public:
    Monster() {}
    Monster(float x, float y, float z,int type);
    void tick(float usery, float userz);
    void draw(glm::mat4 VP);
    int ehealth;
   int type;
    Ball body[6];
    CannonBall head;
};


class Boat:public Ball {
public:
    Boat() {}
    Boat(float x, float y,float z);
    Ball arrowBody;
    Rock arrowHead;
    Sail sail;
    float wind,direction;
    void draw(glm::mat4 VP);
    void tick();
    Monster guy;
};
#endif // BALL_H
