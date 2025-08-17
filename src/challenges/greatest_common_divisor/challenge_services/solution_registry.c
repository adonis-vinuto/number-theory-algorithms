/**
 * @file solution_registry.c
 * @brief Registry service for GCD algorithm implementations
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file implements a registry service that organizes and provides access
 * to all available GCD algorithm implementations. Simple and focused on
 * providing easy access to your algorithms.
 */

#include "../challenge_definition.h"
#include "../solutions/euclidean_family/solution_spec.h"
#include "../solutions/binary_family/solution_spec.h"
#include "../solutions/euclidean_family/implementations/classic.c"
#include "../solutions/euclidean_family/implementations/recursive.c"
#include "../solutions/binary_family/implementations/stein.c"
#include "../../../infrastructure/utilities/memory_utils.h"
#include <stdio.h>
#include <string.h>

// ============================================================================
// REGISTRY STRUCTURE
// ============================================================================

/**
 * @brief Maximum number of implementations that can be registered
 */
#define MAX_REGISTERED_IMPLEMENTATIONS 16

/**
 * @brief Registry entry for a GCD algorithm implementation
 */
typedef struct
{
    GcdAlgorithmVariant variant;
    const ImplementationSpec *implementation;
    const char *display_name;
    bool is_available;
} RegistryEntry;

/**
 * @brief Main registry structure
 */
typedef struct
{
    RegistryEntry entries[MAX_REGISTERED_IMPLEMENTATIONS];
    MathNatural entry_count;
    bool is_initialized;
} GcdSolutionRegistry;

// Global registry instance
static GcdSolutionRegistry g_registry = {0};

// ============================================================================
// REGISTRY INITIALIZATION
// ============================================================================

/**
 * @brief Initialize the GCD solution registry with all available implementations
 *
 * @return MATH_SUCCESS if initialization successful
 */
MathStatus gcd_registry_init(void)
{
    if (g_registry.is_initialized)
    {
        return MATH_SUCCESS; // Already initialized
    }

    // Clear registry
    memset(&g_registry, 0, sizeof(GcdSolutionRegistry));

    // Register classic Euclidean implementations
    g_registry.entries[g_registry.entry_count++] = (RegistryEntry){
        .variant = GCD_EUCLIDEAN_MODULO,
        .implementation = &euclidean_modulo_spec,
        .display_name = "Euclidean (Modulo)",
        .is_available = true};

    g_registry.entries[g_registry.entry_count++] = (RegistryEntry){
        .variant = GCD_EUCLIDEAN_SUBTRACTION,
        .implementation = &euclidean_subtraction_spec,
        .display_name = "Euclidean (Subtraction)",
        .is_available = true};

    g_registry.entries[g_registry.entry_count++] = (RegistryEntry){
        .variant = GCD_EUCLIDEAN_DIVISION,
        .implementation = &euclidean_division_spec,
        .display_name = "Euclidean (Division)",
        .is_available = true};

    // Register recursive Euclidean implementations
    g_registry.entries[g_registry.entry_count++] = (RegistryEntry){
        .variant = GCD_RECURSIVE_MODULO,
        .implementation = &euclidean_recursive_modulo_spec,
        .display_name = "Recursive Euclidean (Modulo)",
        .is_available = true};

    g_registry.entries[g_registry.entry_count++] = (RegistryEntry){
        .variant = GCD_RECURSIVE_SUBTRACTION,
        .implementation = &euclidean_recursive_subtraction_spec,
        .display_name = "Recursive Euclidean (Subtraction)",
        .is_available = true};

    g_registry.entries[g_registry.entry_count++] = (RegistryEntry){
        .variant = GCD_EXTENDED_EUCLIDEAN,
        .implementation = &euclidean_extended_spec,
        .display_name = "Extended Euclidean",
        .is_available = true};

    // Register binary implementations
    g_registry.entries[g_registry.entry_count++] = (RegistryEntry){
        .variant = GCD_BINARY_STEIN,
        .implementation = &stein_binary_spec,
        .display_name = "Stein Binary GCD",
        .is_available = true};

    g_registry.is_initialized = true;
    return MATH_SUCCESS;
}

/**
 * @brief Check if registry is initialized
 *
 * @return true if registry is ready to use
 */
bool gcd_registry_is_initialized(void)
{
    return g_registry.is_initialized;
}

// ============================================================================
// IMPLEMENTATION ACCESS
// ============================================================================

