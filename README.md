# minesweeper

I made this project for fun to learn the Qt library and environment a little better.

I've compiled this under windows with mingw version of Qt (both 4.8.7 and 5.6.3).  These versions can be downloaded at:
- https://download.qt.io/official_releases/qt/4.8/4.8.7/
- https://download.qt.io/official_releases/qt/5.6/5.6.3/

However, this should build on most any "modern" Qt release, and presumably on all platforms (though I haven't tried anything but Windows).

To build, run the following from a Qt command prompt in the top-level directory where MineSweeper.pro resides:
```
qmake -project
qmake
make
```

Then run the compiled executable.  (In Windows, this shows up in debug\MineSweeper.exe)

