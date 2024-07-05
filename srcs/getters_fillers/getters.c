// Function to get manufacturer data by ID
#include "ble_parser.h"
#include "data_structs.h"

t_le_manufacturer_data	*get_company_from_tree(t_le_manufacturer_data *node,
		int manufacturer_id)
{
	t_le_manufacturer_data	*found_node;

	if (node == NULL)
		return (NULL);
	if (node->id == manufacturer_id)
	{
		printf("ID: %x, Name: %s\n", node->id, node->name);
		return (node);
	}
	found_node = get_company_from_tree(node->left, manufacturer_id);
	if (found_node == NULL)
	{
		found_node = get_company_from_tree(node->right, manufacturer_id);
	}
	return (found_node);
}

t_le_cod_major_class	*get_cod_major_class(t_le_adv_data_repository *repo,
		uint8_t class_code)
{
	t_le_cod_major_class	*current;

	current = repo->implemented_ad_types.cod.major_class;
	while (current)
	{
		if (current->major == class_code)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

t_le_cod_minor_class	*get_cod_minor_class(t_le_cod_major_class *major_class,
		uint8_t class_code)
{
	t_le_cod_minor_class	*current;

	current = major_class->minor;
	while (current)
	{
		if (current->value == class_code)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

t_le_cod_subminor_class	*get_cod_subminor_class(t_le_cod_major_class *major_class,
		uint8_t class_code)
{
	t_le_cod_subminor_class	*current;

	current = major_class->subminor;
	while (current)
	{
		if (current->value == class_code)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

t_le_cod_minor_bit	*get_cod_minor_bit(t_le_cod_major_class *major_class,
		uint8_t class_code)
{
	t_le_cod_minor_bit	*current;

	current = major_class->minor_bits;
	while (current)
	{
		if (current->value == class_code)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}

t_le_cod_service	*get_cod_service(t_le_adv_data_repository *repo,
		uint32_t bit)
{
	t_le_cod_service	*current;

	current = repo->implemented_ad_types.cod.service;
	while (current)
	{
		if (current->bit == bit)
		{
			return (current);
		}
		current = current->next;
	}
	return (NULL);
}
