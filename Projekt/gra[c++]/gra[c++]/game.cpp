#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace sf;
using namespace std;
const int heightMap = 156, weightMap = 120;
float mapMoving_x = 0, mapMoving_y = 0;
string tileMap[heightMap];
int l = 0;
bool win_l1 = false;
bool win_l2 = false;
bool win_l3 = false;
bool win_l4 = false;
bool key1 = false;
bool key2 = false;
bool key3 = false;
bool key4 = false;
bool open1 = true;
bool open2 = true;
bool open3 = true;
bool open4 = true;
bool ledder = true;
bool ledder_d1 = false;
bool ledder_d2 = false;
bool ledder_d3 = false;
bool onLedder = false;
bool power = false;
bool powerDraw = true;
bool p1 = true;
bool p2 = true;
int ledder_c = 0;
int door1_x = -500;
int door1_y = -500;
int door2_x = -500;
int door2_y = -500;
int door3_x = -500;
int door3_y = -500;
int door4_x = -500;
int door4_y = -500;
string set_player;

class doorClose {
public:
	Texture tex;
	Sprite door;
	FloatRect rect;

	doorClose(int x, int y) {
		tex.loadFromFile("door.png");
		door.setTexture(tex);
		door.setTextureRect(IntRect(11, 10, 76, 85));
		rect = FloatRect(x, y, 76, 85);

	}

	void Update() {

		door.setPosition(rect.left - mapMoving_x, rect.top - mapMoving_y);
	}

};

class doorOpen {
public:
	Texture tex;
	Sprite door;
	FloatRect rect;

	doorOpen(int x, int y) {
		tex.loadFromFile("door.png");
		door.setTexture(tex);
		door.setTextureRect(IntRect(11, 300, 76, 85));
		rect = FloatRect(x, y, 76, 85);
	}
	void Update() {

		door.setPosition(rect.left - mapMoving_x, rect.top - mapMoving_y);
	}

};

class loadMap
{
public:
	Texture tileTexture1;
	Sprite tiles1;

	string linie;

	int i = 0;

	void load_map(const char* filename) {

		ifstream File;
		File.open(filename);
		if (File.is_open()) {

			while (getline(File, linie))
			{
				tileMap[i] = linie;
				i++;
			}

		}

	}

};

class Player
{
public:
	float dx = 0;
	float dy = 0;
	FloatRect rect;
	Texture tex;
	Sprite ludzik;
	float currentFrame = 0;
	bool onGround;
	bool moveAble = true;
	Clock clockk;

	Player() {
		tex.loadFromFile(set_player);
		ludzik.setTexture(tex);
		ludzik.setTextureRect(IntRect(16, 143, 32, 46));
		rect = FloatRect(207, 980, 32, 46);
		//dx = dy = 0;
		//currentFrame = 0;

	}
	void agan() {
		
		rect.top = 1000;
		rect.left = 100;
		mapMoving_x = 0;
		mapMoving_y = 0;
	}
	void collisionX() {

		for (int i = rect.top / 30; i < (rect.top + rect.height) / 30; i++)
			for (int j = rect.left / 30; j < (rect.left + rect.width) / 30; j++) {
				if ((tileMap[i][j] == '0')){

					if (dx > 0) {

						rect.left = j * 30 - rect.width;
						moveAble = false;
					}
					if (dx < 0) {

						rect.left = j * 30 + 30;
						moveAble = false;

					}
				}
				else {
					moveAble = true;
				}

				if ((tileMap[i][j] == '1')) {
					key1 = true;
					win_l1 = true;
				}

				if ((tileMap[i][j] == '2')) {
					key2 = true;
					win_l2 = true;
				}

				if ((tileMap[i][j] == '3')) {
					key3 = true;
					win_l3 = true;
				}

				if ((tileMap[i][j] == '4')) {
					key4 = true;
					win_l4 = true;
				}

				if ((tileMap[i][j] == 'l')) {
					ledder_c += 1;
					if (ledder_c == 3) {
						ledder_d1 = true;
						ledder = false;
					}
				}

				if ((tileMap[i][j] == 'i')) {
					ledder_c += 1;
					if (ledder_c == 3) {
						ledder_d2 = true;
						ledder = false;
					}
				}			

				if ((tileMap[i][j] == 'j')) {
					ledder_c += 1;
					if (ledder_c == 3) {
						ledder_d3 = true;
						ledder = false;
					}
				}

				if ((tileMap[i][j] == 'M')) {
					power = true;
					powerDraw = false;
				}

			}
			
		for (int i = rect.top / 30; i < (rect.top + rect.height) / 30; i++)
			for (int j = rect.left / 30; j < (rect.left + 13) / 30; j++) {

				if ((tileMap[i][j] == 'L')) {
					onLedder = true;
				}
				else {
					onLedder = false;

				}

				
			}

		for (int i = rect.top / 30; i < (rect.top + rect.height) / 30; i++)
			for (int j = (rect.left - 5) / 30; j < (rect.left + rect.width + 5) / 30; j++) {

				if ((tileMap[i][j] == 'A') && power == false) {
					agan();
				}

			}




	}

