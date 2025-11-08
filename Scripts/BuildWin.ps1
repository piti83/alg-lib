param([ValidateSet('Debug','Release','All')] [string]$Cfg = 'Debug')
$ErrorActionPreference = 'Stop'
$Repo = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path

if ($Cfg -eq 'All') {
  & "$PSCommandPath" -Cfg Debug
  & "$PSCommandPath" -Cfg Release
  exit
}

$Bld = Join-Path $Repo "out/build/win-$Cfg"
cmake -S $Repo -B $Bld -G "Visual Studio 17 2022" -A x64 -DCMAKE_EXPORT_COMPILE_COMMANDS=1
cmake --build $Bld --config $Cfg -j
