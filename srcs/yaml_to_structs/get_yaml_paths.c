// Helper function to check if a directory exists
#include "ble_parser.h"
#include <dirent.h>
#include <libgen.h>
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int	directory_exists(const char *path)
{
	struct stat	st;

	return (stat(path, &st) == 0 && S_ISDIR(st.st_mode));
}

int	find_libbleparser(char *base_path, size_t size)
{
	char	test_path[PATH_MAX] = {0};
	char	*slash;

	if (directory_exists(base_path))
	{
		snprintf(test_path, PATH_MAX, "%s/libbleparser", base_path);
		if (directory_exists(test_path))
		{
			strncat(base_path, "/libbleparser", size - strlen(base_path) - 1);
			return (1);
		}
	}
	slash = strrchr(base_path, '/');
	if (slash)
	{
		*slash = '\0';
		return (find_libbleparser(base_path, size));
	}
	return (0);
}

void	init_yaml_paths(t_yaml_paths *paths)
{
	char exe_path[PATH_MAX] = {0};
	char base_path[PATH_MAX] = {0};
	const ssize_t count = readlink("/proc/self/exe", exe_path, PATH_MAX);

	if (count == -1)
	{
		perror("readlink");
		exit(EXIT_FAILURE);
	}
	exe_path[count] = '\0';
	strcpy(base_path, dirname(exe_path));
	if (!find_libbleparser(base_path, PATH_MAX))
	{
		fprintf(stderr, "libbleparser directory not found\n");
		exit(EXIT_FAILURE);
	}
	// Construct paths relative to the base path
	snprintf(paths->ad_types_path, PATH_MAX, "%s/%s", base_path,
		LE_REPO_AD_TYPES_PATH);
	snprintf(paths->company_identifiers_path, PATH_MAX, "%s/%s", base_path,
		LE_REPO_COMPANY_IDENTIFIERS_PATH);
	snprintf(paths->cod_path, PATH_MAX, "%s/%s", base_path, LE_REPO_COD_PATH);
	printf("ad_types_path: %s\n", paths->ad_types_path);
	printf("company_identifiers_path: %s\n", paths->company_identifiers_path);
	printf("cod_path: %s\n", paths->cod_path);
}