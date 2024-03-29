#ifndef S_H
#define S_H

#include "cube_types.h"
#include "move_types.h"

int copy_string(char *buffer, int write_start_pos, char *string);

int colour_ansi_backgorund(char *buff, int write_start_pos, enum Colour colour);

int sticker_string(char *buff, int write_start_pos, enum Colour colour);

int blank_stickers_string(char *buffer, int write_start_pos, int count);

int cube_net_string(char *buffer, struct Cube *cube);

int move_code(char *buffer, int write_start_pos, enum Move move_id);

int move_codes(char *buffer, int write_start_pos, enum Move *moves,
               int moveCount);

#endif
