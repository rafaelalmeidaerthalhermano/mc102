/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Labirinto
    Vers�o : 1.0.0
    Conclu�da : 30/05/2011

    Tarefa
    A atividade consiste em escrever um programa com o aux�lio do Allegro 5 que construa um labirinto "perfeito" (isto �, um labirinto em que sempre � poss�vel encontrar um percurso entre duas c�lulas quaisquer do labirinto) e depois determine o percurso de uma c�lula na borda que representa o ponto de entrada e outra c�lula tamb�m na borda que representa o ponto de sa�da.


    Algoritmo para constru��o de um labirinto "perfeito"

    Um poss�vel algoritmo (adaptado de "How to Build a Maze") para construir um labirinto "perfeito" se baseia em um algoritmo de "busca em profundidade" e ele parte de um reticulado de c�lulas com todos os "muros" entre c�lulas levantados. Abaixo � representado um reticulado de c�lulas de 15 linhas e 20 colunas com os "muros" levantados.

    levantar muros entre todas as c�lulas
    criar pilhaDePosicoesDeCelulas
    totalDeCelulas <- n�mero de c�lulas da grade
    escolher aleatoriamente uma c�lula e denomin�-la celulaCorrente
    celulasVisitadas <- 1
    enquanto celulasVisitadas < totalDeCelulas
    encontrar todas as c�lulas vizinhas de celulaCorrente com muros intactos
    se uma ou mais foram encontradas
    escolher uma aleatoriamente e denomin�-la proximaCelula
    derrubar o muro entre proximaCelula e celulaCorrente
    empilhar a posi��o de celulaCorrente em pilhaDePosicoesDeCelulas
    considerar proximaCelula como celulaCorrente
    celulasVisitadas <- celulasVisitadas + 1
    sen�o
    desempilhar posi��o de c�lula pilhaDePosicoesDeCelulas e consider�-la como celulaCorrente



    Algoritmo para a busca da sa�da



    Tamb�m � poss�vel determinar a sa�da do labirinto a partir do algoritmo de "busca em profundidade":


    marcar todas as c�lulas como n�o visitadas
    criar pilhaDePosicoesDeCelulas
    marcar a c�lula de entrada do labirinto como visitada
    considerar a c�lula de entrada como sendo a celulaCorrente
    enquanto celulaCorrente diferente da c�lula de sa�da do labirinto
    encontrar todas as c�lulas vizinhas acess�veis de celulaCorrente ainda n�o visitadas
    se uma ou mais foram encontradas
    escolher uma aleatoriamente e denomin�-la proximaCelula
    marcar proximaCelula como visitada
    tra�ar segmento de reta entre celulaCorrente e proximaCelula
    empilhar a posi��o de celulaCorrente em pilhaDePosicoesDeCelulas
    considerar proximaCelula como celulaCorrente
    sen�o
    desempilhar posi��o de c�lula pilhaDePosicoesDeCelulas e consider�-la como celulaAnterior
    apagar segmento de reta entre celulaCorrente e celulaAnterior
    considerar celulaAnterior como celulaCorrente
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>

#define MAZE_DIMENSION 50
#define CELL_DIMENSION 5

#define ALONE 1
#define NEIGHBOR 0

#define LINE 0
#define COLUMN 1

int AllegroStart();
int PrimitivesStart();
int DisplayStart(ALLEGRO_DISPLAY**);
int EventQueueStart(ALLEGRO_EVENT_QUEUE**);

struct Cell
{
    int visited;

    int left;
    int right;
    int top;
    int bottom;
};

int isAlone(struct Cell point)
{
    return point.bottom == ALONE && point.top == ALONE && point.left == ALONE && point.right == ALONE;
}

