# Game of Life

A clone of John Conway's Game of life written in C. Powered by SDL 2.

![](https://github.com/DigitalCyan/game-of-life/blob/main/demo/demo.gif?raw=true)

## Dependencies:
- SDL 2

## Development dependencies:
- cmake
- make-pkg

## Configuration
The program can be configured by editing `config.h` pre-compilation. Feel free to update these fields as you please (just don't touch the computed ones unless you know what you're doing).

```c
#define WORLD_EDGE_SIZE 64
#define CELL_SIZE 16
#define THINK_DELAY 50
```
