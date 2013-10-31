/*
    Autor : Rafael Almeida Erthal Hermano
    Turma : MC102
    RA : 121286

    Programa : Jogo da Vida
    Vers�o : 1.0.0
    Conclu�da : 23/05/2011

    Narrativa Livre :
    Alternativa A (valendo 10.0):
    Escreva um programa com o apoio da biblioteca Allegro 5, que implemente o Jogo da Velha, sendo o usu�rio um jogador e o computador o outro. No in�cio, o programa deve sortear (definir aleatoriamente) quem come�a o jogo. O programa deve sempre deixar claro de quem � a vez.
    Segundo o artigo "Jogo da Velha" da Wikipedia,

    Um jogador pode facilmente jogar um jogo perfeito seguindo as seguintes regras, por ordem de prioridade:
    Em geral, � melhor jogar no centro e em seguida nos cantos pois h� maior possibilidade de bloquear ou vencer.
    1.Ganhar: Se voc� tem duas pe�as numa linha, ponha a terceira.
    2.Bloquear: Se o oponente tiver duas pe�as em linha, ponha a terceira para boque�-lo.
    3.Tri�ngulo: Crie uma oportunidade em que voc� poder� ganhar de duas maneiras.
    4.Bloquear o Tri�ngulo do oponente:

    1.Op��o 1: Crie 2 pe�as em linha para for�ar o oponente a se defender, contanto que n�o resulte nele criando um tri�ngulo ou vencendo. Por exemplo, se 'X' tem dois cantos opostos do tabuleiro e 'O' tem o centro, 'O' n�o pode jogar num canto (Jogar no canto nesse cen�rio criaria um tri�ngulo em que 'X' vence).
    2.Op��o 2: Se existe uma configura��o em que o oponente pode formar um tri�ngulo, bloqueie-no.
    5.Centro: Jogue no centro.
    6.Canto vazio: jogue num canto vazio.
    Em suma, a n�o ser em condi��es especiais, o jogador deve ter prefer�ncia pela posi��o central, seguida pelos cantos, seguidos pelas bordas.

    Quando � a vez do computador, ele deve posicionar a sua pe�a segundo a estrat�gia definida para o "jogo perfeito" detalhada acima. O usu�rio indica o posicionamento de sua pe�a atrav�s de um clique na posi��o do tabuleiro com o bot�o esquerdo do mouse. Se a posi��o j� est� ocupada, uma advert�ncia precisa ser dada com a fun��o al_show_native_message_box( ) [Native dialogs support, Allegro 5 Manual]. O programa deve dar uma mensagem apropriada quando houver um empate ou quando algu�m (o usu�rio ou o computador) ganhar o jogo (aplausos?).

    //FICOU FALTANDO EXIBIR DE QUEM � A VEZ.(REALMENTE NECESS�RIO?? TENDO EM VISTA QUE A JOGADA DO COMPUTADOR OCORRE MUITO R�PIDO)
*/

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#define EMPTY -1
#define COMPUTER 0
#define PLAYER 1

#define X 0
#define Y 1

#define HASH_DIMENSION 3
#define CELL_DIMENSION 115

int AllegroStart();
int ImageStart();
int MouseStart();
int DisplayStart(ALLEGRO_DISPLAY**);
int EventQueueStart(ALLEGRO_EVENT_QUEUE**);

