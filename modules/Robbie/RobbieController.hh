#pragma once
#ifndef ROBBIE_CONTROLLER_HH_
#define ROBBIE_CONTROLLER_HH_

#include "BiuLabConfig.hh"
#include "CoreBase.hh"
#include "Robbie.hh"
#include "RobbieConfig.hh"
#include "SimpleMap.hh"
#include <string>
using namespace std;

typedef struct RobbieResult {
    // vector<int> scores;
    double aver_score;
    // int robbie_id;
    // int map_id;
} RobbieResult;

typedef struct RobbieControllerData : public CoreBase {
    int                  loop_controller;
    int                  loop_map;
    int                  robbie_cnt;
    int                  global_id;
    int                  speed;
    int                  history_size;
    bool                 train_stop_check;
    float                mutate_rate;
    float                max_histyory;
    RobbieActionHistory  history;
    SimpleMap*           dis_map;
    Robbie*              dis_rob;
    vector<Robbie>       robbies;
    vector<SimpleMap*>   maps;
    vector<RobbieResult> robbie_scores;
    vector<RobbieResult> robbie_scores_tf;

    RobbieControllerData() {}

    ~RobbieControllerData() {}

} RobbieControllerData;

class RobbieController : public CoreBase {
  public:
    RobbieController();
    ~RobbieController();
    // char                  robbie_path[256];
    // char                  robbie_name[256];
    // char                  map_path[256];
    // char                  map_name[256];
    bool                  save_run;
    bool                  running;
    bool                  stoped;
    bool                  run_step;
    RobbieControllerData* data;

    void Init();

    void Train();

    void Print_str();

    void Play();

    void Stop();

    void UpdateInFrame();

    Robbie LoadRobbie(string robbie_path);

    void SaveRobbie(Robbie& rob, string robbie_path);

    void SetMap(SimpleMap* map);

    int ShowHisgram(int num);

    int GetIndex(float random_index);

    void PlayOne();
};

#endif