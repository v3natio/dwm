/* See LICENSE file for copyright and license details. */

/* appearance */
static unsigned int borderpx = 3; // border pixel of windows
static const unsigned int gappx = 6; // gaps between windows
static unsigned int snap = 32; // snap pixel
static const int swallowfloating = 0; // 1 means swallow floating windows by default
static int showbar = 1; // 0 means no bar
static int topbar = 1; // 0 means bottom bar
static char font[] = "JetbrainsMono Nerd Font:size=15:antialias=true:autohint=true";
static char dmenufont[] = "JetbrainsMono Nerd Font:size=15:antialias=true:autohint=true";
static const char *fonts[] = { "JetbrainsMono Nerd Font:size=15:antialias=true:autohint=true" };
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#005577";
static char selbgcolor[] = "#005577";
static char termcol0[] = "#000000";
static char termcol1[] = "#ff0000";
static char termcol2[] = "#33ff00";
static char termcol3[] = "#ff0099";
static char termcol4[] = "#0066ff";
static char termcol5[] = "#cc00ff";
static char termcol6[] = "#00ffff";
static char termcol7[] = "#d0d0d0";
static char termcol8[]  = "#808080";
static char termcol9[]  = "#ff0000";
static char termcol10[] = "#33ff00";
static char termcol11[] = "#ff0099";
static char termcol12[] = "#0066ff";
static char termcol13[] = "#cc00ff";
static char termcol14[] = "#00ffff";
static char termcol15[] = "#ffffff";
static char *termcolor[] = {
  termcol0,
  termcol1,
  termcol2,
  termcol3,
  termcol4,
  termcol5,
  termcol6,
  termcol7,
  termcol8,
  termcol9,
  termcol10,
  termcol11,
  termcol12,
  termcol13,
  termcol14,
  termcol15,
};
static char *colors[][3] = {
  /* foreground, background, border */
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel]  = { selfgcolor, selbgcolor, selbordercolor },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
  /*
  * xprop(1):
  *	WM_CLASS(STRING) = instance, class
  *	WM_NAME(STRING) = title
  */
  /* class, instance, title, tags mask, isfloating, isterminal, noswallow, monitor */
  { "Gimp", NULL, NULL, 1 << 7, 0, 0, 0, -1 },
  { NULL, NULL, "Event Tester", 0, 0, 0, 1, -1 }, // xev
};

