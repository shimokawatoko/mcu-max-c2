/*
 * mcu-max UCI chess interface example
 *
 * (C) 2022-2024 Gissio
 *
 * License: MIT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mcu-max.h"
#include "mcumax_state.h"
#include "mcumax_debug.h"

#define MAIN_VALID_MOVES_NUM 512

void print_board()
{
    const char *symbols = ".PPNKBRQ.ppnkbrq";

    printf("  +-----------------+\n");

    for (uint32_t y = 0; y < 8; y++)
    {
        printf("%d | ", 8 - y);
        for (uint32_t x = 0; x < 8; x++)
            printf("%c ", symbols[mcumax_get_piece(0x10 * y + x)]);
        printf("|\n");
    }

    printf("  +-----------------+\n");
    printf("    a b c d e f g h\n");

    printf("\n");
}

mcumax_square get_square(char *s)
{
    mcumax_square rank = s[0] - 'a';
    if (rank > 7)
        return MCUMAX_SQUARE_INVALID;

    mcumax_square file = '8' - s[1];
    if (file > 7)
        return MCUMAX_SQUARE_INVALID;

    return 0x10 * file + rank;
}

bool is_square_valid(char *s)
{
    return (get_square(s) != MCUMAX_SQUARE_INVALID);
}

bool is_move_valid(char *s)
{
    return is_square_valid(s) && is_square_valid(s + 2);
}

void print_square(mcumax_square square)
{
    printf("%c%c",
           'a' + ((square & 0x07) >> 0),
           '1' + 7 - ((square & 0x70) >> 4));
}

void print_move(mcumax_move move)
{
    if ((move.from == MCUMAX_SQUARE_INVALID) ||
        (move.to == MCUMAX_SQUARE_INVALID))
        printf("(none)");
    else
    {
        print_square(move.from);
        print_square(move.to);
    }
}

bool send_uci_command(char *line)
{
    char *token = strtok(line, " \n");

    if (!token)
        return false;

    if (!strcmp(token, "uci"))
    {
        printf("id name " MCUMAX_ID "\n");
        printf("id author " MCUMAX_AUTHOR "\n");
        printf("uciok\n");
    }
    else if (!strcmp(token, "uci") ||
             !strcmp(token, "ucinewgame"))
        mcumax_init();
    else if (!strcmp(token, "isready"))
        printf("readyok\n");
    else if (!strcmp(token, "d"))
        print_board();
    else if (!strcmp(token, "l"))
    {
        mcumax_move valid_moves[MAIN_VALID_MOVES_NUM];
        uint32_t valid_moves_num = mcumax_search_valid_moves(valid_moves, MAIN_VALID_MOVES_NUM);

        for (uint32_t i = 0; i < valid_moves_num; i++)
        {
            print_move(valid_moves[i]);
            printf(" ");
        }
        printf("\n");
    }
    else if (!strcmp(token, "position"))
    {
        int fen_index = 0;
        char fen_string[256];

        while (token = strtok(NULL, " \n"))
        {
            if (fen_index)
            {
                strcat(fen_string, token);
                strcat(fen_string, " ");

                fen_index++;
                if (fen_index > 6)
                {
                    mcumax_set_fen_position(fen_string);

                    fen_index = 0;
                }
            }
            else
            {
                if (!strcmp(token, "startpos"))
                    mcumax_init();
                else if (!strcmp(token, "fen"))
                {
                    fen_index = 1;
                    strcpy(fen_string, "");
                }
                else if (is_move_valid(token))
                {
                    mcumax_play_move((mcumax_move){
                        get_square(token + 0),
                        get_square(token + 2),
                    });
                }
            }
        }
        // 局面設定後に評価値をログ出力
        mcumax_log_evaluation("position_evaluation.log");
    }
    else if (!strcmp(token, "go"))
    {
        uint32_t node_max = 500000;   // 探索の最大ノード数
        uint32_t depth_max = 10;      // 最大探索深さ

        // 探索前の評価値をログ出力
        mcumax_log_evaluation("before_search.log");

        // 時間計測開始
        clock_t start_time = clock();

        // 探索前に深さと探索ノード数をリセット
        mcumax.current_depth = 0;
        mcumax.node_count = 0;

        mcumax_print_memory_info();
        
        mcumax_move move = mcumax_search_best_move(node_max, depth_max);
        mcumax_play_move(move);
        
        mcumax_print_memory_info();

        // 時間計測終了
        clock_t end_time = clock();

        // 探索後の評価値をログ出力
        mcumax_log_evaluation("after_search.log");

        // ログファイルにノード情報を出力
        FILE *log_file = fopen("search_log.txt", "a");
        if (log_file != NULL) {
            double search_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

            fprintf(log_file, "検索情報:\n");
            fprintf(log_file, "  最善手: ");
            print_move(move);
            fprintf(log_file, "\n");
            fprintf(log_file, "  探索時間: %.3f秒\n", search_time);
            fprintf(log_file, "  最大探索ノード数: %u\n", node_max);
            fprintf(log_file, "  実際の探索ノード数: %u\n", mcumax_get_node_count());  // 実際のノード数
            fprintf(log_file, "  最大探索深さ: %u\n\n", depth_max);
            fprintf(log_file, "  実際の最大探索深さ: %u\n\n", mcumax_get_max_depth());

            fclose(log_file);
        }


        printf("bestmove ");
        print_move(move);
        printf("\n");
    }
    else if (!strcmp(token, "quit"))
        return true;
    else
        printf("Unknown command: %s\n", token);

    return false;
}

int main()
{
    mcumax_init();

    while (true)
    {
        fflush(stdout);

        char line[65536];
        fgets(line, sizeof(line), stdin);

        if (send_uci_command(line))
            break;
    }
}
