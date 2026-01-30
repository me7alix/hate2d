#include <stdio.h>
#include <raylib.h>
#include <epsl_api.h>
#include <math.h>

#define check_signature(ctx, cloc, msg, args, ...) \
	do { \
		int sig[] = {__VA_ARGS__}; \
		if (sizeof(sig)/sizeof(*sig) != (args)->count) { \
			epsl_throw_error(ctx, cloc, msg); \
			return EPSL_VNONE; \
		} \
		for (size_t i = 0; i < (args)->count; i++) { \
			if ((args)->items[i].kind != sig[i]) { \
				epsl_throw_error(ctx, cloc, msg); \
				return EPSL_VNONE; \
			} \
		} \
	} while (0)

EpslVal EInitWindow(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "(width: int, height: int, title: string) expected",
			&args, EPSL_VAL_INT, EPSL_VAL_INT, EPSL_VAL_STR);

	InitWindow(args.items[0].as.vint,
			args.items[1].as.vint,
			epsl_val_get_str(args.items[2])->items);

	return EPSL_VNONE;
}

EpslVal ECloseWindow(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "() expected", &args);
	CloseWindow();
	return EPSL_VNONE;
}

EpslVal EWindowShouldClose(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "() expected", &args);

	return (EpslVal){
		.kind = EPSL_VAL_BOOL,
		.as.vbool = WindowShouldClose(),
	};
}

EpslVal EBeginDrawing(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "() expected", &args);
	BeginDrawing();
	return EPSL_VNONE;
}

EpslVal EEndDrawing(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "() expected", &args);
	EndDrawing();
	return EPSL_VNONE;
}

EpslVal EClearBackground(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "(color: int) expected", &args, EPSL_VAL_INT);
	ClearBackground(GetColor(args.items[0].as.vint));
	return EPSL_VNONE;
}

EpslVal ESqrt(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	if (args.count != 1) goto error;

	switch (args.items[0].kind) {
	case EPSL_VAL_INT:
		return (EpslVal){
			.kind = EPSL_VAL_FLOAT,
			.as.vfloat = sqrt(args.items[0].as.vint),
		};
	case EPSL_VAL_FLOAT:
		return (EpslVal){
			.kind = EPSL_VAL_FLOAT,
			.as.vfloat = sqrt(args.items[0].as.vfloat),
		};
	default:;
	}

error:
	epsl_throw_error(ctx, cloc, "(int/float) expected");
	return EPSL_VNONE;
}

EpslVal EDrawRectangle(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "(x: int, y: int, w: int, h: int, color: int) expected",
			&args, EPSL_VAL_INT, EPSL_VAL_INT, EPSL_VAL_INT, EPSL_VAL_INT, EPSL_VAL_INT);

	DrawRectangle(args.items[0].as.vint,
			args.items[1].as.vint,
			args.items[2].as.vint,
			args.items[3].as.vint,
			GetColor(args.items[4].as.vint));

	return EPSL_VNONE;
}

EpslVal EDrawEllipse(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "(x: int, y: int, r1: float, r2: float, color: int) expected",
			&args, EPSL_VAL_INT, EPSL_VAL_INT, EPSL_VAL_FLOAT, EPSL_VAL_FLOAT, EPSL_VAL_INT);

	DrawEllipse(args.items[0].as.vint,
			args.items[1].as.vint,
			args.items[2].as.vfloat,
			args.items[3].as.vfloat,
			GetColor(args.items[4].as.vint));

	return EPSL_VNONE;
}

EpslVal EGetMouseX(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "() expected", &args);

	return (EpslVal){
		.kind = EPSL_VAL_INT,
		.as.vint = GetMouseX(),
	};
}

EpslVal EGetMouseY(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "() expected", &args);

	return (EpslVal){
		.kind = EPSL_VAL_INT,
		.as.vint = GetMouseY(),
	};
}

EpslVal EGetMouseDX(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "() expected", &args);

	return (EpslVal){
		.kind = EPSL_VAL_FLOAT,
		.as.vfloat = GetMouseDelta().x,
	};
}

EpslVal EGetMouseDY(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "() expected", &args);

	return (EpslVal){
		.kind = EPSL_VAL_FLOAT,
		.as.vfloat = GetMouseDelta().y,
	};
}

EpslVal EGetFrameTime(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "() expected", &args);

	return (EpslVal){
		.kind = EPSL_VAL_FLOAT,
		.as.vfloat = GetFrameTime(),
	};
}

