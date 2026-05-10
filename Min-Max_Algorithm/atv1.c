#include <stdio.h>

void conq(int vet[], int inicio, int fim, int *min, int *max){
    if(inicio == fim){
        *min = vet[inicio];
        *max = vet[inicio];
        return;
    }

    if(inicio + 1 == fim){
        if(vet[inicio] < vet[fim]){
            *min = vet[inicio];
            *max = vet[fim];
        } else {
            *min = vet[fim];
            *max = vet[inicio];
        }
        return;
    }

    int meio = (inicio+fim)/2;
    int min1, min2, max1, max2;

    conq(vet, inicio, meio, &min1, &max1);
    conq(vet, meio + 1, fim, &min2, &max2);

    if(min1 < min2){
        *min = min1;
    }else{
        *min = min2;
    }
    if(max1 > max2){
        *max = max1;
    }else{
        *max = max2;
    }
}

int main(void){
    int vet[5] = {12, 18, 20, 2, 6};
    int n = sizeof(vet) / sizeof(vet[0]);
    int min, max;

    conq(vet, 0, n-1, &min, &max);

    printf("min: %d\n", min);
    printf("max: %d\n", max);

    return 0;
}