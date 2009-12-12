/************************************************************************
*            Atrinik, a Multiplayer Online Role Playing Game            *
*                                                                       *
*                     Copyright (C) 2009 Alex Tokar                     *
*                                                                       *
* Fork from Daimonin (Massive Multiplayer Online Role Playing Game)     *
* and Crossfire (Multiplayer game for X-windows).                       *
*                                                                       *
* This program is free software; you can redistribute it and/or modify  *
* it under the terms of the GNU General Public License as published by  *
* the Free Software Foundation; either version 2 of the License, or     *
* (at your option) any later version.                                   *
*                                                                       *
* This program is distributed in the hope that it will be useful,       *
* but WITHOUT ANY WARRANTY; without even the implied warranty of        *
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
* GNU General Public License for more details.                          *
*                                                                       *
* You should have received a copy of the GNU General Public License     *
* along with this program; if not, write to the Free Software           *
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.             *
*                                                                       *
* The author can be reached at admin@atrinik.org                        *
************************************************************************/

/* anim.c */
extern void free_all_anim();
extern void init_anim();
extern int find_animation(char *name);
extern void animate_object(object *op, int count);

/* arch.c */
extern object *get_archetype_by_object_name(const char *name);
extern archetype *get_skill_archetype(int skillnr);
extern int item_matched_string(object *pl, object *op, const char *name);
extern void init_archetypes();
extern void arch_info(object *op);
extern void dump_arch(archetype *at);
extern void dump_all_archetypes();
extern void free_all_archs();
extern object *arch_to_object(archetype *at);
extern object *get_archetype(const char *name);
extern archetype *find_archetype(const char *name);
extern object *clone_arch(int type);

/* button.c */
extern void push_button(object *op);
extern void update_button(object *op);
extern void update_buttons(mapstruct *m);
extern void use_trigger(object *op);
extern int check_altar_sacrifice(object *altar, object *sacrifice);
extern int operate_altar(object *altar, object **sacrifice);
extern int check_trigger(object *op, object *cause);
extern void add_button_link(object *button, mapstruct *map, int connected);
extern void remove_button_link(object *op);
extern int get_button_value(object *button);
extern void do_mood_floor(object *op, object *op2);
extern object *check_inv_recursive(object *op, const object *trig);
extern void check_inv(object *op, object *trig);

/* exp.c */
extern uint32 level_exp(int level, double expmul);
extern sint32 add_exp(object *op, int exp, int skill_nr);
extern void player_lvl_adj(object *who, object *op);
extern int adjust_exp(object *pl, object *op, int exp);
extern void apply_death_exp_penalty(object *op);
extern float calc_level_difference(int who_lvl, int op_lvl);

/* friend.c */
extern void add_friendly_object(object *op);
extern void remove_friendly_object(object *op);
extern void dump_friendly_objects();

/* holy.c */
extern void init_gods();
extern godlink *get_rand_god();
extern object *pntr_to_god_obj(godlink *godlnk);
extern void free_all_god();
extern void dump_gods();

/* info.c */
extern void dump_abilities();
extern void print_monsters();

/* image.c */
extern int read_bmap_names();
extern int find_face(char *name, int error);
extern void free_all_images();

/* init.c */
extern void free_strings();
extern void init_library();
extern void init_globals();
extern void write_todclock();

/* item.c */
extern char *describe_resistance(object *op, int newline);
extern char *query_weight(object *op);
extern char *get_levelnumber(int i);
extern char *query_short_name(object *op, object *caller);
extern char *query_name(object *op, object *caller);
extern char *query_base_name(object *op, object *caller);
extern char *describe_item(object *op);
extern int need_identify(object *op);
extern void identify(object *op);
extern void set_traped_flag(object *op);

/* links.c */
extern objectlink *get_objectlink();
extern oblinkpt *get_objectlinkpt();
extern void free_objectlink(objectlink *ol);
extern void free_objectlinkpt(oblinkpt *obp);

/* living.c */
extern void set_attr_value(living *stats, int attr, signed char value);
extern void change_attr_value(living *stats, int attr, signed char value);
extern signed char get_attr_value(living *stats, int attr);
extern void check_stat_bounds(living *stats);
extern int change_abil(object *op, object *tmp);
extern void drain_stat(object *op);
extern void drain_specific_stat(object *op, int deplete_stats);
extern void fix_player(object *op);
extern void set_dragon_name(object *pl, object *abil, object *skin);
extern void dragon_level_gain(object *who);
extern void fix_monster(object *op);
extern object *insert_base_info_object(object *op);
extern object *find_base_info_object(object *op);
extern void set_mobile_speed(object *op, int index);

/* loader.c */
extern int lex_load(object *op, int map_flags);
extern void yyrestart(FILE *input_file);
extern void yy_load_buffer_state();
extern int yyerror(char *s);
extern void delete_loader_buffer(void *buffer);
extern void *create_loader_buffer(void *fp);
extern int load_object(void *fp, object *op, void *mybuffer, int bufstate, int map_flags);
extern int set_variable(object *op, char *buf);
extern char *get_ob_diff(object *op, object *op2);
extern void save_object(FILE *fp, object *op, int flag);

