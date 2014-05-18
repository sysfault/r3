/*
 * r3.h
 * Copyright (C) 2014 c9s <c9s@c9smba.local>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef NODE_H
#define NODE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <pcre.h>

#include "str_array.h"

#define node_edge_pattern(node,i) node->edges[i]->pattern
#define node_edge_pattern_len(node,i) node->edges[i]->pattern_len


struct _edge;
struct _node;
struct _condition;
typedef struct _edge edge;
typedef struct _node node;
typedef struct _condition condition;

struct _node {
    edge  ** edges;
    int      edge_len;
    int      edge_cap;

    condition ** conditions;
    int      condition_len;
    int      condition_cap;


    /** compile-time variables here.... **/

    /* the combined regexp pattern string from pattern_tokens */
    char * combined_pattern;
    int    combined_pattern_len;
    pcre * pcre_pattern;
    pcre_extra * pcre_extra;
    int    ov_cnt;
    int *  ov;

    /**
     * the pointer of condition data
     */
    void * data;

    int endpoint;
};

struct _edge {
    char * pattern;
    int    pattern_len;
    bool   has_slug;
    node * child;
};

typedef struct {
    str_array * vars;
    char * path; // current path to dispatch
    int    path_len; // the length of the current path
    int    request_method;  // current request method

    void * data; // condition ptr

    char * host; // the request host 
    int    host_len;

    char * remote_addr;
    int    remote_addr_len;
} match_entry;

struct _condition {
    char * path;
    int    path_len;

    int    request_method; // can be (GET || POST)

    char * host; // required host name
    int    host_len;

    void * data;

    char * remote_addr_pattern;
    int    remote_addr_pattern_len;
};


node * r3_tree_create(int cap);

node * r3_node_create();

void r3_tree_free(node * tree);

void r3_edge_free(edge * edge);

edge * r3_node_add_child(node * n, char * pat , node *child);

edge * r3_node_find_edge(node * n, char * pat);

void r3_node_append_edge(node *n, edge *child);

node * r3_tree_insert_path(node *tree, char *path, condition * condition, void * data);

node * r3_tree_insert_pathl(node *tree, char *path, int path_len, condition * condition, void * data);

void r3_tree_dump(node * n, int level);

int r3_tree_render_file(node * tree, char * format, char * filename);

int r3_tree_render_dot(node * tree);

edge * r3_node_find_edge_str(node * n, char * str, int str_len);


void r3_tree_compile(node *n);

void r3_tree_compile_patterns(node * n);

node * r3_tree_match(node * n, char * path, int path_len, match_entry * entry);

node * r3_tree_match_with_entry(node * n, match_entry * entry);

bool r3_node_has_slug_edges(node *n);

edge * r3_edge_create(char * pattern, int pattern_len, node * child);

void r3_edge_branch(edge *e, int dl);

void r3_edge_free(edge * edge);


node * r3_tree_insert_route(node *tree, condition * condition, void * data);

match_entry * match_entry_createl(char * path, int path_len);

#define match_entry_create(path) match_entry_createl(path,strlen(path))

void match_entry_free(match_entry * entry);


condition * condition_create(char * path);

condition * condition_createl(char * path, int path_len);

int condition_cmp(condition *r1, condition *r2);

void r3_node_append_condition(node * n, condition * condition);

void condition_free(condition * condition);

#define METHOD_GET 2
#define METHOD_POST 2<<1
#define METHOD_PUT 2<<1
#define METHOD_DELETE 2<<1

#endif /* !NODE_H */
