#include "data_structs.h"
#include "ble_parser.h"

// Function to create a new minor class node
static t_le_cod_minor_class *create_minor_class_node(uint32_t value, const char *name)
{
	t_le_cod_minor_class *node = malloc(sizeof(t_le_cod_minor_class));
	if (!node)
	{
		perror("Failed to allocate memory for minor class node");
		return NULL;
	}
	node->value = value;
	node->name = strdup(name);
	node->next = NULL;
	return node;
}

// Function to create a new subminor class node
static t_le_cod_subminor_class *create_subminor_class_node(uint32_t value, const char *name)
{
	t_le_cod_subminor_class *node = malloc(sizeof(t_le_cod_subminor_class));
	if (!node)
	{
		perror("Failed to allocate memory for subminor class node");
		return NULL;
	}
	node->value = value;
	node->name = strdup(name);
	node->next = NULL;
	return node;
}

// Function to create a new minor bit node
static t_le_cod_minor_bit *create_minor_bit_node(uint32_t value, const char *name)
{
	t_le_cod_minor_bit *node = malloc(sizeof(t_le_cod_minor_bit));
	if (!node)
	{
		perror("Failed to allocate memory for minor bit node");
		return NULL;
	}
	node->value = value;
	node->name = strdup(name);
	node->next = NULL;
	return node;
}

// Function to create a new major class node
static t_le_cod_major_class *create_major_class_node(uint32_t major, const char *name, uint32_t subsplit)
{
	t_le_cod_major_class *node = malloc(sizeof(t_le_cod_major_class));
	if (!node)
	{
		perror("Failed to allocate memory for major class node");
		return NULL;
	}
	node->major = major;
	node->name = strdup(name);
	node->subsplit = subsplit;
	node->minor = NULL;
	node->subminor = NULL;
	node->minor_bits = NULL;
	node->next = NULL;
	return node;
}

// Function to create a new service node
static t_le_cod_service *create_service_node(uint32_t bit, const char *name)
{
	t_le_cod_service *node = malloc(sizeof(t_le_cod_service));
	if (!node)
	{
		perror("Failed to allocate memory for service node");
		return NULL;
	}
	node->bit = bit;
	node->name = strdup(name);
	node->next = NULL;
	return node;
}

// Function to parse the CoD minor classes
static int parse_minor_classes(yaml_document_t *document, yaml_node_t *node, t_le_cod_minor_class **minor_list)
{
	yaml_node_item_t *item;
	for (item = node->data.sequence.items.start; item < node->data.sequence.items.top; item++)
	{
		yaml_node_t *mapping_node = yaml_document_get_node(document, *item);
		if (!mapping_node || mapping_node->type != YAML_MAPPING_NODE)
			continue;

		uint32_t value = 0;
		char *name = NULL;
		yaml_node_pair_t *pair;
		for (pair = mapping_node->data.mapping.pairs.start; pair < mapping_node->data.mapping.pairs.top; pair++)
		{
			yaml_node_t *key_node = yaml_document_get_node(document, pair->key);
			yaml_node_t *value_node = yaml_document_get_node(document, pair->value);

			if (strcmp((char *)key_node->data.scalar.value, "value") == 0)
			{
				value = (uint32_t)strtol((char *)value_node->data.scalar.value, NULL, 0);
			}
			else if (strcmp((char *)key_node->data.scalar.value, "name") == 0)
			{
				name = strdup((char *)value_node->data.scalar.value);
			}
		}
		t_le_cod_minor_class *new_node = create_minor_class_node(value, name);
		if (!new_node)
			return -1;

		new_node->next = *minor_list;
		*minor_list = new_node;
		free(name);
	}
	return 0;
}

