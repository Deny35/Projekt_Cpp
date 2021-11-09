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

class Key {

public:
    int top, bottom, left, right;


    Key(string imgd, int x, int y) {
        ter.loadFromFile(imgd);
        //IntRect rect (0, 65, 35, 32);
        key.setTexture(ter);
        //key.setTextureRect(IntRect(860, 20, 143, 122));
        //Sprite ludzik(ter, rect);
        key.scale(0.25, 0.25);
        key.setPosition(x, y);
        left = key.getPosition().x;
        top = key.getPosition().y;
        bottom = key.getPosition().x + 11;
        left = key.getPosition().y + 27;


    }

    void drawKey(RenderWindow& window) {
        window.draw(key);
    }
private:
    Texture ter;
    Sprite key;
};

