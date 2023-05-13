#ifndef ENEMY_H
#define ENEMY_H

#include "Tank.h"

class Enemy final :public Tank {

public:
    Enemy(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size = glm::vec2(2.0f, 2.0f), GLfloat Speed = 0.05);
    ~Enemy()=default;
    Enemy() :Enemy(nullptr, {}) {};

    virtual void init();
    virtual void level_up() ;
    virtual void level_down() ;
};

#endif /*ENEMY_H*/