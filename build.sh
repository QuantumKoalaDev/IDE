#!/usr/bin/env bash

set -e

rm -rf build
mkdir build

echo "[*] Configuring with preset: build-clang-debug"
cmake --preset=build-clang-debug

echo "[*] Building..."
cmake --build --preset=build-clang-debug

echo "[✓] Done"
