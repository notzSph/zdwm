/* See LICENSE file for copyright and license details. */

/* PATCHES */
#include "tcl.c"
#include "shiftview.c"
#include "movestack.c"

/* MACROS */
#define MODKEY Mod4Mask
#define MODKEY2 Mod1Mask

#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,           view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,           toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,           tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,           toggletag,      {.ui = 1 << TAG} },

/* HELPERS */

/* Shell */
#define SHCMD(cmd)              { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* Firefox */
#define CMD_FF_DISCORD   "MOZ_WM_CLASS=FFDiscord   firefox --no-remote< --new-window 'https://discord.com/channels/@me'"
#define CMD_FF_TV        "MOZ_WM_CLASS=FFTrading   firefox --no-remote< --new-window 'https://tradingview.com/chart/jgs0xOGh'"
#define CMD_FF_GENERIC   "MOZ_WM_CLASS=FFBrowser   firefox --no-remote< --new-window"
#define CMD_FF_CHATGPT   "MOZ_WM_CLASS=FFChatGPT   firefox --no-remote< --new-window 'https://chat.openai.com'"
#define CMD_FF_EXCAL     "MOZ_WM_CLASS=FFExcal     firefox --no-remote< --new-window 'https://excalidraw.com'"
#define CMD_FF_NOTION    "MOZ_WM_CLASS=FFNotion    firefox --no-remote< --new-window 'https://notion.so'"
#define CMD_FF_YT        "MOZ_WM_CLASS=FFYoutube   firefox --no-remote< --new-window 'https://youtube.com'"
#define CMD_FF_SPOTIFY   "MOZ_WM_CLASS=FFSpotify   firefox --no-remote< --new-window 'https://open.spotify.com/collection/tracks'"
#define CMD_FF_TELEGRAM  "MOZ_WM_CLASS=FFTelegram  firefox --no-remote< --new-window 'https://web.telegram.org/a'"

/* STYLES */

/* Appearence */
static const unsigned int borderpx	= 1;
static const unsigned int gappx 	= 2;
static const unsigned int snap 		= 32;
static const int showbar 			= 1;
static const int topbar 			= 1;

/* Layouts */
static const float mfact 		= 0.55;
static const int nmaster 		= 1;
static const int resizehints 	= 1;
static const int lockfullscreen = 1;

static const Layout layouts[] = {
	/* symbol	arrange function */
	{"", 		tile	},
	{"", 		NULL	},
	{"", 		monocle },
	{"", 		tcl		},
};

/* Fonts */
static const char *fonts[] = {
	"anonymous-pro:size=10:antialias=true",
	"fontawesome:size=11:antialias=true"
};

static const char dmenufont[] = "anonymous-pro:size=10:antialias=true";

/* Colors */
static const char col_bg_norm[]. = "#020203";
static const char col_nborder[]  = "#444444";
static const char col_fg_norm[]  = "#e6e6e6";
static const char col_fg_sel[] 	 = "#ff8800";
static const char col_fg_dmenu[] = "#00fcc2";
static const char col_bg_sel[] 	 = "#060012";

static const char *colors[][3] = {
    /*               fg           bg           border   */
    [SchemeNorm] = { col_fg_norm, col_bg_norm, col_nborder  },
    [SchemeSel]  = { col_fg_sel,  col_bg_sel,  col_fg_dmenu },
};

/* TAGS */

/* tagging
 * 1:   Terminal
 * 2:   Discord
 * 3:   Trading
 * 4:   Web
 * 5:   Dev
 * 6:   Sketching
 * 7:   Files
 * 8:   Media
 * 9:   monitoring
 */
static const char *tags[] = {"", "", "", "", "", "", "", "", ""};

/* RULES */
static const Rule rules[] = {
    /* class         instance    title       tags mask     isfloating   monitor */
    { "Gimp",        NULL,       NULL,       0,            1,           -1 },
    { "FFDiscord",   NULL,       NULL,       1 << 1,       0,           -1 },
    { "FFTelegram",  NULL,       NULL,       1 << 1,       0,           -1 },
    { "FFTrading",   NULL,       NULL,       1 << 2,       0,           -1 },
    { "FFBrowser",   NULL,       NULL,       1 << 3,       0,           -1 },
    { "FFChatGPT",   NULL,       NULL,       1 << 4,       0,           -1 },
    { "FFExcal",     NULL,       NULL,       1 << 5,       0,           -1 },
    { "FFNotion",    NULL,       NULL,       1 << 6,       0,           -1 },
    { "FFYoutube",   NULL,       NULL,       1 << 7,       0,           -1 },
    { "FFSpotify",   NULL,       NULL,       1 << 7,       0,           -1 },
};

