/* Daniel's Idiot friendly bare metal ARM linker script */
OUTPUT_ARCH(arm)
ENTRY(_start)

SECTIONS {
	/* Stores code and stuff */
	. = ALIGN(4);
	.text : {
		_text_start = .;
		*(.text)
		_text_end = .;
	}

	. = ALIGN(4);
	.rodata : {
		_rodata_start = .;
		*(.rodata*)
		_rodata_end = .;
	}

	/* Block starting symbol, for unitialized global arrays */
	. = ALIGN(4);
	.bss : {
		_bss_start = .;
		*(.bss*)
		_bss_end = .;
	}

	. = ALIGN(4);
	.got : {
		_got_start = .;
		*(.got*)
		_got_end = .;
	}

	/* Regular data */
	. = ALIGN(4);
	.data : {
		_data_start = .;
		*(.data*)
		_data_end = .;
	}

	/* Regular data */
	. = ALIGN(4);
	.symtab : {
		_data_start = .;
		*(.symtab*)
		_data_end = .;
	}

		/* Regular data */
	. = ALIGN(4);
	.strtab : {
		*(.strtab*)
	}

	/* The data will be appended */
	_symbol_table_start = .;
}
