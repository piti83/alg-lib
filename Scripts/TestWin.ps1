param(
  [ValidateSet('Debug','Release','All')] [string]$Cfg = 'Debug',
  [string]$Label = ''
)
$ErrorActionPreference = 'Stop'
$Repo = (Resolve-Path (Join-Path $PSScriptRoot '..')).Path

if ($Cfg -eq 'All') {
  & "$PSCommandPath" -Cfg Debug -Label $Label
  & "$PSCommandPath" -Cfg Release -Label $Label
  exit
}

$LogDir = Join-Path $Repo "out/logs"
New-Item -ItemType Directory -Force -Path $LogDir | Out-Null
$RunId   = (Get-Date).ToString('yyyyMMdd-HHmmss')
$Suffix  = if ($Label) { "-$Label" } else { "" }
$LogFile = Join-Path $LogDir "win-$Cfg-$RunId$Suffix.txt"

$Bld = Join-Path $Repo "out/build/win-$Cfg"

ctest --test-dir $Bld --build-config $Cfg -V --output-on-failure *> $LogFile
$code = $LASTEXITCODE

$summary = (Get-Content $LogFile | Select-String -Pattern '^\s*\d+% tests passed|^100% tests passed|^The following tests FAILED:' -SimpleMatch:$false) -join "`n"
if ($summary) { Write-Host $summary } else { Write-Host "Test log written to -> $((Convert-Path $LogFile) -replace '\\','/')" }

if ($code -eq 0) {
  Write-Host "WIN $($Cfg): ALL TESTS PASSED" -ForegroundColor Green
} else {
    Write-Host "WIN $($Cfg): SOME TESTS FAILED — CHECK LOG:" -ForegroundColor Red
}
$abs = (Convert-Path $LogFile) -replace '\\','/'
Write-Host "Log: $abs"
exit $code
