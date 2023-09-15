#include <stdio.h>
#include <stdlib.h>

#define LIN 10
#define COL 40

#ifdef _WIN32
#include <windows.h>
#define SLEEP Sleep(2000)
#endif

#ifdef __linux__
#include <unistd.h>
#define SLEEP sleep(2)
#endif

/* ------- Protótipo da Função -------*/
void saudacao();
int verificar_sala();
int escolha_ingresso(int sala);
int verificar_quant_ingressos(int sala, int quant_ingressos);
int ingressos_restantes(int sala, int quant_ingressos);
int meia_entrada(int quant_ingressos, int sala);
int adicionarCarteirinha(int carteirinha, int sala);
int validar_carteirinha(int carteirinha, int sala);
int desconto_itasil(int quant_ingressos, int sala);
int adicionaritasil(int cod_ita, int sala);
int validar_itasil(int cod_ita, int sala);
int zerarmapa();
void cadeiras(int sala);
int verificar_posicao(int sala, int fila, char col);
void zerarmeia();
void zeraritasil();
void zeraringressos();
void valortotal(float valor);
int solicitar_posicao(int quant_ingressos, int sala);
void criarsalas();

int main(){
    int sala = 5;
    int quant_int;
    int quant_ingressos;
    int meia;
    int itasil;
    float valor;
    do{
        criarsalas();
        saudacao();
        sala = verificar_sala();
        quant_ingressos = escolha_ingresso(sala);
        quant_int = quant_ingressos;
        meia = meia_entrada(quant_int, sala);
        quant_int = quant_int - meia;
        itasil = desconto_itasil(quant_int, sala);
        quant_int = quant_int - itasil;
        solicitar_posicao(quant_ingressos, sala);
        valor = quant_int * 20 + meia * 10 + itasil * 14;
        valortotal(valor);
    }while(sala!=0);
    return 0;
}

void criarsalas(){
    FILE *mapasala1, *mapasala2, *mapasala3;
    mapasala1 = fopen("mapasala1.txt", "r");
    if(mapasala1 == NULL){
        zerarmapa();
    }
    else{
        fclose(mapasala1);
    }
    mapasala2 = fopen("mapasala2.txt", "r");
    if(mapasala2 == NULL){
        zerarmapa();
    }
    else{
        fclose(mapasala2);
    }
    mapasala3 = fopen("mapasala3.txt", "r");
    if(mapasala3 == NULL){
        zerarmapa();
    }
    else{
        fclose(mapasala3);
    }
}

void zeraringressos(){
    FILE *ingressosdisponiveis;
    int ingressos_disponiveis_sala1 = 400, ingressos_disponiveis_sala2 = 400, ingressos_disponiveis_sala3 = 400;
    ingressosdisponiveis = fopen("ingressosdisponiveis.txt", "w");
    if(ingressosdisponiveis == NULL){
        printf("Erro ao abrir o arquivo\n");
    }
    else{
        fprintf(ingressosdisponiveis, "%d %d %d", ingressos_disponiveis_sala1, ingressos_disponiveis_sala2, ingressos_disponiveis_sala3);
        fclose(ingressosdisponiveis);
    }
}

void zerarmeia(){
    FILE *vetormeia1, *vetormeia2, *vetormeia3;
    vetormeia1 = fopen("vetormeia1.txt", "w");
    fclose(vetormeia1);
    vetormeia2 = fopen("vetormeia2.txt", "w");
    fclose(vetormeia2);
    vetormeia3 = fopen("vetormeia3.txt", "w");
    fclose(vetormeia3);
}

void zeraritasil(){
    FILE *vetoritasil1, *vetoritasil2, *vetoritasil3;
    vetoritasil1 = fopen("vetoritasil1.txt", "w");
    fclose(vetoritasil1);
    vetoritasil2 = fopen("vetoritasil2.txt", "w");
    fclose(vetoritasil2);
    vetoritasil3 = fopen("vetoritasil3.txt", "w");
    fclose(vetoritasil3);
}

