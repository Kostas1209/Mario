#include  <SFML/Graphics.hpp>
#include  <SFML/Audio.hpp>
#include  <sstream>
#include  "map.h"
#include  <iostream>
#include  <locale>
#define ABS(X) ((X) < 0 ? -(X) : (X))
#include  <Windows.h>
#include  <conio.h>


using namespace sf;
//using namespace std;

int main() {
    std::cout<<"You Dont crash stone if you do not up gryb"<<std::endl<<"You have 90 seconds, time start"<<std::endl;
   Sleep(3000);
    bool win = false;
    RenderWindow window(VideoMode(1000,500), "Mario Bros");
    /*Image hero;
    hero.loadFromFile("Mario.png");*/
    Texture Mar;
    Mar.loadFromFile("Mario.png");
    Sprite Mario;
    Mario.setTexture(Mar);
    bool live=true;
    int temp=0;
    float timeGame=0;
    Font font;
    font.loadFromFile("CyrilicOld.ttf");
    Text Over("",font,100);
    Over.setColor(Color::Red);
    Text text("",font,30);
    text.setColor(Color::Red);
    text.setStyle(Text::Bold | Text::Underlined);
   Vector2f velocity;
   SoundBuffer bufferCoins;
   bufferCoins.loadFromFile("smb_coin.wav");
   Sound Coins(bufferCoins);
           SoundBuffer buffer;
            buffer.loadFromFile("smb_jump-small.wav");
            Sound up(buffer);

   Clock clock;
   float CurrentFlame=0;

   bool big=false;
  Music music;
  music.openFromFile("Mario.ogg");
  music.play();


   Image b;
   b.loadFromFile("Enemy.png");
   Texture d;
   d.loadFromImage(b);
   float velocityEnemy[10];
   for(int i=0;i<10;i++)
   {
       velocityEnemy[i]=0.15;
   }
   float posxEnemy[10]={500,2000,2100,2700,5300,5800,5700,6850,6950,8700};
    Sprite Enemy[30];
    float newxEnemy[10];
  //Enemy.setPosition(posxEnemy,500);
   bool damage[10];
   bool zdavlen[10];
   for(int i=0;i<10;i++)
   {
       damage[i]=true;
       Enemy[i].setTextureRect(IntRect(0,0,50,50));
       zdavlen[i]=false;
   }

   float newx;

    Image map_image;
    map_image.loadFromFile("map_Mario.jpg");
    Texture map;
    map.loadFromImage(map_image);
    Sprite s_map;
    bool Earth =true;
    s_map.setTexture(map);
    Mario.setTextureRect(IntRect(50*int(CurrentFlame),0,50,50));
    Mario.setPosition(0,300);
    while (window.isOpen()) {
        Event evt;
        while (window.pollEvent(evt)) {
            if (evt.type == Event::Closed || Event::KeyPressed && evt.key.code == Keyboard::Escape)
                window.close();
        }

        float time=clock.getElapsedTime().asMicroseconds();
        float timeG=clock.getElapsedTime().asSeconds();
        clock.restart();
        timeGame+=timeG;
        time=time/800;
        for(int i=0;i<Height_Level;i++)
        {
            for(int  j=0;j<Width_Level+10;j++)
            {
                if(Level[i][j]=='s')s_map.setTextureRect(IntRect(50,0,50,50));
                if(Level[i][j]=='k')s_map.setTextureRect(IntRect(100,0,50,50));
                if(Level[i][j]=='g')s_map.setTextureRect(IntRect(0,0,50,50));
                if(Level[i][j]=='0')s_map.setTextureRect(IntRect(150,0,50,50));
                if(Level[i][j]=='?')s_map.setTextureRect(IntRect(200,0,50,50));
                if(Level[i][j]=='f')s_map.setTextureRect(IntRect(250,0,50,50));
                if(Level[i][j]=='p')s_map.setTextureRect(IntRect(300,0,50,50));
                if(Level[i][j]=='c')s_map.setTextureRect(IntRect(350,0,50,50));
                if(Level[i][j]=='m')s_map.setTextureRect(IntRect(400,0,50,50));

                //if(Level[i][j]=='e')s_map.setTextureRect(IntRect(450,0,50,50));

        s_map.setPosition(j*50,i*50);
        window.draw(s_map);
            }
        }
        bool moving = false;
        if(newx>0 && Keyboard::isKeyPressed(Keyboard::Left))//êåáí
        {
            CurrentFlame+=0.005*time;
            if(CurrentFlame>3)CurrentFlame-=3;
            Mario.setTextureRect(IntRect(50*int(CurrentFlame),50,50,50));
            velocity.x = -0.25;
            moving = true;
        }
        if(Keyboard::isKeyPressed(Keyboard::Right))//áîïþáí
        {
            CurrentFlame+=0.005*time;
            if(CurrentFlame>3)CurrentFlame-=3;
            Mario.setTextureRect(IntRect(50*int(CurrentFlame),0,50,50));
            velocity.x = 0.25;
            moving = true;
        }
        if (!moving) {
            velocity.x *= 0.8;
            if (ABS(velocity.x) < 0.001) velocity.x = 0;
        }
        if(Earth && Keyboard::isKeyPressed(Keyboard::Space))///îïõôíé ááåïó áîïþáí õ áêåáí
        {
            Earth=false;

            Mario.setTextureRect( IntRect( 0,150,50,50));

            velocity.y = -0.5;

            up.play();
        }
        float posy = Mario.getPosition().y;
        float posx = Mario.getPosition().x;

        if (Earth) {
            float testy = posy + 5;

            bool canStand = false;
            for (int i = testy / 50; i <= (testy + 49) / 50; ++i) {
                for (int j = posx / 50; j <= (posx + 49) / 50; ++j) {
                    if (i > -1 && j > -1 && i < 15  && j < 200 && Level[i][j] != '0') {
                        canStand = true;
                    }
                }
            }
            if (!canStand) {
                Earth = false;
            }
        }
        if(Earth==false)
        {
           velocity.y += 0.01;
        }
        float newy = posy + velocity.y * time;
        for (int i = newy / 50; i <= (newy + 49) / 50; ++i) {
            for (int j = posx / 50; j <= (posx + 49) / 50; ++j) {
                    if(Level[i+1][j]=='c' )
                    {
                        Level[i+1][j]='0';
                        temp++;
                        Coins.play();
                    }
                    if(!Earth && Level[i-1][j]=='c')
                    {
                        Level[i-1][j]='0';
                        Coins.play();
                    }
                    if(Level[i+1][j]=='f')
                    {
                        Level[i+1][j]='0';
                        big=true;
                    }
                if (i > -1 && j > -1 && i < 15  && j < 210 && Level[i][j] != '0'  )
                    {
                    if (velocity.y > 0) {
                        velocity.y = 0;
                        Earth = true;
                        newy = (i - 1) * 50;
                    } else if (velocity.y < 0) {
                        if (Level[i][j] == 'k' && big) {
                            Level[i][j] = '0';
                        }
                        if(Level[i][j]=='?')
                        {
                            Level[i-1][j]='f';
                            Level[i][j]='p';
                        }
                        if(Level[i][j]=='m')
                        {
                            Level[i][j]=='m';
                            velocity.y+=0.005;
                        }


                        velocity.y = 0;
                        newy = (i + 1) * 50;
                    }
                }
            }
        }
         newx = posx + velocity.x * time;
        for (int i = newy / 50; i <= (newy + 49) / 50; ++i) {
            for (int j = newx / 50; j <= (newx + 49) / 50; ++j) {
                if (i > -1 && j > -1 && i < 15 && j < 210 && Level[i][j] != '0' ) {
                    if (velocity.x > 0)
                        {
                        velocity.x = 0;
                        newx = (j - 1) * 50;
                        }
                    else if (velocity.x < 0)
                        {
                        velocity.x = 0;
                        newx = (j + 1) * 50;
                       }
                     }

                if( Level[i][j]=='f')
                {
                    Level[i][j]='0';
                    big=true;
                }
                if (Level[i][j]=='c')
                {
                    Level[i][j]='0';
                    temp++;
                    Coins.play();
                }

            }
        }
    for(int i=0;i<10;i++)
   {
       Enemy[i].setTexture(d);
       //Enemy[i].setTextureRect(IntRect(0,0,50,50));
       Enemy[i].setPosition(posxEnemy[i],500);
       if(Level[10][newxEnemy[i]/50+1]=='k')
        {
            velocityEnemy[i]= -1 * velocityEnemy[i];
        }
        else velocityEnemy[i]=1*velocityEnemy[i];
        newxEnemy[i]=velocityEnemy[i]*time+posxEnemy[i];
        Enemy[i].setPosition(newxEnemy[i],500);
        posxEnemy[i]=newxEnemy[i];
        window.draw(Enemy[i]);
   }
    Mario.setPosition(newx,newy);

         View view(FloatRect(0,0,1000,550));
   view.setCenter(newx,newy-50);

        if(newx<500)
        {
            view.setCenter(500,newy-50);
        }
        if(newy<400 )
        {
            view.setCenter(newx,350);
        }
        if(newx<500 && newy<400)
        {

            view.setCenter(500,350);
        }

         if(newy>550 || timeGame > 90 )
        {
            Mario.setTextureRect(IntRect(0,200,50,50));
            Over.setString("GAME OVER ");
            music.stop();
            Over.setPosition(view.getCenter().x-300,view.getCenter().y-300);
            window.draw(Over);
            view.setCenter(newx,375);
            velocity.x=0;
            velocity.y=0;
            time=0;
            live=false;
        }
        for(int j=0;j<10;j++)
        {
        if(ABS(newx-newxEnemy[j])<25 && newy>450 && !Earth && velocity.y>0 && !zdavlen[j])
        {
            Enemy[j].setTextureRect(IntRect(50,0,50,50));
            velocityEnemy[j]=0;
            damage[j]=false;
            velocity.y=-0.2;
            up.play();
            zdavlen[j]=true;
            temp+=2;
        }
        if(newx>10300)
        {
            Over.setString("You Win");
            music.stop();
            Over.setPosition(9800,350);
            window.draw(Over);
            velocity.y=0;
            velocity.x=0;
            win=true;
        }
       if(ABS(newx-newxEnemy[j])<30 && Earth && damage[j] && newy>480 )
        {
            Mario.setTextureRect(IntRect(0,200,50,50));
            Over.setString("GAME OVER ");
            music.stop();
            Over.setPosition(view.getCenter().x-300,view.getCenter().y-300);
            window.draw(Over);

            if(newx<500)
            {
                view.setCenter(500,375);
            }
            else view.setCenter(newx,375);
            velocity.x=0;
            velocity.y=0;
            time=0;
            for(int i=0;i<10;i++)
            {
            velocityEnemy[i]=0;
            }
            live=false;
        }
        }
        std::ostringstream playerScoreString;
        playerScoreString<<temp;
        text.setString("ENTER COINS: " + playerScoreString.str());
        text.setPosition(view.getCenter().x-500,view.getCenter().y-250);
        window.draw(text);
        window.setView(view);
        window.draw(Mario);
        window.display();
        if(live==false )
        {
            Music Game;
            Game.openFromFile("smb_gameover.wav");
            Game.play();
               while(!Keyboard::isKeyPressed(Keyboard::Escape))
            {

            }
            window.close();
        }
        if(win)
        {
            while(!Keyboard::isKeyPressed(Keyboard::Escape))
            {

            }
            window.close();
        }
    }
    std::cout<<"Your Coeficient : "<<timeGame/temp;
    _getch();
}
