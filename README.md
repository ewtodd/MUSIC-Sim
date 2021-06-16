# MUSIC simulator

Created by Daniel Santiago-Gonzalez (Argonne National Laboratory)
ver 3.1 (2021/6)


## Requirements

1. linux based operating system (tested in Ubuntu 20, Debian 9 and CentOS 7) or MacOS
2. ROOT 6 with EVE utilities for 3D visualization (see https://root.cern.ch/eve). Tested with ROOT 6.18/02 and 6.22/06 prepackaged binary files downloaded from [this website](https://root.cern/install/all_releases/).
3. `g++` compiler (tested with g++ 4.8.4)
4. `git` (tested with version 1.9.1)
5. `make` 

## Installation instructions (for linux or MacOS) 

1. Get the source code. `cd` to your preferred working directory then type

`git clone https://gitlab.phy.anl.gov/music/sim`

2. Change direcotry

`cd sim` 

3. Compile it by typing 

`make`

4. Test it

`./musicsim basic.msc`

If everything went well you should see two windows, one with a 2D plot of the MUSIC traces and another one with a 3D view of the event.
