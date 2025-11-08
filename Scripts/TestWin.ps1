param([ValidateSet('Debug','Release','All')] [string]$Cfg = 'Debug')
$ErrorActionPreference = 'Stop'
$Repo = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path

if ($Cfg -eq 'All') {
  & "$PSCommandPath" -Cfg Debug
  & "$PSCommandPath" -Cfg Release
  exit
}

$LogDir = Join-Path $Repo "out/logs"
New-Item -ItemType Directory -Force -Path $LogDir | Out-Null

$RunId   = (Get-Date).ToString('yyyyMMdd-HHmmss')
$Suffix  = if ($Label) { "-$Label" } else { "" }
$LogFile = Join-Path $LogDir "win-$Cfg-$RunId$Suffix.txt"

$Bld = Join-Path $Repo "out/build/win-$Cfg"

ctest --test-dir $Bld --build-config $Cfg -V --output-on-failure | tee $LogFile
