/**
 * @file   KVS.h
 * @author Zhenjie Chen <zhenjie@cs.unm.edu>
 * @date   Mon Jul  8 03:37:52 2013
 * 
 * @brief  Key Value Store definition
 * 
 * 
 */

#ifndef LIBI_KVS_H
#define LIBI_KVS_H

#include "libi/libi_api_std.h"
#include "cpp_zhtclient.h"

#include <string>

using std::string;

namespace LIBI
{
   namespace KVS
   {
      enum
      {
         LIBI_KVS_ZHT_EINIT // initiation
      };

      class ZHT
      {
      public:
         ZHT();
         ZHT(const string zht_conf, const string neighbor_conf);
         ~ZHT();

         libi_rc_e init(const string &zht_conf, const string &neighbor_conf);
         libi_rc_e finalize();
         libi_rc_e put(const string &key, const string &value);
         libi_rc_e fence();
         libi_rc_e get(const string &key, string &value);

      private:
         bool initialized;
         ZHTClient zc;
      };
      
      /* class PMI */
      /* { */
      /* }; */
   }
}

#endif // LIBI_KVS_H
