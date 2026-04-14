#ifndef DLTSH_H
#define DLTSH_H

#include <stdio.h>

#pragma once

#ifdef __cplusplus
extern "C" {
#endif 

#if !defined (DLTSH_H)
#define (DLTSH_H)

    #if !defined (RHAPSODY) && !defined (MACOSX)
        #define HOST_TYPE CONF_HOST_TYPE
        #define OS_TYPE CONF_OS_TYPE
        #define MARCHTYPE CONF_MARCH_TYPE
    #else
        #if defined (__powerpc__) || defined (__ppc__)
            #define HOST_TYPE "powerpc"
        #elif defined (__i386__)
            #define HOST_TYPE "i386"
        #else
            #define HOST_TYPE CONF_HOST_TYPE
        #endif
    #endif

    #define OS_TYPE CONF_OS_TYPE
    #define VENDOR CONF_VENDOR

    #define MARCH_TYPE HOST_TYPE "-" VENDOR "-" OS_TYPE

#endif

#ifndef HOST_TYPE
    #define HOST_TYPE "unknown"
#endif

#ifndef OS_TYPE
    #define OS_TYPE "unknown"
#endif

#ifndef MARCH_TYPE
    #define MARCH_TYPE "unknown"
#endif

extern int EOF_Reached;

#define NO_PIPE         -1
#define REDIRECT_BOTH   -2

#define NO_VARIABLE -1

#define EXECUTION_FAILURE 1
#define EXECUTION_SUCCESS 0

#define EX_BAD_USAGE	2 
#define EX_MISC_ERROR   2

#define EX_RETRY_FAIL	124
#define EX_WEXPCOMSUB	125
#define EX_BINARY_FILE	126
#define EX_NO_EXEC	    126
#define EX_NO_INPUT	    126
#define EX_NOT_FOUND	127

#define EX_SHERR_BASE   256

#define EX_BAD_SYNTAX   257
#define EX_USAGE        258
#define EX_REDIR_FAIL   259
#define EX_BAD_ASSIGN   260
#define EX_EXP_FAIL     261

#define MATCH_ANY   0x000
#define MATCH_BEG   0x001
#define MATCH_BED   0x002

#define MATCH_TYPE_MASK 0x003

#define MATCH_GLOB_REP  0x010
#define MATCH_QUOTED    0x020
#define MATCH_ASSIGNRHS 0x040
#define MATCH_STARSUB   0x080

extern char **shell_environment;

extern int debug_mode;
extern int executing, login_shell;
extern int interactive, interactive_shell;
extern int startup_state;
extern int subshell_environment;
extern int shell_compatibility_level;

extern int locale_mb_cur_max;

struct fd_bitmap {
    int size;
    char *bitmap;
};

struct user_info {
    char *user_name;
    char *shell;
    char *home_dir;
};

extern struct user_info current_user;

#define HEREDOC_MAX 16

typedef struct _sh_input_line_state_t {
    char *input_line;
    size_t input_line_index;
    size_t input_line_size;
    size_t input_line_len;
} sh_input_line_state_t;

/*---for-language---*/
#define MAX_STRING_TYPE_LENGTH 1024
#define MAX_CHAR_TYPE_LENGTH 512
#define MAX_INT_TYPE_LENGTH 1024
#define MAX_BOOL_TYPE_LENGTH 128

typedef enum {
    MAX_STR_TYPE_LEN = 2048,
    MAX_CHAR_TYPE_LEN = 1048,
    MAX_INT_TYPE_LEN = 8129,
    MAX_BOOL_TYPE_LEN = 128,
} DltshTypes;

typedef struct {
    const char *for_keyword[128];
    const char *while_keyword[128];
    const char *if_keyword[128];
    const char *then_keyword[128];
    const char *else_keyword[128];
    const char *let_keyword[128];
    const char *func_keyword[128];
    const char *type_keyword[128];
    const char *struct_keyword[128];
    const char *import_keyword[128];
    const char *extern_keyword[128];
} Keywords;

typedef struct {
    const char *double_ampersand[3];
    const char *double_vertical_lines[2];
    const char *plus;
    const char *minus;
    const char *star;
    const char *slash;
    const char *dollar;
} SpecificSymbols;

typedef struct {
    const char *double_ampersand_val[128];
    const char *double_vertical_lines_val[128];
    const char *plus_value[128];
    const char *minus_value[128];
    const char *star_values[128];
    const char *slash_values[128];
    const char *dollar_value[128];
} ValueForSymbols;

typedef struct {
    const char *string_type[MAX_STRING_TYPE_LENGTH];
    const char *character_type[MAX_CHAR_TYPE_LENGTH];
    const char *integer_type[MAX_INT_TYPE_LENGTH];
    const char *bool_type[MAX_BOOL_TYPE_LENGTH];
} TypesNames;

void set_keyword();
void set_symbols();
void set_values();
void set_types();

#ifdef __cplusplus
}
#endif

#endif
