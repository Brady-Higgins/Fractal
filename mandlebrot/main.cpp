#include <iostream>
#include <SDL2/SDL.h>

const int WIDTH = 800, HEIGHT = 600;
const int X_BOUND = 50, Y_BOUND = 800;

void set_background(SDL_Renderer *renderer)
{
    // sets background to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

void draw_axis(SDL_Renderer *renderer )
{
    SDL_RenderSetScale(renderer, 1, 1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    // x-axis
    SDL_RenderDrawLine(renderer, 0, HEIGHT/2, WIDTH, HEIGHT/2);
    // y-axis
    SDL_RenderDrawLine(renderer, WIDTH/2, 0, WIDTH/2, HEIGHT);
    SDL_RenderPresent(renderer);
}

void plot_equation(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    int x_origin = WIDTH / 2;
    int y_origin = HEIGHT / 2;
    int x_step = WIDTH / X_BOUND;
    // i serves as intercept for plotting to screen
    int x = -X_BOUND / 2;
    for (int i = 0; i <= WIDTH; i++)
    {
        // Keep Graph Width but num x intercepts = X_BOUND * 2
        if (i % x_step == 0)
        {
            int y = x * x;
            SDL_RenderDrawPoint(renderer, i, y_origin - y);
            x++;
        }
    }
    SDL_RenderPresent(renderer);
}

int main( int argc, char *argv[] )
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("HELLo World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, 0, 0);
    set_background(renderer);
    draw_axis(renderer);
    plot_equation(renderer);

    // Check if window is init wrong
    if (NULL == window)
    {
        std::cout << "Error" << SDL_GetError() << std::endl;
        return 1;
    }

    // Keep Window until exit event
    SDL_Event windowEvent;
    while (true)
    {
        if ( SDL_PollEvent( &windowEvent)){
            if (SDL_QUIT == windowEvent.type){
                break;
            }
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}