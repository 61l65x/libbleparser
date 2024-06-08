
#include "ble_parser.h"

int					init_le_ad_types(t_le_adv_data_repository *repo);

static t_ble_parser	*init_ble_parser(void)
{
	t_ble_parser	*parser;

	parser = (t_ble_parser *)calloc(1, sizeof(t_ble_parser));
	if (parser == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for BLE parser\n");
		return (NULL);
	}
	return (parser);
}

int	main(void)
{
	t_ble_parser	*parser;
	t_le_ad_types	*ad_type;

	parser = init_ble_parser();
	if (init_le_ad_types(&parser->repo) != 0)
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
	// Cleanup
	free_le_adv_data_repository(&parser->repo);
	return (0);
}
