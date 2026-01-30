# Hate2D
Hate2D is a simple framework for creating 2D games which is based on Raylib and EpsiLang.

## Dependencies
- Raylib
- EpsiLang

## Hello, World!
```c
init_window(800, 600, "Hello, World!");
clear_background(DARK_GRAY);

while !window_should_close() {
	begin_drawing();
	clear_background(DARK_GRAY);
	draw_rect(100, 100, 200, 300, RED);
	end_drawing();
}

close_window();
```
