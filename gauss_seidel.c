#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Thiago dos Santos

double **criaMatriz(int linha,int coluna)
{
    int i,j;
    double **mat;
    mat=malloc(linha*sizeof(double*));
    printf("Digite os valores da matriz:\n");
    for (i=0;i<linha;i++)
    {
        mat[i]=malloc(coluna*sizeof(double));
        for (j=0;j<coluna;j++)
        {
            scanf("%lf",&mat[i][j]);
        }
    }
    return mat;
}

double *criaVetorVazio(int tamanho)
{
    int i;
    double *vetor;
    vetor=(double *)malloc(tamanho*sizeof(double));
    for (i=0;i<tamanho;i++)
    {
        vetor[i]=0;
    }
    return vetor;
}

double *criaVetor(int tamanho)
{
    int i;
    double *vetor;
    vetor=(double *)malloc(tamanho*sizeof(double));
    printf("\nDigite os valore do vetor:\n");
    for (i=0;i<tamanho;i++)
    {
        scanf("%lf",&vetor[i]);
    }
    return vetor;
}

double *subVetor(double *vetor1,double *vetor2,int tamanho)
{
    int i;
    double *result;
    result=malloc(tamanho*sizeof(*vetor1));
    for (i=0;i<tamanho;i++)
    {
        if (vetor1[i]>vetor2[i])
            result[i]=vetor1[i]-vetor2[i];

        else
            result[i]=vetor2[i]-vetor1[i];
    }
    return result;
}

double *multVetor(double **matriz,double *vetor,int linha,int coluna)
{
    int i,j;
    double *result,aux;
    result=(double *)malloc(coluna*sizeof(*vetor));
    for (i=0;i<linha;i++)
    {
        result[i]=0;
        for (j=0;j<coluna;j++)
        {
            aux=matriz[i][j]*vetor[j];
            result[i]=result[i]+aux;
        }
    }
    return result;
}

double maxVet(double *vetor)
{
    int i;
    double maiorGlobal,maiorLocal;
    maiorGlobal=vetor[0];
    for (i=0;i<3;i++)
    {
        if (vetor[i]>vetor[i+1])
            maiorLocal=vetor[i];

        else
            maiorLocal=vetor[i+1];

        if (maiorLocal>maiorGlobal)
            maiorGlobal=maiorLocal;
    }
    return maiorGlobal;
}

int main()
{
    int i,j,n=1,linha,coluna;
    double  **A,*b,*x0,*x1,*ErroR,*ErroX=0,*aux,erro=pow(10,-8),Er,Ex;
    printf("Digite o numero de linhas da matriz A:\n");
    scanf("%d",&linha);
    printf("Digite o numero de colunas da matriz A:\n");
    scanf("%d",&coluna);
    A=criaMatriz(linha,coluna);
    b=criaVetor(linha);
    x0=criaVetorVazio(coluna);
    x1=criaVetorVazio(coluna);
    printf("\nmatriz A:\n");
    for (i=0;i<3;i++)
    {
        for (j=0;j<3;j++)
        {
            printf("%.15lf\t",A[i][j]);
        }
        printf("\n");
    }
    printf("\nvetor b:\n");
    for (i=0;i<linha;i++)
    {
        printf("%.15lf\n",b[i]);
    }
    printf("\n");
    do
    {
        printf("iteracao %d:\n",n);
        for (i=0;i<coluna;i++)
        {
            x1[i]=b[i];

            for (j=0;j<=i-1;j++)
            {
                x1[i]=x1[i]-(A[i][j]*x1[j]);
            }

            for (j=i+1;j<coluna;j++)
            {
                x1[i]=x1[i]-(A[i][j]*x0[j]);
            }

            if (A[i][i]!=0)
                x1[i]=x1[i]/A[i][i];

            else
                return 0;

            printf("%.15lf\n",x1[i]);
        }
        printf("\n");
        n++;
        ErroX=subVetor(x1,x0,coluna);
        aux=multVetor(A,x1,linha,coluna);
        ErroR=subVetor(aux,b,linha);
        Ex=maxVet(ErroX);
        printf("\nErro x:%.15lf\n",Ex);
        Er=maxVet(ErroR);
        printf("\nErro r:%.15lf\n\n",Er);
        for (i=0;i<sizeof(x1);i++)
        {
            x0[i]=x1[i];
        }
    }while (Er>erro || Ex>erro);
		free(A);
    free(b);
    free(x0);
    free(x1);
    free(aux);
		free(ErroX);
    free(ErrorR);
    return 0;
}
