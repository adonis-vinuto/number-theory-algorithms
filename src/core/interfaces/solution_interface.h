/**
 * @file solution_interface.h
 * @brief Interface contract for solution families
 * @author Adonis G G Vinuto
 * @version 1.0
 *
 * This file defines the standard interface for solution families, which
 * group related algorithm implementations. It provides functions for
 * managing implementations, executing algorithms, and retrieving metadata.
 */

#ifndef SOLUTION_INTERFACE_H
#define SOLUTION_INTERFACE_H

#include "../domain/mathematical_types.h"
#include "implementation_interface.h"
#include <stdbool.h>

// ============================================================================
// FORWARD DECLARATIONS
// ============================================================================

typedef struct SolutionFamily SolutionFamily;
typedef struct SolutionConfig SolutionConfig;
typedef struct SolutionRegistry SolutionRegistry;

// ============================================================================
// SOLUTION FAMILY METADATA
// ============================================================================

/**
 * @brief Maximum number of implementations per solution family
 */
#define MAX_IMPLEMENTATIONS_PER_FAMILY 8

/**
 * @brief Solution family characteristics and metadata
 *
 * Simplified metadata for GCD algorithm families.
 */
typedef struct
{
    char name[MATH_MAX_NAME_LENGTH];               /**< Family name */
    char description[MATH_MAX_DESCRIPTION_LENGTH]; /**< Detailed description */

    MathAlgorithmFamily family_type;        /**< Primary algorithm family */
    MathComplexity typical_time_complexity; /**< Typical time complexity */
} SolutionFamilyMetadata;

// ============================================================================
// SOLUTION FAMILY STRUCTURE
// ============================================================================

/**
 * @brief Complete specification for a solution family
 *
 * Simplified container for a family of related GCD algorithm implementations.
 */
struct SolutionFamily
{
    // Metadata
    SolutionFamilyMetadata metadata;

    // Implementations registry
    ImplementationSpec *implementations[MAX_IMPLEMENTATIONS_PER_FAMILY];
    MathNatural implementation_count;
};

// ============================================================================
// SOLUTION FAMILY INTERFACE FUNCTIONS
// ============================================================================

/**
 * @brief Register an implementation with a solution family
 *
 * @param family Solution family
 * @param implementation Implementation to register
 * @return MATH_SUCCESS if registration successful
 */
MathStatus solution_family_register(
    SolutionFamily *family,
    ImplementationSpec *implementation);

/**
 * @brief Execute a specific implementation by index
 *
 * @param family Solution family
 * @param impl_index Index of implementation to execute
 * @param input Input parameters
 * @return MathResult with computation result and metadata
 */
MathResult solution_family_execute_by_index(
    SolutionFamily *family,
    MathNatural impl_index,
    const MathBinaryInput *input);

/**
 * @brief Get list of all available implementations in family
 *
 * @param family Solution family
 * @param implementations Array to store implementation pointers
 * @param max_implementations Maximum number of implementations to return
 * @return Number of implementations available
 */
MathNatural solution_family_list_implementations(
    const SolutionFamily *family,
    const ImplementationSpec **implementations,
    MathNatural max_implementations);

/**
 * @brief Macro to define solution family metadata
 */
#define SOLUTION_FAMILY_METADATA(name_param, desc_param, family_type_param, time_comp) { \
    .name = {name_param},                                                                \
    .description = {desc_param},                                                         \
    .family_type = family_type_param,                                                    \
    .typical_time_complexity = time_comp}

#endif // SOLUTION_INTERFACE_H