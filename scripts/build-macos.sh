#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
cd "$ROOT_DIR"

echo "==> Build macOS (native clang)"
cmake -S . -B build/macos -DCMAKE_BUILD_TYPE=Release
cmake --build build/macos --config Release -j

echo "Artifacts: build/macos/draw, build/macos/imgdiff"
