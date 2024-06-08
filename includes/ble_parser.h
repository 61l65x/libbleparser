#ifndef BLE_PARSER_H
# define BLE_PARSER_H

# include "assigned_numbers.h"
# include "ble_data_structs.h"
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

#endif // BLE_PARSER_H
