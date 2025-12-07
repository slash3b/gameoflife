#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define cols 25
#define rows 25
#define dead '.'
#define alive '*'

void clear() { printf("\033[H\033[2J"); }

void printcell(int i, char *board) {
  if (board[i] == alive) {
    printf("%c", alive);
    return;
  }

  printf("%c", dead);
}

int coord_to_index(int x, int y) {
  if (x < 0 || x > cols * rows) {
    return -1;
  }

  if (y < 0 || y > cols * rows) {
    return -1;
  }

  int point = x * cols + y;
  printf("point %d \n", point);
  if (point > cols * rows) {
    return -1;
  }

  return point;
}

void setgrid(int x, int y, char *board, char val) {
  int res = coord_to_index(x, y);
  if (res == -1) {
    return;
  }

  board[res] = val;
}

/* void countliveneigh(int x, int y, char *board) { */
/*     // -1, -1 */
/*     // do it in the loop */
/* } */

int coordtoidx(int x, int y) {
  if (x < 1 || y < 1) {
    return -1;
  }

  int point = ((y - 1) * cols) + x;

  if (point > cols * rows) {
    return -1;
  }

  return point;
}

void setgrid2(int x, int y, char *grid, char state) {
  int point = coordtoidx(x, y);
  if (point == -1) {
    return;
  }

  grid[point] = state;
}

int neighcount(int x, int y, char *grid) {
  int res = 0;

  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (x == i && y == j) {
        continue;
      }
      int point = coordtoidx(i, j);
      if (point != -1) {
        if (grid[point] == alive) {
          res++;
        }
        // printf("x:%d y:%d char:%c\n",i, j, grid[point]);
      }
    }
  }

  // printf("%d\n", res);
  return res;

  // x-1, y+1
  // x-1, y
  // x-1, y-1

  // x+1, y+1
  // x+1, y
  // x+1, y-1

  // x, y-1
  // x, y+1
}

void printgrid(char *grid) {
  for (int y = rows - 1; y >= 0; y--) {
    printf("%02d ", y + 1);
    for (int x = 1; x <= cols; x++) {
      int point = y * cols + x;

      printcell(point, grid);
      // printf("%d", point);
    }

    printf("\n");
  }
}

char *propagate(char *b1) {
  char *board2 = malloc(cols * rows);

  for (int y = rows - 1; y >= 0; y--) {
    for (int x = 1; x <= cols; x++) {

      int p = coordtoidx(x, y);
      int cnt = neighcount(x, y, b1);

      /* if (cnt == 3) { */
      /*   printf("%d %d %d\n", cnt, x, y); */
      /*   printf("%c\n", b1[p]); */
      /* } */

      // Reproduction: A dead cell with exactly three live
      // neighbors becomes a live cell
      // i
      if (b1[p] == dead && cnt == 3) {
        board2[p] = alive;
        continue;
      }

      if (b1[p] == alive) {
        if (cnt < 2) {
          board2[p] = dead;
          continue;
        }
        if (cnt > 3) {
          board2[p] = dead;
          continue;
        }
        if (cnt == 2 || cnt == 3) {
          board2[p] = alive;
          continue;
        }
      }
      // fallbask;
      board2[p] = dead;

      // int cnt = neighcount(yy, xx, b1);
      //  if (b1[]
      // Underpopulation: A live cell with fewer than two
      // live neighbors dies.
      //
      // Survival: A live cell with two or three live neighbors
      // stays alive.
      //
      // Overpopulation: A live cell with more than three live
      // neighbors dies.
      //
    }
  }

  return board2;
}

int main() {
  char *board = malloc(cols * rows);
  memset(board, dead, cols * rows);

  setgrid2(1, 1, board, alive);
  setgrid2(25, 1, board, alive);

  setgrid2(10, 10, board, alive);
  setgrid2(10, 11, board, alive);
  setgrid2(10, 12, board, alive);

  neighcount(10, 11, board);
  neighcount(1, 1, board);

  while (1) {

    printgrid(board);
    clear();
    board = propagate(board);
    usleep(1000000); // 400 ms // 1 sec
  }


  printf("\n");

  // do here the changes

  // }

  // printf("\n");
}

// The system evolves in discrete time steps (generations)
// based on the state of neighbors in the previous step:
//
// Underpopulation: A live cell with fewer than two
// live neighbors dies.
//
// Survival: A live cell with two or three live neighbors
// stays alive.
//
// Overpopulation: A live cell with more than three live
// neighbors dies.
//
// Reproduction: A dead cell with exactly three live
// neighbors becomes a live cell
