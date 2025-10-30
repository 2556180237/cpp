#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT_DIR"

rm -rf result/ build/

echo "Build Linux"
cmake -S . -B build/linux -DCMAKE_BUILD_TYPE=Release
cmake --build build/linux --config Release -j

echo "Build Windows (MinGW-w64)"
if command -v x86_64-w64-mingw32-g++ >/dev/null 2>&1; then
  cmake -S . -B build/win64 -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw64.cmake
  cmake --build build/win64 --config Release -j
else
  echo "[SKIP] MinGW-w64 not found. Install: sudo apt-get install -y mingw-w64" >&2
fi

echo "Build macOS (osxcross)"
if [[ -n "${OSXCROSS_ROOT:-}" ]] && command -v o64-g++ >/dev/null 2>&1; then
  cmake -S . -B build/macos -DCMAKE_BUILD_TYPE=Release \
    -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/osxcross.cmake
  cmake --build build/macos --config Release -j
else
  echo "[SKIP] osxcross not configured. Set OSXCROSS_ROOT and ensure o64-g++ is in PATH." >&2
fi

echo "Done. Artifacts in: build/linux/, build/win64/, build/macos/"


