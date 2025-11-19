# 🐚 minishell

> A tiny Bash-like shell written in C as part of the 42 curriculum.  
> Signals, pipes, redirections, heredocs, builtins… all from scratch.

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-blue.svg" />
  <img src="https://img.shields.io/badge/School-42-black?logo=42" />
  <img src="https://img.shields.io/badge/Project-minishell-success" />
  <img src="https://img.shields.io/badge/Status-Completed-brightgreen" />
</p>

---

## ✨ Overview

`minishell` is a minimalist re-implementation of **Bash**.  
The goal: understand what happens *between* your keyboard and the kernel.

It supports:

- A prompt and interactive line editing
- Command parsing (pipes, redirections, heredocs)
- Environment variable expansion (`$PATH`, `$USER`, `$?`, etc.)
- A set of builtins (`echo`, `cd`, `export`, …)
- Proper signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Exit codes compatible with Bash (as much as the subject requires)

---

## 🧪 Demo

```bash
minishell$ echo "hello, world"
hello, world

minishell$ export NAME=kerim
minishell$ echo "hi $NAME"
hi kerim

minishell$ ls | grep .c > sources.txt
minishell$ cat << EOF
> heredocs are fun
> EOF
heredocs are fun
