# CTULib

A proper standard library that was meant to be read by human beings. This library is still very much a work in progress and is not yet fit for production use. One other thing to note is the modified license (this only applies to video games)

## Building

### windows
```
mkdir Build
cd Build
cmake .. -G "Visual Studio 15 2017"
```

### mac/linux

```sh
mkdir Build
cd Build
cmake ..
make
```

### Options
enable debug flags
```
-DDEBUG=ON
```
enable optimizations
```
-DRELEASE=ON
```
make `CTU_INLINE` use `ALWAYSINLINE` instead of `inline`
```
-DFORCEINLINE=ON
```

## Documenting

adding documentation is as easy as commenting your code using the doxygen @ style, additionally all classes/functions put inside 
```cpp
namespace Private
```
will be ignored by doxygen docs. to build docs install doxygen, navigate to the root directory and execute `doxygen CthulhuLib`

## Branches

staging is where stuff changes alot, master is where stuff does not