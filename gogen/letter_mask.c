#include "letter_mask.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
// ################################## PART A ##################################

void print_bitmask(letter_mask_t mask) {
    for (int row = 0; row < HEIGHT; ++row) {
        printf("row %d: ", row);
        for (int col = 0; col < WIDTH; ++col) {
            printf("%d ", MSB(mask));
            mask = mask << 1;
        }
        printf("\n");
    }
    printf("unused: ");
    for (int i = HEIGHT * WIDTH; i < NUM_BITS; i++) {
        printf("%d", MSB(mask));
        mask = mask << 1;
    }
    printf("\n");
}

// ################################ QUESTION 1 ################################
bool get_bit_value(letter_mask_t mask, int row, int col) {
    assert(row >= 0 && row < HEIGHT);
    assert(col >= 0 && col < WIDTH);
    return MSB(mask << (row * WIDTH + col));
}

// ################################ QUESTION 2 ################################
void set_bit_value(letter_mask_t *mask, int row, int col, bool value) {
    assert(row >= 0 && row < HEIGHT);
    assert(col >= 0 && col < WIDTH);
    int pos = NUM_BITS - 1 - row * WIDTH - col;
    *mask = (*mask & ~(1 << pos)) | (value << pos);
}

// ################################ QUESTION 3 ################################
void set_all_bits(letter_mask_t *mask, bool value) {
    *mask = (value ? BOARD_ONES : BOARD_ZEROS);
}

// ################################ QUESTION 4 ################################
bool is_free_letter(letter_mask_t mask) {
    bool found_one = false;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (get_bit_value(mask, i, j)) {
                if (found_one) {
                    return true;
                } else {
                    found_one = true;
                }
            }
        }
    }
    return false;
}

// ################################ QUESTION 5 ################################

bool is_fixed_letter(letter_mask_t mask) {
    bool found_one = false;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (get_bit_value(mask, i, j)) {
                if (found_one) {
                    return false;
                } else {
                    found_one = true;
                }
            }
        }
    }
    return found_one;
}

bool get_fixed_letter_pos(letter_mask_t mask, int *row, int *col) {
    if (is_fixed_letter(mask)) {
        for (int i = 0; i < HEIGHT; i++) {
            for (int j = 0; j < WIDTH; j++) {
                if (get_bit_value(mask, i, j)) {
                    *row = i;
                    *col = j;
                    return true;
                }
            }
        }
    }
    return false;
}

// ################################ QUESTION 6 ################################

letter_mask_t neighbourhood(letter_mask_t *mask) {
    letter_mask_t neighbourhood = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (get_bit_value(*mask, i, j)) {
                for (int a = -1; a <= 1; a++) {
                    for (int b = -1; b <= 1; b++) {
                        if (i + a >= 0 && i + a < HEIGHT && j + b >= 0 && j + b < WIDTH) {
                            set_bit_value(&neighbourhood, i + a, j + b, true);
                        }
                    }
                }
            }
        }
    }
    return neighbourhood;
}

void intersect_neighbourhoods(letter_mask_t *fst, letter_mask_t *snd) {
    letter_mask_t fst_neighbourhood = neighbourhood(fst);
    *fst = *fst & neighbourhood(snd);
    *snd = *snd & fst_neighbourhood;
}

#ifdef MAIN_LETTER_MASK
int main(void) {
    print_bitmask(BOARD_ZEROS);
    print_bitmask(BOARD_ONES);
    print_bitmask(FIRST_ROW_SET);
    print_bitmask(LAST_ROW_SET);
    print_bitmask(FIRST_COL_SET);
    print_bitmask(LAST_COL_SET);
    print_bitmask(FIRST_CELL_SET);
    print_bitmask(0x8A88A8BA); // cross and 0111010 (0b10001010100010001010100010111010)
    print_bitmask(0x213E4257); // plus  and 1010111 (0b00100001001111100100001001010111)
    return 0;
}
#endif
