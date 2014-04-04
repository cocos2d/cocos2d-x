Function CreateSolution()
{
    $solution = New-Module -AsCustomObject -ScriptBlock {
        . ".\scripts\converterutils.ps1"

        #use MSBuild namespace
        $ms = 'http://schemas.microsoft.com/developer/msbuild/2003'
        $ns = @{ ms = $ms }

        $projects = @()
        $solutionDir = ""


        Function AddProject($path) {
            $globals = GetProjectGlobals $path $ns
            $guid = $globals.Node.ProjectGuid
            $relativePath = Get-RelativePath $this.solutionDir $path
            $project = New-Object –TypeName PSObject
            $project | Add-Member –MemberType NoteProperty –Name guid –Value $globals.Node.ProjectGuid
            $project | Add-Member –MemberType NoteProperty –Name path –Value $relativePath
            if($globals.Node.ProjectName)
            {
                $project | Add-Member –MemberType NoteProperty –Name name –Value $globals.Node.ProjectName
            }
            else
            {
               $project | Add-Member –MemberType NoteProperty –Name name –Value $globals.Node.RootNamespace
            }

            $this.projects += $project
        }

        Function Save($path, $platform) {
            $output = New-Item $path -type file -force

            if($platform -eq "winrt")
            {
                $template = join-path $PSScriptRoot "templates\winrt_sln_header_template.txt"
            }
            elseif($platform -eq "wp8")
            {
                $template = join-path $PSScriptRoot "templates\wp8_sln_header_template.txt"
            }
            else
            {
                throw "Unknown platform argument (winrt or wp8)"
            }

            (Get-Content $template) | 
            Add-Content $path

            foreach($project in $this.projects)
            {
                $line = 'Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "' + $project.name + '", "' + $project.path + '", "' + $project.guid + '"'
                #Add-Content $path 'Project("{8BC9CEB8-8B4A-11D0-8D11-00A0C91BC942}") = "opencv_core", "opencv_core.vcxproj", "{8F928FE0-8A06-4F93-99FE-53B9C7A006CA}"'
                Add-Content $path $line
                Add-Content $path 'EndProject'
            }

            $template = join-path $PSScriptRoot "templates\global_start_template.txt"
            (Get-Content $template) | 
            Add-Content $path

            $template = join-path $PSScriptRoot "templates\globalsection_template.txt"
            foreach($project in $this.projects)
            {
                (Get-Content $template) | 
                Foreach-Object {$_ -replace "REPLACE_GUID", $project.guid} |
                Add-Content $path
            }

            $template = join-path $PSScriptRoot "templates\global_end_template.txt"
            (Get-Content $template) | 
            Add-Content $path
        }

        Export-ModuleMember -Variable * -Function *
    }
    return $solution
}

<#
$solutionDir = join-path $WorkingDir ".\modules\core"
$path = join-path $solutionDir "opencv_core.vcxproj"
$output = join-path $solutionDir "opencv_core2.sln"


$solution = CreateSolution
$solution.solutionDir = $solutionDir
$solution.AddProject($path)

$path = join-path $WorkingDir ".\3rdparty\zlib\zlib.vcxproj"
$solution.AddProject($path)

$solution.Save($output)
notepad $output
#>

