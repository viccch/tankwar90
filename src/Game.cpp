#include "Game.h"

TextRenderer* Text;
// SpriteRenderer* spriteRenderer;
MeshRenderer* meshRenderer;
SpriteRenderer* commonRenderer;
SoundEngine* soundEngine;

Game::Game(GLuint width, GLuint height) {
    this->width = width;
    this->height = height;
    this->current_level = nullptr;
    this->projection = glm::mat4(1.0f);
}

Game::~Game() {
    delete Text;
    // delete spriteRenderer;
    delete meshRenderer;
    delete commonRenderer;
    delete soundEngine;
}

void Game::init() {
    // load shader
    ResourceManager::loadShader("../resource/shader/text_vs.glsl", "../resource/shader/text_fs.glsl", nullptr, "text");
    // ResourceManager::loadShader("../resource/shader/sprite_vs.glsl", "../resource/shader/sprite_fs.glsl", nullptr, "sprite");
    ResourceManager::loadShader("../resource/shader/mesh_vs.glsl", "../resource/shader/mesh_fs.glsl", nullptr, "mesh");
    ResourceManager::loadShader("../resource/shader/common_vs.glsl", "../resource/shader/common_fs.glsl", nullptr, "common");

    projection = glm::ortho(0.0f, 26.0f * ((float)width / (float)height), 0.0f, 26.0f);
    // ResourceManager::getShader("sprite")->use().setMatrix4("proj", projection);
    ResourceManager::getShader("mesh")->use().setMatrix4("proj", projection);
    ResourceManager::getShader("common")->use().setMatrix4("proj", projection);

    // load textures
    ResourceManager::loadTexture("../resource/image/tank_T1_0.png", GL_TRUE, "tank_T1_0");
    ResourceManager::loadTexture("../resource/image/tank_T1_1.png", GL_TRUE, "tank_T1_1");
    ResourceManager::loadTexture("../resource/image/tank_T1_2.png", GL_TRUE, "tank_T1_2");
    ResourceManager::loadTexture("../resource/image/tank_T2_0.png", GL_TRUE, "tank_T2_0");
    ResourceManager::loadTexture("../resource/image/tank_T2_1.png", GL_TRUE, "tank_T2_1");
    ResourceManager::loadTexture("../resource/image/tank_T2_2.png", GL_TRUE, "tank_T2_2");

    ResourceManager::loadTexture("../resource/image/home1.png", GL_FALSE, "home1");
    ResourceManager::loadTexture("../resource/image/home_destroyed.png", GL_TRUE, "home_destroyed");
    ResourceManager::loadTexture("../resource/image/home.png", GL_FALSE, "home");
    ResourceManager::loadTexture("../resource/image/brick.png", GL_FALSE, "brick");
    ResourceManager::loadTexture("../resource/image/iron.png", GL_FALSE, "iron");
    ResourceManager::loadTexture("../resource/image/river1.png", GL_TRUE, "river1");
    ResourceManager::loadTexture("../resource/image/river2.png", GL_TRUE, "river2");
    ResourceManager::loadTexture("../resource/image/tree.png", GL_TRUE, "tree");
    ResourceManager::loadTexture("../resource/image/ice.png", GL_FALSE, "ice");

    ResourceManager::loadTexture("../resource/image/bullet_up.png", GL_TRUE, "bullet_up");
    ResourceManager::loadTexture("../resource/image/bullet_down.png", GL_TRUE, "bullet_down");
    ResourceManager::loadTexture("../resource/image/bullet_left.png", GL_TRUE, "bullet_left");
    ResourceManager::loadTexture("../resource/image/bullet_right.png", GL_TRUE, "bullet_right");

    // ResourceManager::loadTexture("../resource/image/tip.png", GL_FALSE, "tip");
    ResourceManager::loadTexture("../resource/image/logo.png", GL_TRUE, "logo");


    ResourceManager::loadTexture("../resource/image/enemy_1_0.png", GL_TRUE, "enemy_1_0");
    ResourceManager::loadTexture("../resource/image/enemy_1_1.png", GL_TRUE, "enemy_1_1");
    ResourceManager::loadTexture("../resource/image/enemy_1_2.png", GL_TRUE, "enemy_1_2");
    ResourceManager::loadTexture("../resource/image/enemy_1_3.png", GL_TRUE, "enemy_1_3");

    ResourceManager::loadTexture("../resource/image/enemy_2_0.png", GL_TRUE, "enemy_2_0");
    ResourceManager::loadTexture("../resource/image/enemy_2_1.png", GL_TRUE, "enemy_2_1");
    ResourceManager::loadTexture("../resource/image/enemy_2_2.png", GL_TRUE, "enemy_2_2");
    ResourceManager::loadTexture("../resource/image/enemy_2_3.png", GL_TRUE, "enemy_2_3");

    ResourceManager::loadTexture("../resource/image/enemy_3_0.png", GL_TRUE, "enemy_3_0");
    ResourceManager::loadTexture("../resource/image/enemy_3_1.png", GL_TRUE, "enemy_3_1");
    ResourceManager::loadTexture("../resource/image/enemy_3_2.png", GL_TRUE, "enemy_3_2");
    ResourceManager::loadTexture("../resource/image/enemy_3_3.png", GL_TRUE, "enemy_3_3");

    ResourceManager::loadTexture("../resource/image/enemy_4_0.png", GL_TRUE, "enemy_4_0");
    ResourceManager::loadTexture("../resource/image/enemy_4_1.png", GL_TRUE, "enemy_4_1");
    ResourceManager::loadTexture("../resource/image/enemy_4_2.png", GL_TRUE, "enemy_4_2");
    ResourceManager::loadTexture("../resource/image/enemy_4_3.png", GL_TRUE, "enemy_4_3");

    ResourceManager::loadTexture("../resource/image/food_boom.png", GL_TRUE, "food_boom");
    ResourceManager::loadTexture("../resource/image/food_clock.png", GL_TRUE, "food_clock");
    ResourceManager::loadTexture("../resource/image/food_gun.png", GL_TRUE, "food_gun");
    ResourceManager::loadTexture("../resource/image/food_iron.png", GL_TRUE, "food_iron");
    ResourceManager::loadTexture("../resource/image/food_protect.png", GL_TRUE, "food_protect");
    ResourceManager::loadTexture("../resource/image/food_star.png", GL_TRUE, "food_star");
    ResourceManager::loadTexture("../resource/image/food_tank.png", GL_TRUE, "food_tank");

    ResourceManager::loadTexture("../resource/image/boom_dynamic.png", GL_TRUE, "boom_dynamic");
    ResourceManager::loadTexture("../resource/image/boom_static.png", GL_TRUE, "boom_static");

    ResourceManager::loadTexture("../resource/image/protect.png", GL_TRUE, "protect");

    ResourceManager::loadBGM("../resource/music/add.wav", "add");
    ResourceManager::loadBGM("../resource/music/bang.wav", "bang");
    ResourceManager::loadBGM("../resource/music/blast.wav", "blast");
    ResourceManager::loadBGM("../resource/music/fire.wav", "fire");
    ResourceManager::loadBGM("../resource/music/gunfire.wav", "gunfire");
    ResourceManager::loadBGM("../resource/music/hit.wav", "hit");
    ResourceManager::loadBGM("../resource/music/start.wav", "start");

    // 文字渲染
    Text = new TextRenderer(ResourceManager::getShader("text"), this->width, this->height);
    Text->Load("../resource/font/DePixelBreit.TTF", 24);

    // spriteRenderer = new SpriteRenderer(ResourceManager::getShader("sprite"));
    meshRenderer = new MeshRenderer(ResourceManager::getShader("mesh"));
    commonRenderer = new SpriteRenderer(ResourceManager::getShader("common"));
    soundEngine = new SoundEngine();


    /*绘制网格线*/
    std::vector<std::pair<glm::vec2, glm::vec2>> mesh;
    for (int i = 0; i < 26; i += 2) {
        mesh.push_back({ {i, 0}, {i, 26} });
        mesh.push_back({ {0, i}, {26, i} });
    }
    mesh.push_back({ {26, 0}, {26, 26} });
    meshRenderer->initRenderData(mesh);

    /*加载关卡*/
    this->levels_path.push_back("../resource/level/1.lvl");
    this->levels_path.push_back("../resource/level/2.lvl");
    this->levels_path.push_back("../resource/level/3.lvl");

    this->level_idx = 0;
    this->Levels.push_back(GameLevel::Load(levels_path[level_idx].data()));

    /*指定当前关卡*/
    this->current_level = &this->Levels.back();
    this->enemys = &this->current_level->enemys;
    this->bullets = &this->current_level->bullets;
    this->foods = &this->current_level->foods;
    this->tiles = &this->current_level->tiles;

    /*添加player*/
    this->player_1 = &this->current_level->player_1;
    this->player_2 = &this->current_level->player_2;
    // this->player_1 = Player(ResourceManager::getTexture("tank_T1_0"), glm::vec2(8, 0));
    // this->player_2 = Player(ResourceManager::getTexture("tank_T2_0"), glm::vec2(16, 0));

    this->state = GameState::GAME_CHOOSE;
    soundEngine->play(ResourceManager::getBGM("start"), get_time_from_init());
}