/* layout(s) */
static const float mfact = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster = 1; /* number of clients in master area */
static const int resizehints = 0; /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
  /* symbol, arrange function */
  { "[M]", monocle }, // Default: windows on top of each other
  { "[]=", tile }, // Tile: master on left, slaves on right
  { "[D]", deck }, // Deck: master on left, slaves monocle on right
  { ">M>", centeredfloatingmaster }, // Floating Center: master floats in center
  { "|M|", centeredmaster }, // Center: master on center, slaves on sides
  { "><>", NULL }, // Floating: window is freefloat
  { NULL, NULL}, // placeholder for cycle-layouts
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY, KEY, view, {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask, KEY, toggleview, {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask, KEY, tag, {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY, toggletag, {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
  { MOD, XK_j, ACTION##stack, {.i = INC(+1) } }, \
  { MOD, XK_k, ACTION##stack, {.i = INC(-1) } }, \
  { MOD, XK_v, ACTION##stack, {.i = 0 } },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; // component of dmenucmd, manipulated in spawn()
static const char *dmenucmd[] = { "dmenu_recency", "-m", dmenumon, NULL };
static const char *termcmd[]  = { "st", NULL };

#include <X11/XF86keysym.h> // add XF86 keys support
#include "patches/shiftview.c" // add shiftview patch

static const Key keys[] = {
  /* modifier, key, function, argument */
  // main
  STACKKEYS(MODKEY, focus)
  STACKKEYS(MODKEY|ShiftMask, push)
  TAGKEYS(XK_1, 0)
  TAGKEYS(XK_2, 1)
  TAGKEYS(XK_3, 2)
  TAGKEYS(XK_4, 3)
  TAGKEYS(XK_5, 4)
  TAGKEYS(XK_6, 5)
  TAGKEYS(XK_7, 6)
  TAGKEYS(XK_8, 7)
  TAGKEYS(XK_9, 8)
  { MODKEY, XK_0,	view,	{.ui = ~0 } },
  { MODKEY|ShiftMask, XK_0,	tag,{.ui = ~0 } },
  { MODKEY, XK_F12, xrdb, {.v = NULL } },

  // main
  { MODKEY, XK_BackSpace, spawn, SHCMD("dmenu_system") },
	{ MODKEY, XK_d, spawn, SHCMD("dmenu_recency") },
	{ MODKEY, XK_Return, spawn, {.v = termcmd } },
  { MODKEY|ShiftMask, XK_Return, spawn, SHCMD("samedir") },
  { MODKEY, XK_q, killclient, {0} },
  { MODKEY|ShiftMask, XK_e, quit, {0} },

  // launch scripts
  { MODKEY, XK_w, spawn, SHCMD("dmenu_network") },
  { MODKEY, XK_F8, spawn, SHCMD("dmenu_blue") },
  { MODKEY, XK_F7, spawn, SHCMD("dmenu_display") },
  { MODKEY, XK_F11, spawn, SHCMD("dmenu_mount") },
  { MODKEY|ShiftMask, XK_F11, spawn, SHCMD("dmenu_unmount") },
  { 0, XK_Print, spawn, SHCMD("dmenu_maim") },
  { MODKEY, XK_Print,  spawn, SHCMD("dmenu_record") },
  { MODKEY|ShiftMask, XK_Print, spawn, SHCMD("dmenu_record kill") },

  // launch programs
  { MODKEY|ShiftMask, XK_w, spawn, SHCMD("$BROWSER") },
  { MODKEY, XK_r, spawn, SHCMD("$TERMINAL -e yazi") },
  { MODKEY|ShiftMask, XK_r, spawn, SHCMD("$TERMINAL -e btm") },
  { MODKEY, XK_t, spawn, SHCMD("obsidian") },
  { MODKEY, XK_n, spawn, SHCMD("$TERMINAL -e newsboat") },
  { MODKEY, XK_m, spawn, SHCMD("$TERMINAL -e spotify_player") },
  { MODKEY, XK_a, spawn, SHCMD("$TERMINAL -e pulsemixer; kill -44 $(pidof dwmblocks)") },

  // brightness
  { 0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl --device='intel_backlight' --quiet set +5%") },
	{ 0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl --device='intel_backlight' --quiet set 5%-") },
  { 0, XF86XK_Launch3, spawn, SHCMD("xsct -t") },

  // multimedia
  { 0, XF86XK_AudioMute, spawn, SHCMD("amixer set Master toggle; kill -44 $(pidof dwmblocks)") },
  { 0, XF86XK_AudioLowerVolume, spawn,	SHCMD("amixer set Master 5%-; kill -44 $(pidof dwmblocks)") },
  { 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("amixer set Master 5%+; kill -44 $(pidof dwmblocks)") },
  { 0, XF86XK_AudioPlay, spawn, SHCMD("playerctl -p %any play-pause") },
  { 0, XF86XK_AudioPrev, spawn, SHCMD("playerctl -p %any previous") },
  { 0, XF86XK_AudioNext, spawn, SHCMD("playerctl -p %any next") },
  { 0, XF86XK_Launch2, spawn, SHCMD("playerctl -p %any play-pause") },
  { MODKEY, XK_comma, spawn, SHCMD("playerctl -p %any previous") },
  { MODKEY, XK_period, spawn, SHCMD("playerctl -p %any next") },

  // layouts
  { MODKEY, XK_l, setmfact, {.f = +0.05} },
  { MODKEY, XK_h, setmfact, {.f = -0.05} },
  { MODKEY, XK_o, shiftview, {.i = +1 } },
  { MODKEY, XK_y, shiftview, {.i = -1 } },
  { MODKEY, XK_Tab, view, {0} },
  { MODKEY|ShiftMask, XK_u, cyclelayout, {.i = -1 } },
  { MODKEY|ShiftMask, XK_i, cyclelayout, {.i = +1 } },
  { MODKEY, XK_u, setlayout, {.v = &layouts[0]} }, // tile
  { MODKEY, XK_i, setlayout, {.v = &layouts[1]} }, // monocle
  { MODKEY, XK_g,  setgaps, {.i = +1 } },
  { MODKEY|ShiftMask, XK_g, setgaps, {.i = -1 } },
  { MODKEY|ControlMask, XK_g, setgaps, {.i = 0 } },
  { MODKEY, XK_x, incnmaster, {.i = +1 } },
  { MODKEY|ShiftMask, XK_x, incnmaster, {.i = -1 } },
  { MODKEY|ShiftMask, XK_space, togglefloating, {0} },
  { MODKEY, XK_f, togglefullscr, {0} },
  { MODKEY, XK_b, togglebar, {0} },
  { MODKEY, XK_space, zoom, {0} },
  { MODKEY, XK_s, togglesticky, {0} },
  { MODKEY, XK_Down, moveresize, {.v = "0x 25y 0w 0h" } },
  { MODKEY, XK_Up, moveresize, {.v = "0x -25y 0w 0h" } },
  { MODKEY, XK_Right, moveresize, {.v = "25x 0y 0w 0h" } },
  { MODKEY, XK_Left, moveresize, {.v = "-25x 0y 0w 0h" } },
  { MODKEY|ShiftMask, XK_Down, moveresize, {.v = "0x 0y 0w 25h" } },
  { MODKEY|ShiftMask, XK_Up, moveresize, {.v = "0x 0y 0w -25h" } },
  { MODKEY|ShiftMask, XK_Right, moveresize, {.v = "0x 0y 25w 0h" } },
  { MODKEY|ShiftMask, XK_Left, moveresize, {.v = "0x 0y -25w 0h" } },

  // monitors
	//{ MODKEY, XK_Right, focusmon, {.i = +1 } },
	//{ MODKEY|ShiftMask, XK_Right, tagmon, {.i = +1 } },
	//{ MODKEY, XK_Left, focusmon, {.i = -1 } },
	//{ MODKEY|ShiftMask, XK_Left, tagmon, {.i = -1 } },
};

/* button definitions */
/*
* click can be: ClkTagBar, ClkLtSymbol,
* ClkStatusText, ClkClientWin, or ClkRootWin
*/
static const Button buttons[] = {
  // click, event mask, button, function, argument
  { ClkLtSymbol, 0, Button1, setlayout, {0} },
  { ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[1]} },
  { ClkStatusText, 0, Button2, spawn, {.v = termcmd } },
  { ClkClientWin, MODKEY, Button1, movemouse, {0} },
  { ClkClientWin, MODKEY, Button2, togglefloating, {0} },
  { ClkClientWin, MODKEY, Button3, resizemouse, {0} },
  { ClkTagBar, 0, Button1, view, {0} },
  { ClkTagBar, 0, Button3, toggleview, {0} },
  { ClkTagBar, MODKEY, Button1, tag, {0} },
  { ClkTagBar, MODKEY, Button3, toggletag, {0} },
};

