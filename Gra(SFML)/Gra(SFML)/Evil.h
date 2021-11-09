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

class Evil{
public:
    Vector2f velocity;
    float bottom, left, right, top;
    bool grav_evil = true;
    bool evil_run = true;
    int x = 0;
    int timee = 0;

    Evil(string imgd) {
        ter.loadFromFile(imgd);
        //IntRect rect (0, 65, 35, 32);
        ludzik.setTexture(ter);
        
        //Sprite ludzik(ter, rect);
        ludzik.scale(0.5, 0.5);
        ludzik.setPosition(400, 600);
    }
    void drawPlayer(RenderWindow& window) {
        window.draw(ludzik);
    }

    void Update() {

        ludzik.move(velocity);
        if (timee == 150) {
            x += 83;
            ludzik.setTextureRect(IntRect(x, 1, 83, 137));
            timee = 0;
        }
        else {
            timee++;
            
            ludzik.setTextureRect(IntRect(x, 1, 83, 137));
        }

        if (x > 429) {
            x = 0;
        }
        bottom = ludzik.getPosition().y +68 ;
        left = ludzik.getPosition().x -20 ;
        right = ludzik.getPosition().x +32 ;
        top = ludzik.getPosition().y;
        bottom = ceil(bottom);
        left = ceil(left);
        right = ceil(right);
        top = ceil(top);
    }
    void move(int x) {
        ludzik.scale(x, 1);
    }
private:
    Texture ter;
    Sprite ludzik;
};

