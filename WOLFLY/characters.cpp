#include "characters.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

string Sheep::GetColor()
{
    return Color;
}

void Sheep::locate(SDL_Renderer *renderer)
{
    getScreenSize();
    OX = SCREEN_WIDTH + Sheep_WIDTH;
    OY = (rand() % (SCREEN_HEIGHT - Sheep_HEIGHT));
    int num = rand() % 7;
    Color = std::to_string(num);
    std::string path = "media/Characters/Sheep/" + Color + ".png";
    if (! loadFromFile(renderer, path))
    {
        printf("Failed to load sheep texture!\n");
    }
    VelocityX = SCREEN_WIDTH / 220;
}

void Sheep::move(std::string &act, SDL_Renderer *renderer)
{
    ReSize();
    OX -= VelocityX;
    if (OX <= 0 - Sheep_WIDTH)
    {
        act += 's';
        locate(renderer);
    }
}

void Sheep::render(SDL_Renderer *renderer)
{
    renderTexture(renderer, OX, OY, Sheep_WIDTH, Sheep_HEIGHT);
}

void Sheep::ReSize()
{
    getScreenSize();
    Sheep_WIDTH = SCREEN_WIDTH / 15.5;
    VelocityX = SCREEN_WIDTH / 220;
}

Star::Star(SDL_Renderer* renderer)
{
    if (!loadFromFile(renderer, "media/Background/star.png"))
    {
        printf("Failed to load star texture!\n");
    }
}

Star::~Star()
{
    Star_WIDTH = 0;
    OX = 0;
    OY = 0;
    VelocityY = 0;
    free();
}

void Star::locate(int x)
{
    getScreenSize();
    OX = (rand() % (SCREEN_WIDTH - Star_WIDTH));
    OY = x;

    VelocityY = SCREEN_HEIGHT / 124;
}

void Star::move(std::string &act)
{
    getScreenSize();
    VelocityY = SCREEN_HEIGHT / 124;
    Star_HEIGHT = SCREEN_HEIGHT / 7.3;

    OY += VelocityY;
    if (OY >= SCREEN_HEIGHT)
    {
        OX = (rand() % (SCREEN_WIDTH - Star_WIDTH));
        OY = 0 - Star_HEIGHT;
        act += 'f';
    }
}

void Star::render(SDL_Renderer *renderer)
{
    renderTexture(renderer, OX, OY, Star_WIDTH, Star_HEIGHT);
}

HEAD::HEAD(SDL_Renderer* renderer)
{
    if (!loadFromFile(renderer, "media/Characters/Wolf/d.png"))
    {
        printf("Failed to load wolf texture!\n");
    }

    getScreenSize();
    OX = 0;
    OY = SCREEN_HEIGHT / 2 - HEAD_WIDTH / 2;
    HEAD_VEL = SCREEN_WIDTH / 124;
    VelocityX = 0;
    VelocityY = 0;
}

HEAD::~HEAD()
{
    HEAD_HEIGHT = 0;
    HEAD_WIDTH = 0;
    HEAD_VEL = 0;
    OX = 0;
    OY = 0;
    VelocityX = 0;
    VelocityY = 0;
}

void HEAD::handleEvent(SDL_Event &e)
{
    HEAD_VEL = SCREEN_WIDTH / 124;
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            VelocityY -= HEAD_VEL;
            break;
        case SDLK_DOWN:
            VelocityY += HEAD_VEL;
            break;
        case SDLK_LEFT:
            flip = SDL_FLIP_HORIZONTAL;
            VelocityX -= HEAD_VEL;
            break;
        case SDLK_RIGHT:
            flip = SDL_FLIP_NONE;
            VelocityX += HEAD_VEL;
            break;
        }
    }
    else if (e.type == SDL_KEYUP && e.key.repeat == 0)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            VelocityY += HEAD_VEL;
            break;
        case SDLK_DOWN:
            VelocityY -= HEAD_VEL;
            break;
        case SDLK_LEFT:
            VelocityX += HEAD_VEL;
            break;
        case SDLK_RIGHT:
            VelocityX -= HEAD_VEL;
            break;
        }
    }
}

