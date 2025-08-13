#include <stdio.h>
#include <stdbool.h>

// --- Constantes Globais ---
// Definir constantes ajuda na legibilidade e manutenção do código.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// --- Tipos de Dados Personalizados ---
/**
 * @brief Enumeração para representar as diferentes orientações possíveis de um navio.
 * Usar um enum é mais claro e seguro do que usar números ou booleanos.
 */
typedef enum {
    HORIZONTAL,
    VERTICAL,
    DIAGONAL_PRINCIPAL,  // Navio desce da esquerda para a direita.
    DIAGONAL_SECUNDARIA  // Navio desce da direita para a esquerda.
} Orientacao;


// --- Protótipos das Funções ---
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool validar_posicao(int linha, int coluna, int tamanho, Orientacao orientacao);
bool verificar_sobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, Orientacao orientacao);
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, Orientacao orientacao);
void tentar_posicionar_um_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, Orientacao orientacao, const char* nome_navio);


int main() {
    // 1. Criar um Tabuleiro 10x10 e inicializá-lo com 0 (água).
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    inicializar_tabuleiro(tabuleiro);
    printf("Tabuleiro 10x10 inicializado com água (0).\n\n");

    // 2. Posicionar Quatro Navios (coordenadas e orientações definidas no código)
    // Para simplificar o processo de validação e posicionamento, criei uma função
    // chamada "tentar_posicionar_um_navio" que faz todo o trabalho.
    tentar_posicionar_um_navio(tabuleiro, 1, 1, HORIZONTAL, "Navio Horizontal");
    tentar_posicionar_um_navio(tabuleiro, 3, 8, VERTICAL, "Navio Vertical");
    tentar_posicionar_um_navio(tabuleiro, 5, 1, DIAGONAL_PRINCIPAL, "Navio Diagonal Principal");
    tentar_posicionar_um_navio(tabuleiro, 1, 8, DIAGONAL_SECUNDARIA, "Navio Diagonal Secundária");

    // 3. Exibir o Tabuleiro
    printf("===== TABULEIRO FINAL DE BATALHA NAVAL =====\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Tenta posicionar um navio no tabuleiro, realizando todas as validações necessárias.
 * @param tabuleiro A matriz do jogo.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param orientacao A orientação do navio (HORIZONTAL, VERTICAL, etc.).
 * @param nome_navio Uma string para identificar o navio nos logs.
 */
void tentar_posicionar_um_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, Orientacao orientacao, const char* nome_navio) {
    printf("Tentando posicionar '%s' na linha %d, coluna %d...\n", nome_navio, linha, coluna);

    // Valida se o navio cabe nos limites do tabuleiro.
    if (!validar_posicao(linha, coluna, TAMANHO_NAVIO, orientacao)) {
        printf("ERRO: Posição do '%s' fora dos limites do tabuleiro!\n\n", nome_navio);
        return; // Encerra a função se a posição for inválida.
    }

    // Valida se o navio não se sobrepõe a outro já existente.
    if (verificar_sobreposicao(tabuleiro, linha, coluna, TAMANHO_NAVIO, orientacao)) {
        printf("ERRO: Sobreposição detectada na posição do '%s'!\n\n", nome_navio);
        return; // Encerra a função se houver sobreposição.
    }

    // Se todas as validações passaram, posiciona o navio.
    posicionar_navio(tabuleiro, linha, coluna, TAMANHO_NAVIO, orientacao);
    printf("'%s' posicionado com sucesso!\n\n", nome_navio);
}

/**
 * @brief Valida se um navio cabe nos limites do tabuleiro.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param tamanho O tamanho do navio.
 * @param orientacao A orientação do navio.
 * @return Retorna true se a posição for válida, false caso contrário.
 */
bool validar_posicao(int linha, int coluna, int tamanho, Orientacao orientacao) {
    switch (orientacao) {
        case HORIZONTAL:
            return (coluna + tamanho) <= TAMANHO_TABULEIRO;
        case VERTICAL:
            return (linha + tamanho) <= TAMANHO_TABULEIRO;
        case DIAGONAL_PRINCIPAL:
            // Precisa caber tanto na vertical quanto na horizontal.
            return (linha + tamanho) <= TAMANHO_TABULEIRO && (coluna + tamanho) <= TAMANHO_TABULEIRO;
        case DIAGONAL_SECUNDARIA:
            // Precisa caber na vertical e não pode "sair" pela esquerda.
            return (linha + tamanho) <= TAMANHO_TABULEIRO && (coluna - tamanho + 1) >= 0;
    }
    return false; // Caso padrão
}

/**
 * @brief Verifica se a posição de um novo navio se sobrepõe a um já existente.
 * @param tabuleiro A matriz do jogo.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param tamanho O tamanho do navio.
 * @param orientacao A orientação do navio.
 * @return Retorna true se houver sobreposição, false caso contrário.
 */
bool verificar_sobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, Orientacao orientacao) {
    for (int i = 0; i < tamanho; i++) {
        switch (orientacao) {
            case HORIZONTAL:
                if (tabuleiro[linha][coluna + i] != 0) return true;
                break;
            case VERTICAL:
                if (tabuleiro[linha + i][coluna] != 0) return true;
                break;
            case DIAGONAL_PRINCIPAL:
                // Posição: (linha+0, coluna+0), (linha+1, coluna+1), ...
                if (tabuleiro[linha + i][coluna + i] != 0) return true;
                break;
            case DIAGONAL_SECUNDARIA:
                 // Posição: (linha+0, coluna-0), (linha+1, coluna-1), ...
                if (tabuleiro[linha + i][coluna - i] != 0) return true;
                break;
        }
    }
    return false; // Nenhuma sobreposição encontrada
}

/**
 * @brief Posiciona o navio (valor 3) no tabuleiro nas coordenadas corretas.
 * @param tabuleiro A matriz do jogo.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param tamanho O tamanho do navio.
 * @param orientacao A orientação do navio.
 */
void posicionar_navio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, Orientacao orientacao) {
     for (int i = 0; i < tamanho; i++) {
        switch (orientacao) {
            case HORIZONTAL:
                tabuleiro[linha][coluna + i] = 3;
                break;
            case VERTICAL:
                tabuleiro[linha + i][coluna] = 3;
                break;
            case DIAGONAL_PRINCIPAL:
                tabuleiro[linha + i][coluna + i] = 3;
                break;
            case DIAGONAL_SECUNDARIA:
                tabuleiro[linha + i][coluna - i] = 3;
                break;
        }
    }
}

/**
 * @brief Preenche o tabuleiro com 0 (água).
 */
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

/**
 * @brief Exibe o estado atual do tabuleiro no console.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("  ");
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}