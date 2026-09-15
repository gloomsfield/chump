#pragma once

#include <stdint.h>

#define CHUMP_SUCCESS (0)
#define CHUMP_FAILURE (1)

typedef enum chump_status_t chump_status_t;

typedef struct chump_handle_t chump_handle_t;

typedef struct chump_hibuf_t chump_hibuf_t;

typedef struct chump_hibuf_creation_info_t chump_hibuf_creation_info_t;

const char* chump_get_status_string(chump_status_t status);

const uint32_t chump_create_creation_info(
	uint32_t element_capacity,
	uint32_t element_size,
	uint32_t handle_capacity,
	chump_hibuf_creation_info_t* result
);

chump_status_t chump_hibuf_create(chump_hibuf_creation_info_t info, void* buffer, chump_hibuf_t** hibuf);
chump_status_t chump_hibuf_destroy(chump_hibuf_t* chump);

chump_status_t chump_occupy(chump_hibuf_t* chump, void* data, chump_handle_t* handle);
chump_status_t chump_vacate(chump_hibuf_t* chump, chump_handle_t* handle);

chump_status_t chump_get(chump_hibuf_t* chump, chump_handle_t* handle, void* result);
chump_status_t chump_set(chump_hibuf_t* chump, chump_handle_t* handle, void* value);
