//
//  Pathfinder.h
//  Lab 05
//
//  Created by Zac Clark on 2/8/16.
//  Copyright © 2016 Zac Clark. All rights reserved.
//

#pragma once
#include "PathfinderInterface.h"
#include <cstdlib>
#include <sstream>
#include <fstream>

using namespace std;

class Pathfinder : public PathfinderInterface
{
public:
    Pathfinder();
    ~Pathfinder();
    string getMaze();
    void createRandomMaze();
    bool importMaze(string file_name);
    vector<string> solveMaze();
    bool find(int x, int y, int z, string MazeArray[5][5][5]);
private:
    string file_name;
    vector <string> path;
    string currentMaze[5][5][5];
};