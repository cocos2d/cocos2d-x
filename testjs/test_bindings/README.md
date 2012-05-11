# How to create my own bindings

While the `generate_bindings.rb` ruby script is mainly used to create the cocos2d-x bindings, the idea
is that it can be used to wrap more C++ classes needed by your game.

This document will try to explain how to use this script and what tools you need in order to make it
work.

Please note that this script is a preliminary effort and it won't work in all cases. Here's what is
**not** working:

* `std::string` - plain c strings works ok though (`char *`). We're working to add support for this
  but a workaround would be to either switch to c strings (not really an option for many of us) or
  create a simple wrapper function that will receive c strings.
* namespaces - It's not that they're not working, but if you're wrapping a class `C` that lives in `A::B::C`
  the scripting interface generated will inherit from `C` and you would have to manually set the namespace
  of the parent class to `A::B`.
* variable number of arguments - This is not working yet

## Required tools

* clang 2.8 - You can get it from the (download section)[http://llvm.org/releases/download.html] of clang. Please
  note that it **has** to be version 2.8 and not a newer version. Newer versions have the xml output for the AST
  broken.
* ruby 1.9 and nokogiri gem
    * You can download ruby from http://www.ruby-lang.org
    * After you have ruby installed, you can install nokogiri: `sudo gem install nokogiri`
    * Alternatively you can use (rvm)[https://rvm.io/]

## Making it work

The first thing you need to create, is the (AST)[http://en.wikipedia.org/wiki/Abstract_syntax_tree] for your class.
Since you're using clang, you can safely point the script to your main header, for instance, for cocos2d-x we
point the script to the `cocos2d.h` header file. Take into account though, that files should be reachable or you
should modify the header search paths (`-I` in the script).

    ./generate_ast_xml.sh test_bindings/simple_class.h

That will create the XML for the AST in the current working directory, in this case `simple_class.xml`. Now you need
to pass this to the ruby script that will parse the tree and then generate the proper bindings:

    CXX_CLASSES=SimpleNativeClass ruby generate_bindings.rb simple_class.xml simple_native_generated

What this is doing, is specifying what classes are going to be binded (`CXX_CLASSES` is a colon separated string, and
is being passed as a environmental variable to the script), the two arguments for the script specify the XML file and
what is the name of the generated output. If no second argument is passed, it will generate `out.cpp` and `out.hpp`.

Once you run this, it should generate the files `simple_native_generated.cpp` and `simple_native_generated.hpp`. You
can then include those files in your project.

Please note that if the class you're binding is namespaced, then the scripting class (`S_SimpleNativeClass` in this
example) is not inheriting from the right class, so you should add the proper namespace. That should be the only
thing you would need to do in order to compile that file.

## What is doing internally

Explain here how it's wrapping the classes