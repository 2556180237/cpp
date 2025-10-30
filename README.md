# Draw (C++) — рендер фигур в матрицу с экспортом в PNG

Проект рисует простые фигуры (прямоугольник, круг, треугольник) в двумерные матрицы и сохраняет результат только в PNG. Генерация PNG реализована внутри проекта (без ImageMagick и прочих утилит), декодер используется в тестовом инструменте сравнения изображений.

## Возможности
- Готовые сцены:
  - RGB «house» → `result/house.png`
  - BW «mushroom» → `result/mushroom.png`
- Встроенный PNG‑кодек (`include/PngCodec.hpp`, `src/PngCodec.cpp`):
  - кодирование RGB8 в PNG (с `zlib`, если доступен; без него — совместимый поток хранения)
  - декодирование PNG в RGB8 (на Windows в CI — `zlib` через vcpkg)
- Сравнение изображений: `test/diff.cpp` сравнивает `examples/*.png` и `result/*.png`, создаёт диффы `test/diff_*.png`
- Бенчмарк рендера без IO: `--bench N` (CI сохраняет логи бенчмарка)
- Кроссплатформенная сборка CMake; CI‑матрица Ubuntu/Windows/macOS

## Структура
- `include/` — `Color.hpp`, `Shape.hpp`, `Matrix.hpp`, `Circle.hpp`, `Rectangle.hpp`, `Triangle.hpp`, `PngCodec.hpp`
- `src/` — реализации, включая `PngCodec.cpp`
- `main.cpp` — входная точка (сцены, бенчмарк, экспорт PNG)
- `test/diff.cpp` — сравнение PNG и генерация diff‑изображений
- `examples/` — эталонные PNG для сравнения
- `scripts/` — скрипты сборки: `build-linux.sh`, `build-windows.ps1`, `build-macos.sh`
- `.github/workflows/build.yml` — CI (GitHub Actions)

## Сборка
Требуется: CMake ≥ 3.12, компилятор C++17.

### Linux (native)
```bash
./scripts/build-linux.sh
./build-linux/draw
# PNG появятся в ./result
```

### Windows (native, PowerShell)
```powershell
./scripts/build-windows.ps1
./build-win/Release/draw.exe
```

### macOS (native)
```bash
./scripts/build-macos.sh
./build/macos/draw
```

## Использование
```bash
# Генерация PNG
./build-linux/draw                 # Linux
./build-win/Release/draw.exe       # Windows
./build/macos/draw                 # macOS

# Бенчмарк без IO
./build-linux/draw --bench 10
```
Выходные файлы:
- `result/house.png`
- `result/mushroom.png`

Вывод PPM/PGM отключён по умолчанию макросом `NO_LEGACY_PPM` (методы `display()` заглушены).

## Сравнение изображений
```bash
./build-linux/imgdiff
# Сравнивает examples/*.png и result/*.png;
# создаёт diff‑карты test/diff_*.png (различия отмечены красным)
```
На Windows в CI декодирование PNG обеспечивается установленным через vcpkg `zlib`.

## Бенчмарк
```bash
./build-linux/draw --bench 5
```
Параметры и метрики:
- `--bench N` — число итераций (по умолчанию 3)
- Эталон: `PERF_BASELINE_MS` (мс), по умолчанию 3000
- Оценка: `perf = clamp(baselineMs / avgMs, 0..1.5)`; `score = 7.0 + perf * 2.0` в диапазоне [0..10]

## CI (GitHub Actions)
- Матрица: `ubuntu-22.04`, `ubuntu-24.04`, `windows-2022`, `macos-13`, `macos-14`
- Шаги:
  - сборка `draw` и `imgdiff`
  - запуск генерации PNG и отдельный бенчмарк (`--bench 10`), сохранение вывода в `bench-<os>.txt`
  - запуск `imgdiff` на всех ОС
  - артефакты: `result/**`, `test/diff_*.png`, бинарники и логи бенчмарка
- Windows: установка `zlib` через vcpkg (см. `vcpkg.json`, `vcpkg-configuration.json`)

## Примечания
- PNG реализован для 8‑бит RGB/RGBA, без интерлейсинга; при записи используется фильтр 0
- При наличии `zlib` IDAT сжимается; без `zlib` используется совместимый поток (stored‑блоки)
- Комментарии в коде — на английском