. ".\scripts\createsln.ps1"

#use MSBuild namespace
$ms = 'http://schemas.microsoft.com/developer/msbuild/2003'
$ns = @{ ms = $ms }

Function GetDirectoryName($path)
{
    return [System.IO.Path]::GetFileName($path)
}

Function GetFileName($path)
{
    return [System.IO.Path]::GetFileName($path)
}

Function Get-RelativePath($Folder, $FilePath)
{
   Write-Verbose "Resolving paths relative to '$Folder'"
   $from = $Folder = split-path $Folder -NoQualifier -Resolve:$Resolve
   $to = $filePath = split-path $filePath -NoQualifier -Resolve:$Resolve

   while($from -and $to -and ($from -ne $to)) {
      if($from.Length -gt $to.Length) {
         $from = split-path $from
      } else {
         $to = split-path $to
      }
   }

   $filepath = $filepath -replace "^"+[regex]::Escape($to)+"\\"
   $from = $Folder
   while($from -and $to -and $from -gt $to ) {
      $from = split-path $from
      $filepath = join-path ".." $filepath
   }
   return $filepath
}


Function ReplaceText($path, $text, $replace)
{
    (Get-Content $path) | 
    Foreach-Object {$_ -replace $text, $replace} |
    Set-Content $path
}



Function LoadXmlFile($path)
{
    $xml = New-Object -TypeName XML
    $xml.Load($path)
    return $xml
}

Function AddElement($xml, $root, $name, $value, $namespace)
{
	$newEl = $xml.CreateElement($name, $namespace)
	$xmlText = $xml.CreateTextNode($value)
	$newEl.AppendChild($xmlText)
	$root.AppendChild($newEl)
	return $newEl
}

Function GetProjectGlobals($path, $namespace)
{
    $xml = LoadXmlFile($path)
    $globals = Select-XML -Xml $xml -XPath '//ms:PropertyGroup[@Label="Globals"]' -Namespace $namespace
    return $globals
}

Function AddProjectReference($toProject, $projects)
{
    $xml = LoadXmlFile($toProject)
    $xdNS = $xml.DocumentElement.NamespaceURI

    foreach($fromProject in $projects)
    {
        $globals = GetProjectGlobals $fromProject $ns
	    $itemGroup = $xml.CreateElement("ItemGroup", $xdNS)
	    $projectReference = $xml.CreateElement("ProjectReference", $xdNS)
	    $project = $xml.CreateElement("Project", $xdNS)
	    $xmlText = $xml.CreateTextNode($globals.Node.ProjectGuid)
	    $project.AppendChild($xmlText)
	    $projectReference.AppendChild($project)

        $include = $xml.CreateAttribute("Include")

        $dir = Split-Path -parent $toProject
        $include.Value = Get-RelativePath $dir $fromProject
        $projectReference.Attributes.Append($include)


	    $itemGroup.AppendChild($projectReference)

        $root = Select-XML -Xml $xml -XPath '//ms:Project[@DefaultTargets="Build"]' -Namespace $ns
 	    $root.Node.AppendChild($itemGroup)
    }
    $xml.Save($toProject)
}

Function AddPreprocessorDefine($xml, $define)
{
    foreach($item in (Select-XML -Xml $xml -XPath '//ms:ItemDefinitionGroup' -Namespace $ns))
    {
        if(!($item.Node.ClCompile.PreprocessorDefinitions -match ($define + ';')))
        {
            $item.Node.ClCompile.PreprocessorDefinitions = $define + ";" + $item.Node.ClCompile.PreprocessorDefinitions
        }
    }
}

<#
  <ItemGroup>
    <ProjectReference Include="..\..\3rdparty\zlib\zlib.vcxproj">
      <Project>{c38fab57-9dec-4546-bd9a-6c1dbba6c077}</Project>
    </ProjectReference>
  </ItemGroup>
#>




Function RemoveNode($xml, $xpath)
{
    $item = Select-XML -Xml $xml -XPath $xpath -Namespace $ns
    if($item)
    {
        $item.Node.ParentNode.RemoveChild($item.node)
    }
}

Function RemoveProjectFile($path, $filename)
{
    $xml = LoadXmlFile($path)
    $xpath = '//ms:ClCompile [@Include="' + $filename + '"]' 
    RemoveNode $xml $xpath
    $xml.Save($path)
    $xml = LoadXmlFile($path + ".filters")
    RemoveNode $xml $xpath
    $xml.Save($path + ".filters")
}

Function CreateSolutionFile($path, $platform, $projects)
{
    $solution = CreateSolution
    $solution.solutionDir = Split-Path -parent $path
    foreach($project in $projects)
    {
        $solution.AddProject($project)
    }
    $solution.Save($path, $platform)
}



