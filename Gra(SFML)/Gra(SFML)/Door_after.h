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

class Door_after {

public:
    int top, bottom, left, right;

    Door_after(string imgd, int x, int y) {
        ter.loadFromFile(imgd);
        //IntRect rect (0, 65, 35, 32);
        door.setTexture(ter);
        //door.setTextureRect(IntRect(860, 20, 143, 122));
        //Sprite ludzik(ter, rect);
        door.scale(2.0, 2.0);
        door.setPosition(x, y);
        left = door.getPosition().x;
        top = door.getPosition().y;
        bottom = door.getPosition().y + 86;
        right = door.getPosition().x + 74;

    }

    void drawDoor(RenderWindow& window) {
        window.draw(door);
    }
private:
    Texture ter;
    Sprite door;
};

