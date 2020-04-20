#ifndef MICROUI_H
#define MICROUI_H

#define MU_COMMANDLIST_SIZE     (256 * 1024)
#define MU_ROOTLIST_SIZE        32
#define MU_CONTAINERSTACK_SIZE  32
#define MU_CLIPSTACK_SIZE       32
#define MU_IDSTACK_SIZE         32
#define MU_LAYOUTSTACK_SIZE     16
#define MU_CONTAINERPOOL_SIZE   48
#define MU_TREENODEPOOL_SIZE    48
#define MU_MAX_WIDTHS           16
#define MU_REAL                 float
#define MU_REAL_FMT             "%.3g"
#define MU_SLIDER_FMT           "%.2f"
#define MU_MAX_FMT              127

#define mu_stack(T, n)          struct { int idx; T items[n]; }
#define mu_min(a, b)            ((a) < (b) ? (a) : (b))
#define mu_max(a, b)            ((a) > (b) ? (a) : (b))
#define mu_clamp(x, a, b)       mu_min(b, mu_max(a, x))

enum {
  MU_CLIP_PART = 1,
  MU_CLIP_ALL
};

enum {
  MU_COMMAND_JUMP = 1,
  MU_COMMAND_CLIP,
  MU_COMMAND_RECT,
  MU_COMMAND_TEXT,
  MU_COMMAND_ICON,
  MU_COMMAND_MAX
};

enum {
  MU_COLOR_TEXT,
  MU_COLOR_BORDER,
  MU_COLOR_WINDOWBG,
  MU_COLOR_TITLEBG,
  MU_COLOR_TITLETEXT,
  MU_COLOR_PANELBG,
  MU_COLOR_BUTTON,
  MU_COLOR_BUTTONHOVER,
  MU_COLOR_BUTTONFOCUS,
  MU_COLOR_BASE,
  MU_COLOR_BASEHOVER,
  MU_COLOR_BASEFOCUS,
  MU_COLOR_SCROLLBASE,
  MU_COLOR_SCROLLTHUMB,
  MU_COLOR_MAX
};

enum {
  MU_ICON_CLOSE = 1,
  MU_ICON_CHECK,
  MU_ICON_COLLAPSED,
  MU_ICON_EXPANDED,
  MU_ICON_MAX
};

enum {
  MU_RES_ACTIVE       = (1 << 0),
  MU_RES_SUBMIT       = (1 << 1),
  MU_RES_CHANGE       = (1 << 2)
};

enum {
  MU_OPT_ALIGNCENTER  = (1 << 0),
  MU_OPT_ALIGNRIGHT   = (1 << 1),
  MU_OPT_NOINTERACT   = (1 << 2),
  MU_OPT_NOFRAME      = (1 << 3),
  MU_OPT_NORESIZE     = (1 << 4),
  MU_OPT_NOSCROLL     = (1 << 5),
  MU_OPT_NOCLOSE      = (1 << 6),
  MU_OPT_NOTITLE      = (1 << 7),
  MU_OPT_HOLDFOCUS    = (1 << 8),
  MU_OPT_AUTOSIZE     = (1 << 9),
  MU_OPT_POPUP        = (1 << 10),
  MU_OPT_CLOSED       = (1 << 11),
  MU_OPT_EXPANDED     = (1 << 12)
};

enum {
  MU_MOUSE_LEFT       = (1 << 0),
  MU_MOUSE_RIGHT      = (1 << 1),
  MU_MOUSE_MIDDLE     = (1 << 2)
};

enum {
  MU_KEY_SHIFT        = (1 << 0),
  MU_KEY_CTRL         = (1 << 1),
  MU_KEY_ALT          = (1 << 2),
  MU_KEY_BACKSPACE    = (1 << 3),
  MU_KEY_RETURN       = (1 << 4)
};

typedef MU_REAL mu_Real;
typedef void * mu_Font;

typedef struct { int x, y; } mu_Vec2;
typedef struct { int x, y, w, h; } mu_Rect;
typedef struct { unsigned char r, g, b, a; } mu_Color;

typedef struct { int type, size; } mu_BaseCommand;
typedef struct { mu_BaseCommand base; void *dst; } mu_JumpCommand;
typedef struct { mu_BaseCommand base; mu_Rect rect; } mu_ClipCommand;
typedef struct { mu_BaseCommand base; mu_Rect rect; mu_Color color; } mu_RectCommand;
typedef struct { mu_BaseCommand base; mu_Font font; mu_Vec2 pos; mu_Color color; char str[1]; } mu_TextCommand;
typedef struct { mu_BaseCommand base; mu_Rect rect; int id; mu_Color color; } mu_IconCommand;

