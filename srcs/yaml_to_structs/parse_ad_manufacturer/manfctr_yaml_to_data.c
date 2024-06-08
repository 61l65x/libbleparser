#include "ble_data_structs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <yaml.h>

typedef struct s_company_identifier
{
    int     id;
    char    *name;
}           t_company_identifier;

int parse_company_identifiers_yaml(const char *file_path,
        t_company_identifier **companies, size_t *company_count)
{
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

    // Find the "company_identifiers" node
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

    size_t count = 0;
    size_t capacity = company_identifiers_node->data.sequence.items.top - company_identifiers_node->data.sequence.items.start;
    t_company_identifier *company_list = malloc(capacity * sizeof(t_company_identifier));
    if (!company_list)
    {
        perror("Failed to allocate memory for company list");
        yaml_document_delete(&document);
        yaml_parser_delete(&parser);
        fclose(file);
        return -1;
    }

    yaml_node_item_t *item;
    for (item = company_identifiers_node->data.sequence.items.start; item < company_identifiers_node->data.sequence.items.top; item++)
    {
        yaml_node_t *node = yaml_document_get_node(&document, *item);
        if (!node || node->type != YAML_MAPPING_NODE)
            continue;

        t_company_identifier company = {0};
        yaml_node_pair_t *sub_pair;
        for (sub_pair = node->data.mapping.pairs.start; sub_pair < node->data.mapping.pairs.top; sub_pair++)
        {
            yaml_node_t *key_node = yaml_document_get_node(&document, sub_pair->key);
            yaml_node_t *value_node = yaml_document_get_node(&document, sub_pair->value);

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

    yaml_document_delete(&document);
    yaml_parser_delete(&parser);
    fclose(file);

    *companies = company_list;
    *company_count = count;

    return 0;
}
