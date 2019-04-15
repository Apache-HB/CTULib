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

### Testing

we use the `ctest` test suite, it can be run by typing `ctest --output-on-failure`

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

disable native instruction set (on by default)
```
-DNATIVE=OFF
```
## Documenting

adding documentation is as easy as commenting your code using the doxygen @ style, additionally all classes/functions put inside 
```cpp
namespace Private
```
will be ignored by doxygen docs. to build docs install doxygen, navigate to the root directory and create a document folder
`mkdir Docs && cd Docs`
then run doxygen
`doxygen ../Doxyfile`

## Branches

staging is where stuff changes alot, master is where stuff does not