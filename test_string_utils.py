"""
Unit tests for string_utils module.
This test suite aims for 80%+ code coverage with 10+ test cases.
"""

import pytest
from string_utils import (
    reverse_string, is_palindrome, count_vowels, count_consonants,
    capitalize_words, remove_whitespace, is_anagram, count_words,
    truncate_string, find_substring_count
)


class TestReverseString:
    """Test reverse_string function."""
    
    def test_reverse_simple_string(self):
        """Test reversing simple strings."""
        assert reverse_string("hello") == "olleh"
        assert reverse_string("world") == "dlrow"
    
    def test_reverse_empty_string(self):
        """Test reversing empty string."""
        assert reverse_string("") == ""
    
    def test_reverse_single_char(self):
        """Test reversing single character."""
        assert reverse_string("a") == "a"
    
    def test_reverse_with_spaces(self):
        """Test reversing string with spaces."""
        assert reverse_string("hello world") == "dlrow olleh"
    
    def test_reverse_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Input must be a string"):
            reverse_string(123)


class TestPalindrome:
    """Test is_palindrome function."""
    
    def test_palindrome_simple(self):
        """Test simple palindromes."""
        assert is_palindrome("racecar") is True
        assert is_palindrome("level") is True
        assert is_palindrome("noon") is True
    
    def test_palindrome_with_spaces(self):
        """Test palindromes with spaces."""
        assert is_palindrome("race car") is True
        assert is_palindrome("A man a plan a canal Panama") is True
    
    def test_not_palindrome(self):
        """Test non-palindromes."""
        assert is_palindrome("hello") is False
        assert is_palindrome("world") is False
    
    def test_palindrome_case_insensitive(self):
        """Test case insensitivity."""
        assert is_palindrome("Racecar") is True
        assert is_palindrome("RaceCar") is True
    
    def test_palindrome_empty_string(self):
        """Test empty string is palindrome."""
        assert is_palindrome("") is True
    
    def test_palindrome_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Input must be a string"):
            is_palindrome(12321)


class TestVowelCount:
    """Test count_vowels function."""
    
    def test_count_vowels_simple(self):
        """Test counting vowels in simple strings."""
        assert count_vowels("hello") == 2
        assert count_vowels("world") == 1
        assert count_vowels("aeiou") == 5
    
    def test_count_vowels_uppercase(self):
        """Test counting uppercase vowels."""
        assert count_vowels("HELLO") == 2
        assert count_vowels("AEIOUaeiou") == 10
    
    def test_count_vowels_no_vowels(self):
        """Test string with no vowels."""
        assert count_vowels("xyz") == 0
    
    def test_count_vowels_empty_string(self):
        """Test empty string."""
        assert count_vowels("") == 0
    
    def test_count_vowels_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Input must be a string"):
            count_vowels(123)


class TestConsonantCount:
    """Test count_consonants function."""
    
    def test_count_consonants_simple(self):
        """Test counting consonants in simple strings."""
        assert count_consonants("hello") == 3
        assert count_consonants("world") == 4
    
    def test_count_consonants_no_consonants(self):
        """Test string with no consonants."""
        assert count_consonants("aeiou") == 0
    
    def test_count_consonants_with_numbers(self):
        """Test string with numbers and special chars."""
        assert count_consonants("hello123") == 3
    
    def test_count_consonants_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Input must be a string"):
            count_consonants(123)


class TestCapitalizeWords:
    """Test capitalize_words function."""
    
    def test_capitalize_simple(self):
        """Test capitalizing simple strings."""
        assert capitalize_words("hello world") == "Hello World"
        assert capitalize_words("python programming") == "Python Programming"
    
    def test_capitalize_already_capitalized(self):
        """Test already capitalized string."""
        assert capitalize_words("Hello World") == "Hello World"
    
    def test_capitalize_all_lowercase(self):
        """Test all lowercase."""
        assert capitalize_words("test") == "Test"
    
    def test_capitalize_empty_string(self):
        """Test empty string."""
        assert capitalize_words("") == ""
    
    def test_capitalize_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Input must be a string"):
            capitalize_words(123)


