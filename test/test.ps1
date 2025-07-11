Write-Host "正在编译 main.py..."
nuitka .\main.py --mode=onefile

if ($LASTEXITCODE -ne 0) {
    Write-Host "Nuitka编译失败！"
    exit
}

Write-Host "正在提取可执行文件..."
.\nuitka-extractor.exe .\main.exe

if ($LASTEXITCODE -ne 0) {
    Write-Host "提取器执行失败！"
    exit
}

Write-Host "正在复制文件..."
Copy-Item ..\boot.exe main.exe_extracted\boot.exe
Copy-Item .\main.exe main.exe_extracted\main.exe

Set-Location main.exe_extracted
Write-Host "启动应用程序..."
.\boot.exe main.exe