$python = "C:\\Python27\\python.exe"

function Download-Url
{
	param([string]$url, [string]$output)

	(New-Object Net.WebClient).DownloadFile($url, $output)
}

function LS
{
	param([string]$path)

	Get-ChildItem $path | get-acl
}

function Download-Deps
{
    $json = Get-Content -Raw -Path "$env:APPVEYOR_BUILD_FOLDER/external/config.json" | ConvertFrom-Json
    $version = $json.version
    $url = "https://github.com/cocos2d/cocos2d-x-3rd-party-libs-bin/archive/$version.zip"
    $output = "$env:APPVEYOR_BUILD_FOLDER/$version.zip"
    Write-Host "downloading $url"
    Download-Url $url $output
    Write-Host "finish downloading $url"

    Write-Host "unzip $url"
    $zipfile = $output
    $output = $env:APPVEYOR_BUILD_FOLDER
    Add-Type -AssemblyName System.IO.Compression.FileSystem
    [System.IO.Compression.ZipFile]::ExtractToDirectory($zipfile, $output)
    $file_subffix = $version.Substring(1)
    Copy-Item -Path "$output/cocos2d-x-3rd-party-libs-bin-$file_subffix/*" -Destination "$env:APPVEYOR_BUILD_FOLDER/external" -Recurse
    Write-Host "finish unziping $url"
}

function Download-NDK
{
	$url = "https://dl.google.com/android/repository/android-ndk-r16-windows-x86.zip"
    $output = "$env:APPVEYOR_BUILD_FOLDER/../android-ndk-r16-windows-x86.zip"
    Write-Host "downloading $url"
	Start-FileDownload $url $output
	Write-Host "finish downloading $url"

	Write-Host "installing NDK"
    Push-Location $env:APPVEYOR_BUILD_FOLDER/../
	$zipfile = $output
    Invoke-Expression "7z.exe x $zipfile"
	Write-Host "finish installing NDK"
    Pop-Location
    $env:NDK_ROOT = "$env:APPVEYOR_BUILD_FOLDER/../android-ndk-r16"
    Write-Host "set environment NDK_ROOT to $env:NDK_ROOT"
}

function Generate-Binding-Codes
{

    # install python module
    & pip install PyYAML Cheetah
	Write-Host "generating binding codes"

    $env:PYTHON_BIN = $python
	Write-Host "set environment viriable PYTHON_BIN to $env:PYTHON_BIN"

	Push-Location $env:APPVEYOR_BUILD_FOLDER\tools\tolua
	& $python $env:APPVEYOR_BUILD_FOLDER\tools\tolua\genbindings.py
	Pop-Location

    Push-Location $env:APPVEYOR_BUILD_FOLDER\tools\tojs
	& $python $env:APPVEYOR_BUILD_FOLDER\tools\tojs\genbindings.py
	Pop-Location
}

function Update-SubModule
{
	Push-Location $env:APPVEYOR_BUILD_FOLDER
	& git submodule init
	& git submodule update --recursive
	Pop-Location
}

Update-SubModule
Download-Deps
Download-NDK
Generate-Binding-Codes