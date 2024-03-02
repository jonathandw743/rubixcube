#include <stdio.h>

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

// doesn't need to be the most perfect hash
unsigned int move_hash(int seed, int x) {
  return ((unsigned int)((((x * 78234567) % 23453) + seed) * 23483) % 12);
}

void (*move(unsigned int move_id))(struct Cube *cube) {
  switch (move_id) {
  case 0:
    return move_u;
  case 1:
    return move_u_prime;
  case 2:
    return move_d;
  case 3:
    return move_d_prime;
  case 4:
    return move_f;
  case 5:
    return move_f_prime;
  case 6:
    return move_b;
  case 7:
    return move_b_prime;
  case 8:
    return move_r;
  case 9:
    return move_r_prime;
  case 10:
    return move_l;
  case 11:
    return move_l_prime;
  default:
    return no_op_move;
  }
}

int move_code(char *buffer, int write_start_pos, unsigned int move_id) {
  switch (move_id) {
  case 0:
    return copy_string(buffer, write_start_pos, "U");
  case 1:
    return copy_string(buffer, write_start_pos, "U'");
  case 2:
    return copy_string(buffer, write_start_pos, "D");
  case 3:
    return copy_string(buffer, write_start_pos, "D'");
  case 4:
    return copy_string(buffer, write_start_pos, "F");
  case 5:
    return copy_string(buffer, write_start_pos, "F'");
  case 6:
    return copy_string(buffer, write_start_pos, "B");
  case 7:
    return copy_string(buffer, write_start_pos, "B'");
  case 8:
    return copy_string(buffer, write_start_pos, "R");
  case 9:
    return copy_string(buffer, write_start_pos, "R'");
  case 10:
    return copy_string(buffer, write_start_pos, "L");
  case 11:
    return copy_string(buffer, write_start_pos, "L'");
  default:
    return copy_string(buffer, write_start_pos, "?");
  }
}

void shuffle(int seed, struct Cube *cube) {
  char shuffle_code[151];
  int end = 0;
  for (int i = 0; i < 50; i++) {
    unsigned int move_id = move_hash(seed, i);
    move(move_id)(cube);
    end = move_code(shuffle_code, end, move_id);
    end = copy_string(shuffle_code, end, " ");
  }
  printf("%s\n", shuffle_code);
}

int main() {
  struct Cube cube = SOLVED_CUBE;

  char buffer[1024];

  cube_net_string(buffer, &cube);
  printf("%s\n", buffer);

  int seed;
  scanf("%d", &seed);

  shuffle(seed, &cube);

  cube_net_string(buffer, &cube);
  printf("%s\n", buffer);

  return 0;
}
