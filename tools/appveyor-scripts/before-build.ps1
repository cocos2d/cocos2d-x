Set-PSDebug -Trace 1
$python = "C:\\Python27\\python.exe"
$git_retry = "$pyhon $env:APPVEYOR_BUILD_FOLDER\tools\appveyor-scripts\git_retry.py"


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
    & $git_retry submodule init
    & $git_retry submodule update --recursive --depth=1
    Pop-Location
}

Update-SubModule

Download-Deps

& python -m pip install retry

# don't need generate binding codes for cpp only target
If ($env:build_type -ne "android_cpp_tests") {
    & $python -u .\tools\appveyor-scripts\setup_android.py --ndk_only
    Generate-Binding-Codes
}

If ($env:build_type -like "android*") {
    & choco install ninja
    & ninja --version
    & $python -u .\tools\appveyor-scripts\setup_android.py
    if ($lastexitcode -ne 0) {throw}
}