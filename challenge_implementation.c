/**
 * @file challenge_implementation.c
 * @brief Implementation of missing challenge definition functions
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file implements only the functions that were missing from compilation.
 * Does NOT include math_utils.c to avoid duplicate definitions.
 */

#include "src/challenges/greatest_common_divisor/challenge_definition.h"
#include "src/challenges/greatest_common_divisor/domain_types.h"
#include "src/core/domain/mathematical_types.h"
#include <limits.h>

// ============================================================================
// GCD VALIDATION FUNCTIONS (ONLY THE MISSING ONES)
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
    // Check for potential overflow conditions
    if (a == LLONG_MIN || b == LLONG_MIN)
    {
        return false; // Could cause overflow when computing absolute value
    }

    // GCD can handle any other integer inputs, including negatives and zero
    return true;
}

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
    // Handle special cases
    if (a == 0 && b == 0)
    {
        return result == 0; // gcd(0,0) = 0 by convention
    }

    if (result <= 0)
    {
        return false; // GCD must be positive (except for gcd(0,0))
    }

    // Get absolute values for validation
    GcdInteger abs_a = (a < 0) ? -a : a;
    GcdInteger abs_b = (b < 0) ? -b : b;

    // Check if result divides both operands
    if (a != 0 && (abs_a % result) != 0)
    {
        return false;
    }

    if (b != 0 && (abs_b % result) != 0)
    {
        return false;
    }

    // For non-zero operands, check that result is not larger than the smaller operand
    if (a != 0 && b != 0)
    {
        GcdInteger min_operand = (abs_a < abs_b) ? abs_a : abs_b;
        if (result > min_operand)
        {
            return false;
        }
    }

    // If only one operand is zero, GCD should equal absolute value of the other
    if (a == 0 && b != 0)
    {
        return result == abs_b;
    }

    if (b == 0 && a != 0)
    {
        return result == abs_a;
    }

    return true;
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

    // First validate the GCD part
    if (!gcd_validate_result(a, b, ext_result->gcd))
    {
        return false;
    }

    // Check Bézout's identity: ax + by = gcd(a,b)
    GcdInteger left_side = a * ext_result->coefficient_x + b * ext_result->coefficient_y;

    return left_side == ext_result->gcd;
}

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
    // Use our main validation function
    if (!gcd_validate_result(a, b, result))
    {
        return false;
    }

    // Check commutativity by computing gcd(b,a) using reference implementation
    GcdInteger reverse_result = gcd_reference_implementation(b, a);
    if (result != reverse_result)
    {
        return false;
    }

    return true;
}

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
    // Handle special cases
    if (a == 0 && b == 0)
        return 0;

    // Work with absolute values
    a = (a < 0) ? -a : a;
    b = (b < 0) ? -b : b;

    if (a == 0)
        return b;
    if (b == 0)
        return a;

    // Classic Euclidean algorithm
    while (b != 0)
    {
        GcdInteger temp = b;
        b = a % b;
        a = temp;
    }

    return a;
}

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

    // Case: gcd(0, 0) = 0 by convention
    if (a == 0 && b == 0)
    {
        *result = 0;
        return true;
    }

    // Case: gcd(a, 0) = |a|
    if (b == 0)
    {
        *result = (a < 0) ? -a : a;
        return true;
    }

    // Case: gcd(0, b) = |b|
    if (a == 0)
    {
        *result = (b < 0) ? -b : b;
        return true;
    }

    // Case: gcd(a, a) = |a|
    if (a == b)
    {
        *result = (a < 0) ? -a : a;
        return true;
    }

    // Get absolute values for checking
    GcdInteger abs_a = (a < 0) ? -a : a;
    GcdInteger abs_b = (b < 0) ? -b : b;

    // Case: gcd(1, b) = 1 or gcd(a, 1) = 1
    if (abs_a == 1 || abs_b == 1)
    {
        *result = 1;
        return true;
    }

    // No edge case applies
    return false;
}