void BuildMaze(struct Cell maze[MAZE_DIMENSION][MAZE_DIMENSION])
{
    int totalCells = MAZE_DIMENSION * MAZE_DIMENSION;
    int visitedCells = 1;

    int positionsHeap[totalCells][2];
    int neighborsHeap[4][3];

    int positionsHeapPosition = 0;
    int neighborsHeapPosition = 0;

    int currentCell[2];
    int nextCell[2];

    int neighbor;

    currentCell[LINE] = 0;
    currentCell[COLUMN] = 0;

    while (visitedCells < totalCells)
    {
        neighborsHeapPosition = 0;

        //pega vizinhos
        if(currentCell[LINE] > 0)
            if(isAlone(maze[currentCell[LINE] - 1][currentCell[COLUMN]]))
            {
                neighborsHeap[neighborsHeapPosition][LINE] = currentCell[LINE] - 1;
                neighborsHeap[neighborsHeapPosition][COLUMN] = currentCell[COLUMN];
                neighborsHeap[neighborsHeapPosition][2] = 1;
                neighborsHeapPosition++;
            }

        if(currentCell[LINE] < MAZE_DIMENSION - 1)
            if(isAlone(maze[currentCell[LINE] + 1][currentCell[COLUMN]]))
            {
                neighborsHeap[neighborsHeapPosition][LINE] = currentCell[LINE] + 1;
                neighborsHeap[neighborsHeapPosition][COLUMN] = currentCell[COLUMN];
                neighborsHeap[neighborsHeapPosition][2] = 2;
                neighborsHeapPosition++;
            }

        if(currentCell[COLUMN] > 0)
            if(isAlone(maze[currentCell[LINE]][currentCell[COLUMN] - 1]))
            {
                neighborsHeap[neighborsHeapPosition][LINE] = currentCell[LINE];
                neighborsHeap[neighborsHeapPosition][COLUMN] = currentCell[COLUMN] - 1;
                neighborsHeap[neighborsHeapPosition][2] = 3;
                neighborsHeapPosition++;
            }

        if(currentCell[COLUMN] < MAZE_DIMENSION - 1)
            if(isAlone(maze[currentCell[LINE]][currentCell[COLUMN] + 1]))
            {
                neighborsHeap[neighborsHeapPosition][LINE] = currentCell[LINE];
                neighborsHeap[neighborsHeapPosition][COLUMN] = currentCell[COLUMN] + 1;
                neighborsHeap[neighborsHeapPosition][2] = 4;
                neighborsHeapPosition++;
            }

        if (neighborsHeapPosition > 0)
        {
            //escolhe um vizinho aleat�rio
            neighbor = rand() % neighborsHeapPosition;

            //derruba paredes
            if(neighborsHeap[neighbor][2] == 1)
            {
                maze[currentCell[LINE]][currentCell[COLUMN]].top = NEIGHBOR;
                maze[currentCell[LINE] - 1][currentCell[COLUMN]].bottom = NEIGHBOR;
            }

            if(neighborsHeap[neighbor][2] == 2)
            {
                maze[currentCell[LINE]][currentCell[COLUMN]].bottom = NEIGHBOR;
                maze[currentCell[LINE] + 1][currentCell[COLUMN]].top = NEIGHBOR;
            }

            if(neighborsHeap[neighbor][2] == 3)
            {
                maze[currentCell[LINE]][currentCell[COLUMN]].left = NEIGHBOR;
                maze[currentCell[LINE]][currentCell[COLUMN] - 1].right = NEIGHBOR;
            }

            if(neighborsHeap[neighbor][2] == 4)
            {
                maze[currentCell[LINE]][currentCell[COLUMN]].right = NEIGHBOR;
                maze[currentCell[LINE]][currentCell[COLUMN] + 1].left = NEIGHBOR;
            }

            nextCell[LINE] = neighborsHeap[neighbor][LINE];
            nextCell[COLUMN] = neighborsHeap[neighbor][COLUMN];
            //empilha o corrente
            positionsHeap[positionsHeapPosition][LINE] = currentCell[LINE];
            positionsHeap[positionsHeapPosition][COLUMN] = currentCell[COLUMN];
            positionsHeapPosition++;

            currentCell[LINE] = nextCell[LINE];
            currentCell[COLUMN] = nextCell[COLUMN];

            visitedCells++;
        }
        else
        {
            positionsHeapPosition--;
            currentCell[LINE] = positionsHeap[positionsHeapPosition][LINE];
            currentCell[COLUMN] = positionsHeap[positionsHeapPosition][COLUMN];
        }
    }
}