void Game::update_welcome() {
    if (this->keys[GLFW_KEY_W] || this->keys[GLFW_KEY_UP])
    {
        this->play_mode = PlayMode::ONE_PLAYER;
        soundEngine->play(ResourceManager::getBGM("fire"), get_time_from_init());

    }
    else if (this->keys[GLFW_KEY_S] || this->keys[GLFW_KEY_DOWN])
    {
        this->play_mode = PlayMode::TWO_PLAYERS;
        soundEngine->play(ResourceManager::getBGM("fire"), get_time_from_init());

    }
    else if (this->keys[GLFW_KEY_ENTER] || this->keys[GLFW_KEY_KP_ENTER])
    {
        this->state = GameState::GAME_ENTER;
        soundEngine->play(ResourceManager::getBGM("fire"), get_time_from_init());
    }
}

void Game::update_game() {
    this->current_level->create_enemy();
    obj_move();

    if (this->current_level->home.boom) {
        this->current_level->home.boom_doing();

        for (auto& bullet : *this->bullets)
            bullet.speed = 0;
        for (auto& tank : *this->enemys)
            tank.speed = 0;
        player_1->speed = 0;
        if (this->play_mode == PlayMode::TWO_PLAYERS)
            player_2->speed = 0;
    }

    auto tank_check = [=](Tank& tank) {
        if (tank.protect) {
            tank.protect_doing();
        }
        if (tank.boom) {
            tank.boom_doing();
        }
    };

    tank_check(*this->player_1);
    if (this->play_mode == PlayMode::TWO_PLAYERS)
        tank_check(*this->player_2);

    for (auto& enemy : *this->enemys)
        tank_check(enemy);

    switch (this->current_level->state)
    {

    case  GameLevel::LevelState::LEVEL_ON:
    {

    }
    break;

    case GameLevel::LevelState::LEVEL_WIN:
    {
        this->current_level->win();

        if (keys[GLFW_KEY_ENTER])
        {
            this->level_idx++;
            this->Levels.clear();
            this->Levels.push_back(GameLevel::Load(levels_path[level_idx].data()));
            /*指定当前关卡*/
            this->current_level = &this->Levels.back();
            this->enemys = &this->current_level->enemys;
            this->bullets = &this->current_level->bullets;
            this->foods = &this->current_level->foods;
            this->tiles = &this->current_level->tiles;

            this->current_level->state = GameLevel::LevelState::LEVEL_ON;
        }
    }
    break;

    case  GameLevel::LevelState::LEVEL_LOSE:
    {
        this->current_level->lose();

        if (keys[GLFW_KEY_ENTER])
        {
        }

    }
    break;

    default:
        break;

    };
}

