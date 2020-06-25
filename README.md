# cdfr2020BaseRoulanteRework
code de la base roulante pour la participation de robotronik a la coupe de france 2020 (WIP)


Reminder: To clone the submodule in the same time, use `git clone --recurse-submodules`, then don't forget to build libopencm3

## Documentation
Microcontroller used: STM32F303K8 on a Nulceo-32 board, main doc:
* [Reference Manual STM32F3 line, doc RM0316, 1141 pages](https://www.st.com/content/ccc/resource/technical/document/reference_manual/4a/19/6e/18/9d/92/43/32/DM00043574.pdf/files/DM00043574.pdf/jcr:content/translations/en.DM00043574.pdf)
    * memory map, p57, table 4
* [STM32F303x6/x8 Datasheet, 124 pages](https://www.st.com/content/ccc/resource/technical/document/datasheet/group3/38/c6/ca/d1/f7/d5/4e/30/DM00092070/files/DM00092070.pdf/jcr:content/translations/en.DM00092070.pdf)
    * alternate function, p41, table 14
* [Reference STM Nuleo-32 Board, doc UM1956, 37 pages](https://www.st.com/content/ccc/resource/technical/document/user_manual/e3/0e/88/05/e8/74/43/a0/DM00231744.pdf/files/DM00231744.pdf/jcr:content/translations/en.DM00231744.pdf)

## Coding style

* Tabs are spaces = 4

* Brackets :
    ```
    def MyFunction(params){
        code...
        some more code...
    }
    ```
* Function naming
    * _ is the separator
    * peripheral_action_subjectofaction
    * function starting with _ are private and should not be called in high level code
  
* Variables
    * aaa

* Documentation using doxygen
    * comment the function interface in the .h files (javadoc like)
    * detail the function in .c files

* We envision three levels for the code :
    * 