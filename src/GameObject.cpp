#include "GameObject.h"

double get_time_from_init() {
    return glfwGetTime();
}

GameObject::GameObject(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size)
    :pos(Pos), size(Size), texture(Tex)
{
    this->IsDestroyed = false;
    this->type = OBJ::DEFAULT;
}

void  GameObject::draw(SpriteRenderer& renderer)const {
    renderer.draw_common(this->texture, this->pos, this->size);
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
    int seed =(int) std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rand_engine(seed);
    std::uniform_int_distribution<unsigned> int_rand(left, right); /*产生随机数*/
    return int_rand(rand_engine);
}

float get_rand_real(float left, float right) {
    /*随机数*/
    int seed =(int) std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine rand_engine(seed);
    std::uniform_real_distribution<float> real_rand(left, right);  /*产生随机数*/
    return real_rand(rand_engine);
}