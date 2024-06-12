#include "assigned_numbers.h"
#include "ble_parser.h"
#include <linux/limits.h>

int		parse_ad_types_yaml(t_le_adv_data_repository *repo,
			const char *file_path);
int		create_manufacturer_tree(const char *file,
			t_le_manufacturer_data **root);
int		parse_class_of_device(const char *file_path, t_le_class_of_device *cod);

void	init_yaml_paths(t_yaml_paths *paths)
{
	const char	*lib_path = "/libbleparser";
	char		base_path[PATH_MAX] = {0};
	const char	*pwd = getenv("PWD");
	char		*pos;

	pos = NULL;
	if (pwd)
	{
		pos = strstr(pwd, lib_path);
	}
	if (pos)
	{
		strncpy(base_path, pwd, PATH_MAX);
	}
	else
	{
		snprintf(base_path, PATH_MAX, "%s/libbleparser", pwd ? pwd : ".");
	}
	snprintf(paths->ad_types_path, PATH_MAX, "%s/%s", base_path,
		LE_REPO_AD_TYPES_PATH);
	snprintf(paths->company_identifiers_path, PATH_MAX, "%s/%s", base_path,
		LE_REPO_COMPANY_IDENTIFIERS_PATH);
	snprintf(paths->cod_path, PATH_MAX, "%s/%s", base_path, LE_REPO_COD_PATH);
	printf("ad_types_path: %s\n", paths->ad_types_path);
	printf("company_identifiers_path: %s\n", paths->company_identifiers_path);
	printf("cod_path: %s\n", paths->cod_path);
}

int	parse_all_yaml(t_le_adv_data_repository *repo)
{
	t_le_ad_types *ad_type;
	t_yaml_paths yaml_paths = {0};

	repo->ad_types = NULL;
	repo->num_le_adv_data = 0;
	init_yaml_paths(&yaml_paths);
	if (parse_ad_types_yaml(repo, yaml_paths.ad_types_path) != 0)
	{
		return (-1);
	}
	ad_type = repo->ad_types;
	while (ad_type)
	{
		switch (ad_type->type)
		{
		case AD_TYPE_MANUFACTURER_SPECIFIC_DATA:
			if (create_manufacturer_tree(yaml_paths.company_identifiers_path,
					&repo->implemented_ad_types.root) != 0)
				return (-1);
			break ;
		case AD_TYPE_CLASS_OF_DEVICE:
			if (parse_class_of_device(yaml_paths.cod_path,
					&repo->implemented_ad_types.cod) != 0)
				return (-1);
			break ;
		default:
			break ;
		}
		ad_type = ad_type->next;
	}
	return (0);
}