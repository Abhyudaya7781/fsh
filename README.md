fsh – A Simple Unix-Like Shell in C

fsh is a lightweight Unix-style shell written in C, designed to execute commands, handle basic input/output redirection, and support custom commands. It’s a small, educational project that demonstrates process management, command parsing, and file operations in C.

Features

Execute standard system commands (like ls, pwd, echo, etc.).

Supports custom commands implemented in C.

Handles basic input/output redirection (>, <).

Modular structure: easily extendable with new commands.

Educational tool for learning fork, exec, and process handling in C.

Project Structure
fsh/
├── src/               # Source code files
├── test/              # Example test scripts
├── Makefile           # Build instructions
└── README.md          # Project overview

Installation

Clone the repository:

git clone https://github.com/Abhyudaya7781/fsh.git
cd fsh


Build the shell:

make


This will compile the source code and generate the executable fsh.

Usage

Run the shell:

./fsh


Once inside, you can enter commands just like a regular shell:

fsh> ls
fsh> pwd
fsh> echo "Hello, World!"


To run custom commands, type their names as implemented in the src/main/commands directory.

Testing

You can test example commands provided in the test/ folder:

./test/test_commands.sh
