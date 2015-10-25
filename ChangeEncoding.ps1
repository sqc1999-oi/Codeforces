foreach ($f in (dir -recurse))
{
    if ($f.extension -eq ".sln" -or $f.extension -eq ".cs" -or $f.extension -eq ".csproj" -or $f.extension -eq ".vcxproj" -or $f.extension -eq ".cpp")
    {
        $s=gc $f.fullname
        sc -path $f.fullname -value $s -encoding utf8
    }
}