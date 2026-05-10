#include <stdio.h>

int funcao(int vet[], int len){
    printf("Ultimo numero do vetor: %d\n", vet[len - 1]);
    printf("Tamanho do vetor: %d\n", len);
    if(len == 0)
    return 0;
    return vet[len - 1] + funcao(vet, len - 1);
}
 int main(){

    int vet [5] = {4, 5, 8, 10, 11};
    int res = funcao(vet, 5);
    printf("Resultado = %d", res);
 }
