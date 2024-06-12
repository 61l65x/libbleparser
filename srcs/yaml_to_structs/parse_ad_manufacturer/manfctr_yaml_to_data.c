#include "data_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct s_company_identifier
{
    int     id;
    char    *name;
}           t_company_identifier;

static int parse_company_identifiers_node(yaml_document_t *document, yaml_node_t *node, t_company_identifier **companies, size_t *company_count)
{
	yaml_node_item_t *item;
	t_company_identifier *company_list;
	size_t count = 0;
	size_t capacity = node->data.sequence.items.top - node->data.sequence.items.start;

	company_list = malloc(capacity * sizeof(t_company_identifier));
	if (!company_list)
	{
		perror("Failed to allocate memory for company list");
		return -1;
	}

	for (item = node->data.sequence.items.start; item < node->data.sequence.items.top; item++)
	{
		yaml_node_t *mapping_node = yaml_document_get_node(document, *item);
		if (!mapping_node || mapping_node->type != YAML_MAPPING_NODE)
			continue;

		t_company_identifier company = {0};
		yaml_node_pair_t *pair;
		for (pair = mapping_node->data.mapping.pairs.start; pair < mapping_node->data.mapping.pairs.top; pair++)
		{
			yaml_node_t *key_node = yaml_document_get_node(document, pair->key);
			yaml_node_t *value_node = yaml_document_get_node(document, pair->value);

			if (strcmp((char *)key_node->data.scalar.value, "value") == 0)
			{
				company.id = (int)strtol((char *)value_node->data.scalar.value, NULL, 0);
			}
			else if (strcmp((char *)key_node->data.scalar.value, "name") == 0)
			{
				company.name = strdup((char *)value_node->data.scalar.value);
			}
		}
		company_list[count++] = company;
	}

	*companies = company_list;
	*company_count = count;

	return 0;
}

// Function to parse the company_identifiers.yaml file
int parse_company_identifiers_yaml(const char *file_path, t_company_identifier **companies, size_t *company_count)
{
	printf("Parsing company identifiers YAML file: %s\n", file_path);
	FILE *file = fopen(file_path, "r");
	if (!file)
	{
		perror("Failed to open file");
		return -1;
	}

	yaml_parser_t parser;
	if (!yaml_parser_initialize(&parser))
	{
		perror("Failed to initialize YAML parser");
		fclose(file);
		return -1;
	}
	yaml_parser_set_input_file(&parser, file);

	yaml_document_t document;
	if (!yaml_parser_load(&parser, &document))
	{
		perror("Failed to load YAML document");
		yaml_parser_delete(&parser);
		fclose(file);
		return -1;
	}

	yaml_node_t *root_node = yaml_document_get_root_node(&document);
	if (!root_node || root_node->type != YAML_MAPPING_NODE)
	{
		fprintf(stderr, "Invalid YAML document structure\n");
		yaml_document_delete(&document);
		yaml_parser_delete(&parser);
		fclose(file);
		return -1;
	}

	yaml_node_pair_t *pair;
	yaml_node_t *company_identifiers_node = NULL;
	for (pair = root_node->data.mapping.pairs.start; pair < root_node->data.mapping.pairs.top; pair++)
	{
		yaml_node_t *key_node = yaml_document_get_node(&document, pair->key);
		if (strcmp((char *)key_node->data.scalar.value, "company_identifiers") == 0)
		{
			company_identifiers_node = yaml_document_get_node(&document, pair->value);
			break;
		}
	}

	if (!company_identifiers_node || company_identifiers_node->type != YAML_SEQUENCE_NODE)
	{
		fprintf(stderr, "Invalid or missing company_identifiers node\n");
		yaml_document_delete(&document);
		yaml_parser_delete(&parser);
		fclose(file);
		return -1;
	}

	int result = parse_company_identifiers_node(&document, company_identifiers_node, companies, company_count);
	yaml_document_delete(&document);
	yaml_parser_delete(&parser);
	fclose(file);
	return result;
}
