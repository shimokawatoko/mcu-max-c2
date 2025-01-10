// mcumax_debug.c
#include <stdio.h>
#include <stdint.h>
#include "mcumax_debug.h"
#include "mcumax_state.h"
#include "mcu-max.h"  // マクロ定義のために追加

// 構造体の再定義を削除し、外部参照のみを残す
extern struct mcumax_state mcumax;

void mcumax_log_evaluation(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) return;

    fprintf(fp, "Current position evaluation:\n");
    fprintf(fp, "Total score: %d\n", mcumax.score);
    
    fprintf(fp, "\nPiece positions and values:\n");
    for (int y = 0; y < 8; y++) {
        for (int x = 0; x < 8; x++) {
            uint8_t square = y * 16 + x;
            uint8_t piece = mcumax.board[square];
            int8_t position_value = mcumax.board[square + 8];
            
            fprintf(fp, "Square %c%d: ", 'a' + x, 8 - y);
            
            if (piece & MCUMAX_BOARD_WHITE) 
                fprintf(fp, "White ");
            else if (piece & MCUMAX_BOARD_BLACK)
                fprintf(fp, "Black ");
            
            switch (piece & 0x7) {
                case MCUMAX_EMPTY: fprintf(fp, "Empty"); break;
                case MCUMAX_PAWN_UPSTREAM: 
                case MCUMAX_PAWN_DOWNSTREAM: fprintf(fp, "Pawn"); break;
                case MCUMAX_KNIGHT: fprintf(fp, "Knight"); break;
                case MCUMAX_KING: fprintf(fp, "King"); break;
                case MCUMAX_BISHOP: fprintf(fp, "Bishop"); break;
                case MCUMAX_ROOK: fprintf(fp, "Rook"); break;
                case MCUMAX_QUEEN: fprintf(fp, "Queen"); break;
            }
            
            fprintf(fp, " Position value: %d\n", position_value);
        }
        fprintf(fp, "\n");
    }

    fprintf(fp, "Total non-pawn material: %d\n", mcumax.non_pawn_material);
    
    fclose(fp);
}