#include "ble_parser.h"

int					parse_all_yaml(t_le_adv_data_repository *repo);
void                print_class_of_device(t_le_class_of_device *cod);

t_ble_parser	*init_ble_parser(void)
{
	t_ble_parser	*parser;

	parser = calloc(1, sizeof(t_ble_parser));
	if (parser == NULL)
	{
		fprintf(stderr, "Failed to allocate memory for BLE parser\n");
		return (NULL);
	}
    if (parse_all_yaml(&parser->repo) != 0)
    {
        fprintf(stderr, "Failed to initialize LE advertising data repository\n");
        return (NULL);
    }
	return (parser);
}

void destroy_ble_parser(t_ble_parser *parser)
{
	free_le_adv_data_repository(&parser->repo);
	free(parser);
	parser = NULL;
}
