#include "Enemy.h"

Enemy::Enemy(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size, GLfloat Speed) :Tank(Tex, Pos, Size, Speed)
{
    init();
}

void Enemy::init() {
    this->level_max = 0;//3
    this->level = this->level_max;
    this->cd_bullet *= 2;
}

void Enemy::level_up() {
    level++;
    if (level < level_max) {
        //std::string tex_id = "tank_T1_0";
        std::string tex_id = this->texture->name;
        tex_id.back() += 1;

        this->texture = ResourceManager::getTexture(tex_id);
    }
}

void Enemy::level_down() {
    if (level > 0) {
        level--;

        //std::string tex_id = "tank_T1_0";
        std::string tex_id = this->texture->name;
        tex_id[6] = '1' + level;
        this->texture = ResourceManager::getTexture(tex_id);
    }
    else if (level == 0) {
        // this->IsDestroyed = true;
        this->boom_start();
    }
}