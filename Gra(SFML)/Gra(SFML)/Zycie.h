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

class Zycie {

public:
    int top, bottom, left, right;
    

    Zycie(string imgd) {
        ter.loadFromFile(imgd);
        //IntRect rect (0, 65, 35, 32);
        zycie.setTexture(ter);
        
        //Sprite ludzik(ter, rect);
        //zycie.scale(2, 2);
        zycie.setPosition(0, 0);



    }
    void Update(int x) {
        zycie.setTextureRect(IntRect(x, 0, 40, 73));
    }
    void drawZycie(RenderWindow& window) {
        window.draw(zycie);
    }
private:
    Texture ter;
    Sprite zycie;
};