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

- **GLEW**: Required for OpenGL support.  
  License: See `external/glew-2.2.0/LICENSE.txt`

- **FreeType**: Used for text rendering.  
  License: See `external/freetype/docs/FTL.TXT`

> On Windows, make sure to include `glew.h` and link GLEW properly when building.

## Build

- **Linux** (tested on Ubuntu):
  First, build the GLEW library separately inside `external/glew-2.2.0` by running: `make`.  
  Afterwards, run `./build.sh` in the root directory.

- **Windows**:  
  Open the Visual Studio solution at `external/glew-2.2.0/build/vc15/glew.sln` and build the project in Release mode.  
  Then, run `./build.bat` in the root directory.

## Licenses

- **GLEW**: License file is located in `external/glew-2.2.0`.
- **FreeType**: License file is located in `external/freetype/docs/FTL.txt`. This library is included as a git submodule.

For details on the software license and third-party components, see [LICENSE.txt](./LICENSE.txt).