// Function to parse the CoD subminor classes
static int parse_subminor_classes(yaml_document_t *document, yaml_node_t *node, t_le_cod_subminor_class **subminor_list)
{
	yaml_node_item_t *item;
	for (item = node->data.sequence.items.start; item < node->data.sequence.items.top; item++)
	{
		yaml_node_t *mapping_node = yaml_document_get_node(document, *item);
		if (!mapping_node || mapping_node->type != YAML_MAPPING_NODE)
			continue;

		uint32_t value = 0;
		char *name = NULL;
		yaml_node_pair_t *pair;
		for (pair = mapping_node->data.mapping.pairs.start; pair < mapping_node->data.mapping.pairs.top; pair++)
		{
			yaml_node_t *key_node = yaml_document_get_node(document, pair->key);
			yaml_node_t *value_node = yaml_document_get_node(document, pair->value);

			if (strcmp((char *)key_node->data.scalar.value, "value") == 0)
			{
				value = (uint32_t)strtol((char *)value_node->data.scalar.value, NULL, 0);
			}
			else if (strcmp((char *)key_node->data.scalar.value, "name") == 0)
			{
				name = strdup((char *)value_node->data.scalar.value);
			}
		}
		t_le_cod_subminor_class *new_node = create_subminor_class_node(value, name);
		if (!new_node)
			return -1;

		new_node->next = *subminor_list;
		*subminor_list = new_node;
		free(name);
	}
	return 0;
}

// Function to parse the CoD minor bits
static int parse_minor_bits(yaml_document_t *document, yaml_node_t *node, t_le_cod_minor_bit **minor_bit_list)
{
	yaml_node_item_t *item;
	for (item = node->data.sequence.items.start; item < node->data.sequence.items.top; item++)
	{
		yaml_node_t *mapping_node = yaml_document_get_node(document, *item);
		if (!mapping_node || mapping_node->type != YAML_MAPPING_NODE)
			continue;

		uint32_t value = 0;
		char *name = NULL;
		yaml_node_pair_t *pair;
		for (pair = mapping_node->data.mapping.pairs.start; pair < mapping_node->data.mapping.pairs.top; pair++)
		{
			yaml_node_t *key_node = yaml_document_get_node(document, pair->key);
			yaml_node_t *value_node = yaml_document_get_node(document, pair->value);

			if (strcmp((char *)key_node->data.scalar.value, "value") == 0)
			{
				value = (uint32_t)strtol((char *)value_node->data.scalar.value, NULL, 0);
			}
			else if (strcmp((char *)key_node->data.scalar.value, "name") == 0)
			{
				name = strdup((char *)value_node->data.scalar.value);
			}
		}
		t_le_cod_minor_bit *new_node = create_minor_bit_node(value, name);
		if (!new_node)
			return -1;

		new_node->next = *minor_bit_list;
		*minor_bit_list = new_node;
		free(name);
	}
	return 0;
}

// Function to parse the CoD services
static int parse_services(yaml_document_t *document, yaml_node_t *node, t_le_cod_service **service_list)
{
	yaml_node_item_t *item;
	for (item = node->data.sequence.items.start; item < node->data.sequence.items.top; item++)
	{
		yaml_node_t *mapping_node = yaml_document_get_node(document, *item);
		if (!mapping_node || mapping_node->type != YAML_MAPPING_NODE)
			continue;

		uint32_t bit = 0;
		char *name = NULL;
		yaml_node_pair_t *pair;
		for (pair = mapping_node->data.mapping.pairs.start; pair < mapping_node->data.mapping.pairs.top; pair++)
		{
			yaml_node_t *key_node = yaml_document_get_node(document, pair->key);
			yaml_node_t *value_node = yaml_document_get_node(document, pair->value);

			if (strcmp((char *)key_node->data.scalar.value, "bit") == 0)
			{
				bit = (uint32_t)strtol((char *)value_node->data.scalar.value, NULL, 0);
			}
			else if (strcmp((char *)key_node->data.scalar.value, "name") == 0)
			{
				name = strdup((char *)value_node->data.scalar.value);
			}
		}
		t_le_cod_service *new_node = create_service_node(bit, name);
		if (!new_node)
			return -1;

		new_node->next = *service_list;
		*service_list = new_node;
		free(name);
	}
	return 0;
}

