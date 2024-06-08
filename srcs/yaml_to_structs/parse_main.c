#include "ble_parser.h"

int	parse_ad_types_yaml(t_le_adv_data_repository *repo, const char *file_path);
int create_manufacturer_tree(t_le_manufacturer_data **root);

int	parse_all_yaml(t_le_adv_data_repository *repo)
{
	yaml_parser_t yaml_parser;
	t_le_ad_types *ad_type;

	repo->ad_types = NULL;
	repo->num_le_adv_data = 0;

	if (parse_ad_types_yaml(repo, LE_REPO_AD_TYPES_PATH) != 0)
	{
		yaml_parser_delete(&yaml_parser);
		return (-1);
	}
	ad_type = repo->ad_types;
	while (ad_type)
	{
		switch (ad_type->type)
		{
		case AD_TYPE_MANUFACTURER_SPECIFIC_DATA:
			if (create_manufacturer_tree(&repo->implemented_ad_types.manufacturer_data) != 0)
				return (-1);
			break ;
		// case AD_TYPE_CLASS_OF_DEVICE:
		// 	if (init_yaml_parser(LE_COD_PATH, &yaml_parser) != 0
		// 		|| parse_class_of_device(LE_COD_PATH,
		// 			&ad_type->implemented_ad_types->cod, &yaml_parser) != 0)
		// 	{
		// 		yaml_parser_delete(&yaml_parser);
		// 		return (-1);
		// 	}
		// 	yaml_parser_delete(&yaml_parser);
		// 	break ;
		default:
			break ;
		}
		ad_type = ad_type->next;
	}

	return (0);
}