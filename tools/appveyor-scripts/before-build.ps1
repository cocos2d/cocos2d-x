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

If ($env:build_type -eq "windows32_cmake_test" ) {
    & $python -u .\tools\appveyor-scripts\setup_android.py --ndk_only
    Generate-Binding-Codes
}
elseif ($env:build_type -like "android*") {
    & choco install ninja
    & ninja --version
    & $python -u .\tools\appveyor-scripts\setup_android.py
    If ($env:build_type -eq "android_lua_tests") {
        Generate-Binding-Codes
    }
    if ($lastexitcode -ne 0) {throw}
}