/**
 * Attention: This is a smaller version of the original stb.h file that just contains the compression functions
 * needed in IrrIMGUI Unit Test to compress a TTF.
 *
 * The original file can be found here: https://github.com/nothings/stb
 *
 * Note that this file is not under MIT license, but has a different public domain license defined by the project side.
 *
 * This is the original header:
 */

/* stb.h - v2.25 - Sean's Tool Box -- public domain -- http://nothings.org/stb.h
          no warranty is offered or implied; use this code at your own risk

   This is a single header file with a bunch of useful utilities
   for getting stuff done in C/C++.

   Documentation: http://nothings.org/stb/stb_h.html
   Unit tests:    http://nothings.org/stb/stb.c


 ============================================================================
   You MUST                                                                  
                                                                             
      #define STB_DEFINE                                                     
                                                                             
   in EXACTLY _one_ C or C++ file that includes this header, BEFORE the
   include, like this:                                                                
                                                                             
      #define STB_DEFINE                                                     
      #include "stb.h"
      
   All other files should just #include "stb.h" without the #define.
 ============================================================================


Version History

   2.25   various warning & bugfixes
   2.24   various warning & bugfixes
   2.23   fix 2.22
   2.22   64-bit fixes from '!='; fix stb_sdict_copy() to have preferred name
   2.21   utf-8 decoder rejects "overlong" encodings; attempted 64-bit improvements
   2.20   fix to hash "copy" function--reported by someone with handle "!="
   2.19   ???
   2.18   stb_readdir_subdirs_mask
   2.17   stb_cfg_dir
   2.16   fix stb_bgio_, add stb_bgio_stat(); begin a streaming wrapper
   2.15   upgraded hash table template to allow:
            - aggregate keys (explicit comparison func for EMPTY and DEL keys)
            - "static" implementations (so they can be culled if unused)
   2.14   stb_mprintf
   2.13   reduce identifiable strings in STB_NO_STB_STRINGS
   2.12   fix STB_ONLY -- lots of uint32s, TRUE/FALSE things had crept in
   2.11   fix bug in stb_dirtree_get() which caused "c://path" sorts of stuff
   2.10   STB_F(), STB_I() inline constants (also KI,KU,KF,KD)
   2.09   stb_box_face_vertex_axis_side
   2.08   bugfix stb_trimwhite()
   2.07   colored printing in windows (why are we in 1985?)
   2.06   comparison functions are now functions-that-return-functions and
          accept a struct-offset as a parameter (not thread-safe)
   2.05   compile and pass tests under Linux (but no threads); thread cleanup
   2.04   stb_cubic_bezier_1d, smoothstep, avoid dependency on registry
   2.03   ?
   2.02   remove integrated documentation
   2.01   integrate various fixes; stb_force_uniprocessor
   2.00   revised stb_dupe to use multiple hashes
   1.99   stb_charcmp
   1.98   stb_arr_deleten, stb_arr_insertn
   1.97   fix stb_newell_normal()
   1.96   stb_hash_number()
   1.95   hack stb__rec_max; clean up recursion code to use new functions
   1.94   stb_dirtree; rename stb_extra to stb_ptrmap
   1.93   stb_sem_new() API cleanup (no blockflag-starts blocked; use 'extra')
   1.92   stb_threadqueue--multi reader/writer queue, fixed size or resizeable
   1.91   stb_bgio_* for reading disk asynchronously
   1.90   stb_mutex uses CRITICAL_REGION; new stb_sync primitive for thread
          joining; workqueue supports stb_sync instead of stb_semaphore
   1.89   support ';' in constant-string wildcards; stb_mutex wrapper (can
          implement with EnterCriticalRegion eventually)
   1.88   portable threading API (only for win32 so far); worker thread queue
   1.87   fix wildcard handling in stb_readdir_recursive
   1.86   support ';' in wildcards
   1.85   make stb_regex work with non-constant strings;
               beginnings of stb_introspect()
   1.84   (forgot to make notes)
   1.83   whoops, stb_keep_if_different wasn't deleting the temp file
   1.82   bring back stb_compress from stb_file.h for cmirror
   1.81   various bugfixes, STB_FASTMALLOC_INIT inits FASTMALLOC in release
   1.80   stb_readdir returns utf8; write own utf8-utf16 because lib was wrong
   1.79   stb_write
   1.78   calloc() support for malloc wrapper, STB_FASTMALLOC
   1.77   STB_FASTMALLOC
   1.76   STB_STUA - Lua-like language; (stb_image, stb_csample, stb_bilinear)
   1.75   alloc/free array of blocks; stb_hheap bug; a few stb_ps_ funcs;
          hash*getkey, hash*copy; stb_bitset; stb_strnicmp; bugfix stb_bst
   1.74   stb_replaceinplace; use stdlib C function to convert utf8 to UTF-16
   1.73   fix performance bug & leak in stb_ischar (C++ port lost a 'static')
   1.72   remove stb_block, stb_block_manager, stb_decompress (to stb_file.h)
   1.71   stb_trimwhite, stb_tokens_nested, etc.
   1.70   back out 1.69 because it might problemize mixed builds; stb_filec()
   1.69   (stb_file returns 'char *' in C++)
   1.68   add a special 'tree root' data type for stb_bst; stb_arr_end
   1.67   full C++ port. (stb_block_manager)
   1.66   stb_newell_normal
   1.65   stb_lex_item_wild -- allow wildcard items which MUST match entirely
   1.64   stb_data
   1.63   stb_log_name
   1.62   stb_define_sort; C++ cleanup
   1.61   stb_hash_fast -- Paul Hsieh's hash function (beats Bob Jenkins'?)
   1.60   stb_delete_directory_recursive
   1.59   stb_readdir_recursive
   1.58   stb_bst variant with parent pointer for O(1) iteration, not O(log N)
   1.57   replace LCG random with Mersenne Twister (found a public domain one)
   1.56   stb_perfect_hash, stb_ischar, stb_regex
   1.55   new stb_bst API allows multiple BSTs per node (e.g. secondary keys)
   1.54   bugfix: stb_define_hash, stb_wildmatch, regexp
   1.53   stb_define_hash; recoded stb_extra, stb_sdict use it
   1.52   stb_rand_define, stb_bst, stb_reverse
   1.51   fix 'stb_arr_setlen(NULL, 0)'
   1.50   stb_wordwrap
   1.49   minor improvements to enable the scripting language
   1.48   better approach for stb_arr using stb_malloc; more invasive, clearer
   1.47   stb_lex (lexes stb.h at 1.5ML/s on 3Ghz P4; 60/70% of optimal/flex)
   1.46   stb_wrapper_*, STB_MALLOC_WRAPPER
   1.45   lightly tested DFA acceleration of regexp searching
   1.44   wildcard matching & searching; regexp matching & searching
   1.43   stb_temp
   1.42   allow stb_arr to use stb_malloc/realloc; note this is global
   1.41   make it compile in C++; (disable stb_arr in C++)
   1.40   stb_dupe tweak; stb_swap; stb_substr
   1.39   stb_dupe; improve stb_file_max to be less stupid
   1.38   stb_sha1_file: generate sha1 for file, even > 4GB
   1.37   stb_file_max; partial support for utf8 filenames in Windows
   1.36   remove STB__NO_PREFIX - poor interaction with IDE, not worth it
          streamline stb_arr to make it separately publishable
   1.35   bugfixes for stb_sdict, stb_malloc(0), stristr
   1.34   (streaming interfaces for stb_compress)
   1.33   stb_alloc; bug in stb_getopt; remove stb_overflow
   1.32   (stb_compress returns, smaller&faster; encode window & 64-bit len)
   1.31   stb_prefix_count
   1.30   (STB__NO_PREFIX - remove stb_ prefixes for personal projects)
   1.29   stb_fput_varlen64, etc.
   1.28   stb_sha1
   1.27   ?
   1.26   stb_extra
   1.25   ?
   1.24   stb_copyfile
   1.23   stb_readdir
   1.22   ?
   1.21   ?
   1.20   ?
   1.19   ?
   1.18   ?
   1.17   ?
   1.16   ?
   1.15   stb_fixpath, stb_splitpath, stb_strchr2
   1.14   stb_arr
   1.13   ?stb, stb_log, stb_fatal
   1.12   ?stb_hash2
   1.11   miniML
   1.10   stb_crc32, stb_adler32
   1.09   stb_sdict
   1.08   stb_bitreverse, stb_ispow2, stb_big32
          stb_fopen, stb_fput_varlen, stb_fput_ranged
          stb_fcmp, stb_feq
   1.07   (stb_encompress)
   1.06   stb_compress
   1.05   stb_tokens, (stb_hheap)
   1.04   stb_rand
   1.03   ?(s-strings)
   1.02   ?stb_filelen, stb_tokens
   1.01   stb_tolower
   1.00   stb_hash, stb_intcmp
          stb_file, stb_stringfile, stb_fgets
          stb_prefix, stb_strlower, stb_strtok
          stb_image
          (stb_array), (stb_arena)

Parenthesized items have since been removed.

LICENSE

This software is in the public domain. Where that dedication is not
recognized, you are granted a perpetual, irrevocable license to copy,
distribute, and modify this file as you see fit.

CREDITS

 Written by Sean Barrett.

 Fixes:
  Philipp Wiesemann
  Robert Nix
  r-lyeh
  blackpawn
  Mojofreem@github
  Ryan Whitworth
  Vincent Isambart
*/

