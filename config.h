/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int gappx     = 2;        /* gap pixel between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "anonymous-pro:size=10:antialias=true; fontawesome:size=11:antialias=true" };
static const char dmenufont[]       = "anonymous-pro:size=10:antialias=true";
static const char col_bg_norm[]     = "#020203";
static const char col_nborder[]     = "#444444";
static const char col_fg_norm[]     = "#e6e6e6";
static const char col_fg_sel[]      = "#ff8800";
static const char col_fg_dmenu[]    = "#00fcc2";
static const char col_bg_sel[]      = "#060012";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_fg_norm, col_bg_norm, col_nborder  },
	[SchemeSel]  = { col_fg_sel , col_bg_sel ,  col_fg_dmenu },
};

/* tagging */
static const char *tags[] = { "", "", "", "", "", "", "", "", ""};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

#include "tcl.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "",      tile    },    /* first entry is default */
	{ "",      NULL    },    /* no layout function means floating behavior */
	{ "",     monocle },
	{ "",      tcl     },

};

/* key definitions */
#define MODKEY Mod4Mask
#define MODKEY2 Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_bg_norm, "-nf", col_fg_norm, "-sb", col_fg_dmenu, "-sf", col_bg_sel, NULL };
static const char *termcmd[]  = { "urxvt", NULL };

#include "shiftview.c"
#include "movestack.c"
static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_r,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,	                XK_n,  	   spawn,          SHCMD("pcmanfm &") },
	{ MODKEY,             		XK_g,	   spawn,          SHCMD("firefox https://chat.openai.com &") },
	{ MODKEY|ShiftMask,     	XK_t,	   spawn,          SHCMD("firefox https://tradingview.com/chart/jgs0xOGh &") },
	{ MODKEY,             		XK_e,	   spawn,          SHCMD("firefox https://excalidraw.com &") },
	{ MODKEY,             		XK_y,	   spawn,          SHCMD("firefox https://youtube.com &") },
	{ MODKEY,             		XK_f,	   spawn,          SHCMD("firefox &") },
	{ MODKEY2,	                XK_n,  	   spawn,          SHCMD("firefox https://notion.so &") },
	{ MODKEY,                       XK_d,	   spawn,          SHCMD("firefox https://discord.com/channels/@me &") },
	{ MODKEY,                       XK_s,	   spawn,          SHCMD("firefox https://open.spotify.com/collection/tracks &") },
	{ MODKEY2|ShiftMask,            XK_t,	   spawn,          SHCMD("firefox https://web.telegram.org/a &") },
	{ MODKEY|MODKEY2|ShiftMask,     XK_s,	   spawn,          SHCMD("shutdown now") },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY2,                      XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY2,                      XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },
	{ MODKEY2,                      XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY2,                      XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_comma,  setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY2,                      XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY2,                      XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY,	 	        XK_Tab, shiftview,         {.i = +1 } },
	{ MODKEY|ShiftMask ,            XK_Tab,	shiftview,         {.i = -1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

