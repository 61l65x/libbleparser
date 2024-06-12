#include "ble_parser.h"
#include "data_structs.h"

typedef struct s_company_identifier
{
	int							id;
	char						*name;
}								t_company_identifier;

int								parse_company_identifiers_yaml(const char *file_path,
									t_company_identifier **companies,
									size_t *company_count);

static t_le_manufacturer_data	*create_manufacturer_node(int id,
		const char *name)
{
	t_le_manufacturer_data	*node;

	node = calloc(1, sizeof(t_le_manufacturer_data));
	if (!node)
	{
		perror("Failed to allocate memory for manufacturer node");
		return (NULL);
	}
	node->id = id;
	node->name = strdup(name);
	node->proprietary_data = NULL;
	node->proprietary_data_len = 0;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static t_le_manufacturer_data	*build_balanced_tree(t_company_identifier *companies,
		int start, int end)
{
	int						mid;
	t_le_manufacturer_data	*root;

	if (start > end)
		return (NULL);
	mid = (start + end) / 2;
	root = create_manufacturer_node(companies[mid].id, companies[mid].name);
	if (!root)
		return (NULL);
	root->left = build_balanced_tree(companies, start, mid - 1);
	root->right = build_balanced_tree(companies, mid + 1, end);
	return (root);
}

int	create_manufacturer_tree(const char *file, t_le_manufacturer_data **root)
{
	t_company_identifier	*companies;
	size_t					company_count;

	companies = NULL;
	company_count = 0;
	if (parse_company_identifiers_yaml(file, &companies, &company_count) != 0)
	{
		return (-1);
	}
	*root = build_balanced_tree(companies, 0, company_count - 1);
	for (size_t i = 0; i < company_count; i++)
	{
		free(companies[i].name);
	}
	free(companies);
	return (0);
}
