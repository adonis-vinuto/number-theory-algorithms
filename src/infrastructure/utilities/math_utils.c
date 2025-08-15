/**
 * @file math_utils.c
 * @brief Essential mathematical utilities for GCD algorithms
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file implements basic mathematical operations, timing utilities,
 * and result creation functions used throughout the GCD algorithms.
 */

#include "../../core/domain/mathematical_types.h"
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>

// Platform detection for high-precision timing
#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)) || defined(_POSIX_VERSION)
#ifndef SIMPLE_TIMING
#define HAS_POSIX_TIMING 1
#endif
#endif

// Include POSIX headers only when available
#ifdef HAS_POSIX_TIMING
#include <unistd.h>
#endif

// ============================================================================
// BASIC MATHEMATICAL OPERATIONS (needed by GCD algorithms)
// ============================================================================

/**
 * @brief Compute absolute value with overflow protection
 *
 * @param value Input value
 * @param result Pointer to store the absolute value
 * @return MATH_SUCCESS if successful, MATH_ERROR_OVERFLOW if overflow
 */
MathStatus math_safe_abs(MathInteger value, MathInteger *result)
{
    if (result == NULL)
    {
        return MATH_ERROR_INVALID_INPUT;
    }

    if (value == LLONG_MIN)
    {
        return MATH_ERROR_OVERFLOW; // abs(LLONG_MIN) would overflow
    }

    *result = (value < 0) ? -value : value;
    return MATH_SUCCESS;
}

/**
 * @brief Swap two integer values
 *
 * @param a Pointer to first value
 * @param b Pointer to second value
 */
void math_swap_integers(MathInteger *a, MathInteger *b)
{
    if (a != NULL && b != NULL && a != b)
    {
        MathInteger temp = *a;
        *a = *b;
        *b = temp;
    }
}

/**
 * @brief Check if a number is even (for Stein's algorithm)
 *
 * @param value Input value
 * @return true if even, false if odd
 */
bool math_is_even(MathInteger value)
{
    return (value & 1) == 0;
}

/**
 * @brief Count trailing zeros in binary representation (for Stein's algorithm)
 *
 * @param value Input value (must be non-zero)
 * @return Number of trailing zeros
 */
MathNatural math_count_trailing_zeros(MathInteger value)
{
    if (value == 0)
    {
        return 0;
    }

    MathNatural count = 0;
    MathInteger abs_value = MATH_ABS(value);

    while ((abs_value & 1) == 0)
    {
        abs_value >>= 1;
        count++;
    }

    return count;
}

/**
 * @brief Safe modulo operation with sign handling
 *
 * @param dividend Dividend
 * @param divisor Divisor (must be non-zero)
 * @param result Pointer to store result
 * @return MATH_SUCCESS if successful, error code otherwise
 */
MathStatus math_safe_modulo(MathInteger dividend, MathInteger divisor, MathInteger *result)
{
    if (result == NULL)
    {
        return MATH_ERROR_INVALID_INPUT;
    }

    if (divisor == 0)
    {
        return MATH_ERROR_DIVISION_BY_ZERO;
    }

    *result = dividend % divisor;
    return MATH_SUCCESS;
}

/**
 * @brief Safe division operation with overflow check
 *
 * @param dividend Dividend
 * @param divisor Divisor (must be non-zero)
 * @param quotient Pointer to store quotient
 * @param remainder Pointer to store remainder (optional)
 * @return MATH_SUCCESS if successful, error code otherwise
 */
MathStatus math_safe_division(MathInteger dividend, MathInteger divisor, MathInteger *quotient, MathInteger *remainder)
{
    if (quotient == NULL)
    {
        return MATH_ERROR_INVALID_INPUT;
    }

    if (divisor == 0)
    {
        return MATH_ERROR_DIVISION_BY_ZERO;
    }

    // Check for overflow: LLONG_MIN / -1 would overflow
    if (dividend == LLONG_MIN && divisor == -1)
    {
        return MATH_ERROR_OVERFLOW;
    }

    *quotient = dividend / divisor;

    if (remainder != NULL)
    {
        *remainder = dividend % divisor;
    }

    return MATH_SUCCESS;
}

