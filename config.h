// See LICENSE file for copyright and license details.

// Appearance
static unsigned int borderpx = 3;
static unsigned int snap = 32; // snap pixel
static unsigned int gappih = 6;
static unsigned int gappiv = 6;
static unsigned int gappoh = 6;
static unsigned int gappov = 6;
static const int smartgaps = 1; // 0 is no smartgaps
static int showbar = 1; // 0 is no bar
static int topbar = 1; // 0 is bottom bar
static char *fonts[] = { "JetbrainsMono Nerd Font:size=13:antialias=true:autohint=true" };
static char normbgcolor[] = "#222222";
static char normbordercolor[] = "#444444";
static char normfgcolor[] = "#bbbbbb";
static char selfgcolor[] = "#eeeeee";
static char selbordercolor[] = "#770000";
static char selbgcolor[] = "#005577";
static char *colors[][3] = {
                // foreground, background, border
  [SchemeNorm] = { normfgcolor, normbgcolor, normbordercolor },
  [SchemeSel] = { selfgcolor, selbgcolor, selbordercolor },
};

// Tagging
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	// class, instance, title, tags mask, isfloating, isterminal, noswallow, monitor
	{ "Gimp", NULL, NULL, 1 << 7, 0, 0, 0, -1 },
	{ "inkscape", NULL, NULL, 1 << 7, 0, 0, 0, -1 },
	{ "zoom", NULL, NULL, 1 << 8, 0, 0, 0, -1 },
};

// Layouts
static float mfact = 0.55; // master area size
static int nmaster = 1; // clients in master area
static int resizehints = 0; // 1 is respect size hints in tiled resizals
static const Layout layouts[] = {
	// symbol, arrange, function
	{ "[]=", tile }, // Default: Master on left, slaves on right
	{ "[M]", monocle }, // Monocle: Windows on top of each other
	{ "><>", NULL }, // Floating: Window is freefloat
};

// Key definitions
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
/*{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } }, \
	{ MOD, XK_a,     ACTION##stack, {.i = 1 } }, \
	{ MOD, XK_z,     ACTION##stack, {.i = 2 } }, \
	{ MOD, XK_x,     ACTION##stack, {.i = -1 } },*/

// Spawn shell commands
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

// Xresources preferences to load at startup
ResourcePref resources[] = {
  { "color0", STRING, &normbordercolor },
  { "color10", STRING, &selbordercolor },
  { "color0", STRING, &normbgcolor },
  { "color8", STRING, &normfgcolor },
  { "color0", STRING, &selfgcolor },
  { "color8", STRING, &selbgcolor },
  { "borderpx", INTEGER, &borderpx },
  { "snap", INTEGER, &snap },
  { "showbar", INTEGER, &showbar },
  { "topbar", INTEGER, &topbar },
  { "nmaster", INTEGER, &nmaster },
  { "resizehints", INTEGER, &resizehints },
  { "mfact", FLOAT, &mfact },
};

// commands when clicking statusbar
static const StatusCmd statuscmds[] = {
	{ "notify-send Mouse$BUTTON", 1 },
};
static const char *statuscmd[] = { "/bin/sh", "-c", NULL, NULL };

#include <X11/XF86keysym.h>
#include "patches/shiftview.c"

