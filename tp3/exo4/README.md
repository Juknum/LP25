## Expected result:

```powershell
>> ./ihex2bin Appli-ng.hex Appli-ng.bin
# Windows:
>> diff -ReferenceObject (Get-Content -Path Appli-ng.bin) -DifferenceObject (Get-Content -Path Appli-ng_ORIGIN.bin)
# Unix:
>> diff Appli-ng.bin Appli-ng_ORIGIN.bin

-> No output should be shown

```
