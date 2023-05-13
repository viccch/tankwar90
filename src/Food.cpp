#include "Food.h"
#include "Player.h"

Food::Food(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, FOOD e, const glm::vec2& Size, float duration)
    :GameObject(Tex, Pos, Size), food(e), duration(duration)
{
    this->IsDestroyed = false;
    this->type = OBJ::FOODOBJ;
}
