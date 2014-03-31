. ".\scripts\converterutils.ps1"

#use MSBuild namespace
$ms = 'http://schemas.microsoft.com/developer/msbuild/2003'
$ns = @{ ms = $ms }




Function ConvertAdditionalIncludesToRelativePaths($paths, $folder)
{
    $result = ""
    $tokens = $paths.replace(' ','').split(';')
    foreach($token in $tokens)
    {
        if($token -ne "%(AdditionalIncludeDirectories)")
        {
            $result += (Get-RelativePath $folder $token)  + ';'
        }
        else
        {
            $result += "%(AdditionalIncludeDirectories);"
        }

    }
    return $result
}




Function WinrtConverter($inFile, $outFile, $platform)
{
    $InputDirPath = Split-Path -parent $inFile
    $InputDir =  [System.IO.Path]::GetFileNameWithoutExtension($InputDirPath)
    $fileName = [System.IO.Path]::GetFileNameWithoutExtension($inFile)
    $OutDir = Split-Path -parent $outFile

    #create output dir
    New-Item -ItemType Directory -Force -Path $OutDir

    <# 
        Try to load the output file.
        If successful, copy the guid out of the globals section
    #>

    $guid =$null

    try
    {
        $xml = New-Object -TypeName XML
        $xml.Load($outFile)
        $globals = Select-XML -Xml $xml -XPath '//ms:PropertyGroup[@Label="Globals"]' -Namespace $ns
        $guid = $globals.Node.ProjectGuid
    }
    catch
    {
        $guid = '{' + [guid]::NewGuid().toString().ToUpper() + '}'
    }

    # load input file into an XML object:
    $xml_win32 = New-Object -TypeName XML
    $xml_win32.Load($inFile)

    $configs = Select-XML -Xml $xml_win32 -XPath '//ms:PropertyGroup[@Label="Configuration"]' -Namespace $ns

    $Template = $null

    if($platform -eq "winrt")
    {
        if($configs[0].Node.ConfigurationType -eq "DynamicLibrary")
        {
            $Template = join-path $PSScriptRoot "templates\winrt_dll_template.vcxproj"
        }
        elseif($configs[0].Node.ConfigurationType -eq "StaticLibrary")
        {
            $Template = join-path $PSScriptRoot "templates\winrt_lib_template.vcxproj"
        }
        else
        {
            throw "Unknown vcxproj type"
        }
    }
    elseif($platform -eq "wp8")
    {
        if($configs[0].Node.ConfigurationType -eq "DynamicLibrary")
        {
            $Template = join-path $PSScriptRoot "templates\wp8_dll_template.vcxproj"
        }
        elseif($configs[0].Node.ConfigurationType -eq "StaticLibrary")
        {
            $Template = join-path $PSScriptRoot "templates\wp8_lib_template.vcxproj"
        }
        elseif($configs[0].Node.ConfigurationType -eq "Application")
        {
            $Template = join-path $PSScriptRoot "templates\wp8_lib_template.vcxproj"
        }
        else
        {
            throw "Unknown vcxproj type"
        }
    }
    else
    {
        throw "Unknown platform argument -p (winrt or wp8)"
    }

    $xml_template = New-Object -TypeName XML
    $xml_template.Load($Template)


    #Update Project Guid and Name
    $win32_globals = Select-XML -Xml $xml_win32 -XPath '//ms:PropertyGroup[@Label="Globals"]' -Namespace $ns

    $winrt_globals = Select-XML -Xml $xml_template -XPath '//ms:PropertyGroup[@Label="Globals"]' -Namespace $ns
    $winrt_globals.Node.ProjectGuid = $guid


    if($win32_globals.Node.ProjectName)
    {
        $winrt_globals.Node.RootNamespace = $win32_globals.Node.ProjectName
 
        if($winrt_globals.Node.ProjectName)
        {
            $winrt_globals.Node.ProjectName = $win32_globals.Node.ProjectName
        }
    }



    if($win32_globals.Node.RootNamespace)
    {
        $winrt_globals.Node.RootNamespace = $win32_globals.Node.RootNamespace
    }

    $project = Select-XML -Xml $xml_template -XPath '//ms:Project' -Namespace $ns



    foreach($item in (Select-XML -Xml $xml_win32 -XPath '//ms:ItemGroup' -Namespace $ns))
    {
        if ($item.node.ClInclude -or $item.node.ClCompile)
        {
            $newNode = $xml_template.ImportNode($item.Node, $true)
            $project.Node.AppendChild($newNode)
        }
    }


    #Copy ItemDefinitionGroup properties
    $debug_properties = $null
    $release_properties = $null


    foreach($item in (Select-XML -Xml $xml_win32 -XPath '//ms:ItemDefinitionGroup' -Namespace $ns))
    {
        if($item.node.Condition -match "debug")
        {
            $debug_properties = $item
        }
        else
        {
            $release_properties = $item
        }
    }

    $debug_includes = $debug_properties.Node.ClCompile.AdditionalIncludeDirectories
    $release_includes = $release_properties.Node.ClCompile.AdditionalIncludeDirectories


    foreach($item in (Select-XML -Xml $xml_template -XPath '//ms:ItemDefinitionGroup' -Namespace $ns))
    {
        $includes = $release_includes;
        $properties = $release_properties

        if($item.node.Condition -match "debug")
        {
            $includes = $debug_includes;
            $properties = $debug_properties
        }

        AddElement $xml_template $item.Node.ClCompile 'AdditionalIncludeDirectories'  $includes $ms
        AddElement $xml_template $item.Node.ClCompile 'PreprocessorDefinitions'  $properties.Node.ClCompile.PreprocessorDefinitions $ms
        if($properties.Node.ClCompile.PrecompiledHeader)
        {
           $item.Node.ClCompile.PrecompiledHeader = $properties.Node.ClCompile.PrecompiledHeader
        }

        if($properties.Node.ClCompile.PrecompiledHeaderFile)
        {
            AddElement $xml_template $item.Node.ClCompile 'PrecompiledHeaderFile'  "precomp.hpp" $ms
        }



        if($properties.Node.ClCompile.ForcedIncludeFiles)
        {
            AddElement $xml_template $item.Node.ClCompile 'ForcedIncludeFiles'  "precomp.hpp" $ms
         }


        if($properties.Node.ClCompile.DisableSpecificWarnings)
        {
            AddElement $xml_template $item.Node.ClCompile 'DisableSpecificWarnings'  $properties.Node.ClCompile.DisableSpecificWarnings $ms
        }
    }


    #save output file
    $xml_template.Save($outFile)




    foreach($item in (Select-XML -Xml $xml_template -XPath '//ms:Project//ms:ItemGroup//ms:ClCompile//ms:PrecompiledHeader' -Namespace $ns))
    {
        $newNode = $xml_template.ImportNode($item.Node, $true)
        $newNode.Condition = $newNode.Condition.replace("Win32", "ARM")
        $item.Node.parentNode.AppendChild($newNode)
        $newNode = $xml_template.ImportNode($item.Node, $true)
        $newNode.Condition = $newNode.Condition.replace("Win32", "x64")
        $item.Node.parentNode.AppendChild($newNode)
    }

    foreach($item in (Select-XML -Xml $xml_template -XPath '//ms:Project//ms:ItemGroup//ms:ClCompile//ms:PrecompiledHeaderFile' -Namespace $ns))
    {
        $item.Node."#text" = "precomp.hpp"
        $newNode = $xml_template.ImportNode($item.Node, $true)
        $newNode.Condition = $newNode.Condition.replace("Win32", "ARM")
        $item.Node.parentNode.AppendChild($newNode)
        $newNode = $xml_template.ImportNode($item.Node, $true)
        $newNode.Condition = $newNode.Condition.replace("Win32", "x64")
        $item.Node.parentNode.AppendChild($newNode)
    }

    $xml_template.selectNodes('//data/value[contains(.,"precomp.hpp")]')|
    ForEach-Object{
        $_.'#text' = 'precomp.hpp'
    }

    $xml_template.Save($outFile)


    #copy .filters file
    try
    {
        $filters = $inFile + ".filters"
        $xml_filters = New-Object -TypeName XML    
        $xml_filters.Load($filters)
        $xml_filters.Save($outFile + ".filters")
    }
    catch
    {
        Write-Host "No .filters file"
    }
}



