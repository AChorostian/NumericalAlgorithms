//
//  Created by Andrzej Chorostian on 09.10.2018.
//

#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <limits>

#define MAX_N 182 // confirmed by tests
#define SCR_W 1200 // SDL window attributes
#define SCR_H 800
#define SCR_X SDL_WINDOWPOS_UNDEFINED
#define SCR_Y SDL_WINDOWPOS_UNDEFINED

using namespace std;

SDL_Window* gWindow = NULL; // global SDL structures
SDL_Renderer* gRenderer = NULL;

double taylor1  , taylor2  , taylor3  , taylor4;
double roznica1 , roznica2 , roznica3 , roznica4;

double factorial[MAX_N] = {0}; // once calculated factorials

void init()
{
    SDL_Init( SDL_INIT_VIDEO );
    gWindow = SDL_CreateWindow( "Algorytmy Numeryczne", SCR_X, SCR_Y, SCR_W, SCR_H, SDL_WINDOW_SHOWN );
    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
}
void close()
{
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;
    SDL_Quit();
}
double taylorPatternFromBegin(double x, int n)
{
    double sin_sum=x;
    double e_sum=1;
    for( int i=1; i<n; i++)
    {
        double power=x;
        double fact=1;
        for(int j=1; j<=i; j++)
        {
            power = power * x * x;
            fact = fact * ((j*2) * ((j*2)+1));
        }
        if (i%2 == 1)
            power *= -1;
        sin_sum += power / fact;
    }
    for( int i=1; i<n; i++)
    {
        double power = 1;
        for( int j=1; j<=i; j++)
            power *= sin_sum;
        e_sum += power/factorial[i];
    }
    return e_sum;
}
double taylorDynamicFromBegin(double x, int n)
{
    double previous=x;
    double sin_sum=x;
    double e_sum=1;
    for( int i=1; i<n; i++)
    {
        previous *= (-1 * x * x) / ((2 + (2 * (i-1)) ) * (3 + (2 * (i-1) ))) ;
        sin_sum += previous;
    }
    previous=1;
    for( int i=1; i<n; i++)
    {
        previous *= sin_sum / i;
        e_sum += previous;
    }
    return e_sum;
}
double taylorPatternFromEnd(double x, int n)
{
    double sin_element[MAX_N]={0};
    double sin_sum=0;
    double e_element[MAX_N]={0};
    double e_sum=0;
    sin_element[0]= x;
    e_element[0]= 1;
    for( int i=1; i<n; i++)
    {
        double power=x;
        double fact=1;
        for(int j=1; j<=i; j++)
        {
            power = power * x * x;
            fact = fact * ((j*2) * ((j*2)+1));
        }
        if (i%2 == 1)
            power *= -1;
        sin_element[i]= power / fact;
    }
    for (int i=0; i<n; i++)
        sin_sum += sin_element[n-i-1];
    
    for( int i=1; i<n; i++)
    {
        double power = 1;
        for( int j=1; j<=i; j++)
            power *= sin_sum;
        e_element[i]= power/factorial[i];
    }
    for (int i=0; i<n; i++)
        e_sum += e_element[n-i-1];
    return e_sum;
}
double taylorDynamicFromEnd(double x, int n)
{
    double sin_element[MAX_N]={0};
    double sin_sum=0;
    double e_element[MAX_N]={0};
    double e_sum=0;
    sin_element[0]=x;
    e_element[0]=1;
    for( int i=1; i<n; i++)
    {
        sin_element[i] = sin_element[i-1] * (-1 * x * x) / ((2 + (2 * (i-1)) ) * (3 + (2 * (i-1) ))) ;
    }
    for (int i=0; i<n; i++)
        sin_sum += sin_element[n-i-1];
    for( int i=1; i<n; i++)
    {
        e_element[i] = e_element[i-1] * sin_sum / i;
    }
    for (int i=0; i<n; i++)
        e_sum += e_element[n-i-1];
    return e_sum;
}

void draw_big_point(double x, double y)
{
    SDL_RenderDrawPoint( gRenderer, x-1 , y-2 );
    SDL_RenderDrawPoint( gRenderer, x , y-2 );
    SDL_RenderDrawPoint( gRenderer, x+1 , y-2 );
    
    SDL_RenderDrawPoint( gRenderer, x-2 , y-1 );
    SDL_RenderDrawPoint( gRenderer, x-1 , y-1 );
    SDL_RenderDrawPoint( gRenderer, x , y-1 );
    SDL_RenderDrawPoint( gRenderer, x+1 , y-1 );
    SDL_RenderDrawPoint( gRenderer, x+2 , y-1 );
    
    SDL_RenderDrawPoint( gRenderer, x-2 , y );
    SDL_RenderDrawPoint( gRenderer, x-1 , y );
    SDL_RenderDrawPoint( gRenderer, x , y );
    SDL_RenderDrawPoint( gRenderer, x+1 , y );
    SDL_RenderDrawPoint( gRenderer, x+2 , y );
    
    SDL_RenderDrawPoint( gRenderer, x-2 , y+1 );
    SDL_RenderDrawPoint( gRenderer, x-1 , y+1 );
    SDL_RenderDrawPoint( gRenderer, x , y+1 );
    SDL_RenderDrawPoint( gRenderer, x+1 , y+1 );
    SDL_RenderDrawPoint( gRenderer, x+2 , y+1 );
    
    SDL_RenderDrawPoint( gRenderer, x-1 , y+2 );
    SDL_RenderDrawPoint( gRenderer, x , y+2 );
    SDL_RenderDrawPoint( gRenderer, x+1 , y+2 );
    
}


