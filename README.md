# fsh

A small Unix-like shell written in C — supports command execution, custom commands, and more.

## Features
- Executes external commands using fork+exec
- Built-in commands in `src/main/commands`
- Simple prompt and history support

## Requirements
- gcc, make / build-essential (Linux/WSL) OR MinGW on Windows

## Build & Run (WSL / Linux)
```bash
make
./fsh
