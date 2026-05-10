#include <stdio.h>

int funcao(int n, int e){
    if(e == 0)
    return 1;
    return n * funcao(n, e - 1);

}

int main(){
    int num, exp;
    printf("Digite seu numero: ");
    scanf("%d", &num);
    printf("\n");
    printf("Digite seu expoente: ");
    scanf("%d", &exp);
    int res = funcao(num, exp);
    printf("\n");
    printf("Resultado: %d", res);
    return 0;
}
