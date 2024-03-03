#include "../h/cube_types.h"
#include "../h/move_types.h"

#include <stdlib.h>

void move_u(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[3];
  for (int i = 3; i >= 1; i--) {
    cube->cornerPieces[i] = cube->cornerPieces[i - 1];
  }
  cube->cornerPieces[0] = tempPiece;
}

void move_u_prime(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[0];
  for (int i = 0; i < 4; i++) {
    cube->cornerPieces[i] = cube->cornerPieces[i + 1];
  }
  cube->cornerPieces[3] = tempPiece;
}

void move_d(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[7];
  for (int i = 7; i >= 5; i--) {
    cube->cornerPieces[i] = cube->cornerPieces[i - 1];
  }
  cube->cornerPieces[4] = tempPiece;
}

void move_d_prime(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[4];
  for (int i = 4; i < 8; i++) {
    cube->cornerPieces[i] = cube->cornerPieces[i + 1];
  }
  cube->cornerPieces[7] = tempPiece;
}

struct CornerPiece rotate_corner_piece_cw(struct CornerPiece cornerPiece) {
  enum Colour tempColour = cornerPiece.c;
  cornerPiece.c = cornerPiece.b;
  cornerPiece.b = cornerPiece.a;
  cornerPiece.a = tempColour;
  return cornerPiece;
}

struct CornerPiece rotate_corner_piece_acw(struct CornerPiece cornerPiece) {
  enum Colour tempColour = cornerPiece.a;
  cornerPiece.a = cornerPiece.b;
  cornerPiece.b = cornerPiece.c;
  cornerPiece.c = tempColour;
  return cornerPiece;
}

void move_f(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[4];
  cube->cornerPieces[4] = rotate_corner_piece_cw(cube->cornerPieces[5]);
  cube->cornerPieces[5] = rotate_corner_piece_acw(cube->cornerPieces[2]);
  cube->cornerPieces[2] = rotate_corner_piece_cw(cube->cornerPieces[3]);
  cube->cornerPieces[3] = rotate_corner_piece_acw(tempPiece);
}

void move_f_prime(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[3];
  cube->cornerPieces[3] = rotate_corner_piece_acw(cube->cornerPieces[2]);
  cube->cornerPieces[2] = rotate_corner_piece_cw(cube->cornerPieces[5]);
  cube->cornerPieces[5] = rotate_corner_piece_acw(cube->cornerPieces[4]);
  cube->cornerPieces[4] = rotate_corner_piece_cw(tempPiece);
}

void move_b(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[6];
  cube->cornerPieces[6] = rotate_corner_piece_cw(cube->cornerPieces[7]);
  cube->cornerPieces[7] = rotate_corner_piece_acw(cube->cornerPieces[0]);
  cube->cornerPieces[0] = rotate_corner_piece_cw(cube->cornerPieces[1]);
  cube->cornerPieces[1] = rotate_corner_piece_acw(tempPiece);
}

void move_b_prime(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[1];
  cube->cornerPieces[1] = rotate_corner_piece_acw(cube->cornerPieces[0]);
  cube->cornerPieces[0] = rotate_corner_piece_cw(cube->cornerPieces[7]);
  cube->cornerPieces[7] = rotate_corner_piece_acw(cube->cornerPieces[6]);
  cube->cornerPieces[6] = rotate_corner_piece_cw(tempPiece);
}

void move_r(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[5];
  cube->cornerPieces[5] = rotate_corner_piece_cw(cube->cornerPieces[6]);
  cube->cornerPieces[6] = rotate_corner_piece_acw(cube->cornerPieces[1]);
  cube->cornerPieces[1] = rotate_corner_piece_cw(cube->cornerPieces[2]);
  cube->cornerPieces[2] = rotate_corner_piece_acw(tempPiece);
}

void move_r_prime(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[2];
  cube->cornerPieces[2] = rotate_corner_piece_acw(cube->cornerPieces[1]);
  cube->cornerPieces[1] = rotate_corner_piece_cw(cube->cornerPieces[6]);
  cube->cornerPieces[6] = rotate_corner_piece_acw(cube->cornerPieces[5]);
  cube->cornerPieces[5] = rotate_corner_piece_cw(tempPiece);
}

void move_l(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[7];
  cube->cornerPieces[7] = rotate_corner_piece_cw(cube->cornerPieces[4]);
  cube->cornerPieces[4] = rotate_corner_piece_acw(cube->cornerPieces[3]);
  cube->cornerPieces[3] = rotate_corner_piece_cw(cube->cornerPieces[0]);
  cube->cornerPieces[0] = rotate_corner_piece_acw(tempPiece);
}

void move_l_prime(struct Cube *cube) {
  struct CornerPiece tempPiece = cube->cornerPieces[0];
  cube->cornerPieces[0] = rotate_corner_piece_acw(cube->cornerPieces[3]);
  cube->cornerPieces[3] = rotate_corner_piece_cw(cube->cornerPieces[4]);
  cube->cornerPieces[4] = rotate_corner_piece_acw(cube->cornerPieces[7]);
  cube->cornerPieces[7] = rotate_corner_piece_cw(tempPiece);
}

void no_op_move(struct Cube *cube) {}

// doesn't need to be the most perfect hash
enum Move move_hash(int seed, int x) {
  return ((enum Move)((((x * 78234567) % 23453) + seed) * 23483) % 12);
}

void (*move_procedure(enum Move move_id))(struct Cube *cube) {
  switch (move_id) {
  case U:
    return move_u;
  case UPrime:
    return move_u_prime;
  case D:
    return move_d;
  case DPrime:
    return move_d_prime;
  case F:
    return move_f;
  case FPrime:
    return move_f_prime;
  case B:
    return move_b;
  case BPrime:
    return move_b_prime;
  case R:
    return move_r;
  case RPrime:
    return move_r_prime;
  case L:
    return move_l;
  case LPrime:
    return move_l_prime;
  default:
    return no_op_move;
  }
}

enum Move move_from_move_code(char *moveCode) {
  if (moveCode[0] == 'U') {
    if (moveCode[1] == '\'') {
      return UPrime;
    }
    return U;
  }
  if (moveCode[0] == 'D') {
    if (moveCode[1] == '\'') {
      return DPrime;
    }
    return D;
  }
  if (moveCode[0] == 'F') {
    if (moveCode[1] == '\'') {
      return FPrime;
    }
    return F;
  }
  if (moveCode[0] == 'B') {
    if (moveCode[1] == '\'') {
      return BPrime;
    }
    return B;
  }
  if (moveCode[0] == 'R') {
    if (moveCode[1] == '\'') {
      return RPrime;
    }
    return R;
  }
  if (moveCode[0] == 'L') {
    if (moveCode[1] == '\'') {
      return LPrime;
    }
    return L;
  }
  return None;
}

enum Move *shuffle_moves(int seed, int moveCount) {
  enum Move *moves = malloc(moveCount * sizeof(enum Move));
  for (int i = 0; i < moveCount; i++) {
    moves[i] = move_hash(seed, i);
  }
  return moves;
}

void execute_moves(struct Cube *cube, enum Move *moves, int moveCount) {
  for (int i = 0; i < moveCount; i++) {
    move_procedure(moves[i])(cube);
  }
}
