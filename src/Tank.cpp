
#include "Tank.h"

Tank::Tank(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size, GLfloat Speed)
    :GameObject(Tex, Pos, Size), speed(Speed)
{
    this->IsDestroyed = false;

    this->direction = Direction::UP;/*初始方向*/
    this->roll = 0;/*初始轮子*/
    this->cd_bullet = 0.5f;/*0.5s，cd*/
    this->last_shoot_time = 0.0f;
    this->type = OBJ::TANK;

    /*爆炸动画*/
    this->boom = false;
    this->boom_duration = 0.4f;/*爆炸时间1s*/
    this->boom_start_time = 0.0;
    this->boom_current_step = 0;

    /*出生保护动画*/
    this->protect = true;
    this->protect_duration = 5.0f;/*5s*/
    this->protect_start_time = get_time_from_init();
    this->protect_wink = false;
}

void Tank::draw_boom(SpriteRenderer& renderer)const {
    if (this->boom)
        renderer.draw_common(ResourceManager::getTexture("boom_static"), this->pos, this->size, glm::vec4(1, 1, 0, 0));
}

void Tank::draw(SpriteRenderer& renderer) const {
    renderer.draw_common(this->texture, this->pos, this->size, glm::vec4(2, 4, this->roll, this->direction));

    if (this->boom)
        this->draw_boom(renderer);
    if (this->protect)
        this->draw_protect(renderer);
}
void Tank::draw_protect(SpriteRenderer& renderer)const {
    if (this->protect)
        renderer.draw_common(ResourceManager::getTexture("protect"), this->pos, this->size, glm::vec4(2, 1, this->protect_wink, 0));
}

void Tank::move(GLfloat x, GLfloat y)
{
    this->pos.x += x;
    this->pos.y += y;
}

void Tank::do_roll() {
    if (this->roll)this->roll = false;
    else this->roll = true;
}

void Tank::protect_doing() {
    double current_time = get_time_from_init();
    if (protect_start_time + protect_duration < current_time) {
        protect = false;/*时间到*/
    }
    else {
        /*若每秒60个tick，每个tick约0.16秒，*/
        int step = (int)((current_time - protect_start_time) / 0.0167);
        if (step % 8 == 0) {/*每8tick渲染一次*/
            if (this->protect_wink)
                this->protect_wink = false;
            else
                protect_wink = true;
        }
    }
}

void Tank::protect_start() {
    protect = true;
    protect_start_time = get_time_from_init();
}

/*回调函数*/
Bullet Tank::fire() {
    last_shoot_time = get_time_from_init();/*记录此次开火的时刻*/
    Bullet bullet(nullptr, pos, direction, false);
    bullet.pos += this->size * 0.5f - bullet.size * 0.5f;
    bullet.enhanced = bullet_enhanced;/*碎铁*/

    switch (direction) {
    case Direction::UP:
        bullet.texture = ResourceManager::getTexture("bullet_up");
        break;
    case Direction::DOWN:
        bullet.texture = ResourceManager::getTexture("bullet_down");
        break;
    case Direction::LEFT:
        bullet.texture = ResourceManager::getTexture("bullet_left");
        break;
    case Direction::RIGHT:
        bullet.texture = ResourceManager::getTexture("bullet_right");
        break;
    default:
        break;
    }

    return bullet;
}

bool Tank::cd_bullet_ok(double time_from_init)const
{
    return  cd_bullet + last_shoot_time < time_from_init;
}

/*被击中*/
void Tank::get_shot(bool enhanced) {
    this->level_down();
}

void Tank::boom_start() {
    boom = true;
    boom_start_time = get_time_from_init();

    this->speed = 0;
}

void Tank::boom_doing() {
    double current_time = get_time_from_init();
    if (boom_start_time + boom_duration < current_time) {
        boom = false;/*时间到，停止绘制*/
        IsDestroyed = true;
    }
    else {
        boom_current_step = (int)((current_time - boom_start_time) / boom_duration * 6);
    }
}