void Game::update() {
    this->check_game_state();

    switch (state)
    {
    case GameState::GAME_CHOOSE:
        update_welcome();
        break;
    case GameState::GAME_ENTER:
        update_game();
        break;
    default:
        break;
    }
}

void Game::render_welcome()const {

    /*绘制网格线*/
   // meshRenderer->draw();

    GameObject obj(ResourceManager::getTexture("logo"), glm::vec2(2, 13), glm::vec2(30, 5));
    obj.draw(*commonRenderer);

    Text->RenderText("1 PLAYER", 280, 410, 1.8f);
    Text->RenderText("2 PLAYERS", 280, 470, 1.8f);

    Player tank(ResourceManager::getTexture("tank_T1_0"), glm::vec2(9, 6.5));
    tank.protect = false;
    tank.boom = false;
    tank.direction = Direction::RIGHT;

    if (this->play_mode == PlayMode::ONE_PLAYER)
        tank.pos = glm::vec2(9, 6.5);
    else
        tank.pos = glm::vec2(9, 4);

    tank.draw(*commonRenderer);
}

void Game::render_game()const {

    /*绘制网格线*/
    meshRenderer->draw();

    /*绘制提示文字*/
    Text->RenderText(R"(Player 1:)", 600, 0, 1.0f);
    Text->RenderText(R"(W,S,A,D)", 600, 30, 1.0f);
    Text->RenderText(R"(Player 2:)", 600, 60, 1.0f);
    Text->RenderText(R"(ARROWS)", 600, 90, 1.0f);
    Text->RenderText(std::to_string(current_level->get_enemys_remain()), 600, 120, 1.0f);

    /*绘制player*/
    this->player_1->draw(*commonRenderer);
    if (this->play_mode == PlayMode::TWO_PLAYERS) {
        this->player_2->draw(*commonRenderer);
    }

    /*绘制关卡*/
    this->current_level->Draw(*commonRenderer);

    /*当前关卡状态*/
    switch (current_level->state)
    {
    case GameLevel::LevelState::LEVEL_ON:
        break;
    case GameLevel::LevelState::LEVEL_WIN:
        Text->RenderText("YOU WIN", 100, 300, 3.0f);
        break;
    case GameLevel::LevelState::LEVEL_LOSE:
        Text->RenderText("GAME OVER", 100, 300, 3.0f);
        break;
    default:
        break;
    };
}

