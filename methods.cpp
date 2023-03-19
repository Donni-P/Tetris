#include <SFML/Graphics.hpp>
#include<cstdlib>
#include"head.h"
#include<vector>
#include<iostream>
#include<math.h>
#include<fstream>
using namespace sf;
using namespace std;
vector <vector<RectangleShape*>> matrix(21,vector<RectangleShape*>(10));
vector <vector<RectangleShape*>> figuresPocket(3,vector<RectangleShape*>(22));
vector <vector<RectangleShape*>> buffer(4,vector<RectangleShape*>(4));
vector<Color> cpocket={Color::Green,Color::Magenta,Color::Yellow,Color::Red,Color::Cyan,Color::Blue,Color(255,165,0,255)};
void matrixClear(){
    for(int i=0;i<21;i++){
        matrix[i].clear();
        matrix[i].insert(matrix[i].begin(),10,NULL);
    }
}
void bufferClear(){
    for(int i=0;i<4;i++)
        for(int j = 0; j<4;j++)
            buffer[i][j] = NULL;
}
void fillPocket(){
    for(int i=1;i<14;i++){
        figuresPocket[1][i]=new RectangleShape(Vector2f(28,28));
        figuresPocket[1][i]->setOutlineColor(Color::Black);
        figuresPocket[1][i]->setOutlineThickness(2);
    }
    for(int i=3;i<12;i+=4){
        figuresPocket[0][i]=new RectangleShape(Vector2f(28,28));
        figuresPocket[0][i]->setOutlineColor(Color::Black);
        figuresPocket[0][i]->setOutlineThickness(2);
    }
    for(int i=0;i<15;i+=13){
        figuresPocket[0][i]=new RectangleShape(Vector2f(28,28));
        figuresPocket[0][i]->setOutlineColor(Color::Black);
        figuresPocket[0][i]->setOutlineThickness(2);
        figuresPocket[0][i+1]=new RectangleShape(Vector2f(28,28));
        figuresPocket[0][i+1]->setOutlineColor(Color::Black);
        figuresPocket[0][i+1]->setOutlineThickness(2);
    }
    for(int i=16;i<18;i++){
        figuresPocket[0][i]=new RectangleShape(Vector2f(28,28));
        figuresPocket[0][i]->setOutlineColor(Color::Black);
        figuresPocket[0][i]->setOutlineThickness(2);
    }
    for(int i=16;i<22;i++){
        figuresPocket[1][i]=new RectangleShape(Vector2f(28,28));
        figuresPocket[1][i]->setOutlineColor(Color::Black);
        figuresPocket[1][i]->setOutlineThickness(2);
    }
}

//====================================================================================

