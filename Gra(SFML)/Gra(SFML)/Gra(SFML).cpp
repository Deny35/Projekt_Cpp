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
#include "Evil.h"
#include "Key.h"
#include "Door.h"
#include "Door_after.h"
#include "Player.h"
#include "Zycie.h"


using namespace sf;
using namespace std;

vector<vector<Vector2i>> mapa1;
Texture tileTexture1;
Sprite tiles1;

int pt[100];
int t = 0;
int x1, x2, x3, y3;
bool win_key = false;
int sa;
int health = 0;
int key_x = 10;
int key_y = 100;
int timee = 100;


void loadMap1(const char* filename) {
    ifstream openfile(filename);
    vector<Vector2i> tempMap;
    mapa1.clear();


    if (openfile.is_open()) {

        string tileLocation;
        openfile >> tileLocation;
        tileTexture1.loadFromFile(tileLocation);
        tiles1.setTexture(tileTexture1);

        while (!openfile.eof()) {

            string str, value;
            getline(openfile, str);
            stringstream stream(str);

            while (getline(stream, value, ' ')) {

                if (value.length() > 0) {

                    string xx = value.substr(0, value.find(','));
                    string yy = value.substr(value.find(',') + 1);

                    int x, y, i, j;

                    for (i = 0; i < xx.length(); i++) {

                        if (!isdigit(xx[i]))
                            break;
                    }

                    for (j = 0; j < xx.length(); j++) {

                        if (!isdigit(yy[j]))
                            break;
                    }

                    x = (i == xx.length()) ? atoi(xx.c_str()) : -1;
                    y = (j == yy.length()) ? atoi(yy.c_str()) : -1;

                    tempMap.push_back(Vector2i(x, y));
                }

            }
            mapa1.push_back(tempMap);
            tempMap.clear();
        }
    }
}

int main() {
 
    loadMap1("Map1.txt");
    RenderWindow window(VideoMode(1408, 768), "SFML works!");
    
    Player player("121.png");
    Evil evil("zlo1.png");
    Key key("key.png", key_x, key_y);
    Door door("door.png", 1308 - 73, 768 - 33 - 85);
    Door_after door_after("door_after.png", 1308 - 73, 768 - 33 - 85);
    Zycie zycie("zycie.png");
    while (window.isOpen()) {

        sf::Event Event;

        while (window.pollEvent(Event)) {

            switch (Event.type) {

            case (Event::Closed):
                window.close();
                break;

            case (Event::KeyPressed):

                break;
            }
            
        }
 

        player.Update();
        evil.Update();
        //zycie.Update(health);
        // RYSOWANIE MAPY I GRAWITACJA
        window.clear(Color(68 ,213, 249));
        t = 0;
        for (int i = 0; i < mapa1.size(); i++) {

            for (int k = 0; k < mapa1[i].size(); k++) {


                if (mapa1[i][k].x != -1 && mapa1[i][k].y != -1) {


                    Sprite sprite1 = tiles1;
                    tiles1.setPosition(k * 32, i * 32);
                    tiles1.setTextureRect(IntRect(mapa1[i][k].x * 32, mapa1[i][k].y * 32, 32, 32));
                    window.draw(tiles1);

                    if (player.grav == true || (player.left > x1 + 32 || player.right < x1)) {

                        if (player.bottom == tiles1.getPosition().y && (player.right >= tiles1.getPosition().x && player.left <= tiles1.getPosition().x + 32)) {

                            x1 = tiles1.getPosition().x;
                            player.velocity.y = 0.0f;
                            player.grav = false;
                            player.jump = true;
                        }
                        else {
                            player.velocity.y = 0.1f;

                        }


                    }
                    // ^
                    // KOLIZJA X
                    if (player.movee == true || player.right < x3  || player.left > x3 + 32 || player.bottom < y3 +32 || player.top > y3 ) {
                        if (player.bottom >= tiles1.getPosition().y + 32 && player.top <= tiles1.getPosition().y && player.left <= tiles1.getPosition().x + 32 && player.right >= tiles1.getPosition().x) {

                            if (player.right >= tiles1.getPosition().x + 32) {
                                player.lewo = false;
                                x3 = tiles1.getPosition().x;
                                y3 = tiles1.getPosition().y;
                                player.movee = false;
                                cout << "1";

                            }
                            if (player.left <= tiles1.getPosition().x) {
                                player.prawo = false;
                                x3 = tiles1.getPosition().x;
                                y3 = tiles1.getPosition().y;
                                player.movee = false;
                                cout << "2";
                            }

                        }
                        else
                        {
                            player.prawo = true;
                            player.lewo = true;
                            player.movee = true;


                        }
                    }
                    // ^
                     //RUCH ZOMBIE
                    if (evil.grav_evil == true || (evil.left > x2 + 32 || evil.right < x2)) {

                        if (evil.bottom == tiles1.getPosition().y && (evil.right >= tiles1.getPosition().x && evil.left <= tiles1.getPosition().x + 32)) {

                            x2 = tiles1.getPosition().x;
                            evil.velocity.y = 0.0f;
                            evil.grav_evil = false;
                            if (evil.evil_run == true) {
                                evil.velocity.x = 0.1f;
                                evil.evil_run = false;
                            }
                        }
                        else {
                            evil.velocity.y = 0.1f;

                        }


                    }

                    if (evil.bottom >= tiles1.getPosition().y + 32 && evil.top <= tiles1.getPosition().y && evil.left <= tiles1.getPosition().x + 32 && evil.right >= tiles1.getPosition().x) {

                        if (evil.right >= tiles1.getPosition().x + 32) {
                            evil.velocity.x = 0.1f;
                            evil.move(-1);

                        }
                        if (evil.left <= tiles1.getPosition().x) {
                            evil.velocity.x = -0.1f;
                            evil.move(-1);


                        }

                    }
                    // ^

                }

            }
        }
        // ZDOBYCIE KLUCZA
        if (win_key == true || (key.right > player.left && key.bottom < player.bottom && key.top > player.top)) {

            door_after.drawDoor(window);
            win_key = true;
            if (door_after.bottom <= player.bottom && door_after.top <= player.top && door_after.left <= player.right) {
                return 0;
            }

        }
        else {

            key.drawKey(window);
            door.drawDoor(window);
        }
        // ^
        // POSTAĆ VS ZOMBIE
        if (evil.bottom <= player.bottom && evil.top <= player.top && (evil.left == player.right || evil.right == player.left)) {
            return 0;
            
        };
        
        //zycie.drawZycie(window);
        player.drawPlayer(window);
        evil.drawPlayer(window);
        window.display();
    }

    return 0;
}