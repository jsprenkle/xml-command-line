@echo off
rem
rem Test and example for XmlCmdImageToPng program
rem written by Jay Sprenkle
rem
echo Convert Example.Image.xml to a PNG format image

rem
rem validate
rem
if not exist dist\Debug\MinGW-Windows\XmlCmdImageToPng.exe (
    echo The "XmlCmdImageToPng" program is missing.
)
if not exist Example.Image.xml (
    echo The "Example.Image.xml" file is missing.
)

rem
rem actual work
rem As per the usual standards you can pass parameters via a configuration file.
rem Add "-c XmlCmdImageToPng.Config.xml" to specify a configuration file to use.
rem The command line file names will trump the file names given in the configuration file.
rem This allows you to use a default global configuration that you can easily override.
rem
dist\Debug\MinGW-Windows\XmlCmdImageToPng TwoColor.Example.xml Test.png

echo Example.png created.
