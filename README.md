# nox-cpp

Safe algebraic datatypes for C++ without exceptions.

## Motivation

Many coding environments eschew exceptions,
but the standard library relies on them extensively.
This is an experiment to implement algebraic datatypes without exceptions.
The primary objective is for me to learn how to implement interesting types.
Also,
I want to experiment with different,
possibly safer interfaces than the types provided by the standard library.

## Roadmap

- optional
- variant

## Random Musings

This is a great article describing how tuples are implemented by variadic templates:
https://eli.thegreenplace.net/2014/variadic-templates-in-c/.
