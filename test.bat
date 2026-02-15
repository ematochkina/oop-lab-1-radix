set PROGRAM="%~1"
set INT_MIN_16="-80000000"
set INT_MAX_16="7FFFFFFF"
set INT_MIN_OVERFLOW_16="-80000001"
set INT_MAX_OVERFLOW_16="80000000"

rem ожидаем ненулевой код ошибки при запуске без параметров
%PROGRAM% > %TEMP%\invalid-argumenst-output.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение о предполагаемом формате ввода
fc.exe %TEMP%\invalid-argumenst-output.txt invalid-argumenst-output.txt 
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запуске с недостаточным количеством параметров
%PROGRAM% 10 2 > %TEMP%\invalid-argumenst-output.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение о предполагаемом формате ввода
fc.exe %TEMP%\invalid-argumenst-output.txt invalid-argumenst-output.txt 
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запуске с избыточным количеством параметров
%PROGRAM% 10 2 5 -h > %TEMP%\invalid-argumenst-output.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение о предполагаемом формате ввода
fc.exe %TEMP%\invalid-argumenst-output.txt invalid-argumenst-output.txt 
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запуске с нечисловым основанием
%PROGRAM% d 2 5 > %TEMP%\non-numeric-radix-output.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение об ошибке в исходной системе счисления
fc.exe %TEMP%\non-numeric-radix-output.txt non-numeric-radix-output.txt 
if ERRORLEVEL 1 goto err
 
rem ожидаем ненулевой код ошибки при запуске с частично числовым основанием
%PROGRAM% 10ab 2 5 > %TEMP%\mixed-radix-output.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение об ошибке в исходной системе счисления
fc.exe %TEMP%\mixed-radix-output.txt mixed-radix-output.txt 
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запуске со значением основания меньшим 2 
%PROGRAM% 1 2 0 > %TEMP%\radix-out-of-range-output.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение об ошибке в исходной системе счисления
fc.exe %TEMP%\radix-out-of-range-output.txt radix-out-of-range-output.txt 
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запуске со значением основания большим 36 
%PROGRAM% 37 2 5 > %TEMP%\invalid-argumenst-output.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение об ошибке в исходной системе счисления
fc.exe %TEMP%\radix-out-of-range-output.txt radix-out-of-range-output.txt 
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запуске с неверно указанной целевой ситемой счисления
%PROGRAM% 36 38 5 > %TEMP%\invalid-destination-output.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение об ошибках в обоих системах счисления
fc.exe %TEMP%\invalid-destination-output.txt invalid-destination-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запуске с обеими неверно указанными ситемами счисления
%PROGRAM% 37 d 5 > %TEMP%\invalid-both-radix-output.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение об ошибках в обоих системах счисления
fc.exe %TEMP%\invalid-both-radix-output.txt invalid-both-radix-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запускеc пустым числом
%PROGRAM% 10 16 "" > %TEMP%\empty-value-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\empty-value-output.txt empty-value-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при запуске с числом, содержащим невалидные символы
%PROGRAM% 10 16 123A > %TEMP%\invalid-symbol-in-radix.txt
if NOT ERRORLEVEL 1 goto err
rem ожидаем оповещение об ошибке в поступишем числе
fc.exe %TEMP%\invalid-symbol-in-radix.txt invalid-symbol-in-radix.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при указании знака (-) без числа
%PROGRAM% 16 10 - > %TEMP%\sign-only-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\sign-only-output.txt sign-only-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при указании знака (+) без числа
%PROGRAM% 16 10 + > %TEMP%\sign-only-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\sign-only-output.txt sign-only-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при переполнении по нижней границе
%PROGRAM% 16 10 -80000001 > %TEMP%\overflow-low-border-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\overflow-low-border-output.txt overflow-low-border-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при переполнении по верхней границе
%PROGRAM% 16 10 80000000 > %TEMP%\overflow-high-border-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\overflow-high-border-output.txt overflow-high-border-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при переполнении по нижней границе при умножении
%PROGRAM% 16 10 %INT_MIN_OVERFLOW_16% > %TEMP%\overflow-multiply-low-border-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\overflow-multiply-low-border-output.txt overflow-multiply-low-border-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при переполнении по верхней границе при умножении
%PROGRAM% 16 10 %INT_MAX_OVERFLOW_16% > %TEMP%\overflow-multiply-high-border-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\overflow-multiply-high-border-output.txt overflow-multiply-high-border-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем успешное выполнение при min int
%PROGRAM% 16 10 %INT_MIN_16% > %TEMP%\low-border-output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\low-border-output.txt low-border-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем успешное выполнение при max int
%PROGRAM% 16 10 %INT_MAX_16% > %TEMP%\high-border-output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\high-border-output.txt high-border-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем успешное выполнение при переводе между граничными системами счисления
%PROGRAM% 36 2 Z > %TEMP%\borders-notation-output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\borders-notation-output.txt borders-notation-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем успешное выполнение при переводе отрицательного нуля
%PROGRAM% 5 12 -0 > %TEMP%\zero-output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\zero-output.txt zero-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем успешное выполнение при переводе положительного нуля
%PROGRAM% 13 25 +0 > %TEMP%\zero-output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\zero-output.txt zero-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем успешное выполнение при переводе нуля
%PROGRAM% 14 30 0000 > %TEMP%\zero-output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\zero-output.txt zero-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем успешное выполнение при переводе числа, начинающиегося на 0
%PROGRAM% 33 17 000U2V > %TEMP%\zero-first-output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\zero-first-output.txt zero-first-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем вывод поданного значения в рамках одной системы счисления
%PROGRAM% 17 17 6B68 > %TEMP%\in-one-radix-output.txt
if ERRORLEVEL 1 goto err
fc.exe %TEMP%\in-one-radix-output.txt in-one-radix-output.txt
if ERRORLEVEL 1 goto err

rem ожидаем ненулевой код ошибки при указании некорректного числа в одной системе счисления
%PROGRAM% 35 35 YYZ > %TEMP%\invalid-value-in-one-radix-output.txt
if NOT ERRORLEVEL 1 goto err
fc.exe %TEMP%\invalid-value-in-one-radix-output.txt invalid-value-in-one-radix-output.txt
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit 0

:err
echo Program testing failed
exit 1