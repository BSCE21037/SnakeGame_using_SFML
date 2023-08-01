#include <SFML/Graphics.hpp>    //include SFML graphics library
#include <time.h>               //include time library
#include <iostream>            //include iostream library
using namespace std;            //using namespace std
using namespace sf;             //using namespace sf

int N = 30, M = 20;           //create int N and size and set to 30 and 20
int w = 16 * N;                //create int w and set to size times N
int h = 16 * M;                //create int h and set to size times N

int dir, num = 4;              //create int dir and num and set to 4

class Snake{                  //create class Snake
public:                       //public
    int x, y;                  //create int x and y
};
Snake s[100];                      //create array s of size 100

class Fruit{                  //create class Fruit
public:                       //public
    int x, y;                  //create int x and y
};
Fruit f;                           //create object f


void Tick(){
    for(int i = num; i > 0; --i){   //for loop
        s[i].x = s[i - 1].x;        //set s[i].x to s[i - 1].x
        s[i].y = s[i - 1].y;        //set s[i].y to s[i - 1].y
    }
    if(dir == 0){                   //if dir is 0
        s[0].y += 1;                //set s[0].y to s[0].y + 1
    }
    if(dir == 1){                   //if dir is 1
        s[0].x -= 1;                //set s[0].x to s[0].x - 1
    }
    if(dir == 2){                   //if dir is 2
        s[0].x += 1;                //set s[0].x to s[0].x + 1
    }
    if(dir == 3){                   //if dir is 3
        s[0].y -= 1;                //set s[0].y to s[0].y - 1
    }
    //
    if((s[0].x == f.x) && (s[0].y == f.y)){   //if s[0].x is equal to f.x and s[0].y is equal to f.y
        num++;                                //increment num
        f.x = rand() % N;                     //set f.x to random number between 0 and N
        f.y = rand() % M;                     //set f.y to random number between 0 and M
    }

    //
    if(s[0].x > N){   //if s[0].x is greater than N
        s[0].x = 0;   //set s[0].x to 0
    }
    if(s[0].x < 0){   //if s[0].x is less than 0
        s[0].x = N;   //set s[0].x to N
    }
    if(s[0].y > M){   //if s[0].y is greater than M
        s[0].y = 0;   //set s[0].y to 0
    }
    if(s[0].y < 0){   //if s[0].y is less than 0
        s[0].y = M;   //set s[0].y to M
    }
    for(int i = 1; i < num; i++){   //for loop
        if(s[0].x == s[i].x && s[0].y == s[i].y){   //if s[0].x is equal to s[i].x and s[0].y is equal to s[i].y
            num = i;                               //set num to i
        }
    }
    

    

}


int main()                //main function
{
    srand(time(0));       //seed random number generator with time(0

    RenderWindow window(sf::VideoMode(w, h), "Snake Game", Style::Close | Style::Titlebar);  //create window with size w x h, title TicTacToe, and close and titlebar buttons on window 
    window.setFramerateLimit(60);   //set framerate limit to 60
    Texture white, green, red;             //create textures t1, t2, and t3
    if(!white.loadFromFile("white.png")){   //if t1 cannot load image from file
        cout << "Error loading image tiles.png" << endl;  //output error message
    }
    if(!green.loadFromFile("green.png")){   //if t2 cannot load image from file
        cout << "Error loading image checkers.png" << endl;  //output error message
    }
    if(!red.loadFromFile("red.png")){   //if t3 cannot load image from file
        cout << "Error loading image figures.png" << endl;  //output error message
    }
    Sprite w(white);   //create sprite w and set texture to t1
    Sprite g(green);   //create sprite g and set texture to t2
    Sprite r(red);   //create sprite r and set texture to t3
    
    Clock clock;   //create clock
    float timer = 0, delay = 0.1;   //create float timer and delay and set to 0 and 0.1

    f.x = 10;   //set f.x to 10
    f.y = 10;   //set f.y to 10

    while(window.isOpen()){   //while window is open
        float time = clock.getElapsedTime().asSeconds();   //create float time and set to clock time
        clock.restart();   //restart clock
        timer += time;   //add time to timer
        Event e;              //create event e
        while(window.pollEvent(e)){   //while window is polling event e
            switch(e.type){            //switch statement for event e
                case Event::KeyReleased:   //if event e is key released
                    if(e.key.code == Keyboard::Left){   //if key released is left arrow
                        dir = 1;   //set dir to 1
                    }
                    else if(e.key.code == Keyboard::Right){   //if key released is right arrow
                        dir = 2;   //set dir to 2
                    }
                    else if(e.key.code == Keyboard::Up){   //if key released is up arrow
                        dir = 3;   //set dir to 3
                    }
                    else if(e.key.code == Keyboard::Down){   //if key released is down arrow
                        dir = 0;   //set dir to 0
                    }
                    break;   //break
                
                case Event::Closed:       //if event e is closed
                    window.close();             //close window
                    break;                      //break
            }
        }
        if (timer > delay)   //if timer is greater than delay
        {
            timer = 0;   //set timer to 0
            Tick();   //call Tick function
        }

    
        window.clear(Color::Black); //clear window with white color
        // for (int i = 0; i < N; i++)
        // {
        //     for (int j = 0; j < M; j++)
        //     {
        //         w.setPosition(i * 16, j * 16); //set position of sprite w
        //         window.draw(w);                 //draw sprite w
        //     }
            
        // }
        for (int i = 0; i < num; i++)
        {
            g.setPosition(s[i].x * 16, s[i].y * 16); //set position of sprite g
            window.draw(g);                           //draw sprite g
        }

        g.setPosition(f.x * 16, f.y * 16); //set position of sprite r
        window.draw(g);                           //draw sprite r
        window.display();           //display window
    
    }
    return 0;                   
}
