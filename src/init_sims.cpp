#include "cs251_base.hpp"
#include "render.hpp"
#include "dominos.hpp"

namespace cs251
{
	sim_t* sim[10] = { 
					   new sim_t("Dominos1", dominos_t1::create),
					   NULL,//new sim_t("Dominos2", dominos_t2::create),
					   NULL,//new sim_t("Dominos3", dominos_t3::create),
					   NULL,//new sim_t("Dominos4", dominos_t4::create),
					   NULL,//new sim_t("Dominos5", dominos_t5::create),
					   NULL,//new sim_t("Dominos6", dominos_t6::create),
					   NULL,//new sim_t("Dominos7", dominos_t7::create),
					   NULL,//new sim_t("Dominos8", dominos_t8::create),
					   NULL,//new sim_t("Dominos9", dominos_t9::create),
					   NULL,//new sim_t("Dominos10", dominos_t10::create),
					 };
}