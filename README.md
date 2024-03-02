# how the cube is layed out

## top (white)

+-b-+
|0 1|
o w r
|3 2|
+-g-+

U: 0->1, 1->2, 2->3, 3->0
U': 0->3, 1->0, 2->1, 3->2

## front (green)

+-w-+
|3 2|
o g r
|4 5|
+-y-+

F: 3->2, 2->5, 5->4, 4->3
F': 3->4, 2->3, 5->2, 4->5

## bottom (yellow)

+-g-+
|4 5|
o y r
|7 6|
+-b-+

D: 4->5, 5->6, 6->7, 7->4
D': 4->7, 5->4, 6->5, 7->6

## right (red)

+-w-+
|2 1|
g r b
|5 6|
+-b-+

R: 2->1, 1->6, 6->5, 5->2
R': 2->5, 1->2, 6->1, 5->6

## back (blue)

+-w-+
|1 0|
g r b
|6 7|
+-b-+

B: 1->0, 0->7, 7->6, 6->1
B': 1->6, 0->1, 7->0, 6->7

## left (orange)

+-w-+
|0 3|
b o g
|7 4|
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

         0.a   1.a

         3.a   2.a
0.b   3.c3.b   2.c2.b   1.c1.b   0.c

7.c   4.b4.c   5.b5.c   6.b6.c   7.b
         4.a   5.a

         7.a   6.a
