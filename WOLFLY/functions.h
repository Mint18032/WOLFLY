//các hàm trong game
#pragma once
#include "button.h"
#include "characters.h"

string soundControl(BUTTON& Sound, BUTTON& BMusic); //kiểm soát các chế độ
void soundEffect(std::string act); //tạo hiệu ứng âm thanh
void scrollBackground(SDL_Renderer* renderer, Texture& BgTexture, int& scrollingOffset, int SCREEN_WIDTH, int SCREEN_HEIGHT); //vẽ nền cuộn
void closePauseScreen(BUTTON& pause, BUTTON& replay, BUTTON& menu, BUTTON& Play, SDL_Renderer* renderer); //giải phóng bộ nhớ sau khi thoát chế độ pause

////
