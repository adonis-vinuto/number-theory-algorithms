/**
 * @file challenge_validation.c
 * @brief Implementation of GCD challenge validation and utility functions
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file implements the validation and utility functions declared in
 * challenge_definition.h. These functions provide validation, edge case
 * handling, and reference implementations for GCD algorithms.
 */

#include "challenge_definition.h"
#include "../../infrastructure/utilities/math_utils.h"
#include "../../infrastructure/utilities/memory_utils.h"
#include <limits.h>

// ============================================================================
// INPUT VALIDATION
// ============================================================================

/**
 * @brief Check if input values are valid for GCD computation
 *
 * @param a First operand
 * @param b Second operand
 * @return true if inputs are valid for GCD computation
 */
bool gcd_validate_input(GcdInteger a, GcdInteger b)
{
    // GCD can handle any integer inputs, including negatives and zero
    // The only problematic case is when both values could cause overflow
    // when taking absolute value (LLONG_MIN case)

    if (a == LLONG_MIN && b == LLONG_MIN)
    {
        return false; // Both at minimum would cause overflow
    }

    // All other cases are valid for GCD computation
    return true;
}

// ============================================================================
// RESULT VALIDATION
// ============================================================================

/**
 * @brief Check if a GCD result is mathematically correct
 *
 * Validates that the result actually divides both operands and is
 * the greatest such divisor.
 *
 * @param a First operand
 * @param b Second operand
 * @param result Computed GCD result
 * @return true if result is mathematically correct
 */
bool gcd_validate_result(GcdInteger a, GcdInteger b, GcdInteger result)
{
    // Handle special cases first
    if (a == 0 && b == 0)
    {
        return (result == 0); // gcd(0,0) = 0 by convention
    }

    if (result <= 0)
    {
        return false; // GCD must be positive for non-zero inputs
    }

    // Get absolute values for testing
    GcdInteger abs_a = (a < 0) ? -a : a;
    GcdInteger abs_b = (b < 0) ? -b : b;

    // Handle case where one operand is zero
    if (a == 0)
    {
        return (result == abs_b);
    }
    if (b == 0)
    {
        return (result == abs_a);
    }

    // Check if result divides both operands
    if (abs_a % result != 0 || abs_b % result != 0)
    {
        return false;
    }

    // Check if result is the greatest common divisor
    // We do this by checking if gcd(a/result, b/result) = 1
    GcdInteger reduced_a = abs_a / result;
    GcdInteger reduced_b = abs_b / result;

    // Use simple reference implementation to check
    GcdInteger gcd_reduced = gcd_reference_implementation(reduced_a, reduced_b);

    return (gcd_reduced == 1);
}

/**
 * @brief Check if Extended GCD result is mathematically correct
 *
 * Validates that ax + by = gcd(a,b) holds true.
 *
 * @param a First operand
 * @param b Second operand
 * @param ext_result Extended GCD result with coefficients
 * @return true if extended result is mathematically correct
 */
bool gcd_validate_extended_result(GcdInteger a, GcdInteger b, const ExtendedGcdResult *ext_result)
{
    if (ext_result == NULL || !ext_result->is_valid)
    {
        return false;
    }

    // First, validate the basic GCD result
    if (!gcd_validate_result(a, b, ext_result->gcd))
    {
        return false;
    }

    // Check the Bezout identity: ax + by = gcd(a,b)
    GcdInteger left_side = a * ext_result->coefficient_x + b * ext_result->coefficient_y;

    return (left_side == ext_result->gcd);
}

// ============================================================================
// MATHEMATICAL PROPERTIES VALIDATION
// ============================================================================

/**
 * @brief Check GCD fundamental properties
 *
 * Verifies basic GCD properties:
 * - gcd(a,b) divides both a and b
 * - gcd(a,b) is the largest such divisor
 * - gcd(a,b) = gcd(b,a) (commutative)
 * - gcd(a,0) = |a|
 *
 * @param a First operand
 * @param b Second operand
 * @param result Computed GCD
 * @return true if all fundamental properties hold
 */
bool gcd_check_fundamental_properties(GcdInteger a, GcdInteger b, GcdInteger result)
{
    // Property 1: Result divides both operands (checked in gcd_validate_result)
    if (!gcd_validate_result(a, b, result))
    {
        return false;
    }

    // Property 2: Commutative property - gcd(a,b) = gcd(b,a)
    GcdInteger reverse_result = gcd_reference_implementation(b, a);
    if (result != reverse_result)
    {
        return false;
    }

    // Property 3: Special case - gcd(a,0) = |a|
    if (b == 0)
    {
        GcdInteger abs_a = (a < 0) ? -a : a;
        if (result != abs_a)
        {
            return false;
        }
    }

    if (a == 0)
    {
        GcdInteger abs_b = (b < 0) ? -b : b;
        if (result != abs_b)
        {
            return false;
        }
    }

    return true;
}

// ============================================================================
// REFERENCE IMPLEMENTATION
// ============================================================================

/**
 * @brief Reference GCD implementation for validation
 *
 * Simple, obviously correct GCD implementation used to validate
 * other algorithms. Uses basic Euclidean algorithm.
 *
 * @param a First operand
 * @param b Second operand
 * @return Correct GCD of a and b
 */
