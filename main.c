#include <stdio.h>
#include <stdlib.h>

#define SOLVED_CUBE                                                            \
  {                                                                            \
    .cornerPieces = {                                                          \
      {.a = White, .b = Orange, .c = Blue},                                    \
      {.a = White, .b = Blue, .c = Red},                                       \
      {.a = White, .b = Red, .c = Green},                                      \
      {.a = White, .b = Green, .c = Orange},                                   \
      {.a = Yellow, .b = Orange, .c = Green},                                  \
      {.a = Yellow, .b = Green, .c = Red},                                     \
      {.a = Yellow, .b = Red, .c = Blue},                                      \
      {.a = Yellow, .b = Blue, .c = Orange},                                   \
    }                                                                          \
  }

#define STICKER "  "

#define ANSI_BG_RED "\x1b[41m"
#define ANSI_BG_GREEN "\x1b[42m"
#define ANSI_BG_BLUE "\x1b[44m"
#define ANSI_BG_YELLOW "\x1b[43m"
#define ANSI_BG_WHITE "\x1b[47m"
// could need adjusting https://en.wikipedia.org/wiki/ANSI_escape_code#Colors
#define ANSI_BG_ORANGE "\x1b[48:5:202m"

#define ANSI_BG_RESET "\x1b[0m"

enum Colour {
  White,
  Yellow,
  Red,
  Orange,
  Blue,
  Green,
};

// copies string into buff starting at write_start_pos
// returns the position in the buffer that the terminating character is at
int copy_string(char *buffer, int write_start_pos, char *string) {
  // points to where the buffer is being written to
  char *p_buffer = buffer;
  p_buffer += write_start_pos;
  // character
  int i = write_start_pos;
  // points to where is being read from
  char *p_string = string;
  while (*p_string != '\0') {
    *p_buffer = *p_string;
    p_buffer++;
    p_string++;
    i++;
  }
  // need this to qrite the terminating character
  *p_buffer = *p_string;
  return i;
}

int colour_ansi_backgorund(char *buff, int write_start_pos,
                           enum Colour colour) {
  switch (colour) {
  case White:
    return copy_string(buff, write_start_pos, ANSI_BG_WHITE);
  case Yellow:
    return copy_string(buff, write_start_pos, ANSI_BG_YELLOW);
  case Red:
    return copy_string(buff, write_start_pos, ANSI_BG_RED);
  case Orange:
    return copy_string(buff, write_start_pos, ANSI_BG_ORANGE);
  case Blue:
    return copy_string(buff, write_start_pos, ANSI_BG_BLUE);
  case Green:
    return copy_string(buff, write_start_pos, ANSI_BG_GREEN);
  }
}

struct CornerPiece {
  enum Colour a;
  enum Colour b;
  enum Colour c;
};

// struct EdgePiece {
//   enum Colour a;
//   enum Colour b;
// };

struct Cube {
  struct CornerPiece cornerPieces[8];
  // struct EdgePiece edgePieces[12];
};

int sticker_string(char *buff, int write_start_pos, enum Colour colour) {
  int prefix_end = colour_ansi_backgorund(buff, write_start_pos, colour);
  return copy_string(buff, prefix_end, STICKER ANSI_BG_RESET);
}

int blank_stickers_string(char *buffer, int write_start_pos, int count) {
  int end = write_start_pos;
  for (int i = 0; i < count; i++) {
    end = copy_string(buffer, end, STICKER);
  }
  return end;
}

