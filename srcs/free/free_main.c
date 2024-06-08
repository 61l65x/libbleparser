#include "ble_data_structs.h"
#include "ble_parser.h"

void	free_manufacturer_data(t_le_manufacturer_data *node)
{
	if (node == NULL)
		return ;
	free_manufacturer_data(node->left);
	free_manufacturer_data(node->right);
	free(node->name);
	free(node->proprietary_data);
	free(node);
}

void	free_class_of_device_list(t_le_class_of_device *cod)
{
	t_le_class_of_device	*next_cod;

	while (cod)
	{
		next_cod = cod->next;
		free(cod->major_class);
		free(cod->minor_class);
		free(cod);
		cod = next_cod;
	}
}

void	free_le_adv_data_repository(t_le_adv_data_repository *repo)
{
	t_le_ad_types	*current_ad_type;
	t_le_ad_types	*next_ad_type;

	current_ad_type = repo->ad_types;
	while (current_ad_type)
	{
		next_ad_type = current_ad_type->next;
		free(current_ad_type->name);
		free(current_ad_type->implemented_ad_types);
		free(current_ad_type);
		current_ad_type = next_ad_type;
	}
	free_manufacturer_data(repo->manufacturer_data);
	free_class_of_device_list(repo->cod);
	repo->ad_types = NULL;
	repo->manufacturer_data = NULL;
	repo->cod = NULL;
	repo->num_le_adv_data = 0;
}