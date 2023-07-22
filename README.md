<h1 align="center">Game of Life</h1>
<p align="center">A clone of John Conway's Game of life written in C and powered by SDL 2.</p>

<p align="center">
    <img src="https://github.com/DigitalCyan/game-of-life/blob/main/demo/demo.gif?raw=true" />
</p>

## About:

The Game of Life is a cellular automaton created by John Conway (rest in peace) that was created with a goal 
of demonstrating the possibility of emergent behavior with four simple rules:

1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

## Limitations:

Unlike the original, this clone of Game of Life does not actually house an infinite universe.
Instead, it runs on a configurable grid. For more details on configuration, 
check the [Configuration](#configuration) section.

---

## Dependencies:
- SDL 2
- SDL 2 - TTF

## Development dependencies:
- make
- cmake
- gcc

## Satisfying dependencies
I you are running a Linux distribution that uses `apt` as it's package manager, you should be able to obtain
all the required dependencies by running the following command:
```shell
sudo apt install libsdl2-ttf-2.0-0 libsdl2-dev libsdl2-ttf-2.0-0 libsdl2-ttf-dev make cmake gcc
```

If you are on some other distribution, you are probably experienced enough to find your own way of obtaining
the dependencies. If not, do a few searches, it won't hurt.

## Compiling
In order to compile the program, make sure you satisfy all the development depencencies and follow these steps:

```shell
git clone https://github.com/DigitalCyan/game-of-life --recurse-submodules
cd game-of-life
cmake -S . -B build && make --directory=build && cp -vr assets/ build/
```

The last line builds the program and copies the `assets` folder from the project root to the build folder. It's 
important to keep the `assets` folder next to the compiled binary so the binary can access it.

## Configuration
The program can be configured by editing `config.h` pre-compilation. Feel free to update these fields as you please (just don't touch the computed ones unless you know what you're doing).

```c
#define WORLD_EDGE_SIZE 64
#define CELL_SIZE 16
#define THINK_DELAY 50
```
