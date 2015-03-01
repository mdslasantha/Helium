#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>

#include "analysis/preprocess.h"
#include "analysis/x86_analysis.h"
#include "analysis/staticinfo.h"


using namespace std;

void filter_disasm_vector(vec_cinstr &instrs, vector<Static_Info *> &static_info){

	for (int i = 0; i < static_info.size(); i++){

		uint32_t pc = static_info[i]->pc;

		bool found = false;
		for (int j = 0; j < instrs.size(); j++){
			cinstr_t * instr = instrs[j].first;
			if (instr->pc == pc){
				found = true;
				break;
			}
		}

		if (!found){
			static_info.erase(static_info.begin() + i--);
		}

	}

}

std::vector<uint32_t> get_instrace_startpoints(vec_cinstr &instrs, uint32_t pc){

	vector<uint32_t> start_points;
	int line = 0;

	for (int i = 0; i < instrs.size(); i++){
		cinstr_t * instr = instrs[i].first;
		if (instr != NULL){
			if (instr->pc == pc){
				start_points.push_back(i + 1);
			}
		}
	}

	return start_points;

}

vec_cinstr filter_instr_trace(uint32_t start_pc, uint32_t end_pc, vec_cinstr &unfiltered_instrs){


	vec_cinstr instrs;
	bool start = false;

	for (int i = 0; i < unfiltered_instrs.size(); i++){
		if (unfiltered_instrs[i].first->pc == start_pc){
			start = true;
		}
		if (start) instrs.push_back(unfiltered_instrs[i]);
		if (unfiltered_instrs[i].first->pc == end_pc){
			start = false;
		}
	}

	return instrs;


}







