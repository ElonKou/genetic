/*================================================================
*  Copyright (C)2019 All rights reserved.
*  FileName : SimpleMap.cc
*  Author   : elonkou
*  Email    : elonkou@ktime.cc
*  Date     : 2019年12月29日 星期日 13时20分43秒
================================================================*/

#include "SimpleMap.hh"
#include "Lib.hh"
#include <fstream>
#include <iostream>

using namespace std;

SimpleMap::SimpleMap() {
    size            = {MAP_WIDTH, MAP_HEIGHT};
    rubbish_cnt     = RUBBISH_CNT;
    gem_cnt         = GEM_CNT;
    only_show_round = false;
    map             = nullptr;
    target          = nullptr;
    map_name        = "base.map";
    version         = "0.1";
    path_name       = BIULAB_APPLICATION_PATH "/genetic";
}

SimpleMap::SimpleMap(vec_2i map_size) {
    size   = map_size;
    map    = new int*[size.y];
    target = new int*[size.y];
    for (int i = 0; i < size.y; i++) {
        map[i]    = new int[size.x];
        target[i] = new int[size.x];
    }
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            map[i][j]    = MAP_EMPTY;
            target[i][j] = MAP_EMPTY;
        }
    }
}

SimpleMap::~SimpleMap() {}

void SimpleMap::CleanTarget() {
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            target[i][j] = map[i][j];
        }
    }
}

void SimpleMap::RandomMap() {
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            if (map[i][j] == MAP_RUBBISH || map[i][j] == MAP_GEM) {
                map[i][j] = MAP_EMPTY;
            }
            if (target[i][j] == MAP_RUBBISH || map[i][j] == MAP_GEM) {
                target[i][j] = MAP_EMPTY;
            }
        }
    }
    for (int i = 0; i < rubbish_cnt;) {
        int temp_x = RandomInt(size.x);
        int temp_y = RandomInt(size.y);
        if (map[temp_y][temp_x] == MAP_EMPTY) {
            map[temp_y][temp_x]    = MAP_RUBBISH;
            target[temp_y][temp_x] = MAP_RUBBISH;
            i++;
        }
    }
    for (int i = 0; i < gem_cnt;) {
        int temp_x = RandomInt(size.x);
        int temp_y = RandomInt(size.y);
        if (map[temp_y][temp_x] == MAP_EMPTY) {
            map[temp_y][temp_x]    = MAP_GEM;
            target[temp_y][temp_x] = MAP_GEM;
            i++;
        }
    }
}

void SimpleMap::CleanMap() {
    for (int i = 0; i < size.y; i++) {
        for (int j = 0; j < size.x; j++) {
            map[i][j]    = MAP_EMPTY;
            target[i][j] = MAP_EMPTY;
        }
    }
}

bool SimpleMap::InMap(vec_2i pos) {
    return (pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y);
}

void SimpleMap::Init() {
    // init the std map
    map    = new int*[size.y];
    target = new int*[size.y];
    for (int i = 0; i < size.y; i++) {
        map[i]    = new int[size.x];
        target[i] = new int[size.x];
    }
    CleanMap();
    for (int i = 0; i < size.y; i++) {
        map[i][0] = map[i][size.x - 1] = MAP_EDGE;
        target[i][0] = target[i][size.x - 1] = MAP_EDGE;
    }
    for (int i = 0; i < size.x; i++) {
        map[0][i] = map[size.y - 1][i] = MAP_EDGE;
        target[0][i] = target[size.y - 1][i] = MAP_EDGE;
    }
    RandomMap();
}

void SimpleMap::UpdateSize(vec_2i new_size) {
    int map_temp[size.y][size.x];
    for (int j = 0; j < size.y; j++) {
        for (int i = 0; i < size.x; i++) {
            map_temp[j][i] = map[j][i];
        }
    }
    if (map) {
        for (int i = 0; i < size.y; i++) {
            if (map[i]) {
                delete map[i];
            }
        }
    }
    delete map;
    if (target) {
        for (int i = 0; i < size.y; i++) {
            if (target[i]) {
                delete target[i];
            }
        }
    }
    delete target;
    map    = new int*[new_size.y];
    target = new int*[new_size.y];
    for (int i = 0; i < new_size.y; i++) {
        map[i]    = new int[new_size.x];
        target[i] = new int[new_size.x];
    }
    int min_x = size.x < new_size.x ? size.x : new_size.x;
    int min_y = size.y < new_size.y ? size.y : new_size.y;
    // int max_x = size.x > new_size.x ? size.x : new_size.x;
    // int max_y = size.y > new_size.y ? size.y : new_size.y;
    for (int i = 0; i < new_size.y; i++) {
        for (int j = 0; j < new_size.x; j++) {
            if (i < min_y && j < min_x) {
                map[i][j]    = map_temp[i][j];
                target[i][j] = map_temp[i][j];
            } else {
                map[i][j]    = MAP_EMPTY;
                target[i][j] = MAP_EMPTY;
            }
        }
    }
    size = new_size;
}