void saudacao(){
    FILE *ingressosdisponiveis;
    int ingressos_disponiveis_sala1 = 400, ingressos_disponiveis_sala2 = 400, ingressos_disponiveis_sala3 = 400;

    ingressosdisponiveis = fopen("ingressosdisponiveis.txt", "r");

    if(ingressosdisponiveis != NULL){
        fscanf(ingressosdisponiveis, "%d %d %d", &ingressos_disponiveis_sala1, &ingressos_disponiveis_sala2, &ingressos_disponiveis_sala3);
        fclose(ingressosdisponiveis);
    }

    else {
        ingressosdisponiveis = fopen("ingressosdisponiveis.txt", "w");
        fprintf(ingressosdisponiveis, "%d %d %d", ingressos_disponiveis_sala1, ingressos_disponiveis_sala2, ingressos_disponiveis_sala3);
        if(ingressosdisponiveis == NULL){
            printf("Erro ao abrir o arquivo\n");
            exit(1);
        }
        else{
            fclose(ingressosdisponiveis);
        }
        
    }

    printf("-------------------------------------------------------------------\n");
    printf("                             CINEMA                                \n");
    printf("-------------------------------------------------------------------\n");
    printf("Seja Bem-Vindo ao Nosso Cinema!\n");
    printf("Filmes em cartaz:\n");
    printf("1- VELOZES E FURIOSOS 137\n");
    printf("2- THE FLASH\n");
    printf("3- TRANSFORMERS\n");
    printf("\n");
    if (ingressos_disponiveis_sala1 == 0) printf(" (Sessão esgotada)\n");
    else printf(" A sala 1 tem %d ingressos disponiveis\n", ingressos_disponiveis_sala1);
    
    if (ingressos_disponiveis_sala2 == 0) printf(" (Sessão esgotada)\n");
    else printf(" A sala 2 tem %d ingressos disponiveis\n", ingressos_disponiveis_sala2);
    
    if (ingressos_disponiveis_sala3 == 0) printf(" (Sessão esgotada)\n");
    else printf(" A sala 3 tem %d ingressos disponiveis\n", ingressos_disponiveis_sala3);
    SLEEP;
}

int verificar_sala (){
    int opc_filme;
    while (opc_filme < 0 || opc_filme > 3){
        printf("Selecione um dos filmes\n>");
        scanf("%d", &opc_filme);
        if(opc_filme==0) exit(1);
        else if(opc_filme==999){
            zerarmapa();
            zeraringressos();
            zeraritasil();
            zerarmeia();
            printf("Informações resetadas com sucesso\n");
            exit(1);
        }
        else if(!(opc_filme < 0 || opc_filme > 3)) return opc_filme;
        else{
            printf("Opção inválida\n");
        }
    }
    return 0;
}

int escolha_ingresso(int sala){
    int quant_ingressos;
    printf("-------------------------------------------------------------------\n");
    printf("Quantos ingressos você deseja?\n>");
    while (1){
        scanf("%d", &quant_ingressos);
        if (verificar_quant_ingressos(sala, quant_ingressos) == 1) {
            printf("Quantidade de ingressos armazenada com sucesso\n");
            ingressos_restantes(sala, quant_ingressos);
            return quant_ingressos;
        }
        printf("Digite novamente\n>");
    }
    return 0;
}

int verificar_quant_ingressos(int sala, int quant_ingressos){
    FILE *ingressosdisponiveis;
    int ingressos_disponiveis_sala1, ingressos_disponiveis_sala2, ingressos_disponiveis_sala3;
    ingressosdisponiveis = fopen("ingressosdisponiveis.txt", "r");
    if(ingressosdisponiveis == NULL){
        printf("Erro ao abrir o arquivo.");
        return 0;
    }
    else{
        fscanf(ingressosdisponiveis, "%d %d %d", &ingressos_disponiveis_sala1, &ingressos_disponiveis_sala2, &ingressos_disponiveis_sala3);
        fclose(ingressosdisponiveis);
    }
    
    if (sala == 1){
        if(quant_ingressos<=ingressos_disponiveis_sala1 && quant_ingressos>0) return 1;
        else{
            printf("Quantidade de ingressos indisponível.\n");
            return 0;
        }
    }
    if (sala == 2){
        if(quant_ingressos<=ingressos_disponiveis_sala2 && quant_ingressos>0) return 1;
        else{
            printf("Quantidade de ingressos indisponível.\n");
            return 0;
        }
    }
    if (sala == 3){
        if(quant_ingressos<=ingressos_disponiveis_sala3 && quant_ingressos>0) return 1;
        else{
            printf("Quantidade de ingressos indisponível.\n");
            return 0;
        }
    }
    return 1;
}