	void collisionY()
	{


		for (int i = rect.top / 30; i <= (rect.top + rect.height) / 30; i++)
			for (int j = (rect.left )/ 30; j <= (rect.left + rect.width - 12) / 30; j++) {

				if ((tileMap[i][j] == 'D') || (tileMap[i][j] == '0')
					|| (tileMap[i][j] == 'G') || (tileMap[i][j] == 'P')
					|| (tileMap[i][j] == 'I') || (tileMap[i][j] == 'J')) {

					if (dy > 0) {
						rect.top = i * 30 - rect.height;
						dy = 0;
						onGround = true;
						//ludzik.setColor(Color::Red);

					}
					if (dy < 0) {
						rect.top = i * 30 + 30;
						dy = 0;
						//ludzik.setColor(Color::Red);
					}
				}
				else {
					onGround = false;
					//ludzik.setColor(Color::Blue);
				}

				if ((tileMap[i][j] == 'H')) {
					agan();
					
				}


			
			}

	}


	void Update(float time)
	{

		rect.left += dx * time;
		collisionX();

		if (onGround == false) {
			dy = dy + 0.0005 * time;
		}
		rect.top += dy * time;
		collisionY();

		if (power == true) {
			int power_time = clockk.getElapsedTime().asSeconds();
			if (power_time > 30) {
				clockk.restart();
				power = false;
			}
		}

		if (onGround == true) {

			currentFrame += 0.001 * time;

			if (currentFrame > 8) currentFrame -= 8;

			if (dx < 0) ludzik.setTextureRect(IntRect(16 + (32 * (int(currentFrame) * 2)), 79, 32, 47));
			if (dx > 0) ludzik.setTextureRect(IntRect(16 + (32 * (int(currentFrame) * 2)), 207, 32, 47));
		}
		ludzik.setPosition(rect.left - mapMoving_x, rect.top - mapMoving_y);
		dx = 0;

	}

};

class Enemy
{
public:
	float dx, dy;
	FloatRect rect;
	Sprite sprite;
	Texture tex;
	float currentFrame;
	bool life;


	Enemy(string imgd, int x, int y)
	{

		tex.loadFromFile(imgd);
		sprite.setTexture(tex);
		sprite.setTextureRect(IntRect(21, 211, 22, 43));
		rect = FloatRect(x, y, 22, 43);
		dx = -0.05;
		currentFrame = 0;
		life = true;

	}

	void Update(float time)
	{
		rect.left += dx * time;

		collision();

		currentFrame += 0.009 * time;
		if (currentFrame > 7) currentFrame -= 7;

		if (dx < 0) {
			sprite.setTextureRect(IntRect(84 + ((41 + 22) * int(currentFrame)), 83, 23 + (2 * currentFrame), 43));
		}
		if (dx > 0) {
			sprite.setTextureRect(IntRect(84 + ((41 + 22) * int(currentFrame)), 211, 23 + currentFrame, 43));
		}


		sprite.setPosition(rect.left - mapMoving_x, rect.top - mapMoving_y);

	}


	void collision()
	{
		for (int i = rect.top / 30; i < (rect.top + rect.height) / 30; i++)
			for (int j = rect.left / 30; j < (rect.left + rect.width) / 30; j++)
				if ((tileMap[i][j] == 'S')) {
					if (dx > 0) {
						rect.left = j * 30 - rect.width;
						dx *= -1;
					}
					else if (dx < 0) {
						rect.left = j * 30 + 30;
						dx *= -1;
					}

				}
	}


};

