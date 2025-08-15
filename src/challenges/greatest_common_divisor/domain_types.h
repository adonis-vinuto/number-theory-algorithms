/**
 * @file domain_types.h
 * @brief Domain-specific types for Greatest Common Divisor (GCD) algorithms
 * @author Adonis G G Vinuto
 * @version 1.0
 *
 * This file defines types and constants specific to GCD computation.
 */

#ifndef GCD_DOMAIN_TYPES_H
#define GCD_DOMAIN_TYPES_H

#include "../../core/domain/mathematical_types.h"
#include "../../core/interfaces/implementation_interface.h"

// ============================================================================
// GCD-SPECIFIC TYPE ALIASES
// ============================================================================

/**
 * @brief Type alias for GCD operands (for semantic clarity)
 *
 * Same as MathInteger, but makes code more readable when dealing specifically
 * with GCD inputs.
 */
typedef MathInteger GcdInteger;

/**
 * @brief Type alias for GCD results (for semantic clarity)
 *
 * Same as MathResult, but makes it clear this is a GCD computation result.
 */
typedef MathResult GcdResult;

/**
 * @brief Type alias for GCD input pairs (for semantic clarity)
 *
 * Same as MathBinaryInput, but specific to GCD operations.
 */
typedef MathBinaryInput GcdInput;

// ============================================================================
// GCD ALGORITHM VARIANTS
// ============================================================================

/**
 * @brief Specific GCD algorithm variants implemented in the system
 *
 * This enum categorizes the actual GCD implementations we have,
 * based on your existing code in iterativo.c and recursivo.c
 */
typedef enum
{
    GCD_EUCLIDEAN_MODULO,      /**< Euclidean algorithm using modulo (%) */
    GCD_EUCLIDEAN_SUBTRACTION, /**< Euclidean algorithm using subtraction */
    GCD_EUCLIDEAN_DIVISION,    /**< Euclidean algorithm using division */
    GCD_BINARY_STEIN,          /**< Binary GCD (Stein's algorithm) */
    GCD_RECURSIVE_MODULO,      /**< Recursive Euclidean with modulo */
    GCD_RECURSIVE_SUBTRACTION, /**< Recursive Euclidean with subtraction */
    GCD_EXTENDED_EUCLIDEAN     /**< Extended Euclidean algorithm */
} GcdAlgorithmVariant;

// ============================================================================
// GCD-SPECIFIC CONSTANTS
// ============================================================================

/**
 * @brief Special GCD result values
 */
#define GCD_UNDEFINED 0 /**< gcd(0,0) result by convention */
#define GCD_IDENTITY 1  /**< gcd(a,1) = gcd(1,b) = 1 */

/**
 * @brief GCD computation limits (reasonable for most use cases)
 */
#define GCD_MAX_SAFE_VALUE LLONG_MAX /**< Maximum safe input value */
#define GCD_MIN_SAFE_VALUE LLONG_MIN /**< Minimum safe input value */

// ============================================================================
// EXTENDED GCD RESULT
// ============================================================================

/**
 * @brief Result structure for Extended Euclidean Algorithm
 *
 * Extended GCD computes gcd(a,b) and also finds coefficients x,y
 * such that ax + by = gcd(a,b). Only needed for mdc_ext function.
 */
typedef struct
{
    GcdInteger gcd;           /**< The greatest common divisor */
    GcdInteger coefficient_x; /**< Coefficient for first operand */
    GcdInteger coefficient_y; /**< Coefficient for second operand */
    bool is_valid;            /**< Whether the result is valid */
} ExtendedGcdResult;

// ============================================================================
// UTILITY MACROS FOR GCD
// ============================================================================

/**
 * @brief Create a GCD input from two integers
 */
#define GCD_INPUT(a, b) {.operand_a = (a), .operand_b = (b)}

/**
 * @brief Check if GCD result is valid and positive
 */
#define GCD_IS_VALID_POSITIVE(result) \
    (MATH_IS_VALID_RESULT(result) && (result).value > 0)

/**
 * @brief Initialize Extended GCD result
 */
#define EXTENDED_GCD_INIT(gcd_val, x_val, y_val) { \
    .gcd = (gcd_val),                              \
    .coefficient_x = (x_val),                      \
    .coefficient_y = (y_val),                      \
    .is_valid = true}

/**
 * @brief Invalid Extended GCD result
 */
#define EXTENDED_GCD_INVALID { \
    .gcd = MATH_INVALID_VALUE, \
    .coefficient_x = 0,        \
    .coefficient_y = 0,        \
    .is_valid = false}

#endif // GCD_DOMAIN_TYPES_H