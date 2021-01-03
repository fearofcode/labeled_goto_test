#define OP_HALT     0x0
#define OP_INC      0x1
#define OP_DEC      0x2
#define OP_MUL2     0x3
#define OP_DIV2     0x4
#define OP_ADD7     0x5
#define OP_NEG      0x6

#include <benchmark/benchmark.h>

int interp_switch(const unsigned char* code, int initval) {
    int pc = 0;
    int val = initval;

    while (true) {
        switch (code[pc++]) {
            case OP_HALT:
                return val;
            case OP_INC:
                val++;
                break;
            case OP_DEC:
                val--;
                break;
            case OP_MUL2:
                val *= 2;
                break;
            case OP_DIV2:
                val /= 2;
                break;
            case OP_ADD7:
                val += 7;
                break;
            case OP_NEG:
                val = -val;
                break;
            default:
                return val;
        }
    }
}

static void BM_SwitchTable(benchmark::State& state) {
    unsigned char code[] = {
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_HALT
    };
    for (auto _ : state) {
        benchmark::DoNotOptimize(interp_switch(code, 42));
    }
}
BENCHMARK(BM_SwitchTable);

int interp_cgoto(const unsigned char* code, int initval) {
    static void* dispatch_table[] = {
            &&do_halt, &&do_inc, &&do_dec, &&do_mul2,
            &&do_div2, &&do_add7, &&do_neg};

    int pc = 0;
    int val = initval;

    #define DISPATCH() goto *dispatch_table[code[pc++]]

    DISPATCH();
    while (true) {
        do_halt:
            return val;
        do_inc:
            val++;
            DISPATCH();
        do_dec:
            val--;
            DISPATCH();
        do_mul2:
            val *= 2;
            DISPATCH();
        do_div2:
            val /= 2;
            DISPATCH();
        do_add7:
            val += 7;
            DISPATCH();
        do_neg:
            val = -val;
            DISPATCH();
    }
}

static void BM_ComputedGoto(benchmark::State& state) {
    unsigned char code[] = {
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_INC, OP_INC, OP_DEC, OP_MUL2, OP_DEC, OP_ADD7, OP_DIV2, OP_INC, OP_DEC,
            OP_HALT
    };
    for (auto _ : state) {
        benchmark::DoNotOptimize(interp_cgoto(code, 42));
    }
}
BENCHMARK(BM_ComputedGoto);

BENCHMARK_MAIN();