// Function to parse the CoD major classes
static int parse_major_classes(yaml_document_t *document, yaml_node_t *node, t_le_cod_major_class **cod)
{
	yaml_node_item_t *item;
	for (item = node->data.sequence.items.start; item < node->data.sequence.items.top; item++)
	{
		yaml_node_t *mapping_node = yaml_document_get_node(document, *item);
		if (!mapping_node || mapping_node->type != YAML_MAPPING_NODE)
			continue;

		uint32_t major = 0;
		char *name = NULL;
		uint32_t subsplit = 0;
		t_le_cod_minor_class *minor_list = NULL;
		t_le_cod_subminor_class *subminor_list = NULL;
		t_le_cod_minor_bit *minor_bit_list = NULL;
		yaml_node_pair_t *pair;
		for (pair = mapping_node->data.mapping.pairs.start; pair < mapping_node->data.mapping.pairs.top; pair++)
		{
			yaml_node_t *key_node = yaml_document_get_node(document, pair->key);
			yaml_node_t *value_node = yaml_document_get_node(document, pair->value);

			if (strcmp((char *)key_node->data.scalar.value, "major") == 0)
			{
				major = (uint32_t)strtol((char *)value_node->data.scalar.value, NULL, 0);
			}
			else if (strcmp((char *)key_node->data.scalar.value, "name") == 0)
			{
				name = strdup((char *)value_node->data.scalar.value);
			}
			else if (strcmp((char *)key_node->data.scalar.value, "subsplit") == 0)
			{
				subsplit = (uint32_t)strtol((char *)value_node->data.scalar.value, NULL, 0);
			}
			else if (strcmp((char *)key_node->data.scalar.value, "minor") == 0 && value_node->type == YAML_SEQUENCE_NODE)
			{
				if (parse_minor_classes(document, value_node, &minor_list) != 0)
					return -1;
			}
			else if (strcmp((char *)key_node->data.scalar.value, "subminor") == 0 && value_node->type == YAML_SEQUENCE_NODE)
			{
				if (parse_subminor_classes(document, value_node, &subminor_list) != 0)
					return -1;
			}
			else if (strcmp((char *)key_node->data.scalar.value, "minor_bits") == 0 && value_node->type == YAML_SEQUENCE_NODE)
			{
				if (parse_minor_bits(document, value_node, &minor_bit_list) != 0)
					return -1;
			}
		}
		t_le_cod_major_class *new_node = create_major_class_node(major, name, subsplit);
		if (!new_node)
			return -1;

		new_node->minor = minor_list;
		new_node->subminor = subminor_list;
		new_node->minor_bits = minor_bit_list;
		new_node->next = *cod;
		*cod = new_node;
		free(name);
	}
	return 0;
}

// Function to parse the class of device (CoD) YAML file
int parse_class_of_device(const char *file_path, t_le_class_of_device *cod)
{
	FILE			*file;
	yaml_parser_t	parser;
	yaml_document_t	document;
	yaml_node_t		*root_node;
	int				result = -1;

	file = fopen(file_path, "r");
	if (!file)
	{
		perror("Failed to open file");
		return -1;
	}
	if (!yaml_parser_initialize(&parser))
	{
		perror("Failed to initialize YAML parser");
		fclose(file);
		return -1;
	}
	yaml_parser_set_input_file(&parser, file);
	if (!yaml_parser_load(&parser, &document))
	{
		perror("Failed to load YAML document");
		yaml_parser_delete(&parser);
		fclose(file);
		return -1;
	}
	root_node = yaml_document_get_root_node(&document);
	if (root_node->type != YAML_MAPPING_NODE)
	{
		fprintf(stderr, "Invalid YAML document structure\n");
		goto cleanup;
	}

	// Parse major classes
	yaml_node_pair_t *pair;
	for (pair = root_node->data.mapping.pairs.start; pair < root_node->data.mapping.pairs.top; pair++)
	{
		yaml_node_t *key_node = yaml_document_get_node(&document, pair->key);
		yaml_node_t *value_node = yaml_document_get_node(&document, pair->value);
		if (strcmp((char *)key_node->data.scalar.value, "cod_device_class") == 0 && value_node->type == YAML_SEQUENCE_NODE)
		{
			if (parse_major_classes(&document, value_node, &cod->major_class) != 0)
				goto cleanup;
		}
		else if (strcmp((char *)key_node->data.scalar.value, "cod_services") == 0 && value_node->type == YAML_SEQUENCE_NODE)
		{
			if (parse_services(&document, value_node, &cod->service) != 0)
				goto cleanup;
		}
	}
	result = 0;

cleanup:
	yaml_document_delete(&document);
	yaml_parser_delete(&parser);
	fclose(file);
	return result;
}
