@echo off
rem
rem Unit Test for XmlCompare program
rem written by Jay Sprenkle
rem
if not exist dist\Debug\MinGW-Windows\XmlCompare.exe (
    ECHO The "XmlCompare" program is missing.
    EXIT /B 1
)

rem test 01: files are identical
rem
rem validate inputs and required programs exist
rem
if not exist Test01a.xml (
    ECHO The "Test01a.xml" file is missing.
    EXIT /B 1
)
if not exist Test01b.xml (
    ECHO The "Test01b.xml" file is missing.
    EXIT /B 1
)
rem
rem run test
rem
dist\Debug\MinGW-Windows\XmlCompare Test01a.xml Test01b.xml
if NOT %errorlevel%==0 (
    ECHO Test01: The comparison failed but should not have.
    EXIT /B 1
) ELSE (
    ECHO Test01 PASS
)


rem test 02: Second file is missing a node
rem
rem validate inputs and required programs exist
rem
if not exist Test02a.xml (
    ECHO The "Test02a.xml" file is missing.
    EXIT /B 1
)
if not exist Test02b.xml (
    ECHO The "Test02b.xml" file is missing.
    EXIT /B 1
)
rem
rem run test
rem
dist\Debug\MinGW-Windows\XmlCompare Test02a.xml Test02b.xml
if %errorlevel%==0 (
    ECHO Test02: The comparison succeeded but should not have.
    EXIT /B 1
) ELSE (
    ECHO Test02 PASS
)

rem test 03: First file is missing a node
rem
rem validate inputs and required programs exist
rem
if not exist Test03a.xml (
    ECHO The "Test03a.xml" file is missing.
    EXIT /B 1
)
if not exist Test03b.xml (
    ECHO The "Test03b.xml" file is missing.
    EXIT /B 1
)
rem
rem run test
rem
dist\Debug\MinGW-Windows\XmlCompare Test03a.xml Test03b.xml
if %errorlevel%==0 (
    ECHO Test03: The comparison succeeded but should not have.
    EXIT /B 1
) ELSE (
    ECHO Test03 PASS
)


rem test 04: files missing
rem
dist\Debug\MinGW-Windows\XmlCompare Test04a.xml Test04b.xml
if %errorlevel%==0 (
    ECHO Test04: The comparison succeeded but should not have.
    EXIT /B 1
) ELSE (
    ECHO Test04 PASS
)

rem test 05: files missing
rem
dist\Debug\MinGW-Windows\XmlCompare Test01a.xml Test05b.xml
if %errorlevel%==0 (
    ECHO Test05: The comparison succeeded but should not have.
    EXIT /B 1
) ELSE (
    ECHO Test05 PASS
)

rem test 06: files missing
rem
dist\Debug\MinGW-Windows\XmlCompare Test06a.xml Test01b.xml
if %errorlevel%==0 (
    ECHO Test06: The comparison succeeded but should not have.
    EXIT /B 1
) ELSE (
    ECHO Test06 PASS
)

rem test 07: First file content different
rem
rem validate inputs and required programs exist
rem
if not exist Test07a.xml (
    ECHO The "Test07a.xml" file is missing.
    EXIT /B 1
)
if not exist Test07b.xml (
    ECHO The "Test07b.xml" file is missing.
    EXIT /B 1
)
rem
rem run test
rem
dist\Debug\MinGW-Windows\XmlCompare Test07a.xml Test07b.xml
if %errorlevel%==0 (
    ECHO Test07: The comparison succeeded but should not have.
    EXIT /B 1
) ELSE (
    ECHO Test07 PASS
)

rem test 08: Second file content different
rem
rem validate inputs and required programs exist
rem
if not exist Test08a.xml (
    ECHO The "Test08a.xml" file is missing.
    EXIT /B 1
)
if not exist Test08b.xml (
    ECHO The "Test08b.xml" file is missing.
    EXIT /B 1
)
rem
rem run test
rem
dist\Debug\MinGW-Windows\XmlCompare Test08a.xml Test08b.xml
if %errorlevel%==0 (
    ECHO Test08: The comparison succeeded but should not have.
    EXIT /B 1
) ELSE (
    ECHO Test08 PASS
)
