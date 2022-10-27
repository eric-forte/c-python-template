import ctypes
from pathlib import Path

class Mynum(ctypes.Structure):
    _fields_ = [('num', ctypes.c_int),
                ('desc',  ctypes.POINTER(ctypes.c_char))]

''' Wrap a c function call in a python function call'''
def call_c_add(libc, num_one: int, num_two: int):
    num_one = ctypes.c_int(num_one)
    num_two = ctypes.c_int(num_two)
    result = libc.my_add(num_one, num_two)
    return result


if __name__ == "__main__":
    x = 5
    y = 7
    # Load the shared library into c types
    libname = Path.cwd() / 'libmynum.so'
    LIBC = ctypes.CDLL(libname)
    # Calling C from python
    result = call_c_add(LIBC, x, y)
    print(f"The result of adding {x} and {y} via C is: {result}\n")
    
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
