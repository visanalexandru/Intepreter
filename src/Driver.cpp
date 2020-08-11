#include "Driver.h"


int Driver::parse(const std::string&f){
    current_file=f;
	location.initialize(&current_file);
	scan_begin();
	yy::parser parser(*this);
	int res=parser();
	scan_end();
	return res;
}