#include <cstdio>
#include <assert.h>
#include <string.h>

#ifndef STB__INCLUDE_STB_H
#define STB__INCLUDE_STB_H

#if defined(STB_USE_LONG_FOR_32_BIT_INT) || defined(STB_LONG32)
  typedef unsigned long  stb_uint32;
  typedef          long  stb_int32;
#else
  typedef unsigned int   stb_uint32;
  typedef          int   stb_int32;
#endif

typedef unsigned int  stb_uint;
typedef unsigned char stb_uchar;
stb_uint stb_compress (stb_uchar *out,stb_uchar *in,stb_uint len);
size_t stb_get_compression_length(size_t const length);

static  stb_uint stb__hashsize = 32768;
static stb_uchar *stb__out;
static FILE      *stb__outfile;
static stb_uint   stb__outbytes;
static int stb__window = static_cast<int>(0x40000); // 256K
static stb_uint32 stb__running_adler;

static void stb__write(unsigned char v)
{
   fputc(v, stb__outfile);
   ++stb__outbytes;
}

static void stb_out(unsigned char v)
{
  if (stb__out)
  {
    *stb__out++ = (stb_uchar) (v);
  }
  else
  {
    stb__write((stb_uchar) (v));
  }
  return;
}

#define stb__hc2(q,h,c,d)   (((h) << 14) + ((h) >> 18) + (q[c] << 7) + q[d])
#define stb__hc3(q,c,d,e)   ((q[c] << 14) + (q[d] << 7) + q[e])

