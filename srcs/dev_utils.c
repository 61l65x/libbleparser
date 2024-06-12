
#include "ble_parser.h"

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

void print_manufacturer_tree(t_le_manufacturer_data *node)
{
    if (node == NULL)
        return;
    print_manufacturer_tree(node->left);
    printf("ID: %x, Name: %s\n", node->id, node->name);
    print_manufacturer_tree(node->right);
}