void Game::render() const {
    switch (this->state)
    {
    case GameState::GAME_WELCOME:
    case GameState::GAME_CHOOSE:
        this->render_welcome();
        break;
    case GameState::GAME_ENTER:
        this->render_game();
    default:
        break;
    }
}

/*
轴对齐碰撞箱(Axis-aligned Bounding Box)
*/
bool check_AABB(const GameObject& one, const GameObject& two) {
    float Delta = 0.08f;
    // x轴方向碰撞？
    bool collisionX = one.pos.x + one.size.x - two.pos.x > Delta && two.pos.x + two.size.x - one.pos.x > Delta;
    // y轴方向碰撞？
    bool collisionY = one.pos.y + one.size.y - two.pos.y > Delta && two.pos.y + two.size.y - one.pos.y > Delta;
    // 只有两个轴向都有碰撞时才碰撞
    return collisionX && collisionY;
}

/*边界检查*/
bool check_Bound(GameObject& one) {
    bool flag = false;
    if (one.pos.x < 0) {
        one.pos.x = 0;
        flag |= true;
    }
    if (one.pos.y < 0) {
        one.pos.y = 0;
        flag |= true;
    }
    if (one.pos.x > 26 - one.size.x) {
        one.pos.x = 26 - one.size.x;
        flag |= true;
    }
    if (one.pos.y > 26 - one.size.y) {
        one.pos.y = 26 - one.size.y;
        flag |= true;
    }
    return flag;
}

template<class T>
auto obj_vector_clear = [](std::vector<T>& vec) {
    std::vector<int> idx_to_erase; /*记录将要删除的对象的下标*/

    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i].IsDestroyed) {
            soundEngine->play(ResourceManager::getBGM("blast"), get_time_from_init());
            idx_to_erase.push_back(i);
        }
    }
    while (!idx_to_erase.empty()) {
        while (!idx_to_erase.empty() && idx_to_erase.back() == (int)vec.size() - 1) {
            vec.pop_back();
            idx_to_erase.pop_back();
        }
        if (!idx_to_erase.empty()) {
            std::swap(vec[idx_to_erase.back()], vec.back());
            vec.pop_back();
            idx_to_erase.pop_back();
        }
    }
};