EpslVal EIsMouseButtonPressed(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "(button: int) expected", &args, EPSL_VAL_INT);

	return (EpslVal){
		.kind = EPSL_VAL_BOOL,
		.as.vbool = IsMouseButtonPressed(args.items[0].as.vint),
	};
}

EpslVal EIsMouseButtonDown(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "(button: int) expected", &args, EPSL_VAL_INT);

	return (EpslVal){
		.kind = EPSL_VAL_BOOL,
		.as.vbool = IsMouseButtonDown(args.items[0].as.vint),
	};
}

EpslVal EIsMouseButtonReleased(EpslEvalCtx *ctx, EpslLocation cloc, EpslVals args) {
	check_signature(ctx, cloc, "(button: int) expected", &args, EPSL_VAL_INT);

	return (EpslVal){
		.kind = EPSL_VAL_BOOL,
		.as.vbool = IsMouseButtonReleased(args.items[0].as.vint),
	};
}

void print_error(EpslLocation loc, EpslErrorKind ek, char *msg) {
	size_t lines_num = loc.line_num + 1;
	size_t chars_num = loc.line_char - loc.line_start + 1;
	const char *err_type =
		ek == EPSL_ERROR_COMPTIME ? "comptime error:" :
		ek == EPSL_ERROR_RUNTIME  ? "runtime error:"  : "";

	printf("\n%s:%zu:%zu: %s %s\n", loc.file, lines_num, chars_num, err_type, msg);

	loc.line_char = loc.line_start;
	char err_ptr[512];
	size_t cnt = 0;

	while (*loc.line_char != '\n' && *loc.line_char != '\0'){
		printf("%c", *loc.line_char);
		if (cnt < chars_num - 1) {
			if (*loc.line_char != '\t') {
				err_ptr[cnt++] = ' ';
			} else {
				err_ptr[cnt++] = '\t';
			}
		}

		loc.line_char++;
	}

	printf("\n");
	err_ptr[cnt++] = '^';
	err_ptr[cnt] = '\0';
	printf("%s\n", err_ptr);
}

int main(int argc, char *argv[]) {
	char *input_file = argv[1];
	EpslCtx *ctx = epsl_from_file(print_error, input_file);
	if (!ctx) {
		fprintf(stderr, "No such file...\n");
		return 1;
	}

	epsl_reg_var(ctx, "DARK_GRAY", (EpslVal){
		.kind = EPSL_VAL_INT,
		.as.vint = 0x181818FF,
	});

	epsl_reg_var(ctx, "RED", (EpslVal){
		.kind = EPSL_VAL_INT,
		.as.vint = 0xFF0000FF,
	});

	epsl_reg_var(ctx, "MOUSE_RIGHT", (EpslVal){
		.kind = EPSL_VAL_INT,
		.as.vint = MOUSE_BUTTON_RIGHT,
	});

	epsl_reg_var(ctx, "MOUSE_LEFT", (EpslVal){
		.kind = EPSL_VAL_INT,
		.as.vint = MOUSE_BUTTON_LEFT,
	});

	epsl_reg_func(ctx, "sqrt",                     ESqrt);
	epsl_reg_func(ctx, "init_window",              EInitWindow);
	epsl_reg_func(ctx, "close_window",             ECloseWindow);
	epsl_reg_func(ctx, "window_should_close",      EWindowShouldClose);
	epsl_reg_func(ctx, "begin_drawing",            EBeginDrawing);
	epsl_reg_func(ctx, "end_drawing",              EEndDrawing);
	epsl_reg_func(ctx, "clear_background",         EClearBackground);
	epsl_reg_func(ctx, "draw_rect",                EDrawRectangle);
	epsl_reg_func(ctx, "draw_ellipse",             EDrawEllipse);
	epsl_reg_func(ctx, "get_mouse_x",              EGetMouseX);
	epsl_reg_func(ctx, "get_mouse_y",              EGetMouseY);
	epsl_reg_func(ctx, "get_mouse_dx",             EGetMouseDX);
	epsl_reg_func(ctx, "get_mouse_dy",             EGetMouseDY);
	epsl_reg_func(ctx, "get_frame_time",           EGetFrameTime);
	epsl_reg_func(ctx, "is_mouse_button_pressed",  EIsMouseButtonPressed);
	epsl_reg_func(ctx, "is_mouse_button_released", EIsMouseButtonReleased);
	epsl_reg_func(ctx, "is_mouse_button_down",     EIsMouseButtonDown);
	epsl_eval(ctx);
	return 0;
}