stb_uint stb_adler32(stb_uint adler32, stb_uchar *buffer, stb_uint buflen)
{
   const unsigned long ADLER_MOD = 65521;
   unsigned long s1 = adler32 & 0xffff, s2 = adler32 >> 16;
   unsigned long blocklen, i;

   blocklen = buflen % 5552;
   while (buflen) {
      for (i=0; i + 7 < blocklen; i += 8) {
         s1 += buffer[0], s2 += s1;
         s1 += buffer[1], s2 += s1;
         s1 += buffer[2], s2 += s1;
         s1 += buffer[3], s2 += s1;
         s1 += buffer[4], s2 += s1;
         s1 += buffer[5], s2 += s1;
         s1 += buffer[6], s2 += s1;
         s1 += buffer[7], s2 += s1;

         buffer += 8;
      }

      for (; i < blocklen; ++i)
         s1 += *buffer++, s2 += s1;

      s1 %= ADLER_MOD, s2 %= ADLER_MOD;
      buflen -= blocklen;
      blocklen = 5552;
   }
   return (s2 << 16) + s1;
}

static void stb_out3(stb_uint v) { stb_out(v >> 16); stb_out(v >> 8); stb_out(v); }
static void stb_out4(stb_uint v) { stb_out(v >> 24); stb_out(v >> 16);
                                   stb_out(v >> 8 ); stb_out(v);                  }

