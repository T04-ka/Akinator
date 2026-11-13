#include "aki.h"
#include "includes/bintree.h"
#include "includes/myformat.cpp"

void free_tree_nodes_value(tree_node_t* tree_node_ptr, bool do_recursively PASS_PREV_DATA);

int main() {


    FILE* input_f = fopen("preorder.txt", "r");
    tree_node_t* tree_ptr = read_tree(input_f, TREE_PREORDER PASS_CURRENT_LOCATION);
    fclose(input_f);



    FILE* output_f = fopen("preorder.txt", "w");
    tree_write_preorder(output_f, tree_ptr PASS_CURRENT_LOCATION);
    fclose(output_f);

    FILE* html_file = fopen("tree_dump.html", "w");
    tree_dump_in_html(tree_ptr, html_file, "1.png", tree_ptr PASS_CURRENT_LOCATION);
    fclose(html_file);

    free_tree_nodes_value(tree_ptr, true PASS_CURRENT_LOCATION);
    tree_node_destroy(tree_ptr, true PASS_CURRENT_LOCATION);

    return 0;
}

//---------------------------------------------------------------------------------------------------------------------------------

void free_tree_nodes_value(tree_node_t* tree_node_ptr, bool do_recursively PASS_PREV_DATA) {

    ASSERT(tree_node_ptr != NULL);

    if (do_recursively) {

        if (tree_node_ptr->left != NULL) {

            free_tree_nodes_value(tree_node_ptr->left, true PASS_CURRENT_LOCATION);
        }

        if (tree_node_ptr->right != NULL) {

            free_tree_nodes_value(tree_node_ptr->right, true PASS_CURRENT_LOCATION);
        }
    }

    free(tree_node_ptr->value);
}

//---------------------------------------------------------------------------------------------------------------------------------

void game_cicl(tree_node_t* tree_root_ptr) {


    int input_c = -1;

    while (input_c) {

        scanf("%d", &input_c);

        char* str_to_w = NULL;
        scanf("%ms", &str_to_w);

        if (input_c == (int) 'l') {

            tr
        }
    }
}