Figure::Figure(RenderWindow* window){
    if(figuresPocket[1] == figuresPocket[2])fillPocket();
    int ind = rand()%7;
    while(figuresPocket[1][1+ind*3] == NULL)ind = rand()%7;
    int cb = 0;
    type = ind;
    int d = 0;
    if(type == 6)d++;
    for(int i = 0;i<3+d;i++){
        matrix[0][3+i] = figuresPocket[0][ind*3+i];
        if(figuresPocket[0][ind*3+i] != NULL){
            matrix[0][3+i]->setFillColor(cpocket[ind]);
            blocks[cb][0] = 0; blocks[cb][1] = 3+i;
            cb++;
        }
        matrix[1][3+i] = figuresPocket[1][ind*3+i];
        if(figuresPocket[1][ind*3+i] != NULL){
            matrix[1][3+i]->setFillColor(cpocket[ind]);
            blocks[cb][0] = 1; blocks[cb][1] = 3+i;
            cb++;
        }
        figuresPocket[1][ind*3+i] = NULL;
    }
}
bool Figure::isPlace(){
    return (matrix[0][3]==NULL && matrix[0][4]==NULL && matrix[0][5]==NULL && matrix[0][6]==NULL &&
    matrix[1][3]==NULL && matrix[1][4]==NULL && matrix[1][5]==NULL && matrix[1][6]==NULL);
}
void Figure::draw_f(RenderWindow* window){
    for(int i=1;i<21;i++){
        for(int j=0;j<10;j++){
            if(matrix[i][j]!=NULL){
                matrix[i][j]->setPosition(150+30*j,181+30*(i-1));
                window->draw(*matrix[i][j]);
            }
        }
    }
}
int Figure::isBlock(int x,int y){
    for(int i=0;i<4;i++){
        if(blocks[i][0]==x && blocks[i][1]==y)
            return i;
    }
    return -1;
}
int Figure::getType(){return type;}
void Figure::moveLeft(RenderWindow* window){
    int d=0;
    if(type==6)d++;
    bool moveImp = true;
    for(int i = corner.x;i<corner.x+3+d;i++){
        for(int j = corner.y;j<corner.y+3+d;j++){
            if(isBlock(i,j)!=-1){
                if(matrix[i][j-1] != NULL || j < 0){
                    moveImp = false;
                }else {j = corner.y+3;}
            }
        }
    }
    if(moveImp){
        for(int i = corner.x;i<corner.x+3+d;i++){
            for(int j = corner.y;j<corner.y+3+d;j++){
                int indb = isBlock(i,j);
                if(indb != -1){
                    swap(matrix[i][j],matrix[i][j-1]);
                    blocks[indb][1]=j-1;
                }
            }
        }
        corner.y -=1;
        draw_f(window);
    }
}
void Figure::moveRight(RenderWindow* window){
    int d=0;
    if(type==6)d++;
    bool moveImp = true;
    for(int i = corner.x+2+d;i>=corner.x;i--){
        for(int j = corner.y+2+d;j>=corner.y;j--){
            if(isBlock(i,j)!=-1){
                if(matrix[i][j+1] != NULL || j > 9){
                    moveImp = false;
                }else {j = corner.y-1;}
            }
        }
    }
    if(moveImp){
        for(int i = corner.x+2+d;i>=corner.x;i--){
            for(int j = corner.y+2+d;j>=corner.y;j--){
                int indb = isBlock(i,j);
                if(indb != -1){
                    swap(matrix[i][j],matrix[i][j+1]);
                    blocks[indb][1]=j+1;
                }
            }
        }
        corner.y +=1;
        draw_f(window);
    }
}
void Figure::moveDown(){
    int d=0;
    if(type==6)d++;
    bool moveImp = true;
    for(int i = corner.y;i < corner.y+3+d; i++){
        for(int j = corner.x+2+d;j>=corner.x; j--){
            if(isBlock(j,i)!=-1){
                if( j+1 > 20){//ошибка
                    moveImp = false;
                }else if(matrix[j+1][i] != NULL){
                    moveImp = false;
                }else {j = corner.x-1;}
            }
        }
    }
    if(moveImp){
        for(int i = corner.y;i < corner.y+3+d; i++){
            for(int j = corner.x+2+d;j>=corner.x; j--){
                int indb = isBlock(j,i);
                if(indb != -1){
                    swap(matrix[j][i],matrix[j+1][i]);
                    blocks[indb][0]=j+1;
                }
            }
        }
        corner.x += 1;
    }else{setFall(true);}
}
bool Figure::isFall(){return fall;}
void Figure::setFall(bool b){fall = b;}
void Figure::setType(int t){type = t;}
void Figure::rotateRight(RenderWindow* window){
    if(type!=5){
    int d=0;int c=0;
    if(type==6)d++;
    bool moveImp = true;
    for(int i = corner.x;i<corner.x+3+d;i++){
        for(int j = corner.y;j<corner.y+3+d;j++){
            if(isBlock(i,j)!=-1){
                if(matrix[corner.x+j-corner.y][corner.y+2+d-i+corner.x] != NULL && isBlock(corner.x+j-corner.y,corner.y+2+d-i+corner.x) == -1){
                    moveImp = false;
                }
                buffer[j-corner.y][2+d-i+corner.x] = matrix[i][j];
            }
        }
    }
    if(moveImp){
        for(int i=0;i<4;i++){
            matrix[corner.x+blocks[i][1]-corner.y][corner.y+2+d-blocks[i][0]+corner.x] = matrix[blocks[i][0]][blocks[i][1]];
            if(buffer[blocks[i][0]-corner.x][blocks[i][1]-corner.y] == NULL)
                matrix[blocks[i][0]][blocks[i][1]] = NULL;
            int b0 = blocks[i][0];
            blocks[i][0] = corner.x+blocks[i][1]-corner.y;
            blocks[i][1] = corner.y+2+d-b0+corner.x;
        }
        draw_f(window);
    }
    bufferClear();
    }
}
void Figure::rotateLeft(RenderWindow* window){
    if(type!=5){
    int d=0;int c=0;
    if(type==6)d++;
    bool moveImp = true;
    for(int i = corner.x;i<corner.x+3+d;i++){
        for(int j = corner.y;j<corner.y+3+d;j++){
            if(isBlock(i,j)!=-1){
                //buffer[i-corner.x][j-corner.y] = matrix[i][j];
                if(matrix[corner.x+2+d-j+corner.y][corner.y+i-corner.x] != NULL && isBlock(corner.x+2+d-j+corner.y,corner.y+i-corner.x) == -1){
                    moveImp = false;
                }
                buffer[2+d-j+corner.y][i-corner.x] = matrix[i][j];
            }
        }
    }
    if(moveImp){
        for(int i=0;i<4;i++){
            matrix[corner.x+2+d-blocks[i][1]+corner.y][corner.y+blocks[i][0]-corner.x] = matrix[blocks[i][0]][blocks[i][1]];
            if(buffer[blocks[i][0]-corner.x][blocks[i][1]-corner.y] == NULL)
                matrix[blocks[i][0]][blocks[i][1]] = NULL;
            int b0 = blocks[i][0];
            blocks[i][0] = corner.x+2+d-blocks[i][1]+corner.y;
            blocks[i][1] = corner.y+b0-corner.x;
        }
        draw_f(window);
    }
    bufferClear();
    }
}
void Figure::hardDrop(RenderWindow* window){
    while(fall != true)moveDown();
    draw_f(window);
}

