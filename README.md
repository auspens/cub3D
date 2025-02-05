# 3D Advent calendar

A "3D Advent calendar" is a program created to fulfill requirements of the cub3D project at 42berlin.
The main idea of the project is to use a rendering technique called Raycasting in order to create a first-person 3D-perspective, based on a 2D-map.
The project requires use of miniLibX simple graphics library for linux.

![Advent 3D experience](adventcub3d.gif)

---

## Authors

- **Eleonora Winkler** - [GitHub Profile](https://github.com/eluscha)
- **auspens** - [GitHub Profile](https://github.com/auspens)

---

## Features

- Supports wall textures of your choice (.xpm format)
- Supports different maps, as long as they comply with the map requirements.
- Advent calender features correspond to the bonus part of the cub3d project: small gifts (animated sprites) are hidden behind multiple doors (up to 24) in a maze.

### Map files Requirements

- A .cub map file must provide the paths to all the wall textures and the colors (R,G,B) of the floor (F) and the ceiling (C):
    ```bash
    NO <path_to_north_texture>
    SO <path_to_south_texture>
    WE <path_to_west_texture>
    EA <path_to_east_texture>
    C 225,30,0
    F 0,0,0

    ```
- Those identifiers are followed with the 2D map data, that defines the space/maze.
- A basic (non-bonus) map must be composed of only 6 characters: 0 (empty walkable space), 1 (wall), and N, S , E or W for the start position and spawning
orientation of the player. Bonus map allows another character: D (door).
- A map must be closed/surrounded by walls

---

## Limitations

- Bonus part: for the sake of time only the first two doors will have unique sprites behind them, after that they are repeated. Also only the first three doors are numbered. More sprites can be easily added to make it a proper calender.
- General limitations of the raycasting technology (it is a pseudo-3D space, sprites are 2D).
- Limitations of the miniLibX library (e.g. fixed window size, textures must be of xpm format).
- Beware of the “Power of Two” rule, when using your own wall textures.

---

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/eluscha/cub3D.git cub3D
   cd cub3D
   ```
   
2. If the contents of the minilibx-linux didn't download, you need to do it manually:

   ```bash
   git submodule update --init --recursive
   ```
   
3. For simple version (without sprites, no mouse movement, etc.):

   ```bash
   make
   ./cub3D <map_name>
   ```

4. For bonus features (advent calender):

   ```bash
   make bonus
   ./cub3D <bonusmap_name>
   ```

---

## Usage

### Basic functionality

- Launch the executable with an appropriate map (examples provided in the repo).
- Use <kbd>W</kbd>, <kbd>A</kbd>, <kbd>S</kbd>, and <kbd>D</kbd> keys to move through the maze.
- Use <kbd>left</kbd> and <kbd>right</kbd> arrow keys to look left and right.
- Press <kbd>ESC</kbd> or cross to exit.

### Bonus functionality

- You can use the mouse to look left and right.
- To open doors come closer to them and press the <kbd>space</kbd>.

---

## Built With

- **C Language** - The core programming language used.
- **miniLibX graphics library** - a simple X-Window programming API in C, designed for educational purposes at 42.

---

## Acknowledgements

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) was used to learn about the raycasting and sprite projections.
- [Caz pixelart](https://caz-creates-games.itch.io/ducky-2) was used for the adorable ducky sprite.
- [karsiori pixelart]( https://karsiori.itch.io/free-pixel-art-christmas-trees) was used for the Christmas tree sprite.
- Paintings of Wassily Kandinsky and Natalia Goncharova were used as wall textures.

---
