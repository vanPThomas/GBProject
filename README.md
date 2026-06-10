# Game Boy Learning Project

A small, constantly evolving Game Boy (and Game Boy Color) homebrew project written in **C** using **GBDK-2020**. 

The main goal of this repository is to **learn low-level game development** on severely constrained 8-bit hardware. Starting from the absolute basics and gradually pushing the limits of the original Game Boy.

## Philosophy
Creativity born from limitations.  
This project is my playground for understanding how classic games (like the original Pokémon) were made under tight memory, CPU, and graphics constraints. Expect messy but educational code as I learn and improve.

## Current Features
- Basic sprite rendering
- D-pad controlled player movement with screen bounds clamping
- Proper game loop with VBlank synchronization
- Clean multi-file structure (planned)

## Tech Stack
- **Language**: C (with plans to mix in 6502-style assembly later)
- **Toolchain**: GBDK-2020 + SDCC
- **Emulator**: BGB (for development and debugging)
- **Target**: Original Game Boy + Game Boy Color

## How to Build
1. Install [GBDK-2020](https://github.com/gbdk-2020/gbdk-2020)
2. Add GBDK's `bin` folder to your PATH
3. Run:
   ```bash
   lcc -o game.gb main.c