// ============================================================================
// TIMING UTILITIES (for performance measurement)
// ============================================================================

/**
 * @brief Get current time in milliseconds
 *
 * @return Current time in milliseconds, or -1.0 on error
 */
double math_get_time_ms(void)
{
#ifndef SIMPLE_TIMING
#ifdef HAS_POSIX_TIMING
    // POSIX systems (Linux, macOS, etc.) - high precision
    struct timespec ts;
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
    {
        return (double)ts.tv_sec * 1000.0 + (double)ts.tv_nsec / 1000000.0;
    }
#endif
#endif

    // Fallback for all systems - standard C library
    clock_t current_clock = clock();
    if (current_clock == (clock_t)-1)
    {
        return -1.0;
    }

    return (double)current_clock * 1000.0 / CLOCKS_PER_SEC;
}

/**
 * @brief Calculate elapsed time between two timestamps
 *
 * @param start_time Start timestamp in milliseconds
 * @param end_time End timestamp in milliseconds
 * @return Elapsed time in milliseconds, or 0.0 if invalid
 */
double math_elapsed_time_ms(double start_time, double end_time)
{
    if (start_time < 0.0 || end_time < 0.0 || end_time < start_time)
    {
        return 0.0;
    }

    return end_time - start_time;
}

// ============================================================================
// RESULT CREATION (for consistent return values)
// ============================================================================

/**
 * @brief Create a successful math result
 *
 * @param value Result value
 * @param iterations Number of iterations performed
 * @param execution_time_ms Execution time in milliseconds
 * @return Initialized MathResult structure
 */
MathResult math_create_success_result(MathInteger value, MathNatural iterations, double execution_time_ms)
{
    MathResult result = {
        .value = value,
        .status = MATH_SUCCESS,
        .is_valid = true,
        .iterations = iterations,
        .execution_time_ms = execution_time_ms};
    return result;
}

/**
 * @brief Create an error math result
 *
 * @param error_status Error status code
 * @param iterations Number of iterations performed before error
 * @param execution_time_ms Execution time before error
 * @return Initialized MathResult structure with error
 */
MathResult math_create_error_result(MathStatus error_status, MathNatural iterations, double execution_time_ms)
{
    MathResult result = {
        .value = MATH_INVALID_VALUE,
        .status = error_status,
        .is_valid = false,
        .iterations = iterations,
        .execution_time_ms = execution_time_ms};
    return result;
}

/**
 * @brief Create default binary input with sensible defaults
 *
 * @param a First operand
 * @param b Second operand
 * @return Initialized MathBinaryInput structure
 */
MathBinaryInput math_create_binary_input(MathInteger a, MathInteger b)
{
    MathBinaryInput input = {
        .operand_a = a,
        .operand_b = b,
        .validate_input = true,
        .max_iterations = MATH_DEFAULT_MAX_ITERATIONS,
        .timeout_ms = MATH_DEFAULT_TIMEOUT_MS};
    return input;
}

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
    double timeout_ms)
{
    MathBinaryInput input = {
        .operand_a = a,
        .operand_b = b,
        .validate_input = validate_input,
        .max_iterations = max_iterations,
        .timeout_ms = timeout_ms};
    return input;
}

// ============================================================================
// GCD SPECIAL CASES (specific to GCD algorithms)
// ============================================================================

/**
 * @brief Handle special cases for GCD computation
 *
 * @param a First operand
 * @param b Second operand
 * @param result Pointer to store result if special case handled
 * @return true if special case was handled, false if normal computation needed
 */
