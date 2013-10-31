/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Foca no tanque
    Versão : 1.0.0
    Concluída : 18/04/2011

    Narrativa Livre : O programa renderiza uma foca em um tanque que depois de algum tempo emerge para respirar.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

#define X 0
#define Y 1

const int TANK_WIDTH = 640;
const int TANK_HEIGHT = 480;

const int SEAL_WIDTH = 96;
const int SEAL_HEIGHT = 58;

const int BREATHING_VERTICAL_POSITION = 10;

const int RIGHT_MARGIN = 20;
const int LEFT_MARGIN = 20;
const int TOP_MARGIN = 40;
const int BOTTOM_MARGIN = 20;

//Método que retorna o estado da foca
int sealIsSubmerged(int position[])
{
    return (position[Y] != BREATHING_VERTICAL_POSITION);
}

//Método que diz se a foca precisa respirar
int sealNeedsToBreath()
{
    return (rand() % 3 == 0);
}

//Método que diz se a foca respirou o bastante
int sealCanSumberge()
{
    return (rand() % 10 == 0);
}

//Método que retorna uma posição horizontal randomica dentro da area permitida
int randomHorizontalPosition()
{
    return LEFT_MARGIN + rand() % (TANK_WIDTH - SEAL_WIDTH - LEFT_MARGIN - RIGHT_MARGIN);
}

//Método que retorna uma posição vertical randomica dentro da area permitida
int randomVerticalPosition()
{
    return TOP_MARGIN + rand() % (TANK_HEIGHT - SEAL_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN);
}

//Método que faz o movimento na foca no display
void moveSeal(int newPosition[], int oldPosition[] ,int tank, int seal)
{
      int x = oldPosition[X], y = oldPosition[Y];
      while(
                //garante que o laço sera executado até o final do movimento da foca sendo progressivo ou retrógrado
                ((newPosition[X] > oldPosition[X] && x < newPosition[X] ) || (newPosition[X] < oldPosition[X] && x > newPosition[X] )) ||
                ((newPosition[Y] > oldPosition[Y] && y < newPosition[Y] ) || (newPosition[Y] < oldPosition[Y] && y > newPosition[Y] ))
            )
      {
            al_draw_bitmap(tank, 0, 0, 0);
            al_draw_bitmap(seal, x , y , (newPosition[X] > oldPosition[X] ? 0 : 1));
            al_flip_display();
            al_rest(0.01);

            if(newPosition[X] > oldPosition[X])
            {
                //caso o movimento seja progressivo incrementa a posição
                if (x < newPosition[X] ) x++;
            }
            else
            {
                //caso o movimento seja retrógrado diminui a posição
                if (x > newPosition[X] ) x--;
            }

            if(newPosition[Y] > oldPosition[Y])
            {
                //caso o movimento seja progressivo incrementa a posição
                if (y < newPosition[Y] ) y++;
            }
            else
            {
                //caso o movimento seja retrógrado diminui a posição
                if (y > newPosition[Y] ) y--;
            }
      }
}

//Método que inicializa as bibliotecas do allegro
int allegroStart()
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar allegro!\n");
        return 0;
    }

    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar o complemento image!\n");
        return 0;
    }

    return 1;
}

//Método que cria o display
int displayStart(int *display)
{
    *display = al_create_display(TANK_WIDTH, TANK_HEIGHT);
    if (! *display)
    {
        fprintf(stderr, "Falha ao criar display!\n");
        return 0;
    }
    al_set_window_title(*display, "Foca em tanque sem audio");
    al_set_target_bitmap(al_get_backbuffer(*display));

    return 1;
}

//Método que inicializa a fila de eventos
int eventQueueStart(int *eventQueue)
{
    *eventQueue = al_create_event_queue();
    if (!*eventQueue)
    {
        fprintf(stderr, "Falha ao criar fila de eventos!\n");
        return -1;
    }
    return 1;
}

//Método que cria a imagem do tanque
int tankStart(int *tank)
{
    *tank = al_load_bitmap("tanque.gif");
    if (!*tank)
    {
        fprintf(stderr, "Falha ao carregar tanque.gif\n");
        return -1;
    }
    return 1;
}

//Método que cria a imagem da foca
int sealStart(int *seal)
{
    *seal = al_load_bitmap("foca.gif");
    if (!*seal)
    {
        fprintf(stderr, "Falha ao carregar foca.gif\n");
        return -1;
    }
    return 1;
}

int main(void)
{
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;
    ALLEGRO_EVENT event;
    ALLEGRO_BITMAP *tank;
    ALLEGRO_BITMAP *seal;

    int oldPosition[2], newPosition[2];

    //inicializa as variáveis necessárias
    if(!allegroStart()) return -1;
    if(!displayStart(&display)) return -1;
    if(!eventQueueStart(&eventQueue)) return -1;
    if(!tankStart(&tank)) return -1;
    if(!sealStart(&seal)) return -1;

    al_register_event_source(eventQueue, al_get_display_event_source(display));

    srand(time(NULL));

    oldPosition[X] = randomHorizontalPosition();
    oldPosition[Y] = randomVerticalPosition();

    while (true)
    {
          //caso o usuario queira sair
          if (al_peek_next_event(eventQueue, &event))
              if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) break;

          //verificar o estado da foca
          if(sealIsSubmerged(oldPosition))
          {
                //verifica se a foca precisa respirar
                if(sealNeedsToBreath()) newPosition[Y] = BREATHING_VERTICAL_POSITION;
                else newPosition[Y] = randomVerticalPosition();
          }
          else
          {
                //verifica se a foca ja pode mergulhar
                if(sealCanSumberge) newPosition[Y] = randomVerticalPosition();
                else newPosition[Y] = BREATHING_VERTICAL_POSITION;
          }
          //pega uma posição qualquer na horizontal
          newPosition[X] = randomHorizontalPosition();

          moveSeal(newPosition, oldPosition, tank, seal);

          //armazena a posição atual da foca
          oldPosition[X] = newPosition[X];
          oldPosition[Y] = newPosition[Y];
    }

    return 0;
}
