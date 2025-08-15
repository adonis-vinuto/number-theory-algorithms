/**
 * @file solution_interface.h
 * @brief Interface contract for solution families
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This file defines the standard interface for solution families - groups of
 * related algorithm implementations that share common mathematical principles.
 * Solution families provide higher-level organization and automatic selection
 * capabilities for algorithm implementations.
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
#define MAX_IMPLEMENTATIONS_PER_FAMILY 16

/**
 * @brief Solution family characteristics and metadata
 *
 * Describes the mathematical approach and characteristics shared
 * by all implementations within a solution family.
 */
typedef struct
{
    char name[MATH_MAX_NAME_LENGTH];                      /**< Family name */
    char description[MATH_MAX_DESCRIPTION_LENGTH];        /**< Detailed description */
    char mathematical_basis[MATH_MAX_DESCRIPTION_LENGTH]; /**< Mathematical foundation */

    MathAlgorithmFamily family_type;         /**< Primary algorithm family */
    MathComplexity typical_time_complexity;  /**< Typical time complexity */
    MathComplexity typical_space_complexity; /**< Typical space complexity */

    bool supports_parallel_execution; /**< Can run in parallel */
    bool requires_preprocessing;      /**< Needs data preprocessing */
    bool is_deterministic;            /**< Always produces same result */
    bool handles_edge_cases_well;     /**< Robust with edge cases */

    MathNatural optimal_input_size_min; /**< Optimal input range minimum */
    MathNatural optimal_input_size_max; /**< Optimal input range maximum */
} SolutionFamilyMetadata;

/**
 * @brief Configuration for solution family operations
 *
 * Controls behavior of the solution family, including automatic
 * implementation selection and execution parameters.
 */
struct SolutionConfig
{
    bool auto_select_implementation;      /**< Enable automatic selection */
    bool prefer_speed_over_accuracy;      /**< Prioritize speed vs accuracy */
    bool prefer_memory_efficiency;        /**< Prioritize memory usage */
    bool enable_fallback_implementations; /**< Use fallbacks on failure */
    bool collect_comparative_metrics;     /**< Collect comparison data */

    MathNatural max_parallel_implementations; /**< Max parallel executions */
    double selection_timeout_ms;              /**< Timeout for selection process */

    ImplementationConfig default_impl_config; /**< Default config for implementations */
};

/**
 * @brief Implementation selection criteria
 *
 * Criteria used for automatic selection of the best implementation
 * for given input characteristics and requirements.
 */
typedef struct
{
    MathNatural input_magnitude;        /**< Size/magnitude of input */
    bool prioritize_speed;              /**< Speed is primary concern */
    bool prioritize_accuracy;           /**< Accuracy is primary concern */
    bool prioritize_memory;             /**< Memory usage is primary concern */
    bool require_deterministic;         /**< Must be deterministic */
    bool require_thread_safe;           /**< Must be thread-safe */
    double available_time_budget_ms;    /**< Available execution time */
    MathNatural available_memory_bytes; /**< Available memory */
} SelectionCriteria;

// ============================================================================
// SOLUTION FAMILY FUNCTION SIGNATURES
// ============================================================================

/**
 * @brief Implementation selection function signature
 *
 * Selects the best implementation from the family based on
 * input characteristics and selection criteria.
 *
 * @param family Solution family
 * @param input Input parameters
 * @param criteria Selection criteria
 * @return Pointer to selected implementation, NULL if none suitable
 */
typedef const ImplementationSpec *(*SolutionSelectFunc)(
    const SolutionFamily *family,
    const MathBinaryInput *input,
    const SelectionCriteria *criteria);

/**
 * @brief Family initialization function signature
 *
 * Initializes all implementations within the family and
 * prepares the family for use.
 *
 * @param family Solution family to initialize
 * @param config Configuration parameters
 * @return MATH_SUCCESS if initialization successful
 */
typedef MathStatus (*SolutionInitFunc)(
    SolutionFamily *family,
    const SolutionConfig *config);

/**
 * @brief Family cleanup function signature
 *
 * Cleans up all implementations and releases resources
 * used by the solution family.
 *
 * @param family Solution family to clean up
 * @return MATH_SUCCESS if cleanup successful
 */
typedef MathStatus (*SolutionCleanupFunc)(
    SolutionFamily *family);

/**
 * @brief Implementation registration function signature
 *
 * Registers a new implementation with the solution family.
 *
 * @param family Solution family
 * @param implementation Implementation to register
 * @return MATH_SUCCESS if registration successful
 */
typedef MathStatus (*SolutionRegisterFunc)(
    SolutionFamily *family,
    ImplementationSpec *implementation);

// ============================================================================
// SOLUTION FAMILY STRUCTURE
// ============================================================================

/**
 * @brief Complete specification for a solution family
 *
 * Contains all implementations, metadata, and management functions
 * for a family of related algorithm implementations.
 */
struct SolutionFamily
{
    // Metadata
    SolutionFamilyMetadata metadata;

    // Implementations registry
    ImplementationSpec *implementations[MAX_IMPLEMENTATIONS_PER_FAMILY];
    MathNatural implementation_count;

