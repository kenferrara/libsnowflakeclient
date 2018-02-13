/*
 * Copyright (c) 2017-2018 Snowflake Computing, Inc. All rights reserved.
 */

#include <snowflake/logger.h>
#include "test_setup.h"

void initialize_test(sf_bool debug) {
    // default location and the maximum logging
    snowflake_global_init(NULL, SF_LOG_TRACE);

    snowflake_global_set_attribute(SF_GLOBAL_CA_BUNDLE_FILE, getenv("SNOWFLAKE_TEST_CA_BUNDLE_FILE"));
    snowflake_global_set_attribute(SF_GLOBAL_DEBUG, &debug);
}

SF_CONNECT *setup_snowflake_connection() {
    return setup_snowflake_connection_with_autocommit(
            "UTC", SF_BOOLEAN_TRUE);
}

SF_CONNECT *setup_snowflake_connection_with_autocommit(
        const char *timezone, sf_bool autocommit) {
    SF_CONNECT *sf = snowflake_init();

    snowflake_set_attribute(sf, SF_CON_ACCOUNT,
                            getenv("SNOWFLAKE_TEST_ACCOUNT"));
    snowflake_set_attribute(sf, SF_CON_USER, getenv("SNOWFLAKE_TEST_USER"));
    snowflake_set_attribute(sf, SF_CON_PASSWORD,
                            getenv("SNOWFLAKE_TEST_PASSWORD"));
    snowflake_set_attribute(sf, SF_CON_DATABASE,
                            getenv("SNOWFLAKE_TEST_DATABASE"));
    snowflake_set_attribute(sf, SF_CON_SCHEMA, getenv("SNOWFLAKE_TEST_SCHEMA"));
    snowflake_set_attribute(sf, SF_CON_ROLE, getenv("SNOWFLAKE_TEST_ROLE"));
    snowflake_set_attribute(sf, SF_CON_WAREHOUSE,
                            getenv("SNOWFLAKE_TEST_WAREHOUSE"));
    snowflake_set_attribute(sf, SF_CON_AUTOCOMMIT, &autocommit);
    snowflake_set_attribute(sf, SF_CON_TIMEZONE, timezone);
    char *host, *port, *protocol;
    host = getenv("SNOWFLAKE_TEST_HOST");
    if (host) {
        snowflake_set_attribute(sf, SF_CON_HOST, host);
    }
    port = getenv("SNOWFLAKE_TEST_PORT");
    if (port) {
        snowflake_set_attribute(sf, SF_CON_PORT, port);
    }
    protocol = getenv("SNOWFLAKE_TEST_PROTOCOL");
    if (protocol) {
        snowflake_set_attribute(sf, SF_CON_PROTOCOL, protocol);
    }
    return sf;
}

void dump_error(SF_ERROR_STRUCT *error) {
    fprintf(stderr, "Error code: %d, message: %s\nIn File, %s, Line, %d\n",
            error->error_code,
            error->msg,
            error->file,
            error->line);
}