/* logger.c */
extern void LOG(LogLevel logLevel, const char *format, ...);

/* los.c */
extern void init_block();
extern void set_block(int x, int y, int bx, int by);
extern void update_los(object *op);
extern void clear_los(object *op);
extern void print_los(object *op);
extern void adjust_light_source(mapstruct *map, int x, int y, int light);
extern void check_light_source_list(mapstruct *map);
extern void remove_light_source_list(mapstruct *map);
extern int obj_in_line_of_sight(object *obj, rv_vector *rv);

/* map.c */
extern mapstruct *has_been_loaded_sh(const char *name);
extern char *create_pathname(const char *name);
extern char *normalize_path(const char *src, const char *dst, char *path);
extern void dump_map(mapstruct *m);
extern void dump_all_maps();
extern int wall(mapstruct *m, int x, int y);
extern int blocks_view(mapstruct *m, int x, int y);
extern int blocks_magic(mapstruct *m, int x, int y);
extern int blocks_cleric(mapstruct *m, int x, int y);
extern int blocked(object *op, mapstruct *m, int x, int y, int terrain);
extern int blocked_link(object *op, int xoff, int yoff);
extern int blocked_link_2(object *op, mapstruct *map, int x, int y);
extern int blocked_tile(object *op, mapstruct *m, int x, int y);
extern int arch_blocked(archetype *at, object *op, mapstruct *m, int x, int y);
void set_map_darkness(mapstruct *m, int value);
extern mapstruct *get_linked_map();
extern mapstruct *get_empty_map(int sizex, int sizey);
extern mapstruct *load_original_map(const char *filename, int flags);
extern int new_save_map(mapstruct *m, int flag);
extern void free_map(mapstruct *m, int flag);
extern void delete_map(mapstruct *m);
extern int check_map_owner(mapstruct *map, object *op);
extern char *create_map_owner(mapstruct *map);
extern mapstruct *ready_map_name(const char *name, int flags);
extern void clean_tmp_map(mapstruct *m);
extern void free_all_maps();
extern void update_position(mapstruct *m, int x, int y);
extern void set_map_reset_time(mapstruct *map);
extern mapstruct *out_of_map(mapstruct *m, int *x, int *y);
extern mapstruct *out_of_map2(mapstruct *m, int *x, int *y);
extern int get_rangevector(object *op1, object *op2, rv_vector *retval, int flags);
extern int get_rangevector_from_mapcoords(mapstruct *map1, int x1, int y1, mapstruct *map2, int x2, int y2, rv_vector *retval, int flags);
extern int on_same_map(object *op1, object *op2);
extern int players_on_map(mapstruct *m);

/* mempool.c */
extern uint32 nearest_pow_two_exp(uint32 n);
extern void init_mempools();
extern void setup_poolfunctions(struct mempool *pool, chunk_constructor constructor, chunk_destructor destructor);
extern struct mempool *create_mempool(const char *description, uint32 expand, uint32 size, uint32 flags, chunk_initialisator initialisator, chunk_deinitialisator deinitialisator, chunk_constructor constructor, chunk_destructor destructor);
extern void return_poolchunk_array_real(void *data, uint32 arraysize_exp, struct mempool *pool);
extern void *get_poolchunk_array_real(struct mempool *pool, uint32 arraysize_exp);
extern void dump_mempool_statistics(object *op, int *sum_used, int *sum_alloc);

/* object.c */
extern void init_materials();
extern void mark_object_removed(object *ob);
extern int CAN_MERGE(object *ob1, object *ob2);
extern object *merge_ob(object *op, object *top);
extern signed long sum_weight(object *op);
extern object *is_player_inv(object *op);
extern void dump_object(object *op);
extern void dump_me(object *op, char *outstr);
extern object *find_object(int i);
extern object *find_object_name(char *str);
extern void free_all_object_data();
extern object *get_owner(object *op);
extern void clear_owner(object *op);
extern void set_owner(object *op, object *owner);
extern void copy_owner(object *op, object *clone);
extern void initialize_object(object *op);
extern void copy_object(object *op2, object *op);
extern void copy_object_data(object *op2, object *op);
extern object *get_object();
extern void update_turn_face(object *op);
extern void update_ob_speed(object *op);
extern void update_object(object *op, int action);
extern void destroy_object(object *ob);
extern void remove_ob(object *op);
extern void destruct_ob(object *op);
extern object *insert_ob_in_map(object *op, mapstruct *m, object *originator, int flag);
extern void replace_insert_ob_in_map(char *arch_string, object *op);
extern object *get_split_ob(object *orig_ob, int nr);
extern object *decrease_ob_nr(object *op, int i);
extern object *insert_ob_in_ob(object *op, object *where);
extern int check_walk_on(object *op, object *originator, int flags);
extern int check_walk_off (object *op, object *originator, int flags);
extern object *present_arch(archetype *at, mapstruct *m, int x, int y);
extern object *present(unsigned char type, mapstruct *m, int x, int y);
extern object *present_in_ob(unsigned char type, object *op);
extern object *present_arch_in_ob(archetype *at, object *op);
extern void set_cheat(object *op);
extern int find_free_spot(archetype *at, object *op, mapstruct *m, int x, int y, int start, int stop);
extern int find_first_free_spot(archetype *at, mapstruct *m, int x, int y);
extern int find_first_free_spot2(archetype *at, mapstruct *m,int x,int y, int start, int range);
extern int find_dir(mapstruct *m, int x, int y, object *exclude);
extern int find_dir_2(int x, int y);
extern int absdir(int d);
extern int dirdiff(int dir1, int dir2);
extern int get_dir_to_target(object *op, object *target, rv_vector *range_vector);
extern int can_pick(object *who, object *item);
extern object *object_create_clone(object *asrc);
extern int was_destroyed(object *op, tag_t old_tag);
extern object *load_object_str(char *obstr);
extern void object_gc();
extern int auto_apply(object *op);
extern int can_see_monsterP(mapstruct *m, int x, int y, int dir);
extern void free_key_values(object *op);
extern key_value *get_ob_key_link(const object *ob, const char *key);
extern const char *get_ob_key_value(const object *op, const char *const key);
extern int set_ob_key_value(object *op, const char *key, const char *value, int add_key);
extern void init_object_initializers();

