# Coverage report script
Write-Host "`n===== CODE COVERAGE =====`n" -ForegroundColor Cyan

$gcovFiles = Get-ChildItem .pio\build\native -Recurse -Include *.gcda
if (!$gcovFiles) { Write-Host "No coverage data. Run: pio test -e native" -ForegroundColor Yellow; exit 1 }

$result = @()
foreach ($g in $gcovFiles) {
    Push-Location $g.Directory
    $out = (gcov $g.Name -r 2>&1 | Out-String)
    $out -split "`n" | Where {$_ -match "^File 'src/"} | ForEach {
        if ($_ -match "File '([^']+)'") { $file = $Matches[1] }
        $next = ($out -split "`n" | Select-String -Pattern "Lines executed" -Context 0,0 | Select -First 1).Line
        if ($next -match "Lines executed:([\d.]+)% of (\d+)") {
            $result += [PSCustomObject]@{File=$file; Coverage=[double]$Matches[1]; Lines=[int]$Matches[2]}
        }
    }
    Pop-Location
}

if ($result) {
    $result | ForEach { $c = [int]$_.Coverage; $bar = '█' * ($c/5); Write-Host "  $($_.File.PadRight(40)) $($c.ToString().PadLeft(3))% $bar" -ForegroundColor $(if($c -eq 100){'Green'}else{'Yellow'}) }
    $total = [math]::Round(($result | Measure -Property Lines -Sum).Sum)
    Write-Host "`n  Total lines covered: $total" -ForegroundColor Cyan
}
Write-Host "`n========================`n" -ForegroundColor Cyan
