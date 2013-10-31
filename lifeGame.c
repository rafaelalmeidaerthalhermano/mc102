/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Jogo da Vida
    Versão : 1.0.0
    Concluída : 16/05/2011

    Narrativa Livre : O programa usa a biblioteca allegro para implemenatar o jogo da vida em um toro.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define TOROID_DIMENSION 50
#define CELL_DIMENSION 5

#define DEAD 0
#define ALIVE 1

int AllegroStart();
int PrimitivesStart();
int DisplayStart(ALLEGRO_DISPLAY**);
int EventQueueStart(ALLEGRO_EVENT_QUEUE**);
int CellIsAlone(int);
int CellIsHungry(int);
int CellCanBorn(int);
int AdjustInterval(int);
int AliveNeighbors(int [][TOROID_DIMENSION], int, int);
void RenderToroid(int [][TOROID_DIMENSION]);
void GenerateRandomToroid(int [][TOROID_DIMENSION]);
void CopyToroid(int [][TOROID_DIMENSION], int [][TOROID_DIMENSION]);

int main (void)
{
    int currentToroid[TOROID_DIMENSION][TOROID_DIMENSION], lastToroid[TOROID_DIMENSION][TOROID_DIMENSION];
    int horizontalIndex, verticalIndex, aliveNeighbors;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_EVENT event;

    if (!AllegroStart()) return -1;
    if (!PrimitivesStart()) return -1;
    if (!DisplayStart(&display)) return -1;
    if (!EventQueueStart(&eventQueue)) return -1;

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_set_target_bitmap(al_get_backbuffer(display));

    //Gerar matriz aleatória
    GenerateRandomToroid(currentToroid);
    CopyToroid(currentToroid, lastToroid);

    //calcular estado atual do toro
    while (true)
    {
        if (al_peek_next_event(eventQueue, &event)) break;

        //calcular o estado de cada célula
        for (horizontalIndex = 0; horizontalIndex < TOROID_DIMENSION; horizontalIndex ++)
            for (verticalIndex = 0; verticalIndex < TOROID_DIMENSION; verticalIndex ++)
            {
                aliveNeighbors = AliveNeighbors(lastToroid, horizontalIndex, verticalIndex);

                if (CellIsAlone(aliveNeighbors) || CellIsHungry(aliveNeighbors))
                    currentToroid[horizontalIndex][verticalIndex] = DEAD;
                else if (CellCanBorn(aliveNeighbors))
                    currentToroid[horizontalIndex][verticalIndex] = ALIVE;
            }

        //armazenar o novo toro
        CopyToroid(currentToroid, lastToroid);

        //printar o toro
        al_clear_to_color(al_map_rgb(255, 255, 255));
        RenderToroid(currentToroid);
        al_flip_display();

        al_rest(0.1);
    }

    return 0;
}

// inicialização do allegro
int AllegroStart()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar allegro!\n");
        return 0;
    }

    return 1;
}

// inicialização do complemento "primitives"
int PrimitivesStart()
{
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar complemento primitives!\n");
        return 0;
    }

    return 1;
}

// inicialização do display
int DisplayStart(ALLEGRO_DISPLAY **display)
{
    int windowHeight, windowWidth;

    windowWidth = CELL_DIMENSION * TOROID_DIMENSION;
    windowHeight = CELL_DIMENSION * TOROID_DIMENSION;

    *display = al_create_display(windowWidth, windowHeight);
    if (!*display)
    {
        fprintf(stderr, "Falha ao criar display!\n");
        return 0;
    }

    return 1;
}

// inicialização da lista de eventos
int EventQueueStart(ALLEGRO_EVENT_QUEUE **eventQueue)
{
    *eventQueue = al_create_event_queue();
    if (!*eventQueue)
    {
        fprintf(stderr, "Falha ao criar lista de eventos!\n");
        return 0;
    }

    return 1;
}

int CellIsAlone(int neighbors)
{
    return (neighbors < 2);
}

int CellIsHungry(int neighbors)
{
    return (neighbors > 3);
}

int CellCanBorn(int neighbors)
{
    return (neighbors == 3);
}

int AdjustInterval(int position)
{
    if (position < 0)
        return TOROID_DIMENSION - 1;
    else if (position > TOROID_DIMENSION - 1)
        return 0;
    else
        return position;
}

int AliveNeighbors(int toroid[][TOROID_DIMENSION], int horizontalIndex, int verticalIndex)
{
    int currentHorizontalIndex, currentVerticalIndex, aliveNeighbors = 0;

    for (currentHorizontalIndex = horizontalIndex - 1; currentHorizontalIndex <= horizontalIndex + 1; currentHorizontalIndex ++)
        for (currentVerticalIndex = verticalIndex - 1; currentVerticalIndex <= verticalIndex + 1; currentVerticalIndex ++)
            aliveNeighbors += toroid[AdjustInterval(currentHorizontalIndex)][AdjustInterval(currentVerticalIndex)];

    aliveNeighbors -= toroid[horizontalIndex][verticalIndex];

    return aliveNeighbors;
}

void GenerateRandomToroid(int toroid[][TOROID_DIMENSION])
{
    int horizontalIndex, verticalIndex;

    srand(time(NULL));

    for (horizontalIndex = 0; horizontalIndex < TOROID_DIMENSION; horizontalIndex ++)
        for (verticalIndex = 0; verticalIndex < TOROID_DIMENSION; verticalIndex ++)
            toroid[horizontalIndex][verticalIndex] = rand() % 2;
}

void CopyToroid(int originToroid[][TOROID_DIMENSION], int destinyToroid[][TOROID_DIMENSION])
{
    int horizontalIndex, verticalIndex;

    for (horizontalIndex = 0; horizontalIndex < TOROID_DIMENSION; horizontalIndex ++)
        for (verticalIndex = 0; verticalIndex < TOROID_DIMENSION; verticalIndex ++)
            destinyToroid[horizontalIndex][verticalIndex] = originToroid[horizontalIndex][verticalIndex];
}

void RenderToroid(int toroid[][TOROID_DIMENSION])
{
    ALLEGRO_COLOR color;
    int horizontalIndex, verticalIndex;


    for (horizontalIndex = 0; horizontalIndex < TOROID_DIMENSION; horizontalIndex ++)
    {
        for (verticalIndex = 0; verticalIndex < TOROID_DIMENSION; verticalIndex ++)
        {
            color = toroid[horizontalIndex][verticalIndex] ? al_map_rgb(255, 0, 0) : al_map_rgb(255, 255, 255);
            al_draw_filled_rectangle(horizontalIndex * CELL_DIMENSION, verticalIndex * CELL_DIMENSION, (horizontalIndex + 1) * CELL_DIMENSION, (verticalIndex + 1) * CELL_DIMENSION, color);
        }
    }
}
