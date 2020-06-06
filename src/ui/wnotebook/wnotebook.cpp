#include "wnotebook.hpp"


WNotebook::WNotebook() {
    prepend_page(*frm1, tabLabel1.c_str());
    prepend_page(*frm2, tabLabel2.c_str()); 
    prepend_page(*frm3, tabLabel3.c_str()); 


}

WNotebook::~WNotebook(){}
