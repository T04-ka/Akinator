#include "aki.h"
#include "includes/bintree.h"
#include "includes/myformat.cpp"
#include <cstdio>

void free_tree_nodes_value(tree_node_t* tree_node_ptr, bool do_recursively PASS_PREV_DATA);
void game_cicl(tree_node_t* tree_root_ptr);
void ask_question(tree_node_t** cur_node_ptr PASS_PREV_DATA);
void nodes_resplace(tree_node_t* last_character_node, tree_node_elem_t new_character, \
                    tree_node_elem_t question, bool is_last_character_match PASS_PREV_DATA);
void make_guess(tree_node_t** cur_node_ptr PASS_PREV_DATA);
void clear_buffer(int last_char);

int main() {

    FILE* input_f = fopen("preorder.txt", "r");
    tree_node_t* tree_ptr = read_tree(input_f, TREE_PREORDER PASS_CURRENT_LOCATION);
    fclose(input_f);

    FILE* html_file = fopen("tree_dump.html", "w");
    tree_dump_in_html(tree_ptr, html_file, "begin.png", tree_ptr PASS_CURRENT_LOCATION);
    fclose(html_file);

    game_cicl(tree_ptr);

    FILE* output_f = fopen("preorder.txt", "w");
    tree_write_preorder(output_f, tree_ptr PASS_CURRENT_LOCATION);
    fclose(output_f);

    html_file = fopen("tree_dump.html", "w");
    tree_dump_in_html(tree_ptr, html_file, "end.png", tree_ptr PASS_CURRENT_LOCATION);
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
//
// <-cur_node->
// if left != null:
//      ask a quastion
// else:
//      make a decision
//
// --------------------------
// ask a quation:
// ask
// if yes:
//      cur_node = ->left
// else :
//      cur_node = ->right
//
// -------------------------
// make a desision:
// is it a...?
// if yes:
//      gol
// else:
//      hwo is this? (charact)
//      difference in question (quest)
//
void game_cicl(tree_node_t* tree_root_ptr) {

    printf("\nStart Akinator\n");

    tree_node_t* cur_node = tree_root_ptr->left;

    while (true) {

        if (cur_node->left != NULL) {

            ask_question(&cur_node PASS_CURRENT_LOCATION);
        }
        else {

            make_guess(&cur_node PASS_CURRENT_LOCATION);
            break;
        }
    }

    printf("End Akinator\n");
}

//---------------------------------------------------------------------------------------------------------------------------------

void nodes_resplace(tree_node_t* last_character_node, tree_node_elem_t new_character, \
                    tree_node_elem_t question, bool is_last_character_match PASS_PREV_DATA) {


    ASSERT(last_character_node != NULL);

    tree_node_t* new_character_node = tree_node_create(new_character);
    tree_node_t* question_node      = tree_node_create(question);

    tree_node_t* parent_node = last_character_node->parent;

    if (parent_node->left == last_character_node) {

        tree_node_link(parent_node, question_node, TREE_NODE_SIDE_LEFT PASS_CURRENT_LOCATION);
    }
    else if (parent_node->right == last_character_node) {

        tree_node_link(parent_node, question_node, TREE_NODE_SIDE_RIGHT PASS_CURRENT_LOCATION);
    }
    else {

        ASSERT(0);
    }

    tree_node_link(question_node, last_character_node, (tree_node_side_t) is_last_character_match PASS_CURRENT_LOCATION);
    tree_node_link(question_node, new_character_node, (tree_node_side_t) !is_last_character_match PASS_CURRENT_LOCATION);
}

//---------------------------------------------------------------------------------------------------------------------------------

void ask_question(tree_node_t** cur_node_ptr PASS_PREV_DATA) {

    ASSERT(cur_node_ptr != NULL);
    ASSERT(*cur_node_ptr != NULL);

    tree_node_t* cur_node = *cur_node_ptr;

    printf("%s?(y\\n)\n", cur_node->value);

    char answer = 0;
    scanf("%c[^\n]", &answer);
    clear_buffer(0);

    $c(answer);

    if (answer == 'y') {

        *cur_node_ptr = cur_node->right;
    }
    else if (answer == 'n') {

        *cur_node_ptr = cur_node->left;
    }
    else {

        $;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------

void make_guess(tree_node_t** cur_node_ptr PASS_PREV_DATA) {

    ASSERT(cur_node_ptr != NULL);
    ASSERT(*cur_node_ptr != NULL);

    tree_node_t* cur_node = *cur_node_ptr;

    printf("Is it a %s?(y\\n)\n", cur_node->value);

    char answer = 0;
    scanf("%c[^\n]", &answer);
    clear_buffer(0);

    if (answer == 'y') {

        printf("GOL\n");
    }
    else if (answer == 'n') {

        printf("Then who is this?\n");

        char* new_character = NULL;
        scanf("%m[^\n]", &new_character);
        clear_buffer(0);

        printf("Which difference between %s and %s?\n", cur_node->value, new_character);

        char* question = NULL;
        scanf("%m[^\n]", &question);
        clear_buffer(0);

        printf("Does %s matches to this definition?(Y\\n)\n", cur_node->value);

        char is_match = 0;
        scanf("%c[^\n]", &is_match);
        clear_buffer(0);

        nodes_resplace(cur_node, new_character, question, (bool) (is_match - 'n') PASS_CURRENT_LOCATION);
    }
    else {

        $;
    }
}

void clear_buffer(int last_char){

    if (last_char == '\n'){

        return;
    }

    int c = 0;
    while ((c = getchar()) != '\n') {}
}
