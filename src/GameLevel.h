#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Food.h"
#include "Home.h"

class GameLevel {

public:
  static GameLevel Load(const GLchar* file);
  void Clear();

public:
  Player player_1;/*单人或双人*/
  Player player_2;/*单人或双人*/
  std::vector<Enemy> enemys; /*敌人坦克*/
  std::vector<Bullet>bullets;/*子弹*/
  std::vector<Food>foods;/*food*/
  std::vector<GameObject> tiles;/*障碍*/
  Home home;/*home*/
  enum LevelState { LEVEL_ON, LEVEL_WIN, LEVEL_LOSE, }state;/**/

public:
  ~GameLevel();/*若私有析构函数，将只能由new构造函数*/
  void Draw(SpriteRenderer& renderer)const;/*renderer绘制*/
  void create_enemy();/*生成enemy*/
  void create_food();/*产生food*/
  bool create_food_ok();
  void enemy_die();/*敌人减员*/
  void win();/*通过本关卡*/
  void lose();/*失败*/
  int get_enemys_remain();

  GameLevel(GameLevel&&) = default;
private:
  GameLevel();/*私有默认构造函数，只允许使用静态函数构建和拷贝构建*/
  int num_columns = 26;/*场地尺寸*/
  int num_rows = 26;/*场地尺寸*/
  int enemy_nums;        /* 本关卡敌人数量*/
  int enemy_survive_max; /*场上最多同时存在的敌人数量*/
  std::vector<glm::vec2> enemy_born_pos; /*敌人出生点*/

  int enemy_surviving; /*场上存在的敌人数量*/
  int enemy_created;   /*已经出生的敌人数量*/
};

#endif /*GAMELEVEL_H*/