void RenderHash(int hash[HASH_DIMENSION][HASH_DIMENSION]);
void CopyHash(int hashOrigin[HASH_DIMENSION][HASH_DIMENSION], int hashDestiny[HASH_DIMENSION][HASH_DIMENSION]);
int IsDraw(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int GameOver(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int WinnigModes(int hash[HASH_DIMENSION][HASH_DIMENSION], int user);
int IsWinner(int hash[HASH_DIMENSION][HASH_DIMENSION], int user);
int MovementIsValid(int hash[HASH_DIMENSION][HASH_DIMENSION], int cell[2]);
int CenterIsAvailable(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int CornerIsAvailable(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int *GetPosition(int line, int column);
int *CenterPosition();
int *RandomCorner(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int CanWin(int hash[HASH_DIMENSION][HASH_DIMENSION], int user);
int *GetWinningPosition(int hash[HASH_DIMENSION][HASH_DIMENSION], int user);
int CanBuildTriangle(int hash[HASH_DIMENSION][HASH_DIMENSION], int user);
int *GetTrianglePosition(int hash[HASH_DIMENSION][HASH_DIMENSION], int user);

int PlayPlayer(int hash[HASH_DIMENSION][HASH_DIMENSION], ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_DISPLAY **display);
int *GetCellCicked(ALLEGRO_EVENT_QUEUE **eventQueue);
int PlayerCanWin(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int PlayerCanBuildTriangle(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int *PlayerWinningPosition(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int *PlayerTrianglePosition(int hash[HASH_DIMENSION][HASH_DIMENSION]);

int PlayComputer(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int *GetComputerMovement(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int ComputerCanWin(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int ComputerCanBuildTriangle(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int *ComputerWinningPosition(int hash[HASH_DIMENSION][HASH_DIMENSION]);
int *ComputerTrianglePosition(int hash[HASH_DIMENSION][HASH_DIMENSION]);

int main(void)
{
    int hash[HASH_DIMENSION][HASH_DIMENSION];
    int playerRound, x;

    int line, column;

    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *eventQueue;

    for(line = 0; line < HASH_DIMENSION; line++)
        for(column = 0; column < HASH_DIMENSION; column++)
            hash[line][column] = -1;

    if (!AllegroStart()) return -1;
    if (!ImageStart()) return -1;
    if (!MouseStart()) return -1;
    if (!DisplayStart(&display)) return -1;
    if (!EventQueueStart(&eventQueue)) return -1;

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_set_target_bitmap(al_get_backbuffer(display));

    playerRound = rand() % 2;

    RenderHash(hash);

    while ( !GameOver(hash) )
    {
        if ( playerRound == COMPUTER )playerRound = PlayComputer(hash);
        else playerRound = PlayPlayer(hash, &eventQueue, &display);

        RenderHash(hash);
    }

    if (IsWinner(hash, COMPUTER)) al_show_native_message_box(display,"Computador Venceu", "", "Computador Venceu", "Ok",1);
    else if (IsWinner(hash, PLAYER)) al_show_native_message_box(display,"Voc� Venceu", "", "Voc� Venceu", "Ok",1);
    else al_show_native_message_box(display,"Deu Velha", "", "Deu Velha", "Ok",1);

    return 0;
}

/*Fun��es Gerais
----------------------------------------------------------------------------------*/
//Desenha RASH
void RenderHash(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    int line, column;
    ALLEGRO_BITMAP *backgroud, *oImage, *xImage;

    backgroud = al_load_bitmap("background.png");
    oImage = al_load_bitmap("imageO.png");
    xImage = al_load_bitmap("imageX.png");

    al_clear_to_color(al_map_rgb(255, 255, 255));
    al_draw_bitmap(backgroud, 0, 0, 0);

    for (line = 0; line < HASH_DIMENSION; line++)
    {
        for (column = 0; column < HASH_DIMENSION; column++)
            switch(hash[line][column])
            {
                case 0:
                    al_draw_bitmap(oImage,line * CELL_DIMENSION,column * CELL_DIMENSION,0);
                    break;

                case 1:
                    al_draw_bitmap(xImage,line * CELL_DIMENSION,column * CELL_DIMENSION,0);
                    break;
            }
    }
    al_flip_display();
}

//Copia rash
void CopyHash(int hashOrigin[HASH_DIMENSION][HASH_DIMENSION], int hashDestiny[HASH_DIMENSION][HASH_DIMENSION])
{
    int line, column;

    for (line = 0; line < HASH_DIMENSION; line++)
        for (column = 0; column < HASH_DIMENSION; column++)
            hashDestiny[line][column] = hashOrigin[line][column];
}

//verifica se o jogo acabou
int GameOver(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return IsWinner(hash, COMPUTER) || IsWinner(hash, PLAYER) || IsDraw(hash);
}

//verifica se deu empate
int IsDraw(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    int line, column;

    for (line = 0; line < HASH_DIMENSION; line++)
        for (column = 0; column < HASH_DIMENSION; column++)
            if (hash[line][column] == EMPTY) return 0;

    return 1;
}

//retorna o n�mero de maneiras de vit�ria
int WinnigModes(int hash[HASH_DIMENSION][HASH_DIMENSION], int user)
{
    int line, column, positions, winnigModes = 0;

    //verificando as linhas
    for(line = 0; line < HASH_DIMENSION; line++)
    {
        positions = 0;
        for(column = 0; column < HASH_DIMENSION; column++)
            positions += (hash[line][column] == user) ? 1 : 0;

        if(positions == HASH_DIMENSION) winnigModes++;
    }

    //verificando as colunas
    for(column = 0; column < HASH_DIMENSION; column++)
    {
        positions = 0;
        for(line = 0; line < HASH_DIMENSION; line++)
            positions += (hash[line][column] == user) ? 1 : 0;

        if(positions == HASH_DIMENSION) winnigModes++;
    }

    //verificando a diagonal principal
    positions = 0;
    for(line = 0; line < HASH_DIMENSION; line++)
        positions += (hash[line][line] == user) ? 1 : 0;

    if(positions == HASH_DIMENSION) winnigModes++;

    //verificando a diagonal secund�ria
    positions = 0;
    for(line = 0; line < HASH_DIMENSION; line++)
        positions += (hash[line][HASH_DIMENSION - line - 1] == user) ? 1 : 0;

    if(positions == HASH_DIMENSION) winnigModes++;

    return winnigModes;
}

//verifica se o user venceu a partida
int IsWinner(int hash[HASH_DIMENSION][HASH_DIMENSION], int user)
{
    return (WinnigModes(hash, user) > 0) ? 1 : 0;
}

//verifica se o movimento � v�lido
int MovementIsValid(int hash[HASH_DIMENSION][HASH_DIMENSION], int cell[2])
{
    if(cell[X] < HASH_DIMENSION && cell[Y] < HASH_DIMENSION)
        if(hash[ cell[X] ][ cell[Y] ] == EMPTY)
            return 1;

    return 0;
}

//retorna uma posi��o
int *GetPosition(int line, int column)
{
    int *cell = (int *) malloc(2*sizeof(int));

    cell[X] = line;
    cell[Y] = column;

    return cell;
}

//retorna o centro do hash
int *CenterPosition(void)
{
    return GetPosition(HASH_DIMENSION / 2 + 1, HASH_DIMENSION / 2 + 1);
}

//verifica se o centro esta disponivel
int CenterIsAvailable(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return MovementIsValid(hash,CenterPosition());
}

//verifica se os cantos est�o dispon�veis
int CornerIsAvailable(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    int *cornerPosition;

    cornerPosition = RandomCorner(hash);

    return cornerPosition[X] != EMPTY && cornerPosition[Y] != EMPTY;
}

//retorna um canto qualquer
int *RandomCorner(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    if (MovementIsValid(hash,GetPosition(0,0))) return GetPosition(0,0);

    if (MovementIsValid(hash,GetPosition(HASH_DIMENSION-1,0))) return GetPosition(HASH_DIMENSION-1,0);

    if (MovementIsValid(hash,GetPosition(0,HASH_DIMENSION-1))) return GetPosition(0,HASH_DIMENSION-1);

    if (MovementIsValid(hash,GetPosition(HASH_DIMENSION-1,HASH_DIMENSION-1))) return GetPosition(HASH_DIMENSION-1,HASH_DIMENSION-1);

    return GetPosition(-1,-1);
}

//retorna uma posi��o qualquer
int *RandomPosition(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    int line, column;

    for(line = 0; line < HASH_DIMENSION; line++)
        for(column = 0; column < HASH_DIMENSION; column++)
            if (MovementIsValid(hash,GetPosition(line,column))) return GetPosition(line,column);
}

//retorna se � possivel vencer com o cen�rio corrente
int CanWin(int hash[HASH_DIMENSION][HASH_DIMENSION], int user)
{
    int *winningPosition;

    winningPosition = GetWinningPosition(hash, user);

    return winningPosition[X] != EMPTY && winningPosition[Y] != EMPTY;
}

//retorna o n�mero de maneiras que � possivel vencer
int *GetWinningPosition(int hash[HASH_DIMENSION][HASH_DIMENSION], int user)
{
    int line, column;
    int *cell = (int *) malloc(2*sizeof(int));
    int NewHash[HASH_DIMENSION][HASH_DIMENSION];

    CopyHash(hash, NewHash);

    //verificando as linhas
    for(line = 0; line < HASH_DIMENSION; line++)
        for(column = 0; column < HASH_DIMENSION; column++)
        {
            cell[X] = line;
            cell[Y] = column;

            if(MovementIsValid(hash,cell))
            {
                NewHash[line][column] = user;
                if(IsWinner(NewHash, user)) return cell;

                NewHash[line][column] = hash[line][column];
            }
        }

    cell[X] = EMPTY;
    cell[Y] = EMPTY;
    return cell;
}

//verifica se pode construir o triangulo
int CanBuildTriangle(int hash[HASH_DIMENSION][HASH_DIMENSION], int user)
{
    int *trianglePosition;

    trianglePosition = GetTrianglePosition(hash, user);

    return trianglePosition[X] != EMPTY && trianglePosition[Y] != EMPTY;
}

//retorna a posi��o para formar o triangulo
int *GetTrianglePosition(int hash[HASH_DIMENSION][HASH_DIMENSION], int user)
{
    int line, column;
    int *cell = (int *) malloc(2*sizeof(int));
    int NewHash[HASH_DIMENSION][HASH_DIMENSION];

    CopyHash(hash, NewHash);

    //verificando as linhas
    for(line = 0; line < HASH_DIMENSION; line++)
        for(column = 0; column < HASH_DIMENSION; column++)
        {
            cell[X] = line;
            cell[Y] = column;

            if(MovementIsValid(hash,cell))
            {
                NewHash[line][column] = user;
                if(WinnigModes(NewHash, user) > 1) return cell;

                NewHash[line][column] = hash[line][column];
            }
        }

    cell[X] = EMPTY;
    cell[Y] = EMPTY;
    return cell;
}

/*Fun��es do Jogador
----------------------------------------------------------------------------------*/
int PlayPlayer(int hash[HASH_DIMENSION][HASH_DIMENSION], ALLEGRO_EVENT_QUEUE **eventQueue, ALLEGRO_DISPLAY **display)
{
    int *cellClicked;

    //valida��o da posi��o escolhida
    cellClicked = GetCellCicked(eventQueue);
    while(!MovementIsValid(hash, cellClicked))
    {
        al_show_native_message_box(*display,"Movimento Inv�lido", "", "Movimento Inv�lido", "Ok",1);
        cellClicked = GetCellCicked(eventQueue);
    }

    hash[cellClicked[X]][cellClicked[Y]] = PLAYER;

    return COMPUTER;
}

//binda o clique do usuario
int *GetCellCicked(ALLEGRO_EVENT_QUEUE **eventQueue)
{
    int line, column;
    ALLEGRO_EVENT event;

    do al_wait_for_event(*eventQueue, &event); while(event.type != ALLEGRO_EVENT_MOUSE_BUTTON_UP);

    return GetPosition(event.mouse.x / CELL_DIMENSION, event.mouse.y / CELL_DIMENSION);
}

//verifica se o usuario pode vencer
int PlayerCanWin(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return CanWin(hash,PLAYER);
}

//verifica se o usuario pode construir um triangulo
int PlayerCanBuildTriangle(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return CanBuildTriangle(hash,PLAYER);
}

//retorna as posi��es de vit�ria
int *PlayerWinningPosition(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return GetWinningPosition(hash, PLAYER);
}

//retorna as posi��es de triangulo
int *PlayerTrianglePosition(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return GetTrianglePosition(hash, PLAYER);
}

/*Fun��es do Computador
----------------------------------------------------------------------------------*/
int PlayComputer(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    int *computerMovement;

    computerMovement = GetComputerMovement(hash);

    hash[computerMovement[X]][computerMovement[Y]] = COMPUTER;

    return PLAYER;
}

//gera o movimento da maquina
int *GetComputerMovement(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    //se puder vencer ven�a!
    if(ComputerCanWin(hash)) return ComputerWinningPosition(hash);

    //n�o permitir que o advers�rio ven�a!
    if(PlayerCanWin(hash)) return PlayerWinningPosition(hash);

    //tente montar um triangulo
    if(ComputerCanBuildTriangle(hash)) return ComputerTrianglePosition(hash);

    //bloqueie o triangulo do oponente
    if(PlayerCanBuildTriangle(hash)) return PlayerTrianglePosition(hash);

    //jogue no centro
    if(CenterIsAvailable(hash)) return CenterPosition();

    //jogue no canto
    if(CornerIsAvailable(hash)) return RandomCorner(hash);

    //jogue numa posi��o qualquer
    return RandomPosition(hash);
}

//verifica se a maquina pode vencer
int ComputerCanWin(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return CanWin(hash,COMPUTER);
}

//verifica se a maquina pdoe fazer um triangulo
int ComputerCanBuildTriangle(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return CanBuildTriangle(hash,COMPUTER);
}

//retorna as posi��es de vit�ria da maquina
int *ComputerWinningPosition(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return GetWinningPosition(hash, COMPUTER);
}

//retorna as posi��es de triangulo da maquina
int *ComputerTrianglePosition(int hash[HASH_DIMENSION][HASH_DIMENSION])
{
    return GetTrianglePosition(hash, COMPUTER);
}


/*Fun��es do Allegro
----------------------------------------------------------------------------------*/
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
int ImageStart()
{
    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar complemento image!\n");
        return 0;
    }

    return 1;
}

// inicializa��o do mouse
int MouseStart()
{
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar mouse!\n");
        return 0;
    }

    return 1;
}

// inicializa��o do display
int DisplayStart(ALLEGRO_DISPLAY **display)
{
    int windowHeight, windowWidth;

    windowWidth = CELL_DIMENSION * HASH_DIMENSION;
    windowHeight = CELL_DIMENSION * HASH_DIMENSION;

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
