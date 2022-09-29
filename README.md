# DLLFileDropper
C++ DLL code for downloading and executing second stage payloads.

Dropper.dll will download a second stage .exe payload via `URLDownloadToFile` and execute it with `CreateProcess`. 

**You will need to alter the "CHANGE_ME_XXX" values and compile the 'dllmain.cpp' cpp file**

Windows execution -> `C:\Windows\System32\Rundll32.exe C:\temp\Dropper.dll,run` 
