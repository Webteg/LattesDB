/* This file was generated by scm2c from source file "prev.scm" */
/*  "prev.scm" WB-tree File Based Associative String Data Base System. */
/*  Copyright (C) 1991, 1992, 1993, 2000 Free Software Foundation, Inc. */
/*  */
/*  This program is free software: you can redistribute it and/or modify */
/*  it under the terms of the GNU Lesser General Public License as */
/*  published by the Free Software Foundation, either version 3 of the */
/*  License, or (at your option) any later version. */
/*  */
/*  This program is distributed in the hope that it will be useful, but */
/*  WITHOUT ANY WARRANTY; without even the implied warranty of */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU */
/*  Lesser General Public License for more details. */
/*  */
/*  You should have received a copy of the GNU Lesser General Public */
/*  License along with this program.  If not, see */
/*  <http://www.gnu.org/licenses/>. */


#include "wbsys.h"


ENTRY *chain_prev_find(ENTRY *ent,int accmode,unsigned char *key_str,int k_len,int *pkt,ENTRY *prev_ent,int prev_pos)
{
L_chain_prev_find:
  {
    unsigned char *blk = ent_blk(ent);
    blk_find_pos(blk, key_str, k_len, pkt);
    if (((pkt_match_type(pkt))==(pastend))
        && (!(end_of_chain_P(blk))))
      {
	long nxt_num = blk_nxt_id(blk);
	SEGD *seg = ent_seg(ent);
	ENTRY *nent = 0;
	int empty_blk_P = (pkt_match_pos(pkt))==(blk_data_start);
	int ppos = empty_blk_P
	  ?prev_pos
	  :pkt_prev_match_pos(pkt);
	if (empty_blk_P)
	  {
	    release_ent(ent, accmode);
	  }
	else {
	  if (prev_ent)
	    release_ent(prev_ent, accnone);
	  ents_ent_update_access_P(ent, accmode, accnone);
	  prev_ent = ent;
	}
	nent = get_ent(seg, nxt_num, accmode);
	{
	  ent = nent;
	  prev_pos = ppos;
	  goto L_chain_prev_find;
	}
      }
    else if ((pkt_match_pos(pkt))==(blk_data_start))
      if (prev_ent)
	{
	  release_ent(ent, accmode);
	  ents_ent_update_access_P(prev_ent, accnone, accmode);
	  pkt_set_match_type(pkt, match);
	  pkt_set_match_pos(pkt, prev_pos);
	  return prev_ent;
	}
      else {
	pkt_set_match_type(pkt, pastend);
	pkt_set_match_pos(pkt, 0);
	return ent;
      }
    else {
      if (prev_ent)
	release_ent(prev_ent, accnone);
      pkt_set_match_type(pkt, match);
      pkt_set_match_pos(pkt, pkt_prev_match_pos(pkt));
      return ent;
    }
  }
}


int str_gtr_P(unsigned char *a_str,int a_pos,int a_len,unsigned char *b_str,int b_pos,int b_len)
{
  {
    int i = 0;
    int ap = a_pos;
    int bp = b_pos;
L_loop:
    if ((i)>=(a_len))
      return 0;
    else if ((i)>=(b_len))
      return !0;
    else if (((((unsigned char*)(a_str))[ap]))<((((unsigned char*)(b_str))[bp])))
      return 0;
    else if (((((unsigned char*)(b_str))[bp]))<((((unsigned char*)(a_str))[ap])))
      return !0;
    else {
      i = (i)+1;
      ap = (ap)+1;
      bp = (bp)+1;
      goto L_loop;
    }
  }
}

/*  PREV-KEY-ENT [was PREV-KEY] assumes entry with ACCNONE accmode to BLK. */
/*  It either returns the  entry contining PREV(key) (with READ access) */
/*  (and pos(prev) in PKT, type=MATCH) or #f, if there is no such key. */
/*  call PREV-KEY-ENT with ROOT block... */

