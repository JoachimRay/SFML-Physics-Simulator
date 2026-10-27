# SFML Physics Simulator

A small 2D physics demo built with C++ and SFML. A ball falls under gravity, bounces against the bottom and right edges of the window, and can be picked up and dragged with the mouse. The window also shows the mouse position and the ball's center coordinates.

## Features

- Gravity-driven ball motion with simple bouncing.
- Drag the ball with the left mouse button.
- The ball turns white when the mouse is over it and red otherwise.
- Live mouse and ball-center coordinates.
- SFML 3 event handling and a bundled font.

## Controls

| Input | Action |
| --- | --- |
| Move the mouse | Show the mouse's X/Y position; hover over the ball to highlight it |
| Hold the left mouse button on the ball | Drag the ball |
| Release the left mouse button | Let gravity move the ball again |
| Close the window | Quit the simulator |

## Requirements

- Windows 10 or later
- [MSYS2](https://www.msys2.org/) with the **UCRT64** environment
- GCC and SFML 3 installed in `C:\msys64\ucrt64`
- Visual Studio Code (for the included build and run tasks)

Install the compiler and SFML from an **MSYS2 UCRT64** terminal:

```bash
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-sfml
```

The bundled font is loaded from `Fonts/arial_mt_black/ARIBL0.ttf`, relative to the project folder. Keep the `Fonts` directory beside `main.cpp` when running the program.

## Build and run in VS Code

1. Open this project folder in VS Code.
2. Press **Ctrl+Shift+P** and choose **Tasks: Run Task**.
3. Select **Run Physics**. VS Code builds the program and starts `PhysicsApp.exe`.

The tasks are defined in `.vscode/tasks.json`. They expect MSYS2 at `C:\msys64`. If MSYS2 is installed elsewhere, update the compiler, include, library, and PATH locations in that file.

## Build from the UCRT64 terminal

From the project directory, run:

```bash
g++ -std=c++17 -g main.cpp -I/ucrt64/include -L/ucrt64/lib \
  -lsfml-graphics -lsfml-window -lsfml-system -o PhysicsApp.exe
./PhysicsApp.exe
```

Run the executable with the project directory as its working directory so it can find the bundled font.
