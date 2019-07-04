
* OpenVirtualization: 
* For additional details and support contact developer@sierraware.com.
* Additional documentation can be found at www.openvirtualization.org
* 
* Copyright (C) 2011 SierraWare
* 
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
* 
* fat32 file system implementation
*/
#include<sw_types.h>

   23 #ifndef __FAT32_H_
   24 /*
   25  * along with this program; if not, write to the Free Software
   26  * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
   27  * 
   28  * Header file for fat32 filesystem
   29  */
   30 #include<sw_types.h>
   31 
   32 #define END_OF_CLUSTER           0x0FFFFFFF
   33 #define END_OF_ROOT_CLUSTER      0X0FFFFFF8
   34 #define MAX_DIR_ENTRY_CNT        16
   35 #define FILE_SYS_TYPE_OFF        82
   36 #define BYTES_PER_SEC_OFF        11
   37 #define SEC_PER_CLUS_OFF         13
   38 #define RES_SEC_CNT_OFF          14
   39 #define FAT_CNT_OFF              16
   40 #define TOT_SEC_CNT_OFF          32
   41 #define SEC_PER_FAT              36
   42 #define ROOT_DIR_STRT_CLUS_OFF   44
   43 #define FS_INFOSECTOR_OFF        48
   44 #define BACKUP_BOOT_SEC_OFF      50
   45 #define NXT_FREE_CLUS_OFF        492
   46 #define FILE_SYS_TYPE_LENGTH     8 
   47 #define SHRT_FILE_NAME_LEN       11
   48 #define STRT_CLUS_LOW_OFF        26
   49 #define STRT_CLUS_HIGH_OFF       20
   50 #define FILE_SIZE_OFF            28
   51 #define ATTR_OFF                 11
   52 #define FILE_STAT_LEN            21
   53 #define CHECK_SUM_OFF            13
   54 #define FILE_NAME_SHRT_LEN       8
   55 #define FILE_NAME_EXTN_LEN       3
   56 #define LONG_FILE_NAME_LEN       255
   57 #define LOW_CLUSWORD_MASK        0x0000FFFF
   58 #define HIGH_CLUSWORD_MASK       0xFFFF0000
   59 #define LONG_FNAME_MASK          0x0F
   60 #define LAST_ORD_FIELD_SEQ       0x40
   61 #define LFN_END_MARK             0xFFFF
   62 #define LFN_TERM_MARK            0x0000
   63 #define LFN_FIRST_OFF            0x01
   64 #define LFN_SIXTH_OFF            0x0E
   65 #define LFN_TWELVETH_OFF         0x1C
   66 #define LFN_FIRST_SET_CNT        5
   67 #define LFN_SEC_SET_CNT          6
   68 #define LFN_THIRD_SET_CNT        2        
   69 #define LFN_FIRST_SET_LEN        10
   70 #define LFN_SEC_SET_LEN          12
   71 #define LFN_THIRD_SET_LEN        4
   72 #define LFN_EMPTY_LEN            2 
   73 #define LFN_LEN_PER_ENTRY        13
   74 #define FNAME_EXTN_SEP_OFF       6
   75 #define FNAME_SEQ_NUM_OFF        7            
   76 #define BYTES_PER_CLUSTER_ENTRY  4
   77 #define DIR_ENTRY_LEN            32
   78 #define VOL_ID_LEN               4
   79 #define VOL_LABEL_LEN            11
   80 #define RESERV_LEN               12
   81 #define FS_VER_LEN               2 
   82 #define OEM_NAME_LEN             8
   83 #define JUMP_INS_LEN             3
   84 #define MAX_FAT_CNT              2 
   85 #define SPACE_VAL                32 
   86 #define FILE_READ                0x01
   87 #define FILE_WRITE               0X02
   88 #define FILE_CREATE_NEW          0x04
   89 #define FILE_CREATE_ALWAYS       0x08
   90 #define FILE_APPEND              0x10              
   91 #define ATTR_READ                0x01
   92 #define ATTR_HIDDEN              0x02
   93 #define ATTR_SYSTEM              0x04
   94 #define ATTR_VOL_LABEL           0x08
   95 #define ATTR_DIR                 0x10
   96 #define ATTR_ARCHIVE             0x20
   97 #define ATTR_LONG_FNAME          0x0F
   98 #define FREE_DIR_ENTRY           0x00
   99 #define DEL_DIR_ENTRY            0xE5
  100 #define DOT_DIR_ENTRY            0x2E
  101 #define ASCII_DIFF               32
  102 #define FILE_SEEK_SET            0
  103 #define FILE_SEEK_CUR            1
  104 #define FILE_SEEK_END            2
  105 #define DELIMITER                '/'
  106 #define EXTN_DELIMITER           '.'
  107 #define TILDE                    '~'
  108 #define FULL_SHRT_NAME_LEN       13
  109  
  114 typedef struct __attribute__((__packed__))
  115 {
  116         u8   jump[JUMP_INS_LEN];
  117         u8   OEM_name[OEM_NAME_LEN];
  118         u16  bytes_per_sec;
  119         u8   sec_per_clus;
  120         u16  reserved_sec_cnt;
  121         u8   fat_cnt;
  122         u16  root_dir_max_cnt;
  123         u16  tot_sectors;
  124         u8   media_desc;
  125         u16  sec_per_fat_fat16;
  126         u16  sec_per_track;
  127         u16  number_of_heads;
  128         u32  hidden_sec_cnt;  
  129         u32  tol_sector_cnt;
  130         u32  sectors_per_fat;
  131         u16  ext_flags;
  132         u8   fs_version[FS_VER_LEN];   
  133         u32  root_dir_strt_cluster;
  134         u16  fs_info_sector;
  135         u16  backup_boot_sector;
  136         u8   reserved[RESERV_LEN];
  137         u8   drive_number;
  138         u8   reserved1;
  139         u8   boot_sig;
  140         u8   volume_id[VOL_ID_LEN];
  141         u8   volume_label[VOL_LABEL_LEN];
  142         u8   file_system_type[FILE_SYS_TYPE_LENGTH];  
  143 } boot_sector;
  144 
  145 
  150 typedef struct __attribute__((__packed__))
  151 {
  152         u8  name[FILE_NAME_SHRT_LEN];
  153         u8  extn[FILE_NAME_EXTN_LEN];
  154         u8  attr;
  155         u8  reserved;
  156         u8  crt_time_tenth;
  157         u16 crt_time;
  158         u16 crt_date;
  159         u16 lst_access_date;
  160         u16 strt_clus_hword;
  161         u16 lst_mod_time;
  162         u16 lst_mod_date;
  163         u16 strt_clus_lword;
  164         u32 size;
  165 } dir_entry;
  166 
  171 typedef struct
  172 {
  173         u8 ord_field;
  174         u8 fname0_4[LFN_FIRST_SET_LEN];
  175         u8 flag;
  176         u8 reserved;
  177         u8 chksum;
  178         u8 fname6_11[LFN_SEC_SET_LEN];
  179         u8 empty[LFN_EMPTY_LEN];
  180         u8 fname12_13[LFN_THIRD_SET_LEN];       
  181 } lfn_entry;
  182 
  183 struct f_info;
  184 typedef struct f_info file_info;
  190 struct f_info
  191 {
  192         int fd;
  193         dir_entry *entry;
  194         const char *file_path;
  195         u32 strt_cluster;
  196         u32 cur_cluster;
  197         u16 cur_offset;
  198         u32 file_size;
  199         u8  mode;
  200         u32 bytes_traversed;
  201         u8 *dir_entry_offset;
  202         file_info *next;
  203 };
  204 
  205 
  210 typedef struct 
  211 {
  212         char name[FULL_SHRT_NAME_LEN];
  213         const char *lname;
  214         u32 size;
  215         u16 time;
  216         u16 date;
  217         u8 attr;        
  218 } file_stat;
  219 
  228 int mount_file_system(u8 *dev);
  229 
  238 bool chk_fat32_file_system(u8 *file_sys_type);
  239 
  249 void cal_region_offsets(boot_sector *bs, u8 *dev);
  250 
  263 int file_open(const char *file_path,int flags);
  264 
  265 
  287 bool get_dir_entry(char *fname,dir_entry **entry,u8 *strt,
  288                                    u32 strt_clus,bool is_lfn);
  289 
  290 
  305 int lfn_entry_to_name(lfn_entry *entry,char *lfname,int *index);
  306 
  315 u8 * cluster_to_memory_addr(u32 cluster);
  316 
  330 int retrieve_file_info(file_info *finfo,dir_entry *entry,u8 mode,
  331                                            u8 *dir_offset,const char *path);
  341 u32 get_fat_table_entry(u32 cluster);
  342 
  350 void convert_to_uppercase(char * file_name);
  351 
  362 int find_depth(const char *file_path);
  363 
  383 int create_file(char *lfname,char *shrt_name,u32 clus,dir_entry **entry);
  384 
  385 
  398 int file_read(int fd,char * buffer,int bytes_to_read);
  399 
  413 int file_write(int fd, const char *buffer,int bytes_to_write);
  414 
  421 u32 allocate_cluster();
  422 
  432 void write_fat_table(u32 cluster,u32 value);
  433 
  442 void get_short_file_name(char * lfname,char *sfname,char seq_num);
  443 
  459 void fill_lng_fname_entries(char *fname,u8 *entry,u8 chk_sum,int count);
  470 u8 calc_check_sum(u8 * dir_entry);
  471 
  472 
  482 int file_close(int fd);
  483 
  501 int file_seek(int fd,int offset,int whence);
  502 
  518 int get_seek_off(file_info * file_ptr,u32 strt_cluster,int offset);
  519 
  536 int get_long_file_name(char *fname,u8 **dir_strt,int *count);
  537 
  551 int file_rename(const char *old,const char *new);
  552 
  562 int create_dir(const char *path);
  570 int chk_file_lock(const char *path);
  578 file_stat * read_dir(int fd);
  579 
  588 int open_dir(const char *path);
  589 
  597 int cal_req_dir_cnt(int file_name_len);
  598 
  610 int file_truncate(const char* tr_pf,int tr_lgh);
  611 
  621 int file_remove(const char *fl_name);
  622 
  631 int file_unlink(const char *ul_name);
  632 
  641 int list_dir(const char *path);
  642 
  643 #endif