static void stb_out2(stb_uint v)
{
   stb_out(v >> 8);
   stb_out(v);
}

static void outliterals(stb_uchar *in, size_t numlit)
{
   while (numlit > 65536) {
      outliterals(in,65536);
      in     += 65536;
      numlit -= 65536;
   }

   if      (numlit ==     0)    ;
   else if (numlit <=    32)    stb_out (static_cast<stb_uint>(0x000020 + numlit-1));
   else if (numlit <=  2048)    stb_out2(static_cast<stb_uint>(0x000800 + numlit-1));
   else /*  numlit <= 65536) */ stb_out3(static_cast<stb_uint>(0x070000 + numlit-1));

   if (stb__out) {
      memcpy(stb__out,in,numlit);
      stb__out += numlit;
   } else
      fwrite(in, 1, numlit, stb__outfile);
}

static unsigned int stb_matchlen(stb_uchar *m1, stb_uchar *m2, stb_uint maxlen)
{
   stb_uint i;
   for (i=0; i < maxlen; ++i)
      if (m1[i] != m2[i]) return i;
   return i;
}

static int stb_not_crap(size_t best, size_t dist)
{
   return   ((best > 2  &&  dist <= 0x00100)
          || (best > 5  &&  dist <= 0x04000)
          || (best > 7  &&  dist <= 0x80000));
}

