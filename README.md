# jrat

**J**ust **R**ight-Click **A**ny**t**hing

~~Josh Richard Tyson Andrew~~

Right click an image for common manipulation tasks such as crop, resize, convert, flip, etc.

# Setup

* Download [OpenCV 4.9.0](https://github.com/opencv/opencv/releases/tag/4.9.0)
* Put the `opencv_world490.dll` / `opencv_world490d.dll` files somewhere on PATH

**Installer**

In order to build the installer, it needs all the other programs built first. For this reason, the
installer will not build by default unless the `installer/res/` folder exists.

* Build all programs in release mode
* Run `copy_installer_binaries.sh <build directory>` in bash from root project directory
  * FYI: On Visual Studio, build directory is likely `out/build/x64-release/`
  * This will create the `res/` folder with all the binaries it needs
* Build all again. The installer should be built this time
