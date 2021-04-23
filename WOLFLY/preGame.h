//hàm dùng trong main nhưng trước game, biến dùng xuyên suốt
bool loadMedia();
void openMenu(CLOUD& cloud, MOON& moon, BUTTON& Quit);
void renderMenu(CLOUD& cloud, MOON& moon, BUTTON& Quit);
void closeMenu(CLOUD& cloud, MOON& moon, BUTTON& Quit);
void Guide();
void close();

BUTTON Play; //cho biết có đang chơi hay không
BUTTON Sound; //hiệu ứng âm thanh
BUTTON BMusic; //tiếng nhạc nền+âm thanh

Texture BgTexture; //Dùng để vẽ nền (Background Texture)
Texture TextTexture;

bool loadMedia() //load nền, âm thanh, nhạc, các nút
{
    bool success = true;
    if (!BgTexture.loadFromFile(renderer, "media/Background/background.png"))
    {
        printf("Failed to load background texture!\n");
        success = false;
    }

    Music = Mix_LoadMUS("media/Sound/Comical.mp3");
    if (Music == NULL)
    {
        printf("Failed to load the music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    Play.loadButonTexture("Play", renderer);
    Sound.loadButonTexture("unmuted", renderer);
    BMusic.loadButonTexture("munmuted", renderer);

    return success;
}

void openMenu(CLOUD& cloud, MOON& moon, BUTTON& Quit) {  //tạo hiệu ứng đám mây bay lên, trăng, tên trò chơi, tác giả bay xuống
    if (Sound.situation == "unmuted" && BMusic.situation == "munmuted") {
        Mix_PlayMusic(Music, -1);
    }

    Quit.loadButonTexture("Quit", renderer);
    cloud.loadCloud(renderer);

    while (!cloud.appear() || !moon.appear()) {
        renderMenu(cloud, moon, Quit);
    }
}

void renderMenu(CLOUD& cloud, MOON& moon, BUTTON& Quit) {  //các lệnh lặp lại khi render menu
    SDL_RenderClear(renderer);
    BgTexture.renderTexture(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    cloud.render(renderer);
    moon.render(renderer);
    Quit.renderAsIcon(0, 0, renderer);
    BMusic.renderAsIcon(Quit.r * 2, 0, renderer);
    Sound.renderAsIcon(Quit.r * 4, 0, renderer);
    Play.renderWithString(SCREEN_WIDTH / 9, moon.OY, renderer);
    SDL_RenderPresent(renderer);
}

void closeMenu(CLOUD& cloud, MOON& moon, BUTTON& Quit) {   //hiệu ứng tắt/ chuyên màn hình
    while (!cloud.exit() || !moon.exit()) {
        SDL_RenderClear(renderer);
        BgTexture.renderTexture(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        moon.render(renderer);
        cloud.render(renderer);
        Quit.renderAsIcon(0, 0, renderer);
        BMusic.renderAsIcon(Quit.r * 2, 0, renderer);
        Sound.renderAsIcon(Quit.r * 4, 0, renderer);
        SDL_RenderPresent(renderer);
    }

    cloud.freeCloud();
    moon.free();
    Quit.free();
}

void Guide()    //màn hình hướng dẫn chơi
{
    SDL_RenderClear(renderer);
    BgTexture.renderTexture(renderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    Play.loadButonTexture("Paused", renderer);
    Play.renderAsIcon(0, 0, renderer);
    TTF_Font *Font = TTF_OpenFont("media/Text/Lazy.ttf", SCREEN_WIDTH / 52);
    std::string text = "Score: " + std::to_string(0) + "  Best: " + std::to_string(readBest());
    TextTexture.loadFromRenderedText(Font, text, {255, 255, 255}, renderer);
    TextTexture.render(renderer, (SCREEN_WIDTH - TextTexture.getWidth() - 10), (TextTexture.getHeight()) / 2);
    TextTexture.loadFromRenderedText(Font, "Use up, down, left, right keys to control the wolf", {255, 255, 255}, renderer);
    TextTexture.render(renderer, (SCREEN_WIDTH - TextTexture.getWidth()) / 2, (SCREEN_HEIGHT) / 2 - TextTexture.getHeight());
    TextTexture.loadFromRenderedText(Font, "Evade the falling stars and eat the sheep to gain scores", {255, 255, 255}, renderer);
    TextTexture.render(renderer, (SCREEN_WIDTH - TextTexture.getWidth()) / 2, (SCREEN_HEIGHT) / 2 + TextTexture.getHeight());
    SDL_RenderPresent(renderer);
    SDL_Delay(2500);
    Play.loadButonTexture("Play", renderer);
    TTF_CloseFont(Font);
}

void close()  //giải phóng âm thanh, các công cụ đô họa
{
    soundEffect("q");
    BgTexture.free();
    TextTexture.free();
    Play.free();
    Sound.free();
    BMusic.free();
    quit();
}