void HEAD::move()
{
    OX += VelocityX;

    if ((OX < 0) || (OX + HEAD_WIDTH > SCREEN_WIDTH))
    {
        OX -= VelocityX;
    }

    OY += VelocityY;

    if ((OY < 0) || (OY + HEAD_HEIGHT > SCREEN_HEIGHT))
    {
        OY -= VelocityY;
    }
}

void HEAD::fall(bool &quit)
{
    if (OY < SCREEN_HEIGHT)
    {
        OY += SCREEN_HEIGHT / 124;
    }
    else
    {
        quit = true;
    }
}

void HEAD::render(SDL_Renderer *renderer)
{
    getScreenSize();
    HEAD_WIDTH = SCREEN_WIDTH / 9.2;
    HEAD_HEIGHT = SCREEN_HEIGHT / 6.5;
    renderTexture(renderer, OX, OY, HEAD_WIDTH, HEAD_HEIGHT, flip);
}

bool HEAD::checkCollition(double a, double b, double x, double y, double r)
{
    if ((x - a)*(x - a) + (y - b)*(y - b) <= r*r)
    {
        return true;
    }
    return false;
}

bool HEAD::checkMove(Star &s)
{
    double r = s.Star_WIDTH / 2 - s.Star_WIDTH / 30; //co nhỏ vì sao có viền
    double a = s.OX + r;
    double b = s.OY + r; // coi sao như hình tròn
    //kiểm tra va chạm trong 2 trường hợp quay đầu sói, các điểm được kiểm tra: E:\Assignments\INT2215\WOLFLY\media\Characters\checkPoints.png
	if ( flip == SDL_FLIP_NONE && (checkCollition(a, b, OX + HEAD_WIDTH / 4, OY, r) || checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT / 8, r) || checkCollition(a, b, OX, OY + HEAD_HEIGHT * 3 / 8, r) ||
     checkCollition(a, b, OX + HEAD_WIDTH, OY + HEAD_HEIGHT / 2, r) || checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT, r) || checkCollition(a, b, OX + HEAD_WIDTH, OY + HEAD_HEIGHT / 4, r) ||
     checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT / 2, r)) )
    {
        return true;
	}
	if ( flip == SDL_FLIP_HORIZONTAL && (checkCollition(a, b, OX + HEAD_WIDTH * 3 / 4, OY, r) || checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT / 8, r) || checkCollition(a, b, OX + HEAD_WIDTH, OY + HEAD_HEIGHT * 3 / 8, r) ||
     checkCollition(a, b, OX, OY + HEAD_HEIGHT / 2, r) || checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT, r) || checkCollition(a, b, OX, OY + HEAD_HEIGHT / 4, r) ||
     checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT / 2, r)) )
    {
        return true;
	}
	return false;
}

bool HEAD::checkEat(Sheep &s, SDL_Renderer *renderer, string& CurrentColor)
{
    double r = s.Sheep_WIDTH / 2;
    double a = s.OX + r;
    double b = s.OY + r; // cừu hình tròn
    //kiểm tra va chạm tương tự sao
	if ( flip == SDL_FLIP_NONE && (checkCollition(a, b, OX + HEAD_WIDTH / 4, OY, r) || checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT / 8, r) || checkCollition(a, b, OX, OY + HEAD_HEIGHT * 3 / 8, r) ||
     checkCollition(a, b, OX + HEAD_WIDTH, OY + HEAD_HEIGHT / 2, r) || checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT, r) || checkCollition(a, b, OX + HEAD_WIDTH, OY + HEAD_HEIGHT / 4, r) ||
     checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT / 2, r)) )
    {
        CurrentColor = s.GetColor();
        s.locate(renderer);
        return true;
	}
	if ( flip == SDL_FLIP_HORIZONTAL && (checkCollition(a, b, OX + HEAD_WIDTH * 3 / 4, OY, r) || checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT / 8, r) || checkCollition(a, b, OX + HEAD_WIDTH, OY + HEAD_HEIGHT * 3 / 8, r) ||
     checkCollition(a, b, OX, OY + HEAD_HEIGHT / 2, r) || checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT, r) || checkCollition(a, b, OX, OY + HEAD_HEIGHT / 4, r) ||
     checkCollition(a, b, OX + HEAD_WIDTH / 2, OY + HEAD_HEIGHT / 2, r)) )
    {
        CurrentColor = s.GetColor();
        s.locate(renderer);
        return true;
	}
	return false;
}
