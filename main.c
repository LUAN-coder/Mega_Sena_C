
/****************************************************************************************************************************************************/
/**  Desenvolvedor / Developer: Luan Vinicius Arruda da Silva                                                                                       */
/**  email: luanviniciusarruda@gmail.com                                                                                                            */
/**                                                                                                                                                 */
/**  Objetivo do código / Purpose of code:                                                                                                          */
/**                                                                                                                                                 */
/**                            - Criar 'N' jogos da Mega-sena com 'M' dezenas.  /  Create 'N' games from the Mega-Sena with 'M' scores.             */
/**                                                                                                                                                 */
/**                            - A quantidade N de jogos tem que ser 0 < N <= 20. /  The 'N' number of games must be 0 <N <= 20.                    */
/**                                                                                                                                                 */
/**                            - O usuário pode escolher a quantidade de dezenas que cada jogo vai ter; Entre 6 e 15 dezenas.                       */
/**                               /The user can choose the number of tens that each game will have; Between 6 and 15 dozen.                         */
/**                                                                                                                                                 */
/**                            - Os jogos não terão dezenas repetidas.   /   The games will not have dozens repeated.                               */
/**                                                                                                                                                 */
/**                            - O resultado dos jogos serão mostrados na tela.     /    The result of the games will be shown on the screen.       */
/**                                                                                                                                                 */
/**                            - Um arquivo .txt será criado e nele estará contido os últimos jogos feitos.                                         */
/**                              /A '.txt' file will be created and it will contain the latest games made.                                          */
/**                                                                                                                                                 */
/**                            - o nome do arquivo é 'Ultimos_jogos.txt', e estará guardado na mesma pasta deste código.                            */
/**                              /the file name is 'Ultimos_jogos.txt', and will be saved in the same folder as this code.                          */
/**                                                                                                                                                 */
/**  Desenvolvido entre os dias 21 e 23 de abril de 2021                                                                                            */
/**                                                                                                                                                 */
/** Obs: este projeto foi desenvolvido utilizando o software Codeblocks e em um sistema operacional linux.                                          */
/**         this project was developed using Codeblocks software and a linux operating system.                                                      */
/****************************************************************************************************************************************************/

/***************************  Bibliotecas / Libraries ***********************************/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

/***************************  Funções / Functions ***************************************/

/*-------------------------------------------------------------------------------------------------------------------------*/
//  Alocar_matriz_jogos:    o objetivo dessa função é alocar espaço dinâmico para guardar os jogos que o programa vai criar.
//                          tem como entrada a quantidade de jogos "m", e um vetor "n", que contem a quantidade de dezenas que
//                          cada jogo "m" vai ter, e retorna o ponteiro desse espaço alocado.
//                          Exemplo:
//                                              m = 3 -----> significa que vai três jogos
//                                              n[6,8,12] -> o 1° jogo vai ter 6 dezenas
//                                                           o 2° jogo vai ter 8 dezenas
//                                                           o 3° jogo vai ter 12 dezenas
//
//                          the purpose of this function is to allocate dynamic space to store the games that the program will create.
//                          has as input the number of games "m", and a vector "n", which contains the number of tens that
//                          each game "m" is going to have, and returns the pointer of that allocated space.
//                          Example:
//                                              m = 3 -----> means that three games are going
//                                              n[6,8,12] -> the 1st game will have 6 dozens
//                                                           the 2nd game will have 8 dozens
//                                                           the 3rd game will have 12 dozen
/*-------------------------------------------------------------------------------------------------------------------------*/
int **Alocar_matriz_jogos(int m, int *n){  //


  int **M;                                  // ponteiro para a matriz de inteiros               // pointer to the array of integers
  int i;                                    // variável auxiliar para manipulação da matriz     // auxiliary variable for matrix manipulation

                                            // início da alocação                               // start of allocation

  M = (int **)malloc(m*sizeof(int*));       // a função malloc é utilizada para criar primeiro, as linhas da matriz, que irão conter cada uma um vetor dinâmico de inteiros
                                            // the malloc function is used to first create the matrix lines, which will each contain a dynamic vector of integers


  if(M == NULL){                            //condição para verificar se ha espaço suficiente, caso não houver uma mensagem de erro é impressa na tela, e o programa é finalizado.
    printf("Memoria insuficiente.\n");      // condition to check if there is enough space, if there is not an error message is printed on the screen, and the program is terminated.
    exit(1);
  }

  // aloca as colunas da matriz,  onde  irá ficar as dezenas dos jogos              // allocate the columns of the matrix, where the dozens of games will be


  for(i = 0; i < m; i++){                   // processo de repetição para criar colunas dinâmicas, de acordo com a quantidade de dezenas de cada jogo
                                            // repetition process to create dynamic columns, according to the number of tens of each game

    M[i] = (int*)malloc(n[i]*sizeof(int));  // m vetores de n[i] inteiros           // m vectors of n [i] integers

    if(M[i] == NULL){                       //condição para verificar se ha espaço suficiente, caso não houver uma mensagem de erro é impressa na tela, e o programa é finalizado.
      printf("Memoria insuficiente.\n");    //condition to check if there is enough space, if there is not an error message is printed on the screen, and the program is terminated.
      exit(1);
    }
  }
  return M;                                 // retorna o ponteiro da matriz         // returns the array pointer
}

