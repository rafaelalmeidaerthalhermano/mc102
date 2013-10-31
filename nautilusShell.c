/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Concha do caramujo Nautilus
    Versão : 1.0.0
    Concluída : 09/05/2011

    Narrativa Livre : O programa baseado em  Allegro 5 traça uma espiral com base na sequência de Fibonacci .
*/

#include <stdio.h>
#include <math.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define RESIZE_FACTOR 5
#define RIGHT_BOTTOM 0
#define LEFT_BOTTOM 1
#define RIGHT_TOP 2
#define LEFT_TOP 3

//método que calcula o arco de 90º à ser desenhado
void getArc(int* currentTerm, int* position, int* arcCenterX, int* arcCenterY, float* arcDirection)
{
    switch (*position)
    {
        case (RIGHT_BOTTOM) :
            *position = LEFT_BOTTOM;
            *arcDirection -= M_PI_2;
            *arcCenterX += fibonacciValue(*currentTerm-1) * RESIZE_FACTOR;
            break;

        case (LEFT_BOTTOM) :
            *position = RIGHT_TOP;
            *arcDirection -= M_PI_2;
            *arcCenterY -= fibonacciValue(*currentTerm-1) * RESIZE_FACTOR;
            break;

        case (RIGHT_TOP) :
            *position = LEFT_TOP;
            *arcDirection -= M_PI_2;
            *arcCenterX -= fibonacciValue(*currentTerm-1) * RESIZE_FACTOR;
            break;

        case (LEFT_TOP) :
            *position = RIGHT_BOTTOM;
            *arcDirection -= M_PI_2;
            *arcCenterY += fibonacciValue(*currentTerm-1) * RESIZE_FACTOR;
            break;

        default :
            *position = LEFT_BOTTOM;
            *arcDirection = M_PI_2 * 3;
            *arcCenterX = fibonacciValue(*currentTerm-1) * RESIZE_FACTOR;
            *arcCenterY = fibonacciValue(*currentTerm) * RESIZE_FACTOR;
            break;
    }
}

//método que calcula o valor de um termo na sequencia
int fibonacciValue(int position)
{
    if(position < 2) return 1;
    else return fibonacciValue(position-1) + fibonacciValue(position-2);
}

// inicialização do allegro
int allegroStart()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar allegro!\n");
        return 0;
    }

    return 1;
}

// inicialização do complemento "primitives"
int primitivesStart()
{
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar complemento primitives!\n");
        return 0;
    }

    return 1;
}

// inicialização do display
int displayStart(ALLEGRO_DISPLAY **display, int numberOfTerms)
{
    int windowHeight, windowWidth;

    windowWidth = (fibonacciValue(numberOfTerms) + fibonacciValue(numberOfTerms-1)) * RESIZE_FACTOR;
    windowHeight = (fibonacciValue(numberOfTerms)) * RESIZE_FACTOR;
    *display = al_create_display(windowWidth, windowHeight);
    if (!*display)
    {
        fprintf(stderr, "Falha ao criar display!\n");
        return 0;
    }

    return 1;
}

// inicialização da lista de eventos
int eventQueueStart(ALLEGRO_EVENT_QUEUE **eventQueue)
{
    *eventQueue = al_create_event_queue();
    if (!*eventQueue)
    {
        fprintf(stderr, "Falha ao criar lista de eventos!\n");
        return 0;
    }

    return 1;
}

int main(void)
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_COLOR color;
    ALLEGRO_EVENT event;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    int numberOfTerms = 10, currentTerm = 10, arcCenterX, arcCenterY, position = -1;
    float arcDirection;

    if(!allegroStart()) return -1;
    if(!primitivesStart()) return -1;
    if(!displayStart(&display, numberOfTerms)) return -1;
    if(!eventQueueStart(&eventQueue)) return -1;

    al_register_event_source(eventQueue, al_get_display_event_source(display));

    // preparando o display
    al_set_target_bitmap(al_get_backbuffer(display));
    al_clear_to_color(al_map_rgb(255, 255, 255));
    color = al_map_rgb(0,0,0);

    //montagem da espiral
    while(currentTerm>0)
    {
        getArc(&currentTerm, &position, &arcCenterX, &arcCenterY, &arcDirection);
        al_draw_arc(arcCenterX, arcCenterY, fibonacciValue(currentTerm) * RESIZE_FACTOR, arcDirection,  M_PI_2, color, 5);
        currentTerm--;
    }

    al_flip_display();

    while (true) if (al_peek_next_event(eventQueue, &event)) break;

    return 0;
}
