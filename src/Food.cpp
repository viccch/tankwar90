#include "Food.h"
#include "Player.h"


Food::Food() {}
Food::~Food() {}
Food::Food(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, FOOD e, const glm::vec2& Size, float duration)
    :GameObject(Tex, Pos, Size), food(e), duration(duration)
{
    this->type = OBJ::FOODOBJ;
}

void Food::remove(Tank&tank)const{
      std::cout<<"remove_food" << tank.cd_bullet << std::endl;

  switch (this->food)
        {
        case FOOD::FOOD_BOOM:
             break;

        case FOOD::FOOD_CLOCK:
             break;

        case FOOD::FOOD_GUN:
             break;

        case FOOD::FOOD_IRON:
            break;

        case FOOD::FOOD_PROTECT:
            break;

        case FOOD::FOOD_STAR:
             break;

        case FOOD::FOOD_TANK:
        break;
          
        default:
            break;
        }
}

void Food::use(Tank& tank) const{
    std::cout<<"get_food" << tank.cd_bullet << std::endl;

  switch (this->food)
        {
        case FOOD::FOOD_BOOM:
        
            break;

        case FOOD::FOOD_CLOCK:
             break;

        case FOOD::FOOD_GUN:
             break;

        case FOOD::FOOD_IRON:
            tank.bullet_enhanced = true;
            break;

        case FOOD::FOOD_PROTECT:
            break;

        case FOOD::FOOD_STAR:
             break;

        case FOOD::FOOD_TANK:
            tank.level_up();
        break;
          
        default:
            break;
        }
}