//======================================================================================

Game::Game(){
    window = new RenderWindow(VideoMode(900,900), "TETRIS");
}
void Game::update(int elapsed){
        Event event;
        while (window->pollEvent(event))
        {
            if (event.type == Event::Closed){
                window->close();
                file.close();
                file.open("recs.txt",fstream::out | fstream::trunc);
                for(int i=0;i<3;i++)
                    for(int j=0;j<3;j++)
                        file<<records[i][j]<<" ";
                file.close();
            }
            if(stage == 1){
                if(event.type == Event::MouseButtonPressed){
                    if(event.mouseButton.x >= 252 && event.mouseButton.x<=632 && event.mouseButton.y >= 237 && event.mouseButton.y <= 353){
                        stage = 3;
                        Figure* nexT = new Figure(window);
                        b = new Bag(nexT);
                        current = new Figure(window);
                    }
                    if(event.mouseButton.x >= 250 && event.mouseButton.x<=630 && event.mouseButton.y >= 440 && event.mouseButton.y <= 556)
                        stage = 2;
                    if(event.mouseButton.x >= 249 && event.mouseButton.x<=629 && event.mouseButton.y >= 628 && event.mouseButton.y <= 744){
                        stage = 4;
                        for(int i=0;i<3;i++){
                            string s = "score: ";
                            s.append(to_string(records[i][0]));
                            s.append("  lines: ");
                            s.append(to_string(records[i][1]));
                            s.append("  level: ");
                            s.append(to_string(records[i][2]));
                            recs[i].setFont(f);
                            recs[i].setPosition(600,590);
                            recs[i].setColor(Color::Black);
                            recs[i].setCharacterSize(30);
                            recs[i].setString(s);
                            recs[i].setPosition(277,180+i*200);
                        }
                    }
                }
            }
            if(stage == 2){
                if(event.type == Event::MouseButtonPressed){
                    if(event.mouseButton.x >= 379 && event.mouseButton.x <= 520 && event.mouseButton.y >= 756 && event.mouseButton.y <= 829)
                        stage = 1;
                }
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Key::Escape)
                        stage = 1;
                }
            }
            if(stage == 3){
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Key::Right)
                        current->moveRight(window);
                    if(event.key.code == Keyboard::Key::Left)
                        current->moveLeft(window);
                    if(event.key.code == Keyboard::Key::Down){
                        current->moveDown();
                        current->draw_f(window);
                    }
                    if(event.key.code == Keyboard::Key::Up)
                        current->rotateRight(window);
                    if(event.key.code == Keyboard::Key::LAlt)
                        current->rotateLeft(window);
                }
                if(event.type == Event::KeyReleased){
                    if(event.key.code == Keyboard::Key::Space)
                        current->hardDrop(window);
                    if(event.key.code == Keyboard::Key::LShift){
                        if(!(b->isUsed()))
                            b->change(window,current);
                    }
                }
            }
            if(stage == 4){
                if(event.type == Event::MouseButtonPressed){
                    if(event.mouseButton.x >= 420 && event.mouseButton.x <= 561 && event.mouseButton.y >= 732 && event.mouseButton.y <= 805)
                        stage = 1;
                }
                if(event.type == Event::KeyPressed){
                    if(event.key.code == Keyboard::Key::Escape)
                        stage = 1;
                }
            }
        }
        if(stage == 3){
            if(current->isFall()){
                if(!current->isPlace()){
                    GameOver(window);
                }else{
                    b->setUsed(false);
                    checkLines();
                    b->pullOut(window,current);
                }
            }else if(elapsed>time){
                current->moveDown();
                elapsed = clk.restart().asSeconds();
            }
        }
}
void Game::draw(){
    window->clear();
    s.setTextureRect(IntRect(stage*900-900,0,900,900));
    window->draw(s);
    if(stage == 3){
        current->draw_f(window);
        b->draw_b(window);
        window->draw(text);
        window->draw(textLvl);
    }
    if(stage==4){
        for(int i=0;i<3;i++)
            window->draw(recs[i]);
    }
    window->display();
}
void Game::start(){
    file.open("recs.txt",fstream::in | fstream::out | fstream::app);
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            file>>records[i][j];
    txt.loadFromFile("txttetris.png");
    f.loadFromFile("ROGFontsv1.6-Regular.ttf");
    text.setFont(f);textLvl.setFont(f);
    text.setPosition(600,590);textLvl.setPosition(660,680);
    text.setColor(Color::Black);textLvl.setColor(Color::Black);
    text.setCharacterSize(35);textLvl.setCharacterSize(60);
    text.setString(to_string(score));textLvl.setString(to_string(level));
    s.setTexture(txt);
    while (window->isOpen())
    {
        int elapsed = clk.getElapsedTime().asMilliseconds();
        update(elapsed);
        draw();
    }
}
bool Game::isFullLine(vector<RectangleShape*> line){
    bool full = true;
    for(auto x : line)
        if(x == NULL)full = false;
    return full;
}
void Game::checkLines(){
    bool L = false;
    int addS = 0;
    for(int x = 0; x < 4; x++){
        for(int i = 20;i >= 1; i--){
            if(isFullLine(matrix[i]) && !L){
                matrix[i].clear();
                matrix[i].insert(matrix[i].begin(),10,NULL);
                L = true;
                lines++;
                addS = addS*2 + 100;
            }
            if(L)swap(matrix[i],matrix[i-1]);
        }
        L = false;
    }
    score += addS;
    level = 1 + lines/8;
    time = pow((0.8-((level-1)*0.007)),level-1)*1000;
    text.setString(to_string(score));
    textLvl.setString(to_string(level));
}
void Game::GameOver(RenderWindow* window){
    stage = 1;
    matrixClear();
    RectangleShape sh(Vector2f(301,601));
    sh.setPosition(148,179);
    sh.setFillColor(Color(47,79,79,200));
    window->draw(sh);
    Text T("game over",f,50);
    T.setPosition(178,379);
    T.setColor(Color::Red);
    window->draw(T);
    window->display();
    for(int i=0; i < 3; i++){
        if(score > records[i][0]){
            if(i <= 1){
                swap(records[1][0],records[2][0]);
                swap(records[1][1],records[2][1]);
                swap(records[1][2],records[2][2]);
            }
            if(i == 0){
                swap(records[i][0],records[i+1][0]);
                swap(records[i][1],records[i+1][1]);
                swap(records[i][2],records[i+1][2]);
            }
            records[i][0] = score;
            records[i][1] = lines;
            records[i][2] = level;
            i = 3;
        }
    }
    score = 0;
    level = 1;
    lines = 0;
    text.setString(to_string(score));textLvl.setString(to_string(level));
    while(!Keyboard::isKeyPressed(Keyboard::Key::Escape)){}
}

