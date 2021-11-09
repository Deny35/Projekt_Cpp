#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cctype>
#include<algorithm>

using namespace sf;
using namespace std;

class Player {
public:
    float bottom, left, right, top;
    vector<Vector2i>tiles;
    Vector2f velocity;

    int timeep = 100;
    int timeel = 100;
    int s = 1;
    bool lewo = true;
    bool prawo = true;
    bool jump = true;
    bool grav = true;
    bool movee = true;
    int px = 860;


    Player(string imgd) {
        ter.loadFromFile(imgd);
        //IntRect rect (0, 65, 35, 32);
        ludzik.setTexture(ter);
        ludzik.setTextureRect(IntRect(860, 20, 143, 122));
        //Sprite ludzik(ter, rect);
        ludzik.scale(0.5, 0.5);
        ludzik.setPosition(10, 600);



    }

    void Update() {


        if (prawo == true && Keyboard::isKeyPressed(Keyboard::D)) {
            velocity.x = 0.2f;

            if (px < 860) {
                px = 860;
            }

            if (timeep == 100) {

                px += 143;
                ludzik.setTextureRect(IntRect(px, 20, 143, 122));
                timeep = 0;
                timeel = 100;
                s = 1;

            }
            else {
                timeep++;
                timeel = 100;

            }
            if (px > 1700) {

                px = 860;
                ludzik.setTextureRect(IntRect(px, 20, 143, 122));
                s = 1;

            }

        }
        else if (lewo == true && Keyboard::isKeyPressed(Keyboard::A)) {
            velocity.x = -0.2f;

            if (px > 860) {
                px = 860;

            }

            if (timeel == 100) {

                px -= 143;
                ludzik.setTextureRect(IntRect(px, 20, -143, 122));
                timeel = 0;
                timeep = 100;
                s = -1;

            }
            else {
                timeel++;
                timeep = 100;

            }
            if (px < 100) {

                px = 860;
                ludzik.setTextureRect(IntRect(px, 20, -143, 122));
                s = -1;

            }
        }
        else {

            velocity.x = 0.0;
            ludzik.setTextureRect(IntRect(860 + s * 143, 20, s * 143, 122));
        }

        if (jump == true && Keyboard::isKeyPressed(Keyboard::Space)) {

           
            velocity.y += -100;
                 
            
            grav = true;
            jump = false;
        }


        ludzik.move(velocity);

        bottom = ludzik.getPosition().y + 58;
        left = ludzik.getPosition().x+20;
        right = ludzik.getPosition().x + 37;
        top = ludzik.getPosition().y;
        bottom = ceil(bottom);
        left = ceil(left);
        right = ceil(right);
        top = ceil(top);

    }

    void drawPlayer(RenderWindow& window) {
        window.draw(ludzik);
    }

private:
    Texture ter;
    Sprite ludzik;
};


