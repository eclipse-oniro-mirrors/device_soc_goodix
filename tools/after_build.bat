::=============================================================================
:: Developer should configure KEIL_PATH, TOOL_PATH, TARGET
::=============================================================================
@echo off
::set the build environment
@set TARGET=application

rem : 待转换的固件的存放路径
@set RAW_BIN_PATH=.\

rem : 待转后的固件输出路径
@set OUTPUT_DIR_PATH=.\ble_tool_bin
@set TOOL_PATH=.\
@set TARGET_APP=%TARGET%_fw

@if not exist  %OUTPUT_DIR_PATH% (
md %OUTPUT_DIR_PATH%
) else (
del /q/s %OUTPUT_DIR_PATH%\* >nul
)

copy %RAW_BIN_PATH%\%TARGET%.bin %OUTPUT_DIR_PATH%\%TARGET%.bin >nul

::Generate system all output files
%TOOL_PATH%\ble_tools.exe --mode=gen_fw --cfg=custom_config.h  --bin=%OUTPUT_DIR_PATH%\%TARGET%.bin --out_dir=%OUTPUT_DIR_PATH% --app_name=%TARGET_APP%

del /q/s %OUTPUT_DIR_PATH%\*.tmp >nul
del /q/s %OUTPUT_DIR_PATH%\info.* >nul
del /q/s %OUTPUT_DIR_PATH%\header.bin >nul

::copy the bin,axf,sct... to output dir
copy %RAW_BIN_PATH%\%TARGET%.axf %OUTPUT_DIR_PATH%\%TARGET%.axf >nul
copy %LISTING_DIR_PATH%\%TARGET%.map %OUTPUT_DIR_PATH%\%TARGET%.map >nul
copy %RAW_BIN_PATH%\%TARGET%.s %OUTPUT_DIR_PATH%\%TARGET%.s >nul
rename %OUTPUT_DIR_PATH%\%TARGET_APP%.hex load_app.hex >nul

echo Firmware has been successfully generated!

timeout /T 1

exit
