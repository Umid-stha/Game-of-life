# Game of Life

A terminal implementation of Conway's Game of Life, written in C from scratch — no libraries beyond the standard ones, following the rules straight from [Wikipedia](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life).

The grid starts in a random state and evolves generation by generation, rendered live in your terminal.

## Rules

Each cell is either alive (`#`) or dead (`.`). Every generation, each cell's next state is decided by its 8 neighbors:

- A live cell with 2 or 3 live neighbors survives.
- A dead cell with exactly 3 live neighbors becomes alive.
- Every other cell dies or stays dead.

The grid wraps around at the edges (toroidal), so patterns that drift off one side reappear on the other.

## Run

```
gcc -o game main.c && ./game
```

Press `Ctrl+C` to stop.

## How it works

- `generateInitialState` seeds the grid randomly.
- `computeNextGen` calculates the next generation into a separate buffer, then copies it back — this avoids reading and writing the same grid mid-update.
- `render` draws the full grid in one write per frame (using an ANSI cursor-reset escape code instead of clearing the screen) to keep the animation flicker-free.

## Config

Grid size and speed are constants at the top of `main.c`:

```c
#define ROWS 25
#define COLUMNS 30
```

Frame delay is set via `usleep()` in `main` (in microseconds).
