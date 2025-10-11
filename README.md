# libcppdotnet - A C++ library

The `libcppdotnet` C++ library provides <SUMMARY-OF-FUNCTIONALITY>.


## Usage

To start using `libcppdotnet` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: libcppdotnet ^<VERSION>
```

Then import the library in your `buildfile`:

```
import libs = libcppdotnet%lib{<TARGET>}
```


## Importable targets

This package provides the following importable targets:

```
lib{<TARGET>}
```

<DESCRIPTION-OF-IMPORTABLE-TARGETS>


## Configuration variables

This package provides the following configuration variables:

```
[bool] config.libcppdotnet.<VARIABLE> ?= false
```

<DESCRIPTION-OF-CONFIG-VARIABLES>

## NOTES

Under the build2 system, this was created with:

```
bdep new -l c++ -t lib,split,unit-tests libcppdotnet
```
