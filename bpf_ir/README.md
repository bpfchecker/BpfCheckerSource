# bpf ir

# Quick Build for Program Generator

```
mkdir build && cd build
cmake .. && make generator
# you'll get generator binary under build/generator directory
```
generator usage:
```
Usage: Bpf Program Generator [options] 

Optional arguments:
-h --help                       shows help message and exits [default: false]
-v --version                    prints version information and exits [default: false]
-o --output                     specify the output directory. [required]
-n --number                     numbers of program to generate. [default: 1000]
--action_size                   specify the action size. [default: 10]
-g --generation_strategy        specify the generation strategy (alu, mem, jmp, program, all). [default: "program"]
-t --generation_target          specify the generation target (rbpf, ubpf). [default: "rbpf"]
```
e.g., the following command will generate 1000 programs with 10 action size, under the `output` directory.
```
./generator/generator -o ./output/ --number 1000 --action_size 10
```