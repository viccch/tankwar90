//#include <glad/glad.h>
#include <GL/glew.h>

#include <GLFW/glfw3.h>
#include <vector>
#include <tuple>

#include "GameLevel.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Food.h"

#include "../util/ResourceManager.h"
#include "../util/Shader.h"
#include "../util/SpriteRenderer.h"
#include "../util/TextRenderer.h"
#include "../util/MeshRenderer.h"
#include "../util/Sound.h"

enum GameState {
    GAME_WELCOME,
    GAME_CHOOSE,
    GAME_ENTER,
    GAME_WIN,
    GAME_LOSE,
    GAME_PAUSE,
    GAME_EXIT,
    GAME_ERROR
};/*game state*/

class Game {
public:
    bool keys[1024]{};/*按键，初始化置0*/
    GLuint width, height;/*窗口大小*/
    glm::mat4 projection;/*投影矩阵*/

public:
    GameState state;/*游戏状态*/
private:
    enum PlayMode { ONE_PLAYER = 1, TWO_PLAYERS = 2 } play_mode = ONE_PLAYER;/*玩家数量*/
    std::vector<std::string>levels_path;/*关卡加载路径*/
    std::vector<GameLevel>Levels;/*关卡*/
    GameLevel* current_level;/*当前关卡*/
    int level_idx;
    Player *player_1;/*单人或双人*/
    Player *player_2;/*单人或双人*/
    std::vector<Enemy>* enemys;/*敌人坦克*/
    std::vector<Bullet>* bullets;/*发射出的子弹*/
    std::vector<Food>* foods;/*道具*/
    std::vector<GameObject>* tiles;/*障碍物，瓦片,包括砖块，钢铁，水，树，冰等*/
    void next_level();
public:
    Game(GLuint width, GLuint height);
    ~Game();
    void init();
    void update();
    void render()const;
private:
    void obj_move();
    void check_game_state();

    void render_welcome()const;
    void update_welcome();
    void render_game()const;
    void update_game();
public:
};