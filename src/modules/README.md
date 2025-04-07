# Modules

A Module implements a given functionality and can interact with other modules. Modules are therefore implemented as if they are "global"


## Module Structure
Every Module that needs to be updated needs to have a loop and setup function named in such manner:
`void modulename_setup(void)`
`void modulename_loop(void)`

They then need to be called in main.cpp in Arduinos setup and loop functions.