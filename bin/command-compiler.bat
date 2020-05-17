@echo off
echo "COMPILANDO"

cl /c /I .. /EHsc ..\source\data_from_cnab.cpp
cl /c /I .. /EHsc ..\source\read_from_config.cpp
cl /c /I .. /EHsc ..\lib\utility.cpp

lib .\utility.obj

lib .\data_from_cnab.obj
lib .\read_from_config.obj
cl /I .. /EHsc ..\source\main.cpp /link .\read_from_config.lib .\utility.lib .\data_from_cnab.lib
