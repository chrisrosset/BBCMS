BBCMS
=====


Project Description
-------------------

BBCMS is a mock electronic platform for trading commodities contracts written in accordance to the given specification.



High-level Design Overview
--------------------------

BBCMS follows the MVC (Model, View, Controller) design pattern. 
Information entered via standard I/O (or a TCP connection) is processed by the parser to produce an object representing a command.
This command object is passed on to an instance of OrderStore which serves as our model (back-end) and provides the application's core logic.
The results of executing a command are passed back to the controller which uses the "outputBuilder" (a fairly abstact component as it is actually just a bundle of functions) which are responsible for building the actual textual output (this is done to decouple error handling logic from generating the error/output messages).
Finally, the controller outputs these output messages on the appropriate output stream.

                     outputBuilder
                        (View)
                         /|\
                          |
                     7.|  | 6./|\
                      \|/ |    |
                          |
                          |
             1.->        \|/       4.->
     Input/ <-------> Controller <---------> OrderStore
     Output      8.<-    /|\            5.<-  (Model)
                          |
                          |
                     2.|  | 3./|\
                      \|/ |    |
                          |
                          |
                         \|/
                        Parser


Other points:
* eschewing exceptions (well-defined grammar makes for simple error detection)
* hand-written parser (grammar too simple to justify the additional cost of 
  using a parser combinators or a lexer/parser generator)



Extensions
----------

### Extension 1 (reading data over a TCP connections)

Extension 1 has been implemented in accordance with the spec.
It can be tested running `./cms ext1 <port>`, which starts the TCP server.


### Extension 2 (multiple TCP connections)

Not implemented.



Build Instructions
------------------

The project has the following software dependencies:

* GNU G++ Compiler with support for C++03
* GNU Make
* Boost (`boost::unordered\_map`, `boost::asio`)
* pthreads

To build the project `cd` into the main project directory and run make.

    cd BBCMS
    make

This will produce a binary called `cms` in the `bin` folder.
To run it from the project's main directory, execute:

    ./bin/cms <arguments>


Known Bugs
----------