int ingressos_restantes(int sala, int quant_ingressos){
    FILE *ingressosdisponiveis;
    int ingressos_disponiveis_sala1, ingressos_disponiveis_sala2, ingressos_disponiveis_sala3;
    ingressosdisponiveis = fopen("ingressosdisponiveis.txt", "r");
    if(ingressosdisponiveis == NULL){
        printf("Erro ao abrir o arquivo.");
        return 0;
    }
    else{
        fscanf(ingressosdisponiveis, "%d %d %d", &ingressos_disponiveis_sala1, &ingressos_disponiveis_sala2, &ingressos_disponiveis_sala3);
        fclose(ingressosdisponiveis);
    }
    
    if(sala == 1 && verificar_quant_ingressos(sala, quant_ingressos) == 1){
        ingressos_disponiveis_sala1 = ingressos_disponiveis_sala1 - quant_ingressos;
    }
    else if(sala == 2 && verificar_quant_ingressos(sala, quant_ingressos) == 1){
        ingressos_disponiveis_sala2 = ingressos_disponiveis_sala2 - quant_ingressos;
    }
    else if(sala == 3 && verificar_quant_ingressos(sala, quant_ingressos) == 1){
        ingressos_disponiveis_sala3 = ingressos_disponiveis_sala3 - quant_ingressos;
    }
    ingressosdisponiveis = fopen("ingressosdisponiveis.txt", "w");
    if(ingressosdisponiveis == NULL){
        printf("Erro ao abrir o arquivo.");
        return 0;
    }
    else{
        fprintf(ingressosdisponiveis, "%d %d %d", ingressos_disponiveis_sala1, ingressos_disponiveis_sala2, ingressos_disponiveis_sala3);
        fclose(ingressosdisponiveis);
    }
    return 0;
}

int meia_entrada(int quant_ingressos, int sala){
    int i = 1;
    int meia = 999;
    int carteirinha;
    while(meia > quant_ingressos){
        printf("-------------------------------------------------------------------\n");
        printf("Quantos dos %d ingressos serão meia entrada?\n", quant_ingressos);
        scanf("%d", &meia);
        if(meia>quant_ingressos) printf("Digite uma quantidade de meias abaixo da quantidade de ingressos já selecionados.\n");
    }
    while(i <= meia){
        printf("Digite o número da carteirinha do ingresso: %d/%d.\n", i, meia);
        scanf("%d", &carteirinha);
        if(carteirinha == 0){
            meia--;
        }
        else if (validar_carteirinha(carteirinha, sala) == 1){
            i++;
            adicionarCarteirinha(carteirinha, sala);
        }
    }
    return meia;
}

int adicionarCarteirinha(int carteirinha, int sala){
    FILE *vetormeia1, *vetormeia2, *vetormeia3;
    switch (sala)
    {
    case 1:
        vetormeia1 = fopen("vetormeia1.txt", "a+");
        if (vetormeia1 == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 0;
        }
        else{
            fprintf(vetormeia1, "%d\n", carteirinha);
            fclose(vetormeia1);
        }
        break;
    case 2:
        vetormeia2 = fopen("vetormeia2.txt", "a+");
        if (vetormeia2 == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 0;
        }
        else{
            fprintf(vetormeia2, "%d\n", carteirinha);
            fclose(vetormeia2);
        }
        break;
    case 3:
        vetormeia3 = fopen("vetormeia3.txt", "a+");
        if (vetormeia3 == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 0;
        }
        else{
            fprintf(vetormeia3, "%d\n", carteirinha);
            fclose(vetormeia3);
        }
        break;

    default:
        printf("Sala inválida");
        break;
    }
    return 1;
}

