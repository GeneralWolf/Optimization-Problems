# Optimization Problems

## Problem A - 2048 clean up!

### Description
2048 is a single-player game consisting of a 2-dimentional board with numbered tiles. The player can slide the tiles in one of the four possible directions (left, right, up or down). Each play corresponds of a slide in one of the four directions. When a play is performed, all the tiles slide in that direction as far as possible, stopping whenever they collide with the target wall (board limit on the direction of the slide) or with another tile. When a tile collides with another tile of the same value, the two tiles merge into one, of value equal to the sum of their previous values. So, if a tile of value 2 collides with another tile of value 2, the merged tile assumes the value 4. The resulting tile cannot merge again in the same move with any other tile. This means that a slide to the right in in a row with tiles [2,2,4] will result in the sequence [4,4], not [8].

This sliding operation is applied iteratively, tile by tile, starting from the tiles closer to the target wall and advancing to the tiles farther away. This means that if the player makes a slide to the right direction in a row with the tiles [2,2,2], the resulting tiles will be [2, 4]. On contrary, if the play is a slide to the left direction, then the result will be [4, 2]

In the original version of the game, a new tile of value 2 or 4 appears on an empty space of the board after every play (a slide movement). However, in this version, no new tile appears. Also, in the original version the square board is 4x4, and in our version the square board can be of different sizes.

Your objective is to identify the minimum number of plays that merge all tiles into one. A maximum number of plays allowed is provided. If it is not possible to clear the board with that number of plays, you must report no solution.

### Input
The input starts with one line containing the number of test cases.

Then, for each test case, the first line contains two numbers: 1 ≤ N ≤ 20 and 1 ≤ M ≤ 50. N represents the size of the board, i.e. the number of rows and columns, and M represents the maximum number of slides allowed.

After that, N lines follow, each with N values, corresponding to the values of the tiles in the board. Empty tiles are represented by a value of 0.

### Output
For each test case, you should print one integer with the minimum number of slides needed to clear the board, followed by a '\n'.

If it is not possible to clear the board with at most M slides, output the text no solution followed by a '\n'.

### Example
#### Example input:
```python
4
3 5
2 0 2 
4 0 8 
0 0 0 
3 10
4 2 4 
4 2 4 
4 4 4 
3 4
4 2 4 
4 2 4 
4 4 4 
4 10
8 4 0 0 
4 0 0 0 
8 4 0 0 
0 0 4 0
```
#### Example output:
```python
3
5
no solution
4
```

## Problem B - ARChitecture

### Description
You are given n Lego blocks of height h, and you want to build an arc using some (or all) of those blocks in your room which has a ceiling of height H, so the top of your arc cannot be higher than that. Assume that the floor starts at height 0 and that width is not a problem.

For your Lego construction to be considered an arc it needs to conform to the following rules:

An arc consists of 3 ≤ k ≤ n blocks placed consecutively, such that the index i = 1 denotes the first block, i = 2 the second block, and so on until the last block i = k;
The first and last blocks must be placed on the floor, that is h1 = 0 and hk = 0, where hi denotes the height from the floor to the base of the block;
The ith block must share at least 1 height with its neighbors, formally hi + 1 − h < hi < hi + 1 + h for i > 1;
The values of hi should be monotonically increasing, up to a certain block, and then monotonically decreasing. Formally, there exists a block l such that h1 < ⋯ < hl > ⋯ > hk. Note that two consecutive blocks cannot have the same value of hi.
To give some examples the following three constructions are valid arcs for n = 5, h = 3 and H = 6.

However, if H = 4 only the left-most construction would be valid.

Moreover the following constructions are not valid arcs since they break at least one rule.

When building your arc you started wondering how many distinct arcs you could build given your constraints. Your task, is to compute the number of distinct arcs that can be built for the given values n, h and H. Since this number can be very large, you need to report your answer in modulo 1000000007.