/* porting.c */
extern char *tempnam_local(char *dir, char *pfx);
extern char *strdup_local(const char *str);
extern long strtol_local(char *str, char **ptr, int base);
extern char *strerror_local(int errnum);
extern int isqrt(int n);
extern char *ltostr10(signed long n);
extern void save_long(char *buf, char *name, long n);
extern FILE *open_and_uncompress(char *name, int flag, int *compressed);
extern void close_and_delete(FILE *fp, int compressed);
extern void make_path_to_file(char *filename);

/* quest.c */
extern object *create_quest_container(object *op);
extern void check_quest(object *pl, object *quest_container);
extern object *create_quest(object *op, char *quest_name);

/* player.c */
extern void free_player(player *pl);
extern object *find_skill(object *op, int skillnr);
extern int atnr_is_dragon_enabled(int attacknr);
extern int is_dragon_pl(object *op);

/* re-cmp.c */
extern char *re_cmp(char *str, char *regexp);

/* readable.c */
extern int book_overflow(const char *buf1, const char *buf2, int booksize);
extern void init_readable();
extern object *get_random_mon();
extern void tailor_readable_ob(object *book, int msg_type);
extern void free_all_readable();
extern void write_book_archive();

/* recipe.c */
extern recipelist *get_formulalist(int i);
extern void init_formulae();
extern void dump_alchemy();
extern void dump_alchemy_costs();
extern int strtoint(const char *buf);
extern artifact *locate_recipe_artifact(recipe *rp);
extern recipe *get_random_recipe(recipelist *rpl);
extern void free_all_recipes();

/* shstr.c */
extern void init_hash_table();
extern const char *add_string(const char *str);
extern int query_refcount(const char *str);
extern const char *find_string(const char *str);
extern const char *add_refcount(const char *str);
extern void free_string_shared(const char *str);
extern void ss_dump_statistics(char *buf, size_t size);
extern void ss_dump_table(int what, char *buf, size_t size);
extern int buf_overflow(const char *buf1, const char *buf2, size_t bufsize);

/* time.c */
extern void reset_sleep();
extern void get_tod(timeofday_t *tod);
extern void sleep_delta();
extern void set_max_time(long t);
extern void print_tod(object *op);
extern void time_info(object *op);
extern long seconds();

/* treasure.c */
extern void load_treasures();
extern void init_artifacts();
extern void init_archetype_pointers();
extern treasurelist *find_treasurelist(const char *name);
extern object *generate_treasure(treasurelist *t, int difficulty, int a_chance);
extern void create_treasure(treasurelist *t, object *op, int flag, int difficulty, int t_style, int a_chance, int tries, struct _change_arch *change_arch);
extern void set_abs_magic(object *op, int magic);
extern int fix_generated_item(object **op, object *creator, int difficulty, int a_chance, int t_style, int max_magic, int fix_magic, int chance_magic, int flags);
extern artifactlist *find_artifactlist(int type);
extern archetype *find_artifact_archtype(const char *name);
extern void dump_artifacts();
extern void give_artifact_abilities(object *op, artifact *art);
extern int generate_artifact(object *op, int difficulty, int t_style, int a_chance);
extern void free_all_treasures();
extern void dump_monster_treasure(const char *name);
extern int get_enviroment_level(object *op);
extern object *create_artifact(object *op, char *artifactname);

/* utils.c */
extern int random_roll(int min, int max, object *op, int goodbad);
extern int die_roll(int num, int size, object *op, int goodbad);
extern int rndm(int min, int max);
extern int look_up_spell_name(const char *spname);
extern racelink *find_racelink(const char *name);
extern char *cleanup_string(char *ustring);
extern char *get_word_from_string(char *str, int *pos);
extern void replace(const char *src, const char *key, const char *replacement, char *result, size_t resultsize);
extern void replace_unprintable_chars(char *buf);
