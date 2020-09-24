#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    struct t_config
    {
        const char* const host;
        const char* const port;
        const char* const db;
        const char* const user;
        const char* const pass;
        const char* const query;
    };

    typedef struct t_config Config;

    int describe(const Config* config);

#ifdef __cplusplus
}
#endif
