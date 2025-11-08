param([ValidateSet('Debug','Release','All')] [string]$Cfg = 'Debug')
$ErrorActionPreference = 'Stop'
& "$PSScriptRoot/TestWin.ps1" -Cfg $Cfg
& "$PSScriptRoot/TestLin.ps1" -Cfg $Cfg
