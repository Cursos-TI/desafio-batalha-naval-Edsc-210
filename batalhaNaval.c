// ============================================================================
// Desafio Batalha Naval - Nível Mestre
// Objetivo: Implementar e exibir habilidades especiais com área de efeito.
// Autor: Gemini
// Data: 13/08/2025
// ============================================================================

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Para a função abs() (valor absoluto)

// --- Constantes Globais ---
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5 // Usaremos matrizes 5x5 para as habilidades

// --- Marcadores Visuais no Tabuleiro ---
#define AGUA 0
#define NAVIO 3
#define AREA_HABILIDADE 5


// --- Protótipos das Funções ---

// Funções do desafio anterior (com pequenas adaptações)
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibir_tabuleiro_final(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
// (A lógica de posicionamento de navios foi omitida do main para focar no desafio atual,
// mas as funções poderiam ser usadas normalmente para popular o tabuleiro primeiro.)

// Novas funções para o Nível Mestre
void criar_matriz_cone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_matriz_cruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void criar_matriz_octaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int origem_linha, int origem_coluna, int habilidade_matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]);


int main() {
    // 1. Definir o Tabuleiro e posicionar alguns navios para o contexto.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializar_tabuleiro(tabuleiro);
    
    // Posicionando um navio para que as habilidades possam interagir com ele
    tabuleiro[4][4] = NAVIO;
    tabuleiro[4][5] = NAVIO;
    tabuleiro[4][6] = NAVIO;
    
    printf("Tabuleiro inicial com um navio posicionado:\n");
    exibir_tabuleiro_final(tabuleiro);
    printf("\n");

    // 2. Criar Matrizes de Habilidade
    // As matrizes são declaradas aqui e preenchidas pelas funções.
    int matriz_cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matriz_cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int matriz_octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    // As funções preenchem as matrizes usando loops e condicionais, como pedido.
    criar_matriz_cone(matriz_cone);
    criar_matriz_cruz(matriz_cruz);
    criar_matriz_octaedro(matriz_octaedro);
    
    // 3. Integrar Habilidades ao Tabuleiro
    printf("Aplicando habilidades especiais no tabuleiro...\n\n");
    
    // Define um ponto de origem para cada habilidade e a aplica no tabuleiro.
    // O ponto de origem é onde o centro da matriz de habilidade será colocado.
    aplicar_habilidade(tabuleiro, 2, 2, matriz_cone);      // Cone no canto superior esquerdo
    aplicar_habilidade(tabuleiro, 7, 7, matriz_cruz);      // Cruz no canto inferior direito
    aplicar_habilidade(tabuleiro, 4, 5, matriz_octaedro);  // Octaedro centralizado no navio
    

    // 4. Exibir o Tabuleiro com Habilidades
    printf("===== TABULEIRO FINAL COM HABILIDADES APLICADAS =====\n");
    exibir_tabuleiro_final(tabuleiro);

    return 0;
}


// ============================================================================
// FUNÇÕES DE CRIAÇÃO DE HABILIDADES
// ============================================================================

/**
 * @brief Cria uma matriz 5x5 representando uma área em forma de cone.
 * A forma é gerada dinamicamente com base em condicionais.
 * Exemplo (1 = área afetada):
 * 0 0 1 0 0
 * 0 1 1 1 0
 * 1 1 1 1 1
 * 0 0 0 0 0 (não faz parte do cone 3x5)
 * 0 0 0 0 0
 */
void criar_matriz_cone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A largura do cone na linha 'i' é '2*i + 1'.
            // A condição verifica se a coluna 'j' está dentro dessa largura,
            // centralizada na matriz.
            if (i <= centro && j >= centro - i && j <= centro + i) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria uma matriz 5x5 representando uma área em forma de cruz.
 * A forma é gerada dinamicamente com base em condicionais.
 * Exemplo (1 = área afetada):
 * 0 0 1 0 0
 * 0 0 1 0 0
 * 1 1 1 1 1
 * 0 0 1 0 0
 * 0 0 1 0 0
 */
void criar_matriz_cruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // A condição verifica se a célula está na linha central OU na coluna central.
            if (i == centro || j == centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

/**
 * @brief Cria uma matriz 5x5 representando um octaedro (losango).
 * Utiliza a distância de Manhattan para gerar a forma dinamicamente.
 * Exemplo (1 = área afetada):
 * 0 0 1 0 0
 * 0 1 1 1 0
 * 1 1 1 1 1
 * 0 1 1 1 0
 * 0 0 1 0 0
 */
void criar_matriz_octaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            // Distância de Manhattan: |x1 - x2| + |y1 - y2|
            // Se a distância da célula (i, j) ao centro for menor ou igual ao raio (centro),
            // ela pertence ao losango.
            if (abs(i - centro) + abs(j - centro) <= centro) {
                matriz[i][j] = 1;
            } else {
                matriz[i][j] = 0;
            }
        }
    }
}

// ============================================================================
// FUNÇÕES DE LÓGICA E EXIBIÇÃO
// ============================================================================

/**
 * @brief Sobrepõe a matriz de habilidade ao tabuleiro principal.
 * @param tabuleiro O tabuleiro principal 10x10.
 * @param origem_linha A linha do tabuleiro onde o centro da habilidade será aplicado.
 * @param origem_coluna A coluna do tabuleiro onde o centro da habilidade será aplicado.
 * @param habilidade_matriz A matriz 5x5 da habilidade a ser aplicada.
 */
void aplicar_habilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int origem_linha, int origem_coluna, int habilidade_matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro_habilidade = TAMANHO_HABILIDADE / 2;

    // Percorre a matriz da habilidade
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            
            // Verifica se esta parte da habilidade deve ser aplicada (valor 1)
            if (habilidade_matriz[i][j] == 1) {
                // Calcula a posição alvo no tabuleiro principal.
                // A fórmula converte as coordenadas da matriz de habilidade (i, j)
                // para as coordenadas do tabuleiro principal.
                int alvo_linha = origem_linha - centro_habilidade + i;
                int alvo_coluna = origem_coluna - centro_habilidade + j;

                // **Validação de Limites**: Garante que não vamos escrever fora do tabuleiro.
                if (alvo_linha >= 0 && alvo_linha < TAMANHO_TABULEIRO &&
                    alvo_coluna >= 0 && alvo_coluna < TAMANHO_TABULEIRO) {
                    
                    // Marca a posição no tabuleiro principal com o marcador da habilidade.
                    tabuleiro[alvo_linha][alvo_coluna] = AREA_HABILIDADE;
                }
            }
        }
    }
}


void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

/**
 * @brief Exibe o tabuleiro com caracteres visuais para cada tipo de célula.
 */
void exibir_tabuleiro_final(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("    0 1 2 3 4 5 6 7 8 9\n");
    printf("  -----------------------\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d | ", i); // Imprime o índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            char simbolo;
            switch (tabuleiro[i][j]) {
                case AGUA:            simbolo = '~'; break; // Água
                case NAVIO:           simbolo = 'N'; break; // Navio
                case AREA_HABILIDADE: simbolo = '*'; break; // Área de efeito
                default:              simbolo = '?'; break; // Valor inesperado
            }
            printf("%c ", simbolo);
        }
        printf("|\n");
    }
     printf("  -----------------------\n");
}