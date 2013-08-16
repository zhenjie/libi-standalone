/**
 * @file   KVS.cpp
 * @author Zhenjie Chen <zhenjie@cs.unm.edu>
 * @date   Fri Jul 12 14:01:22 2013
 * 
 * @brief  xxx
 * 
 * 
 */

#include "libi/KVS.h"
#include "cpp_zhtclient.h"

using namespace LIBI;
using namespace LIBI::KVS;

/** 
 * Default constructor
 * 
 */
ZHT::ZHT()
{
   initialized = false;
}

ZHT::ZHT(const string zht_conf, const string neighbor_conf)
{
   init(zht_conf, neighbor_conf);
}

ZHT::~ZHT()
{
   finalize();
}

libi_rc_e
ZHT::init(const string &zht_conf, const string &neighbor_conf)
{
   if (zht_conf.empty() || neighbor_conf.empty())
      return LIBI_EINIT;

   /// TODO: when there are errors in zc.init
   zc.init(zht_conf, neighbor_conf);

   initialized = true;

   return LIBI_OK;
}

libi_rc_e
ZHT::finalize()
{
   if(initialized)
   {
      zc.teardown();
      initialized = false;
      return LIBI_OK;
   }

   return LIBI_NO;
}

libi_rc_e
ZHT::put(const string &key, const string &value)
{
   int rc = zc.insert(key, value);

   if (0 == rc)
      return LIBI_OK;
   else
      return LIBI_NO;
}

libi_rc_e
ZHT::get(const string &key, string &value)
{
   int rc = zc.lookup(key, value);

   if (0 == rc)
      return LIBI_OK;
   else
      return LIBI_NO;
}

libi_rc_e
ZHT::fence()
{
}


