/**
 * @file solution_spec.h
 * @brief Solution specification for Binary GCD algorithm family
 * @author Adonis G G Vinuto
 * @version 1.0
 *
 * This file defines the interface for the Binary family of GCD algorithms.
 * Currently covers your existing algorithm: mdc_stein (Stein's binary GCD algorithm).
 */

#ifndef BINARY_SOLUTION_SPEC_H
#define BINARY_SOLUTION_SPEC_H

#include "../../challenge_definition.h"

// ============================================================================
// BINARY FAMILY ALGORITHMS
// ============================================================================

/**
 * @brief Collection of Binary GCD algorithm implementations
 *
 * Simple container for binary/bit-manipulation based GCD algorithms.
 * Currently contains your mdc_stein implementation from iterativo.c
 */
typedef struct
{
    // Binary implementations
    GcdAlgorithmFunc stein; /**< mdc_stein function (Stein's algorithm) */

    // Family metadata
    const char *family_name;
    const char *family_description;
    MathNatural algorithm_count;
} BinaryGcdFamily;

// ============================================================================
// BINARY FAMILY OPERATIONS
// ============================================================================

/**
 * @brief Initialize the Binary GCD family with your algorithm implementations
 *
 * @param family Pointer to family structure to initialize
 * @return MATH_SUCCESS if initialization successful
 */
MathStatus binary_family_init(BinaryGcdFamily *family);

/**
 * @brief Execute a specific Binary algorithm by variant
 *
 * @param family Binary family instance
 * @param variant Which specific algorithm to use
 * @param a First operand
 * @param b Second operand
 * @return GCD result
 */
GcdInteger binary_family_execute(
    const BinaryGcdFamily *family,
    GcdAlgorithmVariant variant,
    GcdInteger a,
    GcdInteger b);

/**
 * @brief Execute Stein's algorithm directly
 *
 * @param family Binary family instance
 * @param a First operand
 * @param b Second operand
 * @return GCD result using Stein's binary algorithm
 */
GcdInteger binary_family_execute_stein(
    const BinaryGcdFamily *family,
    GcdInteger a,
    GcdInteger b);

/**
 * @brief Get list of available algorithms in Binary family
 *
 * @param family Binary family instance
 * @param variants Array to store available variants
 * @param max_variants Maximum number of variants to return
 * @return Number of available variants
 */
MathNatural binary_family_list_variants(
    const BinaryGcdFamily *family,
    GcdAlgorithmVariant *variants,
    MathNatural max_variants);

/**
 * @brief Get name of a specific Binary algorithm variant
 *
 * @param variant Algorithm variant
 * @return Human-readable name of the algorithm
 */
const char *binary_family_get_variant_name(GcdAlgorithmVariant variant);

/**
 * @brief Check if a variant belongs to Binary family
 *
 * @param variant Algorithm variant to check
 * @return true if variant is binary-based
 */
bool binary_family_is_binary_variant(GcdAlgorithmVariant variant);

// ============================================================================
// BINARY FAMILY CONSTANTS
// ============================================================================

/**
 * @brief Number of algorithms in Binary family
 */
#define BINARY_FAMILY_ALGORITHM_COUNT 1

/**
 * @brief Family identification
 */
#define BINARY_FAMILY_NAME "Binary GCD Family"
#define BINARY_FAMILY_DESCRIPTION "GCD algorithms based on binary operations and bit manipulation"

/**
 * @brief Binary algorithm variants (subset of GcdAlgorithmVariant)
 */
#define BINARY_VARIANTS { \
    GCD_BINARY_STEIN}

// ============================================================================
// ALGORITHM FUNCTION DECLARATIONS
// ============================================================================

/**
 * @brief Function declaration for your existing Binary GCD implementation
 *
 * This should match the signature in your iterativo.c file.
 * Declared here so the family can reference it.
 */

// From iterativo.c
extern GcdInteger mdc_stein(GcdInteger a, GcdInteger b);

// ============================================================================
// HELPER MACROS
// ============================================================================

/**
 * @brief Initialize Binary family with your implementations
 */
#define BINARY_FAMILY_INIT {                         \
    .stein = mdc_stein,                              \
    .family_name = BINARY_FAMILY_NAME,               \
    .family_description = BINARY_FAMILY_DESCRIPTION, \
    .algorithm_count = BINARY_FAMILY_ALGORITHM_COUNT}

/**
 * @brief Check if algorithm variant is Stein's algorithm
 */
#define IS_STEIN_ALGORITHM(variant) ((variant) == GCD_BINARY_STEIN)

/**
 * @brief Check if algorithm variant uses bit manipulation
 */
#define USES_BIT_MANIPULATION(variant) \
    binary_family_is_binary_variant(variant)

// ============================================================================
// BINARY ALGORITHM CHARACTERISTICS
// ============================================================================

/**
 * @brief Characteristics specific to binary GCD algorithms
 *
 * Binary algorithms typically:
 * - Use bit operations (shifts, AND operations)
 * - Avoid division and modulo operations
 * - Can be more efficient for large numbers
 * - Work well on binary computers
 */

/**
 * @brief Check if inputs are suitable for binary algorithms
 *
 * Binary algorithms work with any inputs, but may have performance
 * characteristics different from Euclidean algorithms.
 *
 * @param a First operand
 * @param b Second operand
 * @return true if inputs are suitable for binary algorithms
 */
bool binary_family_is_suitable_input(GcdInteger a, GcdInteger b);

/**
 * @brief Estimate performance advantage of binary over Euclidean
 *
 * Simple heuristic to estimate when binary algorithms might be faster.
 *
 * @param a First operand
 * @param b Second operand
 * @return true if binary algorithm likely to be faster
 */
bool binary_family_likely_faster(GcdInteger a, GcdInteger b);

#endif // BINARY_SOLUTION_SPEC_H