int cube_net_string(char *buffer, struct Cube *cube) {
  int end = 0;
  // top (first row)
  end = blank_stickers_string(buffer, end, 3);
  end = sticker_string(buffer, end, cube->cornerPieces[0].a);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[1].a);

  end = copy_string(buffer, end, "\n\n");

  // top (last row)
  end = blank_stickers_string(buffer, end, 3);
  end = sticker_string(buffer, end, cube->cornerPieces[3].a);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[2].a);

  end = copy_string(buffer, end, "\n");

  // left (first row)
  end = sticker_string(buffer, end, cube->cornerPieces[0].b);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[3].c);

  // front (first row)
  end = sticker_string(buffer, end, cube->cornerPieces[3].b);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[2].c);

  // right (first row)
  end = sticker_string(buffer, end, cube->cornerPieces[2].b);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[1].c);

  // back (first row)
  end = sticker_string(buffer, end, cube->cornerPieces[1].b);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[0].c);

  end = copy_string(buffer, end, "\n\n");

  // left (last row)
  end = sticker_string(buffer, end, cube->cornerPieces[7].c);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[4].b);

  // front (last row)
  end = sticker_string(buffer, end, cube->cornerPieces[4].c);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[5].b);

  // right (last row)
  end = sticker_string(buffer, end, cube->cornerPieces[5].c);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[6].b);

  // back (last row)
  end = sticker_string(buffer, end, cube->cornerPieces[6].c);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[7].b);

  end = copy_string(buffer, end, "\n");

  // bottom (first row)
  end = blank_stickers_string(buffer, end, 3);
  end = sticker_string(buffer, end, cube->cornerPieces[4].a);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[5].a);

  end = copy_string(buffer, end, "\n\n");

  // bottom (last row)
  end = blank_stickers_string(buffer, end, 3);
  end = sticker_string(buffer, end, cube->cornerPieces[7].a);
  end = blank_stickers_string(buffer, end, 1);
  end = sticker_string(buffer, end, cube->cornerPieces[6].a);

  end = copy_string(buffer, end, "\n");
  return end;
}

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

void no_op_move(struct Cube *cube) { printf("no-op move\n"); }

enum Move {
  U,
  UPrime,
  D,
  DPrime,
  F,
  FPrime,
  B,
  BPrime,
  R,
  RPrime,
  L,
  LPrime,
  None,
};

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

int move_code(char *buffer, int write_start_pos, enum Move move_id) {
  switch (move_id) {
  case U:
    return copy_string(buffer, write_start_pos, "U");
  case UPrime:
    return copy_string(buffer, write_start_pos, "U'");
  case D:
    return copy_string(buffer, write_start_pos, "D");
  case DPrime:
    return copy_string(buffer, write_start_pos, "D'");
  case F:
    return copy_string(buffer, write_start_pos, "F");
  case FPrime:
    return copy_string(buffer, write_start_pos, "F'");
  case B:
    return copy_string(buffer, write_start_pos, "B");
  case BPrime:
    return copy_string(buffer, write_start_pos, "B'");
  case R:
    return copy_string(buffer, write_start_pos, "R");
  case RPrime:
    return copy_string(buffer, write_start_pos, "R'");
  case L:
    return copy_string(buffer, write_start_pos, "L");
  case LPrime:
    return copy_string(buffer, write_start_pos, "L'");
  default:
    return copy_string(buffer, write_start_pos, "?");
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

// has a trailing space due so move sequence codes can be joined together
int move_codes(char *buffer, int write_start_pos, enum Move *moves,
               int moveCount) {
  int end = write_start_pos;
  for (int i = 0; i < moveCount; i++) {
    end = move_code(buffer, end, moves[i]);
    end = copy_string(buffer, end, " ");
  }
  return end;
}

void execute_moves(struct Cube *cube, enum Move *moves, int moveCount) {
  for (int i = 0; i < moveCount; i++) {
    move_procedure(moves[i])(cube);
  }
}

int main() {
  struct Cube cube = SOLVED_CUBE;

  char cubeDisplayBuffer[1024];

  cube_net_string(cubeDisplayBuffer, &cube);
  printf("%s", cubeDisplayBuffer);

  char shuffleInput;
  printf("shuffle? (y/N): ");
  scanf("%c", &shuffleInput);

  if (shuffleInput == 'y') {
    int seed;
    printf("enter a shuffle seed: ");
    scanf("%d", &seed);

    int shuffleLength = 50;
    enum Move *shuffleMoves = shuffle_moves(seed, shuffleLength);

    char shuffleCodeDisplayBuffer[shuffleLength * 3 + 1];
    move_codes(shuffleCodeDisplayBuffer, 0, shuffleMoves, shuffleLength);
    printf("shuffle code:\n%s\n", shuffleCodeDisplayBuffer);

    execute_moves(&cube, shuffleMoves, shuffleLength);

    cube_net_string(cubeDisplayBuffer, &cube);
    printf("shuffled cube:\n%s", cubeDisplayBuffer);
  }

  while (1) {
    char move_code[3];
    printf("enter a move: ");
    scanf("%s", move_code);

    enum Move move = move_from_move_code(move_code);
    if (move == None) {
      printf("no move entered, exiting");
      break;
    }
    move_procedure(move)(&cube);

    cube_net_string(cubeDisplayBuffer, &cube);
    printf("%s", cubeDisplayBuffer);
  }

  return 0;
}
