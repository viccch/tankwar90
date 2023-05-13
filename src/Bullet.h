#ifndef BULLET_H
#define BULLET_H

#include <vector>
#include "GameObject.h"



class Bullet :public GameObject {

public:
    bool from_player;/*0:enemy，1:player*/
    Direction direction;/*方向，mod*/
    GLfloat speed;/*速度*/
    bool enhanced=false;//增强的子弹，可击穿iron

public:
    Bullet() :Bullet(nullptr, {}, {}, {}) {};
    ~Bullet()=default;
    Bullet(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, Direction direction, bool from_player, GLfloat Speed = 0.15f, const glm::vec2& Size = glm::vec2(0.5f, 0.5f));

    virtual void move();
    virtual void get_shot(bool enhanced = false);
};


#endif /*BULLET_H*/
