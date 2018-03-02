#include <SFML/Graphics.hpp>
#include <time.h>
#include <sstream>
#include <iostream>
using namespace sf;
using namespace std;

struct point
{
    int x, y;
};

    RenderWindow app(VideoMode(400, 533), "Doodle Game!");
    int score, bestScore;


void play()
{
    score = 0;
    bool gameover = false;

    app.setFramerateLimit(60);

    Texture t1,t2,t3;
    Text text, scoreText, bestScoreText, scoreUpdate, bestScoreUpdate;
    Font font;




    font.loadFromFile("GLSNECB.ttf");
    t1.loadFromFile("images/background.png");
    t2.loadFromFile("images/platform.png");
    t3.loadFromFile("images/doodle.png");

    text.setFont(font);
    scoreText.setFont(font);
    bestScoreText.setFont(font);
    bestScoreUpdate.setFont(font);
    scoreUpdate.setFont(font);

    text.setString("Game Over!");
    scoreText.setString("Score : ");
    bestScoreText.setString("Best Score : ");


    text.setCharacterSize(50);
    scoreText.setCharacterSize(24);
    bestScoreText.setCharacterSize(35);
    bestScoreUpdate.setCharacterSize(35);
    scoreUpdate.setCharacterSize(24);

    text.setColor(Color::Red);
    scoreText.setColor(Color::Black);
    bestScoreText.setColor(Color::Black);
    bestScoreUpdate.setColor(Color::Black);
    scoreUpdate.setColor(Color::Black);

    text.setPosition(270/2, 410/2);
    scoreText.setPosition(10,10);
    bestScoreText.setPosition(280/2, 280);
    bestScoreUpdate.setPosition(250, 280);
    scoreUpdate.setPosition(50, 10);





    Sprite sBackground(t1), sPlat(t2), sPers(t3);

    point plat[20];

    for (int i = 0; i < 10; i++)
    {
        plat[i].x = rand()%400;
        plat[i].y = rand()%533;
    }

    int x = 100, y = 100, h = 200;
    float dx = 0, dy = 0;

    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if(e.type == Event::Closed)
                app.close();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right)) x += 3;
        if (x > 400) x = 0;
        if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 3;
        if (x < 0) x = 400;

        dy += 0.2;
        y += dy;

        if (y > 500)
        {
            gameover = true;
        }

        if (y < h)
        {
            for (int i = 0; i < 10; i++)
            {
                y = h;
                plat[i].y = plat[i].y - dy;
                if (plat[i].y > 533)
                {
                    plat[i].y = 0;
                    plat[i].x = rand()%400;
                }
            }
            score += y/100;
            if(score > bestScore)
            {
                bestScore = score;
            }
        }



        for (int i = 0; i < 10; i++)
        {
            if ((x + 50 > plat[i].x)
                && (x + 20 < plat[i].x+68)
                && (y + 70 > plat[i].y)
                && (y + 70 < plat[i].y + 14)
                && (dy > 0))
            {
                dy = -9.8;
            }

        }

        sPers.setPosition(x, y);


       if(!gameover)
       {

            app.draw(sBackground);
            app.draw(sPers);
            app.draw(scoreText);

            stringstream ss;
            ss << score;
            scoreUpdate.setString(ss.str());
            app.draw(scoreUpdate);

            for (int i = 0; i < 10; i++)
            {
                sPlat.setPosition(plat[i].x, plat[i].y);
                app.draw(sPlat);
            }

       }else{
            app.clear();
            app.draw(sBackground);
            app.draw(text);
            stringstream sb;
            sb << bestScore;
            bestScoreUpdate.setString(sb.str());

            app.draw(bestScoreText);
            app.draw(bestScoreUpdate);
       }


        if(gameover && Keyboard::isKeyPressed(Keyboard::Space))
        {
            play();
        }
        app.display();

    }

}


int main()
{
    play();

    return 0;
}
