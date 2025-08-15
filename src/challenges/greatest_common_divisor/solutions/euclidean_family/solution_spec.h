/**
 * @file solution_spec.h
 * @brief Solution specification for Euclidean GCD algorithm family
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file defines the interface for the Euclidean family of GCD algorithms.
 */

#ifndef EUCLIDEAN_SOLUTION_SPEC_H
#define EUCLIDEAN_SOLUTION_SPEC_H

#include "../../challenge_definition.h"
#include "../../../../core/interfaces/implementation_interface.h"

// ============================================================================
// EUCLIDEAN FAMILY ALGORITHMS
// ============================================================================

/**
 * @brief Collection of Euclidean GCD algorithm implementations
 *
 * Simple container for all the Euclidean-based algorithms you have implemented.
 * Maps directly to your existing functions in iterativo.c and recursivo.c
 */
typedef struct
{
    // Iterative implementations (from iterativo.c)
    GcdAlgorithmFunc modulo;      /**< mdc_modulo function */
    GcdAlgorithmFunc subtraction; /**< mdc_subtracao function */
    GcdAlgorithmFunc division;    /**< mdc_divisao function */

    // Recursive implementations (from recursivo.c)
    GcdAlgorithmFunc recursive_modulo;      /**< mdc_mod function */
    GcdAlgorithmFunc recursive_subtraction; /**< mdc_sub function */

    // Extended algorithm (from recursivo.c)
    ExtendedGcdAlgorithmFunc extended; /**< mdc_ext function */

    // Family metadata
    const char *family_name;
    const char *family_description;
    MathNatural algorithm_count;
} EuclideanGcdFamily;

// ============================================================================
// EUCLIDEAN FAMILY OPERATIONS
// ============================================================================

/**
 * @brief Initialize the Euclidean GCD family with your algorithm implementations
 *
 * @param family Pointer to family structure to initialize
 * @return MATH_SUCCESS if initialization successful
 */
MathStatus euclidean_family_init(EuclideanGcdFamily *family);

/**
 * @brief Execute a specific Euclidean algorithm by variant
 *
 * @param family Euclidean family instance
 * @param variant Which specific algorithm to use
 * @param a First operand
 * @param b Second operand
 * @return GCD result
 */
GcdInteger euclidean_family_execute(
    const EuclideanGcdFamily *family,
    GcdAlgorithmVariant variant,
    GcdInteger a,
    GcdInteger b);

/**
 * @brief Execute the Extended Euclidean algorithm
 *
 * @param family Euclidean family instance
 * @param a First operand
 * @param b Second operand
 * @param x Pointer to store coefficient for a
 * @param y Pointer to store coefficient for b
 * @return GCD result
 */
GcdInteger euclidean_family_execute_extended(
    const EuclideanGcdFamily *family,
    GcdInteger a,
    GcdInteger b,
    GcdInteger *x,
    GcdInteger *y);

/**
 * @brief Get list of available algorithms in Euclidean family
 *
 * @param family Euclidean family instance
 * @param variants Array to store available variants
 * @param max_variants Maximum number of variants to return
 * @return Number of available variants
 */
MathNatural euclidean_family_list_variants(
    const EuclideanGcdFamily *family,
    GcdAlgorithmVariant *variants,
    MathNatural max_variants);

/**
 * @brief Get name of a specific Euclidean algorithm variant
 *
 * @param variant Algorithm variant
 * @return Human-readable name of the algorithm
 */
const char *euclidean_family_get_variant_name(GcdAlgorithmVariant variant);

/**
 * @brief Check if a variant belongs to Euclidean family
 *
 * @param variant Algorithm variant to check
 * @return true if variant is Euclidean-based
 */
bool euclidean_family_is_euclidean_variant(GcdAlgorithmVariant variant);

// ============================================================================
// EUCLIDEAN FAMILY CONSTANTS
// ============================================================================

/**
 * @brief Number of algorithms in Euclidean family
 */
#define EUCLIDEAN_FAMILY_ALGORITHM_COUNT 6

/**
 * @brief Family identification
 */
#define EUCLIDEAN_FAMILY_NAME "Euclidean GCD Family"
#define EUCLIDEAN_FAMILY_DESCRIPTION "GCD algorithms based on Euclidean algorithm principle"

/**
 * @brief Euclidean algorithm variants (subset of GcdAlgorithmVariant)
 */
#define EUCLIDEAN_VARIANTS {   \
    GCD_EUCLIDEAN_MODULO,      \
    GCD_EUCLIDEAN_SUBTRACTION, \
    GCD_EUCLIDEAN_DIVISION,    \
    GCD_RECURSIVE_MODULO,      \
    GCD_RECURSIVE_SUBTRACTION, \
    GCD_EXTENDED_EUCLIDEAN}

// ============================================================================
// ALGORITHM FUNCTION DECLARATIONS
// ============================================================================

/**
 * @brief Function declarations for your existing GCD implementations
 *
 * These should match the signatures in your iterativo.c and recursivo.c files.
 * Declared here so the family can reference them.
 */

// From iterativo.c
extern GcdInteger mdc_modulo(GcdInteger a, GcdInteger b);
extern GcdInteger mdc_subtracao(GcdInteger a, GcdInteger b);
extern GcdInteger mdc_divisao(GcdInteger a, GcdInteger b);

// From recursivo.c
extern GcdInteger mdc_mod(GcdInteger a, GcdInteger b);
extern GcdInteger mdc_sub(GcdInteger a, GcdInteger b);
extern GcdInteger mdc_ext(GcdInteger a, GcdInteger b, GcdInteger *x, GcdInteger *y);

// ============================================================================
// HELPER MACROS
// ============================================================================

/**
 * @brief Initialize Euclidean family with your implementations
 */
#define EUCLIDEAN_FAMILY_INIT {                         \
    .modulo = mdc_modulo,                               \
    .subtraction = mdc_subtracao,                       \
    .division = mdc_divisao,                            \
    .recursive_modulo = mdc_mod,                        \
    .recursive_subtraction = mdc_sub,                   \
    .extended = mdc_ext,                                \
    .family_name = EUCLIDEAN_FAMILY_NAME,               \
    .family_description = EUCLIDEAN_FAMILY_DESCRIPTION, \
    .algorithm_count = EUCLIDEAN_FAMILY_ALGORITHM_COUNT}

/**
 * @brief Check if algorithm variant requires coefficients (extended)
 */
#define IS_EXTENDED_EUCLIDEAN(variant) ((variant) == GCD_EXTENDED_EUCLIDEAN)

/**
 * @brief Check if algorithm variant is recursive
 */
#define IS_RECURSIVE_EUCLIDEAN(variant)        \
    ((variant) == GCD_RECURSIVE_MODULO ||      \
     (variant) == GCD_RECURSIVE_SUBTRACTION || \
     (variant) == GCD_EXTENDED_EUCLIDEAN)

#endif // EUCLIDEAN_SOLUTION_SPEC_H