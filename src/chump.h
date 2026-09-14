#pragma once

#define CHUMP_FAILURE (0)
#define CHUMP_SUCCESS (1)

typedef struct chump_t chump_t;

typedef enum chump_status_t chump_status_t;

const char* chump_get_status_string(chump_status_t status);