int main(int argc, const char * argv[]) {
    
    init();
    
    factorial[0] = 1;
    for( int i=1; i<MAX_N; i++)
        factorial[i] = factorial[i-1] * i;
    
    //cout.precision(60);
    
    bool quit = false;
    SDL_Event event;
    
    int procent=0;
    int tay_num=0;
    int ile_razy=1000000;
    
    double sum[4];
    double roznica[4];
    double garbage=0;
    
    double tay1[10000]={0};
    double tay2[10000]={0};
    double tay3[10000]={0};
    
    for( double x=-M_PI; x<M_PI ; x+=M_PI/(ile_razy/2) )
    {
        
        //roznica[0] = abs(exp(sin(x)) - taylorPatternFromBegin(x,100));
        //roznica[1] = abs(exp(sin(x)) - taylorPatternFromEnd(x,100));
        //roznica[2] = abs(exp(sin(x)) - taylorDynamicFromBegin(x,100));

        sum[0] += abs(exp(sin(x)) - taylorDynamicFromEnd(x,8));
        sum[1] += abs(exp(sin(x)) - taylorDynamicFromEnd(x,9));
        sum[2] += abs(exp(sin(x)) - taylorDynamicFromEnd(x,10));
        
        
        procent++;
        
        if (procent%(ile_razy/1000)==0)
        {
            tay1[tay_num] = round(sum[0]*20000);
            tay2[tay_num] = round(sum[1]*20000);
            tay3[tay_num] = round(sum[2]*20000);
            sum[0] = 0;
            sum[1] = 0;
            sum[2] = 0;
            tay_num++;
        }
        
        //procent++;
        cout << procent/(ile_razy/100) << "%\n";
    }
    
    cout << "garb: " << garbage;
    
    
    while( !quit )
    {
        while( SDL_PollEvent( &event ) != 0 )
        {
            //User requests quit
            if( event.type == SDL_QUIT )
            {
                quit = true;
            }
        }
        
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );
        int a=125;
        SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0x00 ); //black
        SDL_RenderDrawLine( gRenderer, a, 700, SCR_W-a, 700 );
        SDL_RenderDrawLine( gRenderer, a, 600, SCR_W-a, 600 );
        SDL_RenderDrawLine( gRenderer, a, 500, SCR_W-a, 500 );
        SDL_RenderDrawLine( gRenderer, a, 400, SCR_W-a, 400 );
        SDL_RenderDrawLine( gRenderer, a, 300, SCR_W-a, 300 );
        SDL_RenderDrawLine( gRenderer, a, 200, SCR_W-a, 200 );
        
        SDL_RenderDrawLine( gRenderer, SCR_W/2 - M_PI*150, 0, SCR_W/2 - M_PI*150, SCR_H-96 ); // -PI
        SDL_RenderDrawLine( gRenderer, SCR_W/2 - 150, 0, SCR_W/2 - 150, SCR_H-96 ); // -1
        SDL_RenderDrawLine( gRenderer, SCR_W/2, 0, SCR_W/2, SCR_H-96 ); // 0
        SDL_RenderDrawLine( gRenderer, SCR_W/2 + M_PI*150, 0, SCR_W/2 + M_PI*150, SCR_H-96 ); // +1
        SDL_RenderDrawLine( gRenderer, SCR_W/2 + 150, 0, SCR_W/2 + 150, SCR_H-96 ); // +PI
        
        for(int i=0; i<1000; i++)
        {
            SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF ); //blue
            draw_big_point(SCR_W/2 - M_PI*150 + i*3*M_PI/10, 700-tay1[i] );
            
            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF ); //red
            draw_big_point(SCR_W/2 - M_PI*150 + i*3*M_PI/10, 700-tay2[i] );
            
            SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF ); //green
            draw_big_point(SCR_W/2 - M_PI*150 + i*3*M_PI/10, 700-tay3[i] );
        }
        
        SDL_RenderPresent( gRenderer );
    }
    
    close();
    return 0;
}
