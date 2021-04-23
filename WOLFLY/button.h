#pragma once
#include "Texture.h"
using namespace std;

class BUTTON
{
    public:
        int r = 0; //bán kinh
        int a = 0, b = 0; //tọa độ tâm
        std::string situation; //tên/trạng thái của 1 nút (1 nút có thể có 2 trạng thái VD: Sound: muted - ummuted)

        bool clickButton(SDL_Event& e); //xác định sự kiện bấm nút
        void loadButonTexture(std::string name, SDL_Renderer *renderer);
        void renderAsIcon(int x, int y, SDL_Renderer *ren); //vẽ nhỏ (ở góc màn hình)
        void renderWithString(int x, int y, SDL_Renderer *ren); //vẽ to, có tên nút bên dưới
        void free();

    private:
        Texture Tbutton; //button Texture
        Texture text; //để viết chữ nếu dùng renderWithString
        int& SCREEN_WIDTH = Tbutton.SCREEN_WIDTH;
        int& SCREEN_HEIGHT = Tbutton.SCREEN_HEIGHT;
        std::string path = "media/Buttons/"; //dường dẫn dùng lúc load
};

/* các nút đều có dạng hình tròn nên xác định như 1 hình tròn */
