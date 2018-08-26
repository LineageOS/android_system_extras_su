/*
** Copyright 2012, The CyanogenMod Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/

#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "utils.h"

/* reads a file, making sure it is terminated with \n \0 */
char* read_file(const char* fn) {
    struct stat st;
    char* data = NULL;

    int fd = open(fn, O_RDONLY);
    if (fd < 0) return data;

    if (fstat(fd, &st)) goto oops;

    data = malloc(st.st_size + 2);
    if (!data) goto oops;

    if (read(fd, data, st.st_size) != st.st_size) goto oops;
    close(fd);
    data[st.st_size] = '\n';
    data[st.st_size + 1] = 0;
    return data;

oops:
    close(fd);
    if (data) free(data);
    return NULL;
}
