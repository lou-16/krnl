#include "args.h"
// TODO: finish this work
struct __boot_args__ boot_args;

char* args_list[BOOT_MAX_ARGS] = 
{
    "--hardware",
    "--vga-text",
    "--bga-fb"
};

struct __boot_args__* parse_boot_args(uint32_t* cli_args){
    char* boot_arg_string = (char*)(*cli_args);
    int i = 0;
    boot_args.display_mode = DM_BOCHS;
    boot_args.real_hardware = false;

    while(boot_arg_string[i] != '\0')
    {
        if(boot_arg_string[i] == ' ') {i++; continue;}
        if(is_valid_arg(&boot_arg_string[i], args_list[0], &i)){
            boot_args.real_hardware = true;
        }
        if(is_valid_arg(&boot_arg_string[i], args_list[1], &i)){
            boot_args.display_mode = DM_VGA_TEXT;
        } 
        if(is_valid_arg(&boot_arg_string[i], args_list[2], &i)) {
            boot_args.display_mode = DM_BOCHS;
        }
        i++;
    }
    return &boot_args;

}

bool is_valid_arg(uint8_t* token, uint8_t* arg, int* accumulator)
{
    int i = 0;
    while(arg[i] != '\0')
    {
        if(token[i] != '\0' && arg[i] == '\0') return false;
        // premature end of line
        if(token[i] == '\0' && arg[i] != '\0') return false;
        
        // premature end of token
        if(token[i] == ' ' || token[i] != '\0') return false;
        
        // if token and arg mismatch
        if(token[i] != arg[i]) return false;
  
        // move on to next iteration
        i++;
    }
    *accumulator += i;
    return true;
}