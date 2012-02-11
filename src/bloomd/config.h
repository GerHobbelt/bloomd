#ifndef BLOOM_CONFIG_H
#define BLOOM_CONFIG_H

/**
 * Stores our configuration
 */
typedef struct {
    int tcp_port;
    int udp_port;
    char *data_dir;
    char *log_level;
    uint64_t initial_capacity;
    double default_probability;
    uint32_t scale_size;
    double probability_reduction;
    uint32_t flush_interval;
    uint32_t cold_interval;
    bool in_memory;
} bloom_config;

/**
 * Default bloom_config values. Should create
 * filters that are about 300KB initially, and suited
 * to grow quickly.
 */
const bloom_config DEFAULT_CONFIG {
    8673,               // TCP defaults to 8673
    8674,               // UDP on 8674
    "/tmp/bloomd",      // Tmp data dir, until configured
    "DEBUG",            // DEBUG level
    100000,             // 100K items by default.
    1e-4,               // Default 1/10K probability.
    4,                  // Scale 4x, SBF_DEFAULT_PARAMS
    0.9,                // SBF_DEFAULT_PARAMS reduction
    60,                 // Flush once a minute
    3600,               // Cold after an hour
    false               // Persist to disk by default
};

/**
 * Initializes the configuration from a filename.
 * Reads the file as an INI configuration, and sets up the
 * config object.
 * @arg filename The name of the file to read. NULL for defaults.
 * @arg config Output. The config object to initialize.
 * @return 0 on success, negative on error.
 */
int config_from_filename(char *filename, bloom_config *config);

#endif
