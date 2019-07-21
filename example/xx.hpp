#ifndef CORE_GENETIC
#define CORE_GENETIC

#define STR_CNT 7       // 基因密码子长度
#define MUTATE_ALL 1000 // 突变总数值
#define MUTATE_VAL 5    // 突变率
#define CLIP_CNT 1      // 剪切数量
#define GENE_CLEAR -1   // 清除基因

#define LOOP_MAP 10    // 执行地图数量
#define LOOP_CNT 100   // 执行步骤数量
#define ROBBIE_CNT 200 // 代际数量(每一代数量)
#define NAME_LEN 16    // 名字长度
#define PARENT_CNT 2   // 双亲数量
#define GENE_LEN 243   // 基因长度

#define MAP_WIDTH 16    // 地图宽度
#define MAP_HEIGHT 16   // 地图长度
#define RUBBISH_CNT 100 // 垃圾数量
#define EDGE 2          // 边界标志
#define RUBBISH 1       // 物体标志
#define EMPTY 0         // 空的标志

#define LOOP_CONTROLLER 10000 // 代数
#define PUNISHMENT_EDGE -5    // 撞墙惩罚
#define PUNISHMENT_PICK -1    // 无效捡东西惩罚
#define REWARD 10             //奖励

int randomInt(int range);
float randomFloat();

typedef union vec_2i {
    struct
    {
        int x;
        int y;
    };
    int v[2];
    vec_2i();
    vec_2i(int a, int b);
    vec_2i operator+(vec_2i other);
    void print();
} vec_2i;

typedef struct Strategy
{
    int key;
    int wmove;
    int hmove;
} Strategy;
struct Map;

class Robbie
{
public:
    Robbie();
    ~Robbie();
    Robbie clone();
    // gene
    int gene_len;
    int str_len;
    int genes[GENE_LEN];
    int mutate_all;
    int mutate_val;
    void init();
    void randomPos();
    void clear();
    void clip(Robbie &other);
    Robbie clip2(Robbie other, int pos);
    void clip3(Robbie other);
    void mutate();
    void compare(Robbie other);
    int move(int action, Map &map);
    int pick(int action, Map &map);
    void play(Map &map);
    void playScreen(Map &map);
    float playOne();
    void print();
    int getScore();
    int getAction(int hash);
    // robbie info
    int id;
    int score;
    int generation;
    int parentId[PARENT_CNT];
    vec_2i pos;
    vec_2i start;
};

class Map
{
public:
    Map();
    ~Map();
    vec_2i size;
    int map[MAP_HEIGHT][MAP_WIDTH];
    int target[MAP_HEIGHT][MAP_WIDTH];
    vec_2i getSize();
    void print(vec_2i pos);
    void cleanTarget();
    void init();
    int inline getValue(vec_2i pos);
    int getHash(vec_2i pos);
    int getTarget(vec_2i pos);
    void setTarget(vec_2i pos, int key);
    int doAction(vec_2i start, vec_2i offset);
};

class Controller
{
public:
    struct Result
    {
        int score;
        int robbie_id;
        int map_id;
    };
    Controller();
    ~Controller();
    int loop_controller;
    int loop_one;
    int loop_cnt;
    int robbie_cnt;
    int map_cnt;
    Robbie *robbies;
    Map *maps;
    Result *scores;
    Result play(Robbie r, Map &m);
    void run();
};
#endif