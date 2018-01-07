
// navigation
extern void (*key_cb)(int);

// message
void ecb_message(int act);
void draw_message(char *msg, int special);

// main menu
void redraw_main();
void draw_slots();
void ecb_main(int act);

extern int maincount;
extern int mainsel;

// options
void ecb_options(int act);
void ecb_subopt(int act);
void redraw_options();
void draw_suboptions();