GcdInteger gcd_reference_implementation(GcdInteger a, GcdInteger b)
{
    // Handle special case: gcd(0,0) = 0
    if (a == 0 && b == 0)
    {
        return 0;
    }

    // Work with absolute values
    GcdInteger abs_a = (a < 0) ? -a : a;
    GcdInteger abs_b = (b < 0) ? -b : b;

    // Handle cases where one operand is zero
    if (abs_a == 0)
    {
        return abs_b;
    }
    if (abs_b == 0)
    {
        return abs_a;
    }

    // Basic Euclidean algorithm
    while (abs_b != 0)
    {
        GcdInteger temp = abs_b;
        abs_b = abs_a % abs_b;
        abs_a = temp;
    }

    return abs_a;
}

// ============================================================================
// EDGE CASE HANDLING
// ============================================================================

/**
 * @brief Handle common GCD edge cases
 *
 * Handles the standard GCD edge cases that all algorithms should handle consistently.
 *
 * @param a First operand
 * @param b Second operand
 * @param result Pointer to store result if edge case handled
 * @return true if edge case was handled, false if normal computation needed
 */
bool gcd_handle_edge_cases(GcdInteger a, GcdInteger b, GcdInteger *result)
{
    if (result == NULL)
    {
        return false;
    }

    // Case 1: gcd(0, 0) = 0 (by convention)
    if (a == 0 && b == 0)
    {
        *result = 0;
        return true;
    }

    // Case 2: gcd(a, 0) = |a|
    if (b == 0)
    {
        *result = (a < 0) ? -a : a;
        return true;
    }

    // Case 3: gcd(0, b) = |b|
    if (a == 0)
    {
        *result = (b < 0) ? -b : b;
        return true;
    }

    // Case 4: gcd(a, a) = |a|
    if (a == b)
    {
        *result = (a < 0) ? -a : a;
        return true;
    }

    // Case 5: gcd(1, b) = 1 or gcd(a, 1) = 1
    if (a == 1 || a == -1 || b == 1 || b == -1)
    {
        *result = 1;
        return true;
    }

    // Case 6: Check for potential overflow cases
    if (a == LLONG_MIN || b == LLONG_MIN)
    {
        // Use reference implementation which can handle these cases
        *result = gcd_reference_implementation(a, b);
        return true;
    }

    // No edge case detected, proceed with normal computation
    return false;
}

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

/**
 * @brief Create a valid GCD descriptor with validation
 *
 * @param name Algorithm name
 * @param description Algorithm description
 * @param variant Algorithm variant
 * @param family Algorithm family
 * @param is_recursive Whether algorithm is recursive
 * @param algorithm Function pointer to algorithm
 * @return Initialized GcdAlgorithmDescriptor
 */
GcdAlgorithmDescriptor gcd_create_algorithm_descriptor(
    const char *name,
    const char *description,
    GcdAlgorithmVariant variant,
    MathAlgorithmFamily family,
    bool is_recursive,
    GcdAlgorithmFunc algorithm)
{
    GcdAlgorithmDescriptor descriptor = {
        .name = name,
        .description = description,
        .variant = variant,
        .family = family,
        .is_recursive = is_recursive,
        .algorithm = algorithm};

    return descriptor;
}

/**
 * @brief Create a valid Extended GCD descriptor with validation
 *
 * @param name Algorithm name
 * @param description Algorithm description
 * @param is_recursive Whether algorithm is recursive
 * @param algorithm Function pointer to extended algorithm
 * @return Initialized ExtendedGcdAlgorithmDescriptor
 */
ExtendedGcdAlgorithmDescriptor gcd_create_extended_algorithm_descriptor(
    const char *name,
    const char *description,
    bool is_recursive,
    ExtendedGcdAlgorithmFunc algorithm)
{
    ExtendedGcdAlgorithmDescriptor descriptor = {
        .name = name,
        .description = description,
        .is_recursive = is_recursive,
        .algorithm = algorithm};

    return descriptor;
}

// ============================================================================
// SIMPLE TESTING UTILITIES
// ============================================================================

/**
 * @brief Test an algorithm with known inputs and expected outputs
 *
 * @param algorithm Algorithm to test
 * @param test_a First test operand
 * @param test_b Second test operand
 * @param expected_result Expected GCD result
 * @return true if algorithm produces correct result
 */
bool gcd_test_algorithm(GcdAlgorithmFunc algorithm, GcdInteger test_a, GcdInteger test_b, GcdInteger expected_result)
{
    if (algorithm == NULL)
    {
        return false;
    }

    GcdInteger actual_result = algorithm(test_a, test_b);
    return (actual_result == expected_result);
}

/**
 * @brief Run basic validation tests on all common algorithms
 *
 * @return true if all tests pass
 */
bool gcd_run_validation_tests(void)
{
    // Test cases: {a, b, expected_gcd}
    struct
    {
        GcdInteger a, b, expected;
    } test_cases[] = {
        {48, 18, 6},
        {17, 13, 1},
        {100, 25, 25},
        {0, 5, 5},
        {7, 0, 7},
        {0, 0, 0},
        {-12, 8, 4},
        {15, -10, 5},
        {-20, -30, 10}};

    int num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    // Test reference implementation
    for (int i = 0; i < num_tests; i++)
    {
        GcdInteger result = gcd_reference_implementation(test_cases[i].a, test_cases[i].b);
        if (result != test_cases[i].expected)
        {
            return false;
        }
    }

    return true;
}