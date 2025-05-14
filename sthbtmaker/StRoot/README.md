# Project
A package for femtoscopic analysis based on StHbtMaker and AliFemto packages
developed in the STAR and ALICE experiments, respectively.

## Description
The project contains several subdirectories:
- *StHbtMaker/*     - main femtoscopic analysis codes (should not be touched by users)
- *StHbtMakerUser/* - directory that contains correlation functions, cut monitors, and any other user-defined classes
- *macro/*          - codes that launch the whole femtoscopic machinery

To work with Monte Carlo data, for instance, with McDst data format,
it should be placed here: *project/McDst*
The McDst data format can be downloaded from here: https://github.com/nigmatkulov/McDst

## Prerequisites
- make
- g++ (version >= 4.8)
- CERN ROOT of versions 5 or 6

## Compilation
There are several ways of the project compilation:

Let us assume that you need to build the project with StFemtoEvent and
McDst. These instructions are assumes that you are using GNU bash or
any other POSIX compatible shell. Also, it is assumed that the
StFemtoEvent and McDst project diretories are in the project root
directory and **already compiled**. These are a steps which you need
to proceed:

**1) Automatic (GNU Autoconf):**

No deep psychodelic mushrooms dimensions:

1a) Run `$ autoconf` to generate *configure* script.

1b) Run `$ ./configure` script to generate makefiles. Use optional
argument to connect StFemtoEvent and/or McDst readers(see
`$ ./configure --help` for more information):

```shell
$ ./configure --enable-femtoevent --enable-mcdst --with-femtoevent="\"$PWD/StFemtoEvent/\"" --with-mcdst="\"$PWD/McDst/\""
```

1c) Run `$ make -j$(( $(nproc) + 1))` to build a project.

1d) Now, you have three libraries inside `libs/` subdirectory. It also
is a nice step to symlink libMcDst.so and libStFemtoDst.so libraries
(to ease your life) to the `libs/` subdirectory:

```shell
$ pushd libs; ls ../McDst/libMcDst.so ../StFemtoEvent/libStFemtoDst.so | while read file; do ln -s "$file" "$(basename $file)"; done; popd1
```

1e) At last, to run a macro you need to specify LD_LIBRARY_PATH
environment variable to make the dynamic linker to had an access to
the libraries inside `libs/` directory. So, you need to issue (once
for a shell session) the following command:

```shell
$ export LD_LIBRARY_PATH="${LD_LIBRARY_PATH-}:$PWD/libs"
```

For Tolkien lovers (Frodo lives, by the way):

The *GNU Autoconf* [1] utility allows to generate *configure* shell
script from the small *configure.ac*. The resulted *configure* is a
portable way to write a *configure.ac*. One could read and acknowledge
the whole generated *configure* script (and win the ticket to the
psychotherapist). However, to generate *configure* script one need to
run `$ autoconf` command. This command will search for *configure.ac*
file, read it and generate M4 [2] macroses, cache and configure. If it
was done earlier, then one need to run `$ autoreconf -fisv` command, where [3]:

-f stands for *force* (consider all files obsolete)

-i stands for *install* (copy missing auxiliary files)

-s stands for *symlink* (with -i, install symbolic links instead of copies)

-v stands for *verbose* (verbosely report processing)

After *configure* script was generated, one could use it to generate *GNU Makefiles*.
This particular version of the *configure* script allows setup following things:

- Enable/disable generation of the debugging information to DSO with
  option --enable-debug. By default it is switched off.

- Enable/disable StFemtoEvent (--enable-femtoevent) and McDst
  (--enable-mcdst) readers supporting. By default they are switched
  off. If one would like to enable them then bear in mind that these
  options will just add -lStFemtoDst and/or -lMcDst to the linker
  flags. So it is assumed that these libraries and headers are located
  in the system wide search directories.

- To set the path to the headers and shared libraries of the
  StFemtoEvent and McDst one could use the --with-femtoevent and
  --wth-mcdst options, e.g.
  `./configure --with-femtoevent="\"$PWD/StFemtoEvent/\"" --enable-femtoevent`
  to point to the StFemtoEvent directory at the current working
  directory. By default they are not set.

- To enable macros compilations one could add --enable-macro. However,
  to build the macros it is required to enable StFemtoEvent and McDst
  readers support because of the dependencies. Default: no.

- The last option is --enable-native. By the native build it is a
  meaning to build the project without STAR software
 framework. Default: yes.

So, there is a command for all-inclusive build (it is assumed that
McDst and StFemtoEvent directories contains headers and compiled
shared libraries):

```shell
./configure --enable-femtoevent --enable-mcdst --with-femtoevent="\"$PWD/StFemtoEvent/\"" --with-mcdst="\"$PWD/McDst/\"" --enable-debug --enable-macro
```

[1] https://www.gnu.org/software/autoconf/

[2] https://www.gnu.org/software/m4/m4.html

[3] man pages, autoreconf(1)

**2) Automatic (manage_project.sh):**

*(Not optimal way to do it. Should be replaced with Makefile and Makefile.mk files in subdirectories. Compilation with CMake should be also added.)*

The project directory contains shell script named *manage_project.sh*
which accepts to options: a) compile, b) clean

In *manage_project.sh* one **HAS TO** setup PROJDIR variable (at the end of the file, a.k.a. entrance point) pointing to the current directory

To compile the project simply run:
```
./manage_project.sh compile
```
This will perform actions listed in the Manual compilation section. It will also create a directory *project/libs/*, where all compiled shared libraries (and dictionaries, if exist)
will be linked. In addition, it will contain *sthbtmaker_environment.sh* shell script with environment variable set.

**3) Manual:**
3a) Go to StHbtMaker/ and run:
```
make
```
This will make libStHbtMaker.so

3b) Go to the MC or experimental data format subdirectory and also compile it

3c) Go to StHbtMakerUser/ and run:
```
make
```
This will make libStHbtMaker.so

3d) Go to macro/ and run:
```
make
```
or
```
make macroName.cxx
```
for specific user-defined macroName.cxx
This action will lead to the creation of executable code macroName

## Environment setup
In case of the automatic compilation directory *libs/* will contain the *sthbtmaker_environment.sh* shell script. To setup the environment one should go to the *macro/* directory run:
```
source sthbtmaker_environment.sh
```

In case of the manual compilation user need to setup the environment variables by himself/herself.

## Running in a standalone mode
If the environment variables set correctly, then codes can be called from, for instance, *macro/* subdirectory. As an example of the StHbtMaker usage please look at hbtMcDst.cxx
file. The compiled and executable file will be called hbtMcDst. To run it call:
```
./hbtMcDst filename.McDst.root nevents
```
or
```
./hbtMcDst filelist.lis(t) nevents
```
where filelist.lis (or filelist.list) is a file that contains a list of somename.mcDst.root files.

## Troubleshooting
In case of errors please contact package maintainer.

## Known errors

*./macroName: error while loading shared libraries: libStHbtMaker.so: cannot open shared object file: No such file or directory*

The environment variable is set incorrectly.

### Current maintainer
Grigory Nigmatkulov

National Research Nuclear University MEPhI

E-mail: nigmatkulov@gmail.com ; ganigmatkulov@mephi.ru
