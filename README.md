# Drawing Shapes to an Image Matrix (PNG only)

C++ project that renders simple shapes (rectangle, circle, triangle) into 2D matrices and saves final images as PNG. PNG encoding/decoding is implemented internally (no external tools).

## Features
- RGB scene "house" → `result/house.png`
- BW scene "mushroom" → `result/mushroom.png`
- Internal PNG encoder/decoder (`include/PngCodec.hpp`, `src/PngCodec.cpp`)
- Image diff tool: compares `result/*.png` against `examples/*.png`
- Optional zlib compression (used if found); works without it as well
- Cross-platform CMake build; cross-compilation toolchains provided

## Project structure
- `include/` headers: `Color.hpp`, `Shape.hpp`, `Matrix.hpp`, `Circle.hpp`, `Rectangle.hpp`, `Triangle.hpp`, `PngCodec.hpp`
- `src/` sources (including `PngCodec.cpp`)
- `main.cpp` entry point
- `test/diff.cpp` image comparison tool
- `scripts/` build helpers

## Build
Requires CMake >= 3.12 and a C++17 compiler.

### Linux (native)
```bash
./scripts/build-linux.sh
./build-linux/draw
# Images will appear in ./result
```

### Windows (native, PowerShell)
```powershell
./scripts/build-windows.ps1
# Run
./build-win/Release/draw.exe
```

### macOS (native)
```bash
./scripts/build-macos.sh
./build/macos/draw
```

## Cross-compilation from Linux (optional)
Toolchains are provided under `cmake/toolchains/`.
- Windows: MinGW-w64 (`cmake/toolchains/mingw64.cmake`)
- macOS: osxcross (`cmake/toolchains/osxcross.cmake`)

Example (Windows):
```bash
sudo apt-get install -y mingw-w64
cmake -S . -B build-win64 -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE=cmake/toolchains/mingw64.cmake
cmake --build build-win64 --config Release -j
```

## Usage
After building `draw`:
```bash
./build-linux/draw           # Linux
./build-win/Release/draw.exe # Windows
./build/macos/draw           # macOS
```
Outputs:
- `result/house.png`
- `result/mushroom.png`

PPM/PGM legacy outputs are disabled by default (`NO_LEGACY_PPM`).

## Image diff
Builds alongside main binary:
```bash
./build-linux/imgdiff
# Compares examples/*.png with result/*.png
# Creates visual diffs in test/diff_*.png (red pixels mark differences)
```

## Benchmark
Run rendering without IO several times and score performance.
```bash
./build-linux/draw --bench 5
```
- Baseline: env `PERF_BASELINE_MS` (default 3000)
- Score formula: `perf = clamp(baselineMs / avgMs, 0..1.5)`; `score = 7.0 + perf * 2.0` (0..10)

## CI
Workflow: `.github/workflows/build.yml` (matrix: Ubuntu, Windows, macOS). Artifacts upload `result/**` and binaries.

## Notes
- If zlib is available, PNG is compressed; otherwise, uncompressed deflate stream is used.
- All code comments are in English. PNG implementation is minimal and focused on 8-bit RGB/RGBA.