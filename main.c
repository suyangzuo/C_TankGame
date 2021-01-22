#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

const int WINDOW_WIDTH = 960;   //窗体宽度
const int WINDOW_HEIGHT = 640;  //窗体高度

//使用旋转角度定义方向
const int UP = 0;
const int DOWN = 180;
const int LEFT = 270;
const int RIGHT = 90;
//-------------------

typedef struct {
    int x;
    int y;
    int width;
    int height;
    int direction;
    SDL_Texture *texture;
} Player;

void RenderPlayer(Player player, SDL_Renderer *renderer) {
    SDL_Rect srcRect = {.x = 0, .y = 0, .w = player.width, .h = player.height};
    SDL_Rect destRect = {.x = player.x, .y = player.y, .w = player.width / 2, .h = player.height / 2};
    SDL_RenderCopyEx(renderer, player.texture, &srcRect, &destRect, player.direction, NULL, SDL_FLIP_NONE);
}

int main(int argc, char *argv[]) {
    SDL_Window *window;
    SDL_Renderer *renderer;
    if (SDL_Init(SDL_INIT_EVERYTHING)) {
        printf("SDL对象初始化失败！\n");
        return -1;
    }

    if (!(window = SDL_CreateWindow("坦克大战", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_OPENGL))) {
        printf("窗体创建失败！\n");
        return -1;
    }

    if (!(renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE))) {
        printf("渲染器创建失败！\n");
        return -1;
    }

    SDL_SetRenderDrawColor(renderer, 76, 110, 150, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Surface *surface = IMG_Load("Tank01.png");
    if (!surface) {
        printf("像素集创建失败：%s\n", IMG_GetError());
        return -1;
    }

    printf("宽度：%d\n高度：%d\n", surface->w, surface->h);

    Player player1 = {(WINDOW_WIDTH - surface->w) / 2, WINDOW_HEIGHT - surface->h, surface->w, surface->h, UP, SDL_CreateTextureFromSurface(renderer, surface)};

    int defaultSpeed = 4;
    int speed;
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_Event event;
    while (1) {
        int flag1 = 0;
        while (SDL_PollEvent(&event)) {
            speed = defaultSpeed;
            switch (event.type) {
                case SDL_KEYDOWN:
                    if (event.key.keysym.mod == KMOD_LSHIFT) {
                        speed = defaultSpeed * 2;
                    }
                    switch (event.key.keysym.sym) {
                        case SDLK_w:
                            if (player1.y > 0) {
                                player1.y -= speed;
                            }
                            player1.direction = UP;
                            break;
                        case SDLK_s:
                            if (player1.y < WINDOW_HEIGHT - player1.height / 2) {
                                player1.y += speed;
                            }
                            player1.direction = DOWN;
                            break;
                        case SDLK_a:
                            if (player1.x > 0) {
                                player1.x -= speed;
                            }
                            player1.direction = LEFT;
                            break;
                        case SDLK_d:
                            if (player1.x < WINDOW_WIDTH - player1.width / 2) {
                                player1.x += speed;
                            }
                            player1.direction = RIGHT;
                            break;
                        case SDLK_ESCAPE:
                            SDL_Quit();
                            flag1 = 1;
                            break;
                    }
                    break;
                case SDL_QUIT:
                    SDL_Quit();
                    flag1 = 1;
                    break;
            }
        }
        SDL_RenderClear(renderer);
        RenderPlayer(player1, renderer);
        SDL_RenderPresent(renderer);  //使用渲染器更新窗体

        if (flag1) {
            break;
        }
    }

    return 0;
}