# Path Finder - Algorithms

The PathFinder application is a C ++ app made on top of wxWidgets and Boost. It has been built and tested on Linux (Ubuntu 18.04) with cmake.
A number of algorithms have been implemented in the system to find a path. These can be selected in the UI to get a visual picture of how the algorithm works.

---

## Pre-conditions / Downloads

The following artifacts / tools are used by and included in the extension as-is:

- wxWidgets 3.1.3: [https://github.com/wxWidgets/wxWidgets/releases/tag/v3.1.3](https://github.com/wxWidgets/wxWidgets/releases/tag/v3.1.3)
- Boost: [https://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html](https://www.boost.org/doc/libs/1_66_0/more/getting_started/unix-variants.html)

---

## Build

- Clone the files from the repo to a folder on your OS. 
- Navigate in the folder where all files are cloned and execute: './autogen.sh' here. 
- run the command: "mkdir build". 
- Then navigate to the build directory using: 'cd build /' 
- Run the command: "../configure --with-cxx = 17". 
- Build the application using: "make -j4"
- The program can be started using the command: './src/robotworld'

