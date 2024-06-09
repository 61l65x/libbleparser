
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

// Function to print minor classes
void print_minor_classes(t_le_cod_minor_class *minor)
{
    while (minor)
    {
        printf("Minor Class - Value: %u, Name: %s\n", minor->value, minor->name);
        minor = minor->next;
    }
}

// Function to print subminor classes
void print_subminor_classes(t_le_cod_subminor_class *subminor)
{
    while (subminor)
    {
        printf("Subminor Class - Value: %u, Name: %s\n", subminor->value, subminor->name);
        subminor = subminor->next;
    }
}

// Function to print minor bits
void print_minor_bits(t_le_cod_minor_bit *minor_bit)
{
    while (minor_bit)
    {
        printf("Minor Bit - Value: %u, Name: %s\n", minor_bit->value, minor_bit->name);
        minor_bit = minor_bit->next;
    }
}

// Function to print major classes
void print_major_classes(t_le_cod_major_class *major)
{
    while (major)
    {
        printf("Major Class - Major: %u, Name: %s, Subsplit: %u\n", major->major, major->name, major->subsplit);
        print_minor_classes(major->minor);
        print_subminor_classes(major->subminor);
        print_minor_bits(major->minor_bits);
        major = major->next;
    }
}

// Function to print services
void print_services(t_le_cod_service *service)
{
    while (service)
    {
        printf("Service - Bit: %u, Name: %s\n", service->bit, service->name);
        service = service->next;
    }
}

// Function to print all details of the Class of Device (CoD)
void print_class_of_device(t_le_class_of_device *cod)
{
    // Print the Class of Device (CoD)
    printf("Class of Device (CoD):\n");
    print_major_classes(cod->major_class);
    print_services(cod->service);
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
	print_manufacturer_tree(parser->repo.implemented_ad_types.root);
	print_class_of_device(&parser->repo.implemented_ad_types.cod);
	// Cleanup
	destroy_ble_parser(parser);
	return (0);
}
