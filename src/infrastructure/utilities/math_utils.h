/**
 * @file math_utils.h
 * @brief Essential mathematical utilities for GCD algorithms
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This header declares basic mathematical operations, timing utilities,
 * and result creation functions used throughout the GCD algorithms.
 */

#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include "../../core/domain/mathematical_types.h"
#include <stdbool.h>

// ============================================================================
// BASIC MATHEMATICAL OPERATIONS
// ============================================================================

/**
 * @brief Compute absolute value with overflow protection
 *
 * @param value Input value
 * @param result Pointer to store the absolute value
 * @return MATH_SUCCESS if successful, MATH_ERROR_OVERFLOW if overflow
 */
MathStatus math_safe_abs(MathInteger value, MathInteger *result);

/**
 * @brief Swap two integer values
 *
 * @param a Pointer to first value
 * @param b Pointer to second value
 */
void math_swap_integers(MathInteger *a, MathInteger *b);

/**
 * @brief Check if a number is even (for Stein's algorithm)
 *
 * @param value Input value
 * @return true if even, false if odd
 */
bool math_is_even(MathInteger value);

/**
 * @brief Count trailing zeros in binary representation (for Stein's algorithm)
 *
 * @param value Input value (must be non-zero)
 * @return Number of trailing zeros
 */
MathNatural math_count_trailing_zeros(MathInteger value);

/**
 * @brief Safe modulo operation with sign handling
 *
 * @param dividend Dividend
 * @param divisor Divisor (must be non-zero)
 * @param result Pointer to store result
 * @return MATH_SUCCESS if successful, error code otherwise
 */
MathStatus math_safe_modulo(MathInteger dividend, MathInteger divisor, MathInteger *result);

/**
 * @brief Safe division operation with overflow check
 *
 * @param dividend Dividend
 * @param divisor Divisor (must be non-zero)
 * @param quotient Pointer to store quotient
 * @param remainder Pointer to store remainder (optional)
 * @return MATH_SUCCESS if successful, error code otherwise
 */
MathStatus math_safe_division(MathInteger dividend, MathInteger divisor, MathInteger *quotient, MathInteger *remainder);

// ============================================================================
// TIMING UTILITIES
// ============================================================================

/**
 * @brief Get current time in milliseconds
 *
 * @return Current time in milliseconds, or -1.0 on error
 */
double math_get_time_ms(void);

/**
 * @brief Calculate elapsed time between two timestamps
 *
 * @param start_time Start timestamp in milliseconds
 * @param end_time End timestamp in milliseconds
 * @return Elapsed time in milliseconds, or 0.0 if invalid
 */
double math_elapsed_time_ms(double start_time, double end_time);

// ============================================================================
// RESULT CREATION
// ============================================================================

/**
 * @brief Create a successful math result
 *
 * @param value Result value
 * @param iterations Number of iterations performed
 * @param execution_time_ms Execution time in milliseconds
 * @return Initialized MathResult structure
 */
MathResult math_create_success_result(MathInteger value, MathNatural iterations, double execution_time_ms);

/**
 * @brief Create an error math result
 *
 * @param error_status Error status code
 * @param iterations Number of iterations performed before error
 * @param execution_time_ms Execution time before error
 * @return Initialized MathResult structure with error
 */
MathResult math_create_error_result(MathStatus error_status, MathNatural iterations, double execution_time_ms);

/**
 * @brief Create default binary input with sensible defaults
 *
 * @param a First operand
 * @param b Second operand
 * @return Initialized MathBinaryInput structure
 */
MathBinaryInput math_create_binary_input(MathInteger a, MathInteger b);

/**
 * @brief Create binary input with custom configuration
 *
 * @param a First operand
 * @param b Second operand
 * @param validate_input Whether to validate input
 * @param max_iterations Maximum iterations allowed
 * @param timeout_ms Timeout in milliseconds
 * @return Initialized MathBinaryInput structure
 */
MathBinaryInput math_create_binary_input_custom(
    MathInteger a,
    MathInteger b,
    bool validate_input,
    MathNatural max_iterations,
    double timeout_ms);

// ============================================================================
// GCD SPECIAL CASES
// ============================================================================

/**
 * @brief Handle special cases for GCD computation
 *
 * @param a First operand
 * @param b Second operand
 * @param result Pointer to store result if special case handled
 * @return true if special case was handled, false if normal computation needed
 */
bool math_handle_gcd_special_cases(MathInteger a, MathInteger b, MathResult *result);

/**
 * @brief Validate GCD computation input
 *
 * @param a First operand
 * @param b Second operand
 * @return MATH_SUCCESS if input is valid, error code otherwise
 */
MathStatus math_validate_gcd_input(MathInteger a, MathInteger b);

// ============================================================================
// MATHEMATICAL STATISTICS UTILITIES
// ============================================================================

/**
 * @brief Calculate average of execution times
 *
 * @param times Array of execution times
 * @param count Number of times
 * @return Average time, or 0.0 if invalid input
 */
double math_calculate_average_time(const double *times, MathNatural count);

/**
 * @brief Find minimum execution time
 *
 * @param times Array of execution times
 * @param count Number of times
 * @return Minimum time, or 0.0 if invalid input
 */
double math_find_min_time(const double *times, MathNatural count);

/**
 * @brief Find maximum execution time
 *
 * @param times Array of execution times
 * @param count Number of times
 * @return Maximum time, or 0.0 if invalid input
 */
double math_find_max_time(const double *times, MathNatural count);

/**
 * @brief Calculate standard deviation of execution times
 *
 * @param times Array of execution times
 * @param count Number of times
 * @param average Average time (pre-calculated)
 * @return Standard deviation, or 0.0 if invalid input
 */
double math_calculate_stddev_time(const double *times, MathNatural count, double average);

#endif // MATH_UTILS_H