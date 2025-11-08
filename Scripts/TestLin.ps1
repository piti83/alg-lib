param(
  [ValidateSet('Debug','Release','All')] [string]$Cfg = 'Debug',
  [string]$Label = ''
)
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
  & "$PSCommandPath" -Cfg Debug -Label $Label
  & "$PSCommandPath" -Cfg Release -Label $Label
  exit
}

$LogDirWin = Join-Path $RepoWin "out/logs"
New-Item -ItemType Directory -Force -Path $LogDirWin | Out-Null
$RunId   = (Get-Date).ToString('yyyyMMdd-HHmmss')
$Suffix  = if ($Label) { "-$Label" } else { "" }
$LogFileWin = Join-Path $LogDirWin "wsl-$Cfg-$RunId$Suffix.txt"

$RepoWsl    = To-WslPath $RepoWin
$LogFileWsl = To-WslPath $LogFileWin
$LogDirWsl  = To-WslPath $LogDirWin
$BldWsl     = "$RepoWsl/out/build/wsl-$Cfg"

wsl.exe bash -lc "mkdir -p '$LogDirWsl'"
wsl.exe bash -lc "export GTEST_COLOR=1; ctest --test-dir '$BldWsl' -V --output-on-failure | tee '$LogFileWsl'"