/*-------------------------------------------------------------------------------------------------------------------------*/
//  Libera_Matriz_jogos:    o objetivo dessa função é liberar o espaço alocado, que a função "Alocar_matriz_jogos", precisou
//                          criar. Tem como parâmetros de entrada a Matriz de inteiros 'M', e o número de jogos = m.
//
//                          the purpose of this function is to free up the allocated space, which the function "Allocate_matrix_games", needed
//                          to create. The input parameters are the Matrix of integers 'M', and the number of games = m.
/*-------------------------------------------------------------------------------------------------------------------------*/


void Libera_Matriz_jogos(int **M, int m){

  int i;                                    // variável auxiliar para manipulação da matriz         // auxiliary variable for matrix manipulation

  for(i = 0; i < m; i++){                   // processo de repetição, enquanto não chegar ao final do número de linhas, o espaço vai sendo liberado
                                            // repetition process, until the end of the number of lines is reached, the space will be freed

    free(M[i]);                             // libera o espaço da linha 'i'                 // frees space from the 'i' line

  }
  free(M);                                  // libera o ponteiro da matriz M                // release the pointer of the matrix M
}

/*-------------------------------------------------------------------------------------------------------------------------*/
//  Arquivar_jogo:    O objetivo dessa função é criar um arquivo 'txt', para  guardar os jogos que foram criados. o mome do
//                    é sempre 'Ultimos_jogos.txt', cada linha do arquivo é um jogo diferente, e no final do arquivo tem
//                    a informação dia, hora e data em que foi criado. Toda vez que novos jogos forem armazenados os antigos
//                    serão apagados. Tem como parâmetros de entrada, uma matriz de inteiros 'M', a quantidade de jogos 'm',
//                    e um vetor de inteiros 'n', que contem a quantidade dezenas que cada jogo tem, similar a como foi
//                    explicado na função Alocar_matriz_jogos.
//
//
//                    The purpose of this function is to create a 'txt' file, to store the games that have been created. the name of
//                    it's always 'Ultimos_jogos.txt', each line of the file is a different game, and at the end of the file there is
//                    the day, time and date information on which it was created. Every time new games are stored the old ones
//                    will be deleted. It has as input parameters, an array of integers 'M', the number of games 'm',
//                    and a vector of integers 'n', which contains the number of tens that each game has, similar to how it was
//                    explained in the function Allocate_matrix_games.
//-------------------------------------------------------------------------------------------------------------------------*/