/*  NOTE: PREV:PREV-K-ENT still needs the PENT kluge to keep the block */
/*  unchanged while it works. */

ENTRY *prev_prev_k_ent(ENTRY *ent,unsigned char *key_str,int k_len,int level,int *pkt)
{
  if (ent)
    {
      ENTRY *pent = get_ent(ent_seg(ent), ent_id(ent), accnone);
      ent = chain_prev_find(ent, accread, key_str, k_len, pkt, 0, 0);
      {
	ENTRY *res_ent = ent;
	if ((pkt_match_type(pkt))!=(match))
	  {
	    release_ent(ent, accread);
	    res_ent = prev_prev_k_ent(prev_blk_ent(pent, level), key_str, k_len, level, pkt);
	  }
	release_ent(pent, accnone);
	return res_ent;
      }
    }
  else return 0;
}


ENTRY *prev_key_ent(ENTRY *ent,unsigned char *key_str,int k_len,int level,int *pkt)
{
  if (ent)
    return prev_prev_k_ent(prev_find_prev_ent(ent, level,  -1, key_str, k_len), key_str, k_len, level, pkt);
  else return 0;
}

/*  CHAIN-TO-PREV-ENT: subroutine for PREV-BLK-ENT */
/*  this routine chains fwd from FROM-ENT to imm predecessor of GOAL-BLK */
/*  called with FROM-ENT open with ACCREAD; assumes GOAL-BLOCK-NO Name-locked */
/*  returns an ENT open ACCREAD unless missed block, which returns #f */
/*  (routine also checks if its past key) */


ENTRY *chain_to_prev_ent(ENTRY *from_ent,long goal_blk_num,unsigned char *goal_key_str,int key_len)
{
L_chain_to_prev_ent:
  {
    unsigned char *from_blk = ent_blk(from_ent);
    if ((blk_nxt_id(from_blk))==(goal_blk_num))
      return from_ent;
    else if (end_of_chain_P(from_blk))
      {
	dprintf((diagout,
	 ">>>>ERROR<<<< %s: hit end of %ld:%ld lev=%d %.*s\n",
	 "chain_to_prev_ent",
	 ent_id(from_ent),
	 goal_blk_num,
	 blk_level(from_blk),
	 key_len,
	 goal_key_str));
	return 0;
      }
    else {
      int b_pos = blk_data_start;
      if (str_gtr_P(from_blk, (b_pos)+2, field_len(from_blk, (b_pos)+1), goal_key_str, 0, key_len))
	{
	  dprintf((diagout,
	 ">>>>ERROR<<<< %s: missed blk %ld:%ld lev=%d %.*s\n",
	 "chain_to_prev_ent",
	 ent_id(from_ent),
	 goal_blk_num,
	 blk_level(from_blk),
	 key_len,
	 goal_key_str));
	  return 0;
	}
      else {
	from_ent = switch_ent(from_ent, accread, blk_nxt_id(from_blk), accread);
	goto L_chain_to_prev_ent;
      }
    }
  }
}

/*  there must be a more efficient way to check this !!! */

int at_root_level_P(SEGD *seg,unsigned char *blk)
{
  if (root_P(blk))
    return !0;
  else {
    ENTRY *rent = get_ent(seg, blk_top_id(blk), accread);
    unsigned char *rblk = ent_blk(rent);
    int rlevel = blk_level(rblk);
    int res_P = (blk_level(blk))==(rlevel);
    release_ent(rent, accread);
    return res_P;
  }
}

/*  PREV-BLK-ENT [was PREV-BLK] is called with ENT (with ACCNONE accmode) */
/*  which IS PRESERVED. IT finds the block that precedes ENT, or #f. */
/*  It returns a (second) entry with READ access or #f. */
/*  TBD - shouldn't it release ENT if returning #f? */
/*  (no, not as things are now -- rjz) */

