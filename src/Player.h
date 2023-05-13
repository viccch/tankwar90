#ifndef PLAYER_H
#define PLAYER_H

#include "Tank.h"

class Player final :public Tank {
public:
    Player(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size = glm::vec2(2.0f, 2.0f), GLfloat Speed = 0.05);
    ~Player()=default;
    Player() :Player(nullptr, {}) {};
    virtual void init();
    virtual void level_up();/*升级，增加血量*/
    virtual void level_down();/*降级，减少血量*/
};


#endif /*PLAYER_H*/