# c-python-template
Notes on integrating C and Python code

## Installation

```
python3 -m venv venv
```

Activate using your preferred shell (e.g. fish)
```
source venv/bin/activate.fish
```

Install `gcc`
* On Ubunutu one can install `gcc` via `apt install gcc`

`Make` is also required to follow the usage section. Many systems include `make` as part of the OS; however, if yours does not, many C build packages include it. Try using your package manager to find one that does. 

## Usage

This repo is intended to be used as notes for integrating C code with Python code. The example highlights how to pass objects/structs between C and Python use them with C functions.  

## Tutorial

### Short Version: Run `make all` and experiment at your leisure.

### Longer Version:

The C code, `mynum.c` and `mynum.h`, contain a simple struct with an int and string (char *) and some accompanying functions. 

First one must compile the C code into a library that we can load into our Python module. To do this, use the `Makefile`. Run the command `make mynum.so` to compile the library. 

Once this is done, one can then load the library using the `ctypes` Python library (included in base Python):
```py
import ctypes
from pathlib import Path

libname = Path.cwd() / 'libmynum.so'
LIBC = ctypes.CDLL(libname)
```

At this point, the functions are available to be called through the `LIBC` object. For example, if one wants to call the `my_add()` function, one can use the following:
```py
LIBC.my_add(num_one, num_two)
```

It is important to remember that C requires function arguments to be of the correct type in order to function. In Python, one can use the `ctypes` library's type definitions to cast Python variables to their appropriate C type. 

For example:
```py
num_one = 1
num_two = 2
num_one = ctypes.c_int(num_one)
num_two = ctypes.c_int(num_two)
result = libc.my_add(num_one, num_two)
```

One of the very useful aspects of using Python and C together is the ability to allocate C structs in either C or Python and use them in C functions. An example of this is included below. Note, there are many more complex ways of doing this where one can wrap the C library in Python, but these are well documented in other tutorials and outside the scope of this repo.
```py
class Mynum(ctypes.Structure):
    _fields_ = [('num', ctypes.c_int),
                ('desc',  ctypes.POINTER(ctypes.c_char))]

result = 15
# Building a struct in both C and Python to showcase shared memory spaces
result = ctypes.c_int(result)
text = "Best Num"
text = ctypes.create_string_buffer(str.encode(text))
# Calling C to make/allocate struct
c_mynum = LIBC.get_mynum(result, text)
# Using Python to make/allocate struct
p_mynum = Mynum(num=result, desc=text)
# Calling C directly with both structs, output should match 
print("Accessing memory allocated in C:")
LIBC.print_mynum_pointer(c_mynum)
print("Accessing memory allocated in Python:")
LIBC.print_mynum(p_mynum)
# Remember to free() as C does not garbage collect for you
LIBC.free_mynum(c_mynum)

```
