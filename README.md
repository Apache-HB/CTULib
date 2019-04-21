# CTULib

A proper standard library that was meant to be read by human beings. This library is still very much a work in progress and is not yet fit for production use. One other thing to note is the modified license (this only applies to video games)

## Building

we use buckaroo and buck to build Cthulhu
you can install buck through https://buckbuild.com/setup/getting_started.html
and buckaroo through https://buckaroo.readthedocs.io/en/latest/quickstart.html

### windows
```
touch .buckconfig
buck build //:CthulhuCore //:CthulhuFileSystem
```

### mac/linux

```sh
touch .buckconfig
buck build //:CthulhuCore //:CthulhuConfig
```

## Branches

staging is where stuff changes alot, master is where stuff does not