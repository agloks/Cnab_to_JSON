cl /c /I .. /EHsc ..\source\date_from_cnab.cpp
lib .\date_from_cnab.obj
cl /I .. /EHsc ..\source\main.cpp /link .\date_from_cnab.lib