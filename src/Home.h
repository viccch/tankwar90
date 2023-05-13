#ifndef HOME_H
#define HOME_H

#include "GameObject.h"


class Home :public GameObject {
public:
    Home() :Home(nullptr, {}, {}) {};
    ~Home()=default;
    Home(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size);
    virtual void draw(SpriteRenderer& renderer)const;
private:
    virtual void draw_boom(SpriteRenderer& renderer)const;

public:/*爆炸动效*/
    bool boom=false;/*是否绘制爆炸*/
    float boom_duration;/*爆炸持续时间*/
    double boom_start_time;/*爆炸开始时间*/
    int boom_current_step;/*爆炸阶段，0-5，共6个阶段*/
    virtual void boom_doing();/*进行一个爆炸*/
    virtual void boom_start();/*开始爆炸*/

    /*被击中*/
    virtual void get_shot(bool enhanced);
};


#endif/*HOME_H*/