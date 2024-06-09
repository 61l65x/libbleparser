
#include "ble_parser.h"

int					parse_all_yaml(t_le_adv_data_repository *repo);
void                print_class_of_device(t_le_class_of_device *cod);

int	main(void)
{
	t_ble_parser	*parser;
	t_le_ad_types	*ad_type;

	parser = init_ble_parser();
	if (parse_all_yaml(&parser->repo) != 0)
	{
		fprintf(stderr,
			"Failed to initialize LE advertising data repository\n");
		return (-1);
	}
	// Access the parsed data
	ad_type = parser->repo.ad_types;
	while (ad_type)
	{
		printf("AD Type: 0x%02x, Name: %s\n", ad_type->type, ad_type->name);
		ad_type = ad_type->next;
	}
	//print_manufacturer_tree(parser->repo.implemented_ad_types.root);
	//print_class_of_device(&parser->repo.implemented_ad_types.cod);
	// Cleanup
	destroy_ble_parser(parser);
	return (0);
}
