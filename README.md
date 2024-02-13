# Project2-ComputerSystems2

To build a parser, implememnt grammar, and build "code beautifier"

Author: Eric Hansson

- What platform you developed your solution on (i.e Linux, OS/X, Windows (God forbid!), ...) <br>
Arch Linux

- any special details on how to compile your project <br>
Used a Makefile which creates a executable called `beautifier`, this is done by running this command:
```
make
```
- any special details on how to run your project <br>
To run the program you need to give the program a input file:
```
./beautifier <input>
```
- any known bugs your project has, and possible fixes to those bugs <br>
The formating is not correctyl, I had issues with the indenting for stmts in a compound.
The main file needs to be fixed to make sure that it can print out if there is a invalid program.

- an overview of how you solved the project. <br>
For the project I focused in implementing on piece at a time. I started with factor and then I worked myself up the list
which, then I had to implement different grammar that was need to other grammar.
