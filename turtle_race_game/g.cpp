#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include <random>


const int N = 10, M = 20;//N is number of turtles
const int size = 32;//each png image size
const int w = N*size;
const int h = M*size;
const int maxs = 20; //max pixels per second

using namespace sf;

struct Turtle
{int x, y, v, c;};
Turtle turtles[N];

void Tick(){
  for(int i=0; i<N; i++){
      if(!turtles[i].c) turtles[i].y -= turtles[i].v;
      if (turtles[i].y<=0){
        std::cout << "turtle " << i << " just arrived!" << std::endl;
        turtles[i].y = h;
        turtles[i].v = 0;
        turtles[i].c = 1;
      }
  }
}


int main(){
  srand(time(0));
  for(int i=0; i<N;i++){
  turtles[i].x = i*size;
  turtles[i].y = h-size;
  turtles[i].v = rand()%maxs + 1;
  turtles[i].c = 0;
  }
  RenderWindow app(VideoMode(w, h), "Turtle");
  Texture t;
  Texture t1;
  t1.loadFromFile("0.png");
  t.loadFromFile("0bg.png");
  Sprite bg(t);
  Sprite s1(t1);
  Clock clock;
  float timer = 0, delay = 0.1;
  
  while (app.isOpen()){
    float time = clock.getElapsedTime().asSeconds();
    clock.restart();
    timer += time;
    Event e;
    while(app.pollEvent(e)){
      if(e.type==Event::Closed){
        app.close();
      }
    }
    if(timer>delay){timer = 0; Tick();}
    app.clear();
    for(int i=0; i<N; i++){
      turtles[i].v = rand()%maxs+1;
      for(int y=0; y<M; y++){
        bg.setPosition(i*size, y*size);
        app.draw(bg);
      }
      s1.setPosition(turtles[i].x, turtles[i].y);
      app.draw(s1);
    }
    app.display();
  }
}