/* CMD */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = {
	"dmenu_run", "-m", dmenumon,
	"-fn", dmenufont,
	"-nb", col_bg_norm,
	"-nf", col_fg_norm,
	"-sb", col_fg_dmenu,
	"-sf", col_bg_sel,
	NULL
};

static const char *termcmd[] = { "urxvt", NULL };

/* KEYS */

static const Key keys[] = {
    /* modifier                     key             function        argument */

    /* Launchers */
    { MODKEY,                       XK_r,           spawn,          {.v = dmenucmd } },
    { MODKEY,                       XK_Return,      spawn,          {.v = termcmd } },
    { MODKEY,                       XK_n,           spawn,          SHCMD("pcmanfm") },

	/* System */
    { MODKEY|ShiftMask,             XK_c,           killclient,     {0} },
    { MODKEY|ShiftMask,             XK_q,           quit,           {0} },
	{ MODKEY|MODKEY2|ShiftMask,     XK_s,           spawn,          SHCMD("shutdown now")  },
	{ MODKEY|MODKEY2|ShiftMask,     XK_s,           spawn,          SHCMD("reboot")		   },

	/* Firefox */
    { MODKEY,                       XK_d,           spawn,          SHCMD(CMD_FF_DISCORD)  },
    { MODKEY2|ShiftMask,            XK_t,           spawn,          SHCMD(CMD_FF_TELEGRAM) },
    { MODKEY|ShiftMask,             XK_t,           spawn,          SHCMD(CMD_FF_TV)       },
    { MODKEY,                       XK_f,           spawn,          SHCMD(CMD_FF_GENERIC)  },
    { MODKEY,                       XK_g,           spawn,          SHCMD(CMD_FF_CHATGPT)  },
    { MODKEY,                       XK_e,           spawn,          SHCMD(CMD_FF_EXCAL)    },
    { MODKEY2,                      XK_n,           spawn,          SHCMD(CMD_FF_NOTION)   },
    { MODKEY,                       XK_y,           spawn,          SHCMD(CMD_FF_YT)       },
    { MODKEY,                       XK_s,           spawn,          SHCMD(CMD_FF_SPOTIFY)  },

	/* Topbar */
    { MODKEY,                       XK_b,           togglebar,      {0} },

    /* Stack */
    { MODKEY,                       XK_j,           focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,           focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_j,           movestack,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_k,           movestack,      {.i = -1 } },
	
	/* Layout Tweaks */
    { MODKEY2,                      XK_i,           incnmaster,     {.i = +1 } },
    { MODKEY2,                      XK_d,           incnmaster,     {.i = -1 } },
    { MODKEY,                       XK_h,           setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,           setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_Return,      zoom,           {0} },

	/* Layout Selection */
    { MODKEY,                       XK_t,           setlayout,      {.v = &layouts[0]} },
    { MODKEY2,                      XK_f,           setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,           setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_comma,       setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_space,       setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,       togglefloating, {0} },

    /* Tag Navigation */
    { MODKEY,                       XK_Tab,         shiftview,      {.i = +1 } },
    { MODKEY|ShiftMask,             XK_Tab,         shiftview,      {.i = -1 } },
    { MODKEY2,                      XK_Tab,         view,           {0} },
    { MODKEY,                       XK_0,           view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,           tag,            {.ui = ~0 } },

	/* Multi-Monitor */
    { MODKEY2,                      XK_comma,       focusmon,       {.i = -1 } },
    { MODKEY2,                      XK_period,      focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,       tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period,      tagmon,         {.i = +1 } },
    
	/* Client */

    /* Tag Keys */
    TAGKEYS(                        XK_1,                          0)
    TAGKEYS(                        XK_2,                          1)
    TAGKEYS(                        XK_3,                          2)
    TAGKEYS(                        XK_4,                          3)
    TAGKEYS(                        XK_5,                          4)
    TAGKEYS(                        XK_6,                          5)
    TAGKEYS(                        XK_7,                          6)
    TAGKEYS(                        XK_8,                          7)
    TAGKEYS(                        XK_9,                          8)
};

/* Buttons */
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