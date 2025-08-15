/**
 * @file challenge_definition.h
 * @brief Definition and contracts for the Greatest Common Divisor (GCD) challenge
 * @author Adonis G G Vinuto
 * @version 1.0
 *
 * This file defines the specific contracts and rules for GCD algorithm implementations.
 * Based on the actual algorithms in your iterativo.c and recursivo.c files.
 *
 * Kept minimal - only what's actually needed to organize your existing GCD algorithms.
 */

#ifndef GCD_CHALLENGE_DEFINITION_H
#define GCD_CHALLENGE_DEFINITION_H

#include "domain_types.h"

// ============================================================================
// CORE GCD ALGORITHM INTERFACE
// ============================================================================

/**
 * @brief Standard GCD algorithm function signature
 *
 * This matches the signature of your existing GCD functions:
 * mdc_modulo, mdc_subtracao, mdc_divisao, mdc_stein, mdc_mod, mdc_sub
 *
 * @param a First operand
 * @param b Second operand
 * @return Greatest common divisor of a and b
 */
typedef GcdInteger (*GcdAlgorithmFunc)(GcdInteger a, GcdInteger b);

/**
 * @brief Extended GCD algorithm function signature
 *
 * This matches your mdc_ext function signature that also computes coefficients.
 *
 * @param a First operand
 * @param b Second operand
 * @param x Pointer to store coefficient for a
 * @param y Pointer to store coefficient for b
 * @return Greatest common divisor of a and b
 */
typedef GcdInteger (*ExtendedGcdAlgorithmFunc)(
    GcdInteger a,
    GcdInteger b,
    GcdInteger *x,
    GcdInteger *y);

// ============================================================================
// GCD ALGORITHM DESCRIPTOR
// ============================================================================

/**
 * @brief Descriptor for a GCD algorithm implementation
 *
 * Simple structure to describe each of your GCD algorithms with
 * essential metadata only.
 */
typedef struct
{
    const char *name;            /**< Algorithm name (e.g., "mdc_modulo") */
    const char *description;     /**< Brief description */
    GcdAlgorithmVariant variant; /**< Which variant this is */
    MathAlgorithmFamily family;  /**< Euclidean or Binary family */
    bool is_recursive;           /**< True if recursive implementation */
    GcdAlgorithmFunc algorithm;  /**< Function pointer to the algorithm */
} GcdAlgorithmDescriptor;

/**
 * @brief Descriptor for Extended GCD algorithm
 *
 * Separate structure for the extended algorithm since it has different signature.
 */
typedef struct
{
    const char *name;                   /**< Algorithm name (e.g., "mdc_ext") */
    const char *description;            /**< Brief description */
    bool is_recursive;                  /**< True if recursive implementation */
    ExtendedGcdAlgorithmFunc algorithm; /**< Function pointer to extended algorithm */
} ExtendedGcdAlgorithmDescriptor;

// ============================================================================
// GCD VALIDATION AND RULES
// ============================================================================

/**
 * @brief Check if input values are valid for GCD computation
 *
 * @param a First operand
 * @param b Second operand
 * @return true if inputs are valid for GCD computation
 */
bool gcd_validate_input(GcdInteger a, GcdInteger b);

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
bool gcd_validate_result(GcdInteger a, GcdInteger b, GcdInteger result);

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
bool gcd_validate_extended_result(GcdInteger a, GcdInteger b, const ExtendedGcdResult *ext_result);

// ============================================================================
// GCD CHALLENGE RULES
// ============================================================================

/**
 * @brief Mathematical properties that define GCD correctness
 *
 * These are the fundamental rules that any GCD algorithm must satisfy.
 */

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
bool gcd_check_fundamental_properties(GcdInteger a, GcdInteger b, GcdInteger result);

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
GcdInteger gcd_reference_implementation(GcdInteger a, GcdInteger b);

// ============================================================================
// ALGORITHM REGISTRATION HELPERS
// ============================================================================

/**
 * @brief Create a GCD algorithm descriptor
 *
 * Helper macro to create algorithm descriptors for your existing functions.
 */
#define GCD_ALGORITHM_DESCRIPTOR(func_name, desc, var, fam, recursive) { \
    .name = #func_name,                                                  \
    .description = desc,                                                 \
    .variant = var,                                                      \
    .family = fam,                                                       \
    .is_recursive = recursive,                                           \
    .algorithm = func_name}

/**
 * @brief Create an Extended GCD algorithm descriptor
 */
#define EXTENDED_GCD_ALGORITHM_DESCRIPTOR(func_name, desc, recursive) { \
    .name = #func_name,                                                 \
    .description = desc,                                                \
    .is_recursive = recursive,                                          \
    .algorithm = func_name}

// ============================================================================
// COMMON GCD SPECIAL CASES
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
bool gcd_handle_edge_cases(GcdInteger a, GcdInteger b, GcdInteger *result);

#endif // GCD_CHALLENGE_DEFINITION_H