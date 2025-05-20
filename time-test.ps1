Write-Host "Running time-test.ps1..."

$testCases = Get-ChildItem "test-cases" -File | Where-Object { $_.Name -ne "teste.txt" }

foreach ($test in $testCases) {
    $testName = $test.BaseName
    $testFile = "experiment-result/time/$testName-times.txt"

    Remove-Item -Path $testFile -ErrorAction SilentlyContinue

    for ($i = 1; $i -le 100; $i++) {
      Write-Host "Running test $i for $testName..."
        Add-Content -Path $testFile -Value "Execution $i"
        & .\ntru "test-cases\$($test.Name)" | Add-Content -Path $testFile
        Add-Content -Path $testFile -Value ""
    }

    if ($args[0] -eq "times-only") {
        (Get-Content $testFile -Raw) `
            -replace '====    Plain.*?Plain Text ====','' `
            -replace '===    Cipher.*?Cipher Text ===','' `
            | Set-Content $testFile
    }
}

Write-Host "Done."
