ENTRY(start)

SECTIONS
{
    /* You must load the kernel at 1MB or higher */
    . = 1M;

    .text BLOCK(4K) : ALIGN(4K)
    {
        /* CRITICAL: Force the multiboot header to the front! */
        *(.multiboot)
        *(.text)
    }

    /* Read-only data. */
    .rodata BLOCK(4K) : ALIGN(4K)
    {
        *(.rodata)
    }

    /* Read-write data (initialized) */
    .data BLOCK(4K) : ALIGN(4K)
    {
        *(.data)
    }

    /* Read-write data (uninitialized) and stack */
    .bss BLOCK(4K) : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
}