    // Function pointers
    SolutionSelectFunc select_implementation;
    SolutionInitFunc initialize;
    SolutionCleanupFunc cleanup;
    SolutionRegisterFunc register_implementation;

    // Configuration and state
    SolutionConfig config;
    bool is_initialized;
    MathNatural total_executions;

    // Performance tracking
    MathPerformanceMetrics family_performance;
    double last_selection_time_ms;
};

// ============================================================================
// SOLUTION FAMILY INTERFACE FUNCTIONS
// ============================================================================

/**
 * @brief Initialize a solution family with default values
 *
 * @param family Pointer to solution family to initialize
 * @param name Name of the solution family
 * @param family_type Type of algorithm family
 * @return MATH_SUCCESS if initialization successful
 */
MathStatus solution_family_init(
    SolutionFamily *family,
    const char *name,
    MathAlgorithmFamily family_type);

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
 * @brief Execute the best implementation for given input
 *
 * Automatically selects and executes the most suitable implementation
 * based on input characteristics and family configuration.
 *
 * @param family Solution family
 * @param input Input parameters
 * @param criteria Selection criteria (NULL for defaults)
 * @return MathResult with computation result and metadata
 */
MathResult solution_family_execute(
    SolutionFamily *family,
    const MathBinaryInput *input,
    const SelectionCriteria *criteria);

/**
 * @brief Execute all implementations and compare results
 *
 * Runs all suitable implementations and provides comparative analysis.
 * Useful for benchmarking and validation purposes.
 *
 * @param family Solution family
 * @param input Input parameters
 * @param results Array to store results (must have space for all implementations)
 * @param max_results Maximum number of results to store
 * @return Number of implementations executed
 */
MathNatural solution_family_execute_all(
    SolutionFamily *family,
    const MathBinaryInput *input,
    MathResult *results,
    MathNatural max_results);

/**
 * @brief Select the best implementation for given criteria
 *
 * @param family Solution family
 * @param input Input parameters
 * @param criteria Selection criteria
 * @return Pointer to selected implementation, NULL if none suitable
 */
const ImplementationSpec *solution_family_select_best(
    const SolutionFamily *family,
    const MathBinaryInput *input,
    const SelectionCriteria *criteria);

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
 * @brief Get performance metrics for the entire solution family
 *
 * @param family Solution family
 * @return Copy of family performance metrics
 */
MathPerformanceMetrics solution_family_get_performance(
    const SolutionFamily *family);

/**
 * @brief Reset performance metrics for all implementations in family
 *
 * @param family Solution family
 */
void solution_family_reset_performance(
    SolutionFamily *family);

// ============================================================================
// SELECTION CRITERIA UTILITIES
// ============================================================================

/**
 * @brief Create default selection criteria
 *
 * @param input_magnitude Size/magnitude of the input
 * @return Default selection criteria for the given input size
 */
SelectionCriteria solution_create_default_criteria(
    MathNatural input_magnitude);

/**
 * @brief Create speed-optimized selection criteria
 *
 * @param input_magnitude Size/magnitude of the input
 * @return Selection criteria optimized for speed
 */
SelectionCriteria solution_create_speed_criteria(
    MathNatural input_magnitude);

/**
 * @brief Create accuracy-optimized selection criteria
 *
 * @param input_magnitude Size/magnitude of the input
 * @return Selection criteria optimized for accuracy
 */
SelectionCriteria solution_create_accuracy_criteria(
    MathNatural input_magnitude);

/**
 * @brief Create memory-optimized selection criteria
 *
 * @param input_magnitude Size/magnitude of the input
 * @return Selection criteria optimized for memory usage
 */
SelectionCriteria solution_create_memory_criteria(
    MathNatural input_magnitude);

// ============================================================================
// UTILITY MACROS FOR SOLUTION FAMILY DEFINITION
// ============================================================================

/**
 * @brief Macro to define solution family metadata
 */
#define SOLUTION_FAMILY_METADATA(name, desc, basis, family_type, time_comp, space_comp) { \
    .name = name,                                                                         \
    .description = desc,                                                                  \
    .mathematical_basis = basis,                                                          \
    .family_type = family_type,                                                           \
    .typical_time_complexity = time_comp,                                                 \
    .typical_space_complexity = space_comp,                                               \
    .supports_parallel_execution = false,                                                 \
    .requires_preprocessing = false,                                                      \
    .is_deterministic = true,                                                             \
    .handles_edge_cases_well = true,                                                      \
    .optimal_input_size_min = 1,                                                          \
    .optimal_input_size_max = UINT64_MAX}

/**
 * @brief Macro to define default solution configuration
 */
#define SOLUTION_DEFAULT_CONFIG {            \
    .auto_select_implementation = true,      \
    .prefer_speed_over_accuracy = false,     \
    .prefer_memory_efficiency = false,       \
    .enable_fallback_implementations = true, \
    .collect_comparative_metrics = true,     \
    .max_parallel_implementations = 1,       \
    .selection_timeout_ms = 100.0,           \
    .default_impl_config = IMPLEMENTATION_DEFAULT_CONFIG}

#endif // SOLUTION_INTERFACE_H