#include "GameObject.h"

double get_time_from_init() {
    return glfwGetTime();
}


GameObject::GameObject() {
    this->IsDestroyed = false;
}
GameObject::GameObject(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size)
    :pos(Pos), size(Size), texture(Tex)
{
    this->IsDestroyed = false;
    // this->IsSolid = true;
}

GameObject ::~GameObject() {};


void  GameObject::draw(SpriteRenderer& renderer)const {
    // renderer.drawSprite(this->texture, this->pos, this->size);
    renderer.draw_common(this->texture, this->pos, this->size);
}

std::vector<glm::vec2> GameObject::get_box()const {
    return {
        pos,                        /*left_bottom*/
        pos + glm::vec2(size.x,0),  /*right_bottom*/
        pos + size,                 /*right_top*/
        pos + glm::vec2(0,size.y)   /*left_top*/
    };
}

/*被bullet击中*/
void GameObject::get_shot(bool enhanced) {

    switch (this->type)
    {
    case OBJ::BULLET: 
    case OBJ::HOME:
    case OBJ::BRICK:
        this->IsDestroyed = true;
        break;
    case OBJ::IRON:
        if (enhanced)
            this->IsDestroyed = true;
        else   
            this->IsDestroyed = false;
        break;
    case OBJ::DEFAULT:
    case OBJ::RIVER:
    case OBJ::TREE:
    case OBJ::ICE:
    default:
        break;
    }
}

int get_rand_int(int left, int right) {
    /*随机数*/
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rand_engine(seed);
    std::uniform_int_distribution<unsigned> int_rand(left, right); /*产生随机数*/
    return int_rand(rand_engine);
}

float get_rand_real(float left, float right) {
    /*随机数*/
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rand_engine(seed);
    std::uniform_real_distribution<float> real_rand(left, right);  /*产生随机数*/
    return real_rand(rand_engine);
}

