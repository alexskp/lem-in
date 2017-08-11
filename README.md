# lem-in

**Lem-in** is a project task from from UNIT Factory school. The program will receive the data describing the ant farm from the standard output in the following format:
   * number_of_ants
   * the_rooms
   * the_links

The ant farm is defined by the following lines:

    ##start
    1 23 3
    2 16 7
    #comment
    3 16 3
    4 16 5
    5 9 3
    6 1 5
    7 4 8
    ##end
    0 9 5
    0-4
    0-6
    1-3
    4-3
    5-2
    3-5
    #another comment
    4-2
    2-1
    7-6
    7-2
    7-4
    6-5
Which corresponds to the following representation:

                  ______________
                /                \
        ______[5]----[3]----[1]   |
      /              |     /      |
    [6]-----[0]----[4]   /        |
     \    _________/ | /          |
       \ /          [2]__________/
        [7]_________/

**There are two parts:**
  - The rooms, which are defined by: name coord_x coord_y
  - The links, which are defined by: name1-name2

Comment line starts with # and can be placed anyware. Lines that start with ## are commands modifying the properties of the line that comes right after. For example, ##start signals the ant farm’s entrance and ##end its exit.

Results displayed on the standard output in the following format:
* number_of_ants
* the_rooms
* the_links
* Lx-y Lz-w Lr-o ...
x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y,
w, o represents the rooms’ names.


**Example:**

        [2]
       / | \
    [0]  |  [1]
       \ | /
        [3]

Console output:

    alex@acer:~/Dropbox/dev/lem-in$ ./lem-in < maps/map
    3
    2 5 0
    ##start
    0 1 2
    ##end
    1 9 2
    3 5 4
    0-2
    0-3
    2-1
    3-1
    2-3

    L1-2 L2-3
    L1-1 L2-1 L3-2
    L3-1
    alex@acer:~/Dropbox/dev/lem-in$
