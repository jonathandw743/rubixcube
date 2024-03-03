# how the cube is layed out

## top (white)

+-b-+
|001|
o3w1r
|322|
+-g-+

U: 0->1, 1->2, 2->3, 3->0
U': 0->3, 1->0, 2->1, 3->2

## front (green)

+-w-+
|322|
o11g10r
|445|
+-y-+

F: 3->2, 2->5, 5->4, 4->3
F': 3->4, 2->3, 5->2, 4->5

## bottom (yellow)

+-g-+
|445|
o7y5r
|766|
+-b-+

D: 4->5, 5->6, 6->7, 7->4
D': 4->7, 5->4, 6->5, 7->6

## right (red)

+-w-+
|211|
g10r9b
|556|
+-b-+

R: 2->1, 1->6, 6->5, 5->2
R': 2->5, 1->2, 6->1, 5->6

## back (blue)

+-w-+
|001|
b9r8g
|766|
+-b-+

B: 1->0, 0->7, 7->6, 6->1
B': 1->6, 0->1, 7->0, 6->7

## left (orange)

+-w-+
|033|
b8o11g
|774|
+-y-+

L: 0->3, 3->4, 4->7, 7->0
L': 0->7, 3->0, 4->3, 4->4

## cornerPieces

0. white, orange, blue
1. white, blue, red
2. white, red, green
3. white, green, orange
4. yellow, orange, green
5. yellow, green, red
6. yellow, red, blue
7. yellow, blue, orange

## net

         0.a0.a1.a
         3.a w 1.a
         3.a2.a2.a
0.b3.b3.c3.b2.b2.c2.b1.b1.c1.b0.b0.c
8.a o  .b .a g  .b .a r 9.b9.a b 8.b
7.c7.b4.b4.c4.b5.b5.c5.b6.b6.c6.b7.b
         4.a4.a5.a
         7.a y 5.a
         7.a6.a6.a
