#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct
{
    int bombas;
    char pontos;

} Matriz;

Matriz **AlocarMatriz(int M, int N) //aloca dinamicamente uma matriz de strusts
{
    int i, j;
    Matriz **mat = (Matriz**)malloc(M*sizeof(Matriz*)); // aloca um vetor de ponteiros
    for(i=0; i<M; i++)
    {
        mat[i]= (Matriz*)malloc(N*sizeof(Matriz)); //aloca um vetor de inteiros para cada posição do vetor de ponteiros
        for(j=0; j<N; j++)
        {
            mat[i][j].bombas = -1; //preenche a matriz com "-1" para indicar q esta vazia
        }
    }
    return mat; //retorna um ponteiro
}
Matriz Preenche_Bombas(Matriz **mat, int m, int n, int x) // funçao que coloca as bombas na matriz
{
    int i, j, aux = 0, lin, col, flag=0;
    srand(time(NULL));  //funçao para jogar numeros aleatorios usando a biblioteca "time.h"
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            mat[i][j].bombas = -1; //para mostrar q a posição da matriz esta vazia
        }
    }
    while (aux < x)  //aqui as bombas são preenchidas na matriz
    {
        lin = rand() % m; //escolhe uma posiçao da linha
        col = rand() % n; //escolhe uma posiçao da coluna
        if (mat[lin][col].bombas == -1)
        {
            mat[lin][col].bombas = 0; //coloca um "0" na posiçao para indicar uma bomba
            flag=1;     //Para indicar q uma posição vazia recebeu uma bomba
        }
        else
            flag=0;     //Para indicar q uma posição que ja possui uma bomba
        while(flag==0) // para procurar outra posição vazia para colocar uma bomba
        {
            lin = rand() % m; //novamente joga uma posiçao aleatoria para a linha
            col = rand() % n; //novamente joga uma posiçao aleatoria para a coluna
            if (mat[lin][col].bombas == -1)//confere se a posiçao esta vazia
            {
                mat[lin][col].bombas = 0; //se estiver vazia coloca um "0" na posiçao para indicar uma bomba
                flag=1; //para indicar que a posiçao tem uma bomba
            }
            else
                flag=0; //indica que a posiçao possui uma bomba
        }
        aux++;
    }
}
void Imprime_Matriz(Matriz **mat, int m, int n) //função para imprimir a matriz
{
    int i, j;
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            printf("%d ", mat[i][j].bombas);
        }
        printf("\n");
    }
}
/*void Tabuleiro(Matriz **mat, int m, int n)
{
    int i, j, x = -1, y = 48; // y=48 pois 48 é equivalente ao numero "0" na tabela ascii

    //for(j=0;j<m;j++)
    //  printf(" %d ", j);

    //printf("\n\n");
    for (i = 0; i < (m + 1); i++)
    {
        //  printf(" %d ", i);
        if(i != 0)
            printf("%d", x); //para indicar o numero de cada linha
        for (j = 0; j < (n + 1); j++)
        {
            if (i == 0 && j!=0)  //para indicar o numero de cada coluna
            {
                printf(" %c", y);
            }
            mat[i + 1][j + 1].pontos = '.'; //preenche a matriz com "pontos" para simular o tabuleiro
            if (i != 0 || j != 0)
                printf("%c ", mat[i][j].pontos); //imprime a matriz com pontos para indicar o tabuleiro
            y++;
        }
        x++;

        printf("\n");
    }
}*/
void Tabuleiro(Matriz **mat, int m, int n)
{
    int i, j;
    for(j=0; j<m; j++)//para mostra a numero das colunas
        printf("%d ", j);
    printf("\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            mat[i][j].pontos = '.'; //preenche a matriz com "pontos" para simular o tabuleiro
            printf("%c ", mat[i][j].pontos); //imprime a matriz com pontos para indicar o tabuleiro
        }
        printf(" %d", i); //para mostrar o numero das linhas
        printf("\n");
    }
    printf("\n");
}
void CriaJogo(Matriz **mat, char frase[], int m, int n) //função que vai criar o jogo com o tamanho do tabuleiro e o numero de bombas
{
    int i, j, bombas;

    if(strcmp(frase, "novo")==0) //verifica se a palavra digitada é igual a palavra "novo"
    {
        scanf("%d", &bombas); //le o numero de linhas, colunas e o numero de bombas
        Preenche_Bombas(mat, m, n, bombas);  //chama a função para preencher a matriz com as bombas
        //Imprime_Matriz(mat,m,n);
        printf("\n");
        Tabuleiro(mat,m,n); //cria o tabuleiro
    }
    else
        printf("ERRO!!\n");
}
void ContarBombas(Matriz **mat, char frase[], int m, int n)   //para contar o numero de bombas adjacentes ao ponto jogado
{
    int i, j, cont=0, aux, aux2;
    aux=m;  //variavel auxiliar
    aux2=n; //variavel auxiliar 2
    for(i=(m-1); i<=(m+1); i++)
    {
        n=aux2;
        for(j=(n-1); j<=(n+1); j++)
        {
            if((i<=aux) || (j<=aux2))
            {
                if(mat[i][j].bombas==0)  //cerifica se a casa contem uma bomba
                {
                    cont++;  //variavel para contar as bombas
                    mat[aux][aux2].bombas=cont;
                }
            }
        }
    }
    MostrarTabuleiro(mat,aux,aux2,cont);
}
void Jogadas(Matriz **mat, char frase[],int m, int n)  //funçao q executa as jogadas do usuario
{
    int i,j,bombas=0,M,N,cont;
    CriaJogo(mat,frase,m,n);  //chama a funçao que vai criar o jogo
    do
    {
        scanf("%s", frase);   //le uma frase do usuario para executar a jogada
        if(strcmp(frase,"jogar")==0)   //confere se a palavra escrita é igual a palavra "jogar"
        {
            printf("\n");
            scanf("%d%d", &M, &N);  //le do usuario a linha e coluna em que vai ser feita a jogada
            if(mat[M][N].bombas == 0)   //verefica se existe uma bomba na posiçaoMatriz **a = AlocarMatriz(m, n);
            {
                printf("Game Over\n");  // se existir uma bomba então Game Over
                //printar o tabulerio aq com "*" na posição que as bombas estiverem
                break;
            }
            else
            {
                ContarBombas(mat,frase,M,N); //chama a funçao para contar as bombas nas casas adjacentes a casa jogada pelo usuario
                //MostrarTabuleiro(mat,m,n,cont);
                cont=1;
            }
        }
        else if(strcmp(frase,"sair")==0) //para encerrar o jogo
            break;
        else if(strcmp(frase,"novo")==0) //indica que ja existe um jogo em andamento
            printf("Ha um jogo em andamento");
        else //indica um comando invalido
            printf("Jogada Invalida");

    }
    while(cont!=0); //enquanto nao estourar uma bomba o usuario vai jogando

}
void MostrarTabuleiro(Matriz **mat, int m, int n, int cont)
{
    int i, j;
    for(j=0; j<m; j++)
        printf("%d ", j);
    printf("\n");
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
        {
            if(mat[i][j].bombas==cont)
                printf("%d", mat[i][j].bombas);
            else
            {
                mat[i][j].pontos = '.';
                printf("%c ", mat[i][j].pontos); //imprime a matriz com pontos para indicar o tabuleiro
            }
        }
        printf(" %d", i);
        printf("\n");
    }
    printf("\n");
}
int main()
{
    int i, j, n, m, x = -1, y = 47, k, l;
    char string[100];
    scanf("%s", string);
    scanf("%d%d", &m,&n);
    Matriz **a = AlocarMatriz(m, n);
    //Preenche_Bombas(a, m, n, 4);
    //Imprime_Matriz(a, m, n);
    //Tabuleiro(a, m, n);
    Jogadas(a,string,m,n);
    //CriaJogo(a,string,m,n);
    free(a);

    return 0;
}
