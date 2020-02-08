#pragma once
#ifndef MAP_EDITOR_WINDOW_H_
#define MAP_EDITOR_WINDOW_H_

#include "MapEditor.hh"
#include "SimpleMap.hh"
#include "WindowBase.hh"

class MapEditorWindow : public WindowBase {
  private:
    char       temp_name[256];
    char       temp_path[256];
    SimpleMap* simple_map;
    MapEditor* map_editor;

  public:
    MapEditorWindow();

    ~MapEditorWindow();

    virtual void Show();

    void UpdateData();
};

#endif