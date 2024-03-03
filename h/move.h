#ifndef MOVE_H
#define MOVE_H

#include "move_types.h"

void move_u(struct Cube *cube);

void move_u_prime(struct Cube *cube);

void move_d(struct Cube *cube);

void move_d_prime(struct Cube *cube);

struct CornerPiece rotate_corner_piece_cw(struct CornerPiece cornerPiece);

struct CornerPiece rotate_corner_piece_acw(struct CornerPiece cornerPiece);

void move_f(struct Cube *cube);

void move_f_prime(struct Cube *cube);

void move_b(struct Cube *cube);

void move_b_prime(struct Cube *cube);

void move_r(struct Cube *cube);

void move_r_prime(struct Cube *cube);

void move_l(struct Cube *cube);

void move_l_prime(struct Cube *cube);

void no_op_move(struct Cube *cube);

enum Move move_hash(int seed, int x);

void (*move_procedure(enum Move move_id))(struct Cube *cube);

int move_code(char *buffer, int write_start_pos, enum Move move_id);

enum Move move_from_move_code(char *moveCode);

enum Move *shuffle_moves(int seed, int moveCount);

int move_codes(char *buffer, int write_start_pos, enum Move *moves,
               int moveCount);

void execute_moves(struct Cube *cube, enum Move *moves, int moveCount);

#endif
