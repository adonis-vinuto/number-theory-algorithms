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
 * Describes the properties and characteristics of a specific
 * algorithm implementation for analysis and selection purposes.
 */
typedef struct
{
    char name[MATH_MAX_NAME_LENGTH];               /**< Implementation name */
    char description[MATH_MAX_DESCRIPTION_LENGTH]; /**< Detailed description */
    char author[MATH_MAX_NAME_LENGTH];             /**< Implementation author */
    char version[16];                              /**< Version string */

    MathAlgorithmFamily family;      /**< Algorithm family */
    MathComplexity time_complexity;  /**< Time complexity */
    MathComplexity space_complexity; /**< Space complexity */

    bool is_recursive;             /**< Uses recursion */
    bool is_iterative;             /**< Uses iteration */
    bool supports_negative_inputs; /**< Handles negative numbers */
    bool supports_large_numbers;   /**< Optimized for large inputs */
    bool is_stable;                /**< Numerically stable */
    bool is_thread_safe;           /**< Thread-safe implementation */

    MathNatural recommended_input_size_min; /**< Minimum recommended input */
    MathNatural recommended_input_size_max; /**< Maximum recommended input */
} ImplementationMetadata;

/**
 * @brief Configuration parameters for implementation execution
 *
 * Allows customization of algorithm behavior without modifying
 * the implementation itself.
 */
struct ImplementationConfig
{
    MathNatural max_iterations;    /**< Maximum iterations allowed */
    double timeout_ms;             /**< Execution timeout */
    bool validate_inputs;          /**< Enable input validation */
    bool collect_performance_data; /**< Collect timing data */
    bool enable_debug_output;      /**< Enable debug information */
    void *custom_parameters;       /**< Implementation-specific params */
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
 * @param config Configuration for the execution
 * @return MathResult containing the result and metadata
 */
typedef MathResult (*ImplementationComputeFunc)(
    const MathBinaryInput *input,
    const ImplementationConfig *config);

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

/**
 * @brief Implementation initialization function signature
 *
 * Performs any necessary setup or initialization for the
 * implementation before it can be used.
 *
 * @param config Configuration parameters
 * @return MATH_SUCCESS if initialization successful
 */
typedef MathStatus (*ImplementationInitFunc)(
    const ImplementationConfig *config);

/**
 * @brief Implementation cleanup function signature
 *
 * Performs cleanup operations and resource deallocation
 * when the implementation is no longer needed.
 *
 * @return MATH_SUCCESS if cleanup successful
 */
typedef MathStatus (*ImplementationCleanupFunc)(void);

/**
 * @brief Performance estimation function signature
 *
 * Estimates the computational complexity for given input size,
 * useful for algorithm selection and planning.
 *
 * @param input_size Size/magnitude of the input
 * @return Estimated number of operations
 */
typedef MathNatural (*ImplementationEstimateFunc)(
    MathNatural input_size);

// ============================================================================
// IMPLEMENTATION SPECIFICATION STRUCTURE
// ============================================================================

/**
 * @brief Complete specification for an algorithm implementation
 *
 * This structure contains all the information needed to use,
 * analyze, and manage a specific algorithm implementation.
 */
struct ImplementationSpec
{
    // Metadata
    ImplementationMetadata metadata;

    // Function pointers
    ImplementationComputeFunc compute;
    ImplementationValidateFunc validate;
    ImplementationInitFunc initialize;
    ImplementationCleanupFunc cleanup;
    ImplementationEstimateFunc estimate_complexity;

    // Configuration
    ImplementationConfig default_config;

    // Runtime state
    bool is_initialized;
    MathNatural usage_count;
    MathPerformanceMetrics performance_history;
};

// ============================================================================
// IMPLEMENTATION INTERFACE FUNCTIONS
// ============================================================================

/**
 * @brief Initialize an implementation specification with default values
 *
 * @param spec Pointer to the implementation spec to initialize
 * @param name Name of the implementation
 * @return MATH_SUCCESS if initialization successful
 */
MathStatus implementation_spec_init(
    ImplementationSpec *spec,
    const char *name);

/**
 * @brief Execute an implementation with given input and configuration
 *
 * @param spec Implementation specification
 * @param input Input parameters
 * @param config Execution configuration (NULL for defaults)
 * @return MathResult with computation result and metadata
 */
MathResult implementation_execute(
    ImplementationSpec *spec,
    const MathBinaryInput *input,
    const ImplementationConfig *config);

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
 * @brief Get performance metrics for an implementation
 *
 * @param spec Implementation specification
 * @return Copy of current performance metrics
 */
MathPerformanceMetrics implementation_get_performance(
    const ImplementationSpec *spec);

/**
 * @brief Reset performance metrics for an implementation
 *
 * @param spec Implementation specification
 */
void implementation_reset_performance(
    ImplementationSpec *spec);

/**
 * @brief Check if implementation is suitable for given input size
 *
 * @param spec Implementation specification
 * @param input_size Size/magnitude of input
 * @return true if implementation is recommended for this input size
 */
bool implementation_is_suitable_for_size(
    const ImplementationSpec *spec,
    MathNatural input_size);

// ============================================================================
// UTILITY MACROS FOR IMPLEMENTATION DEFINITION
// ============================================================================

/**
 * @brief Macro to define implementation metadata
 */
#define IMPLEMENTATION_METADATA(name, desc, family, time_comp, space_comp) { \
    .name = name,                                                            \
    .description = desc,                                                     \
    .author = "Number Theory Algorithms Project",                            \
    .version = "1.0",                                                        \
    .family = family,                                                        \
    .time_complexity = time_comp,                                            \
    .space_complexity = space_comp,                                          \
    .is_recursive = false,                                                   \
    .is_iterative = true,                                                    \
    .supports_negative_inputs = true,                                        \
    .supports_large_numbers = true,                                          \
    .is_stable = true,                                                       \
    .is_thread_safe = true,                                                  \
    .recommended_input_size_min = 1,                                         \
    .recommended_input_size_max = UINT64_MAX}

/**
 * @brief Macro to define default implementation configuration
 */
#define IMPLEMENTATION_DEFAULT_CONFIG {            \
    .max_iterations = MATH_DEFAULT_MAX_ITERATIONS, \
    .timeout_ms = MATH_DEFAULT_TIMEOUT_MS,         \
    .validate_inputs = true,                       \
    .collect_performance_data = true,              \
    .enable_debug_output = false,                  \
    .custom_parameters = NULL}

/**
 * @brief Macro to create a complete implementation specification
 */
#define DEFINE_IMPLEMENTATION_SPEC(name, compute_fn, validate_fn, init_fn, cleanup_fn, estimate_fn, metadata_def) \
    {                                                                                                             \
        .metadata = metadata_def,                                                                                 \
        .compute = compute_fn,                                                                                    \
        .validate = validate_fn,                                                                                  \
        .initialize = init_fn,                                                                                    \
        .cleanup = cleanup_fn,                                                                                    \
        .estimate_complexity = estimate_fn,                                                                       \
        .default_config = IMPLEMENTATION_DEFAULT_CONFIG,                                                          \
        .is_initialized = false,                                                                                  \
        .usage_count = 0,                                                                                         \
        .performance_history = {0}}

#endif // IMPLEMENTATION_INTERFACE_H