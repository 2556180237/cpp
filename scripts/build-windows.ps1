# Requires -Version 5.1
$ErrorActionPreference = 'Stop'

$Root = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)
Set-Location $Root

Write-Host '==> Build Windows (native MSVC)'
cmake -S . -B build-win -DCMAKE_BUILD_TYPE=Release
cmake --build build-win --config Release -j

Write-Host 'Artifacts: build-win\\Release\\draw.exe, build-win\\Release\\imgdiff.exe'
