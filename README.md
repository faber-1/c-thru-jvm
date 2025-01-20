# C-through JVM Bytecode parser

Hello! Welcome to my little parser project. I am implementing a parser for Java class files in C to process them into the different components of a class file. There's a chance I try to turn this to a full bytecode interpreter for JVM, but that's something I will decide later.

Running `make` will create a `bin` folder with a `parse_jvm` executable. You pass one class file to this and it will print out the class file details.

**This is not done yet. I have yet to cover all of the class file format and I've also yet to deal with memory leaks. Oops.**