void SimpleMap::LoadMap(const string& load_path) {
    cout << "Load: " << load_path << endl;
    fstream fp;
    string  line;
    fp.open(load_path, ios::in);
    while (getline(fp, line)) {
        std::string str;
        size_t      found = line.find("version:");
        if (found != string::npos) {
            str = line.substr(found + 8, line.size());
            // float map_version = StringToNum<float>(str);
        }
        found = line.find("name:");
        if (found != string::npos) {
            str      = line.substr(found + 5, line.size());
            map_name = str;
        }
        found = line.find("width:");
        if (found != string::npos) {
            str    = line.substr(found + 6, line.size());
            size.x = StringToNum<int>(str);
        }
        found = line.find("height:");
        if (found != string::npos) {
            str    = line.substr(found + 7, line.size());
            size.y = StringToNum<int>(str);
        }
        found = line.find("rubbish:");
        if (found != string::npos) {
            str         = line.substr(found + 8, line.size());
            rubbish_cnt = StringToNum<int>(str);
        }
        found = line.find("gem:");
        if (found != string::npos) {
            str     = line.substr(found + 4, line.size());
            gem_cnt = StringToNum<int>(str);
        }
        found = line.find("map:");
        if (found != string::npos) {
            map    = new int*[size.y];
            target = new int*[size.y];
            for (int i = 0; i < size.y; i++) {
                map[i]    = new int[size.x];
                target[i] = new int[size.x];
                getline(fp, line);
                vector<string> vec = Split(line, ",");
                for (int j = 0; j < size.x; j++) {
                    auto it = elems.find(vec[j]);
                    if (it != elems.end()) {
                        map[i][j]    = it->second;
                        target[i][j] = it->second;
                    } else {
                        map[i][j]    = MAP_EMPTY;
                        target[i][j] = MAP_EMPTY;
                    }
                }
            }
        }
    }
    fp.close();
}

void SimpleMap::SaveMap(const string& save_path) {
    cout << "Save: " << save_path << endl;
    fstream fp;
    fp.open(save_path, ios::out | ios::trunc);
    if (!fp) {
        cout << "Save error." << endl;
        return;
    }
    rubbish_cnt = 0;
    gem_cnt     = 0;
    for (int j = 0; j < size.y; j++) {
        for (int i = 0; i < size.x; i++) {
            if (map[j][i] == MAP_RUBBISH) {
                rubbish_cnt++;
            }
            if (map[j][i] == MAP_GEM) {
                gem_cnt++;
            }
        }
    }

    fp << "version:" << version << endl;
    fp << "map_name:" << map_name << endl;
    fp << "width:" << to_string(size.x) << endl;
    fp << "height:" << to_string(size.y) << endl;
    fp << "rubbish:" << to_string(rubbish_cnt) << endl;
    fp << "gem:" << to_string(gem_cnt) << endl;
    fp << "map:" << endl;
    for (int j = 0; j < size.y; j++) {
        string x = "";
        for (int i = 0; i < size.x; i++) {
            x = infos[int(map[j][i])].target;
            fp << x << ",";
        }
        if (j != size.y - 1) {
            fp << endl;
        }
    }
    fp.close();
}

// inline int SimpleMap::getValue(vec_2i pos) { return target[pos.y][pos.x]; }

int SimpleMap::GetHash(vec_2i pos) {
    int east  = GetValue4Hash(vec_2i(pos.x + 1, pos.y));
    int north = GetValue4Hash(vec_2i(pos.x, pos.y + 1));
    int west  = GetValue4Hash(vec_2i(pos.x - 1, pos.y));
    int south = GetValue4Hash(vec_2i(pos.x, pos.y - 1));
    int mid   = GetValue4Hash(pos);
    int hash  = 0;
    hash += 1 * east;
    hash += 3 * north;
    hash += 9 * west;
    hash += 27 * south;
    hash += 81 * mid;
    // cout << pos << " : " << east << " " << north << " " << west << " " << south << " " << mid << " " << hash << endl;
    return hash;
}

int SimpleMap::GetTarget(vec_2i pos) { return target[pos.y][pos.x]; }

void SimpleMap::SetTarget(vec_2i pos, int key) { target[pos.y][pos.x] = key; }

int SimpleMap::GetElem(vec_2i pos) { return map[pos.y][pos.x]; }

void SimpleMap::SetElem(vec_2i pos, int key) { map[pos.y][pos.x] = key; }

int SimpleMap::DoAction(vec_2i start, vec_2i offset) {
    // MAP_EDGE : -1(failed)
    // pick : 0(empty)
    // move : 1(succeed)
    int nowVal = GetValue(start);
    if (nowVal == MAP_EDGE) {
        return -1;
    } else if (nowVal == MAP_RUBBISH) {
    } else {
    }
    return 0;
}

int SimpleMap::GetValue4Hash(vec_2i pos) {
    MapType x = MapType(GetValue(pos));
    switch (x) {
    case MAP_EDGE:
        return 2;
        break;
    case MAP_RUBBISH:
        return 1;
        break;
    case MAP_EMPTY:
        return 0;
        break;
    case MAP_OUT:
        return 2;
        break;
    case MAP_GEM:
        return 1;
        break;
    default:
        return 0;
        break;
    }
}

inline int* SimpleMap::operator[](int row) { return map[row]; }

void SimpleMap::Print(vec_2i pos) {
    PrintSucceed("map:\t\t\t\t\t\ttarget:\n");
    for (int i = size.y - 1; i >= 0; i--) {
        for (int j = 0; j < size.x; j++) {
            if (map[i][j] != 0) {
                if (map[i][j] == MAP_EDGE) {
                    PrintSucceed(map[i][j]);
                } else {
                    PrintOk(map[i][j]);
                }
                PrintSucceed(" ");
            } else {
                printf("  ");
            }
        }
        printf("  ");
        for (int j = 0; j < size.x; j++) {
            if (i == pos.y && j == pos.x) {
                PrintError(target[i][j]);
                PrintError(" ");
            } else if (target[i][j] != 0) {
                if (map[i][j] == MAP_EDGE) {
                    PrintSucceed(map[i][j]);
                } else {
                    PrintOk(map[i][j]);
                }
                PrintSucceed(" ");
            } else {
                printf("  ");
            }
        }
        printf("\n");
    }
}
