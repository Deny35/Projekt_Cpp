#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include<algorithm>
#include<math.h>
#include <time.h>
#include <windows.h>

using namespace sf;
using namespace std;

class Door {

public:
    float bottom, left, right, top;

    Door(string imgd, int x, int y) {
        ter.loadFromFile(imgd);
        //IntRect rect (0, 65, 35, 32);
        door.setTexture(ter);
        //door.setTextureRect(IntRect(860, 20, 143, 122));
        //Sprite ludzik(ter, rect);
        //door.scale(0.5, 0.5);
        door.setPosition(x, y);
    }

    void drawDoor(RenderWindow& window) {
        window.draw(door);
    }


private:
    Texture ter;
    Sprite door;
};