ENTRY *prev_blk_ent(ENTRY *ent,int level)
{
  ents_ent_update_access_P(ent, accnone, accread);
  {
    unsigned char *blk = ent_blk(ent);
    ents_ent_update_access_P(ent, accread, accnone);
    if (root_P(blk))
      return 0;
    else {
      int skey_pos = split_key_pos(blk);
      if (0 < (skey_pos))
	{
	  long top_num = blk_top_id(blk);
	  SEGD *seg = ent_seg(ent);
	  long goal_blk_num = ent_id(ent);
	  unsigned char new_str[0x100];
	  int k_len = recon_this_key(blk, skey_pos, new_str, 0, 0x100);
	  if (at_root_level_P(seg, blk))
	    {
	      dprintf((diagout, "%s code which has never been run!!\n", "prev_blk_ent"));
	      return chain_to_prev_ent(get_ent(seg, top_num, accread), goal_blk_num, new_str, k_len);
	    }
	  else {
	    int pkt[pkt_size];
	    ent = prev_key_ent(get_ent(seg, top_num, accnone), new_str, k_len, (level)+1, pkt);
	    if ((ent)==0)
	      return 0;
	    else {
	      int nxt_pos = next_field(ent_blk(ent), 1+(pkt_match_pos(pkt)));
	      long num = 0x0L;
	      if ((nxt_pos)==(blk_end(ent_blk(ent))))
		{
		  dprintf((diagout,
	 "%s: I'm confused: at split key of blk %ld:%ld",
	 "prev_blk_ent",
	 seg_id(ent_seg(ent)),
	 ent_id(ent)));
		  num = (pkt_match_pos(pkt))-0x4L;
		}
	      else num = 0x1L+(nxt_pos);
	      return chain_to_prev_ent(switch_ent(ent, accread, str2long(ent_blk(ent), num), accread), goal_blk_num, new_str, k_len);
	    }
	  }
	}
      else return 0;
    }
  }
}

/*  FIND-PREV-ENT: called (like FIND-NEXT) with ACCNONE accmode on ENT. */
/*  Returns a new ENT with ACCREAD accmode. Will always return an ENT */
/*  unless some GET-ENT fails. */


ENTRY *prev_find_prev_ent(ENTRY *ent,int desired_level,int last_level,unsigned char *key_str,int k_len)
{
L_prev_find_prev_ent:
  if (ent)
    if (ents_ent_update_access_P(ent, accnone, accread))
      {
	unsigned char *blk = ent_blk(ent);
	if ((blk_level(blk))==(desired_level))
	  return ent;
	else if ((blk_level(blk))<(desired_level))
	  {
	    dprintf((diagout, ">>>>ERROR<<<< %s: bad blk level\n", "find_prev_ent"));
	    return 0;
	  }
	else if (((last_level)>=0)
	    && ((blk_level(blk))!=((last_level)-1)))
	  {
	    dprintf((diagout,
	 ">>>>ERROR<<<< %s: bad blk level %d last=%d in %ld:%ld\n",
	 "find_prev_ent",
	 blk_level(blk),
	 last_level,
	 seg_id(ent_seg(ent)),
	 ent_id(ent)));
	    return 0;
	  }
	else {
	  int pkt[pkt_size];
	  ent = chain_find(ent, accread, key_str, k_len, pkt);
	  if (ent)
	    {
	      int nxt_pos = next_field(ent_blk(ent), 1+(pkt_match_pos(pkt)));
	      int ptr_pos = (nxt_pos)==(blk_end(ent_blk(ent)))
		?(pkt_match_pos(pkt))-4
		:1+(nxt_pos);
	      {
		ENTRY *T_ent = switch_ent(ent, accread, str2long(ent_blk(ent), ptr_pos), accnone);
		last_level = blk_level(ent_blk(ent));
		ent = T_ent;
		goto L_prev_find_prev_ent;
	      }
	    }
	  else return 0;
	}
      }
    else return 0;
  else return 0;
}