You may consider the following modulo arithmetic operations:
```cpp
int mod_abs(int a, int mod) {
  return ((a % mod) + mod) % mod;
}
```
```cpp
int mod_add(int a, int b, int mod) {
  return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}
```
```cpp
int mod_sub(int a, int b, int mod) {
  return mod_add(a, -b, mod);
}
```

### Input
The first line contains the number of test cases t. Then, t test cases follow.

For each test case, you are given three space-separated integers in a single line denoting the variables n, h and H respectively.

### Limits
```
t ≤ 20
n ≤ 500
h ≤ 500
H ≤ 60000
```

### Output
For each test case you need to output the number of distinct arcs you can build modulo 1000000007.

### Examples
#### Input (Example 1)
```
7
3 3 3
3 3 4
3 3 5
3 3 6
4 3 7
5 5 10
8 4 30
```
### Output (Example 1)
```
0
1
2
2
4
54
819
```
### Input (Example 2)
```
1
32 3 100
```
### Output (Example 2)
```
431655757
```
### Input (Example 3)
```
2
17 29 5899
70 16 276
```
### Output (Example 3)
```
162344589
70718620
```

##Problem C - Bike Lanes

###Description

The mayor of a big touristic city asked your help to plan the construction of bike lanes in the city in order to
improve the green mobility of tourists. One demand is that bike lanes can only be built in one-way streets, for
safety reasons. You are given a map containing direct connections between points of interest (POIs) and their
distance. Each direct connection is a one-way street that links directly two POIs. Note there might be no
connection between two arbitrary POIs of the map, since we are talking only of the one-way streets of the
town.
Although streets are one-way only for car traffic, bikes will be able to travel both ways on the bike lanes.
Because connecting all POIs is expensive and funding is short, instead of building a bike lane in each and
every street, you are asked to find touristic circuits from those connections, so you can build lanes connecting
the POIs of each circuit independently. A circuit is a set of POIs and connections between those POIs that
allows to travel between any pair of POIs and it has maximal size. Note that by definition a circuit is
composed by at least two POIs.
So, after identifying these circuits, you have to select a subset of streets to build the bike lanes upon. For each
circuit of POIs, you should plan a bike lane that connects all POIs with the minimum possible length.

Having all that information, you go to meet the mayor. He might ask you 4 different questions, namely:
1. How many circuits exist in the city?
2. How many POIs does the largest circuit contain?
3. What is the longest lane to build (considering a different lane for each circuit)?
4. What is the total length of bike lane to build (considering all circuits)?

### Input
The first line of the input gives the number of test cases to process.
Each test case starts with three numbers, 1 ≤ n ≤ 1000 (corresponding to the number of POIs), 1 ≤ m ≤
100000, corresponding to the number of connections between POIs and 1 ≤ q ≤ 4, corresponding to the
number of questions the mayor asks.
Then, m lines follow, each containing 3 values 1 ≤ A ≤ 1000, 1 ≤ B ≤ 1000 and 1 ≤ D ≤ 500. Each line
corresponds to a connection from POI A to POI B, with distance D.

### Output
For each of the test case of the input, print one line with q values, corresponding to the answers from 1 to q.

### Examples
#### Input (Example 1)
```
6
12 18 4
2 1 3
3 2 4
4 1 2
4 2 8
2 5 3
5 2 5
3 6 4
6 3 2
6 5 6
7 5 4
8 6 9
7 8 1
7 9 2
9 10 8
10 7 4
8 11 2
11 12 12
12 10 3
4 4 3
2 1 3
3 2 4
4 1 2
4 2 8
4 4 4
2 1 3
3 2 4
1 4 2
4 2 8
4 4 3
2 1 3
3 2 4
1 4 2
4 2 8
4 4 2
2 1 3
3 2 4
1 4 2
4 2 8
4 4 1
2 1 3
3 2 4
1 4 24 2 8
```
### Output (Example 1)
```
3 6 12 17
0 0 0
1 3 5 5
1 3 5
1 3
1
```
