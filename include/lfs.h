#include "lfs.h"

// Configuration of the filesystem
struct lfs_config cfg = {
    // block device operations
    .read  = block_device_read,
    .prog  = block_device_prog,
    .erase = block_device_erase,
    .sync  = block_device_sync,

    // block device configuration
    .block_size = 4096,
    .block_count = 64,
    .cache_size = 64,
    .lookahead_size = 64,
};

// Variables used by LittleFS
lfs_t lfs;
lfs_file_t file;

void init_filesystem() {
    // Initialize filesystem
    int err = lfs_mount(&lfs, &cfg);

    // Reformat if we can't mount the filesystem
    if (err) {
        printf("Failed to mount filesystem, formatting...\n");
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }
}

// Function to write the default wifi_credentials.txt if it doesn't exist
void write_default_wifi_credentials() {
    const char *default_credentials =
        "SSID:Your_SSID\n"
        "PASSWORD:Your_PASSWORD\n";

    // Check if file exists
    if (lfs_stat(&lfs, "wifi_credentials.txt", NULL) != 0) {
        // File doesn't exist, create it
        lfs_file_open(&lfs, &file, "wifi_credentials.txt", LFS_O_WRONLY | LFS_O_CREAT);
        lfs_file_write(&lfs, &file, default_credentials, strlen(default_credentials));
        lfs_file_close(&lfs, &file);
        printf("Created wifi_credentials.txt with default values\n");
    } else {
        printf("wifi_credentials.txt already exists\n");
    }
}