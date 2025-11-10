param([ValidateSet('Debug','Release','All')] [string]$Cfg = 'Debug')
$ErrorActionPreference = 'Stop'

function To-WslPath([string]$winPath) {
  if (-not $winPath) { throw "To-WslPath: empty path" }
  if ($winPath -match '^[A-Za-z]:\\') {
    $drive = $winPath.Substring(0,1).ToLower()
    $rest  = $winPath.Substring(2) -replace '\\','/'
    return "/mnt/$drive$rest"
  }
  return ($winPath -replace '\\','/')
}

$RepoWin = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path

if ($Cfg -eq 'All') {
  & "$PSCommandPath" -Cfg Debug
  & "$PSCommandPath" -Cfg Release
  exit
}

$RepoWsl = To-WslPath $RepoWin
$BldWsl  = "$RepoWsl/out/build/wsl-$Cfg"

wsl.exe bash -lc "mkdir -p '$BldWsl'"
wsl.exe bash -lc "cmake -S '$RepoWsl' -B '$BldWsl' -G Ninja -DCMAKE_BUILD_TYPE=$Cfg && cmake --build '$BldWsl' -j"
