# libcppdotnet - A C++ library

The `libcppdotnet` C++ library provides a reimplementation of some .NET classes and functionality
using modern C++ methods.

This repository is currently an experiment to port another repository, 'cppdotnet' to use C++20
modules and the 'build2' build system (https/www.build2.org).

**NOTE:** *The current state of g++ (as of 14) has led me to abandon this project, as there are too
many compiler crashes currently and I just got tired of running into them.  I am sad to say that g++ is not ready for
a mediom-sized library that uses modules, and probably will not be for some years to come.  I will revisis this around 2030
and see if the situation has improved.*

## Questions

**Q:** Why did you decide to convert your library to use modules?

**A:** I wanted to see what an implementation of my cppdotnet libraries using modules would look like!  I love to learn
and this is the best way for me to do that.

Lessons Learned:
* G++ can't handle module code of anything beyond simple complexity.  Still too many bugs!
* **CONVERTING** your old code to using modules is a waste of your valuable time.  If you begin with
using modules, then you are fine.  It  provides no benefit that I can ascertain to just
convert old code other than creating complexity for the sake of a feature that you don't
really need to use.
* Modules create compilation-order dependencies, which may reduce the overall parallelism of
your compilation process.

**Q:** Why did you decide to use the 'build2' system instead of just using CMAKE?

**A:** I already have experience with CMAKE and I wanted to learn something different.  I really like
the entire build2 ecosystem and how it integrates with projects at a higher level than just CMAKE alone.

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