//==================================================================================

Bag::Bag(Figure* n){
    next = n;
    hblocks[0][0] = -1;
    for(int i=0;i<4;i++){
        for(int j=3;j<7;j++){
            if(next->isBlock(i,j) != -1){
                bag[i][j-3] = matrix[i][j];
                matrix[i][j] = NULL;
            }
        }
    }
}
bool Bag::isUsed(){return used;}
void Bag::setUsed(bool u){used = u;}
void Bag::pullOut(RenderWindow* window, Figure* current){
    Figure* nexT = new Figure(window);
    for(int i=0;i<4;i++){
        for(int j=3;j<7;j++){
            if(nexT->isBlock(i,j) != -1){
                buffer[i][j-3] = matrix[i][j];
                matrix[i][j] = NULL;
            }
            if(next->isBlock(i,j) != -1){
                matrix[i][j]=bag[i][j-3];
                bag[i][j-3]= buffer[i][j-3];
            }else {bag[i][j-3] = buffer[i][j-3];}
        }
    }
    *current = *next;
    next = nexT;
    bufferClear();
}
void Bag::change(RenderWindow* window, Figure* f){
    used = true;
    for(int i = f->corner.x;i < f->corner.x+4;i++)
        for(int j=f->corner.y;j<f->corner.y+4;j++){
            if(hblocks[0][0] != -1){
                if(bag[i - f->corner.x][j- f->corner.y + 4] != NULL && f->isBlock(i,j) != -1){
                    buffer[0][0] = matrix[i][j];
                    matrix[i - f->corner.x][j- f->corner.y + 3] = bag[i - f->corner.x][j- f->corner.y + 4];
                    bag[i - f->corner.x][j- f->corner.y + 4] = buffer[0][0];
                    if(i - f->corner.x != i || j - f->corner.y + 3 != j)matrix[i][j] = NULL;
                }else if(f->isBlock(i,j) != -1){
                    bag[i - f->corner.x][j- f->corner.y + 4] = matrix[i][j];
                    matrix[i][j] = NULL;
                }else if(bag[i - f->corner.x][j- f->corner.y + 4] != NULL){
                    matrix[i - f->corner.x][j- f->corner.y + 3] = bag[i - f->corner.x][j- f->corner.y + 4];
                    bag[i - f->corner.x][j- f->corner.y + 4] = NULL;
                }
            }else{
                if(f->isBlock(i,j) != -1){
                    bag[i - f->corner.x][j- f->corner.y + 4] = matrix[i][j];
                    matrix[i][j] = NULL;
                }
            }
        }
    if(hblocks[0][0] == -1){
        htype = f->getType();
        for(int i=0;i<4;i++){
            hblocks[i][0] = f->blocks[i][0] - f->corner.x;
            hblocks[i][1] = f->blocks[i][1] - f->corner.y + 3;
        }
        pullOut(window,f);
    }else{
        cout<<"SWAP\n";
        int buf = htype;
        htype = f->getType();
        f->setType(buf);
        for(int i=0;i<4;i++){
            swap(hblocks[i][0],f->blocks[i][0]);
            swap(hblocks[i][1],f->blocks[i][1]);
            hblocks[i][0] -= f->corner.x;
            hblocks[i][1] -= f->corner.y - 3;
        }
    }
    f->corner.x = 0;
    f->corner.y = 3;
    buffer[0][0] = NULL;
}
void Bag::draw_b(RenderWindow* window){
    for(int i=0;i<4;i++){
        for(int j=0;j<8;j++){
            if(bag[i][j] != NULL){
                if(j<4){
                    bag[i][j]->setPosition(620+30*j,250+30*i);
                }else{bag[i][j]->setPosition(520+30*j,440+30*i);}
                window->draw(*bag[i][j]);

            }
        }
    }
}