int main()
{
	RenderWindow window(VideoMode(1024, 420), "window");
 
	Texture tMenu;
	Sprite sMenu;
	Texture tPlay;
	Sprite sPlay;
	Texture tLevel1;
	Sprite sLevel1;
	Texture tLevel2;
	Sprite sLevel2;
	Texture tLevel3;
	Sprite sLevel3;
	Texture tLevel4;
	Sprite sLevel4;
	Texture tChar;
	Sprite sChar;
	Texture tPostac1;
	Sprite sPostac1;
	Texture tPostac2;
	Sprite sPostac2;


	while (window.isOpen()){
		
		tMenu.loadFromFile("menu.png");
		sMenu.setTexture(tMenu);
		

		tPlay.loadFromFile("start.png");
		sPlay.setTexture(tPlay);
		sPlay.setPosition(400-12, 20);

		tLevel1.loadFromFile("poziom1.png");
		sLevel1.setTexture(tLevel1);
		sLevel1.setPosition(13, 130);

		tLevel2.loadFromFile("poziom2.png");
		sLevel2.setTexture(tLevel2);
		sLevel2.setPosition(263, 130);

		tLevel3.loadFromFile("poziom3.png");
		sLevel3.setTexture(tLevel3);
		sLevel3.setPosition(513, 130);

		tLevel4.loadFromFile("poziom4.png");
		sLevel4.setTexture(tLevel4);
		sLevel4.setPosition(763, 130);

		tPostac1.loadFromFile("postac1.png");
		sPostac1.setTexture(tPostac1);
		sPostac1.setPosition(265-12, 240);

		tPostac2.loadFromFile("postac2.png");
		sPostac2.setTexture(tPostac2);
		sPostac2.setPosition(535-12, 240);

	

		int mx = Mouse::getPosition(window).x;
		int my = Mouse::getPosition(window).y;

		if (mx >= 400 && mx <= 650 && my >= 20 && my <= 100){
			sPlay.setColor(Color::Blue);
		}
		else {
			sPlay.setColor(Color(208, 244, 247));

		}
/*
		if (mx >= 13 && mx <= 263 && my >= 130 && my <= 230) {
			sLevel1.setColor(Color::Blue);
		}
		else {
			sLevel1.setColor(Color(208, 244, 247));
		}

		if (mx >= 263 && mx <= 513 && my >= 130 && my <= 230) {
			sLevel2.setColor(Color::Blue);
		}
		else {
			sLevel2.setColor(Color(208, 244, 247));
		}

		if (mx >= 513 && mx <= 763 && my >= 130 && my <= 230) {
			sLevel3.setColor(Color::Blue);
		}
		else {
			sLevel3.setColor(Color(208, 244, 247));
		}

		if (mx >= 763 && mx <= 1013 && my >= 130 && my <= 230) {
			sLevel4.setColor(Color::Blue);
		}
		else {
			sLevel4.setColor(Color(208, 244, 247));
		}
*/
		if (mx >= 265 && mx <= 515 && my >= 240 && my <= 340) {
			sPostac1.setColor(Color::Blue);
		}
		else {
			if (p1 == true)
			sPostac1.setColor(Color(208, 244, 247));
		}

		if (mx >= 535 && mx <= 785 && my >= 240 && my <= 340) {
			sPostac2.setColor(Color::Blue);
		}
		else {
			if(p2==true)
			sPostac2.setColor(Color(208, 244, 247));
		}
		
		if (Mouse::isButtonPressed(Mouse::Left)){
			
			if (mx >= 400 && mx <= 650 && my >= 20 && my <= 100){
				goto gra;
			}
			
			if (mx >= 265 && mx <= 515 && my >= 240 && my <= 340) {
				set_player = "player1.png";
				sPostac2.setColor(Color(208, 244, 247));
				sPostac1.setColor(Color::Blue);
				p1 = false;
				p2 = true;
			}

			if (mx >= 535 && mx <= 785 && my >= 240 && my <= 340) {
				set_player = "player2.png";
				sPostac1.setColor(Color(208, 244, 247));
				sPostac2.setColor(Color::Blue);
				p2 = false;
				p1 = true;
			}

		}

		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed)
				window.close();
		}
		

		window.clear();
		window.draw(sMenu);
		window.draw(sPlay);
		//window.draw(sLevel1);
		//window.draw(sLevel2);
		//window.draw(sLevel3);
		//window.draw(sLevel4);
		window.draw(sPostac1);
		window.draw(sPostac2);
		window.display();
	}

