"""
A multi-line docstring at the top of the file
"""
import math

class MyClass:
    # This is a class-level comment
    def __init__(self, name):
        """Constructor docstring"""
        self.name = name

    def greet(self):
        # Greet method
        print(f"Hello, {self.name}!")

def myFunction(x, y=10):
    """
    A function docstring
    """
    # do something
    total = x + y
    if total > 100:
        return True
    else:
        return "Result is {}".format(total)
