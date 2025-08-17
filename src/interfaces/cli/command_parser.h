/**
 * @file command_parser.h
 * @brief Command line interface parser for GCD algorithm analysis
 * @author Number Theory Algorithms Project
 * @version 1.0
 *
 * This header defines the command line interface for the GCD algorithm
 * analysis system. Provides parsing and execution of CLI commands.
 */

#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include "../../core/domain/mathematical_types.h"
#include "../../challenges/greatest_common_divisor/domain_types.h"
#include <stdbool.h>

// ============================================================================
// COMMAND DEFINITIONS
// ============================================================================

/**
 * @brief Available CLI commands
 */
typedef enum
{
    CMD_HELP,        /**< Show help information */
    CMD_LIST,        /**< List available algorithms */
    CMD_EXECUTE,     /**< Execute specific algorithm */
    CMD_COMPARE,     /**< Compare all algorithms */
    CMD_BENCHMARK,   /**< Run benchmark */
    CMD_EXTENDED,    /**< Execute Extended Euclidean */
    CMD_FASTEST,     /**< Find fastest algorithm */
    CMD_STATUS,      /**< Show system status */
    CMD_TEST,        /**< Run self-test */
    CMD_INTERACTIVE, /**< Interactive mode */
    CMD_UNKNOWN      /**< Unknown command */
} CliCommand;

/**
 * @brief Command argument structure
 */
typedef struct
{
    GcdInteger operand_a;
    GcdInteger operand_b;
    char algorithm_name[64];
    GcdAlgorithmVariant variant;
    MathNatural iterations;
    bool has_operands;
    bool has_algorithm;
    bool has_iterations;
    bool verbose;
} CommandArgs;

// ============================================================================
// PUBLIC FUNCTION DECLARATIONS
// ============================================================================

/**
 * @brief Parse command line arguments
 *
 * @param argc Argument count
 * @param argv Argument vector
 * @param args Pointer to store parsed arguments
 * @return Parsed command type
 */
CliCommand parse_arguments(int argc, char *argv[], CommandArgs *args);

/**
 * @brief Execute command based on parsed arguments
 *
 * @param command Command to execute
 * @param args Command arguments
 * @return Exit code (0 for success)
 */
int execute_command(CliCommand command, const CommandArgs *args);

/**
 * @brief Parse algorithm variant from string
 *
 * @param variant_str Variant string
 * @return Parsed algorithm variant
 */
GcdAlgorithmVariant parse_algorithm_variant(const char *variant_str);

/**
 * @brief Parse integer from string with error checking
 *
 * @param str String to parse
 * @param value Pointer to store parsed value
 * @return true if parsing successful
 */
bool parse_integer(const char *str, GcdInteger *value);

// ============================================================================
// COMMAND EXECUTION FUNCTIONS
// ============================================================================

/**
 * @brief Execute help command
 */
void execute_help_command(void);

/**
 * @brief Execute list command
 *
 * @param verbose Whether to show detailed information
 */
void execute_list_command(bool verbose);

/**
 * @brief Execute interactive mode
 */
void execute_interactive_mode(void);

#endif // COMMAND_PARSER_H