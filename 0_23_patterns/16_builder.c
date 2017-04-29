typedef struct _AssemblePersonalComputer
{
    void (*assemble_cpu)();
    void (*assemble_memory)();
    void (*assemble_harddisk)();
} AssemblePersonalComputer;

// (1)
void assemble_intel_cpu()
{
    printf("intel cpu!\n");
}

void assemble_samsumg_memory()
{
    printf("samsung memory!\n");
}

void assemble_hitachi_harddisk()
{
    printf("hitachi harddisk!\n");
}

// (2)
void assemble_amd_cpu()
{
    printf("amd cpu!\n");
}

void assemble_kingston_memory()
{
    printf("kingston memory!\n");
}

void assemble_wd_harddisk()
{
    printf("wd harddisk!\n");
}
