#include "chump.h"

#define CHUMP_STATUS(CHOOSE_FUNC) \
	CHOOSE_FUNC(SUCCESS = CHUMP_SUCCESS, "chump - success") \
	CHOOSE_FUNC(FAILURE = CHUMP_FAILURE, "chump - generic failure") \

#define CHUMP_CHOOSE_ENUM(ENUM, STRING) ENUM,
#define CHUMP_CHOOSE_STRING(ENUM, STRING) STRING,

enum chump_status_t {
	CHUMP_STATUS(CHUMP_CHOOSE_ENUM)
};

const char* status_strings[] = { CHUMP_STATUS(CHUMP_CHOOSE_STRING) };

const char* chump_get_status_string(chump_status_t status) {
	return status_strings[status];
}


