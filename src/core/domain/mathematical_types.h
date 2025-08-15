/**
 * @file mathematical_types.h
 * @brief Fundamental mathematical types for the Number Theory Algorithm Analysis System
 * @author Adonis G G Vinuto
 * @version 1.0
 *
 * This file defines the core mathematical types used throughout the system.
 * These types provide semantic clarity and type safety for mathematical operations.
 */

#ifndef MATHEMATICAL_TYPES_H
#define MATHEMATICAL_TYPES_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

// ============================================================================
// BASIC MATHEMATICAL TYPES
// ============================================================================

/**
 * @brief Primary mathematical integer type for computations
 *
 * Uses 64-bit signed integer to handle large mathematical values
 * while maintaining compatibility across platforms.
 */
typedef int64_t MathInteger;

/**
 * @brief Mathematical floating-point type for precise calculations
 *
 * Uses double precision for mathematical operations requiring
 * decimal precision or very large number representations.
 */
typedef double MathReal;

/**
 * @brief Unsigned mathematical integer for counting and indexing
 *
 * Used for array indices, counters, and values that are naturally
 * non-negative in mathematical contexts.
 */
typedef uint64_t MathNatural;

// ============================================================================
// COMPUTATION STATUS AND RESULTS
// ============================================================================

/**
 * @brief Status codes for mathematical computations
 *
 * Provides standardized return codes for all mathematical operations
 * to enable consistent error handling and result validation.
 */
typedef enum
{
    MATH_SUCCESS = 0,            /**< Operation completed successfully */
    MATH_ERROR_INVALID_INPUT,    /**< Invalid input parameters */
    MATH_ERROR_DIVISION_BY_ZERO, /**< Division by zero attempted */
    MATH_ERROR_OVERFLOW,         /**< Numerical overflow occurred */
    MATH_ERROR_UNDERFLOW,        /**< Numerical underflow occurred */
    MATH_ERROR_NO_SOLUTION,      /**< No mathematical solution exists */
    MATH_ERROR_TIMEOUT,          /**< Operation exceeded time limit */
    MATH_ERROR_MEMORY,           /**< Memory allocation failed */
    MATH_ERROR_NOT_IMPLEMENTED,  /**< Feature not yet implemented */
    MATH_ERROR_UNKNOWN           /**< Unknown error occurred */
} MathStatus;

/**
 * @brief Container for mathematical computation results
 *
 * Encapsulates both the result value and metadata about the computation,
 * enabling rich result analysis and error handling.
 */
typedef struct
{
    MathInteger value;        /**< Primary result value */
    MathStatus status;        /**< Computation status code */
    bool is_valid;            /**< Whether result is mathematically valid */
    MathNatural iterations;   /**< Number of iterations performed */
    double execution_time_ms; /**< Execution time in milliseconds */
} MathResult;

// ============================================================================
// MATHEMATICAL OPERATIONS METADATA
// ============================================================================

/**
 * @brief Input parameters for binary mathematical operations
 *
 * Standardized input structure for operations that take two operands,
 * such as GCD, LCM, modular arithmetic, etc.
 */
typedef struct
{
    MathInteger operand_a;      /**< First operand */
    MathInteger operand_b;      /**< Second operand */
    bool validate_input;        /**< Whether to validate inputs */
    MathNatural max_iterations; /**< Maximum allowed iterations */
    double timeout_ms;          /**< Timeout in milliseconds */
} MathBinaryInput;

/**
 * @brief Performance metrics for algorithm analysis
 *
 * Captures detailed performance data for comparative analysis
 * of different algorithmic implementations.
 */
typedef struct
{
    double avg_time_ms;          /**< Average execution time */
    double min_time_ms;          /**< Minimum execution time */
    double max_time_ms;          /**< Maximum execution time */
    double stddev_time_ms;       /**< Standard deviation of time */
    MathNatural total_runs;      /**< Total number of executions */
    MathNatural successful_runs; /**< Number of successful runs */
    double success_rate;         /**< Success rate percentage */
} MathPerformanceMetrics;

// ============================================================================
// ALGORITHM IDENTIFICATION AND METADATA
// ============================================================================

/**
 * @brief Maximum length for algorithm names and descriptions
 */
#define MATH_MAX_NAME_LENGTH 64
#define MATH_MAX_DESCRIPTION_LENGTH 256

/**
 * @brief Algorithm complexity classification
 *
 * Theoretical complexity categories for algorithm classification
 * and comparison purposes.
 */
typedef enum
{
    COMPLEXITY_CONSTANT,     /**< O(1) - Constant time */
    COMPLEXITY_LOGARITHMIC,  /**< O(log n) - Logarithmic time */
    COMPLEXITY_LINEAR,       /**< O(n) - Linear time */
    COMPLEXITY_LINEARITHMIC, /**< O(n log n) - Linearithmic time */
    COMPLEXITY_QUADRATIC,    /**< O(n²) - Quadratic time */
    COMPLEXITY_CUBIC,        /**< O(n³) - Cubic time */
    COMPLEXITY_EXPONENTIAL,  /**< O(2^n) - Exponential time */
    COMPLEXITY_FACTORIAL,    /**< O(n!) - Factorial time */
    COMPLEXITY_UNKNOWN       /**< Unknown or variable complexity */
} MathComplexity;

/**
 * @brief Algorithm family classification
 *
 * Categories for grouping related algorithms by their fundamental
 * mathematical approach or technique. Currently focused on GCD algorithms.
 */
typedef enum
{
    ALGORITHM_FAMILY_EUCLIDEAN, /**< Based on Euclidean algorithm (modulo, subtraction) */
    ALGORITHM_FAMILY_BINARY,    /**< Binary/bit manipulation based (Stein's algorithm) */
    ALGORITHM_FAMILY_UNKNOWN    /**< Unknown or not yet classified */
} MathAlgorithmFamily;

// ============================================================================
// UTILITY MACROS AND CONSTANTS
// ============================================================================

/**
 * @brief Mathematical constants
 */
#define MATH_INVALID_VALUE ((MathInteger)(-1))
#define MATH_ZERO ((MathInteger)(0))
#define MATH_ONE ((MathInteger)(1))
#define MATH_DEFAULT_TIMEOUT_MS (5000.0)
#define MATH_DEFAULT_MAX_ITERATIONS (1000000ULL)

/**
 * @brief Utility macros for mathematical operations
 */
#define MATH_ABS(x) ((x) < 0 ? -(x) : (x))
#define MATH_MIN(a, b) ((a) < (b) ? (a) : (b))
#define MATH_MAX(a, b) ((a) > (b) ? (a) : (b))
#define MATH_IS_VALID_RESULT(result) ((result).is_valid && (result).status == MATH_SUCCESS)

/**
 * @brief Result initialization macro
 */
#define MATH_RESULT_INIT(val) { \
    .value = (val),             \
    .status = MATH_SUCCESS,     \
    .is_valid = true,           \
    .iterations = 0,            \
    .execution_time_ms = 0.0}

/**
 * @brief Error result initialization macro
 */
#define MATH_RESULT_ERROR(error_status) { \
    .value = MATH_INVALID_VALUE,          \
    .status = (error_status),             \
    .is_valid = false,                    \
    .iterations = 0,                      \
    .execution_time_ms = 0.0}

#endif // MATHEMATICAL_TYPES_H