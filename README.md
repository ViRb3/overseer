# overseer
A tool that searches an Android device for files containing its MAC address. Originally developed as a part of a generic MAC changer project.

## Usage

Run this tool without any arguments to display help:
```
overseer MAC_ADDR [-v] [-b /ex/skipfile.ext /ex/sub/skipfile2.ext ...]

MAC_ADDR    format: AABBCCDDEEFF
-v          verbose output
-b          blacklisted paths to skip
```

## Binaries

You can grab them [HERE](https://github.com/ViRb3/overseer/releases).

## Building

This project was built with `VisualGDB 5.3` for `Visual Studio 2017`. If you have the same setup, just open the solution and hit `Build`. If not, you can port the source to other platforms or build it using different tools with minimal changes.
