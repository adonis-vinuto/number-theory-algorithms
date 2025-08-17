/**
 * @file memory_utils.h
 * @brief Essential memory utilities for the Number Theory Algorithm System
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This header declares basic memory management and structure initialization
 * functions used throughout the system.
 */

#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include "../../core/domain/mathematical_types.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// ============================================================================
// BASIC SAFE OPERATIONS
// ============================================================================

/**
 * @brief Safe memory deallocation that prevents double-free
 *
 * @param ptr Pointer to memory to free (will be set to NULL)
 */
void memory_safe_free(void **ptr);

/**
 * @brief Safe string copy with bounds checking
 *
 * @param dest Destination buffer
 * @param src Source string
 * @param dest_size Size of destination buffer
 * @return MATH_SUCCESS if successful, error code otherwise
 */
MathStatus memory_safe_strcpy(char *dest, const char *src, size_t dest_size);

/**
 * @brief Safe string concatenation with bounds checking
 *
 * @param dest Destination buffer
 * @param src Source string to append
 * @param dest_size Total size of destination buffer
 * @return MATH_SUCCESS if successful, error code otherwise
 */
MathStatus memory_safe_strcat(char *dest, const char *src, size_t dest_size);

// ============================================================================
// STRUCTURE INITIALIZATION
// ============================================================================

/**
 * @brief Initialize a MathResult structure to default values
 *
 * @param result Pointer to MathResult to initialize
 */
void memory_init_math_result(MathResult *result);

/**
 * @brief Initialize a MathBinaryInput structure with default values
 *
 * @param input Pointer to MathBinaryInput to initialize
 * @param a First operand
 * @param b Second operand
 */
void memory_init_binary_input(MathBinaryInput *input, MathInteger a, MathInteger b);

/**
 * @brief Initialize a MathPerformanceMetrics structure to zero
 *
 * @param metrics Pointer to MathPerformanceMetrics to initialize
 */
void memory_init_performance_metrics(MathPerformanceMetrics *metrics);

/**
 * @brief Copy MathResult structure safely
 *
 * @param dest Destination MathResult
 * @param src Source MathResult
 * @return MATH_SUCCESS if successful
 */
MathStatus memory_copy_math_result(MathResult *dest, const MathResult *src);

/**
 * @brief Copy MathBinaryInput structure safely
 *
 * @param dest Destination MathBinaryInput
 * @param src Source MathBinaryInput
 * @return MATH_SUCCESS if successful
 */
MathStatus memory_copy_binary_input(MathBinaryInput *dest, const MathBinaryInput *src);

// ============================================================================
// BASIC VALIDATION
// ============================================================================

/**
 * @brief Basic validation of a MathResult structure
 *
 * @param result Pointer to validate
 * @return true if basic structure is valid, false otherwise
 */
bool memory_validate_math_result(const MathResult *result);

/**
 * @brief Basic validation of a MathBinaryInput structure
 *
 * @param input Pointer to validate
 * @return true if basic structure is valid, false otherwise
 */
bool memory_validate_binary_input(const MathBinaryInput *input);

/**
 * @brief Basic validation of a MathPerformanceMetrics structure
 *
 * @param metrics Pointer to validate
 * @return true if basic structure is valid, false otherwise
 */
bool memory_validate_performance_metrics(const MathPerformanceMetrics *metrics);

// ============================================================================
// UTILITY FUNCTIONS
// ============================================================================

/**
 * @brief Clear/zero out memory safely
 *
 * @param ptr Pointer to memory to clear
 * @param size Size of memory block in bytes
 */
void memory_clear(void *ptr, size_t size);

/**
 * @brief Check if pointer is aligned properly
 *
 * @param ptr Pointer to check
 * @param alignment Required alignment (must be power of 2)
 * @return true if pointer is properly aligned
 */
bool memory_is_aligned(const void *ptr, size_t alignment);

/**
 * @brief Get the next aligned address
 *
 * @param ptr Current pointer
 * @param alignment Required alignment (must be power of 2)
 * @return Next aligned address or NULL if invalid input
 */
void *memory_align_up(void *ptr, size_t alignment);

#endif // MEMORY_UTILS_H