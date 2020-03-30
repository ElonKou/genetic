#pragma once
#ifndef LIFE_GAME_MAP_BASE_H_
#define LIFE_GAME_MAP_BASE_H_

#include "BiuLabTypes.hh"
#include "Lib.hh"
#include "LifeGameConfig.hh"
#include "LifeGameRuleBase.hh"
#include "WindowBase.hh"

class LifeGameMapBase : public WindowBase {
  public:
    LifeGameMapBase() {}

    ~LifeGameMapBase() {}

    virtual void Show() = 0;

    virtual void UpdateData() = 0;

    virtual void UpdateSize(int width, int history) = 0;

    virtual void RandomElems(int rate = 50) = 0;

    virtual void UpdateMap(LifeGameRuleBase& rule, int rule_id) = 0;
};

#endif