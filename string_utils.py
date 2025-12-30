"""
String utilities module with various string manipulation functions.
This module is designed to demonstrate unit testing and coverage analysis.
"""

def reverse_string(s):
    """Reverse a string."""
    if not isinstance(s, str):
        raise TypeError("Input must be a string")
    return s[::-1]

def is_palindrome(s):
    """
    Check if a string is a palindrome (case-insensitive, ignoring spaces).
    """
    if not isinstance(s, str):
        raise TypeError("Input must be a string")
    # Remove spaces and convert to lowercase
    cleaned = s.replace(" ", "").lower()
    return cleaned == cleaned[::-1]

def count_vowels(s):
    """
    Count the number of vowels in a string.
    """
    if not isinstance(s, str):
        raise TypeError("Input must be a string")
    vowels = "aeiouAEIOU"
    return sum(1 for char in s if char in vowels)

def count_consonants(s):
    """
    Count the number of consonants in a string.
    """
    if not isinstance(s, str):
        raise TypeError("Input must be a string")
    consonants = "bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ"
    return sum(1 for char in s if char in consonants)

def capitalize_words(s):
    """
    Capitalize the first letter of each word in a string.
    """
    if not isinstance(s, str):
        raise TypeError("Input must be a string")
    return ' '.join(word.capitalize() for word in s.split())

def remove_whitespace(s):
    """
    Remove all whitespace from a string.
    """
    if not isinstance(s, str):
        raise TypeError("Input must be a string")
    return ''.join(s.split())

def is_anagram(s1, s2):
    """
    Check if two strings are anagrams (case-insensitive).
    """
    if not isinstance(s1, str) or not isinstance(s2, str):
        raise TypeError("Both inputs must be strings")
    # Remove spaces and convert to lowercase
    cleaned_s1 = s1.replace(" ", "").lower()
    cleaned_s2 = s2.replace(" ", "").lower()
    return sorted(cleaned_s1) == sorted(cleaned_s2)

def count_words(s):
    """
    Count the number of words in a string.
    """
    if not isinstance(s, str):
        raise TypeError("Input must be a string")
    if not s.strip():
        return 0
    return len(s.split())

def truncate_string(s, max_length, suffix="..."):
    """
    Truncate a string to a maximum length and add a suffix.
    """
    if not isinstance(s, str):
        raise TypeError("Input must be a string")
    if not isinstance(max_length, int):
        raise TypeError("max_length must be an integer")
    if max_length < 0:
        raise ValueError("max_length must be non-negative")
    
    if len(s) <= max_length:
        return s
    return s[:max_length] + suffix

def find_substring_count(text, substring):
    """
    Count the number of non-overlapping occurrences of substring in text.
    """
    if not isinstance(text, str) or not isinstance(substring, str):
        raise TypeError("Both inputs must be strings")
    if not substring:
        return 0
    return text.count(substring)
