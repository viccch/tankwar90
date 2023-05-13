#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"

class Player final :public Tank {
public:
    Player(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size = glm::vec2(2.0f, 2.0f), GLfloat Speed = 0.05);
    ~Player();
    Player();
    virtual void init();

    virtual void level_up() ;
    virtual void level_down() ;

};


#endif /*PLAYER_H*/