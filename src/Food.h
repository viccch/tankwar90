#ifndef FOOD_H
#define FOOD_H

#include "GameObject.h"

class Tank;

enum FOOD {
    FOOD_NONE = 0,
    FOOD_BOOM,
    FOOD_CLOCK,
    FOOD_GUN,
    FOOD_IRON,
    FOOD_PROTECT,
    FOOD_STAR,
    FOOD_TANK
};

class Food :public GameObject {
public:
    FOOD food;/*food种类枚举*/
    float duration;/*持续时间*/

public:
    Food() :Food(nullptr, {}, {}){};
    ~Food()=default;
    Food(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, FOOD e, const glm::vec2& Size = glm::vec2(1.5f, 1.5f), float duration = 20.0f);
};

#endif /*FOOD_H*/