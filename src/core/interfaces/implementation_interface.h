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
    MathNatural max_iterations;    /**< Maximum iterations allowed */
    double timeout_ms;             /**< Timeout in milliseconds */
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

/**
 * @brief Initialize an implementation specification
 *
 * @param spec Implementation specification to initialize
 * @param name Implementation name
 * @param description Implementation description
 * @param family Algorithm family
 * @param time_complexity Time complexity
 * @param compute_func Computation function
 * @param validate_func Validation function
 * @return MATH_SUCCESS if initialization successful
 */
MathStatus implementation_init_spec(
    ImplementationSpec *spec,
    const char *name,
    const char *description,
    MathAlgorithmFamily family,
    MathComplexity time_complexity,
    ImplementationComputeFunc compute_func,
    ImplementationValidateFunc validate_func);

// ============================================================================
// UTILITY MACROS FOR IMPLEMENTATION DEFINITION
// ============================================================================

/**
 * @brief Macro to define implementation metadata (static initialization safe)
 */
#define IMPLEMENTATION_METADATA(name, desc, family, time_comp, recursive) { \
    .name = name,                                                           \
    .description = desc,                                                    \
    .family = family,                                                       \
    .time_complexity = time_comp,                                           \
    .is_recursive = recursive}

/**
 * @brief Macro to create a basic implementation specification (static)
 *
 * Note: This creates an uninitialized spec that needs to be initialized
 * at runtime using implementation_init_spec() to avoid function calls
 * in static initialization context.
 */
#define DEFINE_IMPLEMENTATION_SPEC_STATIC(name_str, compute_fn, validate_fn, meta_name, meta_desc, meta_family, meta_complexity, meta_recursive) \
    {                                                                                                                                            \
        .metadata = IMPLEMENTATION_METADATA(meta_name, meta_desc, meta_family, meta_complexity, meta_recursive),                                 \
        .compute = compute_fn,                                                                                                                   \
        .validate = validate_fn,                                                                                                                 \
        .performance = MATH_PERFORMANCE_METRICS_INIT}

/**
 * @brief Helper macro for creating implementation specs with standard parameters
 */
#define STANDARD_IMPLEMENTATION_SPEC(id, display_name, desc, family, complexity, compute_fn, validate_fn) \
    DEFINE_IMPLEMENTATION_SPEC_STATIC(#id, compute_fn, validate_fn, display_name, desc, family, complexity, false)

/**
 * @brief Helper macro for creating recursive implementation specs
 */
#define RECURSIVE_IMPLEMENTATION_SPEC(id, display_name, desc, family, complexity, compute_fn, validate_fn) \
    DEFINE_IMPLEMENTATION_SPEC_STATIC(#id, compute_fn, validate_fn, display_name, desc, family, complexity, true)

// ============================================================================
// IMPLEMENTATION REGISTRY HELPERS
// ============================================================================

/**
 * @brief Maximum number of implementations that can be registered globally
 */
#define MAX_GLOBAL_IMPLEMENTATIONS 32

/**
 * @brief Initialize implementation specification at runtime
 *
 * Use this function to properly initialize specs that need dynamic setup.
 *
 * @param spec Specification to initialize
 * @param name Implementation name
 * @param description Implementation description
 * @param family Algorithm family
 * @param complexity Time complexity
 * @param is_recursive Whether implementation is recursive
 * @param compute_func Computation function
 * @param validate_func Validation function
 */
void implementation_setup_spec(
    ImplementationSpec *spec,
    const char *name,
    const char *description,
    MathAlgorithmFamily family,
    MathComplexity complexity,
    bool is_recursive,
    ImplementationComputeFunc compute_func,
    ImplementationValidateFunc validate_func);

/**
 * @brief Reset performance metrics for an implementation
 *
 * @param spec Implementation specification
 */
void implementation_reset_performance(ImplementationSpec *spec);

/**
 * @brief Update performance metrics after execution
 *
 * @param spec Implementation specification
 * @param execution_time Execution time in milliseconds
 * @param was_successful Whether execution was successful
 */
void implementation_update_performance(
    ImplementationSpec *spec,
    double execution_time,
    bool was_successful);

// ============================================================================
// IMPLEMENTATION VALIDATION HELPERS
// ============================================================================

/**
 * @brief Check if implementation specification is valid
 *
 * @param spec Implementation specification to validate
 * @return true if specification is valid
 */
bool implementation_is_valid_spec(const ImplementationSpec *spec);

/**
 * @brief Get implementation name safely
 *
 * @param spec Implementation specification
 * @return Implementation name or "Unknown" if invalid
 */
const char *implementation_get_name(const ImplementationSpec *spec);

/**
 * @brief Get implementation description safely
 *
 * @param spec Implementation specification
 * @return Implementation description or "No description" if invalid
 */
const char *implementation_get_description(const ImplementationSpec *spec);

#endif // IMPLEMENTATION_INTERFACE_H