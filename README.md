# zDwm

![Version](https://img.shields.io/badge/version-6.6.0-blue)
![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Language](https://img.shields.io/badge/language-C-cyan)
![Display](https://img.shields.io/badge/display-X11-lightgrey)
![License](https://img.shields.io/badge/license-MIT--X-lightgrey)

## Description

`zDwm` is a personal fork of [dwm](https://dwm.suckless.org/), the dynamic window manager from suckless.  
It keeps dwm’s core philosophy (small, fast, configured at compile-time) while baking in:

- Opinionated tag layout (Discord/TradingView/Firefox/ChatGPT/etc. on fixed tags)
- Firefox “apps” with dedicated profiles and `WM_CLASS` rules
- Extra layouts and navigation helpers
- A themed bar and small gaps

---

## Features

- **Dynamic tiling**
  - Standard tiled, monocle and floating layouts.
  - Additional three-column layout via `tcl.c`.

- **Tag-based workflow**
  - 9 tags with icon labels in the bar.
  - Windows can be tagged with one or more tags.
  - Tag cycling via `shiftview` helpers.

- **Firefox “apps” on fixed tags**
  - Discord, Telegram, TradingView, ChatGPT, Excalidraw, Notion, YouTube, Spotify, etc.
  - Each launched with a custom `WM_CLASS` and sent to a specific tag via `rules[]`.

- **Quality-of-life helpers**
  - Move windows up/down the stack.
  - Cycle tags with the keyboard.
  - Small gaps between windows (configured in `config.h`).

### Patches included

These are the upstream patches (or patch-style helpers) that zDwm integrates:

- **movestack** – move the focused client up or down the stack using keybindings.  
  Source: suckless `movestack` patch, via `movestack.c`.   

- **shiftview (shift tools)** – provides `shiftview` to cycle through tags (next/previous) with keybindings.  
  Source: `shift tools` / `shiftview` patch; zDwm uses the `shiftview.c` helper.   

- **Three Column Layout (`tcl.c`)** – adds a three-column layout (master in the middle or side columns, depending on config).  
  Source: `three-column` layout patch (`tcl.c`).   

Other tweaks (like gaps and the Firefox “app” rules) are custom changes in this fork’s `config.h` / `zdwm.c`, not standalone upstream patches.

---

## Requirements

To build `zdwm` you need:

- Xlib headers (`libX11` dev)
- Xft headers (`libXft` dev)
- Xinerama headers (`libXinerama` dev) if building with Xinerama

On most distributions, install the development variants of those libraries from your package manager.

---

## Installation

Edit `config.mk` to match your local setup (`zdwm` is installed into
the `/usr/local` namespace by default):

```sh
PREFIX = /usr/local
# etc...
