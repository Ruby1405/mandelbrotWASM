# A mandelbrot visualiser in Webassembly
Requires a http server to start.
For now scaling or translating the view requires recompiling.

## Description
This was a semi-explorative project that was done as a part of 2 week research-internship in Japan. The task was to create a graphical program that could be run on android. As I was acquainted to the raylib library I decided to write the mandelbrott set in C using Raylib for graphics and compiling it to web assembly to make it cross platform.

## Dependencies
**For running:** A http server
**For recompiling:** Emscripten, Raylib

## Replication
Follow [Raylib - Working for Web](https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5))
I don't remember if I used the makefile or if I compiled in command line (I might have done both)
Compile without ASYNCIFY
I found the flag `-sGL_ENABLE_GET_PROC_ADDRESS` was also needed.

## Running
If you are using visual studio you can open a live server from the `game.html` file and it should work fine. For any other platforms you just need to be able to host a http server.
[Simple HTTP Server (Fedir Tsapana)](https://play.google.com/store/search?q=simple+http+server&c=apps&hl=en&gl=US) worked when running on android.
