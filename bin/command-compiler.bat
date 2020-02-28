echo "COMPILANDO"

cl /c /I .. /EHsc ..\source\date_from_cnab.cpp
cl /c /I .. /EHsc ..\source\read_from_config.cpp
lib .\date_from_cnab.obj
lib .\read_from_config.obj
cl /I .. /EHsc ..\source\main.cpp /link .\date_from_cnab.lib .\read_from_config.lib