#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ncurses.h>

#define WIDTH 10
#define HEIGHT 20

#define MIN_DTIME 420000000
#define SPEED_PER_LVL 20000000

#define LEVEL_THRESHOLD 10

#define SYM_BLOCK "[]"
#define SYM_EMPTY " ."
#define SYM_VERT  "||"
#define SYM_HORZ  "=="

typedef struct {
	int x;
	int y;
} Point;

typedef struct {
	Point points[4];
	Point offset;
} Shape;

const Shape SHAPES[7] = {
	{{{ 0, 0}, {-1, 0}, { 1, 0}, {2, 0}}, {0, 0}}, //I
	{{{ 0, 0}, {-1, 0}, { 1, 0}, {1,-1}}, {0, 0}}, //J
	{{{ 0, 0}, {-1, 0}, {-1,-1}, {1, 0}}, {0, 0}}, //L
	{{{ 0, 0}, { 0, 1}, { 1, 1}, {1, 0}}, {0, 0}}, //O
	{{{ 0, 0}, { 0, 1}, {-1, 0}, {1, 1}}, {0, 0}}, //S
	{{{ 0, 0}, {-1, 0}, { 0,-1}, {1, 0}}, {0, 0}}, //T
	{{{ 0, 0}, { 0, 1}, {-1, 1}, {1, 0}}, {0, 0}}, //Z
};

typedef struct {
	int board[HEIGHT][WIDTH];
	Shape shape;
	Shape next;

	int lines;
	int level;
} Tetris;

int collides(Tetris* t){
	for(int j=0; j<4; j++){
		int x = t->shape.offset.x + t->shape.points[j].x;
		int y = t->shape.offset.y - t->shape.points[j].y;
		if(y < 0) continue;
		if(x < 0 || x >= WIDTH || y >= HEIGHT || t->board[y][x]){
			return 1;
		}
	}
	return 0;
}

void rotate_r(Tetris* t);
void rotate_l(Tetris* t){
	for(int i=0; i<4; i++){
		int x = -t->shape.points[i].y;
		t->shape.points[i].y = t->shape.points[i].x;
		t->shape.points[i].x = x;
	}

	if(collides(t)){
		rotate_r(t);
	}
}

void rotate_r(Tetris* t){
	for(int i=0; i<4; i++){
		int x = t->shape.points[i].y;
		t->shape.points[i].y =-t->shape.points[i].x;
		t->shape.points[i].x = x;
	}

	if(collides(t)){
		rotate_l(t);
	}
}

void move_piece(Tetris* t, int x, int y){
	t->shape.offset.x += x;
	t->shape.offset.y += y;

	if(collides(t)){
		t->shape.offset.x -= x;
		t->shape.offset.y -= y;
	}
}

void remove_row(Tetris* t, int row){
	for(int y=row; y>=0; y--){
		for(int x=0; x<WIDTH; x++){
			t->board[y][x] = (y == 0? 0 : t->board[y-1][x]);
		}
	}	
}

void check_row(Tetris* t){
	int rows = 0;
	for(int x,y=HEIGHT-1; y>=0; y--){
		for(x=0; x<WIDTH && t->board[y][x]; x++);
		
		if(x == WIDTH){
			remove_row(t, y);
			y++;
			rows++;
		}
	}
	t->lines += rows;
	if(rows != 0 && t->lines > t->level * LEVEL_THRESHOLD){
		t->level++;
	}
}

int check_loss(Tetris* t){
	for(int i=0; i<WIDTH; i++){
		if(t->board[0][i] != 0){
			return 1;
		}
	}
	return 0;
}

void lock_in(Tetris* t){
	for(int i=0; i<4; i++){
		int y = t->shape.offset.y - t->shape.points[i].y;
		int x = t->shape.offset.x + t->shape.points[i].x;
		if(y < 0) continue;
		t->board[y][x] = ~0;
	}
}

