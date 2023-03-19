#include <SDL2/SDL.h>
#include <stdio.h>
const int SCREEN_WIDTH = 900;
const int SCREEN_HEIGHT = 450;
const int BORDA = 10;

void DrawCircle(SDL_Renderer * renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
   const int32_t diameter = (radius * 2);
   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
   while (x >= y)
   {
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
      if (error <= 0)
      {
         ++y;
         error += ty;
         ty += 2;
      }
      if (error > 0)
      {
         --x;
         tx += 2;
         error += (tx - diameter);
      }
   }
}
int main( int argc, char* args[] )
{
    SDL_Window* window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Surface* screenSurface = NULL;
    double rx = 10; 
    double ry = 800; 
    double vx = 2 / 10.0; 
    double vy = -5 / 10.0;
    double ax = 0;
    double ay = 5 / 20000.0; 
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    else
    {
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        }
         else
        {
            screenSurface = SDL_GetWindowSurface( window );
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if (renderer == NULL)
                printf("Erro! - criando renderer");
            bool acabou = false;
            for (;!acabou;)
            {
                SDL_Event e;  
                while( SDL_PollEvent( &e ) )
                {
                     if( e.type == SDL_QUIT ) 
                         acabou= true;
                } 
                SDL_SetRenderDrawColor(renderer, 0, 100, 0, 0);
                SDL_RenderClear(renderer);
                DrawCircle(renderer, rx, ry, 20);
                rx = rx + vx;
                ry = ry + vy;
                vx = vx + ax;
                vy = vy + ay;
        
                SDL_SetRenderDrawColor(renderer, 139, 69, 19, SDL_ALPHA_OPAQUE);
                SDL_RenderDrawLine(renderer, 0 + BORDA, 0 + BORDA, SCREEN_WIDTH - BORDA, 0 + BORDA);
                SDL_RenderDrawLine(renderer, SCREEN_WIDTH - BORDA, 0 + BORDA, SCREEN_WIDTH - BORDA, SCREEN_HEIGHT - BORDA);
                SDL_RenderDrawLine(renderer, BORDA, SCREEN_HEIGHT - BORDA, SCREEN_WIDTH - BORDA, SCREEN_HEIGHT - BORDA);
                SDL_RenderDrawLine(renderer, BORDA, BORDA, BORDA, SCREEN_HEIGHT - BORDA);
                SDL_RenderPresent(renderer); 
            }
        }
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    SDL_Quit();
    return 0;
}
