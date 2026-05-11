#include "logs.h"

void gerarLog(const char* usuario, const char* acao) {
    FILE *arquivoLog = fopen("../dados/logs.csv", "a");
    if (!arquivoLog) return;

    fprintf(arquivoLog, "%s;%s\n", usuario, acao);
    fclose(arquivoLog);
}