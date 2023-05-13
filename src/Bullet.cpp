#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, Direction direction, bool from_player, GLfloat Speed, const glm::vec2& Size) :
    GameObject(Tex, Pos, Size), from_player(from_player), direction(direction), speed(Speed)
{
    this->IsDestroyed = false;
    this->type = OBJ::BULLET;
    this->enhanced = false;
}

void Bullet::get_shot(bool enhanced) {
    this->IsDestroyed = true;
}

void Bullet::move() {
    switch (this->direction)
    {
    case Direction::UP:
        this->pos += glm::vec2(0, this->speed);
        break;
    case Direction::DOWN:
        this->pos += glm::vec2(0, -this->speed);
        break;
    case Direction::LEFT:
        this->pos += glm::vec2(-this->speed, 0);
        break;
    case Direction::RIGHT:
        this->pos += glm::vec2(this->speed, 0);
        break;

    default:
        break;
    }
}
