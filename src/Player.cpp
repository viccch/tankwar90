#include "Player.h"


Player::Player(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size, GLfloat Speed) :Tank(Tex, Pos, Size, Speed)
{
    init();
}

void Player::init() {
    this->level_max = 2;/*玩家最大等级*/
    this->level = 0;/*玩家初始等级*/
}

void Player::level_up() {
    level++;
    if (level < level_max) {
        //std::string tex_id = "tank_T1_0";
        std::string tex_id = this->texture->name;
        tex_id.back() += 1;

        this->texture = ResourceManager::getTexture(tex_id);
    }
}

void Player::level_down() {
    if (level > 0) {
        level--;
        //std::string tex_id = "tank_T1_0";
        std::string tex_id = this->texture->name;
        tex_id.back() = '0' + level;

        this->texture = ResourceManager::getTexture(tex_id);
    }
    else if (level == 0) {
        // this->IsDestroyed = true;
        this->boom_start();
    }
}