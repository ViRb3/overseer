# overseer
A library that searches an Android device for files containing its MAC address. Originally developed as a part of a generic MAC changer project.

## Usage

```
overseer MAC_ADDR [-v] [-b /ex/skipfile.ext /ex/sub/skipfile2.ext ...]

MAC_ADDR    format: AABBCCDDEEFF
-v          verbose output
-b          blacklisted paths to skip
```