bool math_handle_gcd_special_cases(MathInteger a, MathInteger b, MathResult *result)
{
    if (result == NULL)
    {
        return false;
    }

    // Case: gcd(0, 0) is undefined, but we return 0 by convention
    if (a == 0 && b == 0)
    {
        *result = math_create_success_result(0, 0, 0.0);
        return true;
    }

    // Case: gcd(a, 0) = |a|
    if (b == 0)
    {
        MathInteger abs_a;
        if (math_safe_abs(a, &abs_a) != MATH_SUCCESS)
        {
            *result = math_create_error_result(MATH_ERROR_OVERFLOW, 0, 0.0);
        }
        else
        {
            *result = math_create_success_result(abs_a, 0, 0.0);
        }
        return true;
    }

    // Case: gcd(0, b) = |b|
    if (a == 0)
    {
        MathInteger abs_b;
        if (math_safe_abs(b, &abs_b) != MATH_SUCCESS)
        {
            *result = math_create_error_result(MATH_ERROR_OVERFLOW, 0, 0.0);
        }
        else
        {
            *result = math_create_success_result(abs_b, 0, 0.0);
        }
        return true;
    }

    // Case: gcd(a, a) = |a|
    if (a == b)
    {
        MathInteger abs_a;
        if (math_safe_abs(a, &abs_a) != MATH_SUCCESS)
        {
            *result = math_create_error_result(MATH_ERROR_OVERFLOW, 0, 0.0);
        }
        else
        {
            *result = math_create_success_result(abs_a, 0, 0.0);
        }
        return true;
    }

    // Case: gcd(1, b) = 1 or gcd(a, 1) = 1
    if (MATH_ABS(a) == 1 || MATH_ABS(b) == 1)
    {
        *result = math_create_success_result(1, 0, 0.0);
        return true;
    }

    return false; // No special case, proceed with normal computation
}

/**
 * @brief Validate GCD computation input
 *
 * @param a First operand
 * @param b Second operand
 * @return MATH_SUCCESS if input is valid, error code otherwise
 */
MathStatus math_validate_gcd_input(MathInteger a, MathInteger b)
{
    // Check for potential overflow conditions
    if (a == LLONG_MIN || b == LLONG_MIN)
    {
        return MATH_ERROR_OVERFLOW;
    }

    // GCD can handle any integer inputs, including negatives and zero
    return MATH_SUCCESS;
}

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
double math_calculate_average_time(const double *times, MathNatural count)
{
    if (times == NULL || count == 0)
    {
        return 0.0;
    }

    double sum = 0.0;
    for (MathNatural i = 0; i < count; i++)
    {
        if (times[i] >= 0.0)
        {
            sum += times[i];
        }
    }

    return sum / (double)count;
}

/**
 * @brief Find minimum execution time
 *
 * @param times Array of execution times
 * @param count Number of times
 * @return Minimum time, or 0.0 if invalid input
 */
double math_find_min_time(const double *times, MathNatural count)
{
    if (times == NULL || count == 0)
    {
        return 0.0;
    }

    double min_time = times[0];
    for (MathNatural i = 1; i < count; i++)
    {
        if (times[i] >= 0.0 && times[i] < min_time)
        {
            min_time = times[i];
        }
    }

    return min_time;
}

/**
 * @brief Find maximum execution time
 *
 * @param times Array of execution times
 * @param count Number of times
 * @return Maximum time, or 0.0 if invalid input
 */
double math_find_max_time(const double *times, MathNatural count)
{
    if (times == NULL || count == 0)
    {
        return 0.0;
    }

    double max_time = times[0];
    for (MathNatural i = 1; i < count; i++)
    {
        if (times[i] >= 0.0 && times[i] > max_time)
        {
            max_time = times[i];
        }
    }

    return max_time;
}

/**
 * @brief Calculate standard deviation of execution times
 *
 * @param times Array of execution times
 * @param count Number of times
 * @param average Average time (pre-calculated)
 * @return Standard deviation, or 0.0 if invalid input
 */
double math_calculate_stddev_time(const double *times, MathNatural count, double average)
{
    if (times == NULL || count <= 1)
    {
        return 0.0;
    }

    double sum_sq_diff = 0.0;
    for (MathNatural i = 0; i < count; i++)
    {
        if (times[i] >= 0.0)
        {
            double diff = times[i] - average;
            sum_sq_diff += diff * diff;
        }
    }

    return sqrt(sum_sq_diff / (double)(count - 1));
}