#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED
#endif // HEAD_H_INCLUDED

#include<SFML/Graphics.hpp>
#include<vector>
#include<fstream>
using namespace sf;
using namespace std;
class Figure{
    int type;
    bool fall = false;
public:
    vector <vector<int>> blocks{4,vector<int>(2)};
    Vector2i corner{0,3};
    Figure(RenderWindow* window);
    void draw_f(RenderWindow* window);
    bool isFall();
    bool isPlace();
    int getType();
    int isBlock(int x,int y);
    void setFall(bool b);
    void setType(int t);
    void rotateRight(RenderWindow* window);
    void rotateLeft(RenderWindow* window);
    void moveRight(RenderWindow* window);
    void moveLeft(RenderWindow* window);
    void moveDown();
    void hardDrop(RenderWindow* window);
};

class Bag{
    Figure* next;
    vector <vector<RectangleShape*>> bag{4,vector<RectangleShape*>(8)};
    vector <vector<int>> hblocks{4,vector<int>(2)};
    bool used = false;
    int htype = -1;
public:
    Bag(Figure* next);
    bool isUsed();
    void setUsed(bool u);
    void pullOut(RenderWindow* window, Figure* current);
    void change(RenderWindow* window, Figure* f);
    void draw_b(RenderWindow* window);
};

class Game{
    int score = 0;
    int lines = 0;
    int level = 1;
    int time = 1000;
    int stage = 1;
    fstream file;
    vector <vector<int>> records={{0,0,0},{0,0,0},{0,0,0}};
    Clock clk;
    Texture txt;
    Font f;
    Text text;
    Text textLvl;
    Text recs[3];
    Sprite s;
    RenderWindow* window;
    Figure* current;
    Bag* b;
    void update(int elapsed);
    void draw();
public:
    Game();
    void start();
    bool isFullLine(vector<RectangleShape*> line);
    void checkLines();
    void GameOver(RenderWindow* window);
};

