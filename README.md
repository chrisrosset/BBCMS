BBCMS
=====


Project Description
-------------------

BBCMS is a mock electronic platform for trading commodities contracts
written in accordance to the given specification.



High-level Design Overview
--------------------------

Model, view, controller
encapsulation, extensibility
division of responsibility

style stuff:
* avoiding exceptions (well-defined grammar makes for simple error detection)
* hand-written parser (grammar too simple to justify the additional cost of 
  using a parser combinators or a lexer/parser generator)


Extensions
----------

### Extension 1 (reading data over a TCP connections)

### Extension 2 (multiple TCP connections)



Build Instructions
------------------

The project has the following software dependencies:

* GNU G++ Compiler with support for C++03
* GNU Make
* Boost (`boost::unordered_map`)

To build the project `cd` into the main project directory and run make.

    cd BBCMS
    make

This will produce a binary called `cms` in the `bin` folder.
To run it from the project's main directory, execute:

    ./bin/cms <arguments>


Known Bugs
----------