gra:
	
	loadMap load_map;
	load_map.load_map("MAPY.txt");

	Player player;
	Clock clock;
	Clock clockk;
	
	Texture tileTexture;
	Sprite tileSprite;
	tileTexture.loadFromFile("world.png");
	tileSprite.setTexture(tileTexture);

	Enemy enemy1("evil.png", 2800, 1068);
	Enemy enemy2("evil.png", 300, 1250);
	Enemy enemy3("evil.png", 1937, 2390);
	Enemy enemy4("evil.png", 1260, 4580);
	
	doorClose door_close1(3390, 1026);
	doorClose door_close2(3390, 1265);
	doorClose door_close3(3420, 3395);
	doorClose door_close4(3450, 4565);

	



	
	while (window.isOpen())
	{
		doorOpen door_open1(door1_x, door1_y);
		doorOpen door_open2(door2_x, door2_y);
		doorOpen door_open3(door3_x, door3_y);
		doorOpen door_open4(door4_x, door4_y);

		
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 700;// spowolnienie czasu aby ruch i animacja byly lepsze

		if (player.onGround == true) {
			player.ludzik.setTextureRect(IntRect(16, 143, 32, 46));
		}
		
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
		}
		// RUCH LEWO
		if (Keyboard::isKeyPressed(Keyboard::Left) && player.moveAble == true) {
			if (player.onGround == true) {;
				player.ludzik.setTextureRect(IntRect(518, 79, 32, 46));
			}
			if (player.onGround == false) {
				player.ludzik.setTextureRect(IntRect(80, 80, 32, 46));
			}
			player.dx = -0.2;
		}
		// ^
		// RUCH PRAWO
		if (Keyboard::isKeyPressed(Keyboard::Right) && player.moveAble == true) {
			if (player.onGround == true) {
				player.ludzik.setTextureRect(IntRect(16, 207, 32, 46));
			}

			if (player.onGround == false) {
				player.ludzik.setTextureRect(IntRect(80, 208, 32, 46));
			}

			player.dx = 0.2;
		}
		// ^
		// SKOSK
		if (Keyboard::isKeyPressed(Keyboard::Up)) {

			if (player.onGround == true) {
				player.ludzik.setTextureRect(IntRect(16, 143, 32, 46));
				player.dy = -0.4;
				player.onGround = false;

			}

		}
		// ^
		// DRABINA
		if (Keyboard::isKeyPressed(Keyboard::Space)) {

			if ( onLedder == true) {
				//player.ludzik.setTextureRect(IntRect(16, 143, 32, 46));
				player.dy = -0.1;
				

			}

		}
		// ^
		player.Update(time);
		enemy1.Update(time);
		enemy2.Update(time);
		enemy3.Update(time);
		enemy4.Update(time);
		door_close1.Update();
		door_open1.Update();
		door_close2.Update();
		door_open2.Update();
		door_close3.Update();
		door_open3.Update();
		door_close4.Update();
		door_open4.Update();

		if (door_open1.rect.left < player.rect.left && door_open1.rect.left + 76 > player.rect.left + 32 && door_open1.rect.top < player.rect.top && door_open1.rect.top + 85 > player.rect.top + 20) {

			player.rect.left = 207;
			player.rect.top = 2024;
			mapMoving_x = 0;
			mapMoving_y = 2024;
		}
		if (door_open2.rect.left < player.rect.left && door_open2.rect.left + 76 > player.rect.left + 32 && door_open2.rect.top < player.rect.top && door_open2.rect.top + 85 > player.rect.top + 20) {

			player.rect.left = 207;
			player.rect.top = 3380;
		}
		if (door_open3.rect.left < player.rect.left && door_open3.rect.left + 76 > player.rect.left + 32 && door_open3.rect.top < player.rect.top && door_open3.rect.top + 85 > player.rect.top + 20) {

			player.rect.left = 207;
			player.rect.top = 4550;
		}



		// RUCH MAPY
		if (player.rect.left > 300) {
			mapMoving_x = player.rect.left - 300;
		}

		if (player.rect.top > 260){
			mapMoving_y = player.rect.top - 260;
		}
		// ^
		
		if (player.rect.intersects(enemy1.rect))
		{
			if (enemy1.life == true && power == false)
			{
				if (player.dy > 0)
				{
					enemy1.dx = 0;
					player.dy = -0.2;
					enemy1.life = false;
				}
				else {
					player.agan();
				}
			}
			
		}

		if (player.rect.intersects(enemy2.rect))
		{
			if (enemy2.life == true && power == false)
			{
				if (player.dy > 0)
				{
					enemy2.dx = 0;
					player.dy = -0.2;
					enemy2.life = false;
				}
				else {
					player.agan();
				}
			}
		}

		if (player.rect.intersects(enemy3.rect))
		{
			if (enemy3.life == true && power == false)
			{
				if (player.dy > 0)
				{
					enemy3.dx = 0;
					player.dy = -0.2;
					enemy3.life = false;
				}
				else {
					player.agan();
				}
			}
		}

		if (player.rect.intersects(enemy4.rect))
		{
			if (enemy4.life == true && power == false)
			{
				if (player.dy > 0)
				{
					enemy4.dx = 0;
					player.dy = -0.2;
					enemy4.life = false;
				}
				else {
					player.agan();
				}

			}
		}
		
		
		window.clear(Color(208, 244, 247));

		for (int i = 0; i < heightMap; i++) {
			for (int j = 0; j < weightMap; j++) {

				if (tileMap[i][j] == 'D') tileSprite.setTextureRect(IntRect(91, 128, 30, 30));
				if (tileMap[i][j] == 'G') tileSprite.setTextureRect(IntRect(91, 159, 30, 30));
				if (tileMap[i][j] == 'K') tileSprite.setTextureRect(IntRect(30, 102, 30, 30));
				if (tileMap[i][j] == 'S') tileSprite.setTextureRect(IntRect(91, 189, 30, 30));
				if (tileMap[i][j] == 'I' || tileMap[i][j] == 'J') tileSprite.setTextureRect(IntRect(0, 183, 30, 30));
				
				if (powerDraw == true) {
					if (tileMap[i][j] == 'M') tileSprite.setTextureRect(IntRect(182, 83, 10, 15));
				}
				else{
					if (tileMap[i][j] == 'M') continue;
				}

				if (key1 == false) {
					if (tileMap[i][j] == '1') tileSprite.setTextureRect(IntRect(121, 84, 30, 15));
				}
				else {
					if (tileMap[i][j] == '1') continue;
				}

				if (key2 == false) {
					if (tileMap[i][j] == '2') tileSprite.setTextureRect(IntRect(121, 84, 30, 15));
				}
				else {
					if (tileMap[i][j] == '2') continue;
				}

				if (key3 == false) {
					if (tileMap[i][j] == '3') tileSprite.setTextureRect(IntRect(121, 84, 30, 15));
				}
				else {
					if (tileMap[i][j] == '3') continue;
				}

				if (key4 == false) {
					if (tileMap[i][j] == '4') tileSprite.setTextureRect(IntRect(121, 84, 30, 15));
				}
				else {
					if (tileMap[i][j] == '4') continue;
				}

				if (ledder == false) {
					if (tileMap[i][j] == 'L') tileSprite.setTextureRect(IntRect(151, 167, 30, 30));
				}
				else {
					if (tileMap[i][j] == 'L') continue;
				}

				if (ledder_d1 == false) {
					if (tileMap[i][j] == 'l') tileSprite.setTextureRect(IntRect(71, 0, 30, 15));
				}
				else {
					if (tileMap[i][j] == 'l') continue;
				}

				if (ledder_d2 == false) {
					if (tileMap[i][j] == 'i') tileSprite.setTextureRect(IntRect(90, 15, 30, 15));
				}
				else {
					if (tileMap[i][j] == 'i') continue;
				}

				if (ledder_d3 == false) {
					if (tileMap[i][j] == 'j') tileSprite.setTextureRect(IntRect(151, 173, 30, 15));
				}
				else {
					if (tileMap[i][j] == 'j') continue;
				}

				if ((tileMap[i][j] == ' ') || (tileMap[i][j] == '0') || (tileMap[i][j] == 'H') || (tileMap[i][j] == 'A')) continue;

				tileSprite.setPosition(j * 30 - mapMoving_x, i * 30 - mapMoving_y);
				window.draw(tileSprite);
			}
		}
		window.draw(player.ludzik);
		if (enemy1.life == true) {
			window.draw(enemy1.sprite);
		}

		if (enemy2.life == true) {
			window.draw(enemy2.sprite);
		}

		if (enemy3.life == true) {
			window.draw(enemy3.sprite);
		}

		if (enemy4.life == true) {
			window.draw(enemy4.sprite);
		}

		if (win_l1 == true) {
			
			window.draw(door_open1.door);
			if (open1 == true) {
				door1_x = 3390;
				door1_y = 1026;
				open1 = false;
			}
		}
		else {
			window.draw(door_close1.door);

		}

		if (win_l2 == true) {

			window.draw(door_open2.door);
			if (open2 == true) {
				door2_x = 3390;
				door2_y = 1265;
				open2 = false;
			}
		}
		else {
			window.draw(door_close2.door);

		}

		if (win_l3 == true) {

			window.draw(door_open3.door);
			if (open3 == true) {
				door3_x = 3420;
				door3_y = 3395;
				open3 = false;
			}
		}
		else {
			window.draw(door_close3.door);

		}

		

		window.display();

	}

	return 0;
}
