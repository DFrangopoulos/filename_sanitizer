# filename_sanitizer
A tool that sanitizes filenames

## Description
Removes any character that is not [A-Z] or [a-z] or [0-9] or [_] and maintains the . (of the extension). The removed character is replaced with an underscore, if there are multiple invalid characters in a row, then they are all replaced by a single underscore. The output string does not include a newline.

## Running
```bash
./filename_sanitizer <input>
```
## TODO
- Add makefile
