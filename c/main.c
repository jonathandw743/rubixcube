#include "../h/cube_types.h"
#include "../h/move.h"
#include "../h/s.h"
#include <stdio.h>

#define SOLVED_CUBE                                                            \
  {                                                                            \
    .cornerPieces =                                                            \
        {                                                                      \
            {.a = White, .b = Orange, .c = Blue},                              \
            {.a = White, .b = Blue, .c = Red},                                 \
            {.a = White, .b = Red, .c = Green},                                \
            {.a = White, .b = Green, .c = Orange},                             \
            {.a = Yellow, .b = Orange, .c = Green},                            \
            {.a = Yellow, .b = Green, .c = Red},                               \
            {.a = Yellow, .b = Red, .c = Blue},                                \
            {.a = Yellow, .b = Blue, .c = Orange},                             \
        },                                                                     \
    .edgePieces = {                                                            \
        {.a = White, .b = Blue},   {.a = White, .b = Red},                     \
        {.a = White, .b = Green},  {.a = White, .b = Orange},                  \
        {.a = Yellow, .b = Green}, {.a = Yellow, .b = Red},                    \
        {.a = Yellow, .b = Blue},  {.a = Yellow, .b = Orange},                 \
        {.a = Orange, .b = Blue},  {.a = Blue, .b = Red},                      \
        {.a = Red, .b = Green},    {.a = Green, .b = Orange},                  \
    },                                                                         \
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
    printf("enter a shuffle length: ");
    scanf("%d", &shuffleLength);

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
