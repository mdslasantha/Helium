#ifndef _FILE_PARSER_H
#define _FILE_PARSER_H

#include <iostream>
#include <utility>
#include <fstream>
#include "canonicalize.h"
#include <stdint.h>
#include <vector>
#include <string>


using namespace std;

cinstr_t * get_next_from_ascii_file(ifstream &file);
cinstr_t * get_next_from_bin_file(ifstream &file);

vector<cinstr_t * > get_all_instructions(ifstream &file);
void walk_instructions(ifstream &file);
vec_cinstr walk_file_and_get_instructions(ifstream &file, vector<disasm_t *> &disasm);

void go_forward_line(ifstream &file);
bool go_backward_line(ifstream &file);
void reverse_file(ofstream &out, ifstream &in);
void go_to_line(uint line_no, ifstream &file);

void print_cinstr(cinstr_t * instr);

uint32_t go_to_line_dest(ifstream &file, uint64_t dest, uint32_t stride);

vector<disasm_t *> parse_debug_disasm(ifstream &file);
void print_disasm(vector<disasm_t *> &disasm);
vector<string> get_disasm_string(vector<disasm_t *> &disasm, uint32_t app_pc);

#endif