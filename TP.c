//Eder Bragança Pereira
//Turma 31
//20.2.4011

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define ANSI_RESET            "\x1b[0m"
#define ANSI_BG_COLOR_WHITE   "\x1b[47m"
#define BG_WHITE(string)   ANSI_BG_COLOR_WHITE   string ANSI_RESET

//função para exibir mensagens padrão
void msg(int i);
//função para o menu inicial
int menu(char *gameState);
//função para liberar as matrizes
void liberaMatriz(char **matriz, int m);
//função para inicializar 1 jogador x cop
int singlePlayer();
//função para inicializar 2 jogadores
int twoPlayer();
//função para carregar o jogo
void loadGame();
//função para salvar o jogo
void saveGame(char **tabuleiro, int contador, char *jogador1, char *jogador2);
//função para criar o tabuleiro
char** criaTabuleiro();
//função para exibir o tabuleiro
void printTabuleiro(char **tabuleiro);
//função q verifica a possibilidade de comer
int podeComer(char **tabuleiro, int l2, int c2, int jogador);
//função onde acontece o jogo de 1 jogador
void jogoPvE(char* jogador1, char* jogador2, char **tabuleiro, int contador, int nmrPecasX, int nmrPecasO);
//função para fazer as jogadas do computador
void compJoga(char **tabuleiro, int *nmrPecasO);
//função onde acontece o jogo de 2 jogadores
void jogoPvP(char *jogador1, char *jogador2, char **tabuleiro, int contador, int nmrPecasX, int nmrPecasO);
//função para fazer as jogadas
int editaTabuleiro(int l1, int c1, int l2, int c2, char **tabuleiro, int jogador);
//função para a limpeza dos fgets
void limparCache();
int main(){
    char gameState[10];
    printf("\n                   ,---.             ___    ,---.        ,-,--.  ");
    printf("\n      _,..---._  .--.'  \\     .-._ .'=.'\\ .--.'  \\     ,-.'-  _\\  ");
    printf("\n    /==/,   -  \\ \\==\\-/\\ \\   /==/ \\|==|  |\\==\\-/\\ \\   /==/_ ,_.'  ");
    printf("\n    |==|   _   _\\/==/-|_\\ |  |==|,|  / - |/==/-|_\\ |  \\==\\  \\     ");
    printf("\n    |==|  .=.   |\\==\\,   - \\ |==|  \\/  , |\\==\\,   - \\  \\==\\ -\\    ");
    printf("\n    |==|,|   | -|/==/ -   ,| |==|- ,   _ |/==/ -   ,|  _\\==\\ ,\\   ");
    printf("\n    |==|  '='   /==/-  /\\ - \\|==| _ /\\   /==/-  /\\ - \\/==/\\/ _ |  ");
    printf("\n    |==|-,   _`/\\==\\ _.\\=\\.-'/==/  / / , |==\\ _.\\=\\.-'\\==\\ - , /  ");
    printf("\n    `-.`.____.'  `--`        `--`./  `--` `--`         `--`---'   ");
 
 
    printf("\n\n\n1- New game\n2- Load game\n\nDigite sua escolha(Digite sair em qualquer fase para encerrar o jogo): ");
    fgets(gameState, 9, stdin);
    gameState[strlen(gameState)-1] = '\0';

    menu(gameState);
    return 0;
}
int menu(char *gameState){
    char gameMode[10];
    if (strcmp(gameState, "1") == 0){
        printf("\n1- 1 jogador(Contra a maquina)\n2- 2 jogadores\n\nDigite uma opcao de jogo:");
        fgets(gameMode, 9, stdin);
        gameMode[strlen(gameMode)-1] = '\0';
            if (strcmp(gameMode, "1" ) == 0)
                singlePlayer();
            else if (strcmp(gameMode, "2" ) == 0)
                twoPlayer();
            else if (strcmp(gameMode, "sair" ) == 0)
                return 0;
            else{
                msg(1);
                menu(gameState);
            }
    }
    else if(strcmp(gameState, "2") == 0)
        loadGame();
    else if(strcmp(gameState, "sair") == 0)
        return 0;
    else{
        msg(1);
        main();
    }
    return 0;
}
int singlePlayer(){
    char jogador1[50], 
    jogador2[7] = {'m','y','s','e','l','f'},
    **tabuleiro = criaTabuleiro();

    printf("\nDigite seu nome: ");
    fgets(jogador1, 49, stdin);
    jogador1[strlen(jogador1) - 1] = '\0';
    if(strcmp("sair", jogador1) == 0)
        return 0;
    jogoPvE(jogador1, jogador2, tabuleiro, 1, 12, 12);

    liberaMatriz(tabuleiro, 8);
    return 0;
}
int twoPlayer(){
    char **tabuleiro = criaTabuleiro(),
    jogador1[50], jogador2[50];
    
    printf("Digite o nome do jogador 1: ");
    fgets(jogador1, 49, stdin);
    jogador1[strlen(jogador1) - 1] = '\0';
    if(strcmp("sair", jogador2) == 0)
        return 0;

    printf("Digite o nome do jogador 2: ");  
    fgets(jogador2, 49, stdin);
    jogador2[strlen(jogador2) - 1] = '\0';
    if(strcmp("sair", jogador2) == 0)
        return 0;    

    jogoPvP(jogador1, jogador2, tabuleiro, 1, 12, 12);
    
    liberaMatriz(tabuleiro, 8);
    return 0;
}
void loadGame(){
    char nomeArquivo[50], jogador1[50], jogador2[50],
    **tabuleiro = criaTabuleiro();
    int contador, nmrPecasX = 0, nmrPecasO = 0;

    printf("Digite o nome do arquivo:");
    fgets(nomeArquivo, 49, stdin);
    nomeArquivo[strlen(nomeArquivo) - 1] = '\0';

    FILE *abrirTxt = fopen(nomeArquivo, "r");
    fgets(jogador1, 49, abrirTxt);
    fgets(jogador2, 49, abrirTxt);

    jogador1[strlen(jogador1) - 1] = '\0';
    jogador2[strlen(jogador2) - 1] = '\0';
    printf("\nJogador 1: %s\nJogador 2: %s\n", jogador1, jogador2);
    for (int i = 7; i >= 0; i--)
    {
        for (int j = 0; j < 8; j++)
        { 
            fscanf(abrirTxt, " %c", &tabuleiro[i][j]);
            if(tabuleiro[i][j] == 'x' || tabuleiro[i][j] == 'X')
                nmrPecasX++;
            else if(tabuleiro[i][j] == 'o' || tabuleiro[i][j] == 'O')
                nmrPecasO++;
        }
    }
    fscanf(abrirTxt, "%d", &contador);
    fclose(abrirTxt); 
    if(strcmp("myself", jogador2) == 0)
        jogoPvE(jogador1, jogador2, tabuleiro, contador, nmrPecasX, nmrPecasO);
    else
        jogoPvP(jogador1, jogador2, tabuleiro, contador, nmrPecasX, nmrPecasO);
}
void saveGame(char **tabuleiro, int contador, char *jogador1, char *jogador2){
    char nomeArquivo[50];
    printf("Digite o nome do arquivo para salvar: ");
    fgets(nomeArquivo, 49, stdin);
    nomeArquivo[strlen(nomeArquivo) - 1] = '\0';

    FILE *salvarEstado = fopen(nomeArquivo, "w");

    fprintf(salvarEstado, "%s", jogador1);
    fprintf(salvarEstado, "\n%s", jogador2);
    for(int i = 7; i >= 0; i--){
        fprintf(salvarEstado, "\n");
        for(int j = 0; j < 8; j++){
            fprintf(salvarEstado, "%c", tabuleiro[i][j]);
        }   
    }
    fprintf(salvarEstado, "\n%d", contador);
    fclose(salvarEstado);
    printf("Arquivo salvo com sucesso em %s", nomeArquivo);
}
char** criaTabuleiro(){
    char **tabuleiro = malloc(8 * sizeof(char*));
    for (int i = 0; i < 8; i++)
        tabuleiro[i] = malloc(8 * sizeof(char));

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (i < 3 && (i + j) % 2 == 0)
                tabuleiro[i][j] = 'x';
            else if (i > 4 && (i + j) % 2 == 0)
                tabuleiro[i][j] = 'o';
            else 
                tabuleiro[i][j] = '-';
        }
    }
    return tabuleiro;
}
void jogoPvE(char* jogador1, char* jogador2, char **tabuleiro, int contador, int nmrPecasX, int nmrPecasO){
    char jogada[10];
    printTabuleiro(tabuleiro);
    
    do{
        printf("\n\n%s, sua jogada:", jogador1);
        fgets(jogada, 9, stdin);
            
        if (strcmp("salvar\n", jogada) == 0){
            saveGame(tabuleiro, contador, jogador1, jogador2);
            printf("\n%s, sua jogada:", jogador1);
            fgets(jogada, 9, stdin);
        }
        
        if(strlen(jogada) == 6){
            int jogadaConcluida = editaTabuleiro(jogada[0], jogada[1], jogada[3], jogada[4], tabuleiro, contador);
            printTabuleiro(tabuleiro);
            if(jogadaConcluida == 1){
                printf("\n\nVez do Computador: \n");
                compJoga(tabuleiro, &nmrPecasO);
                printTabuleiro(tabuleiro);
            }
            else if(jogadaConcluida == 2)
                    nmrPecasX--;
        }
        else if(strcmp("sair\n", jogada) != 0)
            msg(2);
    }while (strcmp("sair\n", jogada) != 0 && nmrPecasX != 0 && nmrPecasO != 0);
    if (nmrPecasX == 0)
        printf("\nGG %s, voce ganhou!", jogador1);
    else if(nmrPecasO == 0)
        printf("\nNao foi dessa vez %s, voce perdeu!", jogador2);
}
void compJoga(char **tabuleiro, int *nmrPecasO){
    int l1, l2, c1, c2;
    //numeros rand
    srand(time(NULL));    
    
    //computador se move 
    for(int i = 0; i < 1;){
        l1 = rand() % 7;
        c1 = rand() % 7;
        
        if (tabuleiro[l1][c1] == 'x'|| tabuleiro[l1][c1] == 'X'){
            if ((tabuleiro[l1+1][c1-1] == '-' || tabuleiro[l1+1][c1+1] == '-' ))
               i++;
        }
    }
    for(int i = 0; i < 1;){
        l2 = rand() % 7;
        c2 = rand() % 7;
        
        if ((l2 == (l1 + 1) && (c2 == (c1 + 1) || c2 == (c1 - 1)) && tabuleiro[l2][c2] == '-'))
            i++;
        else if((l2 == (l1 + 2)|| l2 == l1 - 2) && (c2 == (c1 + 2) || c2 == (c1 - 2)) && tabuleiro[l2][c2] == '-' &&(tabuleiro[l1+1][c1+1] == 'o' || tabuleiro[l1+1][c1+1] == 'O' || tabuleiro[l1+1][c1-1] == 'o' || tabuleiro[l1+1][c1-1] == 'O' || tabuleiro[l1-1][c1+1] == 'o' || tabuleiro[l1-1][c1+1] == 'O' || tabuleiro[l1-1][c1-1] == 'o' || tabuleiro[l1-1][c1-1] == 'O'))
            i++;
    }
    int jogadaConcluida = editaTabuleiro(l1, c1, l2, c2, tabuleiro, 2);
    if(jogadaConcluida == 2)
        nmrPecasO--;
}
void jogoPvP(char* jogador1, char* jogador2, char **tabuleiro, int contador, int nmrPecasX, int nmrPecasO){
    char jogada[10];
    printTabuleiro(tabuleiro);
    do{
        if(contador == 1){
            printf("\n\n%s, sua jogada:", jogador1);
            fgets(jogada, 9, stdin);
            
            if (strcmp("salvar\n", jogada) == 0){
                saveGame(tabuleiro, contador, jogador1, jogador2);
                printf("\n%s, sua jogada:", jogador1);
                fgets(jogada, 9, stdin);
            }

            if(strlen(jogada) == 6){
                    int jogadaConcluida = editaTabuleiro(jogada[0], jogada[1], jogada[3], jogada[4], tabuleiro, contador);
                    printTabuleiro(tabuleiro);
                    if(jogadaConcluida == 1)
                        contador++;
                    else if(jogadaConcluida == 2)
                        nmrPecasX--;
            }
            else if(strcmp("sair\n", jogada) != 0)
                msg(2);
        }
        else{
            printf("\n\n%s, sua jogada:", jogador2);
            fgets(jogada, 9, stdin);

            if(strcmp("salvar\n", jogada) == 0){
                saveGame(tabuleiro, contador, jogador1, jogador2);
                printf("\n%s, sua jogada:", jogador1);
                fgets(jogada, 9, stdin);
            }
            if(strlen(jogada) == 6){
                int jogadaConcluida = editaTabuleiro(jogada[0], jogada[1], jogada[3], jogada[4], tabuleiro, contador);
                printTabuleiro(tabuleiro);
                if (jogadaConcluida == 1)
                    contador--;
                else if(jogadaConcluida == 2)
                    nmrPecasO--;
            }
            else if(strcmp("sair\n", jogada) != 0)
                msg(2);
        }    
    }while (strcmp("sair\n", jogada) != 0 && nmrPecasX != 0 && nmrPecasO != 0);
    if (nmrPecasX == 0)
        printf("\nGG %s, voce ganhou", jogador1);
    else if(nmrPecasO == 0)
        printf("\nGG %s, voce ganhou", jogador2);
}
int editaTabuleiro(int l1, int c1, int l2, int c2, char **tabuleiro, int jogador){ 
    int contador = 0;    
    //substituindo as letras por numeros
    for (int i = 72; i >= 65; i--){   
        if(l1 == i)
            l1 = contador;  
        else if(l2 == i)
            l2 = contador;
        contador++;
    }
    for (int i = 49; i <= 56; i++){   
        if(c1 == i){
            c1 = i - 49;  
        }
        else if(c2 == i)
            c2 = i - 49;
    }
    //regras do tabuleiro
    if(c1 < 8 && c2 < 8 && l1 < 8 && l2 < 8 && (l1 + c1) % 2 == 0 && (l2 + c2) % 2 == 0 && tabuleiro[l2][c2] == '-'){
        //desenvolvendo função de jogada
        if (jogador == 2){
            //movimento normal
            if (tabuleiro[l1][c1] == 'x')
            {   
                int pComerl1 = podeComer(tabuleiro, l1, c1, jogador);
                if((l1 - l2 == 1 || l2 - l1 == 1) && (c1 - c2 == 1|| c2 - c1 == 1) && l2 > l1){
                        if(pComerl1 == 1){
                            msg(3);
                            return 0;
                        }
                        else{
                            tabuleiro[l2][c2] = 'x';
                            if (l2 == 7){
                                tabuleiro[l2][c2] = 'X';
                                msg(4);
                            }
                            tabuleiro[l1][c1] = '-';
                            return 1;
                        }
                }
                else if((l1 - l2 == 2 || l2 - l1 == 2) && (c1 - c2 == 2|| c2 - c1 == 2)){
                    int pComer = podeComer(tabuleiro, l2, c2, jogador);
                    //regras pra comer as peças
                    //come p frente e pra esquerda
                    if (c1 < c2 && (tabuleiro[l2-1][c2-1] == 'o' || tabuleiro[l2-1][c2-1] == 'O'))
                    {
                        tabuleiro[l2][c2] = 'x';
                        if (l2 == 7){
                            tabuleiro[l2][c2] = 'X';
                            msg(4);
                        }
                        tabuleiro[l2-1][c2-1] = '-';
                        tabuleiro[l1][c1] = '-';
                        if(pComer == 1)
                            return 2;
                        else if (pComer == 0)
                            return 1;
                    }
                    //come p frente e pra direita
                    else if (c1 > c2 && (tabuleiro[l2-1][c2+1] == 'o' || tabuleiro[l2-1][c2+1] == 'O'))
                    {
                        tabuleiro[l2][c2] = 'x';
                        if (l2 == 7){
                            tabuleiro[l2][c2] = 'X';
                            msg(4);
                        }
                        tabuleiro[l2-1][c2+1] = '-';
                        tabuleiro[l1][c1] = '-';
                        if(pComer == 1)
                            return 2;
                        else if (pComer == 0)
                            return 1;
                    }
                    //come p tras e pra esquerda
                    else if (c1 < c2 && (tabuleiro[l2+1][c2-1] == 'o' || tabuleiro[l2+1][c2-1] == 'O'))
                    {
                        tabuleiro[l2][c2] = 'x';
                        if (l2 == 7){
                            tabuleiro[l2][c2] = 'X';
                            msg(4);
                        }
                        tabuleiro[l2+1][c2-1] = '-';
                        tabuleiro[l1][c1] = '-';
                        if(pComer == 1)
                            return 2;
                        else if (pComer == 0)
                            return 1;
                    }
                    //come p tras e pra direita
                    else if (c1 > c2 && (tabuleiro[l2+1][c2+1] == 'o' || tabuleiro[l2+1][c2+1] == 'O'))
                    {
                        tabuleiro[l2][c2] = 'x';
                        if (l2 == 7){
                            tabuleiro[l2][c2] = 'X';
                            msg(4);
                        }
                        tabuleiro[l2+1][c2+1] = '-';
                        tabuleiro[l1][c1] = '-';
                        if(pComer == 1)
                            return 2;
                        else if (pComer == 0)
                            return 1;
                    }
                    else{
                        msg(2);
                        return 0;
                    }
                }
                else{
                    msg(2);
                    return 0;
                }
            }
            else if(tabuleiro[l1][c1] == 'X'){
                int dist = l2-l1, caminho = 0, comida = 0;
                int ll, cc,
                pComer = podeComer(tabuleiro, l2, c2, contador);
                if(dist > 0){
                    if(c2 < c1){
                        for(int i = 1; i <= dist; i++){
                            if(tabuleiro[l1+i][c1-i] == '-')
                                caminho++;
                            else if(tabuleiro[l1+i][c1-i] == 'o'|| tabuleiro[l1+i][c1-i] == 'O'){
                                comida++;
                                ll = l1+i;
                                cc = c1-i;
                            }
                            else{
                                msg(2);
                                return 0;
                            }
                        }
                    }
                    else{
                        for(int i = 1; i <= dist; i++){
                            if(tabuleiro[l1+i][c1+i] == '-')
                                caminho++;
                            else if(tabuleiro[l1+i][c1+i] == 'o'|| tabuleiro[l1+i][c1+i] == 'O'){
                                comida++;
                                ll = l1+i;
                                cc = c1+i;
                            }
                            else{
                                msg(2);
                                return 0;
                            }
                        }
                    }
                }
                else if(dist < 0){
                    if (c2 > c1){
                        for(int i = -1; i >= dist; i--){
                            if(tabuleiro[l1+i][c1-i] == '-')
                                caminho++;
                            else if(tabuleiro[l1+i][c1-i] == 'o'|| tabuleiro[l1+i][c1-i] == 'O'){
                                comida++;
                                ll = l1+i;
                                cc = c1-i;
                            }
                            else{
                                msg(2);
                                return 0;
                            }
                        }
                    }
                    else{
                        for(int i = -1; i >= dist; i--){
                            if(tabuleiro[l1+i][c1+i] == '-')
                                caminho++;
                            else if(tabuleiro[l1+i][c1+i] == 'o'|| tabuleiro[l1+i][c1+i] == 'O'){
                                comida++;
                                ll = l1+i;
                                cc = c1+i;
                            }
                            else{
                                msg(2);
                                return 0;
                            }
                        }
                    }
                }    
                else{
                        msg(2);
                        return 0;
                }
                if (caminho == -dist || caminho == dist)
                {
                    tabuleiro[l2][c2] = 'X';
                    tabuleiro[l1][c1] = '-';
                    return 1;
                }
                else if (comida == 1)
                {
                    tabuleiro[l2][c2] = 'X';
                    tabuleiro[ll][cc] = '-';
                    tabuleiro[l1][c1] = '-';
                    if(pComer == 1)
                            return 2;
                    else if (pComer == 0)
                            return 1;
                }
                else{
                    msg(2);
                    return 0;
                }
            }
            else{
                msg(2);
                return 0;
            }
        }
        else if (jogador == 1){
            if (tabuleiro[l1][c1] == 'o')
            {
                int pComerl1 = podeComer(tabuleiro, l1, c1, jogador);
                if((l1 - l2 == 1 || l2 - l1 == 1) && (c1 - c2 == 1|| c2 - c1 == 1) && l2 < l1){                          
                        if(pComerl1 == 1){
                            msg(3);
                            return 0;
                        }
                        else{
                            tabuleiro[l2][c2] = 'o';
                            if (l2 == 0){
                                tabuleiro[l2][c2] = 'O';
                                msg(4);
                            }
                            tabuleiro[l1][c1] = '-';
                            return 1;
                        }
                }
                else if((l1 - l2 == 2 || l2 - l1 == 2) && (c1 - c2 == 2|| c2 - c1 == 2)){
                    int pComer = podeComer(tabuleiro, l2, c2, jogador);
                    //regras pra comer as peças
                    //come p frente e pra esquerda
                    if (c1 > c2 && (tabuleiro[l2+1][c2+1] == 'x' || tabuleiro[l2+1][c2+1] == 'X')){
                        tabuleiro[l2][c2] = 'o';
                        if(l2 == 0){
                            tabuleiro[l2][c2] = 'O';
                            msg(4);
                        }
                        tabuleiro[l2+1][c2+1] = '-';
                        tabuleiro[l1][c1] = '-';
                        if(pComer == 1)
                            return 2;
                        else if (pComer == 0)
                            return 1;
                    }
                    //come p frente e pra direita
                    else if (c1 < c2 && (tabuleiro[l2+1][c2-1] == 'x' || tabuleiro[l2+1][c2-1] == 'X')){
                        tabuleiro[l2][c2] = 'o';
                        if(l2 == 0){
                            tabuleiro[l2][c2] = 'O';
                            msg(4);
                        }
                        tabuleiro[l2+1][c2-1] = '-';
                        tabuleiro[l1][c1] = '-';
                        if(pComer == 1)
                            return 2;
                        else if (pComer == 0)
                            return 1;
                    }
                    //come p tras e pra esquerda
                    else if (c1 > c2 && (tabuleiro[l2-1][c2+1] == 'x' || tabuleiro[l2-1][c2+1] == 'X')){
                        tabuleiro[l2][c2] = 'o';
                        if(l2 == 0){
                            tabuleiro[l2][c2] = 'O';
                            msg(4);
                        }
                        tabuleiro[l2-1][c2+1] = '-';
                        tabuleiro[l1][c1] = '-';
                        if(pComer == 1)
                            return 2;
                        else if (pComer == 0)
                            return 1;
                    }
                    //come p tras e pra direita
                    else if (c1 < c2 && (tabuleiro[l2-1][c2-1] == 'x' || tabuleiro[l2-1][c2-1] == 'X'))
                    {
                        tabuleiro[l2][c2] = 'o';
                        if(l2 == 0){
                            tabuleiro[l2][c2] = 'O';
                            msg(4);
                        }
                        tabuleiro[l2-1][c2-1] = '-';
                        tabuleiro[l1][c1] = '-';
                        if(pComer == 1)
                            return 2;
                        else if (pComer == 0)
                            return 1;
                    }
                    else{
                        msg(2);
                        return 0;
                    }
                }
                else{
                    msg(2);
                    return 0;
                }
            }
            else if(tabuleiro[l1][c1] == 'O')
            {
                int dist = l2-l1, caminho = 0, comida = 0;
                int ll, cc,
                pComer = podeComer(tabuleiro, l2, c2, contador);
                //p cima
                if(dist > 0){
                    if(c2 > c1){
                        for(int i = 1; i <= dist; i++){
                            if(tabuleiro[l1+i][c1+i] == '-')
                                caminho++;
                            else if(tabuleiro[l1+i][c1+i] == 'x'|| tabuleiro[l1+i][c1+i] == 'X'){
                                comida++;
                                ll = l1+i;
                                cc = c1-i;
                            }
                            else{
                                msg(2);
                                return 0;
                            }
                        }
                    }
                    else{
                        for(int i = 1; i <= dist; i++){
                            if(tabuleiro[l1+i][c1-i] == '-')
                                caminho++;
                            else if(tabuleiro[l1+i][c1-i] == 'x'|| tabuleiro[l1+i][c1-i] == 'X'){
                                comida++;
                                ll = l1+i;
                                cc = c1-i;
                            }
                            else{
                                msg(2);
                                return 0;
                            }
                        }
                    }
                }
                else if(dist < 0){
                    if(c2 < c1){
                        for(int i = -1; i >= dist; i--){
                            if(tabuleiro[l1+i][c1+i] == '-')
                                caminho++;
                            else if(tabuleiro[l1+i][c1+i] == 'x'|| tabuleiro[l1+i][c1+i] == 'X'){
                                comida++;
                                ll = l1+i;
                                cc = c1-i;
                            }
                            else{
                                msg(2);
                                return 0;
                            }
                        }
                    }
                    else{
                        for(int i = -1; i >= dist; i--){
                            if(tabuleiro[l1+i][c1-i] == '-')
                                caminho++;
                            else if(tabuleiro[l1+i][c1-i] == 'x'|| tabuleiro[l1+i][c1-i] == 'X'){
                                comida++;
                                ll = l1+i;
                                cc = c1-i;
                            }
                            else{
                                msg(2);
                                return 0;
                            }
                        }
                    }
                }    
                else{
                    msg(2);
                    return 0;
                }
                if (caminho == dist || caminho == -dist)
                {
                    tabuleiro[l2][c2] = 'O';
                    tabuleiro[l1][c1] = '-';
                    return 1;
                }
                if (comida == 1)
                {
                    tabuleiro[l2][c2] = 'O';
                    tabuleiro[ll][cc] = '-';
                    tabuleiro[l1][c1] = '-';
                    if(pComer == 1)
                            return 2;
                    else if (pComer == 0)
                            return 1;
                }
                else{
                    msg(2);
                    return 0;
                }
            }
            else{
                msg(2);
                return 0;
            }
        }
    }    
    else{
        msg(2);
        return 0;
    }
    return 0;
}
int podeComer(char **tabuleiro, int l2,  int c2, int jogador){
    if(jogador == 1 && (((tabuleiro[l2-1][c2-1] == 'x' || tabuleiro[l2-1][c2-1] == 'X') && tabuleiro[l2-2][c2-2] == '-') || ((tabuleiro[l2-1][c2+1] == 'x' || tabuleiro[l2-1][c2+1] == 'X') && tabuleiro[l2-2][c2+2] == '-') || ((tabuleiro[l2+1][c2-1] == 'x'|| tabuleiro[l2+1][c2-1] == 'X') && tabuleiro[l2+2][c2-2] == '-') || ((tabuleiro[l2+1][c2+1] == 'x'|| tabuleiro[l2+1][c2+1] == 'X') && tabuleiro[l2+2][c2+2]== '-')))
        return 1;
    else if(jogador == 2 && (((tabuleiro[l2-1][c2-1] == 'o'||tabuleiro[l2-1][c2-1] == 'O') && tabuleiro[l2-2][c2-2] == '-') || ((tabuleiro[l2-1][c2+1] == 'o' || tabuleiro[l2-1][c2+1] == 'O') && tabuleiro[l2-2][c2+2] == '-') || ((tabuleiro[l2+1][c2-1] == 'o'||tabuleiro[l2+1][c2-1] == 'o') && tabuleiro[l2+2][c2-2] == '-') || ((tabuleiro[l2+1][c2+1] == 'o'||tabuleiro[l2+1][c2-1] == 'O') && tabuleiro[l2+2][c2+2]== '-')))
        return 1;
    else   
        return 0;
}
void printTabuleiro(char **tabuleiro){
    int contador = 1, contador2 = 1;
    printf("   ");
    while(contador <= 8){
        printf(" %d ", contador);
        contador++;
    }
    printf("\n");
    for (int i = 0; i < 8; i++){
        printf("%c |", 72 - i);
        for (int j = 0; j < 8; j++){
            if ((i + j) % 2 != 0){
                printf(BG_WHITE(" - "));
            }
            else
                printf(" %c ", tabuleiro[i][j]);
        } 
        printf("| %c\n", 72 - i);
    }
    printf("   ");
    while(contador2 <= 8){
        printf(" %d ", contador2);
        contador2++;
    }
}
void liberaMatriz(char** mat, int m){
    for (int i = 0; i < m; i++)
       free(mat[i]);
    free(mat); 
}
void limparCache() {
    int ch;
    do {
        ch = fgetc(stdin);
    } while (ch != EOF && ch != '\n');
}
void msg(int i){
    switch (i)
    {
    case 1:
        printf("\nOpção Invalida\n");
        break;
    case 2:
        printf("\nJogada Invalida\n");
        break;
    case 3:
        printf("\nVoce eh obrigado a comer");
        break;
    case 4:
        printf("\nParabens, voce conseguiu uma dama\n");
        break;
    default:
        break;
    }
}