/* This file was generated by scm2c from source file "ents.scm" */

extern LCK **lck_tab;

extern ENTRY **buk_tab;

extern ENTRY **ent_tab;

extern long num_ents_ct;

extern int num_buks;

extern int blk_size;

extern int cache_ent_enable_P;

SCM_EXPORT int ents_ent_write P((ENTRY *ent));

extern int flush_ent_cntr;

extern LCK *flush_ent_lck;
SCM_EXPORT int ents_flush P((long trynum,long flushnum));

SCM_EXPORT int ent_flush_P P((ENTRY *tent));

SCM_EXPORT void release_ent P((ENTRY *ent,int accmode));

SCM_EXPORT int ents_ent_update_access_P P((ENTRY *ent,int old_accmode,int new_accmode));

extern int free_buk_cntr;

extern ENTRY *free_ents;

extern LCK *free_ent_lck;
SCM_EXPORT ENTRY *get_free_free_ent P((void));

SCM_EXPORT void splice_out_ent P((SEGD *seg,long blk_num,ENTRY *buk,ENTRY *ent));

SCM_EXPORT void recycle_ent P((ENTRY *ent));

SCM_EXPORT ENTRY *select_idle_ent P((SEGD *lseg,long lblk_num));

SCM_EXPORT ENTRY *reclaim_ent P((ENTRY *ent,SEGD *lseg,long lblk_num));

SCM_EXPORT ENTRY *try_get_free_ent P((SEGD *lseg,long lblk_num));

SCM_EXPORT ENTRY *allocate_ent P((void));

SCM_EXPORT void ent_copy P((ENTRY *to_ent,ENTRY *from_ent));

SCM_EXPORT int get_ent_copy P((ENTRY *to_ent,SEGD *seg,long blk_num));

SCM_EXPORT void flush_flc P((SEGD *seg,int fullness));

SCM_EXPORT int initload_flc_P P((SEGD *seg));

SCM_EXPORT void amnesia_ent P((ENTRY *ent));

SCM_EXPORT int blk_free P((ENTRY *ent));

SCM_EXPORT int flc_fill P((SEGD *seg));

SCM_EXPORT int flc_proc P((unsigned char *keystr,int klen,unsigned char *vstr,int vlen,long *long_ara));

SCM_EXPORT ENTRY *create_new_blk_ent P((SEGD *seg));

SCM_EXPORT ENTRY *try_get_ent P((SEGD *seg,long blk_num,int accmode));

SCM_EXPORT ENTRY *chain_find_ent P((HAND *han,int accmode,unsigned char *key_str,int k_len,int *pkt));

SCM_EXPORT ENTRY *chain_find_prev_ent P((HAND *han,int accmode,unsigned char *key_str,int k_len,int *pkt));

SCM_EXPORT ENTRY *get_ent P((SEGD *seg,long blk_num,int accmode));

SCM_EXPORT ENTRY *switch_ent P((ENTRY *old_ent,int oldacc,long new_num,int newacc));

SCM_EXPORT void check_blk P((unsigned char *blk));

SCM_EXPORT void check_key_order P((unsigned char *blk));

SCM_EXPORT int do_seg_buffers P((SEGD *seg,int_function func));

SCM_EXPORT int check_buffer P((ENTRY *ent));

SCM_EXPORT void check_access P((void));

SCM_EXPORT int flush_buffer P((ENTRY *ent));

SCM_EXPORT int purge_buffer P((ENTRY *ent));
