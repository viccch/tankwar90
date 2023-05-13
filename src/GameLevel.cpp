
#include "GameLevel.h"

GameLevel GameLevel::Load(const GLchar* file)
{
    GameLevel level;

    level.tiles.clear();
    std::ifstream fp;
    fp.open(file, std::ios::in);

    std::string line = "";

    int rows = 0, cols = 0;
    while (rows * cols == 0)
    {
        std::getline(fp, line);
        int pos = line.find_first_not_of(32); /*space*/
        if (line[pos] == 35)                  /*#*/
            continue;

        int pos_nums;

        std::stringstream ss;

        ss << line;
        ss >> rows >> cols;
        ss >> level.enemy_nums >> level.enemy_survive_max >> pos_nums;
        while (pos_nums--)
        {
            int x, y;
            ss >> x >> y;
            level.enemy_born_pos.push_back({ x, y });
        }
    }

    std::vector<std::vector<int>>Map;

    while (!fp.eof())
    {
        std::getline(fp, line);
        int pos = line.find_first_not_of(32);    /*space*/
        if (line.size() == 0 || line[pos] == 35) /*#*/
            continue;

        std::stringstream ss;
        int num;

        ss << line;

        std::vector<int> row;

        for (int i = 0; i < cols; i++)
        {
            ss >> num;
            row.push_back(num);
        }
        Map.push_back(row);
    }
    fp.close();

    if (!Map.empty())
    {
        [&level, &Map]()->void
        {
            for (int i = 0; i < 26; i++)
            {
                for (int j = 0; j < 26; j++)
                {
                    if (OBJ::DEFAULT == Map[i][j])
                        continue;

                    GameObject obj;
                    obj.IsDestroyed = false;
                    obj.pos = glm::vec2(j, 26 - 1 - i);
                    obj.size = glm::vec2(1, 1);
                    obj.type = (OBJ)Map[i][j];

                    switch (Map[i][j])
                    {
                    case OBJ::HOME:
                    {
                        level.home.IsDestroyed = false;
                        level.home.type = OBJ::HOME;
                        level.home.texture = ResourceManager::getTexture("home");
                        level.home.size = obj.size * 2.0f;
                        level.home.pos = obj.pos;
                        continue;
                        break;
                    }
                    case OBJ::BRICK:
                        obj.texture = ResourceManager::getTexture("brick");
                        break;

                    case OBJ::IRON:
                        obj.texture = ResourceManager::getTexture("iron");
                        break;

                    case OBJ::RIVER:
                        obj.texture = ResourceManager::getTexture("river1");
                        break;

                    case OBJ::TREE:
                        obj.texture = ResourceManager::getTexture("tree");
                        break;

                    case OBJ::ICE:
                        obj.texture = ResourceManager::getTexture("ice");
                        break;

                    case OBJ::DEFAULT:
                    default:
                        break;
                    }

                    level.tiles.push_back(obj);
                }
            }
        }();
    }

    return level;
}

void GameLevel::Draw(SpriteRenderer& renderer)const
{
    /*绘制关卡障碍*/
    for (auto& tile : this->tiles)
    {
        if (!tile.IsDestroyed)
            tile.draw(renderer);
    }

    /*绘制子弹*/
    for (auto& bullet : this->bullets)
        bullet.draw(renderer);

    /*绘制food*/
    for (auto& food : this->foods)
        food.draw(renderer);

    /*绘制敌人*/
    for (auto& enemy : this->enemys)
        enemy.draw(renderer);

    /*home 绘制*/
    home.draw(renderer);
}

GameLevel::GameLevel()
{
    /*添加player*/
    this->player_1 = Player(ResourceManager::getTexture("tank_T1_0"), glm::vec2(8, 0));
    this->player_2 = Player(ResourceManager::getTexture("tank_T2_0"), glm::vec2(16, 0));

    this->enemy_created = 0;
    this->enemy_surviving = 0;

    this->state = GameLevel::LevelState::LEVEL_ON;
}
GameLevel::~GameLevel()
{
}

void GameLevel::create_enemy()
{
    while (enemy_created < enemy_nums && enemy_surviving < enemy_survive_max)
    {
        int num = get_rand_int(0, this->enemy_born_pos.size() - 1);
        this->enemys.push_back(Enemy(ResourceManager::getTexture("enemy_1_3"), this->enemy_born_pos[num]));
        enemy_created++;
        enemy_surviving++;
    }

    if (enemy_created == enemy_nums && enemy_surviving == 0)
    {
        this->state = GameLevel::LevelState::LEVEL_WIN;
    }
}

bool  GameLevel::create_food_ok() {
    if (enemy_created % 2 == 0)
        return true;
    else return false;
}

void GameLevel::create_food()
{
    glm::vec2 food_pos = glm::vec2(get_rand_real(0, 25), get_rand_real(0, 25));
    int food_type = get_rand_int(1, 7);

    /*test*/
    //food_type = FOOD::FOOD_PROTECT;
    /*test*/

    switch (food_type)
    {
    case FOOD::FOOD_BOOM:
        this->foods.push_back(Food(ResourceManager::getTexture("food_boom"), food_pos, FOOD::FOOD_BOOM));
        break;

    case FOOD::FOOD_CLOCK:
        this->foods.push_back(Food(ResourceManager::getTexture("food_clock"), food_pos, FOOD::FOOD_CLOCK));
        break;

    case FOOD::FOOD_GUN:
        this->foods.push_back(Food(ResourceManager::getTexture("food_gun"), food_pos, FOOD::FOOD_GUN));
        break;

    case FOOD::FOOD_IRON:
        this->foods.push_back(Food(ResourceManager::getTexture("food_iron"), food_pos, FOOD::FOOD_IRON));
        break;

    case FOOD::FOOD_PROTECT:
        this->foods.push_back(Food(ResourceManager::getTexture("food_protect"), food_pos, FOOD::FOOD_PROTECT));
        break;

    case FOOD::FOOD_STAR:
        this->foods.push_back(Food(ResourceManager::getTexture("food_star"), food_pos, FOOD::FOOD_STAR));
        break;

    case FOOD::FOOD_TANK:
        this->foods.push_back(Food(ResourceManager::getTexture("food_tank"), food_pos, FOOD::FOOD_TANK));
        break;

    default:
        break;
    }
}

void GameLevel::enemy_die()
{
    enemy_surviving--;
}

void GameLevel::win()
{
    this->state = LevelState::LEVEL_WIN;
    std::cout << "game win!\n";
}

void GameLevel::lose() {
    this->state = LevelState::LEVEL_LOSE;
    std::cout << "game lose!\n";
}

int GameLevel::get_enemys_remain() {
    return enemy_nums - enemy_created + enemy_surviving;
}

void GameLevel::Clear() {
    this->bullets.clear();
    this->foods.clear();
    this->enemys.clear();
    this->tiles.clear();
}
