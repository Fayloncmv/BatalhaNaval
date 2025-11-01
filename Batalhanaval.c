#include <stdio.h>
#include <stdlib.h> 


#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define AGUA 0
#define NAVIO 3
#define AREA 5

// Tamanho das matrizes de habilidade (usar um tamanho ímpar facilita o "centro")
#define HABILIDADE_TAM 5

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO];
    int areaOverlay[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]; // marca se alguma habilidade afeta a posição (0/1)

    // 1) Inicializa tabuleiro e overlay (tudo água / sem área)
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            tabuleiro[i][j] = AGUA;
            areaOverlay[i][j] = 0;
        }
    }

    // --------------------------
    // 2) Posiciona 4 navios (tamanho 3) - exemplo de coordenadas fixas
    // Dois retos (horizontal e vertical) e dois diagonais (? e ?)
    // Essas coordenadas podem ser alteradas diretamente no código conforme necessidade.
    // Garantimos que não haja sobreposição ao posicionar cada navio.
    // --------------------------

    // Função auxiliar simulada aqui: adicionamos manualmente com checagens simples.

    // Navio 1 - Horizontal (linha 2, coluna 3)
    int r1 = 2, c1 = 3;
    if (c1 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int ok = 1;
        for (int k = 0; k < TAMANHO_NAVIO; k++)
            if (tabuleiro[r1][c1 + k] == NAVIO) ok = 0;
        if (!ok) { printf("Erro: sobreposicao ao posicionar navio 1\n"); return 1; }
        for (int k = 0; k < TAMANHO_NAVIO; k++) tabuleiro[r1][c1 + k] = NAVIO;
    } else { printf("Erro: navio 1 fora dos limites\n"); return 1; }

    // Navio 2 - Vertical (linha 5, coluna 7)
    int r2 = 5, c2 = 7;
    if (r2 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int ok = 1;
        for (int k = 0; k < TAMANHO_NAVIO; k++)
            if (tabuleiro[r2 + k][c2] == NAVIO) ok = 0;
        if (!ok) { printf("Erro: sobreposicao ao posicionar navio 2\n"); return 1; }
        for (int k = 0; k < TAMANHO_NAVIO; k++) tabuleiro[r2 + k][c2] = NAVIO;
    } else { printf("Erro: navio 2 fora dos limites\n"); return 1; }

    // Navio 3 - Diagonal principal (?) começando em (0,0)
    int r3 = 0, c3 = 0;
    if (r3 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && c3 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO) {
        int ok = 1;
        for (int k = 0; k < TAMANHO_NAVIO; k++)
            if (tabuleiro[r3 + k][c3 + k] == NAVIO) ok = 0;
        if (!ok) { printf("Erro: sobreposicao ao posicionar navio 3\n"); return 1; }
        for (int k = 0; k < TAMANHO_NAVIO; k++) tabuleiro[r3 + k][c3 + k] = NAVIO;
    } else { printf("Erro: navio 3 fora dos limites\n"); return 1; }

    // Navio 4 - Diagonal secundária (?) começando em (0,9) -> (0,9),(1,8),(2,7)
    int r4 = 0, c4 = 9;
    if (r4 + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && c4 - (TAMANHO_NAVIO - 1) >= 0) {
        int ok = 1;
        for (int k = 0; k < TAMANHO_NAVIO; k++)
            if (tabuleiro[r4 + k][c4 - k] == NAVIO) ok = 0;
        if (!ok) { printf("Erro: sobreposicao ao posicionar navio 4\n"); return 1; }
        for (int k = 0; k < TAMANHO_NAVIO; k++) tabuleiro[r4 + k][c4 - k] = NAVIO;
    } else { printf("Erro: navio 4 fora dos limites\n"); return 1; }

    // --------------------------
    // 3) Construir dinamicamente as matrizes de habilidade (HABILIDADE_TAM x HABILIDADE_TAM)
    // Requisito: usar loops aninhados e condicionais para montar cada matriz com 0/1.
    // O "centro" da matriz é (meio, meio) onde meio = HABILIDADE_TAM/2.
    // --------------------------

    int cone[HABILIDADE_TAM][HABILIDADE_TAM];
    int cruz[HABILIDADE_TAM][HABILIDADE_TAM];
    int octaedro[HABILIDADE_TAM][HABILIDADE_TAM];

    int meio = HABILIDADE_TAM / 2; // ex: 5 -> meio = 2

    // 3.1) Cone apontando para baixo: 
    // definição usada aqui: a "ponta" do cone é o centro (meio,meio),
    // em seguida cada linha abaixo do centro expande em largura (manhattan style).
    // Ex.: para HABILIDADE_TAM=5 (linhas 0..4), as linhas relevantes serão:
    // row meio (ponta): apenas coluna meio = 1
    // row meio+1: col meio-1 .. meio+1 = 1
    // row meio+2: col meio-2 .. meio+2 = 1
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            cone[i][j] = 0; // default não afetado
            int dr = i - meio; // deslocamento em linhas relativo ao centro
            int dc = j - meio; // deslocamento em colunas relativo ao centro

            // condição: queremos células abaixo (dr >= 0) cuja largura cresce com dr
            if (dr >= 0) {
                // largura permitida = dr (ex: dr=0 -> only center; dr=1 -> center +/-1; dr=2 -> center +/-2)
                if ( (dc >= -dr) && (dc <= dr) ) {
                    cone[i][j] = 1;
                }
            }
        }
    }

    // 3.2) Cruz: afetar linha central e coluna central (como um +)
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (i == meio || j == meio) cruz[i][j] = 1;
            else cruz[i][j] = 0;
        }
    }

    // 3.3) Octaedro (vista frontal -> losango/diamante):
    // condição: |dr| + |dc| <= raio, onde raio = meio
    // isso gera um losango centrado.
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            int dr = abs(i - meio);
            int dc = abs(j - meio);
            if (dr + dc <= meio) octaedro[i][j] = 1;
            else octaedro[i][j] = 0;
        }
    }

    // (Opcional) -- se quiser, podemos imprimir as matrizes de habilidade para depuração:
    /*
    printf("\nMATRIZ CONE (1 = afetado):\n");
    for (int i=0;i<HABILIDADE_TAM;i++){ for(int j=0;j<HABILIDADE_TAM;j++) printf("%d ", cone[i][j]); printf("\n"); }
    printf("\nMATRIZ CRUZ (1 = afetado):\n");
    for (int i=0;i<HABILIDADE_TAM;i++){ for(int j=0;j<HABILIDADE_TAM;j++) printf("%d ", cruz[i][j]); printf("\n"); }
    printf("\nMATRIZ OCTAEDRO (1 = afetado):\n");
    for (int i=0;i<HABILIDADE_TAM;i++){ for(int j=0;j<HABILIDADE_TAM;j++) printf("%d ", octaedro[i][j]); printf("\n"); }
    */

    // --------------------------
    // 4) Definir pontos de origem no tabuleiro (coordenadas fixas no código)
    // Cada ponto será o centro da matriz de habilidade ao ser sobreposta.
    // --------------------------
    int origemConeR = 4, origemConeC = 4;     // exemplo: cone centrado em (4,4)
    int origemCruzR = 1, origemCruzC = 8;     // cruz centrada em (1,8)
    int origemOctR = 7, origemOctC = 5;       // octaedro centrado em (7,5)

    // 5) Sobrepor cada matriz de habilidade ao tabuleiro, atualizando areaOverlay.
    //    Usamos condicionais para garantir que não saímos dos limites do tabuleiro.
    //    areaOverlay[pos] = 1 se qualquer habilidade afetar a posição.

    // Helper: função conceptual (implementada inline) para aplicar uma matriz.
    // Para cada célula (i,j) da matriz de habilidade:
    //  mapaRow = origemR - meio + i
    //  mapaCol = origemC - meio + j
    //  se dentro dos limites e matriz[i][j] == 1 -> areaOverlay[mapaRow][mapaCol] = 1

    // Aplicar CONE
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (cone[i][j] == 1) {
                int mapaR = origemConeR - meio + i;
                int mapaC = origemConeC - meio + j;
                if (mapaR >= 0 && mapaR < TAMANHO_TABULEIRO && mapaC >= 0 && mapaC < TAMANHO_TABULEIRO) {
                    areaOverlay[mapaR][mapaC] = 1;
                }
            }
        }
    }

    // Aplicar CRUZ
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (cruz[i][j] == 1) {
                int mapaR = origemCruzR - meio + i;
                int mapaC = origemCruzC - meio + j;
                if (mapaR >= 0 && mapaR < TAMANHO_TABULEIRO && mapaC >= 0 && mapaC < TAMANHO_TABULEIRO) {
                    areaOverlay[mapaR][mapaC] = 1;
                }
            }
        }
    }

    // Aplicar OCTAEDRO
    for (int i = 0; i < HABILIDADE_TAM; i++) {
        for (int j = 0; j < HABILIDADE_TAM; j++) {
            if (octaedro[i][j] == 1) {
                int mapaR = origemOctR - meio + i;
                int mapaC = origemOctC - meio + j;
                if (mapaR >= 0 && mapaR < TAMANHO_TABULEIRO && mapaC >= 0 && mapaC < TAMANHO_TABULEIRO) {
                    areaOverlay[mapaR][mapaC] = 1;
                }
            }
        }
    }

    // --------------------------
    // 6) Exibir o tabuleiro final no console.
    // Regras de exibição (prioridade):
    //  - Se há um NAVIO (3) naquela célula -> imprima 3 (mantemos navio visível)
    //  - Senão, se areaOverlay == 1 -> imprima 5 (área afetada)
    //  - Senão -> imprima 0 (água)
    // --------------------------

    printf("\n=== TABULEIRO COM NAVIOS (3) E AREAS DE HABILIDADE (5) ===\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == NAVIO) {
                printf("%d ", NAVIO);             // mantém navio visível mesmo se área também afetou
            } else if (areaOverlay[i][j] == 1) {
                printf("%d ", AREA);              // área afetada (quando não há navio)
            } else {
                printf("%d ", AGUA);              // água
            }
        }
        printf("\n");
    }

    // Observação: se preferir PRIORIDADE que mostra área sobre navio (ou um valor combinado),
    // podemos ajustar a regra acima para imprimir AREA mesmo se houver NAVIO.

    return 0;
}

