# parameter-framework

## Introduction

The parameter-framework is a plugin-based and rule-based framework for handling
parameters.  This means that you can:

1. Describe your system's structure and its parameters (in XML) - aka. **What**;
2. Write (in C++) or reuse a backend (aka. plugin) for accessing the parameters
that you just described - aka. **How**;
3. Define (in XML or in a domain-specific-language) conditions/rules upon which
a given parameter must take a given value - aka. **When**.

### Usage examples

#### Alsa controls on embedded platforms

The parameter-framework can be used to set the value of alsa controls
(switches, volumes, etc.) on smartphones/tablets based on parameter-framework
rules (in this example, they transcribe use-cases).  For accessing parameters
(i.e. alsa controls), you may use the
[alsa plugin](https://github.com/01org/parameter-framework-plugins-alsa).

### More details

The parameter-framework's core comes in the form of a shared library.  Its
client has to provide it with configuration files.

At runtime, the most usual communication between the client and the
parameter-framework is the update of *criteria* (that are used in the rules
introduced above) and requests for updating the parameter which values may have
changed as the result of the change in criteria.  The parameter-framework uses
the relevant backend for writing the values in each underlying subsystem.

The parameter-framework comes with several tools, including a command-line
interface: `remote-process`.

## Going further

See [the wiki on github](https://github.com/01org/parameter-framework/wiki).

## Compiling

Run `cmake .` then `make`.  You may then install libraries, headers and
binaries with `make install`.  By default, they are installed under
`/usr/local` on unix OSes; if you want to install them under a custom
directory, you may do so by passing it to the `cmake .` command; e.g.
`cmake -DCMAKE_INSTALL_PREFIX=/path/to/custom/install .`.
