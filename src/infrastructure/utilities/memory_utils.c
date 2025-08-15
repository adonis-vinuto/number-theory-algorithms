/**
 * @file memory_utils.c
 * @brief Essential memory utilities for the Number Theory Algorithm System
 * @author Adonis G G Vinuto
 * @version 1.0
 *
 * This file implements basic memory management and structure initialization
 * functions used throughout the system.
 */

#include "../../core/domain/mathematical_types.h"
#include <stdlib.h>
#include <string.h>

// ============================================================================
// BASIC SAFE OPERATIONS
// ============================================================================

/**
 * @brief Safe memory deallocation that prevents double-free
 *
 * @param ptr Pointer to memory to free (will be set to NULL)
 */
void memory_safe_free(void **ptr)
{
    if (ptr != NULL && *ptr != NULL)
    {
        free(*ptr);
        *ptr = NULL;
    }
}

/**
 * @brief Safe string copy with bounds checking
 *
 * @param dest Destination buffer
 * @param src Source string
 * @param dest_size Size of destination buffer
 * @return MATH_SUCCESS if successful, error code otherwise
 */
MathStatus memory_safe_strcpy(char *dest, const char *src, size_t dest_size)
{
    if (dest == NULL || src == NULL || dest_size == 0)
    {
        return MATH_ERROR_INVALID_INPUT;
    }

    size_t src_len = strlen(src);
    if (src_len >= dest_size)
    {
        return MATH_ERROR_INVALID_INPUT; // Not enough space
    }

    strcpy(dest, src);
    return MATH_SUCCESS;
}

// ============================================================================
// STRUCTURE INITIALIZATION
// ============================================================================

/**
 * @brief Initialize a MathResult structure to default values
 *
 * @param result Pointer to MathResult to initialize
 */
void memory_init_math_result(MathResult *result)
{
    if (result != NULL)
    {
        result->value = MATH_INVALID_VALUE;
        result->status = MATH_ERROR_UNKNOWN;
        result->is_valid = false;
        result->iterations = 0;
        result->execution_time_ms = 0.0;
    }
}

/**
 * @brief Initialize a MathBinaryInput structure with default values
 *
 * @param input Pointer to MathBinaryInput to initialize
 * @param a First operand
 * @param b Second operand
 */
void memory_init_binary_input(MathBinaryInput *input, MathInteger a, MathInteger b)
{
    if (input != NULL)
    {
        input->operand_a = a;
        input->operand_b = b;
        input->validate_input = true;
        input->max_iterations = MATH_DEFAULT_MAX_ITERATIONS;
        input->timeout_ms = MATH_DEFAULT_TIMEOUT_MS;
    }
}

/**
 * @brief Initialize a MathPerformanceMetrics structure to zero
 *
 * @param metrics Pointer to MathPerformanceMetrics to initialize
 */
void memory_init_performance_metrics(MathPerformanceMetrics *metrics)
{
    if (metrics != NULL)
    {
        metrics->avg_time_ms = 0.0;
        metrics->min_time_ms = 0.0;
        metrics->max_time_ms = 0.0;
        metrics->stddev_time_ms = 0.0;
        metrics->total_runs = 0;
        metrics->successful_runs = 0;
        metrics->success_rate = 0.0;
    }
}

// ============================================================================
// BASIC VALIDATION
// ============================================================================

/**
 * @brief Basic validation of a MathResult structure
 *
 * @param result Pointer to validate
 * @return true if basic structure is valid, false otherwise
 */
bool memory_validate_math_result(const MathResult *result)
{
    if (result == NULL)
    {
        return false;
    }

    // Check if status is in valid range
    if (result->status < MATH_SUCCESS || result->status > MATH_ERROR_UNKNOWN)
    {
        return false;
    }

    // Check basic consistency between is_valid and status
    if (result->is_valid && result->status != MATH_SUCCESS)
    {
        return false;
    }

    // Check for reasonable execution time (not negative)
    if (result->execution_time_ms < 0.0)
    {
        return false;
    }

    return true;
}

/**
 * @brief Basic validation of a MathBinaryInput structure
 *
 * @param input Pointer to validate
 * @return true if basic structure is valid, false otherwise
 */
bool memory_validate_binary_input(const MathBinaryInput *input)
{
    if (input == NULL)
    {
        return false;
    }

    // Check for reasonable timeout and iteration limits
    if (input->timeout_ms < 0.0 || input->max_iterations == 0)
    {
        return false;
    }

    return true;
}