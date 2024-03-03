#ifndef CUBE_TYPES_H
#define CUBE_TYPES_H

enum Colour {
  White,
  Yellow,
  Red,
  Orange,
  Blue,
  Green,
};

struct CornerPiece {
  enum Colour a;
  enum Colour b;
  enum Colour c;
};

struct EdgePiece {
  enum Colour a;
  enum Colour b;
};

struct Cube {
  struct CornerPiece cornerPieces[8];
  struct EdgePiece edgePieces[12];
};

#endif