int validar_carteirinha(int carteirinha, int sala){
    int soma=0, ultValor, cart2, numerolido;
    FILE *vetormeia1, *vetormeia2, *vetormeia3;
    char linha[100];
    if (carteirinha < 0 || carteirinha > 99999){
        printf("Carteirinha inválida. (Digite 0 para cancelar o desconto nesse ingresso)\n");
        return 0;
    }
    else{
        ultValor = carteirinha%10;
        cart2 = carteirinha/10;
        while(cart2>0) {
            soma+=cart2%10;
            cart2 /= 10;
        }
        if((soma%10) == ultValor) {
            switch (sala)
            {
            case 1:
                vetormeia1 = fopen("vetormeia1.txt", "a+");
                if (vetormeia1 == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                else{
                    while (fgets(linha, sizeof(linha), vetormeia1) != NULL) {
                        numerolido = atoi(linha);
                        if(carteirinha == numerolido){
                            puts("Carteirinha já foi utilizada. (Digite 0 para cancelar o desconto nesse ingresso)\n");
                            return 0;
                        }
                    }
                    fclose(vetormeia1);
                }
                break;
            
            case 2:
                vetormeia2 = fopen("vetormeia2.txt", "a+");
                if (vetormeia2 == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                else{
                    while (fgets(linha, sizeof(linha), vetormeia2) != NULL) {
                        numerolido = atoi(linha);
                        if(carteirinha == numerolido){
                            puts("Carteirinha já foi utilizada. (Digite 0 para cancelar o desconto nesse ingresso)\n");
                            return 0;
                        }
                    }
                    fclose(vetormeia2);
                }
                break;

            case 3:
                vetormeia3 = fopen("vetormeia3.txt", "a+");
                if (vetormeia3 == NULL) {
                    printf("Erro ao abrir o arquivo.\n");
                    return 0;
                }
                else{
                    while (fgets(linha, sizeof(linha), vetormeia3) != NULL) {
                        numerolido = atoi(linha);
                        if(carteirinha == numerolido){
                            puts("Carteirinha já foi utilizada. (Digite 0 para cancelar o desconto nesse ingresso)\n");
                            return 0;
                        }
                    }
                    fclose(vetormeia3);
                }
                break;

            default:
                printf("Sala inválida");
                break;
            }
            
            return 1;
        }
        else{
            printf("Carteirinha inválida. (Digite 0 para cancelar o desconto nesse ingresso)\n");
            return 0;
        }
    }
}

int desconto_itasil(int quant_ingressos, int sala){
    int i = 1;
    int itasil = 999;
    int cod_ita;
    while(itasil > quant_ingressos){
        printf("-------------------------------------------------------------------\n");
        printf("Quantos dos %d ingressos possuirão desconto itasil?\n", quant_ingressos);
        scanf("%d", &itasil);
        if(itasil > quant_ingressos) printf("Digite uma quantidade de ingressos com desconto abaixo da quantidade de ingressos já selecionados.(Lembrando: Ingressos não têm desconto cumulativo)\n");
    }
    while (i <= itasil){
        printf("Digite o número do código itasil do ingresso: %d/%d.\n", i, itasil);
        scanf("%d", &cod_ita);
        if (validar_itasil(cod_ita, sala) == 1){
            i++;
            adicionaritasil(cod_ita, sala);
        }
        else if(cod_ita == 0){
            itasil--;
        }
    }
    return itasil;
}

int adicionaritasil(int cod_ita, int sala){
    FILE *vetoritasil1, *vetoritasil2, *vetoritasil3;
    switch (sala)
    {
    case 1:
        vetoritasil1 = fopen("vetoritasil1.txt", "a+");
        if (vetoritasil1 == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 0;
        }
        else{
            fprintf(vetoritasil1, "%d\n", cod_ita);
            fclose(vetoritasil1);
        }
        break;
    case 2:
        vetoritasil2 = fopen("vetoritasil2.txt", "a+");
        if (vetoritasil2 == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 0;
        }
        else{
            fprintf(vetoritasil2, "%d\n", cod_ita);
            fclose(vetoritasil2);
        }
        break;
    case 3:
        vetoritasil3 = fopen("vetoritasil3.txt", "a+");
        if (vetoritasil3 == NULL) {
            printf("Erro ao abrir o arquivo.\n");
            return 0;
        }
        else{
            fprintf(vetoritasil3, "%d\n", cod_ita);
            fclose(vetoritasil3);
        }
        break;
    default:
        printf("Sala inválida");
        break;
    }
    
    return 1;
}

int validar_itasil(int cod_ita, int sala){
    int numerolido;
    FILE *vetoritasil1, *vetoritasil2, *vetoritasil3;
    char linha[100];
    if(cod_ita % 341 == 0){
        switch (sala)
        {
        case 1:
            vetoritasil1 = fopen("vetoritasil1.txt", "a+");
            if (vetoritasil1 == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                return 0;
            }
            else{
                while (fgets(linha, sizeof(linha), vetoritasil1) != NULL) {
                    numerolido = atoi(linha);
                    if(cod_ita == numerolido){
                        puts("Código já foi utilizado. (Digite 0 para cancelar o desconto nesse ingresso)\n");
                        return 0;
                    }
                }
                fclose(vetoritasil1);
            }
            break;
        
        case 2:
            vetoritasil2 = fopen("vetoritasil2.txt", "a+");
            if (vetoritasil2 == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                return 0;
            }
            else{
                while (fgets(linha, sizeof(linha), vetoritasil2) != NULL) {
                    numerolido = atoi(linha);
                    if(cod_ita == numerolido){
                        puts("Código já foi utilizado. (Digite 0 para cancelar o desconto nesse ingresso)\n");
                        return 0;
                    }
                }
                fclose(vetoritasil2);
            }
            break;

        case 3:
            vetoritasil3 = fopen("vetoritasil3.txt", "a+");
            if (vetoritasil3 == NULL) {
                printf("Erro ao abrir o arquivo.\n");
                return 0;
            }
            else{
                while (fgets(linha, sizeof(linha), vetoritasil3) != NULL) {
                    numerolido = atoi(linha);
                    if(cod_ita == numerolido){
                        puts("Código já foi utilizado. (Digite 0 para cancelar o desconto nesse ingresso)\n");
                        return 0;
                    }
                }
                fclose(vetoritasil3);
            }
            break;
        default:
            printf("Sala inválida");
            break;
        }
            return 1;
    }
    else{
        printf("Código Itasil inválido. (Digite 0 para cancelar o desconto nesse ingresso)\n");
    }
    return 30;
}

int zerarmapa(){
    FILE *mapasala1, *mapasala2, *mapasala3;
    int c, i;
    mapasala1 = fopen("mapasala1.txt", "w+");
    if(mapasala1 == NULL){
        printf("Erro ao abrir arquivo\n");
        return 0;
    }
    else{
        for(c=0; c<COL; c++){
            for(i=0; i<LIN; i++){
                fprintf(mapasala1, "0 ");
            }
            fprintf(mapasala1, "\n");
        }
        fclose(mapasala1);
    }
    mapasala2 = fopen("mapasala2.txt", "w+");
    if(mapasala2 == NULL){
        printf("Erro ao abrir arquivo\n");
        return 0;
    }
    else{
        for(c=0; c<COL; c++){
            for(i=0; i<LIN; i++){
                fprintf(mapasala2, "0 ");
            }
            fprintf(mapasala2, "\n");
        }
        fclose(mapasala2);
    }
    mapasala3 = fopen("mapasala3.txt", "w+");
    if(mapasala3 == NULL){
        printf("Erro ao abrir aqruivo\n");
        return 0;
    }
    else{
        for(c=0; c<COL; c++){
            for(i=0; i<LIN; i++){
                fprintf(mapasala3, "0 ");
            }
            fprintf(mapasala3, "\n");
        }
        fclose(mapasala3);
    }
    return 1;
}

void cadeiras(int sala){
    int c, i;
    char temp;
    FILE *mapasala1, *mapasala2, *mapasala3;
    if (sala == 1){
        mapasala1 = fopen("mapasala1.txt", "r");
        if(mapasala1 == NULL){
            zerarmapa();
        }
        else{
            printf("    A B C D E F G H I J\n");
            for(c=1; c<COL+1; c++) {
                printf("%2d ", c);
                for(i=0; i<LIN; i++) {
                    fscanf(mapasala1, "%c ", &temp);
                    printf(" %c", temp);
                }
                printf("\n");
            }
        }
        fclose(mapasala1);
    }
    else if(sala == 2){
        mapasala2 = fopen("mapasala2.txt", "r");
        if(mapasala2 == NULL){
            zerarmapa();
        }
        else{
            printf("    A B C D E F G H I J\n");
            for(c=1; c<COL+1; c++) {
                printf("%2d ", c);
                for(i=0; i<LIN; i++) {
                    fscanf(mapasala2, "%c ", &temp);
                    printf(" %c", temp);
                }
                printf("\n");
            }
        }
        fclose(mapasala2);
    }
    else if(sala == 3){
        mapasala3 = fopen("mapasala3.txt", "r");
        if(mapasala3 == NULL){
            zerarmapa();
        }
        else{
            printf("    A B C D E F G H I J\n");
            for(c=1; c<COL+1; c++) {
                printf("%2d ", c);
                for(i=0; i<LIN; i++) {
                    fscanf(mapasala3, "%c ", &temp);
                    printf(" %c", temp);
                }
                printf("\n");
            }
        }
        fclose(mapasala3);
    }
}

int solicitar_posicao(int quant_ingressos, int sala){
    int cont=1;
    int fila;
    char col;
    int letra;
    while(cont<=quant_ingressos){
        SLEEP;
        cadeiras(sala);
        printf("-------------------------------------------------------------------\n");
        printf("Escolha a cadeira desejada para o ingresso %d/%d na seguinte formatação: (Fileira[espaço]Coluna.Ex:2 E)\n>", cont, quant_ingressos);
        do{
            scanf("%d %c", &fila, &col);
            letra = col - 65;
            if((fila<0 || fila>40) && (letra < 0 || letra > 9))printf("Fila e colunas fora dos valores possíveis\nDigite novamente\n>");
            else if(fila<0 || fila>40) printf("Fila fora dos valores possíveis\nDigite novamente\n>");
            else if(letra < 0 || letra > 9) printf("Coluna fora dos valores possíveis\nDigite novamente\n>");
            else{
                break;
            }
        }while(0<fila || fila>40 || letra < 0 || letra > 9);
        if(verificar_posicao(sala, fila, col) == 1){
            cont++;
        }
    }
    return 0;
}

int verificar_posicao(int sala, int fila, char col){
    FILE *mapasala1, *mapasala2, *mapasala3;
    int letra = col-65;
    int i, c;
    char temp[COL][LIN];
    if(sala == 1){
        mapasala1 = fopen("mapasala1.txt", "r");
        if(mapasala1!=NULL){
            for(c=0;c<COL;c++){
                for(i=0;i<LIN;i++){
                    fscanf(mapasala1,"%c ", &temp[c][i]);
                }
            }
            fclose(mapasala1);
        }
        else{
            printf("Erro ao abrir arquivo\n");
            return 7;
        }
        if(temp[fila-1][letra] == 'X'){
            printf("Cadeira ocupada, escolha outra!\n");
            return 0;
        }
        else{
            printf("Cadeira selecionada com sucesso\n");
            temp[fila-1][letra] = 'X';
            mapasala1 = fopen("mapasala1.txt", "w");
            for(c=0; c<COL; c++){
                for(i=0; i<LIN; i++){
                    fprintf(mapasala1, "%c ", temp[c][i]);
                }
                fprintf(mapasala1, "\n");
            }
            fclose(mapasala1);
            return 1;
        }
    }
    if(sala == 2){
        mapasala2 = fopen("mapasala2.txt", "r");
        if(mapasala2!=NULL){
            for(c=0;c<COL;c++){
                for(i=0;i<LIN;i++){
                    fscanf(mapasala2,"%c ", &temp[c][i]);
                }
            }
            fclose(mapasala2);
        }
        else{
            printf("Erro ao abrir arquivo\n");
            return 7;
        }
        if(temp[fila-1][letra] == 'X'){
            printf("Cadeira ocupada, escolha outra!\n");
            return 0;
        }
        else{
            printf("Cadeira selecionada com sucesso\n");
            temp[fila-1][letra] = 'X';
            mapasala2 = fopen("mapasala2.txt", "w");
            for(c=0; c<COL; c++){
                for(i=0; i<LIN; i++){
                    fprintf(mapasala2, "%c ", temp[c][i]);
                }
                fprintf(mapasala2, "\n");
            }
            fclose(mapasala2);
            return 1;
        }
    }
    if(sala == 3){
        mapasala3 = fopen("mapasala3.txt", "r");
        if(mapasala3!=NULL){
            for(c=0;c<COL;c++){
                for(i=0;i<LIN;i++){
                    fscanf(mapasala3,"%c ", &temp[c][i]);
                }
            }
            fclose(mapasala3);
        }
        else{
            printf("Erro ao abrir arquivo\n");
            return 7;
        }
        if(temp[fila-1][letra] == 'X'){
            printf("Cadeira ocupada, escolha outra!\n");
            return 0;
        }
        else{
            printf("Cadeira selecionada com sucesso\n");
            temp[fila-1][letra] = 'X';
            mapasala3 = fopen("mapasala3.txt", "w");
            for(c=0; c<COL; c++){
                for(i=0; i<LIN; i++){
                    fprintf(mapasala3, "%c ", temp[c][i]);
                }
                fprintf(mapasala3, "\n");
            }
            fclose(mapasala3);
            return 1;
        }
    }
    return 30;
}

void valortotal(float valor){
    printf("-------------------------------------------------------------------\n");
    printf("O valor a ser pago é: %.2f\n", valor);
    SLEEP;
}