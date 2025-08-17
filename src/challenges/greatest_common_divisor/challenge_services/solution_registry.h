/**
 * @file solution_registry.h
 * @brief Registry service for GCD algorithm implementations
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This header defines a registry service that organizes and provides access
 * to all available GCD algorithm implementations. Simple and focused on
 * providing easy access to algorithms.
 */

#ifndef SOLUTION_REGISTRY_H
#define SOLUTION_REGISTRY_H

#include "../challenge_definition.h"
#include "../domain_types.h"
#include "../../../core/interfaces/implementation_interface.h"
#include "../../../core/domain/mathematical_types.h"
#include <stdbool.h>

// ============================================================================
// REGISTRY INITIALIZATION
// ============================================================================

/**
 * @brief Initialize the GCD solution registry with all available implementations
 *
 * @return MATH_SUCCESS if initialization successful
 */
MathStatus gcd_registry_init(void);

/**
 * @brief Check if registry is initialized
 *
 * @return true if registry is ready to use
 */
bool gcd_registry_is_initialized(void);

// ============================================================================
// IMPLEMENTATION ACCESS
// ============================================================================

/**
 * @brief Get implementation by algorithm variant
 *
 * @param variant Algorithm variant to find
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *gcd_registry_get_implementation(GcdAlgorithmVariant variant);

/**
 * @brief Get implementation by name
 *
 * @param name Implementation name to find
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *gcd_registry_get_implementation_by_name(const char *name);

/**
 * @brief Execute algorithm by variant
 *
 * @param variant Algorithm variant to execute
 * @param a First operand
 * @param b Second operand
 * @return MathResult with computation result
 */
MathResult gcd_registry_execute(GcdAlgorithmVariant variant, GcdInteger a, GcdInteger b);

/**
 * @brief Execute algorithm by name
 *
 * @param name Implementation name to execute
 * @param a First operand
 * @param b Second operand
 * @return MathResult with computation result
 */
MathResult gcd_registry_execute_by_name(const char *name, GcdInteger a, GcdInteger b);

// ============================================================================
// REGISTRY LISTING AND INFORMATION
// ============================================================================

/**
 * @brief Get list of all available algorithm variants
 *
 * @param variants Array to store variants
 * @param max_variants Maximum number of variants to return
 * @return Number of available variants
 */
MathNatural gcd_registry_list_variants(GcdAlgorithmVariant *variants, MathNatural max_variants);

/**
 * @brief Get list of all available implementation names
 *
 * @param names Array to store name pointers
 * @param max_names Maximum number of names to return
 * @return Number of available implementations
 */
MathNatural gcd_registry_list_names(const char **names, MathNatural max_names);

/**
 * @brief Get display name for an algorithm variant
 *
 * @param variant Algorithm variant
 * @return Display name, or "Unknown" if not found
 */
const char *gcd_registry_get_display_name(GcdAlgorithmVariant variant);

/**
 * @brief Get total number of registered implementations
 *
 * @return Number of available implementations
 */
MathNatural gcd_registry_get_count(void);

// ============================================================================
// FAMILY ORGANIZATION
// ============================================================================

/**
 * @brief Get implementations from Euclidean family
 *
 * @param variants Array to store Euclidean variants
 * @param max_variants Maximum number of variants to return
 * @return Number of Euclidean implementations
 */
MathNatural gcd_registry_list_euclidean_variants(GcdAlgorithmVariant *variants, MathNatural max_variants);

/**
 * @brief Get implementations from Binary family
 *
 * @param variants Array to store Binary variants
 * @param max_variants Maximum number of variants to return
 * @return Number of Binary implementations
 */
MathNatural gcd_registry_list_binary_variants(GcdAlgorithmVariant *variants, MathNatural max_variants);

// ============================================================================
// CONSOLE OUTPUT UTILITIES
// ============================================================================

/**
 * @brief Print all available implementations to console
 */
void gcd_registry_print_all(void);

/**
 * @brief Print implementation details
 *
 * @param variant Algorithm variant to describe
 */
void gcd_registry_print_implementation_info(GcdAlgorithmVariant variant);

#endif // SOLUTION_REGISTRY_H