/**
 * @brief Get implementation by algorithm variant
 *
 * @param variant Algorithm variant to find
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *gcd_registry_get_implementation(GcdAlgorithmVariant variant)
{
    if (!gcd_registry_is_initialized())
    {
        gcd_registry_init();
    }

    for (MathNatural i = 0; i < g_registry.entry_count; i++)
    {
        if (g_registry.entries[i].variant == variant && g_registry.entries[i].is_available)
        {
            return g_registry.entries[i].implementation;
        }
    }

    return NULL;
}

/**
 * @brief Get implementation by name
 *
 * @param name Implementation name to find
 * @return Pointer to implementation spec, NULL if not found
 */
const ImplementationSpec *gcd_registry_get_implementation_by_name(const char *name)
{
    if (!gcd_registry_is_initialized() || name == NULL)
    {
        if (!gcd_registry_is_initialized())
        {
            gcd_registry_init();
        }
        if (name == NULL)
        {
            return NULL;
        }
    }

    for (MathNatural i = 0; i < g_registry.entry_count; i++)
    {
        if (g_registry.entries[i].is_available &&
            strcmp(g_registry.entries[i].implementation->metadata.name, name) == 0)
        {
            return g_registry.entries[i].implementation;
        }
    }

    return NULL;
}

/**
 * @brief Execute algorithm by variant
 *
 * @param variant Algorithm variant to execute
 * @param a First operand
 * @param b Second operand
 * @return MathResult with computation result
 */
MathResult gcd_registry_execute(GcdAlgorithmVariant variant, GcdInteger a, GcdInteger b)
{
    const ImplementationSpec *spec = gcd_registry_get_implementation(variant);
    if (spec == NULL)
    {
        return math_create_error_result(MATH_ERROR_NOT_IMPLEMENTED, 0, 0.0);
    }

    MathBinaryInput input = {.operand_a = a, .operand_b = b};
    return spec->compute(&input);
}

/**
 * @brief Execute algorithm by name
 *
 * @param name Implementation name to execute
 * @param a First operand
 * @param b Second operand
 * @return MathResult with computation result
 */
MathResult gcd_registry_execute_by_name(const char *name, GcdInteger a, GcdInteger b)
{
    const ImplementationSpec *spec = gcd_registry_get_implementation_by_name(name);
    if (spec == NULL)
    {
        return math_create_error_result(MATH_ERROR_NOT_IMPLEMENTED, 0, 0.0);
    }

    MathBinaryInput input = {.operand_a = a, .operand_b = b};
    return spec->compute(&input);
}

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
MathNatural gcd_registry_list_variants(GcdAlgorithmVariant *variants, MathNatural max_variants)
{
    if (!gcd_registry_is_initialized())
    {
        gcd_registry_init();
    }

    if (variants == NULL || max_variants == 0)
    {
        return g_registry.entry_count; // Return count without filling array
    }

    MathNatural count = 0;
    for (MathNatural i = 0; i < g_registry.entry_count && count < max_variants; i++)
    {
        if (g_registry.entries[i].is_available)
        {
            variants[count++] = g_registry.entries[i].variant;
        }
    }

    return count;
}

/**
 * @brief Get list of all available implementation names
 *
 * @param names Array to store name pointers
 * @param max_names Maximum number of names to return
 * @return Number of available implementations
 */
MathNatural gcd_registry_list_names(const char **names, MathNatural max_names)
{
    if (!gcd_registry_is_initialized())
    {
        gcd_registry_init();
    }

    if (names == NULL || max_names == 0)
    {
        return g_registry.entry_count; // Return count without filling array
    }

    MathNatural count = 0;
    for (MathNatural i = 0; i < g_registry.entry_count && count < max_names; i++)
    {
        if (g_registry.entries[i].is_available)
        {
            names[count++] = g_registry.entries[i].implementation->metadata.name;
        }
    }

    return count;
}

/**
 * @brief Get display name for an algorithm variant
 *
 * @param variant Algorithm variant
 * @return Display name, or "Unknown" if not found
 */
const char *gcd_registry_get_display_name(GcdAlgorithmVariant variant)
{
    if (!gcd_registry_is_initialized())
    {
        gcd_registry_init();
    }

    for (MathNatural i = 0; i < g_registry.entry_count; i++)
    {
        if (g_registry.entries[i].variant == variant && g_registry.entries[i].is_available)
        {
            return g_registry.entries[i].display_name;
        }
    }

    return "Unknown";
}

/**
 * @brief Get total number of registered implementations
 *
 * @return Number of available implementations
 */
