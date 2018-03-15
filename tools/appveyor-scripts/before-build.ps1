Set-PSDebug -Trace 1
$python = "C:\\Python27\\python.exe"

function Download-Deps
{
    Write-Host "Download-Deps"
    & $python $env:APPVEYOR_BUILD_FOLDER\download-deps.py --remove-download=False
}

function Generate-Binding-Codes
{
    $env:NDK_ROOT=$env:APPVEYOR_BUILD_FOLDER + "\..\android-ndk-r16b"

    # install python module
    & pip install PyYAML Cheetah
    Write-Host "generating binding codes"

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
    & git submodule update --recursive --depth=1
    Pop-Location
}

Update-SubModule

Download-Deps

If ($env:build_type -eq "windows32") {
    & $python -u .\tools\appveyor-scripts\setup_android.py --ndk_only
    Generate-Binding-Codes
} elseif ($env:build_type -like "android*") {
    & $python -u .\tools\appveyor-scripts\setup_android.py
    if ($lastexitcode -ne 0) {throw}
}