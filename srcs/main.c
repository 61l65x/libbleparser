
#include "ble_parser.h"

int					parse_all_yaml(t_le_adv_data_repository *repo);

static t_ble_parser	*init_ble_parser(void)
{
	t_ble_parser	*parser;

	parser = calloc(1, sizeof(t_ble_parser));
	if (parser == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for BLE parser\n");
		return (NULL);
	}
	return (parser);
}

static void destroy_ble_parser(t_ble_parser *parser)
{
	free_le_adv_data_repository(&parser->repo);
	free(parser);
	parser = NULL;
}

void print_manufacturer_tree(t_le_manufacturer_data *node)
{
    if (node == NULL)
        return;
    print_manufacturer_tree(node->left);
    printf("ID: %04x, Name: %s\n", node->id, node->name);
    print_manufacturer_tree(node->right);
}

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
	print_manufacturer_tree(parser->repo.implemented_ad_types.manufacturer_data);
	// Cleanup
	destroy_ble_parser(parser);
	return (0);
}
