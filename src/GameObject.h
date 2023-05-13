

#ifndef GAMEOBJECT_h
#define GAMEOBJECT_h

#include <chrono>
#include <random>
#include <vector>
// #include <glad/glad.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../util/ResourceManager.h"
#include "../util/Shader.h"
#include "../util/SpriteRenderer.h"
#include "../util/Texture2D.h"
#include "../util/Direction.h"

int get_rand_int(int left, int right);/*返回一个随机整数*/
float get_rand_real(float left, float right);/*返回一个随机实数*/
double get_time_from_init();/*返回开始初始化到当前的时间间隔*/

/*障碍物类*/
enum OBJ
{
	DEFAULT = 0,
	HOME,
	BRICK,
	IRON,
	RIVER,
	TREE,
	ICE,

	TANK,
	BULLET,
	FOODOBJ
};

class GameObject {
public:
	glm::vec2 pos;/*left,bottom*/
	glm::vec2 size;/*width,height*/
	std::shared_ptr<Texture2D> texture;/**/
	bool IsDestroyed;/**/
	OBJ type;/**/

public:
	GameObject() :GameObject(nullptr, {}, {}) {};
	GameObject(std::shared_ptr<Texture2D> Tex, const glm::vec2& Pos, const glm::vec2& Size);
	virtual  ~GameObject()=default;
	virtual void draw(SpriteRenderer& renderer)const;
	virtual void get_shot(bool enhanced = false);/*被击中*/
};

#endif