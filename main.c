#include <stdio.h>
#include <unistd.h>

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

int main() {
  char board[cols * rows];

  setgrid2(1,1, board, alive);
  setgrid2(25,1, board, alive);
  setgrid2(10,10, board, alive);
  setgrid2(10,11, board, alive);
  setgrid2(10,12, board, alive);

  for (int y = rows - 1; y >= 0; y--) {
    printf("%02d ", y + 1);
    for (int x = 1; x <= cols; x++) {
      int point = y * cols + x;

      printcell(point, board);
      // printf("%d", point);
    }

    printf("\n");
  }

  printf("\n");

  // do here the changes

  // usleep(1000000); // 400 ms // 1 sec
  // }

  // printf("\n");
}
