#include "Home.h"

Home::Home(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size)
    :GameObject(Tex, Pos, Size)
{
    this->type = OBJ::HOME;
    this->IsDestroyed = false;
    this->boom = false;
    this->boom_start_time = 0.0;
    this->boom_current_step = 0;
    this->boom_duration = 3.0f;
}

void Home::draw(SpriteRenderer& renderer)const
{
    renderer.draw_common(this->texture, this->pos, this->size);

    if (boom) {
        this->draw_boom(renderer);
    }
}

void Home::draw_boom(SpriteRenderer& renderer)const {
    if (this->boom) {
        renderer.draw_common(ResourceManager::getTexture("boom_dynamic"), this->pos, this->size, glm::vec4(6, 1, this->boom_current_step, 0));
    }
}


void Home::boom_start() {
    boom = true;
    boom_start_time = get_time_from_init();
}

void Home::boom_doing() {
    double current_time = get_time_from_init();
    if (boom_start_time + boom_duration < current_time) {
        boom = false;/*时间到，停止绘制*/
        IsDestroyed = true;
    }
    else {
        boom_current_step = (int)((current_time - boom_start_time) / boom_duration * 6);
    }
}



/*被击中*/
void Home::get_shot(bool enhanced) {
    if (!IsDestroyed)
        this->boom_start();
}
