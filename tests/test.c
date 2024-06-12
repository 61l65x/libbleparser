#include "ble_parser.h"
int	main(void)
{
	t_ble_parser	*parser;
	t_le_ad_types	*ad_type;

	parser = init_ble_parser();
	// Access the parsed data
	ad_type = parser->repo.ad_types;
	while (ad_type)
	{
		printf("AD Type: 0x%02x, Name: %s\n", ad_type->type, ad_type->name);
		ad_type = ad_type->next;
	}
	print_manufacturer_tree(parser->repo.implemented_ad_types.root);
	print_class_of_device(&parser->repo.implemented_ad_types.cod);
	// Cleanup
	destroy_ble_parser(parser);
	return (0);
}