static int stb_compress_chunk(stb_uchar *history,
                              stb_uchar *start,
                              stb_uchar *end,
                              int length,
                              int *pending_literals,
                              stb_uchar **chash,
                              stb_uint mask)
{
   int window = stb__window;
   stb_uint match_max;
   stb_uchar *lit_start = start - *pending_literals;
   stb_uchar *q = start;

   #define STB__SCRAMBLE(h)   (((h) + ((h) >> 16)) & mask)

   // stop short of the end so we don't scan off the end doing
   // the hashing; this means we won't compress the last few bytes
   // unless they were part of something longer
   while (q < start+length && q+12 < end) {
      int m;
      stb_uint h1,h2,h3,h4, h;
      stb_uchar *t;
      size_t best = 2, dist=0;

      if (q+65536 > end)
         match_max = static_cast<stb_uint>(static_cast<size_t>(end-q));
      else
         match_max = 65536;

      #define stb__nc(b,d)  ((d) <= window && ((b) > 9 || stb_not_crap(b,d)))

      #define STB__TRY(t,p)  /* avoid retrying a match we already tried */ \
                      if (p ? dist != q-t : 1)                             \
                      if ((m = stb_matchlen(t, q, match_max)) > best)     \
                      if (stb__nc(m,q-(t)))                                \
                          best = m, dist = q - (t)

      // rather than search for all matches, only try 4 candidate locations,
      // chosen based on 4 different hash functions of different lengths.
      // this strategy is inspired by LZO; hashing is unrolled here using the
      // 'hc' macro
      h = stb__hc3(q,0, 1, 2); h1 = STB__SCRAMBLE(h);
                                      t = chash[h1]; if (t) STB__TRY(t,0);
      h = stb__hc2(q,h, 3, 4); h2 = STB__SCRAMBLE(h);
      h = stb__hc2(q,h, 5, 6);        t = chash[h2]; if (t) STB__TRY(t,1);
      h = stb__hc2(q,h, 7, 8); h3 = STB__SCRAMBLE(h);
      h = stb__hc2(q,h, 9,10);        t = chash[h3]; if (t) STB__TRY(t,1);
      h = stb__hc2(q,h,11,12); h4 = STB__SCRAMBLE(h);
                                      t = chash[h4]; if (t) STB__TRY(t,1);

      // because we use a shared hash table, can only update it
      // _after_ we've probed all of them
      chash[h1] = chash[h2] = chash[h3] = chash[h4] = q;

      if (best > 2)
         assert(dist > 0);

      // see if our best match qualifies
      if (best < 3) { // fast path literals
         ++q;
      } else if (best > 2  &&  best <= 0x80    &&  dist <= 0x100) {
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         stb_out(static_cast<unsigned char>(0x80 + best-1));
         stb_out(static_cast<unsigned char>(dist-1));
      } else if (best > 5  &&  best <= 0x100   &&  dist <= 0x4000) {
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         stb_out2(static_cast<stb_uint>(0x4000 + dist-1));
         stb_out(static_cast<unsigned char>(best-1));
      } else if (best > 7  &&  best <= 0x100   &&  dist <= 0x80000) {
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         stb_out3(static_cast<stb_uint>(0x180000 + dist-1));
         stb_out(static_cast<unsigned char>(best-1));
      } else if (best > 8  &&  best <= 0x10000 &&  dist <= 0x80000) {
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         stb_out3(static_cast<stb_uint>(0x100000 + dist-1));
         stb_out2(static_cast<stb_uint>(best-1));
      } else if (best > 9                      &&  dist <= 0x1000000) {
         if (best > 65536) best = 65536;
         outliterals(lit_start, q-lit_start); lit_start = (q += best);
         if (best <= 0x100) {
            stb_out(0x06);
            stb_out3(static_cast<stb_uint>(dist-1));
            stb_out(static_cast<unsigned char>(best-1));
         } else {
            stb_out(0x04);
            stb_out3(static_cast<stb_uint>(dist-1));
            stb_out2(static_cast<stb_uint>(best-1));
         }
      } else {  // fallback literals if no match was a balanced tradeoff
         ++q;
      }
   }

   // if we didn't get all the way, add the rest to literals
   if (q-start < length)
      q = start+length;

   // the literals are everything from lit_start to q
   *pending_literals = (static_cast<stb_uint>(q - lit_start));

   stb__running_adler = stb_adler32(stb__running_adler, start, static_cast<stb_uint>(q - start));
   return static_cast<stb_uint>(q - start);
}

static int stb_compress_inner(stb_uchar *input, stb_uint length)
{
   int literals = 0;
   stb_uint len,i;

   stb_uchar **chash;
   chash = (stb_uchar**) malloc(stb__hashsize * sizeof(stb_uchar*));
   if (chash == NULL) return 0; // failure
   for (i=0; i < stb__hashsize; ++i)
      chash[i] = NULL;

   // stream signature
   stb_out(0x57); stb_out(0xbc);
   stb_out2(0);

   stb_out4(0);       // 64-bit length requires 32-bit leading 0
   stb_out4(length);
   stb_out4(stb__window);

   stb__running_adler = 1;

   len = stb_compress_chunk(input, input, input+length, length, &literals, chash, stb__hashsize-1);
   assert(len == length);

   outliterals(input+length - literals, literals);

   free(chash);

   stb_out2(0x05fa); // end opcode

   stb_out4(stb__running_adler);

   return 1; // success
}

stb_uint stb_compress(stb_uchar *out, stb_uchar *input, stb_uint length)
{
   stb__out = out;
   stb__outfile = NULL;

   stb_compress_inner(input, length);

   return static_cast<stb_uint>(stb__out - out);
}

size_t stb_get_compression_length(size_t const length)
{
  return length + 512 + (length >> 2); // total guess
}

#ifdef STB_DEFINE

#endif // STB_DEFINE

#endif // STB_INCLUDE_STB_H

