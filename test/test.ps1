Write-Host "Compiling main.py..."
nuitka .\main.py --mode=onefile

if ($LASTEXITCODE -ne 0) {
    Write-Host "Nuitka compilation failed!"
    exit
}

Write-Host "Extracting executable..."
.\nuitka-extractor.exe .\main.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "Extractor execution failed!"
    exit
}

Write-Host "Copying files..."
Copy-Item ..\boot.exe main.exe_extracted\boot.exe
Copy-Item .\main.exe main.exe_extracted\main.exe

Set-Location main.exe_extracted
Write-Host "Launching application..."
.\boot.exe main.exe