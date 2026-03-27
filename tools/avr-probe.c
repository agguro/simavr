#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include "sim_avr.h"

extern avr_kind_t * avr_kind[];

void terminal_print_safe(const char *name) {
    if (!name) return;
    for (int i = 0; name[i] != '\0'; i++) {
        unsigned char c = (unsigned char)name[i];
        if (isprint(c)) putchar(c);
    }
}

void show_help(char *bin_name) {
    printf("Usage: %s [options]\n", bin_name);
    printf("Options:\n");
    printf("  -l, --list             List all supported MCU names\n");
    printf("  -a, --all              List all MCUs AND their peripherals (Big output!)\n");
    printf("  -m, --mcu <name>       Show detailed info/peripherals for a specific MCU\n");
    printf("  -s, --search <term>    Find MCUs containing a specific peripheral/IRQ\n");
    printf("  -h, --help             Show this menu\n");
}

void audit_mcu(const char *name, int verbose, const char *search_term) {
    avr_t * avr = avr_make_mcu_by_name(name);
    if (!avr) return;
    avr_init(avr);

    int match = 0;
    if (search_term) {
        for (int j = 0; j < avr->irq_pool.count; j++) {
            if (avr->irq_pool.irq[j] && avr->irq_pool.irq[j]->name) {
                if (strstr(avr->irq_pool.irq[j]->name, search_term)) {
                    match = 1; break;
                }
            }
        }
    }

    if (!search_term || match) {
        printf("\033[1;32m[%s]\033[0m", avr->mmcu);
        if (verbose || match) {
            printf("\n  Flash: 0x%04x | SRAM: 0x%04x\n", avr->flashend, avr->ramend);
            for (int j = 0; j < avr->irq_pool.count; j++) {
                struct avr_irq_t * irq = avr->irq_pool.irq[j];
                if (irq && irq->name && !strstr(irq->name, ".pending") && !strstr(irq->name, ".running")) {
                    if (!search_term || strstr(irq->name, search_term)) {
                        printf("    - ");
                        terminal_print_safe(irq->name);
                        putchar('\n');
                    }
                }
            }
        } else {
            printf("\n");
        }
    }
    avr_terminate(avr);
}

int main(int argc, char *argv[]) {
    int opt;
    static struct option long_options[] = {
        {"list",   no_argument,       0, 'l'},
        {"all",    no_argument,       0, 'a'},
        {"mcu",    required_argument, 0, 'm'},
        {"search", required_argument, 0, 's'},
        {"help",   no_argument,       0, 'h'},
        {0, 0, 0, 0}
    };

    if (argc < 2) { show_help(argv[0]); return 0; }

    while ((opt = getopt_long(argc, argv, "lam:s:h", long_options, NULL)) != -1) {
        int i = 0;
        switch (opt) {
            case 'l':
                while (avr_kind[i]) { printf("  - %s\n", avr_kind[i++]->names[0]); }
                break;
            case 'a':
                while (avr_kind[i]) { audit_mcu(avr_kind[i++]->names[0], 1, NULL); }
                break;
            case 'm':
                audit_mcu(optarg, 1, NULL);
                break;
            case 's':
                printf("Searching for cores with '%s'...\n", optarg);
                while (avr_kind[i]) { audit_mcu(avr_kind[i++]->names[0], 0, optarg); }
                break;
            case 'h':
            default:
                show_help(argv[0]);
                return 0;
        }
    }
    return 0;
}
