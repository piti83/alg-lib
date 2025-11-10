param([ValidateSet('Debug','Release','All')] [string]$Cfg = 'Debug')
$ErrorActionPreference = 'Stop'
& "$PSScriptRoot/BuildWin.ps1" -Cfg $Cfg
& "$PSScriptRoot/BuildLin.ps1" -Cfg $Cfg