static Key keys[] = {
	// modifier, key, function, argument
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
  { MODKEY, XK_BackSpace, spawn, SHCMD("dmenu_system") },
	{ MODKEY, XK_d, spawn, SHCMD("dmenu_recency") },
	{ MODKEY, XK_q, killclient, {0} },
  { MODKEY|ShiftMask, XK_e, quit, {0} },
	{ 0, XF86XK_MonBrightnessUp, spawn, SHCMD("brightnessctl set +10%") },
  { MODKEY, XK_F6, spawn, SHCMD("sct") },
	{ 0, XF86XK_MonBrightnessDown, spawn, SHCMD("brightnessctl set 10%-") },
  { MODKEY, XK_F5, spawn, SHCMD("sct 2700") },

  // launch programs
	{ MODKEY, XK_Return, spawn, SHCMD("$TERMINAL") },
	{ MODKEY|ShiftMask, XK_Return, spawn, SHCMD("samedir") },
  { MODKEY, XK_r, spawn, SHCMD("$TERMINAL -e yazi") },
  { MODKEY|ShiftMask, XK_r, spawn, SHCMD("$TERMINAL -e btm") },
  { MODKEY, XK_t, spawn, SHCMD("obsidian") },
  { MODKEY, XK_n, spawn, SHCMD("$TERMINAL -e newsboat") },
  { MODKEY, XK_m, spawn, SHCMD("$TERMINAL -e ncspot") },
  { MODKEY, XK_a, spawn, SHCMD("$TERMINAL -e pulsemixer; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_Calculator, spawn, SHCMD("$TERMINAL -e bc -l") },
  { MODKEY|ShiftMask, XK_w, spawn, SHCMD("$BROWSER") },

  // launch scripts
  { MODKEY, XK_w, spawn, SHCMD("dmenu_network") },
  { MODKEY, XK_F8, spawn, SHCMD("dmenu_blue") },
  { MODKEY, XK_F7, spawn, SHCMD("dmenu_display") },
  { MODKEY, XK_F11, spawn, SHCMD("dmenu_mount") },
  { MODKEY|ShiftMask, XK_F11, spawn, SHCMD("dmenu_unmount") },
  { 0, XK_Print, spawn, SHCMD("dmenu_maim") },
  { MODKEY, XK_Print,  spawn, SHCMD("dmenu_record") },
  { MODKEY|ShiftMask, XK_Print, spawn, SHCMD("dmenu_record kill") },

  // multimedia
	{ 0, XF86XK_AudioMute, spawn, SHCMD("amixer set Master toggle; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioLowerVolume, spawn,	SHCMD("amixer set Master 5%-; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioRaiseVolume, spawn, SHCMD("amixer set Master 5%+; kill -44 $(pidof dwmblocks)") },
	{ 0, XF86XK_AudioPlay, spawn, SHCMD("playerctl -p ncspot,mpv,%any play-pause") },
	{ 0, XF86XK_AudioPrev, spawn, SHCMD("playerctl -p ncspot,mpv,%any previous") },
  { 0, XF86XK_AudioNext, spawn, SHCMD("playerctl -p ncspot,mpv,%any next") },

  // layouts
  { MODKEY, XK_u, setlayout, {.v = &layouts[0]} }, // tile
	{ MODKEY, XK_i, setlayout, {.v = &layouts[1]} }, // monocle
	{ MODKEY, XK_l, setmfact, {.f = +0.05} },
	{ MODKEY, XK_h, setmfact, {.f = -0.05} },
  { MODKEY, XK_o, shiftview, {.i = +1 } },
  { MODKEY, XK_y, shiftview, {.i = -1 } },
	{ MODKEY, XK_Tab, view, {0} },
  { MODKEY, XK_g, incrgaps, {.i = +3} },
  { MODKEY|ShiftMask, XK_g, incrgaps, {.i = -3} },
  { MODKEY|ControlMask, XK_g, defaultgaps, {0} },
	{ MODKEY, XK_x, incnmaster, {.i = +1 } },
	{ MODKEY|ShiftMask, XK_x, incnmaster, {.i = -1 } },
	{ MODKEY|ShiftMask, XK_space, togglefloating, {0} },
	{ MODKEY, XK_f, togglefullscr, {0} },
	{ MODKEY, XK_b, togglebar, {0} },
	{ MODKEY, XK_space, zoom, {0} },

  // monitors
	{ MODKEY, XK_Right, focusmon, {.i = +1 } },
	{ MODKEY|ShiftMask, XK_Right, tagmon, {.i = +1 } },
	{ MODKEY, XK_Left, focusmon, {.i = -1 } },
	{ MODKEY|ShiftMask, XK_Left, tagmon, {.i = -1 } },
};

// Button definitions
static Button buttons[] = {
	// click, event mask, button, function, argument
	{ ClkLtSymbol, 0, Button1, setlayout, {0} },
	{ ClkLtSymbol, 0, Button3, setlayout, {.v = &layouts[1]} },
	{ ClkWinTitle, 0, Button2, zoom, {0} },
	{ ClkClientWin, MODKEY, Button1, movemouse, {0} },
	{ ClkClientWin, MODKEY, Button2, togglefloating, {0} },
	{ ClkClientWin, MODKEY, Button3, resizemouse, {0} },
	{ ClkTagBar, 0, Button1, view, {0} },
	{ ClkTagBar, 0, Button3, toggleview, {0} },
	{ ClkTagBar, MODKEY, Button1, tag, {0} },
	{ ClkTagBar, MODKEY, Button3, toggletag, {0} },
};