void new_piece(Tetris* t){
	t->shape = t->next;
	t->next = SHAPES[rand() % 7]; 
	t->shape.offset.x = 5;
	t->shape.offset.y = -0;
	t->next.offset.x = 13;
	t->next.offset.y = 1;
}

void tick(Tetris* t){
	int y = t->shape.offset.y;
	move_piece(t, 0, 1);
	if(y == t->shape.offset.y){
		lock_in(t);
		check_row(t);
		new_piece(t);
	}
}

void hard_drop(Tetris* t){
	int y;
	do{
		y = t->shape.offset.y;
		move_piece(t, 0, 1);
	} while(y != t->shape.offset.y);
	tick(t);
}

int input(Tetris* t){
	switch(getch()){
		case 'q': 
			return 1; 
		case 'h':
			move_piece(t, -1, 0);
			break;
		case 'l':
			move_piece(t, 1, 0);
			break;
		case 'j':
			move_piece(t, 0, 1);
			break;
		case 'k':
			rotate_r(t);
			break;
		case 'u':
			move_piece(t, 0, -1);
			break;
		case ' ':
			hard_drop(t);	
			break;
		default:
			break;
	}
	return 0;
}

void draw_shape(Shape* s){
	for(int i=0; i<4; i++){
		int y = s->offset.y - s->points[i].y + 1;
		int x = 2*(s->offset.x + s->points[i].x + 1);
		if(y > 0){
			mvprintw(y, x, "%s", SYM_BLOCK);
		}
	}
}

void draw_next(Tetris* t){
	for(int y=1; y<5; y++){
		for(int x=24; x<33; x++){
			mvprintw(y, x, "%s", "  ");
		}
	}
	draw_shape(&t->next);
}

void draw_board(Tetris* t){
	for(int y=0; y<HEIGHT; y++){
		move(y+1, 2);
		for(int x=0; x<WIDTH; x++){
			printw("%s", (t->board[y][x] == 0? SYM_EMPTY : SYM_BLOCK));
		}
	}
	mvprintw(6, 25, "Level: %d", t->level);
	mvprintw(7, 25, "Lines: %d", t->lines);
	draw_shape(&t->shape);
	draw_next(t);
	refresh();
}

void draw_box(int x, int y, int w, int h){
	for(int i=0; i<h; i++){
		for(int j=0; j<w; j++){
			if((i == 0 || i == h-1) && (j == 0 || j == w-1)){
				mvprintw(y+i, x+j+j, "%s", SYM_BLOCK);
			}else if(i == 0 || i == h-1){
				mvprintw(y+i, x+j+j, "%s", SYM_HORZ);
			}else if(j == 0 || j == w-1){
				mvprintw(y+i, x+j+j, "%s", SYM_VERT);
			}
		}
	}
}

long get_nanos(void) {
	struct timespec ts;
	timespec_get(&ts, TIME_UTC);
	return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

void start(Tetris* t){
	long start = 0, dt = 0;

	while(1){
		start = get_nanos();
		
		if(input(t)) return;
		draw_board(t);		
		
		dt += (get_nanos() - start);

		if(dt > (MIN_DTIME - (t->level * SPEED_PER_LVL))){
			tick(t);
			if(check_loss(t)){
				//pause on game over
				timeout(-1);
				getch();
				return;
			}
			dt = 0;
		}
	}
}

void init_tetris(Tetris* t){
	memset(t, 0, sizeof(Tetris));
	new_piece(t);
	new_piece(t);
}

void init_curses(void){
	initscr();
	raw();
	curs_set(0);
	timeout(0);
	clear();
	noecho();
}

void init(void){
	srand(time(NULL));
	init_curses();
	draw_box(22, 0, 7, 6);
	draw_box(0, 0, 12, 22);
}

int main(void){
	init();

	Tetris t;
	init_tetris(&t);
	start(&t);
	
	endwin();
	return 0; 
}
