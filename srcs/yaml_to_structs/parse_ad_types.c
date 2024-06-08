#include "ble_parser.h"

static t_le_ad_types	*create_ad_type(yaml_document_t *document,
		yaml_node_t *node)
{
	t_le_ad_types		*ad_type;
	yaml_node_pair_t	*ad_type_pair;
	yaml_node_t			*key_node;
	yaml_node_t			*value_node;

	ad_type = malloc(sizeof(t_le_ad_types));
	if (!ad_type)
	{
		perror("Failed to allocate memory for ad_type");
		return (NULL);
	}
	memset(ad_type, 0, sizeof(t_le_ad_types));
	for (ad_type_pair = node->data.mapping.pairs.start; ad_type_pair < node->data.mapping.pairs.top; ad_type_pair++)
	{
		key_node = yaml_document_get_node(document, ad_type_pair->key);
		value_node = yaml_document_get_node(document, ad_type_pair->value);
		if (strcmp((char *)key_node->data.scalar.value, "value") == 0)
		{
			ad_type->type = (uint8_t)strtol((char *)value_node->data.scalar.value,
					NULL, 0);
		}
		else if (strcmp((char *)key_node->data.scalar.value, "name") == 0)
		{
			ad_type->name = strdup((char *)value_node->data.scalar.value);
		}
	}
	return (ad_type);
}

static int	parse_ad_types_node(yaml_document_t *document, yaml_node_t *node,
		t_le_adv_data_repository *repo)
{
	yaml_node_pair_t	*pair;
	yaml_node_t			*key_node;
	yaml_node_t			*value_node;
	yaml_node_item_t	*item;
	yaml_node_t			*ad_type_node;
	t_le_ad_types		*ad_type;

	for (pair = node->data.mapping.pairs.start; pair < node->data.mapping.pairs.top; pair++)
	{
		key_node = yaml_document_get_node(document, pair->key);
		value_node = yaml_document_get_node(document, pair->value);
		if (strcmp((char *)key_node->data.scalar.value, "ad_types") == 0)
		{
			if (value_node->type != YAML_SEQUENCE_NODE)
			{
				fprintf(stderr, "Invalid ad_types structure\n");
				return (-1);
			}
			for (item = value_node->data.sequence.items.start; item < value_node->data.sequence.items.top; item++)
			{
				ad_type_node = yaml_document_get_node(document, *item);
				if (ad_type_node->type != YAML_MAPPING_NODE)
				{
					continue ;
				}
				ad_type = create_ad_type(document, ad_type_node);
				if (!ad_type)
				{
					return (-1);
				}
				ad_type->next = repo->ad_types;
				repo->ad_types = ad_type;
				repo->num_le_adv_data++;
			}
		}
	}
	return (0);
}

int	parse_ad_types_yaml(t_le_adv_data_repository *repo, const char *file_path)
{
	FILE			*file;
	yaml_parser_t	parser;
	yaml_document_t	document;
	yaml_node_t		*root_node;
	int				result;

	file = fopen(file_path, "r");
	if (!file)
	{
		perror("Failed to open file");
		return (-1);
	}
	if (!yaml_parser_initialize(&parser))
	{
		perror("Failed to initialize YAML parser");
		fclose(file);
		return (-1);
	}
	yaml_parser_set_input_file(&parser, file);
	if (!yaml_parser_load(&parser, &document))
	{
		perror("Failed to load YAML document");
		yaml_parser_delete(&parser);
		fclose(file);
		return (-1);
	}
	root_node = yaml_document_get_root_node(&document);
	if (root_node->type != YAML_MAPPING_NODE)
	{
		fprintf(stderr, "Invalid YAML document structure\n");
		yaml_document_delete(&document);
		yaml_parser_delete(&parser);
		fclose(file);
		return (-1);
	}
	result = parse_ad_types_node(&document, root_node, repo);
	yaml_document_delete(&document);
	yaml_parser_delete(&parser);
	fclose(file);
	return (result);
}
