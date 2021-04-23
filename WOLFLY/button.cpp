#include "button.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

bool BUTTON::clickButton(SDL_Event& e)
{
    if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int xm, ym; //tọa độ click chuột
        SDL_GetMouseState(&xm, &ym);

        if ( (xm - a)*(xm - a) + (ym - b)*(ym - b) <= r*r ) //thỏa mãn phương trình đường tròn tức là click vào nút
        {
            return true;
        }
    }
    return false;
}

void BUTTON::loadButonTexture(std::string name, SDL_Renderer* renderer)
{
    Tbutton.free();
    text.free();
    situation = name;
    if(!Tbutton.loadFromFile(renderer, path + name + ".png") || !text.loadFromRenderedText(TTF_OpenFont("media/Text/Debrosee.ttf", SCREEN_WIDTH / 30), name, {255, 255, 255}, renderer))
    {
        printf("Failed to load button texture!\n");
    }
}

void BUTTON::renderAsIcon(int x, int y, SDL_Renderer *ren)
{
    Tbutton.getScreenSize(); //cập nhật kích cỡ màn hình
    r = (SCREEN_WIDTH + SCREEN_HEIGHT) / 100;
    a = x + r;
    b = y + r;
    Tbutton.renderTexture(ren, x, y, 2*r, 2*r);
}

void BUTTON::renderWithString(int x, int y, SDL_Renderer *ren)
{
    if ( Tbutton.getScreenSize() ) {
        text.free();
        text.loadFromRenderedText(TTF_OpenFont("media/Text/Debrosee.ttf", SCREEN_WIDTH / 30), situation, {255, 255, 255}, ren);
    } //tải lại cỡ chữ nếu màn hình thay đổi
    r = (SCREEN_WIDTH + SCREEN_HEIGHT) / 19;
    a = x + r;
    b = y + r;
    Tbutton.renderTexture(ren, x, y, 2*r, 2*r);
    text.render(ren, x + r - text.getWidth()/ 2, y + 2 * r + 2);
}


void BUTTON::free()
{
    r = 0;
    a = 0;
    b = 0;
    situation = '\0';
    Tbutton.free();
    text.free();
}