void ShowSolution(struct Cell maze[MAZE_DIMENSION][MAZE_DIMENSION])
{
    int line, column;

    int positionsHeap[MAZE_DIMENSION*MAZE_DIMENSION][2];
    int positionsHeapPosition = 0;

    int currentCell[2];
    int nextCell[2];

    int neighbor;
    int findNeighbor;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_EVENT event;

    AllegroStart();
    PrimitivesStart();
    DisplayStart(&display);
    EventQueueStart(&eventQueue);

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_set_target_bitmap(al_get_backbuffer(display));

    //desenha labirinto
    al_clear_to_color(al_map_rgb(255, 255, 255));

    for (line = 0; line < MAZE_DIMENSION; line++)
        for(column = 0; column < MAZE_DIMENSION; column++)
        {
            if(maze[line][column].right == ALONE)
                al_draw_line(line*CELL_DIMENSION, (column+1)*CELL_DIMENSION,(line+1)*CELL_DIMENSION, (column+1)*CELL_DIMENSION, al_map_rgb(0, 0, 0), 1);
            if(maze[line][column].bottom == ALONE)
                al_draw_line((line+1)*CELL_DIMENSION, column*CELL_DIMENSION,(line+1)*CELL_DIMENSION, (column+1)*CELL_DIMENSION, al_map_rgb(0, 0, 0), 1);
        }

    al_flip_display();

    currentCell[LINE] = 0;
    currentCell[COLUMN] = 0;
    maze[currentCell[LINE]][currentCell[COLUMN]].visited = 1;

    //procura solu��o
    while (currentCell[LINE] != MAZE_DIMENSION-1 || currentCell[COLUMN] != MAZE_DIMENSION-1)
    {
        if (al_peek_next_event(eventQueue, &event)) break;

        findNeighbor = 0;
        //procura vizinhos nao visitados
        if(maze[currentCell[LINE]][currentCell[COLUMN]].top == NEIGHBOR)
            if(!maze[currentCell[LINE] - 1][currentCell[COLUMN]].visited)
            {
                nextCell[LINE] = currentCell[LINE] - 1;
                nextCell[COLUMN] = currentCell[COLUMN];
                findNeighbor = 1;
            }

        if(maze[currentCell[LINE]][currentCell[COLUMN]].bottom == NEIGHBOR)
            if(!maze[currentCell[LINE] + 1][currentCell[COLUMN]].visited)
            {
                nextCell[LINE] = currentCell[LINE] + 1;
                nextCell[COLUMN] = currentCell[COLUMN];
                findNeighbor = 1;
            }

        if(maze[currentCell[LINE]][currentCell[COLUMN]].left == NEIGHBOR)
            if(!maze[currentCell[LINE]][currentCell[COLUMN] - 1].visited)
            {
                nextCell[LINE] = currentCell[LINE];
                nextCell[COLUMN] = currentCell[COLUMN] - 1;
                findNeighbor = 1;
            }

        if(maze[currentCell[LINE]][currentCell[COLUMN]].right == NEIGHBOR)
            if(!maze[currentCell[LINE]][currentCell[COLUMN] + 1].visited)
            {
                nextCell[LINE] = currentCell[LINE];
                nextCell[COLUMN] = currentCell[COLUMN] + 1;
                findNeighbor = 1;
            }

        if (findNeighbor)
        {
            //deseha tra�ado
            al_draw_line(currentCell[LINE] * CELL_DIMENSION + CELL_DIMENSION/2, currentCell[COLUMN] * CELL_DIMENSION + CELL_DIMENSION/2 ,nextCell[LINE] * CELL_DIMENSION + CELL_DIMENSION/2, nextCell[COLUMN] * CELL_DIMENSION + CELL_DIMENSION/2, al_map_rgb(255, 0, 0), 2);

            maze[nextCell[LINE]][nextCell[COLUMN]].visited = 1;

            positionsHeap[positionsHeapPosition][LINE] = currentCell[LINE];
            positionsHeap[positionsHeapPosition][COLUMN] = currentCell[COLUMN];
            positionsHeapPosition++;

            currentCell[LINE] = nextCell[LINE];
            currentCell[COLUMN] = nextCell[COLUMN];
        }
        else
        {
            positionsHeapPosition--;
            nextCell[LINE] = currentCell[LINE];
            nextCell[COLUMN] = currentCell[COLUMN];

            currentCell[LINE] = positionsHeap[positionsHeapPosition][LINE];
            currentCell[COLUMN] = positionsHeap[positionsHeapPosition][COLUMN];
            //apaga tra�ado
            al_draw_line(currentCell[LINE] * CELL_DIMENSION + CELL_DIMENSION/2, currentCell[COLUMN] * CELL_DIMENSION + CELL_DIMENSION/2 ,nextCell[LINE] * CELL_DIMENSION + CELL_DIMENSION/2,nextCell[COLUMN] * CELL_DIMENSION + CELL_DIMENSION/2, al_map_rgb(255, 255, 255), 2);
        }

        al_flip_display();
        al_rest(0.1);
    }

    while (true){if (al_peek_next_event(eventQueue, &event)) break;}
}

int main(void)
{
    struct Cell maze[MAZE_DIMENSION][MAZE_DIMENSION];
    int line, column;

    srand(time(NULL));

    for (line = 0; line < MAZE_DIMENSION; line++)
        for(column = 0; column < MAZE_DIMENSION; column++)
        {
            maze[line][column].left = ALONE;
            maze[line][column].right = ALONE;
            maze[line][column].top = ALONE;
            maze[line][column].bottom = ALONE;

            maze[line][column].visited = 0;
        }


    BuildMaze(maze);

    ShowSolution(maze);

    return 0;
}


// inicializa��o do allegro
int AllegroStart()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar allegro!\n");
        return 0;
    }

    return 1;
}

// inicializa��o do complemento "primitives"
int PrimitivesStart()
{
    if (!al_init_primitives_addon())
    {
        fprintf(stderr, "Falha ao inicializar complemento primitives!\n");
        return 0;
    }

    return 1;
}

// inicializa��o do display
int DisplayStart(ALLEGRO_DISPLAY **display)
{
    int windowHeight, windowWidth;

    windowWidth = CELL_DIMENSION * (MAZE_DIMENSION);
    windowHeight = CELL_DIMENSION * (MAZE_DIMENSION);

    *display = al_create_display(windowWidth, windowHeight);
    if (!*display)
    {
        fprintf(stderr, "Falha ao criar display!\n");
        return 0;
    }

    return 1;
}

// inicializa��o da lista de eventos
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
