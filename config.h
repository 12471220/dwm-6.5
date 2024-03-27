/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx = 3; /* border pixel of windows */
static const unsigned int gappx = 15;       /* gap pixel between windows */
static const unsigned int snap = 32;	/* snap pixel */
static const int showbar = 1;			/* 0 means no bar */
static const int topbar = 1;			/* 0 means bottom bar */
static const char *fonts[] = {"dejavuSansM nerd font:size=12"};
static const char dmenufont[] = "dejavuSansM nerd font:size=12";
static const char col_gray1[] = "#222222";
static const char col_gray2[] = "#444444";
static const char col_gray3[] = "#bbbbbb";
static const char col_gray4[] = "#eeeeee";
static const char col_gray5[] = "#555555";
static const char col_cyan[] = "#005577";
static const char col_red[] = "#FF0000";

static const char *colors[][3] = {
	/*               fg         bg         border   */
	[SchemeNorm] = {col_gray3, col_gray1, col_gray2},
	[SchemeSel] = {col_gray4, col_gray5, col_red},
};

/* tagging */
static const char *tags[] = {"1", "2", "3", "4", "5", "6", "7", "8", "9"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{"Gimp", NULL, NULL, 0, 1, -1},
	{"Firefox", NULL, NULL, 1 << 8, 0, -1},
};

/* layout(s) */
static const float mfact = 0.55;	 /* factor of master area size [0.05..0.95] */
static const int nmaster = 1;		 /* number of clients in master area */
static const int resizehints = 1;	 /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function(type is Monitor.) */
	{"[t]", tile},	  /* first entry is default */
	{"[f]", NULL},	  /* no layout function means floating behavior */
	{"[m]", monocle}, /*this mode only have one page on the top, but we can use Mod+j,k,..to change top Client.*/
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY, TAG)                                          \
	{MODKEY, 			   			   KEY, view, 		{.ui = 1 << TAG}},\
	{MODKEY | ControlMask, 			   KEY, toggleview, {.ui = 1 << TAG}},\
	{MODKEY | ShiftMask,   			   KEY, tag, 		{.ui = 1 << TAG}},\
	{MODKEY | ControlMask | ShiftMask, KEY, toggletag,  {.ui = 1 << TAG}},

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd)                                           \
	{                                                        \
		.v = (const char *[]) { "/bin/sh", "-c", cmd, NULL } \
	}

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = {"dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-sb", col_gray5, NULL};
/*
-nb 或 --nfcolor: 指定正常状态下的背景颜色。
-nf 或 --nbcolor: 指定正常状态下的文字颜色。
-sb 或 --sfcolor: 指定选中状态下的背景颜色。
-sf 或 --sbcolor: 指定选中状态下的文字颜色。
*/
static const char *termcmd[] = {"alacritty", NULL};
static const char *browser[] = {"google-chrome-stable", NULL};

//media settings
static const char *brightnessDown[] = {"brightnessctl","set","5-", NULL};
static const char *brightnessUp[] = {"brightnessctl","set","+5", NULL};
static const char *volumeDown[] = {"pactl","set-sink-volume","@DEFAULT_SINK@","-3%", NULL};
static const char *volumeUp[] = {"pactl","set-sink-volume","@DEFAULT_SINK@","+3%", NULL};
static const char *volumeMute[] = {"pactl","set-sink-mute","@DEFAULT_SINK@","toggle", NULL};
static const char *stalonetray[] = {"/home/lx/repositories/dwm-6.5/scripts/trayer.sh", NULL};
// static const char *screenshot[] = {"scrot" "%Y-%m-%d_%H:%M:%S.png" "-z" "-e" "mv" "$f" "~/Pictures/ScreenShot/"};

static const Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = stalonetray } },
	// { MODKEY,             			XK_Print,  spawn,          {.v = screenshot } },
	{ MODKEY,             			XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,             			XK_c, 	   spawn,          {.v = browser } },
	{ MODKEY,             			XK_F5, 	   spawn,          {.v = brightnessDown } },
	{ MODKEY,             			XK_F6, 	   spawn,          {.v = brightnessUp } },
	{ MODKEY,             			XK_F2, 	   spawn,          {.v = volumeDown } },
	{ MODKEY,             			XK_F3, 	   spawn,          {.v = volumeUp } },
	{ MODKEY,             			XK_F1, 	   spawn,          {.v = volumeMute } },
	{ MODKEY,						XK_f, 	   bind_fullscreen,{0}},
	{ MODKEY,                       XK_b,      togglebar,      {0} },//hide the bar
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_u,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_Return, zoom,           {0} },//make selected window to the top stack
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	//three layouts.
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	// { MODKEY,             XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_p,      quit,           {0} },
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
