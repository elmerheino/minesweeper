# Minesweeper

Minesweeper is a classic game where you click open tiles on a grid with hidden mines, aim being to clear
the whole area without hitting a mine. This is an implementation in object-oriented C++ using SDL2 media layer.

The project implements graphics, input handling, and game logic. Game logic uses a recursive flood 
fill based algorithm for path searching and mine detection.

Building the project

```sh
git clone
cd minesweeper
xcodebuild -project minesweeper.xcodeproj -scheme minesweeper build
open minesweeper.xcodeproj
```

## Screenshots

<p align="center">
	<img src="img/img1.png" alt="Minesweeper screenshot 1" width="31%" />
	<img src="img/img2.png" alt="Minesweeper screenshot 2" width="31%" />
	<img src="img/img3.png" alt="Minesweeper screenshot 3" width="31%" />
</p>

## Possible next steps

Enable the user to switch between grid sizes according to their preference instead of using fixed 
constants.