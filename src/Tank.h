#ifndef TANK_H
#define TANK_H

#include "Food.h"

/**
 * virtual虚函数是指一个类中希望重载的成员函数
 * 当你用一个基类指针或引用指向一个继承类对象的时候，调用一个虚函数时, 实际调用的是继承类的版本
*/

class Tank : public GameObject {
public:/*移动*/
    Direction direction;//mod
    bool roll;//mod_rol
    GLfloat speed;/*移动速度*/
    virtual void move(GLfloat x, GLfloat y);
    void do_roll();/*轮子转*/

public:/*发射*/
    bool bullet_enhanced = false;/*子弹加强*/
    float cd_bullet;/*cooldown-time，发射冷却时间*/
    double last_shoot_time;/*上一次发射的时刻*/
    bool cd_bullet_ok(double time_from_init)const;/*检查子弹cd，若能发射返回true*/
    void fire(double current_time);/*回调函数*/

public:/*构造，析构*/
    Tank();
    Tank(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size = glm::vec2(2.0f, 2.0f), GLfloat Speed = 0.05);
    ~Tank();

public:/*绘制*/
    virtual void draw(SpriteRenderer& renderer)const;
private:
    virtual void draw_protect(SpriteRenderer& renderer)const;
    virtual void draw_boom(SpriteRenderer& renderer)const;

public: /*被击中*/
    virtual void get_shot(bool enhanced = false);/*被击中*/
    virtual void level_up() = 0;/*降级，减少血量*/
    virtual void level_down() = 0;/*升级，增加血量*/

public:/*等级*/
    int level = 0;/*等级，血量*/
    int level_max = 2;/*最大等级，最大血量*/

public:
    virtual void init() = 0;

public:/*出生保护*/
    bool protect = 1;/*1表示存在保护罩*/
    bool protect_wink;/*保护闪烁*/
    virtual  void protect_doing();/*操作闪烁*/
    float protect_duration = 5;/*保护持续时间*/
    double protect_start_time;/*保护开始时间*/
    virtual  void protect_start();/*获取保护food*/
public:
    public:/*爆炸动效*/
	bool boom = 0;/*是否绘制爆炸*/
	float boom_duration ;/*爆炸持续时间*/
	double boom_start_time;/*爆炸开始时间*/
	int boom_current_step = 0;/*爆炸阶段，0-5，共6个阶段*/
	virtual void boom_doing();/*进行一个爆炸*/
	virtual void boom_start();/*开始爆炸*/
};

#endif /*PLAYER_H*/
