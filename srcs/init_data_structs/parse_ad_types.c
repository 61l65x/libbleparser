#include "ble_parser.h"

int	parse_ad_types(t_le_adv_data_repository *repo)
{
	FILE *file = fopen(LE_AD_TYPES_PATH, "r");
	if (!file)
	{
		perror("Failed to open ad_types.yaml");
		return (-1);
	}

	yaml_parser_t parser;
	yaml_document_t document;
	yaml_node_t *node;

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

	// Assuming the root node is a mapping
	node = yaml_document_get_root_node(&document);
	if (node->type != YAML_MAPPING_NODE)
	{
		perror("Invalid YAML document structure");
		yaml_document_delete(&document);
		yaml_parser_delete(&parser);
		fclose(file);
		return (-1);
	}

	yaml_node_pair_t *pair;
	for (pair = node->data.mapping.pairs.start; pair < node->data.mapping.pairs.top; pair++)
	{
		yaml_node_t *key_node = yaml_document_get_node(&document, pair->key);
		yaml_node_t *value_node = yaml_document_get_node(&document,
				pair->value);

		if (strcmp((char *)key_node->data.scalar.value, "ad_types") == 0)
		{
			if (value_node->type != YAML_SEQUENCE_NODE)
			{
				perror("Invalid ad_types structure");
				yaml_document_delete(&document);
				yaml_parser_delete(&parser);
				fclose(file);
				return (-1);
			}

			yaml_node_item_t *item;
			for (item = value_node->data.sequence.items.start; item < value_node->data.sequence.items.top; item++)
			{
				yaml_node_t *ad_type_node = yaml_document_get_node(&document,
						*item);
				if (ad_type_node->type != YAML_MAPPING_NODE)
				{
					continue ;
				}

				t_le_ad_types *ad_type = malloc(sizeof(t_le_ad_types));
				if (!ad_type)
				{
					perror("Failed to allocate memory for ad_type");
					yaml_document_delete(&document);
					yaml_parser_delete(&parser);
					fclose(file);
					return (-1);
				}

				memset(ad_type, 0, sizeof(t_le_ad_types));

				yaml_node_pair_t *ad_type_pair;
				for (ad_type_pair = ad_type_node->data.mapping.pairs.start; ad_type_pair < ad_type_node->data.mapping.pairs.top; ad_type_pair++)
				{
					yaml_node_t *ad_type_key_node = yaml_document_get_node(&document,
							ad_type_pair->key);
					yaml_node_t *ad_type_value_node = yaml_document_get_node(&document,
							ad_type_pair->value);

					if (strcmp((char *)ad_type_key_node->data.scalar.value,
							"value") == 0)
					{
						ad_type->type = (uint8_t)strtol((char *)ad_type_value_node->data.scalar.value,
								NULL, 0);
					}
					else if (strcmp((char *)ad_type_key_node->data.scalar.value,
							"name") == 0)
					{
						ad_type->name = strdup((char *)ad_type_value_node->data.scalar.value);
					}
				}

				ad_type->next = repo->ad_types;
				repo->ad_types = ad_type;
				repo->num_le_adv_data++;
			}
		}
	}

	yaml_document_delete(&document);
	yaml_parser_delete(&parser);
	fclose(file);
	return (0);
}