#include "assigned_numbers.h"
#include "ble_parser.h"

int	parse_ad_types_yaml(t_le_adv_data_repository *repo, const char *file_path);
int	create_manufacturer_tree(const char *file, t_le_manufacturer_data **root);
int	parse_class_of_device(const char *file_path, t_le_class_of_device *cod);
int	init_yaml_paths(t_yaml_paths *paths);

int	parse_all_yaml(t_le_adv_data_repository *repo)
{
	t_le_ad_types *ad_type = NULL;
	t_yaml_paths yaml_paths = {0};

	repo->ad_types = NULL;
	repo->num_le_adv_data = 0;
	if (init_yaml_paths(&yaml_paths) != 0
		|| parse_ad_types_yaml(repo, yaml_paths.ad_types_path) != 0)
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
