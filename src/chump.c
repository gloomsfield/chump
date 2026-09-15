#include "chump.h"

#include <stdint.h>

#ifndef CHUMP_CAPACITY
#define CHUMP_CAPACITY 8
#endif

#define STRINGIFY_INNER(VALUE) #VALUE
#define STRINGIFY(VALUE) STRINGIFY_INNER(VALUE)

#define CHUMP_STATUS(CHOOSE_FUNC) \
	CHOOSE_FUNC(SUCCESS = CHUMP_SUCCESS, "chump - success") \
	CHOOSE_FUNC(FAILURE = CHUMP_FAILURE, "chump - generic failure") \
	CHOOSE_FUNC(BUFFER_CAPACITY_MISALIGNED, "chump - invalid buffer capacity during hibuf creation, please ensure it is a multiple of " STRINGIFY(CHUMP_CAPACITY)) \
	CHOOSE_FUNC(HANDLE_CAPACITY_MISALIGNED, "chump - invalid handle capacity during hibuf creation, please ensure it is a multiple of " STRINGIFY(CHUMP_CAPACITY)) \

#define CHUMP_CHOOSE_ENUM(ENUM, STRING) ENUM,
#define CHUMP_CHOOSE_STRING(ENUM, STRING) STRING,

enum chump_status_t {
	CHUMP_STATUS(CHUMP_CHOOSE_ENUM)
};

const char* status_strings[] = { CHUMP_STATUS(CHUMP_CHOOSE_STRING) };

typedef struct chump_handle_t {
	uint16_t reference_address_index;
} chump_handle_t;

typedef struct chump_hibuf_t {
	uint32_t capacity;
	uint32_t element_size;

	chump_handle_t* valid_handles;

	void* buffer;
} chump_hibuf_t;

const char* chump_get_status_string(chump_status_t status) {
	return status_strings[status];
}

const uint32_t sizeof_chump_hibuf_t(uint32_t handle_capacity) {
	return (handle_capacity * sizeof(chump_handle_t) + sizeof(chump_hibuf_t));
}

chump_status_t chump_hibuf_create(chump_hibuf_creation_info_t info, chump_hibuf_t* chump) { return FAILURE; }
chump_status_t chump_hibuf_destroy(chump_hibuf_t* chump) { return FAILURE; }

chump_status_t chump_occupy(chump_hibuf_t* chump, void* data, chump_handle_t* handle) { return FAILURE; }
chump_status_t chump_vacate(chump_hibuf_t* chump, chump_handle_t* handle) { return FAILURE; }

chump_status_t chump_get(chump_hibuf_t* chump, chump_handle_t* handle, void* result) { return FAILURE; }
chump_status_t chump_set(chump_hibuf_t* chump, chump_handle_t* handle, void* value) { return FAILURE; }