class TestRemoveWhitespace:
    """Test remove_whitespace function."""
    
    def test_remove_whitespace_simple(self):
        """Test removing whitespace from simple strings."""
        assert remove_whitespace("hello world") == "helloworld"
        assert remove_whitespace("a b c d") == "abcd"
    
    def test_remove_whitespace_tabs_newlines(self):
        """Test removing tabs and newlines."""
        assert remove_whitespace("hello\tworld") == "helloworld"
        assert remove_whitespace("hello\nworld") == "helloworld"
    
    def test_remove_whitespace_no_spaces(self):
        """Test string without spaces."""
        assert remove_whitespace("hello") == "hello"
    
    def test_remove_whitespace_empty_string(self):
        """Test empty string."""
        assert remove_whitespace("") == ""
    
    def test_remove_whitespace_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Input must be a string"):
            remove_whitespace(123)


class TestAnagram:
    """Test is_anagram function."""
    
    def test_anagram_simple(self):
        """Test simple anagrams."""
        assert is_anagram("listen", "silent") is True
        assert is_anagram("evil", "vile") is True
    
    def test_anagram_with_spaces(self):
        """Test anagrams with spaces."""
        assert is_anagram("conversation", "voices rant on") is True
    
    def test_not_anagram(self):
        """Test non-anagrams."""
        assert is_anagram("hello", "world") is False
    
    def test_anagram_case_insensitive(self):
        """Test case insensitivity."""
        assert is_anagram("Listen", "Silent") is True
    
    def test_anagram_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Both inputs must be strings"):
            is_anagram("test", 123)


class TestCountWords:
    """Test count_words function."""
    
    def test_count_words_simple(self):
        """Test counting words in simple strings."""
        assert count_words("hello world") == 2
        assert count_words("one two three four") == 4
    
    def test_count_words_single_word(self):
        """Test single word."""
        assert count_words("hello") == 1
    
    def test_count_words_empty_string(self):
        """Test empty string."""
        assert count_words("") == 0
        assert count_words("   ") == 0
    
    def test_count_words_multiple_spaces(self):
        """Test multiple spaces between words."""
        assert count_words("hello    world") == 2
    
    def test_count_words_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Input must be a string"):
            count_words(123)


class TestTruncateString:
    """Test truncate_string function."""
    
    def test_truncate_long_string(self):
        """Test truncating long strings."""
        assert truncate_string("hello world", 5) == "hello..."
        assert truncate_string("testing truncate", 7) == "testing..."
    
    def test_truncate_short_string(self):
        """Test string shorter than max_length."""
        assert truncate_string("hi", 10) == "hi"
    
    def test_truncate_custom_suffix(self):
        """Test custom suffix."""
        assert truncate_string("hello world", 5, "!!!") == "hello!!!"
    
    def test_truncate_zero_length(self):
        """Test zero max length."""
        assert truncate_string("hello", 0) == "..."
    
    def test_truncate_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Input must be a string"):
            truncate_string(123, 5)
    
    def test_truncate_non_integer_length(self):
        """Test that non-integer max_length raises TypeError."""
        with pytest.raises(TypeError, match="max_length must be an integer"):
            truncate_string("hello", "5")
    
    def test_truncate_negative_length(self):
        """Test that negative max_length raises ValueError."""
        with pytest.raises(ValueError, match="max_length must be non-negative"):
            truncate_string("hello", -5)


class TestFindSubstringCount:
    """Test find_substring_count function."""
    
    def test_find_substring_simple(self):
        """Test finding substring in simple strings."""
        assert find_substring_count("hello hello", "hello") == 2
        assert find_substring_count("test test test", "test") == 3
    
    def test_find_substring_not_found(self):
        """Test substring not found."""
        assert find_substring_count("hello world", "xyz") == 0
    
    def test_find_substring_empty_substring(self):
        """Test empty substring."""
        assert find_substring_count("hello", "") == 0
    
    def test_find_substring_case_sensitive(self):
        """Test case sensitivity."""
        assert find_substring_count("Hello hello", "hello") == 1
    
    def test_find_substring_non_string(self):
        """Test that non-string input raises TypeError."""
        with pytest.raises(TypeError, match="Both inputs must be strings"):
            find_substring_count(123, "test")
