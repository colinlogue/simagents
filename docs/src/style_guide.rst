###################
Documentation Guide
###################
This guide is to lay out the goals, structure, and style conventions for
documentation of the simagents project.

*******
Project
*******

Objective
=========
This project aims to create a framework for running agent-based simulations.

Structure
=========
1. Models
2. 

*************
Documentation
*************

Project
=======
1. Objective
2. Structure

Models
======
1. 

Functions
=========
Functions should be documented in the source file where they are declared,
using the following format:

.. code:c::
  int get_foo(char *bar) {
  /**
    * A brief description of the function.
    *
    * More information can follow on further lines.
    *
    * Arguments
    * ---------
    * bar : *char
    *     Each argument should be described in this section.
    *
    * Returns
    * -------
    * foo : int
    *     A description of the value returned by the function.
  **/

    // function does some stuff here
    return foo;
  }

This mostly follows the documentation guide for numpy, found at: https://docs.scipy.org/doc/numpy/docs/howto_document.html#numpydoc-docstring-guide