typedef union
{
	int type;
	mu_BaseCommand base;
	mu_JumpCommand jump;
	mu_ClipCommand clip;
	mu_RectCommand rect;
	mu_TextCommand text;
	mu_IconCommand icon;
} mu_Command;

struct xui_poolitem_t
{
	unsigned int id;
	int last_update;
};

struct xui_layout_t {
	mu_Rect body;
	mu_Rect next;
	mu_Vec2 position;
	mu_Vec2 size;
	mu_Vec2 max;
	int widths[MU_MAX_WIDTHS];
	int items;
	int item_index;
	int next_row;
	int next_type;
	int indent;
};

struct xui_container_t
{
	mu_Command * head, * tail;
	mu_Rect rect;
	mu_Rect body;
	mu_Vec2 content_size;
	mu_Vec2 scroll;
	int zindex;
	int open;
};

struct xui_style_t
{
	mu_Font font;
	mu_Vec2 size;
	int padding;
	int spacing;
	int indent;
	int title_height;
	int scrollbar_size;
	int thumb_size;
	mu_Color colors[MU_COLOR_MAX];
};

struct mu_context_t
{
	/* callbacks */
	int (*text_width)(mu_Font font, const char *str, int len);
	int (*text_height)(mu_Font font);
	void (*draw_frame)(struct mu_context_t *ctx, mu_Rect rect, int colorid);
	/* core state */
	struct xui_style_t _style;
	struct xui_style_t *style;
	unsigned int hover;
	unsigned int focus;
	unsigned int last_id;
	mu_Rect last_rect;
	int last_zindex;
	int updated_focus;
	int frame;
	struct xui_container_t *hover_root;
	struct xui_container_t *next_hover_root;
	struct xui_container_t *scroll_target;
	char number_edit_buf[MU_MAX_FMT];
	unsigned int number_edit;
	/* stacks */
	mu_stack(char, MU_COMMANDLIST_SIZE)
	command_list;
	mu_stack(struct xui_container_t*, MU_ROOTLIST_SIZE)
	root_list;
	mu_stack(struct xui_container_t*, MU_CONTAINERSTACK_SIZE)
	container_stack;
	mu_stack(mu_Rect, MU_CLIPSTACK_SIZE)
	clip_stack;
	mu_stack(unsigned int, MU_IDSTACK_SIZE)
	id_stack;
	mu_stack(struct xui_layout_t, MU_LAYOUTSTACK_SIZE)
	layout_stack;
	/* retained state pools */
	struct xui_poolitem_t container_pool[MU_CONTAINERPOOL_SIZE];
	struct xui_container_t containers[MU_CONTAINERPOOL_SIZE];
	struct xui_poolitem_t treenode_pool[MU_TREENODEPOOL_SIZE];
	/* input state */
	mu_Vec2 mouse_pos;
	mu_Vec2 last_mouse_pos;
	mu_Vec2 mouse_delta;
	mu_Vec2 scroll_delta;
	int mouse_down;
	int mouse_pressed;
	int key_down;
	int key_pressed;
	char input_text[32];
};

mu_Vec2 mu_vec2(int x, int y);
mu_Rect mu_rect(int x, int y, int w, int h);
mu_Color mu_color(int r, int g, int b, int a);

void mu_init(struct mu_context_t *ctx);
void mu_begin(struct mu_context_t *ctx);
void mu_end(struct mu_context_t *ctx);
void mu_set_focus(struct mu_context_t *ctx, unsigned int id);
unsigned int mu_get_id(struct mu_context_t *ctx, const void *data, int size);
void mu_push_id(struct mu_context_t *ctx, const void *data, int size);
void mu_pop_id(struct mu_context_t *ctx);
void mu_push_clip_rect(struct mu_context_t *ctx, mu_Rect rect);
void mu_pop_clip_rect(struct mu_context_t *ctx);
mu_Rect mu_get_clip_rect(struct mu_context_t *ctx);
int mu_check_clip(struct mu_context_t *ctx, mu_Rect r);
struct xui_container_t* mu_get_current_container(struct mu_context_t *ctx);
struct xui_container_t* mu_get_container(struct mu_context_t *ctx, const char *name);
void mu_bring_to_front(struct mu_context_t *ctx, struct xui_container_t *cnt);

int mu_pool_init(struct mu_context_t *ctx, struct xui_poolitem_t *items, int len, unsigned int id);
int mu_pool_get(struct mu_context_t *ctx, struct xui_poolitem_t *items, int len, unsigned int id);
void mu_pool_update(struct mu_context_t *ctx, struct xui_poolitem_t *items, int idx);

