/*
 * This file is a part of the TChecker project.
 *
 * See files AUTHORS and LICENSE for copyright details.
 *
 */

#include "tchecker/ta/details/builder.hh"
#include "tchecker/async_zg/bounded_spread/async_zg_ta.hh"

namespace tchecker {
  
  namespace async_zg {
    
    namespace bounded_spread {
      
      namespace ta {
        
        /* model_t */
        
        model_t::model_t(tchecker::parsing::system_declaration_t const & system_declaration,
                         tchecker::log_t & log)
        : tchecker::async_zg::bounded_spread::ta::model_instantiation_t
        (tchecker::ta::build_system(system_declaration, log), log)
        {}
        
      } // end of namespace ta
      
    } // end of namespace bounded_spread
    
  } // end of namespace async_zg
  
} // end of namespace tchecker

