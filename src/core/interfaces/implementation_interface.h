/**
 * @file implementation_interface.h
 * @brief Interface contract for algorithm implementations
 * @author Adonis G G Vinuto
 * @version 1.0
 *
 * This file defines the standard interface that all algorithm implementations
 * must follow. It ensures consistency, interchangeability, and polymorphic
 * behavior across different implementations within solution families.
 */

#ifndef IMPLEMENTATION_INTERFACE_H
#define IMPLEMENTATION_INTERFACE_H

#include "../domain/mathematical_types.h"
#include <stdbool.h>

// ============================================================================
// FORWARD DECLARATIONS
// ============================================================================

typedef struct ImplementationSpec ImplementationSpec;
typedef struct ImplementationConfig ImplementationConfig;

// ============================================================================
// IMPLEMENTATION METADATA
// ============================================================================

/**
 * @brief Implementation characteristics and metadata
 *
 * Simplified metadata focused on essential information for GCD implementations.
 */
typedef struct
{
    char name[MATH_MAX_NAME_LENGTH];               /**< Implementation name */
    char description[MATH_MAX_DESCRIPTION_LENGTH]; /**< Detailed description */

    MathAlgorithmFamily family;     /**< Algorithm family */
    MathComplexity time_complexity; /**< Time complexity */

    bool is_recursive; /**< Uses recursion */
} ImplementationMetadata;

/**
 * @brief Configuration parameters for implementation execution
 *
 * Simplified configuration for GCD algorithm execution.
 */
struct ImplementationConfig
{
    bool collect_performance_data; /**< Collect timing data */
};

// ============================================================================
// IMPLEMENTATION FUNCTION SIGNATURES
// ============================================================================

/**
 * @brief Core computation function signature
 *
 * Every implementation must provide this function to perform
 * the actual mathematical computation.
 *
 * @param input Input parameters for the computation
 * @return MathResult containing the result and metadata
 */
typedef MathResult (*ImplementationComputeFunc)(
    const MathBinaryInput *input);

/**
 * @brief Input validation function signature
 *
 * Validates whether the given input is appropriate for this
 * specific implementation.
 *
 * @param input Input parameters to validate
 * @return true if input is valid, false otherwise
 */
typedef bool (*ImplementationValidateFunc)(
    const MathBinaryInput *input);

// ============================================================================
// IMPLEMENTATION SPECIFICATION STRUCTURE
// ============================================================================

/**
 * @brief Complete specification for an algorithm implementation
 *
 * Simplified structure containing essential information to use
 * and manage a GCD algorithm implementation.
 */
struct ImplementationSpec
{
    // Metadata
    ImplementationMetadata metadata;

    // Function pointers
    ImplementationComputeFunc compute;
    ImplementationValidateFunc validate;

    // Runtime state
    MathPerformanceMetrics performance;
};

// ============================================================================
// IMPLEMENTATION INTERFACE FUNCTIONS
// ============================================================================

/**
 * @brief Execute an implementation with given input
 *
 * @param spec Implementation specification
 * @param input Input parameters
 * @return MathResult with computation result and metadata
 */
MathResult implementation_execute(
    ImplementationSpec *spec,
    const MathBinaryInput *input);

/**
 * @brief Validate input for a specific implementation
 *
 * @param spec Implementation specification
 * @param input Input parameters to validate
 * @return true if input is valid for this implementation
 */
bool implementation_validate_input(
    const ImplementationSpec *spec,
    const MathBinaryInput *input);

// ============================================================================
// UTILITY MACROS FOR IMPLEMENTATION DEFINITION
// ============================================================================

/**
 * @brief Macro to define implementation metadata
 */
#define IMPLEMENTATION_METADATA(name, desc, family, time_comp) { \
    .name = name,                                                \
    .description = desc,                                         \
    .family = family,                                            \
    .time_complexity = time_comp,                                \
    .is_recursive = false}

/**
 * @brief Macro to create a complete implementation specification
 */
#define DEFINE_IMPLEMENTATION_SPEC(name, compute_fn, validate_fn, metadata_def) \
    {                                                                           \
        .metadata = metadata_def,                                               \
        .compute = compute_fn,                                                  \
        .validate = validate_fn,                                                \
        .performance = {0}}

#endif // IMPLEMENTATION_INTERFACE_H