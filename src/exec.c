#include <ichor/elf.h>
#include <ichor/syscalls.h>
#include <ichor/vm.h>

int ichor_exec_elf(Task *task, uint8_t *elf_buffer)
{
    Elf64Header *header = (Elf64Header *)elf_buffer;
    Elf64ProgramHeader *program_header = (Elf64ProgramHeader *)(elf_buffer + header->e_phoff);

    if (header->e_ident[0] != ELFMAG0 ||
        header->e_ident[1] != ELFMAG1 ||
        header->e_ident[2] != ELFMAG2 ||
        header->e_ident[3] != ELFMAG3)
    {
        return ERR_INVALID_PARAMETERS;
    }

    if (header->e_type != ET_EXEC)
    {
        return ERR_INVALID_PARAMETERS;
    }

    for (int i = 0; i < header->e_phnum; i++)
    {
        if (program_header->p_type == PT_LOAD)
        {
            size_t misalign = program_header->p_vaddr & (4096 - 1);
            size_t page_count = DIV_CEIL(misalign + program_header->p_memsz, 4096);

            VmObject obj = sys_vm_create(page_count * 4096, 0, 0);
            sys_vm_map(task->space, &obj, VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXEC, program_header->p_vaddr, VM_MAP_FIXED);
            sys_vm_write(task->space, program_header->p_vaddr, (void *)(elf_buffer + program_header->p_offset), program_header->p_filesz);
        }

        program_header = (Elf64ProgramHeader *)((uint8_t *)program_header + header->e_phentsize);
    }

    sys_start_task(task, header->e_entry);

    return ERR_SUCCESS;
}