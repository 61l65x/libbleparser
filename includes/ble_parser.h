#ifndef BLE_PARSER_H
# define BLE_PARSER_H

# include "data_structs.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <yaml.h>

# define LE_REPO_PATH "repository/public/"
# define LE_REPO_AD_TYPES_PATH "repository/assigned_numbers/core/ad_types.yaml"
# define LE_REPO_COMPANY_IDENTIFIERS_PATH "repository/assigned_numbers/company_identifiers/company_identifiers.yaml"
# define LE_REPO_COD_PATH "repository/assigned_numbers/core/class_of_device.yaml"

typedef struct s_le_adv_data_repository
{
	t_le_ad_types				*ad_types;
	t_le_implemented_ad_types	implemented_ad_types;
	int							num_le_adv_data;
}								t_le_adv_data_repository;

typedef struct s_ble_parser
{
	t_le_adv_data_repository	repo;
}								t_ble_parser;

// Functions
int								parse_all_yaml(t_le_adv_data_repository *repo);
void							free_le_adv_data_repository(t_le_adv_data_repository *repo);
void							print_adv_data_redable(t_le_adv_data_repository *repo, uint8_t *data, size_t len);
void							destroy_ble_parser(t_ble_parser *parser);
t_ble_parser					*init_ble_parser(void);

#endif // BLE_PARSER_H
