"""
Integration tests combining calculator and string_utils modules.
This demonstrates integration testing with multiple modules working together.
"""

import pytest
from calculator import add, multiply, factorial, is_prime
from string_utils import (
    reverse_string, count_vowels, capitalize_words, is_palindrome
)


class TestCalculatorWithStringFormatting:
    """
    Integration Test Group 1: Calculator operations with string formatting.
    Tests the integration between mathematical calculations and string output.
    """
    
    def test_calculate_and_format_result(self):
        """Test calculating and formatting results as strings."""
        # Calculate result
        result = add(5, 3)
        # Format as string
        formatted = f"Result: {result}"
        assert formatted == "Result: 8"
        
        # Capitalize the result string
        capitalized = capitalize_words(formatted)
        assert capitalized == "Result: 8"
    
    def test_factorial_result_to_string_reverse(self):
        """Test converting factorial result to string and reversing it."""
        # Calculate factorial
        fact_result = factorial(5)
        assert fact_result == 120
        
        # Convert to string and reverse
        str_result = str(fact_result)
        reversed_str = reverse_string(str_result)
        assert reversed_str == "021"
    
    def test_prime_check_with_vowel_count(self):
        """Test prime checking and counting vowels in result description."""
        # Check if number is prime
        num = 7
        is_prime_result = is_prime(num)
        assert is_prime_result is True
        
        # Create description string
        description = f"The number {num} is prime"
        vowel_count = count_vowels(description)
        assert vowel_count == 6  # e, u, e, i, i, e
    
    def test_multiplication_table_palindrome_check(self):
        """Test creating multiplication results and checking if palindrome."""
        # Calculate multiplication
        result = multiply(11, 11)
        assert result == 121
        
        # Check if result as string is palindrome
        result_str = str(result)
        assert is_palindrome(result_str) is True
    
    def test_addition_chain_with_string_operations(self):
        """Test chaining additions and performing string operations on results."""
        # Chain additions
        step1 = add(10, 5)
        step2 = add(step1, 3)
        step3 = add(step2, 2)
        assert step3 == 20
        
        # Create formatted string and manipulate
        result_str = f"total equals {step3}"
        assert count_vowels(result_str) == 5  # o, a, e, u, a
        assert "20" in result_str


class TestStringUtilsWithCalculatorValidation:
    """
    Integration Test Group 2: String operations validated by calculator logic.
    Tests the integration where string operations are validated using math.
    """
    
    def test_word_count_matches_addition(self):
        """Test that word count can be validated with addition."""
        sentence = "hello world test"
        word_count = len(sentence.split())
        
        # Validate count using addition
        expected = add(add(1, 1), 1)  # 3 words
        assert word_count == expected
    
    def test_string_length_with_multiplication(self):
        """Test string length validation using multiplication."""
        text = "ab"
        repeated = text * 5  # "ababababab"
        
        # Calculate expected length
        expected_length = multiply(len(text), 5)
        assert len(repeated) == expected_length
    
    def test_vowel_consonant_sum(self):
        """Test that vowel and consonant counts sum correctly."""
        text = "hello"
        vowels = count_vowels(text)
        
        from string_utils import count_consonants
        consonants = count_consonants(text)
        
        # Total should match letter count
        total = add(vowels, consonants)
        assert total == len(text)
    
    def test_palindrome_length_check(self):
        """Test palindrome with even/odd length checking."""
        from calculator import is_even
        
        palindrome1 = "racecar"  # 7 chars (odd)
        assert is_palindrome(palindrome1) is True
        assert is_even(len(palindrome1)) is False
        
        palindrome2 = "noon"  # 4 chars (even)
        assert is_palindrome(palindrome2) is True
        assert is_even(len(palindrome2)) is True
    
    def test_anagram_length_equality(self):
        """Test that anagrams have equal lengths."""
        from string_utils import is_anagram
        
        str1 = "listen"
        str2 = "silent"
        
        # Verify they are anagrams
        assert is_anagram(str1, str2) is True
        
        # Verify lengths are equal using subtraction
        from calculator import subtract
        length_diff = subtract(len(str1), len(str2))
        assert length_diff == 0


class TestDataProcessingWorkflow:
    """
    Integration Test Group 3: Complete data processing workflow.
    Tests a realistic workflow combining both modules.
    """
    
    def test_statistical_text_analysis(self):
        """Test statistical analysis of text using both modules."""
        text = "The quick brown fox jumps over the lazy dog"
        
        # String analysis
        words = text.split()
        word_count = len(words)
        vowel_count = count_vowels(text)
        
        # Mathematical validation
        assert word_count == 9
        assert vowel_count > 0
        
        # Calculate average vowels per word (using division)
        from calculator import divide
        # We need at least some vowels
        assert vowel_count >= word_count * 0.2  # Rough estimate
    
    def test_numeric_string_processing(self):
        """Test processing numeric calculations as strings."""
        # Perform calculations
        nums = [factorial(3), factorial(4), factorial(5)]
        
        # Convert to strings and join
        str_nums = [str(n) for n in nums]
        joined = " ".join(str_nums)
        
        # Verify the result
        assert "6" in joined
        assert "24" in joined
        assert "120" in joined
        
        # Count words in result
        from string_utils import count_words
        assert count_words(joined) == 3
    
    def test_error_handling_integration(self):
        """Test that errors are properly handled across modules."""
        # Test calculator error
        with pytest.raises(ValueError):
            from calculator import divide
            divide(10, 0)
        
        # Test string_utils error
        with pytest.raises(TypeError):
            reverse_string(123)
        
        # Verify normal operation continues after error handling
        result = add(5, 5)
        assert result == 10
        reversed_hello = reverse_string("hello")
        assert reversed_hello == "olleh"
