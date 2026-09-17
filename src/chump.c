#include "chump.h"

#include <stdint.h>
#include <string.h>

#ifndef CHUMP_SLOT_COUNT
#define CHUMP_SLOT_COUNT 8
#endif

#define STRINGIFY_INNER(VALUE) #VALUE
#define STRINGIFY(VALUE) STRINGIFY_INNER(VALUE)

#define CHUMP_STATUS(CHOOSE_FUNC) \
	CHOOSE_FUNC(SUCCESS = CHUMP_SUCCESS, "chump - success") \
	CHOOSE_FUNC(FAILURE = CHUMP_FAILURE, "chump - generic failure") \
	CHOOSE_FUNC(NULL_HIBUF_PTR, "chump - chump_hibuf_t pointer was null") \
	CHOOSE_FUNC(INVALID_ELEMENT_SIZE, "chump - invalid element size passed to hibuf creation, please ensure it is greater than 0") \

#define CHUMP_CHOOSE_ENUM(ENUM, STRING) ENUM,
#define CHUMP_CHOOSE_STRING(ENUM, STRING) STRING,

enum chump_status_t {
	CHUMP_STATUS(CHUMP_CHOOSE_ENUM)
};

const char* status_strings[] = { CHUMP_STATUS(CHUMP_CHOOSE_STRING) };

typedef uint16_t offset_t;

typedef struct chump_t {
	uint32_t occupied_slot_count;
	void* data;
} chump_t;

struct chump_hibuf_t {
	uint32_t chump_capacity;

	chump_t* element_chumps;
	chump_t* handle_chumps;
	
	offset_t* offsets;
};

struct chump_hibuf_creation_info_t {
	uint32_t chump_capacity;

	uint32_t element_capacity;
	uint32_t element_size;

	uint32_t handle_capacity;

	uint32_t total_size;
};

struct chump_handle_t {
	uint16_t reference_address_index;
};

const char* chump_get_status_string(chump_status_t status) {
	return status_strings[status];
}

const uint32_t chump_create_creation_info(
	uint32_t element_capacity,
	uint32_t element_size,
	uint32_t handle_capacity,
	chump_hibuf_creation_info_t* result
) {
	uint32_t total = 0;

	uint32_t chump_capacity = 1 + ((2 * element_capacity - 1) / (2 * CHUMP_SLOT_COUNT));
	
	// size of the element buffer
	total += chump_capacity * CHUMP_SLOT_COUNT * element_size;

	// size of the element chumps
	total += chump_capacity * sizeof(chump_t);

	// size of the handle buffer
	total += handle_capacity * sizeof(chump_handle_t);

	// size of the handle chumps
	total += handle_capacity * sizeof(chump_t);

	// size of the offset buffer
	total += chump_capacity * sizeof(offset_t);

	// size of the hibuf itself
	total += sizeof(chump_hibuf_t);

	*result = (chump_hibuf_creation_info_t){
		.chump_capacity = chump_capacity,
		.element_capacity = element_capacity,
		.element_size = element_size,
		.handle_capacity = handle_capacity,
		.total_size = total,
	};

	return total;
}

void initialize_element_chumps(chump_hibuf_creation_info_t info, uint32_t* index_into_buffer, void* buffer, chump_hibuf_t* hibuf) {
	for(int i = 0; i < info.chump_capacity; i++) {
		chump_t new_chump = { .occupied_slot_count = 0, .data = ??? };

		memcpy(&(buffer[*index_into_buffer]), &new_chump, sizeof(chump_t));

		*index_into_buffer += sizeof(chump_t);
	}
}

uint32_t advance_index(uint32_t* index, uint32_t amount) {
	uint32_t old_index = *index;

	*index += amount;

	return old_index;
}

chump_status_t chump_hibuf_create(chump_hibuf_creation_info_t info, void* buffer, chump_hibuf_t** hibuf) {
	if(!hibuf) { return NULL_HIBUF_PTR; }
	if(info.element_size < 1) { return INVALID_ELEMENT_SIZE; }

	uint32_t index_into_buffer = 0;

	(*hibuf) = &(buffer[advance_index(&index_into_buffer, sizeof(chump_hibuf_t))]);

	(*hibuf)->chump_capacity = info.chump_capacity;
	(*hibuf)->element_chumps = &(buffer[advance_index(&index_into_buffer, sizeof(chump_t) * info.chump_capacity)]);
	(*hibuf)->handle_chumps = &(buffer[advance_index(&index_into_buffer, sizeof(chump_handle_t) * info.handle_capacity)]);
	(*hibuf)->offsets = &(buffer[advance_index(&index_into_buffer, sizeof(offset_t) * info.chump_capacity)]);

	return SUCCESS;
}

chump_status_t chump_hibuf_destroy(chump_hibuf_t* chump) { return FAILURE; }

chump_status_t chump_occupy(chump_hibuf_t* chump, void* data, chump_handle_t* handle) { return FAILURE; }
chump_status_t chump_vacate(chump_hibuf_t* chump, chump_handle_t* handle) { return FAILURE; }

chump_status_t chump_get(chump_hibuf_t* chump, chump_handle_t* handle, void* result) { return FAILURE; }
chump_status_t chump_set(chump_hibuf_t* chump, chump_handle_t* handle, void* value) { return FAILURE; }