void Arquivar_jogo(int **M, int m, int *n){
    int i,j;                                  // variável auxiliar para manipulação da matriz           // auxiliary variable for matrix manipulation
    time_t now;                               // variável para armazenar a data e hora                  // variable to store the date and time
    time(&now);

    printf("\n\n");
    printf("O jogo será arquivado com o nome 'Ultimos_jogos.txt',\n na mesma pasta onde está esse código.");

        FILE *arquivo;                        // variável para manipulação de arquivo                   // variable for file manipulation

         arquivo = fopen("Ultimos_jogos.txt", "w+");        //abertura ou criação de arquivo            // opening or creating a file

        if(arquivo == NULL){                                 //condição para verificar se a abertura do arquivo foi correta, caso não seja, o código é finalizado
                                                             // condition to check if the file was opened correctly, if not, the code is finalized
                printf("Erro na abertura do arquivo!");
                return 1;
            }

            for(i=0;i<m;i++){                               //início do processo de repetição passando pelas linhas     // start of the repetition process passing through the lines

                    for(j=0;j<n[i];j++){                    // e aqui pelas colunas                         // and here by the columns

                            if(M[i][j]<10){                 // condição para verificar se o numero é 10, e depois arquivar com um 0 na frente e ficar mais legível
                                                            // condition to check if the number is 10, and then file it with a 0 in front and make it more readable

                                    putc(0+'0', arquivo);           //é escrito o caractere 0 no arquivo                    // character 0 is written to the file
                                    putc(M[i][j]+'0',arquivo);      //é escrito o número do jogo que está sendo analisado   // the number of the game being analyzed is written
                                    putc(' ',arquivo);              //é escrito um espaço em branco no arquivo              // a blank space is written in the file

                            }else{                          //caso contrário se o arquivo for maior que 10                  // otherwise if the file is greater than 10
                                    putc((M[i][j]/10)+'0',arquivo); //é escrito o primeiro caractere do número no arquivo   // the first character of the number is written to the file
                                    putc((M[i][j]%10)+'0',arquivo); //é escrito o segundo caractere  do número no arquivo   // the second character of the number is written to the file
                                    putc(' ',arquivo);              //é escrito um espaço em branco no arquivo              // a blank space is written in the file
                            }
                    }

                    putc('\n',arquivo);                     //é escrito no arquivo '\n' que inicia a escrita do arquivo em uma nova linha
            }                                               //is written to the file '\ n' which starts writing the file on a new line
            putc('\n',arquivo);
            fwrite("  Criado em: ", sizeof(char), 13, arquivo);                 // Escreve "  Criado em: " no arquivo       // Write "Created on:" in the file
            fwrite(ctime(&now), sizeof(char), strlen(ctime(&now)), arquivo);    // Escreve a data e hora no  arquivo        // Writes the date and time to the file
            fclose(arquivo);                                                    // fechar o arquivo                          // fechar o arquivo
            printf("\n\n");
            printf("Jogos arquivados com sucesso!!!");
            printf("\n\n");
}


/********************  Início do código principal / Start of main code  *********************************/

