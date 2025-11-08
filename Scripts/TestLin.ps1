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
$BldWsl     = "$RepoWsl/out/build/wsl-$Cfg"
$LogDirWsl  = To-WslPath $LogDirWin

wsl.exe bash -lc "mkdir -p '$LogDirWsl'"
wsl.exe bash -lc "export GTEST_COLOR=1; ctest --test-dir '$BldWsl' -V --output-on-failure >'$LogFileWsl' 2>&1"
$code = $LASTEXITCODE
wsl.exe bash -lc "grep -E '^[[:space:]]*[0-9]+% tests passed|^100% tests passed|^The following tests FAILED:' '$LogFileWsl' || true"
if ($code -eq 0) {
  Write-Host "WSL $($Cfg): ALL TESTS PASSED" -ForegroundColor Green
} else {
  Write-Host "WSL $($Cfg): SOME TESTS FAILED — CHECK LOG:" -ForegroundColor Red
}
Write-Host "Log: $LogFileWsl"
exit $code
