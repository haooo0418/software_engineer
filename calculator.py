"""
Calculator module with various mathematical operations.
This module is designed to demonstrate unit testing and coverage analysis.
"""

def add(a, b):
    """Add two numbers."""
    return a + b

def subtract(a, b):
    """Subtract b from a."""
    return a - b

def multiply(a, b):
    """Multiply two numbers."""
    return a * b

def divide(a, b):
    """
    Divide a by b.
    Raises ValueError if b is zero.
    """
    if b == 0:
        raise ValueError("Cannot divide by zero")
    return a / b

def power(base, exponent):
    """
    Calculate base raised to the power of exponent.
    Handles edge cases for negative exponents and zero base.
    """
    if base == 0 and exponent < 0:
        raise ValueError("Cannot raise zero to a negative power")
    return base ** exponent

def factorial(n):
    """
    Calculate factorial of n.
    Raises ValueError for negative numbers.
    """
    if not isinstance(n, int):
        raise TypeError("Factorial requires an integer")
    if n < 0:
        raise ValueError("Factorial not defined for negative numbers")
    if n == 0 or n == 1:
        return 1
    result = 1
    for i in range(2, n + 1):
        result *= i
    return result

def is_even(n):
    """Check if a number is even."""
    return n % 2 == 0

def is_prime(n):
    """
    Check if a number is prime.
    Returns False for numbers less than 2.
    """
    if n < 2:
        return False
    if n == 2:
        return True
    if n % 2 == 0:
        return False
    for i in range(3, int(n ** 0.5) + 1, 2):
        if n % i == 0:
            return False
    return True

def gcd(a, b):
    """
    Calculate the greatest common divisor using Euclidean algorithm.
    Handles negative numbers.
    """
    a, b = abs(a), abs(b)
    while b:
        a, b = b, a % b
    return a

def lcm(a, b):
    """
    Calculate the least common multiple.
    Returns 0 if either number is 0.
    """
    if a == 0 or b == 0:
        return 0
    return abs(a * b) // gcd(a, b)
