# cdict 
+ Simple string to string dictionary implementation

## Implementation Detail
+ Internal data structure is just a sorted array. So, it's not efficient when frequent add/delete is required.


## Crosscompile to Windows
```sh
mkdir -p winbuild
cd winbuild
cmake -DCMAKE_TOOLCHAIN_FILE=../TC-mingw.cmake ..

```