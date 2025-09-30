#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Função para verificar se o navio pode ser posicionado sem sair dos limites e sem sobreposição
int pode_posicionar(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int d_linha, int d_coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i * d_linha;
        int c = coluna + i * d_coluna;
        if (l < 0 || l >= TAM_TABULEIRO || c < 0 || c >= TAM_TABULEIRO)
            return 0;
        if (tabuleiro[l][c] != 0)
            return 0;
    }
    return 1;
}

// Função para posicionar o navio
int posiciona_navio(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna, int d_linha, int d_coluna) {
    if (!pode_posicionar(tabuleiro, linha, coluna, d_linha, d_coluna)) {
        printf("Erro: navio ultrapassa os limites ou sobrepoe outro navio.\n");
        return 0;
    }
    for (int i = 0; i < TAM_NAVIO; i++) {
        int l = linha + i * d_linha;
        int c = coluna + i * d_coluna;
        tabuleiro[l][c] = 3;
    }
    return 1;
}

// Função para construir matriz cone
void cria_cone(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int centro = TAM_HABILIDADE / 2;
            matriz[i][j] = (j >= centro - i && j <= centro + i) ? 1 : 0;
        }
    }
}

// Função para construir matriz cruz
void cria_cruz(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = (i == centro || j == centro) ? 1 : 0;
        }
    }
}

// Função para construir matriz octaedro (losango)
void cria_octaedro(int matriz[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            matriz[i][j] = ((i - centro) + (j - centro) <= centro) ? 1 : 0;
        }
    }
}

// Função para verificar se a habilidade pode ser aplicada sem ultrapassar os limites
int pode_aplicar_habilidade(int origem_linha, int origem_coluna) {
    int centro = TAM_HABILIDADE / 2;
    int l_ini = origem_linha - centro;
    int l_fim = origem_linha + centro;
    int c_ini = origem_coluna - centro;
    int c_fim = origem_coluna + centro;
    if (l_ini < 0 || l_fim >= TAM_TABULEIRO || c_ini < 0 || c_fim >= TAM_TABULEIRO)
        return 0;
    return 1;
}

// Função para sobrepor matriz de habilidade ao tabuleiro
int aplica_habilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int matriz[TAM_HABILIDADE][TAM_HABILIDADE], int origem_linha, int origem_coluna) {
    if (!pode_aplicar_habilidade(origem_linha, origem_coluna)) {
        printf("Erro: habilidade ultrapassa os limites do tabuleiro.\n");
        return 0;
    }
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int l = origem_linha - centro + i;
            int c = origem_coluna - centro + j;
            if (matriz[i][j] == 1 && tabuleiro[l][c] == 0) {
                tabuleiro[l][c] = 5;
            }
        }
    }
    return 1;
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Posiciona navios
    posiciona_navio(tabuleiro, 21, 4, 0, 1);
    posiciona_navio(tabuleiro, 6, 1, 1, 0);
    posiciona_navio(tabuleiro, 0, 0, 1, 1);
    posiciona_navio(tabuleiro, 0, 9, 1, -1);

    // Matrizes de habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE] = {0};
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE] = {0};

    cria_cone(cone);
    cria_cruz(cruz);
    cria_octaedro(octaedro);

    // Aplica habilidades em pontos de origem
    aplica_habilidade(tabuleiro, cone, 3, 6);         // Cone em (1,1)
    aplica_habilidade(tabuleiro, cruz, 5, 5);         // Cruz em (5,5)
    aplica_habilidade(tabuleiro, octaedro, 4, 3);     // Octaedro em (8,8)

    // Exibe tabuleiro
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}