#include "cs251_base.hpp"
#include "render.hpp"
#include "dominos.hpp"

namespace cs251
{
	sim_t* sim[10] = { 
					   new sim_t("Dominos1", dominos_t1::create),
					   new sim_t("Dominos2", dominos_t2::create),
					   new sim_t("Dominos3", dominos_t3::create),
					   NULL,
					   NULL,
					   NULL,
					   NULL,
					   NULL,
					   NULL,
					   NULL,
					 };
}