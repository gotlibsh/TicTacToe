#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "ttt_utils.h"


uint8_t static_evaluation(ttt_board* board)
{
    if (IS_WON(board->x_board)) return 1;
    if (IS_WON(board->o_board)) return -1;

    return 0;
}

void get_child_boards(ttt_board* board, ttt_board* child_boards, piece piece, uint8_t* child_count)
{
    uint8_t cell;
    uint8_t child_index = 0;


    *child_count = 0;
    if (is_game_over(board))
    {
        return;
    }

    for(cell = 1; cell <= BOARD_SIZE; cell++)
    {
        if (get_piece(board, cell) == EMPTY)
        {
            child_boards[child_index] = *board;
            set_piece(&child_boards[child_index], cell, piece);
            child_index++;
        }
    }

    *child_count = child_index;
}

uint64_t nodes_visited = 0;
node_result minimax(ttt_board* board, uint16_t depth, piece piece, bool is_maximizer)
{
    node_result result = {0};
    ttt_board child_boards[BOARD_SIZE];
    uint8_t child_count = 0;
    score_t peak_eval = is_maximizer ? MIN_SCORE : MAX_SCORE;
    uint8_t index_of_peak = -1;
    uint8_t i = 0;


    if (depth == 0)
    {
        result.child_index = -1;
        result.eval = static_evaluation(board);
        nodes_visited++;
        return result;
    }

    get_child_boards(board, child_boards, piece, &child_count);

    if (child_count == 0)
    {
        result.child_index = -1;
        result.eval = static_evaluation(board);
        nodes_visited++;
        return result;
    }

    nodes_visited += child_count;

    for(; i < child_count; i++)
    {
        result = minimax(&child_boards[i], depth - 1, OPP_PIECE(piece), !is_maximizer);
        
        if (is_maximizer)
        {
            if (result.eval > peak_eval)
            {
                peak_eval = result.eval;
                index_of_peak = i;
            }
        }
        else
        {
            if (result.eval < peak_eval)
            {
                peak_eval = result.eval;
                index_of_peak = i;
            }
        }
    }

    result.eval = peak_eval;
    result.child_index = index_of_peak;

    return result;
}

void set_next_move(ttt_board* board, uint8_t child_index, piece piece)
{
    ttt_board child_boards[BOARD_SIZE];
    uint8_t child_count = 0;


    get_child_boards(board, child_boards, piece, &child_count);

    assert(child_count != 0);

    *board = child_boards[child_index];
}

void play(bool machine_turn)
{
    ttt_board board = {0};
    node_result res = {0};
    uint16_t depth = 8;
    piece piece = X;
    bool is_maximizer = true;
    uint8_t move_count = 0;
    uint8_t human_move;


    while(!is_game_over(&board))
    {
        if (machine_turn)
        {
            res = minimax(&board, BOARD_SIZE - move_count, piece, is_maximizer);
            set_next_move(&board, res.child_index, piece);
        }
        else
        {
            do
            {
                printf("enter cell location (1-9): ");
                scanf_s("%hhd", &human_move);
            } while(get_piece(&board, human_move) != EMPTY);

            set_piece(&board, human_move, piece);
        }
        
        printf("player: %s\n", PIECE_STR(piece));
        printf("eval: %d\n", res.eval);
        printf("board after move: %d\n", move_count + 1);
        print_board(&board);
        printf("\n");

        piece = OPP_PIECE(piece);
        is_maximizer = !is_maximizer;
        machine_turn = !machine_turn;
        move_count++;
    }

    printf("Game over!\n");
    
    if (IS_WON(board.x_board))
        printf("X player won!\n");
    else if (IS_WON(board.o_board))
        printf("O player won!\n");
    else
        printf("Draw!\n");

    printf("\nnodes-visited: %llu\n", nodes_visited);
}

// defined in tester.c
extern void run_tests();

int main(int argc, char* argv[])
{
    if(argc == 1)
    {
        play(false);
    }
    else if(argc == 2)
    {
        if (strcmp(argv[1], "test") == 0)
        {
            run_tests();
            printf("Tests Passed\n");
            return 0;
        }
        else
        {
            printf("Usage: %s [test]\n", argv[0]);
            return 1;
        }
    }
    else
    {
        printf("Usage: %s [test]\n", argv[0]);
        return 1;
    }
}