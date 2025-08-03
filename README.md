# IDE (mainly for C++)

There is currently no C++ IDE or toolchain on Linux that fully satisfies my expectations — so I started building my own out of curiosity.

## Project Goals

The goal is to build an IDE optimized specifically for C++, combining:

- The power and flexibility of a full-featured IDE  
- The speed and minimalism of console editors like **vim**

## Characteristics

- JSON-based configuration system  
- Full **keybinding** access for all core features  
- Standard toolchain: `clang++` (with `libstdc++`), `clangd`, `lldb`, `cmake` + `ninja`

> ⚠️ This is an early-stage project. Expect rough edges — feedback and ideas are welcome!

## Planned Features & Ideas

- [ ] Compiler configuration via JSON (used by the build script)  
- [ ] Autocompletion and symbol navigation using `clangd`  
- [ ] Customizable bash script parameters via JSON  
- [ ] Syntax highlighting (fully configurable via JSON: color, font style)  

**Long Term:**

- [ ] Vim-style shortcuts and command system
- [ ] AST-based syntax highlighting and autocomplete  
- [ ] Possibly a fully customizable UI  
- [ ] Fully customizable toolchain  
- [ ] Support for other languages via LSP servers  

## Dependencies

- On Windows, you may need to include `glew.h` in your source code.  
  The GLEW license is provided in the `external/GLEW` directory next to the header file.

## Build

- **Linux** (tested on Ubuntu):  
  Run `./build.sh` in the root directory

- **Windows**:  
  Currently in development

## Licenses

- **GLEW**: License file is located in `src/external/GLEW` alongside the header file.

