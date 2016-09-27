//
//  Pathfinder.cpp
//  Lab 05
//
//  Created by Zac Clark on 2/8/16.
//  Copyright © 2016 Zac Clark. All rights reserved.
//

#pragma once
#include "Pathfinder.h"

using namespace std;

Pathfinder::Pathfinder()
{
    //construct new maze of 1's
    //cout << "created new maze of 1's" << endl;
    //jump level
    for (int z = 0; z < 5; z++)
    {
        //jump y coordinate
        for (int y = 0; y < 5; y++)
        {
            //jump x coordinate
            for (int x = 0; x < 5; x++)
            {
                //input 1 in each cell
                currentMaze[x][y][z] = "1";
            }
        }
    }
}
Pathfinder::~Pathfinder()
{
    
}
string Pathfinder::getMaze()
{
    //cout << "ran getMaze" << endl;
    
    string output;
    //jump level
    for (int z = 0; z < 5; z++)
    {
        //jump y coordinate
        for (int y = 0; y < 5; y++)
        {
            //jump x coordinate
            for (int x = 0; x < 5; x++)
            {
                if (x <= 3)
                    output += currentMaze[x][y][z] + " ";
                else
                    output += currentMaze[x][y][z];
            }
            output += "\n";
        }
        if (z !=4)
            output += "\n";
    }
    
    return output;
}
void Pathfinder::createRandomMaze()
{
    //cout << "ran createRandomMaze" << endl;

    int newValue;
    string newValue_string;
    //jump level
    for (int z = 0; z < 5; z++)
    {
        //jump y coordinate
        for (int y = 0; y < 5; y++)
        {
            //jump x coordinate
            for (int x = 0; x < 5; x++)
            {
                //create new 1 or 0 and convert to string
                newValue = rand() % 2;
                stringstream strm;
                strm << newValue;
                newValue_string = strm.str();
                //insert value into array
                currentMaze[x][y][z] = newValue_string;
            }
        }
    }
    currentMaze[0][0][0] = "1";
    currentMaze[4][4][4] = "1";
    
    
}
bool Pathfinder::importMaze(string file_name)
{
    //cout << "ran importMaze" << endl;
    
    bool valid = true;
    //read in maze info
    ifstream maze_in_file_test1;
    maze_in_file_test1.open(file_name);
    if(!maze_in_file_test1.is_open())
    {
        return false;
    }
    
    //read in maze and check valid number of cells
    string tempCellValue;
    int cell_count = 0;
    while (maze_in_file_test1 >> tempCellValue)
    {
        cell_count++;
    }
    if (cell_count != 125)
    {
        //cout << "invalid cell count" << endl;
        valid = false;
    }
    
    //read in maze and check cell value validity
    ifstream maze_in_file_test2;
    maze_in_file_test2.open(file_name);
    
    string testMaze[5][5][5];
    string cellValue_temp;

    for (int z = 0; z < 5; z++)
    {
        //jump y coordinate
        for (int y = 0; y < 5; y++)
        {
            //jump x coordinate
            for (int x = 0; x < 5; x++)
            {
                //insert cell value in maze
                maze_in_file_test2 >> cellValue_temp;
                testMaze[x][y][z] = cellValue_temp;
                if (cellValue_temp != "1" && cellValue_temp != "0")
                {
                    //cout << "cell value not equal to 1 or 0" << endl;
                    valid = false;
                }
            }
        }
    }

    if (testMaze[0][0][0] != "1" || testMaze[4][4][4] != "1")
    {
        //cout << "invalid beginning and/or end value" << endl;
        valid = false;
    }
    
    //invalid maze
    if (valid == false)
    {
        //cout << "valid = false" << endl;
        return false;
    }
    
    //valid maze
    else
    {
        ifstream maze_in_file;
        maze_in_file.open(file_name);
    
        string cellValue;
        //jump level
        for (int z = 0; z < 5; z++)
        {
            //jump y coordinate
            for (int y = 0; y < 5; y++)
            {
                //jump x coordinate
                for (int x = 0; x < 5; x++)
                {
                    //read in cell value and insert in maze
                    maze_in_file >> cellValue;
                    currentMaze[x][y][z] = cellValue;
                }
            }
        }
        return true;
    }
}
vector <string> Pathfinder::solveMaze()
{
    //cout << "ran solveMaze" << endl;
    
    //duplicate maze to solve (and manipulate)
    string mazeDuplicate[5][5][5];
    for (int z = 0; z < 5; z++)
    {
        //jump y coordinate
        for (int y = 0; y < 5; y++)
        {
            //jump x coordinate
            for (int x = 0; x < 5; x++)
            {
                //duplicate cell values
                mazeDuplicate[x][y][z] = currentMaze[x][y][z];
            }
        }
    }
    
    //initialize vector
    vector <string> finalCoordinates;
    path = { };
    if ((find(0, 0, 0, mazeDuplicate)) == true)
    {
        
        //cout << "reached the end echo" << endl;
        for (int i = 0; i < path.size(); i++)
        {
            finalCoordinates.push_back(path[path.size()-(i+1)]);
        }
    }
    else
    {
        //reset vector if no solution was found
        finalCoordinates = { };
    }
    //return vector
    return finalCoordinates;
    
}
bool Pathfinder::find(int x, int y, int z, string MazeArray[5][5][5])
{
    //scans whole maze first, then adds coordinates once base case is found
    //change cell to 2 if already visited (manipulate maze)
    //base cases: found the end, outside the maze, already visited
    
    string coordinates; //(x, y, z)
    string xCoordinate;
    string yCoordinate;
    string zCoordinate;
    stringstream strmx;
    stringstream strmy;
    stringstream strmz;
    //create coordinates string
    strmx << x;
    xCoordinate = strmx.str();
    strmy << y;
    yCoordinate = strmy.str();
    strmz << z;
    zCoordinate = strmz.str();
    
    coordinates = "(" + xCoordinate + ", " + yCoordinate + ", " + zCoordinate + ")";
    //cout << "coordinates: " << coordinates <<  endl;
    
    //if outside the maze
    if (x > 4 || x < 0 || y > 4 || y < 0|| z > 4 || z < 0)
    {
        //cout << "out of bounds" << endl;
        return false;
    }
    //if invalid path (0)
    else if (MazeArray[x][y][z] == "0")
    {
        //cout << "invalid path" << endl;
        return false;
    }
    //if already visited (9)
    else if (MazeArray[x][y][z] == "9")
    {
        //cout << "already visited" << endl;
        return false;
    }
    //if at end, return vector
    else if (coordinates == "(4, 4, 4)")
    {
        //cout << "reached the end" << endl;
        path.push_back(coordinates);
        return true;
    }
    else
    {
        //change cell to mark "visited"
        MazeArray[x][y][z] = "9";
        //search neighbors
        if (find(x+1, y, z, MazeArray) || find(x, y+1, z, MazeArray) || find(x, y, z+1, MazeArray) || find(x-1, y, z, MazeArray) || find(x, y-1, z, MazeArray) || find(x, y, z-1, MazeArray))
        {
            //add to vector
            path.push_back(coordinates);
            return true;
        }
    }
    return false;
}