void mu_input_mousemove(struct mu_context_t *ctx, int x, int y);
void mu_input_mousedown(struct mu_context_t *ctx, int x, int y, int btn);
void mu_input_mouseup(struct mu_context_t *ctx, int x, int y, int btn);
void mu_input_scroll(struct mu_context_t *ctx, int x, int y);
void mu_input_keydown(struct mu_context_t *ctx, int key);
void mu_input_keyup(struct mu_context_t *ctx, int key);
void mu_input_text(struct mu_context_t *ctx, const char *text);

mu_Command* mu_push_command(struct mu_context_t *ctx, int type, int size);
int mu_next_command(struct mu_context_t *ctx, mu_Command **cmd);
void mu_set_clip(struct mu_context_t *ctx, mu_Rect rect);
void mu_draw_rect(struct mu_context_t *ctx, mu_Rect rect, mu_Color color);
void mu_draw_box(struct mu_context_t *ctx, mu_Rect rect, mu_Color color);
void mu_draw_text(struct mu_context_t *ctx, mu_Font font, const char *str, int len, mu_Vec2 pos, mu_Color color);
void mu_draw_icon(struct mu_context_t *ctx, int id, mu_Rect rect, mu_Color color);

void mu_layout_row(struct mu_context_t *ctx, int items, const int *widths, int height);
void mu_layout_width(struct mu_context_t *ctx, int width);
void mu_layout_height(struct mu_context_t *ctx, int height);
void mu_layout_begin_column(struct mu_context_t *ctx);
void mu_layout_end_column(struct mu_context_t *ctx);
void mu_layout_set_next(struct mu_context_t *ctx, mu_Rect r, int relative);
mu_Rect mu_layout_next(struct mu_context_t *ctx);

void mu_draw_control_frame(struct mu_context_t *ctx, unsigned int id, mu_Rect rect, int colorid, int opt);
void mu_draw_control_text(struct mu_context_t *ctx, const char *str, mu_Rect rect, int colorid, int opt);
int mu_mouse_over(struct mu_context_t *ctx, mu_Rect rect);
void mu_update_control(struct mu_context_t *ctx, unsigned int id, mu_Rect rect, int opt);

#define mu_button(ctx, label)             mu_button_ex(ctx, label, 0, MU_OPT_ALIGNCENTER)
#define mu_textbox(ctx, buf, bufsz)       mu_textbox_ex(ctx, buf, bufsz, 0)
#define mu_slider(ctx, value, lo, hi)     mu_slider_ex(ctx, value, lo, hi, 0, MU_SLIDER_FMT, MU_OPT_ALIGNCENTER)
#define mu_number(ctx, value, step)       mu_number_ex(ctx, value, step, MU_SLIDER_FMT, MU_OPT_ALIGNCENTER)
#define mu_header(ctx, label)             mu_header_ex(ctx, label, 0)
#define mu_begin_treenode(ctx, label)     mu_begin_treenode_ex(ctx, label, 0)
#define mu_begin_window(ctx, title, rect) mu_begin_window_ex(ctx, title, rect, 0)
#define mu_begin_panel(ctx, name)         mu_begin_panel_ex(ctx, name, 0)

void mu_text(struct mu_context_t *ctx, const char *text);
void mu_label(struct mu_context_t *ctx, const char *text);
int mu_button_ex(struct mu_context_t *ctx, const char *label, int icon, int opt);
int mu_checkbox(struct mu_context_t *ctx, const char *label, int *state);
int mu_textbox_raw(struct mu_context_t *ctx, char *buf, int bufsz, unsigned int id, mu_Rect r, int opt);
int mu_textbox_ex(struct mu_context_t *ctx, char *buf, int bufsz, int opt);
int mu_slider_ex(struct mu_context_t *ctx, mu_Real *value, mu_Real low, mu_Real high, mu_Real step, const char *fmt, int opt);
int mu_number_ex(struct mu_context_t *ctx, mu_Real *value, mu_Real step, const char *fmt, int opt);
int mu_header_ex(struct mu_context_t *ctx, const char *label, int opt);
int mu_begin_treenode_ex(struct mu_context_t *ctx, const char *label, int opt);
void mu_end_treenode(struct mu_context_t *ctx);
int mu_begin_window_ex(struct mu_context_t *ctx, const char *title, mu_Rect rect, int opt);
void mu_end_window(struct mu_context_t *ctx);
void mu_open_popup(struct mu_context_t *ctx, const char *name);
int mu_begin_popup(struct mu_context_t *ctx, const char *name);
void mu_end_popup(struct mu_context_t *ctx);
void mu_begin_panel_ex(struct mu_context_t *ctx, const char *name, int opt);
void mu_end_panel(struct mu_context_t *ctx);

#endif