void Game::obj_move() {
    /*auto移动enemy*/
    auto enemy_auto_move = [this](Enemy& tank) -> void {
        /*遍历所有瓦片，有碰撞返回真*/
        auto traverse_check = [this](GameObject& obj) -> bool {
            /*检查与边界的碰撞*/
            if (check_Bound(obj)) {
                return true;
            }
            /*检查与障碍物的碰撞*/
            for (auto& tile : *this->tiles) {
                if (tile.IsDestroyed) {
                    continue;
                }
                if (check_AABB(obj, tile)) { /*ICE, TREE*/
                    if (tile.type == OBJ::ICE || tile.type == OBJ::TREE) {
                        continue;
                    }
                    else /*BRICK,IRON,RIVER*/
                        return true;
                }
            }
            /*若没有碰撞，返回false*/
            return false;
        };

        /*随即尝试方向*/
        auto auto_get_rand_dirction = [](Tank& tank) {
            switch (get_rand_int(0, 3)) {
            case Direction::UP:
                tank.direction = Direction::UP;
                break;
            case Direction::DOWN:
                tank.direction = Direction::DOWN;
                break;
            case Direction::LEFT:
                tank.direction = Direction::LEFT;
                break;
            case Direction::RIGHT:
                tank.direction = Direction::RIGHT;
                break;
            }
        };

        /*让坦克轮子转起来！*/
        tank.do_roll();

        /*检查四个方向*/
        switch (tank.direction) {
        case Direction::UP: {
            tank.move(0, tank.speed);
            if (traverse_check(tank)) {
                tank.move(0, -tank.speed);
                auto_get_rand_dirction(tank);
            }
            break;
        }
        case Direction::DOWN: {
            tank.move(0, -tank.speed);
            if (traverse_check(tank)) {
                tank.move(0, tank.speed);
                auto_get_rand_dirction(tank);
            }
            break;
        }
        case Direction::LEFT: {
            tank.move(-tank.speed, 0);
            if (traverse_check(tank)) {
                tank.move(tank.speed, 0);
                auto_get_rand_dirction(tank);
            }
            break;
        }
        case Direction::RIGHT: {
            tank.move(tank.speed, 0);
            if (traverse_check(tank)) {
                tank.move(-tank.speed, 0);
                auto_get_rand_dirction(tank);
            }
            break;
        }
        default: {
            break;
        }
        }
    };

    /*获取food*/
    auto get_food = [this](const Food& food, Player& tank, double time)
    {
        std::cout << "get_food" << tank.cd_bullet << std::endl;

        switch (food.food)
        {
        case FOOD::FOOD_BOOM: {
            for (auto& enemy : *this->enemys)
                enemy.IsDestroyed = true;
            break;
        }case FOOD::FOOD_CLOCK: {
            for (auto& enemy : *this->enemys)
                enemy.speed = 0;
            break;
        }case FOOD::FOOD_GUN: {
            tank.cd_bullet *= 0.5f;
            break;
        }case FOOD::FOOD_IRON: {
            tank.bullet_enhanced = true;
            break;
        }case FOOD::FOOD_PROTECT: {
            tank.protect_start();
            break;
        }case FOOD::FOOD_STAR: {
            std::vector<glm::vec2>pos{
                {11, 2}, { 12,2 }, { 13,2 }, { 14,2 },
                { 11,1 }, { 14,1 },
                { 11,0 }, { 14,0 }
            };
            for (auto& p : pos)
                this->tiles->push_back(GameObject(ResourceManager::getTexture("iron"), p, glm::vec2(1.0f, 1.0f)));
            break;
        }case FOOD::FOOD_TANK: {
            tank.level_up();
            break;
        }default: {
            break;
        }
        }

    };

    /*移动玩家的tank*/
    auto tank_move = [this, get_food](Player& tank, Direction e) -> void {
        /*遍历所有瓦片，有碰撞返回真*/
        auto traverse_check = [this, get_food](Player& tank) -> bool {
            /*检查与边界的碰撞*/
            if (check_Bound(tank)) {
                return true;
            }
            /*检查与障碍物的碰撞*/
            for (auto& tile : *this->tiles) {
                if (tile.IsDestroyed) {
                    continue;
                }
                if (check_AABB(tank, tile)) { /*ICE, TREE*/
                    if (tile.type == OBJ::ICE || tile.type == OBJ::TREE) {
                        continue;
                    }
                    else /*BRICK,IRON,RIVER*/
                        return true;
                }
            }

            // /*检查与敌人碰撞*/
            // for (auto& enemy : this->enemys) {
            //     if (check_AABB(obj, enemy)) {
            //     }
            // }

            /*food*/
            for (auto& food : *this->foods) {
                if (check_AABB(tank, food)) {
                    get_food(food, tank, get_time_from_init());
                    food.IsDestroyed = true;
                }
            }

            /*若没有碰撞，返回false*/
            return false;
        };

        /*让坦克轮子转起来！*/
        tank.do_roll();

        /*移动前先检查方向，若坦克朝向与要去方向不一致，则不移动，原地转向*/
        if (tank.direction != e) {
            tank.direction = e;
            return;
        }

        /*检查四个方向*/
        switch (e) {
        case Direction::UP: {
            tank.move(0, tank.speed);
            if (traverse_check(tank))
                tank.move(0, -tank.speed);
            break;
        }
        case Direction::DOWN: {
            tank.move(0, -tank.speed);
            if (traverse_check(tank))
                tank.move(0, tank.speed);
            break;
        }
        case Direction::LEFT: {
            tank.move(-tank.speed, 0);
            if (traverse_check(tank))
                tank.move(tank.speed, 0);
            break;
        }
        case Direction::RIGHT: {
            tank.move(tank.speed, 0);
            if (traverse_check(tank))
                tank.move(-tank.speed, 0);
            break;
        }
        default: {
            break;
        }
        }
    };

    /*tank 射击*/
    auto tank_shoot = [this](Tank& tank, bool is_player) -> void {
        if (!tank.cd_bullet_ok(get_time_from_init()))
            return;

        Bullet bullet(nullptr, tank.pos, tank.direction, is_player);
        bullet.pos += tank.size * 0.5f - bullet.size * 0.5f;
        bullet.enhanced = tank.bullet_enhanced;
        switch (tank.direction) {
        case Direction::UP:
            bullet.texture = ResourceManager::getTexture("bullet_up");
            break;
        case Direction::DOWN:
            bullet.texture = ResourceManager::getTexture("bullet_down");
            break;
        case Direction::LEFT:
            bullet.texture = ResourceManager::getTexture("bullet_left");
            break;
        case Direction::RIGHT:
            bullet.texture = ResourceManager::getTexture("bullet_right");
            break;
        default:
            break;
        }
        this->bullets->push_back(bullet);

        tank.fire(get_time_from_init()); /*回调函数*/
        soundEngine->play(ResourceManager::getBGM("fire"), get_time_from_init());
    };

    /*移动bullet*/
    auto bullet_move = [this](Bullet& bullet) {
        /*遍历所有瓦片，有碰撞返回真*/
        auto bullet_collision_check = [this](Bullet& bullet) {
            /**
             * @return std::tuple<bool,GameObject*>
             *
             */

            bool has_collision = false;
            std::vector<GameObject*> collision_objs;
            // GameObject* collision_obj;

            /*检查子弹与边界的碰撞*/
            if (check_Bound(bullet)) {
                has_collision = true;
                // collision_obj=nullptr;
            }

            /*检查子弹与障碍物的碰撞*/
            for (auto& tile : *this->tiles) {
                if (tile.IsDestroyed) {
                    continue;
                }
                if (check_AABB(bullet, tile)) { /*ICE, TREE*/
                    if (tile.type == OBJ::ICE || tile.type == OBJ::TREE ||
                        tile.type == OBJ::RIVER) {
                        continue;
                    }
                    else /*BRICK,IRON*/
                    {
                        has_collision = true;
                        collision_objs.push_back(&tile);
                        // break;
                        continue;
                    }
                }
            }

            /*检查子弹与坦克碰撞*/
            for (auto& tank : *this->enemys) {
                if (tank.IsDestroyed || tank.protect) {
                    /*tank有护盾，则不可击中*/
                    continue;
                }
                if (check_AABB(bullet, tank)) {
                    has_collision = true;
                    collision_objs.push_back(&tank);
                    continue;
                }
            }

            /*子弹与子弹碰撞*/
            for (auto& bt : *this->bullets) {
                if (bt.IsDestroyed) {
                    continue;
                }
                /*同方向不可能碰撞*/
                if (check_AABB(bullet, bt) && bt.direction != bullet.direction) {
                    has_collision = true;
                    collision_objs.push_back(&bt);
                    continue;
                }
            }

            /*子弹与home碰撞*/
            if (check_AABB(this->current_level->home, bullet)) {
                has_collision = true;
                collision_objs.push_back(&this->current_level->home);
            }

            /*若没有碰撞，返回false*/
            return std::make_tuple(has_collision, collision_objs);
        };

        /*子弹运动*/
        bullet.move();

        auto [has_collision, collision_objs] = bullet_collision_check(bullet); /*FROM C++20，结构化绑定，Structured Binding*/

        if (has_collision) {
            if (collision_objs.empty()) {
                /*子弹与边界碰撞，超范围*/
                bullet.IsDestroyed = true;
                return;
            }


            /*若碰撞，检查类型，
            * 若被击中，销毁子弹，调用get_shot();
            * 不能被击中则忽略，子弹继续飞行
            */
            for (auto collision_obj : collision_objs) {
                switch (collision_obj->type)
                {
                case OBJ::TANK: {
                    /*玩家发射子弹击中敌人*/
                    if (bullet.from_player) {
                        collision_obj->get_shot();
                        bullet.IsDestroyed = true;
                    }
                    /*敌人发射子弹击中*/
                    else {
                    }
                    soundEngine->play(ResourceManager::getBGM("hit"), get_time_from_init());
                    break;
                }
                case OBJ::BULLET:
                case OBJ::HOME:
                case OBJ::BRICK:
                case OBJ::IRON:
                    collision_obj->get_shot(bullet.enhanced);
                    bullet.IsDestroyed = true;
                    soundEngine->play(ResourceManager::getBGM("hit"), get_time_from_init());
                    break;

                    /*不能被子弹击中的类型*/
                case OBJ::RIVER:
                case OBJ::TREE:
                case OBJ::ICE:
                case OBJ::DEFAULT:
                default:
                    break;
                }
            }
        }
    };

    /*player 移动，player 发射 bullet*/
    {
        /*player_1移动*/
        if (this->keys[GLFW_KEY_W]) {
            tank_move(*player_1, Direction::UP);
        }
        else if (this->keys[GLFW_KEY_S]) {
            tank_move(*player_1, Direction::DOWN);
        }
        else if (this->keys[GLFW_KEY_A]) {
            tank_move(*player_1, Direction::LEFT);
        }
        else if (this->keys[GLFW_KEY_D]) {
            tank_move(*player_1, Direction::RIGHT);
        }
        /*player_1发射 bullet*/
        if (this->keys[GLFW_KEY_J]) {
            tank_shoot(*player_1, true);
        }

        if (this->play_mode == PlayMode::TWO_PLAYERS) {
            /*player_2移动*/
            if (this->keys[GLFW_KEY_UP]) {
                tank_move(*player_2, Direction::UP);
            }
            else if (this->keys[GLFW_KEY_DOWN]) {
                tank_move(*player_2, Direction::DOWN);
            }
            else if (this->keys[GLFW_KEY_LEFT]) {
                tank_move(*player_2, Direction::LEFT);
            }
            else if (this->keys[GLFW_KEY_RIGHT]) {
                tank_move(*player_2, Direction::RIGHT);
            }
            /*player_2发射 bullet*/
            if (this->keys[GLFW_KEY_KP_0]) {
                tank_shoot(*player_2, true);
            }
        }
    }

    /*enemy移动，射击*/
    {for (auto& enemy : *this->enemys) {
        enemy_auto_move(enemy);
        tank_shoot(enemy, false);
    }

    /*bullet 移动*/
    {
        for (auto& bullet : *this->bullets) {
            bullet_move(bullet);
        }
    }}

    /*检查敌人血量,添加敌人，添加food奖励*/
    {
        for (auto& enemy : *this->enemys) {
            if (enemy.IsDestroyed) {
                this->current_level->enemy_die();
                if (this->current_level->create_food_ok()) {
                    this->current_level->create_food();
                    soundEngine->play(ResourceManager::getBGM("add"), get_time_from_init());
                }
            }
        }
    }

    /*清除已经摧毁的子弹、敌人、瓦片*/
    {
        /*清理food*/
        obj_vector_clear<Food>(*this->foods);
        /*清理子弹*/
        obj_vector_clear<Bullet>(*this->bullets);
        /*清理敌人*/
        obj_vector_clear<Enemy>(*this->enemys);
        /*清理瓦片*/
        //obj_vector_clear<GameObject>(*this->tiles);

        /*home被摧毁*/
        if (this->current_level->home.IsDestroyed) {
            this->current_level->home.texture = ResourceManager::getTexture("home_destroyed");
            this->current_level->state = GameLevel::LevelState::LEVEL_LOSE;
        }
    }
}

void Game::check_game_state() {
    if (this->keys[GLFW_KEY_ESCAPE]) {
        this->state = GameState::GAME_EXIT;
    }
}


void Game::next_level() {
    if (level_idx < (int)Levels.size() - 1) {
        current_level++;
        level_idx++;
    }
    else {
        state = GameState::GAME_WIN;/*通过所有关卡*/
    }
}