//
//  main.cpp
//  Lab 05
//
//  Created by Zac Clark on 2/8/16.
//  Copyright © 2016 Zac Clark. All rights reserved.
//

#include <iostream>
#include <sstream>
#include "Pathfinder.h"

using namespace std;

vector <string> find(int x, int y, int z, string MazeArray[5][5][5])
{
    vector<string> path;
    string coordinates; // (x, y, z)
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

    for (int i = 0; i < path.size(); i++)
    {
        //already visited - erase duplicate already in vector
        if (path[i] == coordinates)
        {
            path[i].erase();
        }
    }
    //if at end, return vector
    if (coordinates == "(4, 4, 4)")
    {
        return path;
    }
    else if (MazeArray[x+1][y][z] == "1")
    {
        //add to vector
        path.push_back(coordinates);
        if (x !=4)
            find(x+1, y, z, MazeArray);
        else
            find(x-1, y, z, MazeArray);
        
    }
    else if (MazeArray[x-1][y][z] == "1")
    {
        //add to vector
        path.push_back(coordinates);
        if (x !=4)
            find(x-1, y, z, MazeArray);
        else
            find(x, y+1, z, MazeArray);
    }
    else if (MazeArray[x][y+1][z] == "1")
    {
        //add to vector
        path.push_back(coordinates);
        if (y !=4)
            find(x, y+1, z, MazeArray);
        else
            find(x, y-1, z, MazeArray);
    }
    else if (MazeArray[x][y-1][z] == "1")
    {
        //add to vector
        path.push_back(coordinates);
        if (y !=4)
            find(x, y-1, z, MazeArray);
        else
            find(x, y, z+1, MazeArray);
    }
    else if (MazeArray[x][y][z+1] == "1")
    {
        //add to vector
        path.push_back(coordinates);
        if (z !=4)
            find(x, y, z+1, MazeArray);
        else
            find(x, y, z-1, MazeArray);
    }
    else if (MazeArray[x][y][z-1] == "1")
    {
        //add to vector
        path.push_back(coordinates);
        if (z !=4)
            find(x, y, z-1, MazeArray);
        else
            find(x+1, y, z, MazeArray);
    }
    
    
    return path;
}

int main(int argc, const char * argv[]) {
    
    string newMazeArray[5][5][5];
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
                newMazeArray[x][y][z] = newValue_string;
            }
        }
    }
    newMazeArray[0][0][0] = "1";
    newMazeArray[4][4][4] = "1";
    
    string output;
    for (int z = 0; z < 5; z++)
    {
        //jump y coordinate
        for (int y = 0; y < 5; y++)
        {
            //jump x coordinate
            for (int x = 0; x < 5; x++)
            {
                if (x <= 3)
                    output += newMazeArray[x][y][z] + " ";
                else
                    output += newMazeArray[x][y][z];
            }
            output += "\n";
        }
        if (z <= 3)
            output += "\n";
    }
    
cout << output << endl;

    //find(0, 0, 0, newMazeArray);

    return 0;
}
