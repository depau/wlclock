# Wayland Clock

An Xclock replacement for Wayland (and X11), prettier.

Heavily based on https://developer.gnome.org/gtkmm-tutorial/stable/sec-drawing-clock-example.html.en

My changes mostly improve look and customizability, you still need to change the program to customize it.

Not the prettiest code, please send pull requests and fix if that is a concern.

## Building

Requires Gtkmm, CMake, pkg-config.

```
mkdir build
cd build
cmake ..
make
```

## License

The code it is based on is based on documentation licensed under the [GNU FDL 1.2+](https://developer.gnome.org/gtkmm-tutorial/stable/index-info.html.en)

My changes are licensed under the GNU GPL3+ license.