int main(){

/********************  variáveis / variables ***********************************************************/

    int numero_de_dezenas;                          //variável que armazena o número de dezenas                 // variable that stores the number of tens
    int numero_de_jogos;                            //variável que armazena o número de jogos                   // variable that stores the number of games
    int aux=0;                                      //variável auxiliar                                         // auxiliary variable
    int aux2;                                       //variável auxiliar 2                                       // auxiliary variable 2
    int i,j;                                        //variável auxiliar para manipulação da matriz              // auxiliary variable for matrix manipulation
    int escolha;                                    //variável usada no processo do número de dezenas           // variable used in the process of the number of tens
    int *dezenas_de_cada_jogo;                      //vetor de inteiros alocados dinamicamente para guarda o número de dezenas que cada jogo vai ter            // vector of integers dynamically allocated to store the number of tens that each game will have
    int **Jogos;                                    //Matriz de inteiro alocados dinamicamente para guardar os jogos que serão criados                          // Integer matrix dynamically allocated to store the games that will be created


    printf("*************************************************\n");
    printf("*****   Gerador de jogos para Mega-sena  ********\n");      //tela de boas vindas                   // welcome screen
    printf("*************************************************\n");
    printf("\n");
    printf("\n");

    printf(" Bem vindo!\n\n");

        do{                                         //início de um processo de repetição, que só ocorrerá de o usuário digitar o dado de entrada erroneamente
                                                    // start of a repetition process, which will only occur if the user enters the input data incorrectly

                printf(" Digite quantos jogos quer fazer, não passando de 20:");

                                                    //inserção do número de jogos    //insert number of games

                if (scanf("%d", &numero_de_jogos) != 1){        // condição para verificar se o que está sendo lido é realmente um inteiro, se não for o buffer será apagado
                                                                // condition to check if what is being read is really an integer, if not the buffer will be cleared

                    fflush(stdin);                              // função para limpar o buffer em Windows               // function to clear the buffer in Windows
                    __fpurge(stdin);                            // função para limpar o buffer em linux                 // function to clear the buffer in linux
                    numero_de_jogos = 0;                        // coloca zero, e o processo  será repetido             // set zero, and the process will be repeated


                }

        }while(numero_de_jogos<1 || numero_de_jogos>20);        //enquanto o número de jogos for menor que 1 ou maior que 20 repete o pedido
                                                                // as long as the number of games is less than 1 or greater than 20 repeat the request
        printf("\n\n");
        printf("Você deseja fazer %d jogos!\n", numero_de_jogos );
        printf("\n\n");

        do{                                                     //outro processo de repetição, para saber do usuário se os  jogos terão a mesma quantidade de dezenas ou não
                                                                // another repetition process, to know from the user if the games will have the same amount of tens or not
                printf("Escolha uma das opções abaixo:\n");
                printf("        1 - Os jogos terão a mesma quantidade de dezenas.\n");
                printf("        2 - Cada jogo tera sua quantidade de dezenas diferente.\n\n");
                printf("Digite 1 ou 2:");

                //inserção da decisão de como sera a quantidade de dezenas          // insertion of the decision on how the quantity of tens will be

                if (scanf("%d", &escolha) != 1){                // condição para verificar se o que está sendo lido realmente um inteiro, se não for o buffer será apagado
                                                                // condition to check if what is being read is really an integer, if not the buffer will be cleared

                    fflush(stdin);                              // função para limpar o buffer em Windows               // function to clear the buffer in Windows
                    __fpurge(stdin);                            // função para limpar o buffer em linux                 // function to clear the buffer in linux
                    escolha = 0;                                // coloca zero, e o processo  será repetido             // set zero, and the process will be repeated

                }

        }while(escolha<1 || escolha>2);                         //enquanto a escolha for diferente de 1 ou 2 repete o pedido
                                                                // as long as the choice is different from 1 or 2 repeat the order
        printf("\n\n");

        if(escolha == 1){                                       //se o usuário decidiu que os jogos terão as mesmas quantidade de dezenas tera agora que dizer qual a quantidade de dezenas vai querer para seus jogos
                                                                // if the user has decided that the games will have the same amount of tens, he will now have to say what number of tens he will want for his games
            do{
                printf("Por favor, digite a quantidade de dezenas que deseja ter em seus jogos:");

                //inserção da quantidade de dezenas             // insertion of the amount of tens

                if (scanf("%d", &numero_de_dezenas) != 1){      // condição para verificar se o que está sendo lido realmente um inteiro, se não for o buffer será apagado
                                                                // condition to check if what is being read is really an integer, if not the buffer will be cleared

                    fflush(stdin);                              // função para limpar o buffer em Windows               // function to clear the buffer in Windows
                    __fpurge(stdin);                            // função para limpar o buffer em linux                 // function to clear the buffer in linux
                    numero_de_dezenas = 0;                      // coloca zero, e o processo  será repetido             // set zero, and the process will be repeated


                }

            }while(numero_de_dezenas<6 || numero_de_dezenas>15);              //enquanto o número de dezenas for menor que 6 ou maior que 15 o processo é repetido
                                                                              // as long as the number of tens is less than 6 or greater than 15 the process is repeated

            dezenas_de_cada_jogo = calloc(numero_de_jogos,sizeof(int));       //gera um vetor dinâmico de inteiros, para armazenar a quantidade de dezenas que o usuário pediu para cada jogo
                                                                              // generates a dynamic vector of integers, to store the amount of tens that the user requested for each game

            for(i=0;i<numero_de_jogos;i++){                                   //repetição para preencher o vetor com a quantidade de dezenas escolhida
                                                                              // repetition to fill the vector with the chosen number of tens
                            dezenas_de_cada_jogo[i]=numero_de_dezenas;
            }


        }else{                                                  //se o usuário decidiu que cada jogo terá uma quantidade diferen de dezenas tera agora que dizer qual a quantidade de dezenas para cada um de seus jogos
                                                                // if the user has decided that each game will have a different number of tens, they will now have to say what is the number of tens for each of their games

            dezenas_de_cada_jogo = calloc(numero_de_jogos,sizeof(int));       //gera um vetor dinâmico de inteiros, para armazenar a quantidade de dezenas que o usuário pediu para cada jogo
                                                                              // generates a dynamic vector of integers, to store the amount of tens that the user requested for each game

            do{
                printf("Por favor, digite a quantidade de dezenas entre 6 e 15, que o %d° jogo vai ter:", aux+1);

                //inserção da quantidade de dezenas             // insertion of the amount of tens

                if (scanf("%d", &numero_de_dezenas) != 1){                      // condição para verificar se o que está sendo lido realmente um inteiro, se não for o buffer será apagado
                                                                                // condition to check if what is being read is really an integer, if not the buffer will be cleared

                    fflush(stdin);                                              // função para limpar o buffer em Windows               // function to clear the buffer in Windows
                    __fpurge(stdin);                                            // função para limpar o buffer em linux                 // function to clear the buffer in linux
                    numero_de_dezenas = 0;                                      // coloca zero, e o processo  será repetido             // set zero, and the process will be repeated

                    dezenas_de_cada_jogo[aux]=numero_de_dezenas;                // é inserido no vetor dezenas_de_cada_jogo, o número de dezenas que cada jogo vai ter
                                                                                // is inserted in the tens_de_cada_jogo vector, the number of tens that each game will have

                }else{

                    if(numero_de_dezenas<6 ||numero_de_dezenas>15){                 // verificar se o numero de dezenas do jogo que está sendo contado, é menor 6 ou maior que 15
                                                                                    // check if the number of tens of the game being counted is less than 6 or greater than 15

                        dezenas_de_cada_jogo[aux]=0;                                // é inserido no vetor dezenas_de_cada_jogo, a quantidade de dezenas que cada jogo vai ter
                                                                                    // is inserted in the tens_de_cada_jogo vector, the number of tens that each game will have
                    }
                    else{

                        dezenas_de_cada_jogo[aux]=numero_de_dezenas;                // é inserido no vetor dezenas_de_cada_jogo, a quantidade de dezenas que cada jogo vai ter
                                                                                    // is inserted in the tens_de_cada_jogo vector, the number of tens that each game will have

                        aux++;                                                      // incremento da variável auxiliar, apenas quanto tudo estiver certo
                                                                                    // increment of the auxiliary variable, just when everything is right
                    }
                }

            }while(numero_de_dezenas<6 ||numero_de_dezenas>15 || aux<numero_de_jogos);   // o processo será repetido enquanto o número de dezenas for menor que 6, ou maior que 15, ou enquanto o número de dezenas para cada jogo não for especificada.
        }                                                                                // the process will be repeated as long as the number of tens is less than 6, or greater than 15, or as long as the number of tens for each game is not specified.


        Jogos = Alocar_matriz_jogos(numero_de_jogos, dezenas_de_cada_jogo);     // alocação dinâmica de espaço para guardar os jogos                // dynamic allocation of space to store games

                                                                                //Gera os jogos aleatórios                                          // Generate random games
            for(i=0;i<numero_de_jogos;i++){                                     //repetição que cria um número aleatório para cada espaço da matriz // repetition that creates a random number for each space in the matrix

                    for(j=0;j<dezenas_de_cada_jogo[i];j++){
                    Jogos[i][j] = rand()%60+1;                                  //aqui é gerado um número aleatório entre 1 e 60.                   // a random number between 1 and 60 is generated here.
                    }
            }

                                                                    //organiza os dados do vetor na forma crescente                             // organizes the vector data in ascending form
    for(i=0;i<numero_de_jogos;i++){                                 //essa repetição é para varrer toda a matriz organizando os números em ordem crescente e substituindo os números repitidos
            aux2=0;                                                 // this repetition is to scan the entire matrix by arranging the numbers in ascending order and replacing the repeated numbers
                do{
                    for(j=0;j<(dezenas_de_cada_jogo[i]-1);j++){     //percorre o vetor                                      //cycle the vector
                        if(Jogos[i][j]>Jogos[i][j+1]){              //se tiver um numero que é maior que seu consecutivo    //if it have a number that is greater than your consecutive

                            aux = Jogos[i][j+1];                    //mude de posição com ele                               //change position with him
                            Jogos[i][j+1] = Jogos[i][j];
                            Jogos[i][j] = aux;

                        }else if(Jogos[i][j]==Jogos[i][j+1]){       //se dois números forem iguais                          //if two numbers are the same

                            while(Jogos[i][j]==Jogos[i][j+1]){      //enquanto for igual                                    //as long as it is the same

                                Jogos[i][j+1]=rand()%60+1;          //gera um número randômico entre 1 e 60                 //generates a random number between 1 and 60
                            }
                        }
                    }
                aux2++;
                }while(aux2<dezenas_de_cada_jogo[i]);               //enquanto não verificar cada dezena de cada jogo esse trecho do código é repetido
   }                                                                // as long as you don't check every ten of each game this code snippet is repeated



    printf("\n\n");

    printf("************ Aqui estão os jogos como pedido:   *****************\n");

    printf("\n\n");

            for(i=0;i<numero_de_jogos;i++){                         //processo para apresentar os jogos na tela                     // process for presenting games on the screen

                    printf("%dº jogo =",i+1);

                    for(j=0;j<dezenas_de_cada_jogo[i];j++){

                            if(Jogos[i][j]<10){
                                printf(" 0%d",Jogos[i][j]);         //aqui o 0 é colocado na frente por questão de estética         // here 0 is placed at the front for aesthetic reasons
                            }else{
                                printf(" %d",Jogos[i][j]);
                            }
                    }
                    printf("\n");
            }
                                                                    //após a apresentação dos jogos na tela é apresentado ao usuário a pergunta, se ele deseja salvar estes jogos ou não
        printf("\n");                                               // after the games are presented on the screen, the user is asked the question, whether he wants to save these games or not
        printf("    Deseja Salvar esse jogo em um arquivo no formato.txt?\n");
        printf("    Digite 1, para SIM ou qualquer outra coisa para NÃO:");

        if (scanf("%d", &aux) != 1){                            // condição para verificar se o que está sendo lido realmente um inteiro, se não for o buffer será apagado
                                                                // condition to check if what is being read is really an integer, if not the buffer will be cleared

                    fflush(stdin);                              // função para limpar o buffer em Windows               // function to clear the buffer in Windows
                    __fpurge(stdin);                            // função para limpar o buffer em linux                 // function to clear the buffer in linux
                    aux = 0;                                    // caso escrava errado considera como se tivesse escrito o número zero
                                                                // wrong slave case considers it as if she had written the number zero
                }

        if(aux==1){                                                 //se ele desejar salvar a função 'Arquivar_jogo' salva os jogos em arquivo txt.
                                                                    // if he wants to save the 'Archive_Game' function he saves the games in a txt file.
                Arquivar_jogo(Jogos,numero_de_jogos,dezenas_de_cada_jogo);

        }                                                           //caso contrário se não desejar salvar simplismente pula esta etapa         // otherwise if you don't want to save just skip this step

    Libera_Matriz_jogos(Jogos,numero_de_jogos);                     //liberar espaço da matriz de jogos                 // free space from the game matrix
    free(dezenas_de_cada_jogo);                                     //liberar espaço do vetor de dezenas                // free up space of the tens vector


        printf("************   Fim do código    *****************\n");

    //system("PAUSE");
    return 0;
}



/********************   Fim do código principal   *********************************/
/********************   End of main code          *********************************/