MathNatural gcd_registry_get_count(void)
{
    if (!gcd_registry_is_initialized())
    {
        gcd_registry_init();
    }

    MathNatural count = 0;
    for (MathNatural i = 0; i < g_registry.entry_count; i++)
    {
        if (g_registry.entries[i].is_available)
        {
            count++;
        }
    }

    return count;
}

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
MathNatural gcd_registry_list_euclidean_variants(GcdAlgorithmVariant *variants, MathNatural max_variants)
{
    if (!gcd_registry_is_initialized())
    {
        gcd_registry_init();
    }

    if (variants == NULL || max_variants == 0)
    {
        return 0;
    }

    MathNatural count = 0;
    for (MathNatural i = 0; i < g_registry.entry_count && count < max_variants; i++)
    {
        if (g_registry.entries[i].is_available)
        {
            GcdAlgorithmVariant variant = g_registry.entries[i].variant;
            if (is_classic_euclidean_variant(variant) || is_recursive_euclidean_variant(variant))
            {
                variants[count++] = variant;
            }
        }
    }

    return count;
}

/**
 * @brief Get implementations from Binary family
 *
 * @param variants Array to store Binary variants
 * @param max_variants Maximum number of variants to return
 * @return Number of Binary implementations
 */
MathNatural gcd_registry_list_binary_variants(GcdAlgorithmVariant *variants, MathNatural max_variants)
{
    if (!gcd_registry_is_initialized())
    {
        gcd_registry_init();
    }

    if (variants == NULL || max_variants == 0)
    {
        return 0;
    }

    MathNatural count = 0;
    for (MathNatural i = 0; i < g_registry.entry_count && count < max_variants; i++)
    {
        if (g_registry.entries[i].is_available)
        {
            GcdAlgorithmVariant variant = g_registry.entries[i].variant;
            if (is_stein_variant(variant))
            {
                variants[count++] = variant;
            }
        }
    }

    return count;
}

// ============================================================================
// CONSOLE OUTPUT UTILITIES
// ============================================================================

/**
 * @brief Print all available implementations to console
 */
void gcd_registry_print_all(void)
{
    if (!gcd_registry_is_initialized())
    {
        gcd_registry_init();
    }

    printf("=== Available GCD Algorithm Implementations ===\n\n");

    printf("Euclidean Family:\n");
    for (MathNatural i = 0; i < g_registry.entry_count; i++)
    {
        if (g_registry.entries[i].is_available)
        {
            GcdAlgorithmVariant variant = g_registry.entries[i].variant;
            if (is_classic_euclidean_variant(variant) || is_recursive_euclidean_variant(variant))
            {
                printf("  - %-25s (%s)\n",
                       g_registry.entries[i].display_name,
                       g_registry.entries[i].implementation->metadata.name);
            }
        }
    }

    printf("\nBinary Family:\n");
    for (MathNatural i = 0; i < g_registry.entry_count; i++)
    {
        if (g_registry.entries[i].is_available)
        {
            GcdAlgorithmVariant variant = g_registry.entries[i].variant;
            if (is_stein_variant(variant))
            {
                printf("  - %-25s (%s)\n",
                       g_registry.entries[i].display_name,
                       g_registry.entries[i].implementation->metadata.name);
            }
        }
    }

    printf("\nTotal: %lu implementations available\n\n", (unsigned long)gcd_registry_get_count());
}

/**
 * @brief Print implementation details
 *
 * @param variant Algorithm variant to describe
 */
void gcd_registry_print_implementation_info(GcdAlgorithmVariant variant)
{
    const ImplementationSpec *spec = gcd_registry_get_implementation(variant);
    if (spec == NULL)
    {
        printf("Implementation not found for variant %d\n", variant);
        return;
    }

    printf("=== Implementation Details ===\n");
    printf("Name: %s\n", spec->metadata.name);
    printf("Display Name: %s\n", gcd_registry_get_display_name(variant));
    printf("Description: %s\n", spec->metadata.description);
    printf("Family: %s\n", (spec->metadata.family == ALGORITHM_FAMILY_EUCLIDEAN) ? "Euclidean" : "Binary");
    printf("Recursive: %s\n", spec->metadata.is_recursive ? "Yes" : "No");

    const char *complexity;
    switch (spec->metadata.time_complexity)
    {
    case COMPLEXITY_CONSTANT:
        complexity = "O(1)";
        break;
    case COMPLEXITY_LOGARITHMIC:
        complexity = "O(log n)";
        break;
    case COMPLEXITY_LINEAR:
        complexity = "O(n)";
        break;
    default:
        complexity = "Unknown";
        break;
    }
    printf("Time Complexity: %s\n", complexity);
    printf("\n");
}