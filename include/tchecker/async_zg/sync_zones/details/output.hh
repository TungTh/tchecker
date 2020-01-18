/*
 * This file is a part of the TChecker project.
 *
 * See files AUTHORS and LICENSE for copyright details.
 *
 */

#ifndef TCHECKER_ASYNC_ZG_SYNC_ZONES_DETAILS_OUTPUT_HH
#define TCHECKER_ASYNC_ZG_SYNC_ZONES_DETAILS_OUTPUT_HH

#include <iostream>

#include "tchecker/async_zg/details/output.hh"
#include "tchecker/async_zg/sync_zones/details/state.hh"
#include "tchecker/variables/clocks.hh"
#include "tchecker/variables/intvars.hh"

/*!
 \file output.hh
 \brief Outputters for asynchronous zone graphs with sync zones
 */

namespace tchecker {
  
  namespace async_zg {
    
    namespace sync_zones {
      
      namespace details {
        
        /*!
         \brief Output state
         \tparam VLOC : type of tuple of locations
         \tparam INTVARS_VAL : type of integer variables valuations
         \tparam OFFSET_ZONE : type of offset zone
         \tparam SYNC_ZONE : type of synchronized zone
         \tparam VLOC_PTR : type of pointer to tuple of locations
         \tparam INTVARS_VAL_PTR : type of pointer to integer variables valuation
         \tparam OFFSET_ZONE_PTR : type of pointer to offset zone
         \tparam SYNC_ZONE_PTR : type of pointer to synchronized zone
         \param os : output stream
         \param s : state
         \param intvar_index : index of integer variables
         \param offset_clock_index : index of offset clocks
         \param sync_clock_index : indes of synchronized clocks
         \post s has been output to os using integer variables names from intvar_index, and clock names from
         offset_clock_index and sync_clock_index
         \return os after output
         */
        template <class VLOC, class INTVARS_VAL, class OFFSET_ZONE, class SYNC_ZONE,
        class VLOC_PTR, class INTVARS_VAL_PTR, class OFFSET_ZONE_PTR, class SYNC_ZONE_PTR>
        inline std::ostream & output
        (std::ostream & os,
         tchecker::async_zg::sync_zones::details::state_t<VLOC, INTVARS_VAL, OFFSET_ZONE, SYNC_ZONE,
         VLOC_PTR, INTVARS_VAL_PTR, OFFSET_ZONE_PTR, SYNC_ZONE_PTR> const & s,
         tchecker::intvar_index_t const & intvar_index,
         tchecker::clock_index_t const & offset_clock_index,
         tchecker::clock_index_t const & sync_clock_index)
        {
          tchecker::async_zg::details::output(os, s, intvar_index, offset_clock_index);
          os << " ";
          s.sync_zone().output(os, sync_clock_index);
          return os;
        }
        
        
        
        
        /*!
         \class state_outputter_t
         \brief Outputter for states
         */
        class state_outputter_t : public tchecker::async_zg::details::state_outputter_t {
        public:
          /*!
           \brief Constructor
           \param intvar_index : index of integer variables
           \param offset_clock_index : index of offset clocks
           \param sync_clock_index : index of synchronized clocks
           \note this keeps a reference on intvar_index, a reference on offset_clock_index, and a reference on sync_clock_index
           */
          state_outputter_t(tchecker::intvar_index_t const & intvar_index,
                            tchecker::clock_index_t const & offset_clock_index,
                            tchecker::clock_index_t const & sync_clock_index)
          : tchecker::async_zg::details::state_outputter_t(intvar_index, offset_clock_index),
          _sync_clock_index(sync_clock_index)
          {}
          
          /*!
           \brief Copy constructor
           */
          state_outputter_t(tchecker::async_zg::sync_zones::details::state_outputter_t const &) = default;
          
          /*!
           \brief Move constructor
           */
          state_outputter_t(tchecker::async_zg::sync_zones::details::state_outputter_t &&) = default;
          
          /*!
           \brief Destructor
           */
          ~state_outputter_t() = default;
          
          /*!
           \brief Assignment operator (deleted)
           */
          tchecker::async_zg::sync_zones::details::state_outputter_t &
          operator= (tchecker::async_zg::sync_zones::details::state_outputter_t const &) = delete;
          
          /*!
           \brief Move-assignment operator (deleted)
           */
          tchecker::async_zg::sync_zones::details::state_outputter_t & operator= (tchecker::async_zg::sync_zones::details::state_outputter_t &&) = delete;
          
          /*!
           \brief Output state
           \tparam VLOC : type of tuple of locations
           \tparam INTVARS_VAL : type of integer variables valuations
           \tparam OFFSET_ZONE : type of offset zone
           \tparam SYNC_ZONE : type of synchronized zone
           \tparam VLOC_PTR : type of pointer to tuple of locations
           \tparam INTVARS_VAL_PTR : type of pointer to integer variables valuation
           \tparam OFFSET_ZONE_PTR : type of pointer to offset zone
           \tparam SYNC_ZONE_PTR : type of pointer to synchronized zone
           \param os : output stream
           \param s : state
           \post see tchecker::async_zg::sync_zones::details::output
           \return os after output
           */
          template <class VLOC, class INTVARS_VAL, class OFFSET_ZONE, class SYNC_ZONE,
          class VLOC_PTR, class INTVARS_VAL_PTR, class OFFSET_ZONE_PTR, class SYNC_ZONE_PTR>
          inline std::ostream & output
          (std::ostream & os,
           tchecker::async_zg::sync_zones::details::state_t<VLOC, INTVARS_VAL, OFFSET_ZONE, SYNC_ZONE,
           VLOC_PTR, INTVARS_VAL_PTR, OFFSET_ZONE_PTR, SYNC_ZONE_PTR> const & s)
          {
            return tchecker::async_zg::sync_zones::details::output(os, s, _intvar_index,
                                                                   this->_offset_clock_index,
                                                                   _sync_clock_index);
          }
        protected:
          tchecker::clock_index_t const & _sync_clock_index;    /*!< Index of synchronized clocks */
        };
        
        
        
        
        /*!
         \class transition_ouputter_t
         \brief Transition outputter
         */
        class transition_outputter_t : public tchecker::async_zg::details::transition_outputter_t {
        public:
          using tchecker::async_zg::details::transition_outputter_t::transition_outputter_t;
        };
        
      } // end of namespace details
      
    } // end of namespace sync_zones
    
  } // end of namespace async_zg
  
} // end of namespace tchecker

#endif // TCHECKER_ASYNC_ZG_SYNC_ZONES_DETAILS_OUTPUT_HH


