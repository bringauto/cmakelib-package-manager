
# BringAuto Package Tracker

BringAuto package tracker based on [BringAuto Packager] and [CMake-lib]

## Usage

```
# Add package - download, cache and populate
BA_PACKAGE_LIBRARY(nlohmann-json v3.10.5 PLATFORM_STRING_MODE any_machine)
# Find package as described in the library manual 
FIND_PACKAGE(nlohmann_json 3.2.0 REQUIRED)
```

Full example: [example/]

## Requirements

- [CMake-lib] with STORAGE component enabled. One of the storage entry must points to this repo.
- Package repository that is complain with [BringAuto Packager] package repository structure.


## Macros

- `BA_PACKAGE_LIBRARY` downloads and init package build by [BringAuto Packager]
- `BA_PACKAGE_DEPS_IMPORTED` installs all imported linked dependencies for a given target
- `BA_PACKAGE_DEPS_SET_TARGET_RPATH` update R/RUNPATH for a given target

## Settings

- `REVISION` - git revision to use when accessing Package repository. Default: master
```cmake
# Set REVISION to revision_update
BA_PACKAGE_VARS_SET(REVISION deps_update)
# Obtain nlohmanjson not from default branch but from deps_update branch
BA_PACKAGE_LIBRARY(nlohmann-json v3.10.5 PLATFORM_STRING_MODE any_machine)
```

## FAQ

### Q: Package not found even if it exists in the remote repository

Make sure you choosed correct `PLATFORM_STRING_MODE`.

If package is not bound to the architecture or Linux distro this context info must be passed down by the `PLATFORM_STRING_MODE`.

### Q: Package conflict if I want to build my project by second build type

If you want to use same cache path for Release and Debug build type
you must ensure that the package differ between Debug/Release build config
and does not have files with the same path.

If you have a package that has a same content for Debug and Release you need to
use `NO_DEBUG ON` in `BA_PACKAGE_LIBRARY` otherwise the conflict occure.

(Look at [example/] for quick overview)



[BringAuto Packager]: https://github.com/bringauto/packager
[CMake-lib]: https://github.com/cmakelib/cmakelib
[example/]: example/