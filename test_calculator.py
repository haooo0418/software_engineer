"""
Unit tests for calculator module.
This test suite aims for 80%+ code coverage with 10+ test cases.
"""

import pytest
from calculator import (
    add, subtract, multiply, divide, power, factorial,
    is_even, is_prime, gcd, lcm
)


class TestBasicOperations:
    """Test basic arithmetic operations."""
    
    def test_add_positive_numbers(self):
        """Test adding two positive numbers."""
        assert add(2, 3) == 5
        assert add(100, 200) == 300
    
    def test_add_negative_numbers(self):
        """Test adding negative numbers."""
        assert add(-5, -3) == -8
        assert add(-10, 5) == -5
    
    def test_add_zero(self):
        """Test adding zero."""
        assert add(0, 5) == 5
        assert add(5, 0) == 5
        assert add(0, 0) == 0
    
    def test_subtract_positive_numbers(self):
        """Test subtracting positive numbers."""
        assert subtract(10, 5) == 5
        assert subtract(100, 50) == 50
    
    def test_subtract_negative_numbers(self):
        """Test subtracting negative numbers."""
        assert subtract(-5, -3) == -2
        assert subtract(5, -3) == 8
    
    def test_multiply_positive_numbers(self):
        """Test multiplying positive numbers."""
        assert multiply(3, 4) == 12
        assert multiply(10, 10) == 100
    
    def test_multiply_by_zero(self):
        """Test multiplying by zero."""
        assert multiply(5, 0) == 0
        assert multiply(0, 5) == 0
    
    def test_multiply_negative_numbers(self):
        """Test multiplying negative numbers."""
        assert multiply(-3, 4) == -12
        assert multiply(-3, -4) == 12
    
    def test_divide_positive_numbers(self):
        """Test dividing positive numbers."""
        assert divide(10, 2) == 5
        assert divide(100, 4) == 25
    
    def test_divide_negative_numbers(self):
        """Test dividing negative numbers."""
        assert divide(-10, 2) == -5
        assert divide(-10, -2) == 5
    
    def test_divide_by_zero(self):
        """Test that dividing by zero raises ValueError."""
        with pytest.raises(ValueError, match="Cannot divide by zero"):
            divide(10, 0)
    
    def test_divide_zero_by_number(self):
        """Test dividing zero by a number."""
        assert divide(0, 5) == 0


class TestPowerFunction:
    """Test power function."""
    
    def test_power_positive_exponent(self):
        """Test power with positive exponent."""
        assert power(2, 3) == 8
        assert power(5, 2) == 25
    
    def test_power_zero_exponent(self):
        """Test power with zero exponent."""
        assert power(5, 0) == 1
        assert power(100, 0) == 1
    
    def test_power_negative_exponent(self):
        """Test power with negative exponent."""
        assert power(2, -1) == 0.5
        assert power(10, -2) == 0.01
    
    def test_power_zero_base(self):
        """Test power with zero base."""
        assert power(0, 5) == 0
        assert power(0, 0) == 1
    
    def test_power_zero_to_negative(self):
        """Test that zero to negative power raises ValueError."""
        with pytest.raises(ValueError, match="Cannot raise zero to a negative power"):
            power(0, -1)


class TestFactorial:
    """Test factorial function."""
    
    def test_factorial_zero(self):
        """Test factorial of 0."""
        assert factorial(0) == 1
    
    def test_factorial_one(self):
        """Test factorial of 1."""
        assert factorial(1) == 1
    
    def test_factorial_positive_numbers(self):
        """Test factorial of positive numbers."""
        assert factorial(5) == 120
        assert factorial(6) == 720
        assert factorial(3) == 6
    
    def test_factorial_negative_number(self):
        """Test that factorial of negative number raises ValueError."""
        with pytest.raises(ValueError, match="Factorial not defined for negative numbers"):
            factorial(-5)
    
    def test_factorial_non_integer(self):
        """Test that factorial of non-integer raises TypeError."""
        with pytest.raises(TypeError, match="Factorial requires an integer"):
            factorial(3.5)


class TestEvenCheck:
    """Test is_even function."""
    
    def test_is_even_positive_even(self):
        """Test even positive numbers."""
        assert is_even(2) is True
        assert is_even(10) is True
        assert is_even(100) is True
    
    def test_is_even_positive_odd(self):
        """Test odd positive numbers."""
        assert is_even(3) is False
        assert is_even(11) is False
        assert is_even(99) is False
    
    def test_is_even_zero(self):
        """Test that zero is even."""
        assert is_even(0) is True
    
    def test_is_even_negative(self):
        """Test negative numbers."""
        assert is_even(-2) is True
        assert is_even(-3) is False


class TestPrimeCheck:
    """Test is_prime function."""
    
    def test_is_prime_small_primes(self):
        """Test small prime numbers."""
        assert is_prime(2) is True
        assert is_prime(3) is True
        assert is_prime(5) is True
        assert is_prime(7) is True
    
    def test_is_prime_composite_numbers(self):
        """Test composite numbers."""
        assert is_prime(4) is False
        assert is_prime(6) is False
        assert is_prime(9) is False
        assert is_prime(10) is False
    
    def test_is_prime_edge_cases(self):
        """Test edge cases."""
        assert is_prime(0) is False
        assert is_prime(1) is False
        assert is_prime(-5) is False
    
    def test_is_prime_larger_primes(self):
        """Test larger prime numbers."""
        assert is_prime(17) is True
        assert is_prime(23) is True


class TestGCDAndLCM:
    """Test GCD and LCM functions."""
    
    def test_gcd_positive_numbers(self):
        """Test GCD with positive numbers."""
        assert gcd(12, 8) == 4
        assert gcd(15, 25) == 5
        assert gcd(7, 13) == 1
    
    def test_gcd_with_zero(self):
        """Test GCD with zero."""
        assert gcd(0, 5) == 5
        assert gcd(5, 0) == 5
    
    def test_gcd_negative_numbers(self):
        """Test GCD with negative numbers."""
        assert gcd(-12, 8) == 4
        assert gcd(12, -8) == 4
    
    def test_lcm_positive_numbers(self):
        """Test LCM with positive numbers."""
        assert lcm(4, 6) == 12
        assert lcm(3, 5) == 15
    
    def test_lcm_with_zero(self):
        """Test LCM with zero."""
        assert lcm(0, 5) == 0
        assert lcm(5, 0) == 0
    
    def test_lcm_same_numbers(self):
        """Test LCM with same numbers."""
        assert lcm(5, 5) == 5