int mount_file_system(u8 *dev){
	bool is_fat32;
    boot_sector *bs;
    u8 *ptr = dev;  
    is_fat32 = chk_fat32_file_system(ptr + FILE_SYS_TYPE_OFF);
    if(is_fat32){ 
	    bs = (boot_sector*)ptr;
        cal_region_offsets(bs,dev);
        file_head = NULL;
        fdes = 2;
	    return 0;
	}
    else
        return -1;
}

bool chk_fat32_file_system(u8 *file_sys_type){
	int i;
4         char fs_type[FILE_SYS_TYPE_LENGTH] = "FAT32   ";
5         u8 *type = file_sys_type;
6         for(i=0;i<FILE_SYS_TYPE_LENGTH;i++){
7                 if(*type != fs_type[i] ){
8                         return false;
9                 }
0                 else
1                         type++;
2         }
3         return true;
4 }
5 
5 void cal_region_offsets(boot_sector *bs, u8 *dev)
6 {
7         u32 next_clus;
8         int clus_cnt = 0;
9         sec_size = bs->bytes_per_sec;
0         cluster_size = (bs->sec_per_clus)*sec_size;
1         bs_sector = dev;
2         fs_infosector = bs_sector + (bs->fs_info_sector * sec_size);
3         backup_boot_sector = bs_sector + (bs->backup_boot_sector * sec_size);
4         first_fat = bs_sector + (bs->reserved_sec_cnt * sec_size);
5         if(bs->fat_cnt == MAX_FAT_CNT)
6                 second_fat = (bs->sectors_per_fat * sec_size) + first_fat;
7         root_directory = bs_sector + ((bs->reserved_sec_cnt 
8                                                 + (bs->fat_cnt * bs->sectors_per_fat) 
9                         + (bs->root_dir_strt_cluster-2))*sec_size) ;   
  100         next_clus = bs->root_dir_strt_cluster;
  101         while(next_clus != END_OF_CLUSTER && next_clus != END_OF_ROOT_CLUSTER){
  102                 next_clus = get_fat_table_entry(next_clus);
  103                 clus_cnt++;
  104         }
  105         rt_dir_strt_clus = bs->root_dir_strt_cluster;
  106         root_dir_size = cluster_size * clus_cnt;
  107         rt_dir_entry_cnt = root_dir_size / DIR_ENTRY_LEN;
  108         nxt_free_cluster = *(u32*)(fs_infosector + NXT_FREE_CLUS_OFF);
  109 }
  110 
  111 
  124 int file_open(const char *file_path,int flags)
  125 {
  126         const char *path = file_path;
  127         const char *temp_path,*delim_strt;
  128         char shrt_file_name[SHRT_FILE_NAME_LEN];
  129         char long_file_name[LONG_FILE_NAME_LEN];
  130         int len = 0,fl_des = 0,crt_flag,i;
  131         int delim_cnt = 0;
  132         int mode;
  133         int extn_len_cnt = 0;
  134         int seq_num = 1;
  135         bool is_file_found;
  136         dir_entry *entry = NULL;
  137         file_info *info;
  138         u8 *pwd = root_directory;
  139         u32 strt_cluster = rt_dir_strt_clus;
  140         bool is_long_file_name = false; 
  141 
  142         sw_memset(long_file_name,SPACE_VAL,LONG_FILE_NAME_LEN);
  143         delim_cnt = find_depth(file_path);
  144         
  145         path = file_path;
  146         for(i=0;i<delim_cnt;i++){
  147                 if(*path == DELIMITER){
  148                         delim_strt = path;
  149                         path++;
  150                 }
  151                 while((*path != EXTN_DELIMITER) && (*path != '\0') 
  152                         && (*path != DELIMITER) && (len < LONG_FILE_NAME_LEN)){
  153                         long_file_name[len] = *path; 
  154                         path++; 
  155                         len++;
  156                 }
  157                 temp_path = path;
  158                 if(*temp_path == EXTN_DELIMITER){
  159                         temp_path++;
  160                         while(*temp_path != DELIMITER && *temp_path != '\0'){
  161                                 extn_len_cnt++;
  162                                 temp_path++;
  163                         }
  164                 }
  165                 if(len > FILE_NAME_SHRT_LEN || extn_len_cnt > FILE_NAME_EXTN_LEN)
  166                         is_long_file_name = true;
  167 
  168                 if(is_long_file_name){
  169                         path = delim_strt;
  170                         len = 0;
  171                         if(*path == DELIMITER)
  172                                 path++;
  173                         while(len < LONG_FILE_NAME_LEN  && *path != '\0'
  174                               && *path != DELIMITER){
  175                                 long_file_name[len] = *path;
  176                                 path++;
  177                                 len++;
  178                         }
  179                         long_file_name[len] = '\0';
  180                         if(entry){
  181                                 sw_free(entry);
  182                                 entry = NULL;
  183                         }
  184                         is_file_found = get_dir_entry(long_file_name,&entry,
  185                                                                                   pwd,strt_cluster,true);                               
  186                 }
  187                 else{
  188                         len = FILE_NAME_SHRT_LEN;
  189                         while(len < SHRT_FILE_NAME_LEN  && *path != '\0' 
  190                               && *path != DELIMITER){ 
  191                                 if(*path == EXTN_DELIMITER)
  192                                         path++;
  193                                 long_file_name[len] = *path;
  194                                 path++;
  195                                 len++;
  196                         }
  197                         convert_to_uppercase(long_file_name); 
  198                         if(entry){
  199                                 sw_free(entry);
  200                                 entry = NULL;
  201                         }
  202                         is_file_found = get_dir_entry(long_file_name,&entry,
  203                                                                                   pwd,strt_cluster,false);
  204                 }
  205                 if((is_file_found) & (i != delim_cnt - 1)){ 
  206                         strt_cluster = (entry->strt_clus_hword)<<16 | 
  207                                        (entry->strt_clus_lword);
  208                         pwd = cluster_to_memory_addr(strt_cluster);
  209                         len = 0;
  210                         extn_len_cnt = 0;
  211                         sw_memset(shrt_file_name,SPACE_VAL,SHRT_FILE_NAME_LEN);
  212                         sw_memset(long_file_name,SPACE_VAL,LONG_FILE_NAME_LEN);
  213                         is_long_file_name = false;
  214                 }               
  215         }
  216         if(is_file_found){
  217                 if(flags & FILE_WRITE){
  218                         if(chk_file_lock(file_path) == -1)
  219                                 flags = FILE_READ;                              
  220                         if(entry->attr & ATTR_READ){
  221                                 sw_printf("Cannot open the file in write mode\n");
  222                                 return -1;
  223                         }
  224                 }
  225                 info = (file_info*)sw_malloc(sizeof(file_info));
  226                 fl_des = retrieve_file_info(info,entry,flags,
  227                                                                                         dir_file_offset,file_path);
  228         }  
  229         else{
  230                 if((flags & FILE_CREATE_NEW) || (flags & FILE_CREATE_ALWAYS)
  231                    || (flags & FILE_WRITE)){
  232                         if(is_long_file_name){
  233                                 get_short_file_name(long_file_name,shrt_file_name,
  234                                                                         (char)seq_num);
  235                                 if(get_dir_entry(shrt_file_name,NULL,
  236                                                                  pwd,strt_cluster,false) == true){
  237                                         while(get_dir_entry(shrt_file_name,NULL,
  238                                                                                 pwd,strt_cluster,false)){
  239                                                 seq_num++;
  240                                                 get_short_file_name(long_file_name,
  241                                                                                         shrt_file_name,'seq_num');
  242                                         }
  243                                 }
  244                                 convert_to_uppercase(shrt_file_name);
  245                                 crt_flag = create_file(long_file_name,
  246                                                                            shrt_file_name,strt_cluster,&entry);
  247                         }
  248                         else
  249                                 crt_flag = create_file(NULL,long_file_name,strt_cluster,&entry);
  250                         if(crt_flag == 0)
  251                                 sw_printf("File creation success\n");
  252                         info = (file_info*)sw_malloc(sizeof(file_info));
  253                         fl_des = retrieve_file_info(info,entry,flags,
  254                                                                                 dir_file_offset,file_path);
  255                 }
  256                 else
  257                         return -1;
  258         }
  259         return fl_des;  
  260 }
  261 
  283 bool get_dir_entry(char *fname,dir_entry **entry,u8 *strt,
  284                                    u32 strt_clus,bool is_lfn)
  285 {
  286         u8 *dir_strt = strt;
  287         dir_entry *dir_ptr;
  288         u8 chk_sum;
  289         bool file_found = false;
  290         int i = 0;
  291         int tmp_cnt = 0;
  292         int lfn_len = 0;
  293         char temp_lfn[LONG_FILE_NAME_LEN];
  294         sw_memset(temp_lfn,SPACE_VAL,LONG_FILE_NAME_LEN);
  295         u32 next_clus = strt_clus;
  296         
  297         while(!((next_clus == END_OF_CLUSTER) && (i == MAX_DIR_ENTRY_CNT + 2) && 
  298                         next_clus != END_OF_ROOT_CLUSTER)){
  299                 if((i - MAX_DIR_ENTRY_CNT == 1) && (next_clus != END_OF_CLUSTER) &&
  300                         next_clus != END_OF_ROOT_CLUSTER){
  301                         next_clus = get_fat_table_entry(next_clus);
  302                         if(next_clus == END_OF_CLUSTER || 
  303                                                    next_clus == END_OF_ROOT_CLUSTER)
  304                                                                 break;
  305                                                 dir_strt = cluster_to_memory_addr(next_clus);
  306                         if(next_clus != END_OF_CLUSTER && next_clus != 
  307                                                                                 END_OF_ROOT_CLUSTER)
  308                                 i = 0;
  309                 }
  310                 if(is_lfn){
  311                         if(*(dir_strt + ATTR_OFF) == ATTR_LONG_FNAME){
  312                                 lfn_len = get_long_file_name(temp_lfn,&dir_strt,&tmp_cnt);
  313                                 if(sw_memcmp(temp_lfn,fname,lfn_len) == 0)
  314                                         file_found = true;
  315                         }
  316                 }
  317                 else{
  318                         if(sw_memcmp(fname,dir_strt,SHRT_FILE_NAME_LEN) == 0){
  319                                 file_found = true;
  320                         }
  321                 }
  322                 if(file_found)
  323                         break;
  324                 dir_strt += DIR_ENTRY_LEN;
  325                 //TODO
  326                 if(tmp_cnt != 0)
  327                         i += tmp_cnt;
  328                 else
  329                         i++;
  330                 //i= (tmp_cnt != 0) ? i += tmp_cnt : i++;
  331                 tmp_cnt = 0;
  332         }
  333         if(file_found){
  334                 if(entry != NULL){
  335                         dir_ptr = (dir_entry*)sw_malloc(sizeof(dir_entry));
  336                         sw_memcpy(dir_ptr,dir_strt,DIR_ENTRY_LEN);
  337                         *entry = dir_ptr;
  338                         dir_file_offset = dir_strt;
  339                 }
  340                 return true;
  341         }
  342         else
  343                 return false;
  344 }
  345 
  362 int get_long_file_name(char *fname,u8 **dir_strt,int *count)
  363 {
  364         lfn_entry *lf_ptr;
  365         int index = 0;
  366         int counter = 0;
  367         u8 chk_sum;
  368 
  369         lf_ptr = (lfn_entry *)(*dir_strt);
  370         counter = lf_ptr->ord_field & LONG_FNAME_MASK;
  371         *count = counter;
  372         while((lf_ptr->ord_field > 1) && 
  373              ((lf_ptr->ord_field & LONG_FNAME_MASK) > 1))
  374                 lf_ptr++;               
  375         *dir_strt = (u8 *)lf_ptr + DIR_ENTRY_LEN;
  376         chk_sum = calc_check_sum(*dir_strt);
  377         while(counter--){
  378                 if(*((u8 *)lf_ptr + CHECK_SUM_OFF) == chk_sum){
  379                         if(lfn_entry_to_name(lf_ptr,fname,&index) == 1)
  380                                 break;  
  381                         lf_ptr--;
  382                 }
  383         }
  384         return (index - 1);
  385 }
  386 
  401 int lfn_entry_to_name(lfn_entry *entry,char *lfname,int *index)
  402 {
  403         int i;
  404         for(i = 0; i <= 8; i += 2){
  405                 if(entry->fname0_4[i] == 0)
  406                         return 1;
  407                 lfname[*index] = entry->fname0_4[i];
  408                 (*index)++;
  409         }
  410         for(i = 0; i <= 10; i += 2){
  411                 if(entry->fname6_11[i] == 0)
  412                         return 1;
  413                 lfname[*index] = entry->fname6_11[i];
  414                 (*index)++;
  415         }
  416         for(i = 0 ; i <= 2; i += 2){
  417                 if(entry->fname12_13[i] == 0)
  418                         return 1;
  419                 lfname[*index] = entry->fname12_13[i];
  420                 (*index)++;
  421         }
  422         return 0;
  423 }
  424 
  425 
  439 int retrieve_file_info(file_info *finfo,dir_entry *entry,u8 mode,
  440                                            u8 *dir_offset,const char *path)
  441 {
  442         file_info *temp;
  443         if(file_head == NULL)
  444                 file_head = finfo;
  445         else{
  446                 temp = file_head;
  447                 while(temp->next != NULL)
  448                         temp = temp->next;
  449                 temp->next = finfo;
  450 
  451         }
  452         finfo->fd = fdes = fdes + 1;
  453         finfo->file_path = sw_malloc(sizeof(char) * (sw_strlen(path) + 1));
  454         sw_strcpy(finfo->file_path,path);
  455         finfo->entry = entry;
  456         finfo->strt_cluster = (entry->strt_clus_hword)<<16 | 
  457                               (entry->strt_clus_lword);
  458         finfo->cur_cluster = finfo->strt_cluster;
  459         finfo->cur_offset = 0;
  460         finfo->file_size = entry->size;
  461         finfo->mode = mode;
  462         finfo->bytes_traversed = 0;
  463         finfo->dir_entry_offset = dir_offset;
  464         finfo->next = NULL;
  465         
  466         return(finfo->fd);
  467 }
  468 
  481 int file_read(int fd,char * buffer,int bytes_to_read)
  482 {
  483         file_info *temp = file_head;
  484         u8 *file_cont;
  485         int bytes_to_copy;
  486         int tmp_offset;
  487         int bytes_read = 0;
  488         int tmp_bytes_cnt = 0;
  489 
  490         while(temp != NULL){
  491                 if(temp->fd == fd)
  492                         break;
  493                 temp = temp->next;
  494         }
  495         if(temp->entry->attr != ATTR_DIR){
  496                 tmp_offset = bytes_to_read > (temp->file_size - temp->bytes_traversed) ?
  497                              temp->file_size - temp->bytes_traversed : bytes_to_read; 
  498                 tmp_bytes_cnt = tmp_offset;
  499         }
  500         else
  501                 tmp_offset = tmp_bytes_cnt = bytes_to_read;
  502                         
  503         while(tmp_offset > 0){
  504                 if(temp->cur_cluster != END_OF_CLUSTER && 
  505                    temp->cur_cluster != END_OF_ROOT_CLUSTER){  
  506                         if(cluster_size - temp->cur_offset != 0){
  507                                 file_cont = cluster_to_memory_addr(temp->cur_cluster) 
  508                                             + temp->cur_offset;                                 
  509                                 bytes_to_copy = cluster_size - (tmp_bytes_cnt - bytes_read);
  510                                 bytes_to_copy =  bytes_to_copy > 0 ? 
  511                                                  tmp_bytes_cnt - bytes_read: 
  512                                                  cluster_size;
  513                                 bytes_to_copy = cluster_size 
  514                                                                 - temp->cur_offset > bytes_to_copy ?
  515                                                                 bytes_to_copy : cluster_size - temp->cur_offset;
  516                                 sw_memcpy(buffer + bytes_read,file_cont,bytes_to_copy);
  517                                 tmp_offset -= bytes_to_copy;
  518                                 temp->cur_offset += bytes_to_copy;
  519                                 bytes_read += bytes_to_copy;
  520                         }
  521                         else{
  522                                 temp->cur_cluster = get_fat_table_entry(temp->cur_cluster);
  523                                 temp->cur_offset = 0;
  524                         }
  525                 
  526                 }       
  527                 else{
  528                         break;
  529                 }
  530         }       
  531         temp->bytes_traversed += bytes_read;
  532         return bytes_read;
  533 }
  534 
  548 int file_write(int fd, const char *buffer,int bytes_to_write)
  549 {
  550         file_info *temp = file_head;
  551         u8 *file_cont;
  552         int tmp_offset = bytes_to_write;
  553         int alloc_cluster_cnt = 0;
  554         int bytes_to_copy;
  555         int bytes_written = 0;
  556         u32 new_cluster;
  557         u32 prev_cluster;       
  558 
  559         while(temp != NULL){
  560                 if(temp->fd == fd)
  561                         break;
  562                 temp = temp->next;      
  563         }
  564         if(temp->mode == FILE_READ){
  565                 sw_printf("File opened in read only mode\n");
  566                 return 0;
  567         }
  568         while(tmp_offset > 0){
  569                 if((temp->cur_cluster != 0) && (temp->cur_cluster != END_OF_CLUSTER) 
  570                         && (temp->cur_cluster != END_OF_ROOT_CLUSTER) && 
  571                         (cluster_size - temp->cur_offset != 0)) {
  572                         file_cont = cluster_to_memory_addr(temp->cur_cluster) 
  573                                     + temp->cur_offset;
  574                         bytes_to_copy = cluster_size - (bytes_to_write - bytes_written);
  575                         bytes_to_copy = bytes_to_copy > 0 ?  
  576                                         bytes_to_write - bytes_written: 
  577                                         cluster_size;
  578                         bytes_to_copy = cluster_size - temp->cur_offset > bytes_to_copy ?
  579                                         bytes_to_copy : cluster_size - temp->cur_offset;
  580                         sw_memcpy(file_cont,buffer + bytes_written,bytes_to_copy);
  581                         bytes_written += bytes_to_copy;
  582                         temp->cur_offset += bytes_to_copy;
  583                         tmp_offset -= bytes_to_copy; 
  584                         prev_cluster = temp->cur_cluster;
  585                         if(temp->cur_offset == cluster_size)
  586                                 temp->cur_cluster = get_fat_table_entry(temp->cur_cluster);   
  587                         if(temp->cur_cluster != 0 && temp->cur_cluster != END_OF_CLUSTER
  588                            && temp->cur_cluster != END_OF_ROOT_CLUSTER
  589                            && tmp_offset != 0)
  590                                 temp->cur_offset = 0;
  591                 }
  592                 else{
  593                         new_cluster = allocate_cluster();
  594                         if(alloc_cluster_cnt == 0 && temp->cur_cluster == 0 
  595                            && temp->strt_cluster == 0){
  596                                 temp->strt_cluster = new_cluster;
  597                                 *(u16*)(dir_file_offset + STRT_CLUS_LOW_OFF) = 
  598                                         temp->strt_cluster & LOW_CLUSWORD_MASK;
  599                                 *(u16*)(dir_file_offset + STRT_CLUS_HIGH_OFF) = 
  600                                         (temp->strt_cluster & HIGH_CLUSWORD_MASK) >> 16;
  601 
  602                         }
  603                         else 
  604                                 write_fat_table(prev_cluster,new_cluster);
  605                         temp->cur_cluster = new_cluster;
  606                         temp->cur_offset = 0;
  607                         alloc_cluster_cnt++;       
  608                 }    
  609         }  
  610         temp->bytes_traversed += bytes_written; 
  611         if(temp->file_size < bytes_written){
  612                 *(dir_file_offset + FILE_SIZE_OFF) = (u32)(bytes_written);
  613                 temp->file_size = (u32)(bytes_written);
  614         }       
  615         if(alloc_cluster_cnt > 0)
  616                 write_fat_table(new_cluster,END_OF_CLUSTER);
  617 
  618         return bytes_written;   
  619 }
  620 
  630 int file_close(int fd)
  631 {
  632         file_info *temp = file_head,*prev;
  633         while(temp != NULL){
  634                 if(temp->fd == fd)
  635                         break;
  636                 prev = temp; 
  637                 temp = temp->next;
  638         }
  639         if(temp == NULL) 
  640                 return -1;
  641         if(temp == file_head){
  642                 file_head = temp->next;
  643                 sw_malloc_free(temp->file_path);
  644                 sw_malloc_free(temp->entry);
  645 //              sw_malloc_free(temp->dir_entry_offset);
  646                 sw_malloc_free(temp);
  647         }
  648         else{
  649                 prev->next = temp->next;
  650                 sw_malloc_free(temp->file_path);
  651                 sw_malloc_free(temp->entry);
  652                 sw_malloc_free(temp->dir_entry_offset);
  653                 sw_malloc_free(temp);   
  654         }
  655         return 0;
  656 }
  657  
  677 int create_file(char *lfname,char *shrt_name,u32 clus,dir_entry **entry)
  678 {
  679         u8 *cur_dir_entry;
  680         u32 next_clus = clus;
  681         u32 new_clus;
  682         u32 prev_clus;
  683         int new_clus_cnt = 0;
  684         int i = 0,j = 0,k = 0;
  685         int req_ent_cnt = 0;
  686         int temp_cnt = 0;
  687         char *lfptr = lfname;
  688         bool is_gap_found = false;
  689         u8 chk_sum;
  690         dir_entry *dir_ptr;
  691         
  692         cur_dir_entry = cluster_to_memory_addr(next_clus);
  693         while(!is_gap_found){
  694                 if(k - MAX_DIR_ENTRY_CNT == 1){
  695                         prev_clus = next_clus;
  696                         next_clus = get_fat_table_entry(next_clus);
  697                         cur_dir_entry = cluster_to_memory_addr(next_clus);
  698                         if(next_clus == END_OF_CLUSTER || next_clus == END_OF_ROOT_CLUSTER){
  699                                 new_clus = allocate_cluster();
  700                                 write_fat_table(prev_clus,new_clus);
  701                                 new_clus_cnt++;
  702                                 k = 0;
  703                         }
  704                 }
  705                 if(lfname != NULL){
  706                         chk_sum = calc_check_sum(shrt_name);
  707                         while(*lfptr != '\0'){
  708                                 lfptr++;
  709                                 i++;
  710                         }
  711                         req_ent_cnt = cal_req_dir_cnt(i);
  712                         temp_cnt = req_ent_cnt;
  713                         while(req_ent_cnt--){
  714                                 if(k - MAX_DIR_ENTRY_CNT == 1){
  715                                         req_ent_cnt = temp_cnt;
  716                                         break;
  717                                 }                       
  718                                 if(*cur_dir_entry == FREE_DIR_ENTRY ||
  719                                    *cur_dir_entry == DEL_DIR_ENTRY){
  720                                         cur_dir_entry += DIR_ENTRY_LEN;
  721                                         j++;
  722                                         k++;
  723                                 }
  724                                 else
  725                                         k++;                            
  726                         }
  727                         if(j == temp_cnt){
  728                                 is_gap_found = true;
  729                                 fill_lng_fname_entries(lfname,cur_dir_entry,chk_sum,temp_cnt);
  730                         }
  731                         req_ent_cnt = temp_cnt;
  732                         j = 0;
  733                 }
  734                 else{
  735                         if(*cur_dir_entry == FREE_DIR_ENTRY ||
  736                            *cur_dir_entry == DEL_DIR_ENTRY)
  737                                 is_gap_found = true;
  738                         k++;
  739                 }
  740                 if(is_gap_found){
  741                         sw_memset(cur_dir_entry,0,DIR_ENTRY_LEN);
  742                         sw_memcpy(cur_dir_entry,shrt_name,SHRT_FILE_NAME_LEN);
  743                         *(cur_dir_entry + ATTR_OFF) = ATTR_ARCHIVE;
  744                         dir_ptr = (dir_entry*)sw_malloc(sizeof(dir_entry));
  745                         sw_memcpy(dir_ptr,cur_dir_entry,DIR_ENTRY_LEN);
  746                         *entry = dir_ptr;
  747                         dir_file_offset = cur_dir_entry;
  748                 }
  749                 if(new_clus_cnt > 0)
  750                         write_fat_table(new_clus,END_OF_CLUSTER);       
  751                 cur_dir_entry += DIR_ENTRY_LEN;
  752         }
  753         return 0;
  754 }
  755 
  771 void fill_lng_fname_entries(char *fname,u8 *entry,u8 chk_sum,int count)
  772 {
  773         lfn_entry *lfn_ent = (lfn_entry *)entry;
  774         char *file_name = fname;
  775         u8 *lf_entry;
  776         bool end_of_name = false;
  777         int i,j;
  778         int max_ord_cnt;
  779         int ord_num = 1;
  780         lfn_ent = (u8 *)lfn_ent - DIR_ENTRY_LEN;
  781         while(count--){
  782                 lf_entry = (u8 *)lfn_ent;
  783                 sw_memset(lf_entry,0,DIR_ENTRY_LEN);
  784                 *lf_entry = count - 1 == 0 ? ord_num : ord_num | LAST_ORD_FIELD_SEQ;
  785                 *(lf_entry + ATTR_OFF) = ATTR_LONG_FNAME;
  786                 *(lf_entry + CHECK_SUM_OFF) = chk_sum; 
  787                 for(j = 0;j < 3;j++){
  788                         switch(j){
  789                                 case 0:
  790                                         max_ord_cnt = LFN_FIRST_SET_CNT;
  791                                         lf_entry = (u8 *)lfn_ent + LFN_FIRST_OFF;
  792                                         break;
  793                                 case 1:
  794                                         max_ord_cnt = LFN_SEC_SET_CNT;
  795                                         lf_entry = (u8 *) lfn_ent + LFN_SIXTH_OFF;                      
  796                                         break;
  797                                 case 2:
  798                                         max_ord_cnt = LFN_THIRD_SET_CNT;
  799                                         lf_entry = (u8 *) lfn_ent + LFN_TWELVETH_OFF;
  800                                         break;
  801                         }       
  802                         for(i = 0; i < max_ord_cnt; i++){
  803                                 if(*file_name == '\0'){
  804                                         if(!end_of_name){
  805                                                 *(u16 *)lf_entry = LFN_TERM_MARK;
  806                                                 end_of_name = true;
  807                                         }
  808                                         else
  809                                                 *(u16 *)lf_entry = LFN_END_MARK;
  810                                 }
  811                                 else{                   
  812                                         *(lf_entry) = *file_name;
  813                                         file_name++;
  814                                 }
  815                                 lf_entry += 2;                  
  816                         }
  817                 }
  818                 ord_num++;
  819                 lfn_ent--;      
  820         }
  821 }
  822 
  840 int file_seek(int fd,int offset,int whence)
  841 {
  842         int seek_mode = whence;
  843         file_info *temp = file_head;
  844         int off_bytes;
  845         int tmp_off = offset;
  846         u32 cur_cluster;
  847         u32 strt_cluster;       
  848         int bytes_traversed = 0;
  849         int bytes_to_copy;
  850         int clus_cnt = 0;       
  851 
  852         while (temp != NULL){
  853                 if(temp->fd == fd)
  854                         break;
  855                 temp = temp->next;
  856         }               
  857         if(offset < 0){
  858                 if(seek_mode == FILE_SEEK_CUR){
  859                         tmp_off = temp->bytes_traversed + offset;
  860                         seek_mode = FILE_SEEK_SET;
  861                 }
  862                 else if(seek_mode == FILE_SEEK_END){
  863                         tmp_off = temp->file_size + offset;
  864                         seek_mode = FILE_SEEK_SET;
  865                 }
  866                 else
  867                         return -1;
  868         }
  869                 
  870         switch(seek_mode){
  871                 case FILE_SEEK_SET:
  872                         strt_cluster = temp->strt_cluster;
  873                         temp->cur_offset = 0;
  874                         off_bytes = get_seek_off(temp,strt_cluster,tmp_off);
  875                         break;
  876                 case FILE_SEEK_CUR:
  877                         strt_cluster = temp->cur_cluster;
  878                         off_bytes = (temp->bytes_traversed - temp->cur_offset) +
  879                                     get_seek_off(temp,strt_cluster,tmp_off);
  880                         break;
  881                 case FILE_SEEK_END:
  882                         cur_cluster = temp->strt_cluster;
  883                         while(cur_cluster != END_OF_CLUSTER && 
  884                                                           cur_cluster != END_OF_ROOT_CLUSTER){
  885                                 temp->cur_cluster = cur_cluster;
  886                                 cur_cluster = get_fat_table_entry(cur_cluster);
  887                                 clus_cnt++;
  888                         }
  889                         temp->cur_offset = temp->file_size - 
  890                                            (cluster_size * (clus_cnt - 1));
  891                         off_bytes = get_seek_off(temp,temp->cur_cluster,tmp_off) + 
  892                                     (cluster_size * (clus_cnt - 1));
  893                         break;
  894         }
  895         temp->bytes_traversed = off_bytes;
  896         return off_bytes;
  897 }
  898 
  912 int file_rename(const char *old,const char *new)
  913 {
  914         int fd_old;
  915         int fd_new;
  916         file_info *temp_old;
  917         file_info *temp_new;
  918 
  919         fd_new = file_open(new,FILE_READ);
  920         if(fd_new == -1){
  921                 fd_old = file_open(old,FILE_READ);
  922                 fd_new = 0;
  923                 fd_new = file_open(new,FILE_CREATE_NEW);
  924                 temp_old = temp_new = file_head;
  925                 while(temp_old->fd != fd_old)
  926                         temp_old = temp_old->next;
  927                 while(temp_new->fd != fd_new)
  928                         temp_new = temp_new->next;
  929                 sw_memcpy(temp_new->dir_entry_offset + ATTR_OFF,
  930                           temp_old->dir_entry_offset + ATTR_OFF,FILE_STAT_LEN);
  931                 *(temp_old->dir_entry_offset) = DEL_DIR_ENTRY;
  932                 file_close(fd_old);
  933                 file_close(fd_new);
  934                 return 0;
  935         }
  936         else{
  937                 sw_printf("Already exists\n");
  938                 return -1;
  939         }
  940 
  941 }
  942 
  952 int create_dir(const char *path)
  953 {
  954         int fd;
  955         fd = file_open(path,FILE_READ);
  956         if(fd != -1)
  957                 fd = file_open(path,FILE_CREATE_NEW);
  958         else
  959                 return -1;
  960         return fd;
  961 }
  962 
  971 int open_dir(const char *path)
  972 {
  973         int fd_dir;     
  974         fd_dir = file_open(path,FILE_READ);
  975         return fd_dir;          
  976 }
  977 
  986 int list_dir(const char *path)
  987 {
  988         int fd_dir;
  989         file_stat *finfo;
  990         int file_count = 0;
  991         fd_dir = open_dir(path);
  992         
  993         finfo = read_dir(fd_dir);
  994         if(finfo != NULL){
  995                 file_count++;
  996                 //sw_printf("%s\n",(finfo->lname) != SPACE_VAL ? finfo->lname : 
  997                 //                finfo->name);
  998                 sw_printf("%s\n",finfo->name);
  999                 while(finfo != NULL){
 1000                         finfo = read_dir(fd_dir);
 1001                         if(finfo == NULL)
 1002                                 break;
 1003                         sw_printf("%s\n",finfo->name);
 1004                         file_count++;
 1005                 }
 1006         }
 1007         return file_count;
 1008 }
 1009 
 1017 file_stat * read_dir(int fd)
 1018 {
 1019         file_info *temp;
 1020         file_stat *stat;
 1021         dir_entry *entry;
 1022         
 1023         char lfn[LONG_FILE_NAME_LEN];
 1024         char sfn[FULL_SHRT_NAME_LEN];
 1025         int lfn_len = 0;
 1026         int ent_cnt = 0;
 1027         int lent_cnt = 0;
 1028         int index = 0;
 1029         int index1 = 0;
 1030         int read_count;
 1031         u8 *cur_entry;
 1032         u8 *strt_entry;
 1033         u32 cur_clus;
 1034         bool set_extn_lim = false;
 1035         temp = file_head;
 1036         
 1037         while(temp != NULL){
 1038                 if(temp->fd == fd)
 1039                         break;
 1040                 temp = temp->next;
 1041         }               
 1042         cur_entry = cluster_to_memory_addr(temp->cur_cluster) 
 1043                                                                                         + temp->cur_offset;     
 1044         
 1045         entry = sw_malloc(sizeof(dir_entry));
 1046         sw_memset(entry,SPACE_VAL,DIR_ENTRY_LEN);
 1047         read_count = file_read(fd,(char*)entry,DIR_ENTRY_LEN);
 1048         if(read_count == 0)
 1049                 return NULL;
 1050         while(*(entry->name) == FREE_DIR_ENTRY || *(entry->name) == DEL_DIR_ENTRY
 1051               || *(entry->name) == DOT_DIR_ENTRY){
 1052                 cur_entry = cluster_to_memory_addr(temp->cur_cluster) 
 1053                                                                                         + temp->cur_offset;
 1054                 read_count = file_read(fd,(char*)entry,DIR_ENTRY_LEN);
 1055                 if(read_count == 0)
 1056                         return NULL;
 1057         }
 1058         if(entry->attr == ATTR_LONG_FNAME){
 1059                 lfn_len = get_long_file_name(lfn,&cur_entry,&lent_cnt);
 1060                 lfn[lfn_len + 1] = '\0';
 1061                 sw_memset(entry,SPACE_VAL,DIR_ENTRY_LEN);
 1062                 temp->cur_offset += (lent_cnt - 1) * DIR_ENTRY_LEN;                     
 1063                 read_count = file_read(fd,entry,DIR_ENTRY_LEN);
 1064         }
 1065         
 1066         index = index1 = 0;
 1067         set_extn_lim = false;
 1068         while(index1 < SHRT_FILE_NAME_LEN){
 1069                 if((index1 == FILE_NAME_SHRT_LEN ||
 1070                    (*(u8 *)(entry + index1) == SPACE_VAL)) &&
 1071                    (*(u8*)(entry + FILE_NAME_SHRT_LEN) != SPACE_VAL)){
 1072                         if(!set_extn_lim){
 1073                                 sfn[index] = EXTN_DELIMITER;
 1074                                 set_extn_lim = true;
 1075                                 index++;
 1076                         }
 1077                 }
 1078                 while(*(u8 *)(entry + index1) == SPACE_VAL)
 1079                         index1++;
 1080                 sfn[index] = *(u8 *)(entry + index1);
 1081                 index1++;
 1082                 index++;
 1083         }
 1084         *(sfn + (index + 1)) = '\0';
 1085         stat = sw_malloc(sizeof(file_stat));
 1086         if(*lfn != SPACE_VAL){
 1087                 stat->lname = sw_malloc((lfn_len + 1) * sizeof(char));
 1088                 sw_strcpy(stat->lname,lfn);
 1089                 sw_strcpy(stat->name,entry->name);
 1090         }
 1091         else{
 1092                 sw_strcpy(stat->name,sfn);
 1093                 stat->lname = SPACE_VAL;
 1094         }
 1095         stat->size = entry->size;
 1096         stat->attr = entry->attr;
 1097         sw_memset(sfn,SPACE_VAL,SHRT_FILE_NAME_LEN);
 1098         sw_memset(lfn,SPACE_VAL,LONG_FILE_NAME_LEN);
 1099         sw_malloc_free(entry);
 1100         return stat;
 1101 }
 1102 
 1109 u32 allocate_cluster()
 1110 {
 1111         u32 new_cluster;
 1112         u8 *fat_offset;
 1113         u8 empty_cluster[BYTES_PER_CLUSTER_ENTRY];
 1114         sw_memset(empty_cluster,0,BYTES_PER_CLUSTER_ENTRY);
 1115         fat_offset = first_fat + ((nxt_free_cluster + 1)* BYTES_PER_CLUSTER_ENTRY);
 1116         while(!(sw_memcmp(fat_offset,empty_cluster,BYTES_PER_CLUSTER_ENTRY) == 0 )){
 1117                 fat_offset += BYTES_PER_CLUSTER_ENTRY;
 1118         }
 1119         new_cluster = (fat_offset - first_fat)/BYTES_PER_CLUSTER_ENTRY;
 1120         nxt_free_cluster = new_cluster;
 1121         *(u32 *)(fs_infosector + NXT_FREE_CLUS_OFF) = new_cluster;
 1122         return new_cluster;
 1123 }
 1124 
 1133 u8 * cluster_to_memory_addr(u32 cluster)
 1134 {
 1135         u8 *clus_addr;
 1136         clus_addr = root_directory + sec_size + ((cluster - 3) * sec_size);
 1137         return clus_addr;
 1138 }
 1139 
 1149 u32 get_fat_table_entry(u32 cluster)
 1150 {
 1151         u32 fat_entry;
 1152         fat_entry = *(u32*)(first_fat + (cluster * 4));
 1153         return fat_entry;
 1154 }
 1155 
 1165 void write_fat_table(u32 cluster,u32 value)
 1166 {
 1167         u8 *offset;
 1168         offset = first_fat + (cluster * 4);
 1169         *(u32*)(offset) = value;
 1170 }
 1171 
 1179 void convert_to_uppercase(char * file_name)
 1180 {
 1181         char *name = file_name;
 1182         int count = 0;
 1183         while(*name != '\0' && count++ < SHRT_FILE_NAME_LEN){
 1184                 *name = (*name >= 'a' && *name <= 'z') ? *name - ASCII_DIFF : *name;
 1185                 name++; 
 1186         }
 1187 }
 1188 
 1199 int find_depth(const char *file_path)
 1200 {
 1201         char *path = file_path;
 1202         int count = 0;
 1203         while(*path != '\0'){
 1204                 if(*path == DELIMITER)
 1205                         count++;
 1206                 path++;
 1207         }
 1208         return count;
 1209 }
 1210 
 1226 int get_seek_off(file_info * file_ptr,u32 strt_cluster,int offset)
 1227 { 
 1228         file_info *temp = file_ptr;
 1229         u32 cur_cluster = strt_cluster;
 1230         int tmp_off = offset;
 1231         int off_bytes;
 1232         u32 prev_cluster;
 1233         int clus_cnt = 0;
 1234         int alloc_clus_cnt = 0;
 1235         int bytes_traversed = 0;
 1236         int bytes_to_copy;
 1237 
 1238         if((offset + temp->cur_offset < cluster_size) && strt_cluster != 0){
 1239                 temp->cur_offset += offset;
 1240                 temp->cur_cluster = strt_cluster;
 1241                 return temp->cur_offset;
 1242         }
 1243         else{
 1244                 while(tmp_off > 0){
 1245                         if(cluster_size - temp->cur_offset != 0 && 
 1246                            cur_cluster != 0){
 1247                                 temp->cur_cluster = cur_cluster;
 1248                                 prev_cluster = cur_cluster;
 1249                                 bytes_to_copy = cluster_size -
 1250                                                 (offset - bytes_traversed);
 1251                                 bytes_to_copy = bytes_to_copy > 0 ?
 1252                                                 offset - bytes_traversed : 
 1253                                                 cluster_size;
 1254                                 bytes_to_copy = cluster_size - temp->cur_offset >
 1255                                                 bytes_to_copy ? bytes_to_copy :
 1256                                                 cluster_size - temp->cur_offset;                                
 1257                                 bytes_traversed += bytes_to_copy;
 1258                                 tmp_off -= bytes_to_copy;
 1259                                 temp->cur_offset += bytes_to_copy;
 1260                                 if(temp->cur_offset == cluster_size)
 1261                                         cur_cluster = get_fat_table_entry(cur_cluster);
 1262                                 if(cur_cluster != 0 && cur_cluster != END_OF_CLUSTER 
 1263                                    && cur_cluster != END_OF_ROOT_CLUSTER
 1264                                    && tmp_off != 0)
 1265                                         temp->cur_offset = 0;
 1266                                 clus_cnt++;                     
 1267                         }
 1268                         else{ 
 1269                                 if(cur_cluster == END_OF_CLUSTER || 
 1270                                    cur_cluster == 0 ||
 1271                                    cur_cluster == END_OF_ROOT_CLUSTER){
 1272                                         cur_cluster = allocate_cluster();           
 1273                                         if(alloc_clus_cnt != 0)
 1274                                                 write_fat_table(prev_cluster,cur_cluster);
 1275                                         alloc_clus_cnt++;
 1276                                 }
 1277                                 temp->cur_offset = 0;
 1278                         }
 1279                 }
 1280                 if(alloc_clus_cnt > 0)
 1281                         write_fat_table(temp->cur_cluster,END_OF_CLUSTER);
 1282                 off_bytes = ((clus_cnt -1)*cluster_size) + temp->cur_offset;
 1283         }
 1284         return off_bytes;
 1285 }
 1286 
 1296 void get_short_file_name(char * lfname,char *sfname,char seq_num)
 1297 {
 1298         char *start = lfname;
 1299         char *end = lfname;
 1300         int len = 0;
 1301         int extn_cnt = 0;
 1302         sw_memset(sfname,SPACE_VAL,SHRT_FILE_NAME_LEN);
 1303         while(*end != '\0')
 1304                 end++;
 1305         while(*end != EXTN_DELIMITER && end != start)
 1306                 end--;
 1307         while(*start != '\0' && len != 6){
 1308                 if(*start == EXTN_DELIMITER){ 
 1309                         if(start != end)
 1310                                 start++;
 1311                         else
 1312                                 break;
 1313                 }
 1314                 sfname[len] = *start;
 1315                 start++;
 1316                 len++;          
 1317         }
 1318         sfname[FNAME_EXTN_SEP_OFF] = TILDE;
 1319         sfname[FNAME_SEQ_NUM_OFF] = seq_num; 
 1320         len = FILE_NAME_SHRT_LEN;
 1321         while(*end != DELIMITER && *end != '\0' && extn_cnt != FILE_NAME_EXTN_LEN
 1322               && end != lfname){
 1323                 if(*end == EXTN_DELIMITER)
 1324                         end++;
 1325                 sfname[len] = *end;
 1326                 len++;
 1327                 end++;
 1328                 extn_cnt++;
 1329         }
 1330 }
 1331 
 1339 int chk_file_lock(const char *path)
 1340 {
 1341         file_info *temp; 
 1342         temp = file_head;
 1343         while(temp != NULL){
 1344                 if(sw_strcmp(temp->file_path,path) == 0 &&
 1345                    (temp->mode & FILE_WRITE)){
 1346                         sw_printf("File already opened in write mode\n");
 1347                         return -1;
 1348                 }
 1349                 temp = temp->next;
 1350         }
 1351         return 0;
 1352 }
 1353 
 1354 
 1365 u8 calc_check_sum(u8 * dir_entry)
 1366 {
 1367         int i;
 1368         u8 sum = 0;
 1369         for(i=0;i < SHRT_FILE_NAME_LEN; i++){
 1370                 sum = ((sum & 1) << 7) + (sum >> 1) + dir_entry[i];
 1371         }
 1372         return sum;
 1373 }
 1374 
 1382 int cal_req_dir_cnt(int file_name_len)
 1383 {
 1384         int req_cnt = 0;
 1385         int len = file_name_len;
 1386         while(len >= LFN_LEN_PER_ENTRY){
 1387                 len -= LFN_LEN_PER_ENTRY;
 1388                 req_cnt++;
 1389         }
 1390         req_cnt = len != 0 ? req_cnt++ : req_cnt;
 1391         return req_cnt;
 1392 }
 1393 
 1405 int file_truncate(const char* tr_pf,int tr_lgh)
 1406 {
 1407         u32 new_clstr,prev_clstr,*tr_addr;
 1408         u8 *cur_addr;
 1409         int sk_ted,end_size,tmp_tsize,wt_zo=0,zo_cnt=0,i=1;
 1410         char  buff[1024]={'\0'};
 1411         
 1412     file_info *tinfo= file_head;;
 1413 
 1414     if(tinfo == NULL) {
 1415         return -1;
 1416     }
 1417 
 1418         while((sw_strcmp(tinfo->file_path,tr_pf)) && tinfo != NULL) {
 1419         tinfo = tinfo->next;
 1420     }
 1421         
 1422     tr_addr=(u32)(tinfo->dir_entry_offset+28);
 1423 
 1424         if(*tr_addr==tinfo->file_size) {
 1425     *tr_addr=(u32)tr_lgh;
 1426         
 1427         if(tr_lgh>tinfo->file_size) {
 1428                 sk_ted=file_seek(tinfo->fd,0x00000000,FILE_SEEK_END);
 1429                 
 1430                 if(sk_ted!=-1) {
 1431 
 1432                         cur_addr=cluster_to_memory_addr(tinfo->cur_cluster)+
 1433                                                                            (u32)tinfo->cur_offset;
 1434                 end_size=tr_lgh-(int)(tinfo->file_size);
 1435                         tmp_tsize=end_size;
 1436                         while(end_size){
 1437                 wt_zo+=file_write(tinfo->fd,(const char*)&buff,end_size);
 1438                         --end_size;
 1439                         ++zo_cnt;
 1440                         }
 1441                         if(zo_cnt!=tmp_tsize && wt_zo==0) {
 1442                                 sw_printf("null bytes is not appended \n");
 1443                                 return -1;
 1444                         }
 1445                 }
 1446                 else {
 1447                         return -1;
 1448                 }
 1449         }
 1450 
 1451     tinfo->file_size=(u32)tr_lgh;
 1452     prev_clstr=tinfo->strt_cluster;
 1453 
 1454     if(tinfo->file_size==0) {
 1455         tinfo->cur_offset=(u16)(tinfo->file_size);
 1456         write_fat_table(prev_clstr,0x00000000);
 1457     }
 1458 
 1459     else if(tinfo->file_size>cluster_size){
 1460                 tinfo->cur_offset=(u16)(tinfo->file_size);
 1461     while(tinfo->cur_offset>cluster_size) {
 1462         new_clstr=allocate_cluster();
 1463                 tinfo->cur_offset=(u16)(tinfo->file_size-cluster_size);
 1464                 i=+1;
 1465         write_fat_table(prev_clstr,new_clstr);
 1466         prev_clstr=new_clstr;
 1467     }
 1468         write_fat_table(new_clstr,END_OF_CLUSTER);
 1469     }
 1470 
 1471     else {
 1472         tinfo->cur_offset=(u16)(tinfo->file_size);
 1473         write_fat_table(prev_clstr,END_OF_CLUSTER);
 1474     }
 1475 
 1476         tinfo->file_size=(u32)tr_lgh;
 1477         tinfo->entry->size=(u32)tr_lgh;
 1478     return 0;
 1479 }
 1480         return -1;
 1481 }
 1482 
 1492 int file_remove(const char *fl_name)
 1493 {
 1494         int fl_rem;
 1495         fl_rem=file_unlink(fl_name);
 1496         if(fl_rem!=0) {
 1497                 return -1;
 1498         }
 1499         return 0;
 1500 }
 1501 
 1511 int file_unlink(const char *ul_name)
 1512 {
 1513         u8 *rm_addr;
 1514     int fl_cls;
 1515     file_info *rinfo= file_head;
 1516     if(rinfo == NULL) {
 1517         return -1;
 1518     }
 1519    while((sw_strcmp(rinfo->file_path,ul_name)) && rinfo != NULL) {
 1520         rinfo = rinfo->next;
 1521     }
 1522     rm_addr=rinfo->dir_entry_offset;
 1523     *rm_addr = DEL_DIR_ENTRY;
 1524     fl_cls=file_close(rinfo->fd);
 1525     if(fl_cls!=0) {
 1526                 sw_printf("the file is not removed from the filesystem \n");
 1527         return -1;
 1528     }
 1529     return 0;
 1530 }
