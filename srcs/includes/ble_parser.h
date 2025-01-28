#ifndef BLE_PARSER_H
#define BLE_PARSER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "./parse_yaml/data_structs.h"
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

#define LIB_NOT_FOUND \
	"Could not find libbleparser directory \
if you have changed the name of the library file please change it back to the original 'libbleparser' \n"

#define LE_REPO_AD_TYPES_PATH "srcs/repository/assigned_numbers/core/ad_types.yaml"
#define LE_REPO_COMPANY_IDENTIFIERS_PATH "srcs/repository/assigned_numbers/company_identifiers/company_identifiers.yaml"
#define LE_REPO_COD_PATH "srcs/repository/assigned_numbers/core/class_of_device.yaml"

typedef struct s_yaml_paths {
	char ad_types_path[PATH_MAX];
	char company_identifiers_path[PATH_MAX];
	char cod_path[PATH_MAX];
} t_yaml_paths;

typedef struct s_ParsedAdvData {
	t_ClassOfDeviceData cod_data;
	t_ManufacturerData manf_data;
} t_ParsedAdvData;

typedef struct s_le_adv_data_repository {
	t_le_ad_types *ad_types;
	t_le_implemented_ad_types implemented_ad_types;
	int num_le_adv_data;
} t_le_adv_data_repository;

typedef struct s_ble_parser {
	t_le_adv_data_repository repo;
} t_ble_parser;

// Functions
t_ParsedAdvData parse_adv_data(uint8_t *data, size_t len, t_ble_parser *parser);
int parse_all_yaml(t_le_adv_data_repository *repo);
void free_le_adv_data_repository(t_le_adv_data_repository *repo);
void print_adv_data_readable(t_ble_parser *parser, uint8_t *data, size_t len);
void destroy_ble_parser(t_ble_parser *parser);
t_ble_parser *init_ble_parser(void);
t_le_manufacturer_data *get_company_from_tree(t_le_manufacturer_data *node, int manufacturer_id);

void print_class_of_device(t_le_class_of_device *cod);
void print_manufacturer_tree(t_le_manufacturer_data *node);

#ifdef __cplusplus
}
#endif

#endif // BLE_PARSER_H
