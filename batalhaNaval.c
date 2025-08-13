#include <stdio.h>
#include <stdbool.h> // Necessário para usar o tipo de dado bool (true/false)

// --- Requisitos não funcionais: Legibilidade e Manutenção ---
// Utilizar constantes torna o código mais fácil de ler e modificar.
// Se quisermos um tabuleiro 15x15 no futuro, só precisamos mudar este valor.
#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// --- Protótipos das Funções (boa prática para organizar o código) ---
void inicializar_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]);
bool validar_posicao(int linha, int coluna, int tamanho, bool eh_vertical);
bool verificar_sobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, bool eh_vertical);


int main() {
    // --- 1. Represente o Tabuleiro ---
    // Declara a matriz 10x10 para o nosso jogo.
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];

    // Inicializa todo o tabuleiro com 0 (água).
    inicializar_tabuleiro(tabuleiro);

    // --- 2. Posicione os Navios ---
    // Coordenadas definidas diretamente no código, como pedido no desafio.
    // Navio 1: Horizontal
    int navio_h_linha = 2;
    int navio_h_coluna = 2;

    // Navio 2: Vertical
    int navio_v_linha = 5;
    int navio_v_coluna = 5;

    // --- Validações e Posicionamento do Navio Horizontal ---
    printf("Tentando posicionar navio horizontal na linha %d, coluna %d.\n", navio_h_linha, navio_h_coluna);
    if (validar_posicao(navio_h_linha, navio_h_coluna, TAMANHO_NAVIO, false)) {
        // Se a posição é válida, posiciona o navio.
        // O loop percorre as colunas para posicionar o navio horizontalmente.
        for (int i = 0; i < TAMANHO_NAVIO; i++) {
            tabuleiro[navio_h_linha][navio_h_coluna + i] = 3;
        }
        printf("Navio horizontal posicionado com sucesso!\n\n");
    } else {
        printf("Erro: Posição do navio horizontal fora do tabuleiro!\n\n");
    }

    // --- Validações e Posicionamento do Navio Vertical ---
    printf("Tentando posicionar navio vertical na linha %d, coluna %d.\n", navio_v_linha, navio_v_coluna);
    if (validar_posicao(navio_v_linha, navio_v_coluna, TAMANHO_NAVIO, true)) {
        // Valida se não há sobreposição com navios já existentes.
        if (!verificar_sobreposicao(tabuleiro, navio_v_linha, navio_v_coluna, TAMANHO_NAVIO, true)) {
            // Se a posição é válida e não há sobreposição, posiciona o navio.
            // O loop percorre as linhas para posicionar o navio verticalmente.
            for (int i = 0; i < TAMANHO_NAVIO; i++) {
                tabuleiro[navio_v_linha + i][navio_v_coluna] = 3;
            }
            printf("Navio vertical posicionado com sucesso!\n\n");
        } else {
            printf("Erro: Sobreposição detectada na posição do navio vertical!\n\n");
        }
    } else {
        printf("Erro: Posição do navio vertical fora do tabuleiro!\n\n");
    }


    // --- 3. Exiba o Tabuleiro ---
    printf("===== TABULEIRO DE BATALHA NAVAL =====\n");
    exibir_tabuleiro(tabuleiro);

    return 0;
}

/**
 * @brief Preenche o tabuleiro com 0 (água).
 * @param tabuleiro A matriz do jogo.
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
 * @param tabuleiro A matriz do jogo.
 */
void exibir_tabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    // Imprime cabeçalho das colunas para melhor visualização
    printf("  "); // Espaço para o alinhamento das linhas
    for(int i = 0; i < TAMANHO_TABULEIRO; i++){
        printf("%d ", i);
    }
    printf("\n");

    // Loops aninhados para percorrer a matriz.
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        printf("%d ", i); // Imprime o índice da linha
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            // Imprime o valor da célula (0 para água, 3 para navio)
            printf("%d ", tabuleiro[i][j]);
        }
        // Pula para a próxima linha no console ao final de cada linha da matriz.
        printf("\n");
    }
}

/**
 * @brief Valida se um navio cabe nos limites do tabuleiro.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param tamanho O tamanho do navio.
 * @param eh_vertical Verdadeiro se o navio for vertical, falso se for horizontal.
 * @return Retorna true se a posição for válida, false caso contrário.
 */
bool validar_posicao(int linha, int coluna, int tamanho, bool eh_vertical) {
    if (eh_vertical) {
        // Para um navio vertical, a linha + tamanho não pode exceder o limite do tabuleiro.
        return (linha + tamanho) <= TAMANHO_TABULEIRO;
    } else {
        // Para um navio horizontal, a coluna + tamanho não pode exceder o limite.
        return (coluna + tamanho) <= TAMANHO_TABULEIRO;
    }
}

/**
 * @brief Verifica se a posição de um novo navio se sobrepõe a um já existente.
 * @param tabuleiro A matriz do jogo.
 * @param linha A linha inicial do navio.
 * @param coluna A coluna inicial do navio.
 * @param tamanho O tamanho do navio.
 * @param eh_vertical Verdadeiro se o navio for vertical, falso se for horizontal.
 * @return Retorna true se houver sobreposição, false caso contrário.
 */
bool verificar_sobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, int tamanho, bool eh_vertical) {
    // Percorre as posições que o novo navio ocuparia.
    for(int i = 0; i < tamanho; i++){
        if (eh_vertical) {
            // Se em alguma das futuras posições verticais já existir algo diferente de 0, há sobreposição.
            if(tabuleiro[linha + i][coluna] != 0) return true;
        } else {
            // Se em alguma das futuras posições horizontais já existir algo diferente de 0, há sobreposição.
            if(tabuleiro[linha][coluna + i] != 0) return true;
        }
    }
    // Se o loop terminar sem encontrar nada, não há sobreposição.
    return false;
}