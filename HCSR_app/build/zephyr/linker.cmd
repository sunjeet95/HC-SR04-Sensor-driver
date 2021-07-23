MEMORY
    {
    RAM (wx) : ORIGIN = 0x100000, LENGTH = 32768*1K
    IDT_LIST : ORIGIN = 2K, LENGTH = 2K
    }
  OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
  OUTPUT_ARCH("i386")
ENTRY("__start")
SECTIONS
 {
 .rel.plt :
 {
 *(.rel.plt)
 PROVIDE_HIDDEN (__rel_iplt_start = .);
 *(.rel.iplt)
 PROVIDE_HIDDEN (__rel_iplt_end = .);
 }
 .rela.plt :
 {
 *(.rela.plt)
 PROVIDE_HIDDEN (__rela_iplt_start = .);
 *(.rela.iplt)
 PROVIDE_HIDDEN (__rela_iplt_end = .);
 }
 .rel.dyn :
 {
 *(.rel.*)
 }
 .rela.dyn :
 {
 *(.rela.*)
 }
    /DISCARD/ :
 {
 *(.plt)
 }
    /DISCARD/ :
 {
 *(.iplt)
 }

 . = ALIGN(8);
 _image_rom_start = 0x100000;
 _image_text_start = 0x100000;
 text :
 {
 . = 0x0;
 *(.text_start)
 *(".text_start.*")
 *(.text)
 *(".text.*")
 *(.gnu.linkonce.t.*)
 *(.eh_frame_hdr)
 *(.eh_frame)
 *(.init)
 *(.fini)
 *(.eini)
 KEEP(*(.openocd_dbg))
 KEEP(*(".openocd_dbg.*"))

 } > RAM
 _image_text_end = .;
 _image_text_size = _image_text_end - _image_text_start;
 _image_rodata_start = .;
 app_shmem_regions :
 {
  __app_shmem_regions_start = .;
  KEEP(*(SORT(".app_regions.*")));
  __app_shmem_regions_end = .;
 } > RAM
 devconfig :
 {
  __devconfig_start = .;
  *(".devconfig.*")
  KEEP(*(SORT(".devconfig*")))
  __devconfig_end = .;
 } > RAM
 net_l2 :
 {
  __net_l2_start = .;
  *(".net_l2.init")
  KEEP(*(SORT(".net_l2.init*")))
  __net_l2_end = .;
 } > RAM
 log_const_sections :
 {
  __log_const_start = .;
  KEEP(*(SORT(.log_const_*)));
  __log_const_end = .;
 } > RAM
 log_backends_sections :
 {
  __log_backends_start = .;
  KEEP(*(".log_backends"));
  __log_backends_end = .;
 } > RAM
 shell_root_cmds_sections :
 {
  __shell_root_cmds_start = .;
  KEEP(*(SORT(.shell_root_cmd_*)));
  __shell_root_cmds_end = .;
 } > RAM
 font_entry_sections :
 {
  __font_entry_start = .;
  KEEP(*(SORT(".font_entry.*")))
  __font_entry_end = .;
 } > RAM
 rodata :
 {
 *(.rodata)
 *(".rodata.*")
 *(.gnu.linkonce.r.*)
 . = ALIGN(8);
 _idt_base_address = .;
 . += 256 * 8;
 . = ALIGN(4);
 _irq_to_interrupt_vector = .;
 . += 128;
 } > RAM

 _image_rom_end = .;
 _image_rom_size = _image_rom_end - _image_rom_start;
 _image_rodata_end = _image_rom_end;
 _image_rodata_size = _image_rodata_end - _image_rodata_start;

 /DISCARD/ : {
  *(.got.plt)
  *(.igot.plt)
  *(.got)
  *(.igot)
 }

 bss (NOLOAD) :
 {

 _image_ram_start = .;
 . = ALIGN(4);
 __kernel_ram_start = .;
 __bss_start = .;
 *(.bss)
 *(".bss.*")
 *(COMMON)
 *(".kernel_bss.*")
 . = ALIGN(4);
 __bss_end = .;
 } > RAM
 __bss_num_words = (__bss_end - __bss_start) >> 2;
 noinit (NOLOAD) :
 {
 *(.noinit)
 *(".noinit.*")
 *(".kernel_noinit.*")

 } > RAM
 datas :
 {
 __data_ram_start = .;
 *(.data)
 *(".data.*")
 *(".kernel.*")
 . = ALIGN(4);
 } > RAM
 __data_rom_start = LOADADDR(datas);
 initlevel :
 {
  __device_init_start = .; __device_PRE_KERNEL_1_start = .; KEEP(*(SORT(.init_PRE_KERNEL_1[0-9]))); KEEP(*(SORT(.init_PRE_KERNEL_1[1-9][0-9]))); __device_PRE_KERNEL_2_start = .; KEEP(*(SORT(.init_PRE_KERNEL_2[0-9]))); KEEP(*(SORT(.init_PRE_KERNEL_2[1-9][0-9]))); __device_POST_KERNEL_start = .; KEEP(*(SORT(.init_POST_KERNEL[0-9]))); KEEP(*(SORT(.init_POST_KERNEL[1-9][0-9]))); __device_APPLICATION_start = .; KEEP(*(SORT(.init_APPLICATION[0-9]))); KEEP(*(SORT(.init_APPLICATION[1-9][0-9]))); __device_init_end = .;
 } > RAM
 initlevel_error :
 {
  KEEP(*(SORT(.init_[_A-Z0-9]*)))
 }
 ASSERT(SIZEOF(initlevel_error) == 0, "Undefined initialization levels used.")
 initshell :
 {
  __shell_module_start = .; KEEP(*(".shell_module_*")); __shell_module_end = .; __shell_cmd_start = .; KEEP(*(".shell_cmd_*")); __shell_cmd_end = .;
 } > RAM
 log_dynamic_sections :
 {
  __log_dynamic_start = .;
  KEEP(*(SORT(.log_dynamic_*)));
  __log_dynamic_end = .;
 } > RAM
 _static_thread_area : SUBALIGN(4)
 {
  _static_thread_data_list_start = .;
  KEEP(*(SORT("._static_thread_data.static.*")))
  _static_thread_data_list_end = .;
 } > RAM
 _k_timer_area : SUBALIGN(4)
 {
  _k_timer_list_start = .;
  KEEP(*("._k_timer.static.*"))
  _k_timer_list_end = .;
 } > RAM
 _k_mem_slab_area : SUBALIGN(4)
 {
  _k_mem_slab_list_start = .;
  KEEP(*("._k_mem_slab.static.*"))
  _k_mem_slab_list_end = .;
 } > RAM
 _k_mem_pool_area : SUBALIGN(4)
 {
  _k_mem_pool_list_start = .;
  KEEP(*("._k_mem_pool.static.*"))
  _k_mem_pool_list_end = .;
 } > RAM
 _k_sem_area : SUBALIGN(4)
 {
  _k_sem_list_start = .;
  KEEP(*("._k_sem.static.*"))
  _k_sem_list_end = .;
 } > RAM
 _k_mutex_area : SUBALIGN(4)
 {
  _k_mutex_list_start = .;
  KEEP(*("._k_mutex.static.*"))
  _k_mutex_list_end = .;
 } > RAM
 _k_queue_area : SUBALIGN(4)
 {
  _k_queue_list_start = .;
  KEEP(*("._k_queue.static.*"))
  _k_queue_list_end = .;
 } > RAM
 _k_stack_area : SUBALIGN(4)
 {
  _k_stack_list_start = .;
  KEEP(*("._k_stack.static.*"))
  _k_stack_list_end = .;
 } > RAM
 _k_msgq_area : SUBALIGN(4)
 {
  _k_msgq_list_start = .;
  KEEP(*("._k_msgq.static.*"))
  _k_msgq_list_end = .;
 } > RAM
 _k_mbox_area : SUBALIGN(4)
 {
  _k_mbox_list_start = .;
  KEEP(*("._k_mbox.static.*"))
  _k_mbox_list_end = .;
 } > RAM
 _k_pipe_area : SUBALIGN(4)
 {
  _k_pipe_list_start = .;
  KEEP(*("._k_pipe.static.*"))
  _k_pipe_list_end = .;
 } > RAM
 _net_buf_pool_area : SUBALIGN(4)
 {
  _net_buf_pool_list = .;
  KEEP(*(SORT("._net_buf_pool.static.*")))
 } > RAM
 net_if : SUBALIGN(4)
 {
  __net_if_start = .;
  *(".net_if.*")
  KEEP(*(SORT(".net_if.*")))
  __net_if_end = .;
 } > RAM
 net_if_dev : SUBALIGN(4)
 {
  __net_if_dev_start = .;
  *(".net_if_dev.*")
  KEEP(*(SORT(".net_if_dev.*")))
  __net_if_dev_end = .;
 } > RAM
 net_l2_data : SUBALIGN(4)
 {
  __net_l2_data_start = .;
  *(".net_l2.data")
  KEEP(*(SORT(".net_l2.data*")))
  __net_l2_data_end = .;
 } > RAM

 __data_ram_end = .;
 __kernel_ram_end = 0x100000 + ((32768) << 10);
 __kernel_ram_size = __kernel_ram_end - __kernel_ram_start;
 _image_ram_end = .;
 _image_ram_all = (0x100000 + ((32768) << 10)) - _image_ram_start;
 _end = .;

 intList :
 {
 KEEP(*(.spurIsr))
 KEEP(*(.spurNoErrIsr))
 KEEP(*(.intList))
 KEEP(*(.gnu.linkonce.intList.*))
 } > IDT_LIST
 .stab 0 : { *(.stab) }
 .stabstr 0 : { *(.stabstr) }
 .stab.excl 0 : { *(.stab.excl) }
 .stab.exclstr 0 : { *(.stab.exclstr) }
 .stab.index 0 : { *(.stab.index) }
 .stab.indexstr 0 : { *(.stab.indexstr) }
 .gnu.build.attributes 0 : { *(.gnu.build.attributes .gnu.build.attributes.*) }
 .comment 0 : { *(.comment) }
 .debug 0 : { *(.debug) }
 .line 0 : { *(.line) }
 .debug_srcinfo 0 : { *(.debug_srcinfo) }
 .debug_sfnames 0 : { *(.debug_sfnames) }
 .debug_aranges 0 : { *(.debug_aranges) }
 .debug_pubnames 0 : { *(.debug_pubnames) }
 .debug_info 0 : { *(.debug_info .gnu.linkonce.wi.*) }
 .debug_abbrev 0 : { *(.debug_abbrev) }
 .debug_line 0 : { *(.debug_line .debug_line.* .debug_line_end ) }
 .debug_frame 0 : { *(.debug_frame) }
 .debug_str 0 : { *(.debug_str) }
 .debug_loc 0 : { *(.debug_loc) }
 .debug_macinfo 0 : { *(.debug_macinfo) }
 .debug_weaknames 0 : { *(.debug_weaknames) }
 .debug_funcnames 0 : { *(.debug_funcnames) }
 .debug_typenames 0 : { *(.debug_typenames) }
 .debug_varnames 0 : { *(.debug_varnames) }
 .debug_pubtypes 0 : { *(.debug_pubtypes) }
 .debug_ranges 0 : { *(.debug_ranges) }
 .debug_macro 0 : { *(.debug_macro) }
 /DISCARD/ : { *(.note.GNU-stack) }
 }
